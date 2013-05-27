///////////////////////////////////////////////////////////////////////////////
// Name               : ToolPath.h
// Purpose            : Describing the boundary of the volume to be cut away.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.03.2010
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
//$LastChangedDate: 2011-08-22 22:20:17 +0200 (Mo, 22 Aug 2011) $
//$Revision: 83 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#include "ToolPath.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfToolPath)

#include <wx/log.h>
#include <GL/gl.h>
#include <float.h>

ToolPath::ToolPath()
{
	colorMoving.Set(0.3, 0.8, 0.3);
	colorCutting.Set(0.8, 0.3, 0.3);
}

ToolPath::~ToolPath()
{
}

void ToolPath::Clear(void)
{
	matrix.SetIdentity();
	positions.Empty();
}

//! Overloaded operator for polygon concatenation.
ToolPath & ToolPath::operator+=(const ToolPath &a)
{
	size_t i;
	for(i = 0; i < a.positions.GetCount(); i++)
		this->positions.Add(a.positions[i]);
	return *this;
}

//! Overloaded operator for polygon concatenation.
const ToolPath ToolPath::operator+(const ToolPath &a) const
{
	ToolPath temp = *this;
	temp += a;
	return temp;
}

bool ToolPath::IsEmpty(void) const
{
	return (positions.GetCount() == 0);
}

void ToolPath::ApplyTransformation(void)
{
	size_t i;
	Vector3 temp;
	for(i = 0; i < positions.GetCount(); i++){
		temp.Set(positions[i].axisX, positions[i].axisY, positions[i].axisZ);
		temp = matrix.Transform(temp);
		positions[i].axisX = temp.x;
		positions[i].axisY = temp.y;
		positions[i].axisZ = temp.z;

	}
	matrix.SetIdentity();
}

void ToolPath::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	Vector3 temp;
	for(i = 0; i < positions.GetCount(); i++){
		temp.Set(positions[i].axisX, positions[i].axisY, positions[i].axisZ);
		temp = matrix.Transform(temp);
		positions[i].axisX = temp.x;
		positions[i].axisY = temp.y;
		positions[i].axisZ = temp.z;
	}
}

void ToolPath::Paint(void)
{

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_LINE_STRIP);
	::glNormal3f(0, 0, 1);
	size_t i;
	for(i = 0; i < positions.GetCount(); i++){

		if(positions[i].isCutting)
			::glColor3f(colorCutting.x, colorCutting.y, colorCutting.z);
		else
			::glColor3f(colorMoving.x, colorMoving.y, colorMoving.z);

		::glVertex3f(positions[i].axisX, positions[i].axisY, positions[i].axisZ);
	}

	::glEnd();
	::glPopMatrix();
}

void ToolPath::CalculateMinMaxValues(void)
{
	size_t i;

	minPosition.axisX = +FLT_MAX;
	minPosition.axisY = +FLT_MAX;
	minPosition.axisZ = +FLT_MAX;
	minPosition.axisU = +FLT_MAX;
	minPosition.axisV = +FLT_MAX;
	minPosition.axisW = +FLT_MAX;
	minPosition.axisA = +FLT_MAX;
	minPosition.axisB = +FLT_MAX;
	minPosition.axisC = +FLT_MAX;

	maxPosition.axisX = -FLT_MAX;
	maxPosition.axisY = -FLT_MAX;
	maxPosition.axisZ = -FLT_MAX;
	maxPosition.axisU = -FLT_MAX;
	maxPosition.axisV = -FLT_MAX;
	maxPosition.axisW = -FLT_MAX;
	maxPosition.axisA = -FLT_MAX;
	maxPosition.axisB = -FLT_MAX;
	maxPosition.axisC = -FLT_MAX;

	for(i = 0; i < positions.GetCount(); i++){
		if(positions[i].axisX > maxPosition.axisX) maxPosition.axisX
				= positions[i].axisX;
		if(positions[i].axisY > maxPosition.axisY) maxPosition.axisY
				= positions[i].axisY;
		if(positions[i].axisZ > maxPosition.axisZ) maxPosition.axisZ
				= positions[i].axisZ;
		if(positions[i].axisU > maxPosition.axisU) maxPosition.axisU
				= positions[i].axisU;
		if(positions[i].axisV > maxPosition.axisV) maxPosition.axisV
				= positions[i].axisV;
		if(positions[i].axisW > maxPosition.axisW) maxPosition.axisW
				= positions[i].axisW;
		if(positions[i].axisA > maxPosition.axisA) maxPosition.axisA
				= positions[i].axisA;
		if(positions[i].axisB > maxPosition.axisB) maxPosition.axisB
				= positions[i].axisB;
		if(positions[i].axisC > maxPosition.axisC) maxPosition.axisC
				= positions[i].axisC;

		if(positions[i].axisX < minPosition.axisX) minPosition.axisX
				= positions[i].axisX;
		if(positions[i].axisY < minPosition.axisY) minPosition.axisY
				= positions[i].axisY;
		if(positions[i].axisZ < minPosition.axisZ) minPosition.axisZ
				= positions[i].axisZ;
		if(positions[i].axisU < minPosition.axisU) minPosition.axisU
				= positions[i].axisU;
		if(positions[i].axisV < minPosition.axisV) minPosition.axisV
				= positions[i].axisV;
		if(positions[i].axisW < minPosition.axisW) minPosition.axisW
				= positions[i].axisW;
		if(positions[i].axisA < minPosition.axisA) minPosition.axisA
				= positions[i].axisA;
		if(positions[i].axisB < minPosition.axisB) minPosition.axisB
				= positions[i].axisB;
		if(positions[i].axisC < minPosition.axisC) minPosition.axisC
				= positions[i].axisC;
	}
}

