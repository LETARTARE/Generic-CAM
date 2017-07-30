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
///////////////////////////////////////////////////////////////////////////////

#include "MachinePosition.h"

#include <wx/log.h>
#include <wx/arrimpl.cpp>

#include <math.h>
#include <locale.h>
#include <float.h>

WX_DEFINE_OBJARRAY(ArrayOfMachinePosition)

MachinePosition::MachinePosition(double x, double y, double z, double a,
		double b, double c, double u, double v, double w)
{
	X = x;
	Y = y;
	Z = z;
	A = a;
	B = b;
	C = c;
	U = u;
	V = v;
	W = w;


}

MachinePosition::~MachinePosition()
{
}

//void MachinePosition::Zero(void)
//{
//	X = Y = Z = 0.0;
//	A = B = C = 0.0;
//	U = V = W = 0.0;
//
//	feed = 1.0;
//}

double MachinePosition::AbsXYZ() const
{
	return sqrt(X * X + Y * Y + Z * Z);
}

double MachinePosition::AbsUVW() const
{
	return sqrt(U * U + V * V + W * W);
}

double MachinePosition::AbsXYZUVW() const
{
	return sqrt(
			X * X + Y * Y + Z * Z + U * U
					+ V * V + W * W);
}

//bool MachinePosition::ParseGCodeLine(wxString lineOfText)
//{
//
//	code = GCodeBlock(lineOfText);
//	if(code)
//
//	duration = 1.0;

//	unsigned char state = 0;
//	unsigned char c;
//	unsigned char command = 'N';
//	double number;
//	const double conversionFactor = 0.01 / 2.54; // 1 cm = 2.54 inch
//	double nCount = 0;
//	bool negativ = false;
//	bool isCommand;
//	unsigned int i;
//	lineOfText.MakeUpper();
//	lineOfText += _T(" ");
//	//wxLogMessage(lineOfText);
//	for(i = 0; i < lineOfText.Length(); i++){
//		c = lineOfText[i];
//		if(c == '(') state += 4;
//		if(c == ')') state -= 4;
//		if(c >= 'A' && c <= 'Z')
//			isCommand = true;
//		else
//			isCommand = false;
//
//		if(state > 1 && state < 4
//				&& (isCommand || i == lineOfText.Length() - 1)){
//			// Evaluate Command
//			//wxLogMessage(wxString::Format(_T("Commado: %c mit %f"), command,
//			//	number));
//
//			if(negativ) number = -number;
//			switch(command){
//			case 'F':
//				feed = number;
//				break;
//			case 'G':
//				break;
//
//			case 'I':
//				radiusI = number * conversionFactor;
//				break;
//			case 'J':
//				radiusJ = number * conversionFactor;
//				break;
//			case 'K':
//				radiusK = number * conversionFactor;
//				break;
//			case 'R':
//				radiusR = number * conversionFactor;
//				break;
//
//			case 'A':
//				A = number;
//				break;
//			case 'B':
//				B = number;
//				break;
//			case 'C':
//				C = number;
//				break;
//
//			case 'U':
//				U = number * conversionFactor;
//				break;
//			case 'V':
//				V = number * conversionFactor;
//				break;
//			case 'W':
//				W = number * conversionFactor;
//				break;
//
//			case 'X':
//				X = number * conversionFactor;
//				break;
//			case 'Y':
//				Y = number * conversionFactor;
//				break;
//			case 'Z':
//				Z = number * conversionFactor;
//				break;
//
//			case 'M':
//				break;
//			case 'N':
//				// Ignore linenumber
//				break;
//
//			default:
//				wxLogMessage(
//						wxString::Format(_T("Unknown G-Code: %c"), command));
//				break;
//			}
//			state = 0;
//		}
//
//		switch(state){
//		case 0:
//			if(isCommand){
//				command = c;
//				state = 1;
//				negativ = false;
//				number = 0;
//			}
//			break;
//		case 1:
//			if(c == '-'){
//				negativ = true;
//				state = 2;
//			}
//			if(c >= '0' && c <= '9'){
//				number = (double) (c - '0');
//				state = 2;
//			}
//			if(c == ',' || c == '.'){
//				state = 3;
//				nCount = 1.0;
//				break;
//			}
//			break;
//		case 2:
//			if(c == '-'){
//				if(negativ) wxLogError(
//						_T("ParseGCodeLine: Double '-' in G-Code!"));
//			}
//			if(c >= '0' && c <= '9'){
//				number = number * 10 + (double) (c - '0');
//				break;
//			}
//			if(c == ',' || c == '.'){
//				state = 3;
//				nCount = 1.0;
//				break;
//			}
//
//			break;
//		case 3:
//			if(c >= '0' && c <= '9'){
//				nCount /= 10;
//				number += (double) (c - '0') * nCount;
//				break;
//			}
//			break;
//		}
//	}
//
//	return true;
//}

