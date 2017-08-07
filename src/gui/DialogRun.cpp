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

#include "../project/command/CommandRunWorkpieceAssign.h"
#include "../project/command/CommandRunToolAdd.h"
#include "../project/command/CommandRunToolRemove.h"
#include "../project/command/CommandRunWorkpieceTransform.h"
#include "IDs.h"
#include "../3D/AffineTransformMatrix.h"
#include <wx/event.h>

DialogRun::DialogRun(wxWindow* parent, Project* project, ToolBox * toolbox,
		wxCommandProcessor* commandProcessor, DisplaySettings* settings) :
		GUIRun(parent)
{
	this->project = project;
	this->toolbox = toolbox;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
	loopGuard = false;
}

DialogRun::~DialogRun()
{
}

bool DialogRun::TransferDataToWindow(void)
{
	if(loopGuard) return false;
	size_t i;
	int selected = -1;
	m_choiceRun->Clear();
	m_choiceRun->Append(_T(""));

	for(i = 0; i < project->run.GetCount(); i++){
		m_choiceRun->Append(project->run[i].name);
		if(selected == -1 && project->run[i].selected) selected = i;
	}
	loopGuard = true;
	m_choiceRun->SetSelection(selected + 1);
	loopGuard = false;
	m_choiceWorkpiece->Clear();
	m_choiceWorkpiece->Append(_T(""));
	for(i = 0; i < project->workpieces.GetCount(); i++)
		m_choiceWorkpiece->Append(project->workpieces[i].name);

	for(i = 0; i < toolbox->GetToolCount(); i++){
		if(i >= m_choiceTool->GetCount()){
			m_choiceTool->Append(toolbox->ToolIndex(i)->toolName);
		}else{
			m_choiceTool->SetString(i, toolbox->ToolIndex(i)->toolName);
		}
	}
	for(i = m_choiceTool->GetCount(); i > toolbox->GetToolCount(); i--)
		m_choiceTool->Delete(i - 1);
	loopGuard = true;
	if(m_choiceTool->GetSelection() < 0) m_choiceTool->SetSelection(0);
	loopGuard = false;
	if(selected >= 0){
		loopGuard = true;
		m_choiceWorkpiece->SetSelection(
				project->run[selected].refWorkpiece + 1);
		loopGuard = false;
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

		for(i = 0; i < project->run[selected].machine.tools.GetCount(); i++){
			m_listCtrlTools->InsertItem(i,
					wxString::Format(_T("%i"),
							project->run[selected].machine.tools[i].slotNr));
			m_listCtrlTools->SetItem(i, 1,
					project->run[selected].machine.tools[i].toolName);
			m_listCtrlTools->SetItem(i, 2,
					settings->SmallDistance.TextFromSIWithUnit(
							project->run[selected].machine.tools[i].GetMaxDiameter(),
							1));
		}
	}else{
		m_listCtrlTools->ClearAll();
		m_textCtrlMachineName->SetValue(_T(""));
		loopGuard = true;
		m_choiceWorkpiece->SetSelection(0);
		loopGuard = false;
	}

	return true;
}

bool DialogRun::TransferDataFromWindow(void)
{
	return false;
}

void DialogRun::OnXClose(wxCloseEvent& event)
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
	if(loopGuard) return;
	int id = m_choiceRun->GetSelection() - 1;

	size_t n;
	for(n = 0; n < project->run.GetCount(); n++)
		project->run[n].Select(n == id);

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
}

void DialogRun::OnWorkpieceSelect(wxCommandEvent& event)
{
	if(loopGuard) return;
	const int selected = GetSelected();
	if(selected < 0) return;
	int temp = m_choiceWorkpiece->GetSelection() - 1;
	if(project->run[selected].refWorkpiece != temp){
		if(temp >= 0){
			commandProcessor->Submit(
					new CommandRunWorkpieceAssign(
							_("Set Workpiece to ")
									+ m_choiceWorkpiece->GetString(temp + 1),
							project, selected, temp));
		}else{
			commandProcessor->Submit(
					new CommandRunWorkpieceAssign(_("Removed Workpiece."),
							project, selected, temp));

		}

		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_REFRESHMAINGUI);
		ProcessEvent(selectEvent);
	}
}

void DialogRun::OnRotate(wxCommandEvent& event)
{
	int runNr = GetSelected();
	if(runNr < 0) return;
	int workpieceNr = project->run[runNr].refWorkpiece;
	if(workpieceNr < 0) return;

	AffineTransformMatrix matrix = project->run[runNr].workpiecePlacement;
	matrix.a[12] = 0.0;
	matrix.a[13] = 0.0;
	matrix.a[14] = 0.0;

	wxString description;

	switch(event.GetId()){
	case ID_WORKPIECEROTATEX:
		matrix *= AffineTransformMatrix::RotateXYZ(M_PI_2, 0, 0);
		description = _("Rotate workpiece around X axis");
		break;
	case ID_WORKPIECEROTATEY:
		matrix *= AffineTransformMatrix::RotateXYZ(0, M_PI_2, 0);
		description = _("Rotate workpiece around Y axis");
		break;
	case ID_WORKPIECEROTATEZ:
		matrix *= AffineTransformMatrix::RotateXYZ(0, 0, M_PI_2);
		description = _("Rotate workpiece around Z axis");
		break;
	}

	Vector3 temp(project->workpieces[workpieceNr].GetSizeX(),
			project->workpieces[workpieceNr].GetSizeY(),
			project->workpieces[workpieceNr].GetSizeZ());
	temp = matrix.TransformNoShift(temp);
	if(temp.x < 0.0) matrix.TranslateGlobal(-temp.x, 0, 0);
	if(temp.y < 0.0) matrix.TranslateGlobal(0, -temp.y, 0);
	if(temp.z < 0.0) matrix.TranslateGlobal(0, 0, -temp.z);

	commandProcessor->Submit(
			new CommandRunWorkpieceTransform(description, project, runNr,
					matrix));
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}

void DialogRun::OnMachineLoad(wxCommandEvent& event)
{
	// Select Machine load... from the main menu.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_MACHINELOAD);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogRun::OnToolRemove(wxCommandEvent& event)
{
	int runNr = GetSelected();
	if(runNr < 0) return;
	int index = m_listCtrlTools->GetNextItem(-1, wxLIST_NEXT_ALL,
	wxLIST_STATE_SELECTED);
	if(index < 0) return;
	commandProcessor->Submit(
			new CommandRunToolRemove(
					_(
							"Removed tool ") + project->run[runNr].machine.tools[index].toolName+_(" from run"),
					project, runNr, index));
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
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
			new CommandRunToolAdd(
					_("Added tool to run ")
							+ toolbox->ToolIndex(toolNr)->toolName, project,
					selected, *(toolbox->ToolIndex(toolNr)), slotNr));

	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}
