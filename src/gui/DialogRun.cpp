///////////////////////////////////////////////////////////////////////////////
// Name               : DialogRun.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.01.2015
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

#include "DialogRun.h"
#include "IDs.h"
#include <wx/event.h>

#include "../3D/AffineTransformMatrix.h"
#include "../command/CommandRunSetWorkpiece.h"
#include "../command/CommandRunAddTool.h"
#include "../command/CommandRunRemoveTool.h"
#include "../command/CommandRunWorkpieceTransform.h"

DialogRun::DialogRun(wxWindow* parent, Project* project,
		wxCommandProcessor* commandProcessor, DisplaySettings* settings) :
		GUIRun(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
}

DialogRun::~DialogRun()
{
}

bool DialogRun::TransferDataToWindow(void)
{
	size_t i;
	int selected = -1;
	m_choiceRun->Clear();
	m_choiceRun->Append(_T(""));

	for(i = 0; i < project->run.GetCount(); i++){
		m_choiceRun->Append(project->run[i].name);
		if(selected == -1 && project->run[i].selected) selected = i;
	}
	m_choiceRun->SetSelection(selected + 1);

	m_choiceWorkpiece->Clear();
	m_choiceWorkpiece->Append(_T(""));
	for(i = 0; i < project->workpieces.GetCount(); i++)
		m_choiceWorkpiece->Append(project->workpieces[i].name);

	for(i = 0; i < project->toolbox.tools.GetCount(); i++){
		if(i >= m_choiceTool->GetCount()){
			m_choiceTool->Append(project->toolbox.tools[i].toolName);
		}else{
			m_choiceTool->SetString(i, project->toolbox.tools[i].toolName);
		}
	}
	for(i = m_choiceTool->GetCount(); i > project->toolbox.tools.GetCount();
			i--)
		m_choiceTool->Delete(i - 1);
	if(m_choiceTool->GetSelection() < 0) m_choiceTool->SetSelection(0);

	if(selected > -1){

		m_choiceWorkpiece->SetSelection(project->run[selected].workpieceNr + 1);

		m_textCtrlMachineName->SetValue(
				project->run[selected].machine.fileName.GetName());

		wxSize sz = m_listCtrlTools->GetClientSize();
		unsigned int w = sz.x / 7;

		m_listCtrlTools->ClearAll();
		m_listCtrlTools->InsertColumn(0, _("Toolslot"), wxLIST_FORMAT_CENTER,
				2 * w);
		m_listCtrlTools->InsertColumn(1, _("Tool"), wxLIST_FORMAT_LEFT, 3 * w);
		m_listCtrlTools->InsertColumn(2, _("Diameter"), wxLIST_FORMAT_RIGHT,
				2 * w);

		for(i = 0; i < project->run[selected].toolbox.tools.GetCount(); i++){
			m_listCtrlTools->InsertItem(i,
					wxString::Format(_T("%u"),
							project->run[selected].toolbox.tools[i].slot));
			m_listCtrlTools->SetItem(i, 1,
					project->run[selected].toolbox.tools[i].toolName);
			m_listCtrlTools->SetItem(i, 2,
					settings->SmallDistance.TextFromSIWithUnit(
							project->run[selected].toolbox.tools[i].GetMaxDiameter(),
							1));
		}
	}else{
		m_listCtrlTools->ClearAll();
		m_textCtrlMachineName->SetValue(_T(""));
		m_choiceWorkpiece->SetSelection(0);
	}

	return true;
}

bool DialogRun::TransferDataFromWindow(void)
{
	return false;
}

void DialogRun::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogRun::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogRun::OnRunSelect(wxCommandEvent& event)
{
	int id = m_choiceRun->GetSelection() - 1;

	size_t n;
	for(n = 0; n < project->run.GetCount(); n++)
		project->run[n].selected = (n == id);

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHTREE);
	ProcessEvent(selectEvent);
}

void DialogRun::OnWorkpieceSelect(wxCommandEvent& event)
{
	int selected = GetSelected();
	if(selected < 0) return;
	int temp = m_choiceWorkpiece->GetSelection() - 1;
	if(temp < 0) return;
	if(project->run[selected].workpieceNr != temp){
		commandProcessor->Submit(
				new CommandRunSetWorkpiece(
						_("Set Workpiece to ")
								+ m_choiceWorkpiece->GetString(temp + 1),
						project, selected, temp));
		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
		ProcessEvent(selectEvent);
	}
}

void DialogRun::OnRotate(wxCommandEvent& event)
{
	int selected = GetSelected();
	if(selected < 0) return;

	switch(event.GetId()){
	case ID_WORKPIECEROTATEX:
		commandProcessor->Submit(
				new CommandRunWorkpieceTransform(
						_("Rotate workpiece around X axis"), project, selected,
						AffineTransformMatrix::RotateXYZ(M_PI_2, 0, 0)));
		break;
	case ID_WORKPIECEROTATEY:
		commandProcessor->Submit(
				new CommandRunWorkpieceTransform(
						_("Rotate workpiece around Y axis"), project, selected,
						AffineTransformMatrix::RotateXYZ(0, M_PI_2, 0)));
		break;
	case ID_WORKPIECEROTATEZ:
		commandProcessor->Submit(
				new CommandRunWorkpieceTransform(
						_("Rotate workpiece around Z axis"), project, selected,
						AffineTransformMatrix::RotateXYZ(0, 0, M_PI_2)));
		break;
	}
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogRun::OnMachineLoad(wxCommandEvent& event)
{
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_MACHINELOAD);
	ProcessEvent(selectEvent);
}

void DialogRun::OnToolRemove(wxCommandEvent& event)
{
	int selected = GetSelected();
	if(selected < 0) return;
	int toolNr = m_listCtrlTools->GetNextItem(-1, wxLIST_NEXT_ALL,
	wxLIST_STATE_SELECTED);
	if(toolNr < 0) return;
	int slotNr = project->run[selected].toolbox.tools[toolNr].slot;
	commandProcessor->Submit(
			new CommandRunRemoveTool(
					_("Removed tool from run ")
							+ project->run[selected].toolbox.tools[toolNr].toolName,
					project, selected, slotNr));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

int DialogRun::GetSelected(void)
{
	int selected = -1;
	size_t n;
	for(n = 0; n < project->run.GetCount(); n++){
		if(project->run[n].selected){
			selected = n;
			break;
		}
	}
	return selected;
}

void DialogRun::OnToolAdd(wxCommandEvent& event)
{
	int selected = GetSelected();
	if(selected < 0) return;
	int toolNr = m_choiceTool->GetSelection();
	if(toolNr < 0) return;
	int slotNr = m_spinCtrlToolSlot->GetValue();
	commandProcessor->Submit(
			new CommandRunAddTool(
					_("Added tool to run ")
							+ project->toolbox.tools[toolNr].toolName, project,
					selected, toolNr, slotNr));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}
