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
#include "IDs.h"
#include "../command/CommandRunGeneratorAdd.h"
#include "../command/CommandRunGeneratorDelete.h"
#include "../command/CommandRunGeneratorUpdate.h"

#include "../generator/GeneratorNone.h"
#include "../generator/GeneratorPositioningDrills.h"
#include "../generator/GeneratorLoadFromFile.h"
#include "../generator/GeneratorAreaGridDexel.h"
#define N_GENERATORS 		4

#include <typeinfo>

Generator* DialogToolpathGenerator::NewGenerator(int generatorNr)
{
	assert(generatorNr < N_GENERATORS);

	switch(generatorNr){
	case 0:
		return new GeneratorNone;
		break;
	case 1:
		return new GeneratorPositioningDrills;
		break;
	case 2:
		return new GeneratorLoadFromFile;
		break;
	case 3:
		return new GeneratorAreaGridDexel;
		break;
	}
	return NULL;
}

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

	// Create a list of all available generators
	size_t i;
	generators = new Generator*[N_GENERATORS];
	for(i = 0; i < N_GENERATORS; i++)
		generators[i] = NewGenerator(i);

	// Assign pages to the choicebook for every generator
	wxString generatorName;
	for(i = 0; i < N_GENERATORS; i++){
		generatorName = generators[i]->GetName();
		wxPanel * panel = new wxPanel(m_choicebookGenerator, wxID_ANY,
				wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
		generators[i]->AddToPanel(panel, settings);
		m_choicebookGenerator->AddPage(panel, generatorName, (i == 0));
	}
	TransferDataToWindow();
}

DialogToolpathGenerator::~DialogToolpathGenerator()
{
	int i;
	for(i = 0; i < N_GENERATORS; i++)
		delete generators[i];
	delete[] generators;
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
		for(size_t i = 0; i < project->run[selectedRun].toolpaths.GetCount();
				i++){
			Generator * temp = project->run[selectedRun].toolpaths[i].generator;
			if(temp != NULL){
				m_choiceToolpath->Append(
						wxString::Format(_T("#%u - "), i) + temp->GetName());
			}else{
				m_choiceToolpath->Append(
						wxString::Format(_T("#%u - NULL-Pointer"), i));
			}
			if(selectedToolpath == -1
					&& project->run[selectedRun].toolpaths[i].selected) selectedToolpath =
					i;
		}
		m_choiceToolpath->SetSelection(selectedToolpath + 1);
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

		// Transfer other choicepages
		int pageNr = m_choicebookGenerator->GetSelection();
		generators[pageNr]->TransferDataToPanel();
	}else{
		m_textCtrlX1->SetValue(_T(""));
		m_textCtrlY1->SetValue(_T(""));
		m_textCtrlZ1->SetValue(_T(""));
		m_textCtrlX2->SetValue(_T(""));
		m_textCtrlY2->SetValue(_T(""));
		m_textCtrlZ2->SetValue(_T(""));
		m_textCtrlMarginBelow->SetValue(_T(""));
		m_textCtrlMarginSide->SetValue(_T(""));
		m_choicebookGenerator->SetSelection(0);
	}

	return true;
}

bool DialogToolpathGenerator::TransferDataFromWindow(void)
{
	int pageNr = m_choicebookGenerator->GetSelection();
	generators[pageNr]->TransferDataFromPanel();
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
	return true;
}

void DialogToolpathGenerator::OnClose(wxCloseEvent& event)
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
	for(n = 0; n < project->run[runNr].toolpaths.GetCount(); n++)
		if(project->run[runNr].toolpaths[n].selected) return n;

	return -1;
}

