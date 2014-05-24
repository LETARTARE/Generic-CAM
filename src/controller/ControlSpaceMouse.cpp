///////////////////////////////////////////////////////////////////////////////
// Name               : ControlSpaceMouse.cpp
// Purpose            : Class to get data from a Spaceball controller.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 31.01.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "ControlSpaceMouse.h"
#include <string>
#include <stdint.h>

#include <wx/log.h>

ControlSpaceMouse::ControlSpaceMouse(void)
{
	InBuffer[0] = 0;
	idx = 0;
	isInitialized = false;
}

ControlSpaceMouse::~ControlSpaceMouse(void)
{

}

bool ControlSpaceMouse::Open(void)
{
	bool flag = Control3DAbstract::Open();
	isInitialized = false;
	return flag;
}

void ControlSpaceMouse::InitDevice()
{
	InBuffer[0] = 0;
	idx = 0;

	// Start of data transmission
	char OutBuffer[40];
	OutBuffer[0] = 0;
	strcpy((char *) OutBuffer, "\r\rm3\r");
	port.SendData(OutBuffer, strlen(OutBuffer));
	isInitialized = true;
}

bool ControlSpaceMouse::ProcessPacket()
{
	//static unsigned char spaceorb_errors[7][256] = { "EEPROM storing 0 failed", "Receive queue overflow", "Transmit queue timeout","Bad packet", "Power brown-out", "EEPROM checksum error", "Hardware fault" };
	//unsigned char c = 0;
	unsigned char i;

	// TODO: Find a more general was to initialize the device.
	// The initialize function is called after the first packet is received. If
	// it is done directly after opening of the port, the device is not yet ready
	// to receive commands.
	if(!isInitialized) InitDevice();

	if(idx < 2) return false;

	unsigned int data[(CONTROLSPACEMOUSE_MAXDATALENGTH >> 2) + 1];

	bool error = false;
	// Convert Nibbles to Bytes
	// Command at InBuffer[0].
	unsigned char c;

	const unsigned char check[17] = "0AB3D56GH9:K<MN?";
	for(i = 0; i < (idx - 1); i++){
		c = InBuffer[i + 1];
		if(check[c & 15] != c) error = true;
		if(i % 4 == 0){
			data[i >> 2] = c & 15;
		}else{
			data[i >> 2] = (data[i >> 2] << 4) | (c & 15);
		}
	}

	if(error) return false; // Wrong characters in stream

	switch(InBuffer[0]){
	case 'd':
		if(idx != 25) break;
		Axis[0] = data[0] - (1 << 15);
		Axis[1] = data[1] - (1 << 15);
		Axis[2] = data[2] - (1 << 15);
		Axis[3] = data[3] - (1 << 15);
		Axis[4] = data[4] - (1 << 15);
		Axis[5] = data[5] - (1 << 15);

		//wxLogMessage(_T("%8u %8u %8u %8u %8u %8u"), data[0], data[1], data[2],
		//	data[3], data[4], data[5]);

		//		for(i = 0; i < 6; i++)
		//			Axis[i] = (((int16_t) Axis[i]) << 16) >> 16;
		//
		//
		//		// Right Handed Coordinate System
		//		Axis[2] = -Axis[2]; // Tz = -Tz
		//		Axis[5] = -Axis[5]; // Rz = -Rz
		hasChanged = true;
		break;
	case 'k':
		Button[0] = (data[0] & (1 << 8));
		Button[1] = (data[0] & (1 << 9));
		Button[2] = (data[0] & (1 << 10));
		Button[3] = (data[0] & (1 << 11));
		Button[4] = (data[0] & (1 << 4));
		Button[5] = (data[0] & (1 << 5));
		Button[6] = (data[0] & (1 << 6));
		Button[7] = (data[0] & (1 << 7));
		Button[8] = (data[0] & (1 << 0));
		hasChanged = true;
		break;
	}
	return true;
}

void ControlSpaceMouse::DataIn(unsigned char c)
{
	if(c == '\r'){
		if(idx) ProcessPacket();
		idx = 0;
	}
	if(idx < CONTROLSPACEMOUSE_MAXDATALENGTH){

		if(idx == 0){
			if(c == 'k' || c == 'q' || c == 'n' || c == 'm' || c == 'd'){
				InBuffer[idx++] = c;
			}
		}else{
			InBuffer[idx++] = c;
		}
	}
}
