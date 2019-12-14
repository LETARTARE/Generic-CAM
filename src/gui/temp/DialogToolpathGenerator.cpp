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

#include "../project/command/CommandRunGeneratorAdd.h"
#include "../project/command/CommandRunGeneratorDelete.h"
#include "../project/command/CommandRunGeneratorUpdate.h"
#include "CollectionUnits.h"
#include "FrameMain.h"
#include "FrameParent.h"
#include "IDs.h"

DialogToolpathGenerator::DialogToolpathGenerator(wxWindow* parent) :
		GUIToolpathGenerator(parent)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	loopGuard = false;

	currentRun = -1;
	currentToolpath = -1;
	marginSides = 0.0;
	marginBelow = 0.0;
	box.Clear();
	slotNr = 0;
	freeHeight = 0.001;
	// Assign pages to the choicebook for every generator
	wxString generatorName;
	for(size_t i = 0; i < gc.GetCount(); i++){
		generatorName = gc.generators[i]->GetName();
		wxPanel * panel = new wxPanel(m_choicebookGenerator, wxID_ANY,
				wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		gc.generators[i]->AddToPanel(panel, settings);
		m_choicebookGenerator->AddPage(panel, generatorName, (i == 0));
	}
	TransferDataToWindow();
}

DialogToolpathGenerator::~DialogToolpathGenerator()
{
}

bool DialogToolpathGenerator::TransferDataToWindow(void)
{
	if(loopGuard) return false;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	int selectedRun = -1;
	for(size_t i = 0; i < project->run.GetCount(); i++){
		if(selectedRun == -1 && project->run[i].selected) selectedRun = i;
	}
	int selectedToolpath = -1;
	if(selectedRun >= 0){
		for(size_t i = 0; i < project->run[selectedRun].generators.GetCount();
				i++){
			if(selectedToolpath == -1
					&& (*(project->run[selectedRun].generators[i])).selected) selectedToolpath =
					i;
		}
	}

	if(project->run.GetCount() + 1 != m_choiceRun->GetCount()){
		currentRun = -2;
	}

	loopGuard = true;

	wxArrayString newRuns;
	newRuns.Add(_T(""));
	for(size_t i = 0; i < project->run.GetCount(); i++)
		newRuns.Add(project->run[i].name);
	wxArrayString oldRuns = m_choiceRun->GetStrings();
	if(oldRuns != newRuns) m_choiceRun->Set(newRuns);

	if(selectedRun != currentRun) m_choiceRun->SetSelection(selectedRun + 1);

	wxArrayString newTools;
	newTools.Add(_T(""));
	if(selectedRun >= 0){

		for(int n = 0; n < project->run[selectedRun].machine.tools.GetCount();
				n++){
			newTools.Add(
					wxString::Format(_T("T%i - "), n + 1)
							+ project->run[selectedRun].machine.tools[n].toolName);
		}
	}

	wxArrayString oldTools = m_choiceTool->GetStrings();
	if(oldTools != newTools) m_choiceTool->Set(newTools);

	loopGuard = false;

	if(selectedRun != currentRun || selectedToolpath != currentToolpath){
		loopGuard = true;
		m_choiceToolpath->Clear();
		m_choiceToolpath->Append(_T(""));
		if(selectedRun >= 0){
			for(size_t i = 0;
					i < project->run[selectedRun].generators.GetCount(); i++){
				Generator * temp = project->run[selectedRun].generators[i];
				if(temp != NULL){
					m_choiceToolpath->Append(
							wxString::Format(_T("#%zu - "), i + 1)
									+ temp->GetName());
				}else{
					m_choiceToolpath->Append(
							wxString::Format(_T("#%zu - NULL-Pointer"), i + 1));
				}
			}
			m_choiceToolpath->SetSelection(selectedToolpath + 1);
		}else{
			m_choiceToolpath->SetSelection(0);
		}
		if(selectedRun >= 0 && selectedToolpath >= 0){
			int generatorNr = GetGeneratorNr(selectedRun, selectedToolpath);
			if(generatorNr >= 0){
				gc.generators[generatorNr]->CopyParameterFrom(
						project->run[selectedRun].generators[selectedToolpath]);
			}
			box = project->run[selectedRun].generators[selectedToolpath]->area;
			marginBelow =
					project->run[selectedRun].generators[selectedToolpath]->marginBelow;
			marginSides =
					project->run[selectedRun].generators[selectedToolpath]->marginSide;
			slotNr =
					project->run[selectedRun].generators[selectedToolpath]->refTool;
			freeHeight =
					project->run[selectedRun].generators[selectedToolpath]->freeHeight;

			m_choicebookGenerator->SetSelection(generatorNr);
		}else{
			m_choicebookGenerator->SetSelection(0);
		}
		currentRun = selectedRun;
		currentToolpath = selectedToolpath;

		loopGuard = false;
	}

	m_staticTextUnitX1->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY1->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ1->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitX2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitMarginBelow->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitMarginSide->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitDiameter->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnitFreeHeight->SetLabel(
			settings->SmallDistance.GetOtherName());

	m_textCtrlX1->SetValue(settings->Distance.TextFromSI(box.xmin));
	m_textCtrlY1->SetValue(settings->Distance.TextFromSI(box.ymin));
	m_textCtrlZ1->SetValue(settings->Distance.TextFromSI(box.zmin));

	m_textCtrlX2->SetValue(settings->Distance.TextFromSI(box.xmax));
	m_textCtrlY2->SetValue(settings->Distance.TextFromSI(box.ymax));
	m_textCtrlZ2->SetValue(settings->Distance.TextFromSI(box.zmax));

	m_textCtrlMarginBelow->SetValue(settings->Distance.TextFromSI(marginBelow));
	m_textCtrlMarginSide->SetValue(settings->Distance.TextFromSI(marginSides));

	m_textCtrlFreeHeight->SetValue(
			settings->SmallDistance.TextFromSI(freeHeight));

	loopGuard = true;
	if(selectedRun >= 0 && selectedToolpath >= 0){

		Generator * temp =
				project->run[selectedRun].generators[selectedToolpath];
		if(temp != NULL){
			m_textCtrlInfo->SetValue(temp->output);
		}else{
			m_textCtrlInfo->SetValue(_T(""));
		}

		Tool * tool = NULL;
		if(slotNr < project->run[selectedRun].machine.tools.GetCount()) tool =
				&(project->run[selectedRun].machine.tools[slotNr]);
		if(tool != NULL){
			m_textCtrlToolDiameter->SetValue(
					settings->SmallDistance.TextFromSI(tool->GetMaxDiameter()));
		}else{
			m_textCtrlToolDiameter->SetValue(_T(""));
		}
		//TODO: Check for slotNr +1 > maxToolNumber?
		m_choiceTool->SetSelection(slotNr + 1);

		// Transfer other choicepages
		int pageNr = m_choicebookGenerator->GetSelection();
		gc.generators[pageNr]->TransferDataToPanel();
	}else{
		m_choiceTool->SetSelection(0);

		m_textCtrlX1->SetValue(_T(""));
		m_textCtrlY1->SetValue(_T(""));
		m_textCtrlZ1->SetValue(_T(""));
		m_textCtrlX2->SetValue(_T(""));
		m_textCtrlY2->SetValue(_T(""));
		m_textCtrlZ2->SetValue(_T(""));
		m_textCtrlMarginBelow->SetValue(_T(""));
		m_textCtrlMarginSide->SetValue(_T(""));
		m_textCtrlToolDiameter->SetValue(_T(""));
		m_textCtrlFreeHeight->SetValue(_T(""));
		m_textCtrlInfo->SetValue(_T(""));
		m_choicebookGenerator->SetSelection(0);
	}
	loopGuard = false;

	return true;
}

