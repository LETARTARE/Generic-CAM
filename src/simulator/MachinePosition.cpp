//============================================================================
// Name        : MachinePosition.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 08.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "MachinePosition.h"
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

float MachinePosition::AbsXYZ()
{
	return sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
}

float MachinePosition::AbsUVW()
{
	return sqrt(axisU * axisU + axisV * axisV + axisW * axisW);
}

float MachinePosition::AbsXYZUVW()
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
	float nCount = 0;
	bool negativ;
	bool isCommand;
	unsigned int i;
	lineOfText.MakeUpper();
	lineOfText += _T(" ");
//	wxLogMessage(lineOfText);
	for(i = 0; i < lineOfText.Length(); i++){
		c = lineOfText[i];
		if(c == '(') state += 4;
		if(c == ')') state -= 4;
		if(c == 'F' || c == 'G' || c == 'I' || c == 'J' || c == 'K' || c == 'A'
				|| c == 'B' || c == 'C' || c == 'U' || c == 'V' || c == 'W'
				|| c == 'X' || c == 'Y' || c == 'Z' || c == 'M' || c == 'N'
				|| c == 'R')
			isCommand = true;
		else
			isCommand = false;

		if(state > 1 && state < 4
				&& (isCommand || i == lineOfText.Length() - 1)){
			// Evaluate Command
			if(negativ) number = -number;
			switch(command){
			case 'F':
				feed = number;
				break;
			case 'G':
				break;

			case 'I':
				radiusI = number;
				break;
			case 'J':
				radiusJ = number;
				break;
			case 'K':
				radiusK = number;
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
				axisU = number;
				break;
			case 'V':
				axisV = number;
				break;
			case 'W':
				axisW = number;
				break;

			case 'X':
				axisX = number;
				break;
			case 'Y':
				axisY = number;
				break;
			case 'Z':
				axisZ = number;
				break;

			case 'M':
				break;
			case 'N':
				// Ignore linenumber
				break;

			case 'R':
				break;
			default:
				wxLogMessage(wxString(_T("Unknown G-Code: %c"), command));
				break;
			}
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
