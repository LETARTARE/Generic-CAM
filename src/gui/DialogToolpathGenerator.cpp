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
#include "IDs.h"

DialogToolpathGenerator::DialogToolpathGenerator(wxWindow* parent,
		Project* project, wxCommandProcessor* commandProcessor,
		DisplaySettings * settings) :
		GUIToolpathGenerator(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;

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

	m_choiceRun->Clear();
	m_choiceRun->Append(_T(""));

	int selectedRun = -1;
	for(size_t i = 0; i < project->run.GetCount(); i++){
		m_choiceRun->Append(project->run[i].name);
		if(selectedRun == -1 && project->run[i].selected) selectedRun = i;
	}
	m_choiceRun->SetSelection(selectedRun + 1);

	m_choiceToolpath->Clear();
	m_choiceToolpath->Append(_T(""));
	int selectedToolpath = -1;
	if(selectedRun >= 0){
		for(size_t i = 0; i < project->run[selectedRun].generators.GetCount();
				i++){
			Generator * temp = project->run[selectedRun].generators[i];
			if(temp != NULL){
				m_choiceToolpath->Append(
						wxString::Format(_T("#%u - "), i) + temp->GetName());
			}else{
				m_choiceToolpath->Append(
						wxString::Format(_T("#%u - NULL-Pointer"), i));
			}
			if(selectedToolpath == -1
					&& (*(project->run[selectedRun].generators[i])).selected) selectedToolpath =
					i;
		}
		m_choiceToolpath->SetSelection(selectedToolpath + 1);
	}

	m_choiceTool->Clear();
	m_choiceTool->Append(_T(""));
	if(selectedRun >= 0){
		for(int n = 0; n < project->run[selectedRun].tools.GetCount(); n++){
			m_choiceTool->Append(
					wxString::Format(_T("T%u - "), n)
							+ project->run[selectedRun].tools[n].toolName);
		}
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

	if(selectedRun >= 0 && selectedToolpath >= 0){

		m_textCtrlX1->SetValue(settings->Distance.TextFromSI(box.xmin, 3));
		m_textCtrlY1->SetValue(settings->Distance.TextFromSI(box.ymin, 3));
		m_textCtrlZ1->SetValue(settings->Distance.TextFromSI(box.zmin, 3));

		m_textCtrlX2->SetValue(settings->Distance.TextFromSI(box.xmax, 3));
		m_textCtrlY2->SetValue(settings->Distance.TextFromSI(box.ymax, 3));
		m_textCtrlZ2->SetValue(settings->Distance.TextFromSI(box.zmax, 3));

		m_textCtrlMarginBelow->SetValue(
				settings->Distance.TextFromSI(marginBelow, 3));
		m_textCtrlMarginSide->SetValue(
				settings->Distance.TextFromSI(marginSides, 3));

		m_textCtrlFreeHeight->SetValue(
				settings->SmallDistance.TextFromSI(freeHeight));

		Generator * temp =
				project->run[selectedRun].generators[selectedToolpath];
		if(temp != NULL){
			m_textCtrlInfo->SetValue(temp->output);
		}else{
			m_textCtrlInfo->SetValue(_T(""));
		}

		Tool * tool = &(project->run[selectedRun].tools[slotNr]);
		if(tool != NULL){
			m_textCtrlToolDiameter->SetValue(
					settings->SmallDistance.TextFromSI(tool->GetMaxDiameter()));
		}else{
			m_textCtrlToolDiameter->SetValue(_T(""));
		}
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
	return true;
}

bool DialogToolpathGenerator::TransferDataFromWindow(void)
{
	int pageNr = m_choicebookGenerator->GetSelection();
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

	int runNr = m_choiceRun->GetSelection() - 1;
	int toolNr = m_choiceTool->GetSelection() - 1;
	if(runNr >= 0 && toolNr >= 0){
		slotNr = toolNr;
	}else{
		slotNr = 0;
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

int DialogToolpathGenerator::GetSelectedToolpath(int runNr)
{
	if(runNr < 0) return -1;
	if(runNr >= project->run.GetCount()) return -1;

	size_t n;
	for(n = 0; n < project->run[runNr].generators.GetCount(); n++)
		if((*(project->run[runNr].generators[n])).selected) return n;

	return -1;
}

void DialogToolpathGenerator::OnSelectTool(wxCommandEvent& event)
{
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolNr = m_choiceTool->GetSelection() - 1;
	if(runNr >= 0 && toolNr >= 0){
		slotNr = toolNr;
		m_textCtrlToolDiameter->SetValue(
				settings->SmallDistance.TextFromSI(
						project->run[runNr].tools[toolNr].GetMaxDiameter()));
	}else{
		slotNr = 0;
		m_textCtrlToolDiameter->SetValue(_T(""));
	}
}

int DialogToolpathGenerator::GetGeneratorNr(int runNr, int toolpathNr)
{
	if(runNr < 0) return -1;
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
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->run.GetCount(); n++)
		project->run[n].selected = (n == runNr);

	int toolpathNr = GetSelectedToolpath(runNr);
	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr >= 0){
		gc.generators[generatorNr]->CopyParameterFrom(
				project->run[runNr].generators[toolpathNr]);
		box = project->run[runNr].generators[toolpathNr]->area;
		marginBelow = project->run[runNr].generators[toolpathNr]->marginBelow;
		marginSides = project->run[runNr].generators[toolpathNr]->marginSide;
		slotNr = project->run[runNr].generators[toolpathNr]->refTool;
		freeHeight = project->run[runNr].generators[toolpathNr]->freeHeight;

		m_choicebookGenerator->SetSelection(generatorNr);
	}

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogToolpathGenerator::OnSelectToolpath(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;
	size_t n;
	for(n = 0; n < project->run[runNr].generators.GetCount(); n++)
		project->run[runNr].generators[n]->selected = (n == toolpathNr);

	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr >= 0){
		gc.generators[generatorNr]->CopyParameterFrom(
				project->run[runNr].generators[toolpathNr]);
		box = project->run[runNr].generators[toolpathNr]->area;
		marginBelow = project->run[runNr].generators[toolpathNr]->marginBelow;
		marginSides = project->run[runNr].generators[toolpathNr]->marginSide;
		slotNr = project->run[runNr].generators[toolpathNr]->refTool;
		freeHeight = project->run[runNr].generators[toolpathNr]->freeHeight;

		m_choicebookGenerator->SetSelection(generatorNr);
	}

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogToolpathGenerator::OnAdd(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;

	// The new generator/toolpath is placed behind the selected one.
	// That is the reason for the toolpathNr + 1.
	commandProcessor->Submit(
			new CommandRunGeneratorAdd(
			_("Add generator to run ") + project->run[runNr].name,
					project, runNr, toolpathNr + 1, gc.NewGenerator(0)));

	// Select the newly added generator.
	for(size_t i = 0; i < project->run[runNr].generators.GetCount(); i++){
		project->run[runNr].generators[i]->selected = (i == (toolpathNr + 1));
	}

	box = project->run[runNr].generators[toolpathNr + 1]->area;
	marginBelow = project->run[runNr].generators[toolpathNr + 1]->marginBelow;
	marginSides = project->run[runNr].generators[toolpathNr + 1]->marginSide;
	slotNr = project->run[runNr].generators[toolpathNr + 1]->refTool;
	freeHeight = project->run[runNr].generators[toolpathNr + 1]->freeHeight;
	m_choicebookGenerator->SetSelection(0);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0) return;
	if(toolpathNr < 0) return;

	commandProcessor->Submit(
			new CommandRunGeneratorDelete(
			_("Deleted generator from run ") + project->run[runNr].name,
					project, runNr, toolpathNr));

	toolpathNr = m_choiceToolpath->GetSelection() - 1;
	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr >= 0){
		Generator * temp = gc.generators[generatorNr];
		temp->CopyParameterFrom(project->run[runNr].generators[toolpathNr]);

		box = project->run[runNr].generators[toolpathNr]->area;
		marginBelow = project->run[runNr].generators[toolpathNr]->marginBelow;
		marginSides = project->run[runNr].generators[toolpathNr]->marginSide;
		slotNr = project->run[runNr].generators[toolpathNr]->refTool;
		freeHeight = project->run[runNr].generators[toolpathNr]->freeHeight;

		m_choicebookGenerator->SetSelection(generatorNr);
	}

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnUpdate(wxCommandEvent& event)
{
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

	commandProcessor->Submit(
			new CommandRunGeneratorUpdate(
			_("Update generator on run ") + project->run[runNr].name,
					project, runNr, toolpathNr, temp));

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnSelectArea(wxCommandEvent& event)
{

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
	}
}

void DialogToolpathGenerator::OnChangeText(wxCommandEvent& event)
{
}

void DialogToolpathGenerator::OnPageChanged(wxChoicebookEvent& event)
{
}

void DialogToolpathGenerator::OnResetChanges(wxCommandEvent& event)
{
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr < 0) return;

	gc.generators[generatorNr]->CopyParameterFrom(
			project->run[runNr].generators[toolpathNr]);
	m_choicebookGenerator->SetSelection(generatorNr);
	box = project->run[runNr].generators[toolpathNr]->area;
	marginBelow = project->run[runNr].generators[toolpathNr]->marginBelow;
	marginSides = project->run[runNr].generators[toolpathNr]->marginSide;
	slotNr = project->run[runNr].generators[toolpathNr]->refTool;
	freeHeight = project->run[runNr].generators[toolpathNr]->freeHeight;
	TransferDataToWindow();
}

