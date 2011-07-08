///////////////////////////////////////////////////////////////////////////////
// Name               : MachinePosition.cpp
// Purpose            : The position of the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.03.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "MachinePosition.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachinePosition)

#include <math.h>
#include <wx/log.h>

MachinePosition::MachinePosition(float x, float y, float z, float a, float b,
		float c, float u, float v, float w)
{
	axisX = x;
	axisY = y;
	axisZ = z;
	axisA = a;
	axisB = b;
	axisC = c;
	axisU = u;
	axisV = v;
	axisW = w;

	duration = 1.0;
	feed = 1.0;
	isCutting = false;
}

MachinePosition::~MachinePosition()
{
}

void MachinePosition::Zero(void)
{
	axisX = axisY = axisZ = 0.0;
	axisA = axisB = axisC = 0.0;
	axisU = axisV = axisW = 0.0;
	radiusI = radiusJ = radiusK = 0.0;
	feed = 1.0;
	duration = 1.0;
}

float MachinePosition::AbsXYZ() const
{
	return sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
}

float MachinePosition::AbsUVW() const
{
	return sqrt(axisU * axisU + axisV * axisV + axisW * axisW);
}

float MachinePosition::AbsXYZUVW() const
{
	return sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ + axisU * axisU
			+ axisV * axisV + axisW * axisW);
}

bool MachinePosition::ParseGCodeLine(wxString lineOfText)
{
	code = lineOfText;
	duration = 1.0;

	unsigned char state = 0;
	unsigned char c;
	unsigned char command;
	float number;
	float conversionFactor = 0.01 / 2.54; // 1 cm = 2.54 inch
	float nCount = 0;
	bool negativ;
	bool isCommand;
	unsigned int i;
	lineOfText.MakeUpper();
	lineOfText += _T(" ");
	//wxLogMessage(lineOfText);
	for(i = 0; i < lineOfText.Length(); i++){
		c = lineOfText[i];
		if(c == '(') state += 4;
		if(c == ')') state -= 4;
		if(c >= 'A' && c <= 'Z')
			isCommand = true;
		else
			isCommand = false;

		if(state > 1 && state < 4
				&& (isCommand || i == lineOfText.Length() - 1)){
			// Evaluate Command
			//wxLogMessage(wxString::Format(_T("Commado: %c mit %f"), command,
			//	number));

			if(negativ) number = -number;
			switch(command){
			case 'F':
				feed = number;
				break;
			case 'G':
				break;

			case 'I':
				radiusI = number * conversionFactor;
				break;
			case 'J':
				radiusJ = number * conversionFactor;
				break;
			case 'K':
				radiusK = number * conversionFactor;
				break;

			case 'A':
				axisA = number;
				break;
			case 'B':
				axisB = number;
				break;
			case 'C':
				axisC = number;
				break;

			case 'U':
				axisU = number * conversionFactor;
				break;
			case 'V':
				axisV = number * conversionFactor;
				break;
			case 'W':
				axisW = number * conversionFactor;
				break;

			case 'X':
				axisX = number * conversionFactor;
				break;
			case 'Y':
				axisY = number * conversionFactor;
				break;
			case 'Z':
				axisZ = number * conversionFactor;
				break;

			case 'M':
				break;
			case 'N':
				// Ignore linenumber
				break;

			case 'R':
				// *conversionFactor;
				break;
			default:
				wxLogMessage(
						wxString::Format(_T("Unknown G-Code: %c"), command));
				break;
			}
			state = 0;
		}

		switch(state){
		case 0:
			if(isCommand){
				command = c;
				state = 1;
				negativ = false;
				number = 0;
			}
			break;
		case 1:
			if(c == '-'){
				negativ = true;
				state = 2;
			}
			if(c >= '0' && c <= '9'){
				number = (float) (c - '0');
				state = 2;
			}
			if(c == ',' || c == '.'){
				state = 3;
				nCount = 1.0;
				break;
			}
			break;
		case 2:
			if(c == '-'){
				if(negativ) wxLogError(
						_T("ParseGCodeLine: Double '-' in G-Code!"));
			}
			if(c >= '0' && c <= '9'){
				number = number * 10 + (float) (c - '0');
				break;
			}
			if(c == ',' || c == '.'){
				state = 3;
				nCount = 1.0;
				break;
			}
			break;
		case 3:
			if(c >= '0' && c <= '9'){
				nCount /= 10;
				number += (float) (c - '0') * nCount;
				break;
			}
			break;
		}
	}

	return true;
}
