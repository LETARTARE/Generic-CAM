/*
 * Control6DOFDialog.cpp
 *
 *  Created on: 25.07.2009
 *      Author: toby
 */
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

	this->Connect(wxEVT_TIMER, wxTimerEventHandler(Control6DOFDialog::OnTimer), NULL,
			this);

	timer.Start(100);

	//	timer.Connect( wxEVT_TIMER, wxCommandEventHandler(Control6DOFDialog::OnTimer ), NULL, this );

	//	EVT_TIMER(RINGELWOLF_TIMER_DIALOGCONTROL6DOF, Control6DOFDialog::OnTimer)


}

Control6DOFDialog::~Control6DOFDialog()
{
}

void Control6DOFDialog::SetupWith(Control3D *control)
{
	if(control != NULL){
		this->control = control;
	}


	wxASSERT(this->control!=NULL);

	if(this->control->IsOpen()){
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
	textPort->ChangeValue(this->control->GetPort());

	unsigned char i = this->control->GetType();
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
	SetupWith();
}

void Control6DOFDialog::OnDisconnect(wxCommandEvent& event)
{
	wxASSERT(this->control!=NULL);
	control->Close();
	wxLogMessage(_T("Disconnected from 3D controller!"));
	SetupWith();
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