//unsigned char MachinePosition::GetGNumber(void) const
//{
//	const bool doCircle = (fabs(this->I) > FLT_EPSILON
//			|| fabs(this->J) > FLT_EPSILON || fabs(this->K) > FLT_EPSILON
//			|| fabs(this->R) > FLT_EPSILON);
//	if(!(this->isCutting)){
//		return 0;
//	}else{
//		if(doCircle){
//			if(this->isRotationPositiv){
//				return 3;
//			}else{
//				return 2;
//			}
//		}else{
//			return 1;
//		}
//	}
//}

MachinePosition & MachinePosition::operator+=(const MachinePosition& a)
{
	this->X += a.X;
	this->Y += a.Y;
	this->Z += a.Z;
	this->A += a.A;
	this->B += a.B;
	this->C += a.C;
	this->U += a.U;
	this->V += a.V;
	this->W += a.W;
	return *this;
}

const MachinePosition MachinePosition::operator+(const MachinePosition &b) const
{
	MachinePosition temp = *this;
	temp += b;
	return temp;
}

MachinePosition & MachinePosition::operator-=(const MachinePosition& a)
{
	this->X -= a.X;
	this->Y -= a.Y;
	this->Z -= a.Z;
	this->A -= a.A;
	this->B -= a.B;
	this->C -= a.C;
	this->U -= a.U;
	this->V -= a.V;
	this->W -= a.W;
	return *this;
}

const MachinePosition MachinePosition::operator-(const MachinePosition &b) const
{
	MachinePosition temp = *this;
	temp -= b;
	return temp;
}

const MachinePosition MachinePosition::operator-() const
{
	MachinePosition temp(-this->X, -this->Y, -this->Z, -this->A,
			-this->B, -this->C, -this->U, -this->V,
			-this->W);
	return temp;
}

MachinePosition & MachinePosition::operator*=(const double &b)
{
	this->X *= b;
	this->Y *= b;
	this->Z *= b;
	this->A *= b;
	this->B *= b;
	this->C *= b;
	this->U *= b;
	this->V *= b;
	this->W *= b;
	return *this;
}

const MachinePosition MachinePosition::operator*(const double &b) const
{
	MachinePosition temp = *this;
	temp *= b;
	return temp;
}

MachinePosition & MachinePosition::operator/=(const double &b)
{
	this->X /= b;
	this->Y /= b;
	this->Z /= b;
	this->A /= b;
	this->B /= b;
	this->C /= b;
	this->U /= b;
	this->V /= b;
	this->W /= b;
	return *this;
}

const MachinePosition MachinePosition::operator/(const double &b) const
{
	MachinePosition temp = *this;
	temp /= b;
	return temp;
}

