///////////////////////////////////////////////////////////////////////////////
// Name               : Control3D.cpp
// Purpose            : Main class for 6DOF controller
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.12.2009
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

char Control3D::GetType(void)
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

void Control3D::Close(void)
{
	controller->Close();
}

bool Control3D::IsOpen(void)
{
	if(controller == NULL) return false;
	return controller->IsConnected();
}

bool Control3D::HasChanged(void)
{
	if(controller == NULL) return 0;
	return controller->HasChanged();
}

bool Control3D::IsIdle(void)
{
	if(controller == NULL) return true;
	unsigned char i;
	for(i = 0; i < 6; i++)
		if(controller->GetAxis(i) != 0) return false;
	for(i = 0; i < CONTROL3DABSTRACT_MAXBUTTONS; i++)
		if(controller->GetButton(i) != 0) return false;
	return true;
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

wxString Control3D::GetPort(void)
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

bool Control3D::Pump(void)
{
	if(controller == NULL) return false;
	return controller->Pump();
}

bool Control3D::Load(wxConfig *config)
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

	bool found = config->Read(_T("Control_Port"), &str);

	if(!found || str.IsEmpty()){
#ifdef __LINUX
		str = _T("/dev/ttyS0");
#endif
#ifdef __WIN
		str = _T("COM1");
#endif
	}
	SetPort(str);
	if(config->Read(_T("Control_ActivateOnStartUp"), &str)){
		if(str == _T("Yes")){
			this->Open();
		}
	}
	return true;
}

bool Control3D::Save(wxConfig *config)
{
	wxASSERT(config!=NULL);

	if(controller == NULL) return false;

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

	return true;
}
