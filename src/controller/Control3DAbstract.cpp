/*
 * Control3DAbstract.cpp
 *
 *  Created on: 21.07.2009
 *      Author: toby
 */

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
	return port.Open(connection.ToAscii(),9600);
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
	if(!port.IsOpen()) return false;
	char temp[128];
	unsigned char i, j;
	i = port.ReadData(temp, 128);
	while(i != 0){
		for(j = 0; j < i; j++)
			DataIn((unsigned char)temp[j]);
		i = port.ReadData(temp, 128);
	}
	return true;
}
