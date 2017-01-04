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
///////////////////////////////////////////////////////////////////////////////

#include "ToolPath.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <float.h>

ToolPath::ToolPath()
{
	selected = false;
	colorMoving.Set(0.3, 0.8, 0.3);
	colorCutting.Set(0.8, 0.3, 0.3);
}

ToolPath::ToolPath(const ToolPath& other)
{
	// Performance issues if called.
	printf("Copy constructor on ToolPath called.\n");
	selected = false;
	colorMoving = other.colorMoving;
	colorCutting = other.colorCutting;
	info = other.info;
	positions = other.positions;
	minPosition = other.minPosition;
	maxPosition = other.maxPosition;
}

ToolPath::~ToolPath()
{
}

void ToolPath::Clear(void)
{
	positions.Empty();
}

//! Overloaded operator for polygon concatenation.
ToolPath & ToolPath::operator+=(const ToolPath &a)
{
	for(size_t i = 0; i < a.positions.GetCount(); i++)
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

void ToolPath::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	Vector3 temp;
	for(i = 0; i < positions.size(); i++){
		temp.Set(positions[i].axisX, positions[i].axisY, positions[i].axisZ);
		temp = matrix.Transform(temp);
		positions[i].axisX = temp.x;
		positions[i].axisY = temp.y;
		positions[i].axisZ = temp.z;
	}
}

void ToolPath::Paint(void) const
{
	::glBegin(GL_LINE_STRIP);
	::glNormal3f(0, 0, 1);
	for(size_t i = 0; i < positions.size(); i++){

		if(positions[i].isCutting)
			::glColor3f(colorCutting.x, colorCutting.y, colorCutting.z);
		else
			::glColor3f(colorMoving.x, colorMoving.y, colorMoving.z);

		::glVertex3f(positions[i].axisX, positions[i].axisY,
				positions[i].axisZ);
	}

	::glEnd();
}

void ToolPath::CalculateMinMaxValues(void)
{
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

	for(size_t i = 0; i < positions.GetCount(); i++){
		if(positions[i].axisX > maxPosition.axisX) maxPosition.axisX =
				positions[i].axisX;
		if(positions[i].axisY > maxPosition.axisY) maxPosition.axisY =
				positions[i].axisY;
		if(positions[i].axisZ > maxPosition.axisZ) maxPosition.axisZ =
				positions[i].axisZ;
		if(positions[i].axisU > maxPosition.axisU) maxPosition.axisU =
				positions[i].axisU;
		if(positions[i].axisV > maxPosition.axisV) maxPosition.axisV =
				positions[i].axisV;
		if(positions[i].axisW > maxPosition.axisW) maxPosition.axisW =
				positions[i].axisW;
		if(positions[i].axisA > maxPosition.axisA) maxPosition.axisA =
				positions[i].axisA;
		if(positions[i].axisB > maxPosition.axisB) maxPosition.axisB =
				positions[i].axisB;
		if(positions[i].axisC > maxPosition.axisC) maxPosition.axisC =
				positions[i].axisC;

		if(positions[i].axisX < minPosition.axisX) minPosition.axisX =
				positions[i].axisX;
		if(positions[i].axisY < minPosition.axisY) minPosition.axisY =
				positions[i].axisY;
		if(positions[i].axisZ < minPosition.axisZ) minPosition.axisZ =
				positions[i].axisZ;
		if(positions[i].axisU < minPosition.axisU) minPosition.axisU =
				positions[i].axisU;
		if(positions[i].axisV < minPosition.axisV) minPosition.axisV =
				positions[i].axisV;
		if(positions[i].axisW < minPosition.axisW) minPosition.axisW =
				positions[i].axisW;
		if(positions[i].axisA < minPosition.axisA) minPosition.axisA =
				positions[i].axisA;
		if(positions[i].axisB < minPosition.axisB) minPosition.axisB =
				positions[i].axisB;
		if(positions[i].axisC < minPosition.axisC) minPosition.axisC =
				positions[i].axisC;
	}
}

