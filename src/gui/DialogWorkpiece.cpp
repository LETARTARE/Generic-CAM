///////////////////////////////////////////////////////////////////////////////
// Name               : DialogWorkpiece.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : wx-config needs option "adv"
// Author             : Tobias Schaefer
// Created            : 14.01.2015
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

#include "DialogWorkpiece.h"

#include <wx/grid.h>

#include "../command/CommandWorkpieceAdd.h"
#include "../command/CommandWorkpieceAssignObject.h"
#include "../command/CommandWorkpieceRemoveObject.h"

#include "IDs.h"

DialogWorkpiece::DialogWorkpiece(wxWindow* parent, Project* project,
		wxCommandProcessor* commandProcessor) :
		GUIWorkpiece(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
}

void DialogWorkpiece::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogWorkpiece::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogWorkpiece::OnManageStock(wxCommandEvent& event)
{

}

void DialogWorkpiece::OnAddStock(wxCommandEvent& event)
{
	int selected = m_choiceStock->GetSelection();
	if(selected < 0 || selected >= project->stock.stockMaterials.GetCount()) return;
	wxString name = project->stock.stockMaterials[selected].name;
	CommandWorkpieceAdd * command = new CommandWorkpieceAdd(
	_("Add Workpiece ") + name, project,
			project->stock.stockMaterials[selected]);
	commandProcessor->Submit(command);
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogWorkpiece::OnDBLClick(wxGridEvent& event)
{
	int objectNr = event.GetRow();
	int workpieceNr = event.GetCol();
	unsigned int placementNr;
	for(placementNr = 0;
			placementNr < project->workpieces[workpieceNr].placements.GetCount();
			placementNr++){
		if(project->workpieces[workpieceNr].placements[placementNr].objectNr
				== objectNr){
			commandProcessor->Submit(
					new CommandWorkpieceRemoveObject(
							_("Remove Object from Workpiece"), project,
							workpieceNr, placementNr));
			wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
			ProcessEvent(selectEvent);
			return;
		}
	}
	commandProcessor->Submit(
			new CommandWorkpieceAssignObject(_("Assign Object to Workpiece"),
					project, workpieceNr, objectNr));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogWorkpiece::OnSize(wxSizeEvent& event)
{
//	wxSize sz = m_listCtrl->GetClientSize();
//	unsigned int w = sz.x / 10;
	event.Skip();
	TransferDataToWindow();
}

bool DialogWorkpiece::TransferDataToWindow(void)
{
	if(!this->IsShown()) return false;
	if(project == NULL) return false;

	wxSize sz = m_grid->GetClientSize();
	unsigned int w = sz.x / (3 + project->workpieces.GetCount());
	size_t i, j;

	// Resize grid
	if(m_grid->GetNumberRows() > project->objects.GetCount()){
		m_grid->DeleteRows(0,
				m_grid->GetNumberRows() - project->objects.GetCount());
	}
	if(m_grid->GetNumberRows() < project->objects.GetCount()){
		m_grid->AppendRows(
				project->objects.GetCount() - m_grid->GetNumberRows());
	}
	if(m_grid->GetNumberCols() > project->workpieces.GetCount()){
		m_grid->DeleteCols(0,
				m_grid->GetNumberCols() - project->workpieces.GetCount());
	}
	if(m_grid->GetNumberCols() < project->workpieces.GetCount()){
		m_grid->AppendCols(
				project->workpieces.GetCount() - m_grid->GetNumberCols());
	}

	// Relabel rows and columns
	m_grid->SetRowLabelSize(3 * w);
	for(i = 0; i < project->workpieces.GetCount(); i++){
		m_grid->SetColLabelValue(i, project->workpieces[i].name);
		m_grid->SetColSize(i, w);
	}
	for(i = 0; i < project->objects.GetCount(); i++){
		m_grid->SetRowLabelValue(i, project->objects[i].name);
	}
	m_grid->ClearGrid();

	size_t workpieceNr, objectNr;
	for(workpieceNr = 0; workpieceNr < project->workpieces.GetCount();
			workpieceNr++){
		for(j = 0; j < project->workpieces[workpieceNr].placements.GetCount();
				j++){
			objectNr = project->workpieces[workpieceNr].placements[j].objectNr;
			m_grid->SetCellValue(objectNr, workpieceNr, _T("X"));
		}
	}

	// Update available stock material
	for(i = 0; i < project->stock.stockMaterials.GetCount(); i++){
		if(i >= m_choiceStock->GetCount()){
			m_choiceStock->Append(project->stock.stockMaterials[i].name);
		}else{
			m_choiceStock->SetString(i, project->stock.stockMaterials[i].name);
		}
	}
	for(i = m_choiceStock->GetCount();
			i > project->stock.stockMaterials.GetCount(); i--)
		m_choiceStock->Delete(i - 1);

	return true;
}

bool DialogWorkpiece::TransferDataFromWindow(void)
{

	return true;
}
