///////////////////////////////////////////////////////////////////////////////
// Name               : Control3DAbstract.cpp
// Purpose            : Abstract class for 6DOF controller classes.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.07.2009
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

#include "Control3DAbstract.h"

Control3DAbstract::Control3DAbstract()
{
	int i;

	for(i = 0; i < 6; i++){
		Axis[i] = 0;
	}
	for(i = 0; i < CONTROL3DABSTRACT_MAXBUTTONS; i++){
		Button[i] = false;
	}
	hasChanged = false;
}

Control3DAbstract::~Control3DAbstract()
{

}

void Control3DAbstract::InitDevice()
{

}

void Control3DAbstract::SetPort(wxString connection)
{
	this->connection = connection;
}

wxString Control3DAbstract::GetPort()
{
	return connection;
}

bool Control3DAbstract::Open(void)
{
	return port.Open(connection.ToAscii(), 9600);
}

void Control3DAbstract::Close(void)
{
	port.Close();
}

int Control3DAbstract::GetButton(unsigned char i) const
{
	if(i > (CONTROL3DABSTRACT_MAXBUTTONS)) return false;
	return Button[i];
}

int Control3DAbstract::GetAxis(unsigned char i) const
{
	if(i > 5) return 0;
	return Axis[i];
}

bool Control3DAbstract::Pump()
{
	hasChanged = false;
	if(!port.IsOpen()) return false;
	char temp[128];
	unsigned char i, j;
	i = port.ReadData(temp, 128);
	while(i != 0){
		for(j = 0; j < i; j++)
			DataIn((unsigned char) temp[j]);
		i = port.ReadData(temp, 128);
	}
	return true;
}