void ToolPath::CleanPath(double tolerance)
{
	ArrayOfMachinePosition temp;
	if(positions.GetCount() < 2) return;

//	bool isOnLine;
//	bool isSameSort;
//
//	double gx, gy, gz;
//	double px, py, pz;
//	double s, d2;
//	double hx, hy, hz;
//	double dg;
	const double t2 = tolerance * tolerance;
	size_t lastWritten = 0;
	temp.Add(positions[lastWritten]);
	unsigned char lastGCode = positions[lastWritten].GetGNumber();
//	unsigned char gCode;
	size_t i;
	for(i = 1; i < positions.size(); i++){
		bool isOnLine = true;
		bool isSameSort = true;
		unsigned char gCode = positions[i].GetGNumber();
		if(gCode != lastGCode) isSameSort = false;
		if(lastGCode != 0 && lastGCode != 1) isSameSort = false;

		if(isSameSort){
			double gx = positions[i].axisX - positions[lastWritten].axisX;
			double gy = positions[i].axisY - positions[lastWritten].axisY;
			double gz = positions[i].axisZ - positions[lastWritten].axisZ;

			double dg = gx * gx + gy * gy + gz * gz;
			if(dg > 0.0){

				for(size_t j = lastWritten + 1; j < i; j++){
					const double px = positions[j].axisX
							- positions[lastWritten].axisX;
					const double py = positions[j].axisY
							- positions[lastWritten].axisY;
					const double pz = positions[j].axisZ
							- positions[lastWritten].axisZ;

					const double s = (gx * px + gy * py + gz * pz) / dg;

					if(s < 0.0 || s > 1.0){
						isOnLine = false;
						break;
					}

					double hx = gx * s;
					double hy = gy * s;
					double hz = gz * s;
					hx -= px;
					hy -= py;
					hz -= pz;
					const double d2 = hx * hx + hy * hy + hz * hz;

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

bool ToolPath::WriteToFile(wxTextFile &f)
{
	if(positions.size() < 2) return false;

	CleanPath(0.0003);

	setlocale(LC_ALL, "C"); // To get a 3.1415 instead 3,1415 or else on every computer.

	bool useWithFanucM = false;
	wxTextFileType fileType = wxTextFileType_Dos;

	if(useWithFanucM){
		// For the fanucm.exe g-code simulator.
		f.AddLine(_T("[billet x100 y100 z25"), fileType);
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
		f.AddLine(_T("G4 X3 (Wait For Seconds, Parameter 3 Seconds)"),
				fileType);
	}else{
		f.AddLine(_T("S10000 (Spindle speed rpm)"), fileType);
		f.AddLine(_T("M3 (Start spindel)"), fileType);
		f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"),
				fileType);
	}

	f.AddLine(positions[0].GenerateCommandXYZ(), fileType);
	for(size_t i = 1; i < positions.GetCount(); i++)
		f.AddLine(positions[i].GenerateCommandDiff(positions[i - 1]), fileType);

	f.AddLine(_T("M5 (Stop spindel)"), fileType);
	if(useWithFanucM){
		f.AddLine(_T("G4 X3 (Wait For Seconds, Parameter 3 Seconds)"),
				fileType);
	}else{
		f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"),
				fileType);
	}
	f.AddLine(_T("M2 (End programm)"), fileType);

	setlocale(LC_ALL, "");
	return true;
}

bool ToolPath::ReadGCodeFile(wxFileName fileName)
{
	if(!fileName.IsOk()){
		info =
				_T(
						"ReadGCodeFile: Incorrect fileName ") + fileName.GetFullPath() + _T(" !");
		return false;
	}

	wxTextFile file;

	if(!file.Open(fileName.GetFullPath())){
		info =
		_T("ReadGCodeFile: Can't open ") + fileName.GetFullPath()
		+ _T(" !");
		return false;
	}

	wxString temp;
	if(file.Eof()){
		info = _T("ReadGCodeFile: File is empty!");
		return false;
	}
	temp = file.GetFirstLine();
	if(temp.IsEmpty()){
		info = _T("ReadGCodeFile: File is empty!");
		return false;
	}

	MachinePosition* pos = new MachinePosition;
	positions.Clear();

	if(pos->ParseGCodeLine(temp)){
		positions.Add(pos);
		pos = new MachinePosition;
		*pos = positions[positions.Count() - 1];
	}
	while(!file.Eof()){
		temp = file.GetNextLine();
		if(pos->ParseGCodeLine(temp)){
			positions.Add(pos);
			pos = new MachinePosition;
			*pos = positions[positions.Count() - 1];
		}
	}
	positions.Add(pos);
	file.Close();
	info.Empty();
	return true;
}
