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

#include "../project/command/CommandWorkpieceAdd.h"
#include "../project/command/CommandWorkpieceObjectAssign.h"
#include "../project/command/CommandWorkpieceObjectRemove.h"
#include "IDs.h"
#include <wx/grid.h>

#include "../project/ProjectView.h"
#include "FrameMain.h"
#include "FrameParent.h"

DialogWorkpiece::DialogWorkpiece(wxWindow* parent) :
		GUIWorkpiece(parent)
{
}

void DialogWorkpiece::OnXClose(wxCloseEvent& event)
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
	TransferDataToWindow();
}

void DialogWorkpiece::OnAddStock(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	int selected = m_choiceStock->GetSelection();
	if(selected >= 0 && selected < view->stock.stockMaterials.GetCount()){

		wxString name = view->stock.stockMaterials[selected].name;
		CommandWorkpieceAdd * command = new CommandWorkpieceAdd(
		_("Add Workpiece ") + name, project,
				view->stock.stockMaterials[selected]);
		cmdProc->Submit(command);
		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
		ProcessEvent(selectEvent);
	}

	if(project == NULL) return;

	if(selected > view->stock.stockMaterials.GetCount()
			&& selected
					<= view->stock.stockMaterials.GetCount()
							+ project->objects.GetCount()){

		const size_t objectNr = selected - view->stock.stockMaterials.GetCount()
				- 1;
		StockMaterial tempStock;
		project->objects[objectNr].Update();
		tempStock.sx = project->objects[objectNr].bbox.GetSizeX();
		tempStock.sy = project->objects[objectNr].bbox.GetSizeY();
		tempStock.sz = project->objects[objectNr].bbox.GetSizeZ();
		tempStock.name = project->objects[objectNr].name;
		wxString name = tempStock.name;
		CommandWorkpieceAdd * command = new CommandWorkpieceAdd(
		_("Add Object as Workpiece ") + name, project, tempStock,
				objectNr);
		cmdProc->Submit(command);
		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
		ProcessEvent(selectEvent);
	}
}

void DialogWorkpiece::OnDBLClick(wxGridEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	int objectNr = event.GetRow();
	int workpieceNr = event.GetCol();
	unsigned int placementNr;
	for(placementNr = 0;
			placementNr < project->workpieces[workpieceNr].placements.GetCount();
			placementNr++){
		if(project->workpieces[workpieceNr].placements[placementNr].refObject
				== objectNr){
			cmdProc->Submit(
					new CommandWorkpieceObjectRemove(
							_("Remove Object from Workpiece"), project,
							workpieceNr, placementNr));
			wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
					ID_REFRESHVIEW);
			ProcessEvent(selectEvent);
			return;
		}
	}
	cmdProc->Submit(
			new CommandWorkpieceObjectAssign(_("Assign Object to Workpiece"),
					project, workpieceNr, objectNr));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogWorkpiece::OnSize(wxSizeEvent& event)
{
//	wxSize sz = m_listCtrl->GetClientSize();
//	unsigned int w = sz.x / 10;
	event.Skip();
	TransferDataToWindow();
}

Project* DialogWorkpiece::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}

bool DialogWorkpiece::TransferDataToWindow(void)
{
	if(!this->IsShown()) return false;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
	if(project == NULL) return false;

	wxSize sz = m_grid->GetClientSize();
	const unsigned int w = sz.x / (3 + project->workpieces.GetCount());

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
	for(size_t i = 0; i < project->workpieces.GetCount(); i++){
		m_grid->SetColLabelValue(i, project->workpieces[i].name);
		m_grid->SetColSize(i, w);
	}
	for(size_t i = 0; i < project->objects.GetCount(); i++){
		m_grid->SetRowLabelValue(i, project->objects[i].name);
	}
	m_grid->ClearGrid();

	for(size_t workpieceNr = 0; workpieceNr < project->workpieces.GetCount();
			workpieceNr++){
		for(size_t j = 0;
				j < project->workpieces[workpieceNr].placements.GetCount();
				j++){
			const size_t objectNr =
					project->workpieces[workpieceNr].placements[j].refObject;
			m_grid->SetCellValue(objectNr, workpieceNr, _T("X"));
		}
	}

	// Update available stock material
	size_t nrMaterials = view->stock.stockMaterials.GetCount() + 1
			+ project->objects.GetCount();

	size_t c = 0;
	for(size_t i = 0; i < view->stock.stockMaterials.GetCount(); i++){
		if(c >= m_choiceStock->GetCount()){
			m_choiceStock->Append(view->stock.stockMaterials[i].name);
		}else{
			m_choiceStock->SetString(c, view->stock.stockMaterials[i].name);
		}
		c++;
	}
	if(c >= m_choiceStock->GetCount()){
		m_choiceStock->Append(_T("-----"));
	}else{
		m_choiceStock->SetString(c, _T("-----"));
	}
	c++;
	for(size_t i = 0; i < project->objects.GetCount(); i++){
		if(c >= m_choiceStock->GetCount()){
			m_choiceStock->Append(project->objects[i].name);
		}else{
			m_choiceStock->SetString(c, project->objects[i].name);
		}
		c++;
	}
	for(size_t i = m_choiceStock->GetCount(); i > nrMaterials; i--)
		m_choiceStock->Delete(i - 1);

	if(m_choiceStock->GetSelection() < 0
			|| m_choiceStock->GetSelection() > m_choiceStock->GetCount()){
		m_choiceStock->SetSelection(0);
	}

	return true;
}
