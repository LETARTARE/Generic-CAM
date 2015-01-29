///////////////////////////////////////////////////////////////////////////////
// Name               : DialogPlacement.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.01.2015
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

#include "DialogPlacement.h"
#include "IDs.h"

DialogPlacement::DialogPlacement(wxWindow* parent, Project* project,
		wxCommandProcessor* commandProcessor, DisplaySettings* settings) :
		GUIPlacement(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
	m_topview->InsertProject(project);
}

bool DialogPlacement::TransferDataToWindow(void)
{
	size_t n;
	m_choiceWorkpiece->Clear();
	m_choiceWorkpiece->Append(_T(""));
	for(n = 0; n < project->workpieces.GetCount(); n++)
		m_choiceWorkpiece->Append(project->workpieces[n].name);
	int sel = GetSelectedWorkpiece();
	m_choiceWorkpiece->SetSelection(sel + 1);

	int m;
	m_choiceObject->Clear();
	m_choiceObject->Append(_T(""));
	if(sel < 0){
		m_choiceObject->SetSelection(0);
	}else{
		for(n = 0; n < project->workpieces[sel].placements.GetCount(); n++){
			m = project->workpieces[sel].placements[n].objectNr;
			if(m > -1){
				m_choiceObject->Append(project->objects[m].name);
			}else{
				m_choiceObject->Append(_T(""));
			}
		}
		int selp = GetSelectedPlacement(sel);
		m_choiceObject->SetSelection(selp + 1);
	}

	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());

	return true;
}

bool DialogPlacement::TransferDataFromWindow(void)
{
	return false;
}

void DialogPlacement::OnClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogPlacement::OnClose(wxCommandEvent& event)
{
	this->Hide();
}

void DialogPlacement::OnExtraAdd(wxCommandEvent& event)
{
}

int DialogPlacement::GetSelectedWorkpiece(void)
{
	size_t N = project->workpieces.GetCount();
	if(N == 0) return -1;
	size_t n;
	for(n = 0; n < N; n++){
		if(project->workpieces[n].selected) return n;
	}
	return -1;
}

int DialogPlacement::GetSelectedPlacement(int workpieceNr)
{
	if(workpieceNr < 0) return -1;
	size_t N = project->workpieces[workpieceNr].placements.GetCount();
	if(N == 0) return -1;
	size_t n;
	for(n = 0; n < N; n++){
		if(project->workpieces[workpieceNr].placements[n].selected) return n;
	}
	return -1;
}

void DialogPlacement::OnSelectWorkpiece(wxCommandEvent& event)
{
	int id = m_choiceWorkpiece->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == id);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHTREE);
	ProcessEvent(selectEvent);
}

void DialogPlacement::OnSelectObject(wxCommandEvent& event)
{
	int id = m_choiceWorkpiece->GetSelection() - 1;
	if(id < 0) return;
	int idP = m_choiceWorkpiece->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == id);

	for(n = 0; n < project->workpieces[id].placements.GetCount(); n++)
		project->workpieces[id].placements[n].selected = (n == idP);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHTREE);
	ProcessEvent(selectEvent);
}

void DialogPlacement::OnChangePosition(wxCommandEvent& event)
{
}

void DialogPlacement::OnChangeSlider(wxScrollEvent& event)
{
}

void DialogPlacement::OnSelectForm(wxCommandEvent& event)
{
}

void DialogPlacement::OnTransform(wxCommandEvent& event)
{
	switch(event.GetId()){
	case ID_MOVEXP:
		break;
	case ID_MOVEXN:
		break;
	case ID_MOVEYP:
		break;
	case ID_MOVEYN:
		break;
	case ID_ALIGNTOP:
		break;
	case ID_ALIGNMIDDLE:
		break;
	case ID_ALIGNBOTTOM:
		break;
	}
	Refresh();
}