int DialogToolpathGenerator::GetGeneratorNr(int runNr, int toolpathNr)
{
	if(runNr < 0) return -1;
	if(runNr >= project->run.GetCount()) return -1;
	if(toolpathNr < 0) return -1;
	if(toolpathNr >= project->run[runNr].toolpaths.GetCount()) return -1;

	assert(project->run[runNr].toolpaths[toolpathNr].generator!=NULL);

	int n;
	for(n = 0; n < N_GENERATORS; n++)
		if(typeid(project->run[runNr].toolpaths[toolpathNr].generator)
				== typeid(generators[n])) return n;

	return -1;
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
		Generator * temp = generators[generatorNr];
		temp->CopyFrom(project->run[runNr].toolpaths[toolpathNr].generator);
		m_choicebookGenerator->SetSelection(generatorNr);
	}

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHTREE);
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
	for(n = 0; n < project->run[runNr].toolpaths.GetCount(); n++)
		project->run[runNr].toolpaths[n].selected = (n == toolpathNr);

	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr >= 0){
		Generator * temp = generators[generatorNr];
		temp->CopyFrom(project->run[runNr].toolpaths[toolpathNr].generator);
		m_choicebookGenerator->SetSelection(generatorNr);
	}

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHTREE);
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
					project, runNr, toolpathNr + 1, new GeneratorNone));

	// Select the newly added generator.
	for(size_t i = 0; i < project->run[runNr].toolpaths.GetCount(); i++){
		project->run[runNr].toolpaths[i].selected = (i == (toolpathNr + 1));
	}

	m_choicebookGenerator->SetSelection(0);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
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
		Generator * temp = generators[generatorNr];
		temp->CopyFrom(project->run[runNr].toolpaths[toolpathNr].generator);
		m_choicebookGenerator->SetSelection(generatorNr);
	}

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnUpdate(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr < 0) return;

	Generator * temp = generators[generatorNr];
	project->run[runNr].toolpaths[toolpathNr].generator->CopyFrom(temp);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnSelectArea(wxCommandEvent& event)
{

	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0 || toolpathNr < 0) return;
	int workpieceNr = project->run[runNr].workpieceNr;
	if(workpieceNr < 0) return;

	wxArrayString choices;
	size_t i;
	for(i = 0; i < project->workpieces[workpieceNr].placements.GetCount(); i++){
		int objectNr = project->workpieces[workpieceNr].placements[i].objectNr;
		if(objectNr < 0){
			choices.Add(_T("No object."));
		}else{
			choices.Add(project->objects[objectNr].name);
		}
	}

	wxMultiChoiceDialog dialog(this, _("Select one or more objects:"),
			_("Select object(s)..."), choices);
	if(dialog.ShowModal() == wxID_OK){
		TransferDataFromWindow();
		project->run[runNr].toolpaths[toolpathNr].generator->box.Clear();
		wxArrayInt plSel = dialog.GetSelections();
		for(i = 0; i < plSel.GetCount(); i++){

			float x =
					project->workpieces[workpieceNr].placements[plSel[i]].matrix.a[12];
			float y =
					project->workpieces[workpieceNr].placements[plSel[i]].matrix.a[13];
			float d =
					project->workpieces[workpieceNr].placements[plSel[i]].slotWidth;
			float sx =
					project->workpieces[workpieceNr].placements[plSel[i]].bbox.GetSizeX();
			float sy =
					project->workpieces[workpieceNr].placements[plSel[i]].bbox.GetSizeY();
			project->run[runNr].toolpaths[toolpathNr].generator->box.Insert(
					BoundingBox(x - d, y - d, 0, x + sx + d, y + sy + d,
							project->workpieces[workpieceNr].sz));
		}
		TransferDataToWindow();
	}
}

void DialogToolpathGenerator::OnChangeText(wxCommandEvent& event)
{
	TransferDataFromWindow();
}

void DialogToolpathGenerator::OnPageChanged(wxChoicebookEvent& event)
{
	TransferDataFromWindow();
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	if(runNr < 0 || toolpathNr < 0) return;
	if(project->run[runNr].toolpaths[toolpathNr].generator != NULL){
		delete project->run[runNr].toolpaths[toolpathNr].generator;
	}
	int pageNr = m_choicebookGenerator->GetSelection();
	project->run[runNr].toolpaths[toolpathNr].generator = NewGenerator(pageNr);
	project->run[runNr].toolpaths[toolpathNr].generator->CopyFrom(
			generators[pageNr]);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogToolpathGenerator::OnResetChanges(wxCommandEvent& event)
{
	int runNr = m_choiceRun->GetSelection() - 1;
	int toolpathNr = m_choiceToolpath->GetSelection() - 1;
	int generatorNr = GetGeneratorNr(runNr, toolpathNr);
	if(generatorNr < 0) return;
	generators[generatorNr]->CopyFrom(
			project->run[runNr].toolpaths[toolpathNr].generator);
	TransferDataToWindow();
}

