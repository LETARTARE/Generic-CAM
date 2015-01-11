///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetup6DOFController.cpp
// Purpose            : Setup dialog for 6DOF controller
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogSetup6DOFController.h"
#include <wx/debug.h>

DialogSetup6DOFController::DialogSetup6DOFController(wxWindow* parent) :
		GUISetup6DOFController(parent)
{
	radioDeviceSelect->SetItemToolTip(0, _("Spaceball by Spacetec IMC"));
	radioDeviceSelect->SetItemToolTip(1, _("Spaceorb by Spacetec IMC"));
	radioDeviceSelect->SetItemToolTip(2,
			_("Spacemouse by Logitech/3DConnexion"));

	control = NULL;

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER,
			wxTimerEventHandler(DialogSetup6DOFController::OnTimer),
			NULL, this);
	timer.Start(100);
}

DialogSetup6DOFController::~DialogSetup6DOFController()
{
	this->Disconnect(wxEVT_TIMER,
			wxTimerEventHandler(DialogSetup6DOFController::OnTimer),
			NULL, this);
}

void DialogSetup6DOFController::InsertController(Control3D& control)
{
	this->control = &control;
	TransferDataToWindow();
}

bool DialogSetup6DOFController::TransferDataToWindow()
{
	if(control == NULL) return false;

	if(control->IsOpen()){
		buttonConnect->Enable(false);
		buttonDisconnect->Enable(true);
		radioDeviceSelect->Enable(false);
		textPort->Enable(false);
	}else{
		buttonConnect->Enable(true);
		buttonDisconnect->Enable(false);
		radioDeviceSelect->Enable(true);
		textPort->Enable(true);
	}
	textPort->ChangeValue(control->GetPort());

	unsigned char i = control->GetType();
	switch(i){
	case CONTROLSPACEBALL_ID:
		radioDeviceSelect->SetSelection(0);
		break;
	case CONTROLSPACEORB_ID:
		radioDeviceSelect->SetSelection(1);
		break;
	case CONTROLSPACEMOUSE_ID:
		radioDeviceSelect->SetSelection(2);
		break;
	default:
		radioDeviceSelect->SetSelection(1);
		break;
	}
	return true;
}

void DialogSetup6DOFController::OnConnect(wxCommandEvent& event)
{
	if(control == NULL) return;

	unsigned char i = radioDeviceSelect->GetSelection() + 1;

	if(this->control->IsOpen()){
		this->control->Close();
		wxLogMessage(
				_T("control closed (but should not be open first place)!"));
	}

	switch(i){
	case CONTROLSPACEBALL_ID:
		break;
	case CONTROLSPACEORB_ID:
		break;
	case CONTROLSPACEMOUSE_ID:
		break;
	default:
		wxFAIL_MSG(_T("Unknown controller ID!"));
		break;
	}
	control->SetType(i);
	if(control->Open(textPort->GetValue())) wxLogMessage(
			_T("Connected to 3D controller!"));
	TransferDataToWindow();
}

void DialogSetup6DOFController::OnDisconnect(wxCommandEvent& event)
{
	if(control == NULL) return;
	control->Close();
	wxLogMessage(_T("Disconnected from 3D controller!"));
	TransferDataToWindow();
}
void DialogSetup6DOFController::OnClose(wxCommandEvent& event)
{
	this->Close();
}

void DialogSetup6DOFController::OnTimer(wxTimerEvent& event)
{
	if(control == NULL) return;
	if(!control->IsOpen()) return;

	control->Pump();

	m_sliderTx->SetValue(control->GetAxis(0));
	m_sliderTy->SetValue(control->GetAxis(1));
	m_sliderTz->SetValue(control->GetAxis(2));
	m_sliderRx->SetValue(control->GetAxis(3));
	m_sliderRy->SetValue(control->GetAxis(4));
	m_sliderRz->SetValue(control->GetAxis(5));
}
