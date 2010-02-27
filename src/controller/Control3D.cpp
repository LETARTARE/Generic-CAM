/*
 * Control3D.cpp
 *
 *  Created on: 01.12.2009
 *      Author: toby
 */

//Did this line end up in the repository?

#include "Control3D.h"

Control3D::Control3D()
{
	controller = NULL;
	SetType(1);
}

Control3D::~Control3D()
{
	Close();
	if(controller != NULL) delete controller;
}

bool Control3D::SetType(char id)
{
	if(controller != NULL){
		if(id == controller->ReturnID()) return true;
		delete controller;
		controller = NULL;
	}
	switch(id){
	case CONTROLSPACEBALL_ID:
		controller = new ControlSpaceBall;
		break;
	case CONTROLSPACEORB_ID:
		controller = new ControlSpaceOrb;
		break;
	case CONTROLSPACEMOUSE_ID:
		controller = new ControlSpaceMouse;
		break;
	default:
		return false;
	}
	return true;
}

char Control3D::GetType()
{
	if(controller == NULL) return 0;
	return controller->ReturnID();
}

bool Control3D::Open(wxString connection)
{
	if(controller == NULL) return false;
	Close();
	controller->SetPort(connection);
	return controller->Open();
}

bool Control3D::Open(void)
{
	if(controller == NULL) return false;
	Close();
	return controller->Open();
}

void Control3D::Close()
{
	controller->Close();
}

bool Control3D::IsOpen()
{
	if(controller == NULL) return false;
	return controller->IsConnected();
}

int Control3D::GetButton(unsigned char i)
{
	if(controller == NULL) return 0;
	return controller->GetButton(i);
}

int Control3D::GetAxis(unsigned char i)
{
	if(controller == NULL) return 0;
	return controller->GetAxis(i);
}

wxString Control3D::GetPort()
{
	if(controller == NULL) return _T("");
	return controller->GetPort();
}

bool Control3D::SetPort(wxString port)
{
	if(controller == NULL) return false;
	controller->SetPort(port);
	return true;
}

bool Control3D::Pump()
{
	if(controller == NULL) return false;
	return controller->Pump();
}

bool Control3D::GetConfigFrom(wxConfig *config)
{
	wxASSERT(config!=NULL);

	wxString str;

	if(config->Read(_T("Control_Type"), &str)){
		if(str == _T("Spaceball")){
			SetType(CONTROLSPACEBALL_ID);
		}
		if(str == _T("Spaceorb")){
			SetType(CONTROLSPACEORB_ID);
		}
		if(str == _T("Spacemouse")){
			SetType(CONTROLSPACEMOUSE_ID);
		}

	}

	if(config->Read(_T("Control_Port"), &str)){
		SetPort(str);
	}else{
#ifdef __LINUX
		SetPort(_T("/dev/ttyS0"));
#endif
#ifdef __WIN
		SetPort(_T("COM1"));
#endif
	}
	if(config->Read(_T("Control_ActivateOnStartUp"), &str)){
		if(str == _T("Yes")){
			this->Open();
		}
	}
	return true;
}

bool Control3D::WriteConfigTo(wxConfig *config)
{
	wxASSERT(config!=NULL);

	if(controller != NULL){
		switch(GetType()){
		case CONTROLSPACEBALL_ID:
			config->Write(_T("Control_Type"), _T("Spaceball"));
			break;
		case CONTROLSPACEORB_ID:
			config->Write(_T("Control_Type"), _T("Spaceorb"));
			break;
		case CONTROLSPACEMOUSE_ID:
			config->Write(_T("Control_Type"), _T("Spacemouse"));
			break;
		}

		config->Write(_T("Control_Port"), GetPort());

		if(IsOpen()){
			config->Write(_T("Control_ActivateOnStartUp"), _T("Yes"));
		}else{
			config->Write(_T("Control_ActivateOnStartUp"), _T("No"));
		}
	}else{
		return false;
	}
	return true;
}
