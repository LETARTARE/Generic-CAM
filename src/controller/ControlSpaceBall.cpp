///////////////////////////////////////////////////////////////////////////////
// Name               : ControlSpaceBall.cpp
// Purpose            : Class to get data from a Spaceball controller.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#include "ControlSpaceBall.h"

#include <string>
#include <stdint.h>

ControlSpaceBall::ControlSpaceBall(void)
{
	InBuffer[0] = 0;
	idx = 0;
}

ControlSpaceBall::~ControlSpaceBall(void)
{

}

void ControlSpaceBall::InitDevice()
{
	InBuffer[0] = 0;
	idx = 0;


	// Start of data transmission
	char OutBuffer[40];
	OutBuffer[0] = 0;
	strcpy((char *) OutBuffer, "CB\rNT\rFTp\rFRp\rP@r@r\rMSSV\rZ\rBcC\r");
	port.SendData(OutBuffer, strlen(OutBuffer));
}

bool ControlSpaceBall::ProcessPacket()
{
	//static unsigned char spaceorb_errors[7][256] = { "EEPROM storing 0 failed", "Receive queue overflow", "Transmit queue timeout","Bad packet", "Power brown-out", "EEPROM checksum error", "Hardware fault" };
	//unsigned char c = 0;
	unsigned char i;

	if(idx < 2) return false;
	//	for (i = 0; i < idx; i++) c ^= Data[i];
	//if (c) return false;
	switch(InBuffer[0]){
	case '@': /* Reset packet */
		if(InBuffer[1] == '2') InitDevice();
		break;
	case 'D':
		if(idx != 15) break;
		Axis[0] = (InBuffer[3] << 8) | (InBuffer[4]);
		Axis[1] = (InBuffer[5] << 8) | (InBuffer[6]);
		Axis[2] = (InBuffer[7] << 8) | (InBuffer[8]);
		Axis[3] = (InBuffer[9] << 8) | (InBuffer[10]);
		Axis[4] = (InBuffer[11] << 8) | (InBuffer[12]);
		Axis[5] = (InBuffer[13] << 8) | (InBuffer[14]);

		for(i = 0; i < 6; i++)
			Axis[i] = (((int16_t) Axis[i]) << 16) >> 16;


		// Right Handed Coordinate System
		Axis[2] = -Axis[2]; // Tz = -Tz
		Axis[5] = -Axis[5]; // Rz = -Rz
		hasChanged = true;
		break;
	case 'K':
		Button[0] = (InBuffer[2] & 1);
		Button[1] = (InBuffer[2] & 2);
		Button[2] = (InBuffer[2] & 4);
		Button[3] = (InBuffer[2] & 8);
		Button[4] = (InBuffer[1] & 1);
		Button[5] = (InBuffer[1] & 2);
		Button[6] = (InBuffer[1] & 4);
		Button[7] = (InBuffer[1] & 8);
		Button[8] = (InBuffer[1] & 16);
		hasChanged = true;
		break;
	}
	return true;
}

void ControlSpaceBall::DataIn(unsigned char c)
{
	if(c == '\r'){
		if(idx) ProcessPacket();
		idx = 0;
	}
	if(idx < CONTROLSPACEBALL_MAXDATALENGTH){

		if(idx == 0){
			if(c == 'D' || c == 'K' || c == '.' || c == 'C' || c == 'F' || c
					== 'M' || c == 'N' || c == 'P' || c == '@' || c == 'E' || c
					== 'Z'){
				InBuffer[idx++] = c;
			}
		}else{
			InBuffer[idx++] = c;
		}
	}
}
