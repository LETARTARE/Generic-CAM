/*
 * Control6DOF.cpp
 *
 *  Created on: 21.07.2009
 *      Author: toby
 */

#include "Control6DOF.h"

Control6DOF::Control6DOF()
{
	int i;

	for(i = 0; i < 6; i++){
		Axis[i] = 0;
	}
	for(i = 0; i < CONTROL6DOF_MAXBUTTONS; i++){
		Button[i] = false;
	}
}

Control6DOF::~Control6DOF()
{

}

void Control6DOF::InitDevice()
{

}

void Control6DOF::SetPort(wxString connection)
{
	this->connection = connection;
}

wxString Control6DOF::GetPort()
{
	return connection;
}

bool Control6DOF::Open(void)
{
	return port.Open(connection.ToAscii(),9600);
}

void Control6DOF::Close(void)
{
	port.Close();
}

int Control6DOF::GetButton(unsigned char i) const
{
	if(i > (CONTROL6DOF_MAXBUTTONS)) return false;
	return Button[i];
}

int Control6DOF::GetAxis(unsigned char i) const
{
	if(i > 5) return 0;
	return Axis[i];
}

bool Control6DOF::Pump()
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
