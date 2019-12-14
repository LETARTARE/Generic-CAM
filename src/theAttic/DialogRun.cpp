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

#include "../project/ProjectView.h"
#include "FrameMain.h"
#include "FrameParent.h"

DialogRun::DialogRun(wxWindow* parent) :
		GUIRun(parent)
{
	m_menuPreferences->Append(ID_SETUPUNITS,
			_("Setup &Units") + wxT("\tCtrl+U"));
	loopGuard = false;
}

DialogRun::~DialogRun()
{
}

bool DialogRun::TransferDataToWindow(void)
{
	if(loopGuard) return false;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);

	CollectionUnits* settings = &(frame->GetParentFrame()->units);
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

	for(i = 0; i < view->toolbox.GetToolCount(); i++){
		if(i >= m_listBoxTool->GetCount()){
			m_listBoxTool->Append(view->toolbox.ToolIndex(i)->toolName);
		}else{
			m_listBoxTool->SetString(i, view->toolbox.ToolIndex(i)->toolName);
		}
	}
	for(i = m_listBoxTool->GetCount(); i > view->toolbox.GetToolCount(); i--)
		m_listBoxTool->Delete(i - 1);
	loopGuard = true;
	if(m_listBoxTool->GetSelection() < 0) m_listBoxTool->SetSelection(0);
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
							project->run[selected].machine.tools[i].GetMaxDiameter()));
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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	int id = m_choiceRun->GetSelection() - 1;

	size_t n;
	for(n = 0; n < project->run.GetCount(); n++)
		project->run[n].Select(n == id);

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogRun::OnWorkpieceSelect(wxCommandEvent& event)
{
	if(loopGuard) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	const int selected = GetSelected();
	if(selected < 0) return;
	int temp = m_choiceWorkpiece->GetSelection() - 1;
	if(project->run[selected].refWorkpiece != temp){
		if(temp >= 0){
			cmdProc->Submit(
					new CommandRunWorkpieceAssign(
							_("Set Workpiece to ")
									+ m_choiceWorkpiece->GetString(temp + 1),
							project, selected, temp));
		}else{
			cmdProc->Submit(
					new CommandRunWorkpieceAssign(_("Removed Workpiece."),
							project, selected, temp));
		}

//		wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
//		ID_REFRESHMAINGUI);
//		ProcessEvent(selectEvent);
	}
}

void DialogRun::OnRotate(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	int runNr = GetSelected();
	if(runNr < 0) return;
	int workpieceNr = project->run[runNr].refWorkpiece;
	if(workpieceNr < 0) return;

	AffineTransformMatrix matrix = project->run[runNr].workpiecePlacement;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = 0.0;

	wxString description;

	switch(event.GetId()){
	case ID_WORKPIECEROTATEX:
		matrix *= AffineTransformMatrix::RotationXYZ(M_PI_2, 0, 0);
		description = _("Rotate workpiece around X axis");
		break;
	case ID_WORKPIECEROTATEY:
		matrix *= AffineTransformMatrix::RotationXYZ(0, M_PI_2, 0);
		description = _("Rotate workpiece around Y axis");
		break;
	case ID_WORKPIECEROTATEZ:
		matrix *= AffineTransformMatrix::RotationXYZ(0, 0, M_PI_2);
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

	cmdProc->Submit(
			new CommandRunWorkpieceTransform(description, project, runNr,
					matrix));
//	TransferDataToWindow();
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
//	ProcessEvent(selectEvent);
}

void DialogRun::OnMachineLoad(wxCommandEvent& event)
{
	// Select Machine load... from the main menu.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_MACHINELOAD);
	ProcessEvent(selectEvent);
//	TransferDataToWindow();
}

void DialogRun::OnToolRemove(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	int runNr = GetSelected();
	if(runNr < 0) return;
	int index = m_listCtrlTools->GetNextItem(-1, wxLIST_NEXT_ALL,
	wxLIST_STATE_SELECTED);
	if(index < 0) return;
	cmdProc->Submit(
			new CommandRunToolRemove(
					_(
							"Removed tool ") + project->run[runNr].machine.tools[index].toolName+_(" from run"),
					project, runNr, index));
//	TransferDataToWindow();
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
//	ProcessEvent(selectEvent);
}

int DialogRun::GetSelected(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	int selected = GetSelected();
	if(selected < 0) return;
	int toolNr = m_listBoxTool->GetSelection();
	if(toolNr < 0) return;
	int slotNr = m_spinCtrlToolSlot->GetValue();
	cmdProc->Submit(
			new CommandRunToolAdd(
					_("Added tool to run ")
							+ view->toolbox.ToolIndex(toolNr)->toolName,
					project, selected, *(view->toolbox.ToolIndex(toolNr)),
					slotNr));

	m_spinCtrlToolSlot->SetValue(slotNr + 1);
//	TransferDataToWindow();
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
//	ProcessEvent(selectEvent);
}

Project* DialogRun::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}