bool DialogToolpathGenerator::TransferDataFromWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	const int pageNr = m_choicebookGenerator->GetSelection();
	gc.generators[pageNr]->TransferDataFromPanel();
	box.xmin = settings->Distance.SIFromString(m_textCtrlX1->GetValue());
	box.ymin = settings->Distance.SIFromString(m_textCtrlY1->GetValue());
	box.zmin = settings->Distance.SIFromString(m_textCtrlZ1->GetValue());
	box.xmax = settings->Distance.SIFromString(m_textCtrlX2->GetValue());
	box.ymax = settings->Distance.SIFromString(m_textCtrlY2->GetValue());
	box.zmax = settings->Distance.SIFromString(m_textCtrlZ2->GetValue());
	marginBelow = settings->Distance.SIFromString(
			m_textCtrlMarginBelow->GetValue());
	marginSides = settings->Distance.SIFromString(
			m_textCtrlMarginSide->GetValue());
	freeHeight = settings->SmallDistance.SIFromString(
			m_textCtrlFreeHeight->GetValue());

	const int toolNr = m_choiceTool->GetSelection() - 1;
	if(currentRun >= 0 && toolNr >= 0){
		slotNr = toolNr;
	}else{
		slotNr = -1;
	}
	return true;
}

void DialogToolpathGenerator::OnXClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogToolpathGenerator::OnClose(wxCommandEvent& event)
{
	this->Hide();
}

void DialogToolpathGenerator::OnSelectTool(wxCommandEvent& event)
{
	TransferDataFromWindow();
	const int toolNr = m_choiceTool->GetSelection() - 1;
	if(currentRun >= 0 && toolNr >= 0){
		slotNr = toolNr;
	}else{
		slotNr = 0;
	}
	TransferDataToWindow();
}

void DialogToolpathGenerator::UndoChanges(void)
{
	currentRun = -2;
	currentToolpath = -2;
}

