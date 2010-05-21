///////////////////////////////////////////////////////////////////////////////
// Name               : Control6DOFDialog.cpp
// Purpose            : Setup dialog for 6DOF controller.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "Control6DOFDialog.h"
#include <wx/debug.h>

//TODO: There must be a way to get the timer IDs dynamically.
#define TIMER_DIALOGCONTROL6DOF 1900

Control6DOFDialog::Control6DOFDialog(wxWindow* parent) :
	GUIControl6DOFDialog(parent)
{

	radioDeviceSelect->SetItemToolTip(0, _("Spaceball by Spacetec IMC"));
	radioDeviceSelect->SetItemToolTip(1, _("Spaceorb by Spacetec IMC"));
	radioDeviceSelect->SetItemToolTip(2,
			_("Spacemouse by Logitech/3DConnexion"));

	control = NULL;

	timer.SetOwner(this, TIMER_DIALOGCONTROL6DOF);

	this->Connect(wxEVT_TIMER, wxTimerEventHandler(Control6DOFDialog::OnTimer),
			NULL, this);

	timer.Start(100);


	//	timer.Connect( wxEVT_TIMER, wxCommandEventHandler(Control6DOFDialog::OnTimer ), NULL, this );

	//	EVT_TIMER(RINGELWOLF_TIMER_DIALOGCONTROL6DOF, Control6DOFDialog::OnTimer)


}

Control6DOFDialog::~Control6DOFDialog()
{
}
void Control6DOFDialog::InsertController(Control3D& control)
{
	if(&control != NULL){
		this->control = &control;
		UpdateData();
	}
}
void Control6DOFDialog::UpdateData()
{
	wxASSERT(control!=NULL);

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
}

void Control6DOFDialog::OnConnect(wxCommandEvent& event)
{
	wxASSERT(this->control!=NULL);

	unsigned char i = radioDeviceSelect->GetSelection() + 1;

	if(this->control->IsOpen()){
		this->control->Close();
		wxLogMessage(_T("control closed (but should not be open first place)!"));
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
	}
	control->SetType(i);
	if(control->Open(textPort->GetValue())) wxLogMessage(
			_T("Connected to 3D controller!"));
	UpdateData();
}

void Control6DOFDialog::OnDisconnect(wxCommandEvent& event)
{
	wxASSERT(this->control!=NULL);
	control->Close();
	wxLogMessage(_T("Disconnected from 3D controller!"));
	UpdateData();
}
void Control6DOFDialog::OnClose(wxCommandEvent& event)
{
	this->Close();
}

void Control6DOFDialog::OnTimer(wxTimerEvent& event)
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