//wxString MachinePosition::GenerateCommandXYZ(void)
//{
//	unsigned char gNum = this->GetGNumber();
//	wxString temp = wxString::Format(_T("G%02u"), gNum);
//
//	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->X * 1000.0,
//			this->Y * 1000.0, this->Z * 1000.0);
//
//	if(gNum == 2 || gNum == 3){
//		if(fabs(this->radiusR) > FLT_EPSILON){
//			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
//		}else{
//			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"),
//					this->radiusI * 1000.0, this->radiusJ * 1000.0,
//					this->radiusK * 1000.0);
//		}
//	}
//	return temp;
//}
//
//wxString MachinePosition::GenerateCommandXYZABC(void)
//{
//	unsigned char gNum = this->GetGNumber();
//	wxString temp = wxString::Format(_T("G%02u"), gNum);
//
//	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->X * 1000.0,
//			this->Y * 1000.0, this->Z * 1000.0);
//	temp += wxString::Format(_T(" A%.2f B%.2f C%.2f"), this->A * 1000.0,
//			this->B * 1000.0, this->C * 1000.0);
//
//	if(gNum == 2 || gNum == 3){
//		if(fabs(this->radiusR) > FLT_EPSILON){
//			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
//		}else{
//			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"),
//					this->radiusI * 1000.0, this->radiusJ * 1000.0,
//					this->radiusK * 1000.0);
//		}
//	}
//	return temp;
//}
//wxString MachinePosition::GenerateCommandXYZABCUVW(void)
//{
//	unsigned char gNum = this->GetGNumber();
//	wxString temp = wxString::Format(_T("G%02u"), gNum);
//
//	temp += wxString::Format(_T(" X%.2f Y%.2f Z%.2f"), this->X * 1000.0,
//			this->Y * 1000.0, this->Z * 1000.0);
//	temp += wxString::Format(_T(" A%.2f B%.2f C%.2f"), this->A * 1000.0,
//			this->B * 1000.0, this->C * 1000.0);
//	temp += wxString::Format(_T(" U%.2f V%.2f W%.2f"), this->U * 1000.0,
//			this->V * 1000.0, this->W * 1000.0);
//
//	if(gNum == 2 || gNum == 3){
//		if(fabs(this->radiusR) > FLT_EPSILON){
//			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
//		}else{
//			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"),
//					this->radiusI * 1000.0, this->radiusJ * 1000.0,
//					this->radiusK * 1000.0);
//		}
//	}
//	return temp;
//}
//
//wxString MachinePosition::GenerateCommandDiff(
//		const MachinePosition &oldPosition)
//{
//	wxString temp;
//	unsigned char gNum = this->GetGNumber();
//
//	if(oldPosition.GetGNumber() != gNum){
//		temp = wxString::Format(_T("G%02u"), gNum);
//	}
//	if(fabs(this->X - oldPosition.X) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" X%.2f"), this->X * 1000.0);
//	if(fabs(this->Y - oldPosition.Y) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" Y%.2f"), this->Y * 1000.0);
//	if(fabs(this->Z - oldPosition.Z) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" Z%.2f"), this->Z * 1000.0);
//
//	if(fabs(this->A - oldPosition.A) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" A%.2f"), this->A * 1000.0);
//	if(fabs(this->B - oldPosition.B) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" B%.2f"), this->B * 1000.0);
//	if(fabs(this->C - oldPosition.C) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" C%.2f"), this->C * 1000.0);
//
//	if(fabs(this->U - oldPosition.U) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" U%.2f"), this->U * 1000.0);
//	if(fabs(this->V - oldPosition.V) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" V%.2f"), this->V * 1000.0);
//	if(fabs(this->W - oldPosition.W) > FLT_EPSILON) temp +=
//			wxString::Format(_T(" W%.2f"), this->W * 1000.0);
//
//	if(gNum == 2 || gNum == 3){
//		if(fabs(this->radiusR) > FLT_EPSILON){
//			temp += wxString::Format(_T(" R%.2f"), this->radiusR * 1000.0);
//		}else{
//			temp += wxString::Format(_T(" I%.2f J%.2f K%.2f"),
//					this->radiusI * 1000.0, this->radiusJ * 1000.0,
//					this->radiusK * 1000.0);
//		}
//	}
//	return temp;
//}