Project* DialogToolpathGenerator::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}

int DialogToolpathGenerator::GetGeneratorNr(int runNr, int toolpathNr)
{
	if(runNr < 0) return -1;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	if(runNr >= project->run.GetCount()) return -1;
	if(toolpathNr < 0) return -1;
	if(toolpathNr >= project->run[runNr].generators.GetCount()) return -1;

	assert(project->run[runNr].generators[toolpathNr]!=NULL);

	size_t generatorNr;
	if(!gc.FindGenerator(project->run[runNr].generators[toolpathNr],
			&generatorNr)) return -1;
	return generatorNr;
}

void DialogToolpathGenerator::OnSelectRun(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;

	if(currentRun >= 0){
		for(size_t n = 0; n < project->run[currentRun].generators.GetCount();
				n++)
			project->run[currentRun].generators[n]->selected = false;
	}
	size_t n;
	for(n = 0; n < project->run.GetCount(); n++)
		project->run[n].selected = (n == runNr);

	TransferDataToWindow();

// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnSelectToolpath(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;
	size_t n;
	for(n = 0; n < project->run[runNr].generators.GetCount(); n++)
		project->run[runNr].generators[n]->selected = (n == toolpathNr);

	TransferDataToWindow();

// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnAdd(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;

	// The new generator/toolpath is placed behind the selected one.
	// That is the reason for the toolpathNr + 1.
	cmdProc->Submit(
			new CommandRunGeneratorAdd(
			_("Add generator to run ") + project->run[runNr].name,
					project, runNr, toolpathNr + 1, gc.NewGenerator(0)));

	// Select the newly added generator.
	for(size_t i = 0; i < project->run[runNr].generators.GetCount(); i++){
		project->run[runNr].generators[i]->selected = (i == (toolpathNr + 1));
	}

	TransferDataToWindow();

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnDelete(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;
	if(toolpathNr < 0) return;

	cmdProc->Submit(
			new CommandRunGeneratorDelete(
			_("Deleted generator from run ") + project->run[runNr].name,
					project, runNr, toolpathNr));

	if(toolpathNr >= project->run[runNr].generators.GetCount()){
		toolpathNr = project->run[runNr].generators.GetCount() - 1;
	}

	for(size_t i = 0; i < project->run[runNr].generators.GetCount(); i++){
		project->run[runNr].generators[i]->selected = (i == toolpathNr);
	}

	TransferDataToWindow();

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnUpdate(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0 || toolpathNr < 0) return;
	int generatorNr = m_choicebookGenerator->GetSelection();

	Generator * temp = gc.NewGenerator(generatorNr);
	temp->CopyParameterFrom(gc.generators[generatorNr]);
	temp->area = box;
	temp->marginBelow = marginBelow;
	temp->marginSide = marginSides;
	temp->refTool = slotNr;
	temp->freeHeight = freeHeight;

	cmdProc->Submit(
			new CommandRunGeneratorUpdate(
			_("Update generator on run ") + project->run[runNr].name,
					project, runNr, toolpathNr, temp));

	for(size_t i = 0; i < project->run[runNr].generators.GetCount(); i++){
		project->run[runNr].generators[i]->selected = (i == toolpathNr);
	}

	TransferDataToWindow();

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnSelectArea(wxCommandEvent& event)
{

	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	int runNr = m_choiceRun->GetSelection() - 1;
	if(runNr < 0) return;
	int workpieceNr = project->run[runNr].refWorkpiece;
	if(workpieceNr < 0) return;

	wxArrayString choices;
	for(size_t i = 0;
			i < project->workpieces[workpieceNr].placements.GetCount(); i++){
		int objectNr = project->workpieces[workpieceNr].placements[i].refObject;
		if(objectNr < 0){
			choices.Add(_T("No object in reference (i.e. program error)."));
		}else{
			choices.Add(project->objects[objectNr].name);
		}
	}

	wxMultiChoiceDialog dialog(this, _("Select one or more objects:"),
			_("Select object(s)..."), choices);
	if(dialog.ShowModal() == wxID_OK){
		TransferDataFromWindow();
		box.Clear();
		wxArrayInt plSel = dialog.GetSelections();
		for(size_t i = 0; i < plSel.GetCount(); i++){
			box.Insert(project->workpieces[workpieceNr].placements[plSel[i]]);
		}
		TransferDataToWindow();
		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_REFRESHVIEW);
	}
}

void DialogToolpathGenerator::OnChangeText(wxCommandEvent& event)
{
}

void DialogToolpathGenerator::OnPageChanged(wxChoicebookEvent& event)
{
	int pageNr = m_choicebookGenerator->GetSelection();
	gc.generators[pageNr]->TransferDataToPanel();
}

void DialogToolpathGenerator::OnResetChanges(wxCommandEvent& event)
{
	UndoChanges();
	TransferDataToWindow();
}

