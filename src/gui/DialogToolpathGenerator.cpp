///////////////////////////////////////////////////////////////////////////////
// Name               : DialogToolpathGenerator.cpp
// Purpose            : Dialog to add, update and delete toolpath generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#include "DialogToolpathGenerator.h"

#include "../project/generator/GeneratorFactory.h"

#include "../project/command/CommandRunGeneratorAdd.h"
#include "../project/command/CommandRunGeneratorUpdate.h"
#include "../project/command/CommandRunGeneratorDelete.h"
#include "CollectionUnits.h"
#include "FrameParent.h"
#include "FrameMain.h"
#include "IDs.h"

DialogToolpathGenerator::DialogToolpathGenerator(wxWindow* parent) :
		GUIToolpathGenerator(parent)
{
	runID = 0;
	generatorID = 0;
	localGenerator = NULL;
	TransferDataToWindow();
}

DialogToolpathGenerator::~DialogToolpathGenerator()
{
	if(localGenerator != NULL) delete localGenerator;
}

void DialogToolpathGenerator::OnXClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogToolpathGenerator::SetRunGenerator(size_t runID, size_t generatorID)
{
	std::cout << "DialogToolpathGenerator::SetRunGenerator(" << runID << ", "
			<< generatorID << ")\n";
	const bool updatePanel = (runID != this->runID
			|| this->generatorID != generatorID);
	this->runID = runID;
	this->generatorID = generatorID;

	TransferDataToWindow(updatePanel);
}

bool DialogToolpathGenerator::TransferDataToWindow(bool updateGeneratorPanel)
{
	if(loopguard.TryLock() == wxMUTEX_BUSY){
//		std::cout
//				<< "DialogToolpathGenerator::TransferDataToWindow - wxMUTEX_BUSY.\n";
		return false;
	}
//	std::cout
//			<< "DialogToolpathGenerator::TransferDataToWindow - loopguard.Lock()\n";

	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	m_staticTextUnitSpindle->SetLabel(settings->RotationalSpeed.GetOtherName());
	m_staticTextUnitFeed->SetLabel(settings->LinearSpeed.GetOtherName());
	m_staticTextUnitMarginBelow->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitMarginSide->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitFreeHeight->SetLabel(
			settings->SmallDistance.GetOtherName());

	Project* project = wxStaticCast(frame->GetDocument(), Project);

	wxArrayString newTools;
	for(size_t n = 0; n < project->GetToolCount(); ++n){
		const Tool & tool = project->GetTool(n);
		newTools.Add(
				wxString::Format(_T("T%zu - "), tool.postprocess.number)
						+ tool.description);
	}
	wxArrayString oldTools = m_choiceTool->GetStrings();
	if(oldTools != newTools) m_choiceTool->Set(newTools);

	if(!project->Has(
			Selection(Selection::BaseRun, runID, Selection::Generator,
					generatorID))){
		SetTitle(_T(""));
		m_textCtrlGeometry->SetValue(_T(""));
		m_choiceTool->SetSelection(wxNOT_FOUND);
		m_textCtrlSpindle->SetValue(_T(""));
		m_textCtrlFeed->SetValue(_T(""));
		m_textCtrlFreeHeight->SetValue(_T(""));
		m_textCtrlMarginBelow->SetValue(_T(""));
		m_textCtrlMarginSide->SetValue(_T(""));
		m_textCtrlInfo->SetValue(_T(""));

		loopguard.Unlock();
//		std::cout
//				<< "DialogToolpathGenerator::TransferDataToWindow - loopguard.Unlock()\n";
		return false;
	}
	const Run & run = project->GetRun(runID);
	const Generator & generator = *(run.generators.at(generatorID));

	SetTitle(generator.GetName());

	bufferarea = generator.area;
	m_textCtrlGeometry->SetValue(generator.area.ToString());
	int m = -1;
	for(size_t n = 0; n < project->GetToolCount(); ++n){
		if(project->GetTool(n).guid.compare(generator.toolguid) == 0){
			m = n;
			break;
		}
	}
	m_choiceTool->SetSelection(m);
	m_textCtrlSpindle->SetValue(
			settings->RotationalSpeed.TextFromSI(generator.spindlespeed));
	m_textCtrlFeed->SetValue(
			settings->LinearSpeed.TextFromSI(generator.feedrate));
	m_textCtrlMarginBelow->SetValue(
			settings->SmallDistance.TextFromSI(generator.marginBelow));
	m_textCtrlMarginSide->SetValue(
			settings->SmallDistance.TextFromSI(generator.marginSide));
	m_textCtrlFreeHeight->SetValue(
			settings->SmallDistance.TextFromSI(generator.freeHeight));

	if(updateGeneratorPanel){
		std::cout
				<< "DialogToolpathGenerator::TransferDataToWindow - updatePanel == true\n";

		m_panel->Freeze();
		m_panel->DestroyChildren();
		if(localGenerator != NULL) delete localGenerator;
		localGenerator = GeneratorFactory::NewGenerator(generator.GetType());
		wxSizer * temp = localGenerator->AddToPanel(m_panel, settings);
		m_panel->SetSizer(temp, true);
		m_scrolledWindow->Layout();
		temp->Fit(m_panel);
		this->Layout();
		m_panel->Thaw();
//		wxWindowList& list = m_panel->GetChildren();
	}
	localGenerator->CopyParameterFrom(&generator);
	localGenerator->TransferDataToPanel(m_panel, settings);
	loopguard.Unlock();
//	std::cout
//			<< "DialogToolpathGenerator::TransferDataToWindow - loopguard.Unlock()\n";
	return true;
}