void ToolPath::CleanPath(double tolerance)
{
	ArrayOfMachinePosition temp;
	size_t i, j;
	if(positions.GetCount() < 2) return;

	bool isOnLine;
	bool isSameSort;

	double gx, gy, gz;
	double px, py, pz;
	double s, d2;
	double hx, hy, hz;
	double t2 = tolerance * tolerance;
	double dg;
	size_t lastWritten = 0;
	temp.Add(positions[lastWritten]);
	unsigned char lastGCode = positions[lastWritten].GetGNumber();
	unsigned char gCode;
	for(i = 1; i < positions.GetCount(); i++){
		isOnLine = true;
		isSameSort = true;
		gCode = positions[i].GetGNumber();
		if(gCode != lastGCode) isSameSort = false;
		if(lastGCode != 0 && lastGCode != 1) isSameSort = false;

		if(isSameSort){
			gx = positions[i].axisX - positions[lastWritten].axisX;
			gy = positions[i].axisY - positions[lastWritten].axisY;
			gz = positions[i].axisZ - positions[lastWritten].axisZ;

			dg = gx * gx + gy * gy + gz * gz;
			if(dg > 0.0){

				for(j = lastWritten + 1; j < i; j++){
					px = positions[j].axisX - positions[lastWritten].axisX;
					py = positions[j].axisY - positions[lastWritten].axisY;
					pz = positions[j].axisZ - positions[lastWritten].axisZ;

					s = (gx * px + gy * py + gz * pz) / dg;

					if(s < 0.0 || s > 1.0){
						isOnLine = false;
						break;
					}

					hx = gx * s;
					hy = gy * s;
					hz = gz * s;
					hx -= px;
					hy -= py;
					hz -= pz;
					d2 = hx * hx + hy * hy + hz * hz;

					if(d2 > t2){
						isOnLine = false;
						break;
					}
				}
			}else{
				isOnLine = false;
			}
		}

		if(!isOnLine || !isSameSort){
			if(lastWritten < i - 1){
				temp.Add(positions[i - 1]);
				lastWritten = i - 1;
				lastGCode = positions[lastWritten].GetGNumber();
			}
		}
		if(!isSameSort){
			if(lastWritten < i){
				temp.Add(positions[i]);
				lastWritten = i;
				lastGCode = positions[lastWritten].GetGNumber();
			}
		}
	}
	if(lastWritten < i - 1) temp.Add(positions[i - 1]);
	positions = temp;
}

void ToolPath::WriteToFile(wxTextFile &f)
{
	if(positions.GetCount() < 2) return;

	CleanPath(0.0003);

	setlocale(LC_ALL, "C"); // To get a 3.1415 instead 3,1415 or else on every computer.

	bool useWithFanucM = false;
	wxTextFileType fileType = wxTextFileType_Dos;

	if(useWithFanucM){
		// For the fanucm.exe g-code simulator.
		f.AddLine(_T("[billet x100 y100 z20"), fileType);
		f.AddLine(_T("[tooldef t1 d6 z35"), fileType);
	}else{
		f.AddLine(_T("G90 G80 G40 G54 G21 G17 G50 G94 G64 (safety block)"),
				fileType);
	}
	f.AddLine(_T("G49 (disable tool length compensation)"), fileType);
	f.AddLine(_T("G80 (disable modal motion)"), fileType);
	f.AddLine(_T("G61 (exact path mode)"), fileType);

	f.AddLine(_T("F3000 (Feedrate mm/min)"), fileType);
	f.AddLine(_T("T1 M6 (Tool 1, Select tool)"), fileType);

	if(useWithFanucM){
		f.AddLine(_T("S1000 (Spindle speed rpm)"), fileType);
		f.AddLine(_T("M3 (Start spindel)"), fileType);
		f.AddLine(_T("G4 X3 (Wait For Seconds, Parameter 3 Seconds)"), fileType);
	}else{
		f.AddLine(_T("S10000 (Spindle speed rpm)"), fileType);
		f.AddLine(_T("M3 (Start spindel)"), fileType);
		f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"), fileType);

	}

	size_t i;


	// First two position are the "anti-messup".
	for(i = 2; i < positions.GetCount(); i++){
		positions[i].axisX -= 0.054;
		positions[i].axisY -= 0.008;
		positions[i].axisZ -= 0.0;
	}

	f.AddLine(positions[0].GenerateCommandXYZ(), fileType);
	for(i = 1; i < positions.GetCount(); i++)
		f.AddLine(positions[i].GenerateCommandDiff(positions[i - 1]), fileType);

	for(i = 2; i < positions.GetCount(); i++){
		positions[i].axisX += 0.054;
		positions[i].axisY += 0.008;
		positions[i].axisZ += 0.000;
	}

	f.AddLine(_T("M5 (Stop spindel)"), fileType);
	if(useWithFanucM){
		f.AddLine(_T("G4 X3 (Wait For Seconds, Parameter 3 Seconds)"), fileType);
	}else{
		f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"), fileType);
	}
	f.AddLine(_T("M2 (End programm)"), fileType);

	setlocale(LC_ALL, "");
}