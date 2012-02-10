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
#include <float.h>
#include <locale.h>

MachinePosition::MachinePosition(double x, double y, double z, double a,
		double b, double c, double u, double v, double w)
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
	radiusI = 0.0;
	radiusJ = 0.0;
	radiusK = 0.0;
	radiusR = 0.0;

	isRotationPositiv = true;
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
	radiusR = 0.0;
	isRotationPositiv = true;
	duration = 1.0;
	feed = 1.0;
	isCutting = false;
}

double MachinePosition::AbsXYZ() const
{
	return sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
}

double MachinePosition::AbsUVW() const
{
	return sqrt(axisU * axisU + axisV * axisV + axisW * axisW);
}

double MachinePosition::AbsXYZUVW() const
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
	unsigned char command = 'N';
	double number;
	double conversionFactor = 0.01 / 2.54; // 1 cm = 2.54 inch
	double nCount = 0;
	bool negativ = false;
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
			case 'R':
				radiusR = number * conversionFactor;
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
				number = (double) (c - '0');
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
				number = number * 10 + (double) (c - '0');
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
				number += (double) (c - '0') * nCount;
				break;
			}
			break;
		}
	}

	return true;
}

unsigned char MachinePosition::GetGNumber(void) const
{
	bool doCircle = (fabs(this->radiusI) > FLT_EPSILON || fabs(this->radiusJ)
			> FLT_EPSILON || fabs(this->radiusK) > FLT_EPSILON || fabs(
			this->radiusR) > FLT_EPSILON);
	if(!(this->isCutting)){
		return 0;
	}else{
		if(doCircle){
			if(this->isRotationPositiv){
				return 3;
			}else{
				return 2;
			}
		}else{
			return 1;
		}
	}
}

wxString MachinePosition::GenerateCommandXYZ(void)
{
	unsigned char gNum = this->GetGNumber();
	wxString temp = wxString::Format(_T("G%02u"), gNum);

	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->axisX * 1000.0,
			this->axisY * 1000.0, this->axisZ * 1000.0);

	if(gNum == 2 || gNum == 3){
		if(fabs(this->radiusR) > FLT_EPSILON){
			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
		}else{
			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"), this->radiusI
					* 1000.0, this->radiusJ * 1000.0, this->radiusK * 1000.0);
		}
	}
	return temp;
}

wxString MachinePosition::GenerateCommandXYZABC(void)
{
	unsigned char gNum = this->GetGNumber();
	wxString temp = wxString::Format(_T("G%02u"), gNum);

	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->axisX * 1000.0,
			this->axisY * 1000.0, this->axisZ * 1000.0);
	temp += wxString::Format(_T(" A%.2f B%.2f C%.2f"), this->axisA * 1000.0,
			this->axisB * 1000.0, this->axisC * 1000.0);

	if(gNum == 2 || gNum == 3){
		if(fabs(this->radiusR) > FLT_EPSILON){
			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
		}else{
			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"), this->radiusI
					* 1000.0, this->radiusJ * 1000.0, this->radiusK * 1000.0);
		}
	}
	return temp;
}
wxString MachinePosition::GenerateCommandXYZABCUVW(void)
{
	unsigned char gNum = this->GetGNumber();
	wxString temp = wxString::Format(_T("G%02u"), gNum);

	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->axisX * 1000.0,
			this->axisY * 1000.0, this->axisZ * 1000.0);
	temp += wxString::Format(_T(" A%.2f B%.2f C%.2f"), this->axisA * 1000.0,
			this->axisB * 1000.0, this->axisC * 1000.0);
	temp += wxString::Format(_T(" U%.2f V%.2f W%.2f"), this->axisU * 1000.0,
			this->axisV * 1000.0, this->axisW * 1000.0);

	if(gNum == 2 || gNum == 3){
		if(fabs(this->radiusR) > FLT_EPSILON){
			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
		}else{
			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"), this->radiusI
					* 1000.0, this->radiusJ * 1000.0, this->radiusK * 1000.0);
		}
	}
	return temp;
}

wxString MachinePosition::GenerateCommandDiff(
		const MachinePosition &oldPosition)
{
	wxString temp;
	unsigned char gNum = this->GetGNumber();

	if(oldPosition.GetGNumber() != gNum){
		temp = wxString::Format(_T("G%02u"), gNum);
	}
	if(fabs(this->axisX - oldPosition.axisX) > FLT_EPSILON) temp
			+= wxString::Format(_T(" X%.2f"), this->axisX * 1000.0);
	if(fabs(this->axisY - oldPosition.axisY) > FLT_EPSILON) temp
			+= wxString::Format(_T(" Y%.2f"), this->axisY * 1000.0);
	if(fabs(this->axisZ - oldPosition.axisZ) > FLT_EPSILON) temp
			+= wxString::Format(_T(" Z%.2f"), this->axisZ * 1000.0);

	if(fabs(this->axisA - oldPosition.axisA) > FLT_EPSILON) temp
			+= wxString::Format(_T(" A%.2f"), this->axisA * 1000.0);
	if(fabs(this->axisB - oldPosition.axisB) > FLT_EPSILON) temp
			+= wxString::Format(_T(" B%.2f"), this->axisB * 1000.0);
	if(fabs(this->axisC - oldPosition.axisC) > FLT_EPSILON) temp
			+= wxString::Format(_T(" C%.2f"), this->axisC * 1000.0);

	if(fabs(this->axisU - oldPosition.axisU) > FLT_EPSILON) temp
			+= wxString::Format(_T(" U%.2f"), this->axisU * 1000.0);
	if(fabs(this->axisV - oldPosition.axisV) > FLT_EPSILON) temp
			+= wxString::Format(_T(" V%.2f"), this->axisV * 1000.0);
	if(fabs(this->axisW - oldPosition.axisW) > FLT_EPSILON) temp
			+= wxString::Format(_T(" W%.2f"), this->axisW * 1000.0);

	if(gNum == 2 || gNum == 3){
		if(fabs(this->radiusR) > FLT_EPSILON){
			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
		}else{
			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"), this->radiusI
					* 1000.0, this->radiusJ * 1000.0, this->radiusK * 1000.0);
		}
	}
	return temp;
}