bool DialogToolpathGenerator::TransferDataFromWindow(
		Generator * generator) const
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	if(!project->Has(
			Selection(Selection::BaseRun, runID, Selection::Generator,
					generatorID))) return false;
	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	generator->TransferDataFromPanel(settings);
	generator->area = bufferarea;
	const int m = m_choiceTool->GetSelection();
	if(m == wxNOT_FOUND || m < 0 || m >= project->GetToolCount()){
		generator->toolguid.clear();
	}else{
		generator->toolguid = project->GetTool(m).guid;
	}
	generator->spindlespeed = settings->RotationalSpeed.SIFromString(
			m_textCtrlSpindle->GetValue());
	generator->feedrate = settings->LinearSpeed.SIFromString(
			m_textCtrlFeed->GetValue());
	generator->marginSide = settings->SmallDistance.SIFromString(
			m_textCtrlMarginSide->GetValue());
	generator->marginBelow = settings->SmallDistance.SIFromString(
			m_textCtrlMarginBelow->GetValue());
	generator->freeHeight = settings->SmallDistance.SIFromString(
			m_textCtrlFreeHeight->GetValue());

	return true;
}

bool DialogToolpathGenerator::UpdateGenerator(void)
{
	if(loopguard.TryLock() == wxMUTEX_BUSY) return false;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	if(!project->Has(
			Selection(Selection::BaseRun, runID, Selection::Generator,
					generatorID))){
		loopguard.Unlock();
		return false;
	}
	const Run & run = project->GetRun(runID);
	const Generator & generator = *(run.generators.at(generatorID));
	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	TransferDataFromWindow(localGenerator);

	if(generator == *localGenerator){
		std::cout << "DialogToolpathGenerator::UpdateGenerator - no changes.\n";
		loopguard.Unlock();
		return false;
	}

	Generator * temp = GeneratorFactory::NewGenerator(generator.GetType());
	temp->CopyParameterFrom(localGenerator);

	wxCommandProcessor * cmdProc = project->GetCommandProcessor();
	cmdProc->Submit(
			new CommandRunGeneratorUpdate(_("Update the generator settings."),
					project, runID, generatorID, temp));

	loopguard.Unlock();
	TransferDataToWindow();
	return true;
}

void DialogToolpathGenerator::OnSelectArea(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//		if(!project->Has(
//				Selection(Selection::BaseRun, runID, Selection::Generator,
//						generatorID)))
//			return;
//		const Run & run = project->GetRun(runID);

	frame->RequestSelection(this, event.GetId(), false,
			Selection(Selection::VertexGroup),
			Selection(Selection::TriangleGroup));
}

void DialogToolpathGenerator::OnChar(wxKeyEvent& event)
{
	std::cout << "DialogToolpathGenerator::OnChar\n";
	if(event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_TAB){
		this->UpdateGenerator();
		Refresh();
		return;
	}
	if(event.GetKeyCode() == WXK_ESCAPE){
		this->TransferDataToWindow();
		Refresh();
		return;
	}
	event.Skip();
}

void DialogToolpathGenerator::OnLeftDown(wxMouseEvent& event)
{
	std::cout << "DialogToolpathGenerator::OnLeftDown\n";
	event.Skip();
}

bool DialogToolpathGenerator::OnSelected(size_t ID, Selection selection)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();

	if(!project->Has(
			Selection(Selection::BaseRun, runID, Selection::Generator,
					generatorID))) return false;
	if(ID != ID_SELECTAREAOBJECT){
		std::cout
				<< "DialogToolpathGenerator::OnSelected(...) -> unhandled ID: "
				<< ID << "\n";
		return false;
	}
	std::cout << "DialogToolpathGenerator::OnSelected(" << ID << ", "
			<< selection.ToString() << ")";
	bufferarea = selection;
	this->Show();
	this->UpdateGenerator();
	Refresh();
	return true;
}

void DialogToolpathGenerator::OnSelectTool(wxCommandEvent& event)
{
//	TransferDataFromWindow();
//	const int toolNr = m_choiceTool->GetSelection() - 1;
//	if(currentRun >= 0 && toolNr >= 0){
//		slotNr = toolNr;
//	}else{
//		slotNr = 0;
//	}
	UpdateGenerator();
	Refresh();
}

//void DialogToolpathGenerator::OnUpdate(wxCommandEvent& event)
//{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
//	TransferDataFromWindow();
//	int runNr = m_choiceRun->GetSelection() - 1;
//	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
//	if(runNr < 0 || toolpathNr < 0) return;
//	int generatorNr = m_choicebookGenerator->GetSelection();
//
//	Generator * temp = gc.NewGenerator(generatorNr);
//	temp->CopyParameterFrom(gc.generators[generatorNr]);
//	temp->area = box;
//	temp->marginBelow = marginBelow;
//	temp->marginSide = marginSides;
//	temp->refTool = slotNr;
//	temp->freeHeight = freeHeight;
//
//	cmdProc->Submit(
//			new CommandRunGeneratorUpdate(
//			_("Update generator on run ") + project->run[runNr].name,
//					project, runNr, toolpathNr, temp));
//
//	for(size_t i = 0; i < project->run[runNr].generators.GetCount(); i++){
//		project->run[runNr].generators[i]->selected = (i == toolpathNr);
//	}
//
//	TransferDataToWindow();
//
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
//	ID_REFRESHVIEW);
//	ProcessEvent(selectEvent);
//}

void DialogToolpathGenerator::OnTextEnter(wxCommandEvent& event)
{
	std::cout << "DialogToolpathGenerator::OnTextEnter - ID=" << event.GetId()
			<< "  text=" << event.GetString() << "\n";

	UpdateGenerator();
	Refresh();

//	bool haschanged = true;
//	switch(event.GetId()){
//	case ID_SPEED:
//
//		break;
//	case ID_FEED:
//		break;
//	case ID_MARGINSIDE:
//		break;
//	case ID_MARGINBELOW:
//		break;
//	case ID_CLEARANCEHEIGHT:
//		break;
//	default:
//		haschanged = false;
//	}
//	if(haschanged) TransferDataFromWindow();
}

void DialogToolpathGenerator::OnUpdate(wxCommandEvent& event)
{
	UpdateGenerator();
	Refresh();
}

size_t DialogToolpathGenerator::GetRunID(void) const
{
	return runID;
}
