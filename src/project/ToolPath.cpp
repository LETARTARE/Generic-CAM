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
#include "../Config.h"

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
bool ToolPath::IsEmpty(void) const
{
	return (positions.GetCount() == 0);
}

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

void ToolPath::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	for(size_t i = 0; i < positions.GetCount(); i++){
		Vector3 temp(positions[i].X, positions[i].Y, positions[i].Z);
		temp = matrix.Transform(temp);
		positions[i].X = temp.x;
		positions[i].Y = temp.y;
		positions[i].Z = temp.z;
	}
}

void ToolPath::Translate(Dialect target)
{
	switch(target){
	case FanucM:
		for(size_t i = 0; i < positions.GetCount(); i++){
			// FanucM does not like spindle speeds above 1000 RPM.
			if(positions[i].S > 1000.0 / 60.0) positions[i].S = 1000.0 / 60.0;

			// FanucM uses X instead P for the dwell-time in G4
			if(positions[i].G[0] == 40){
				if(positions[i].P > -FLT_EPSILON){
					positions[i].X = positions[i].P
							* positions[i].conversionFactor;
					positions[i].XFlag = true;
					positions[i].P = -1.0;
				}else{
					positions[i].XFlag = false;
				}
			}

			// Remove A,B,C and U,V,W for FanucM
			positions[i].AFlag = false;
			positions[i].BFlag = false;
			positions[i].CFlag = false;
			positions[i].UFlag = false;
			positions[i].VFlag = false;
			positions[i].WFlag = false;

		}
		break;

	case RS274NGC:
		// Nothing to do.
		break;
	}
}

void ToolPath::CalculateMinMaxValues(void)
{
	minPosition.X = +FLT_MAX;
	minPosition.Y = +FLT_MAX;
	minPosition.Z = +FLT_MAX;
	minPosition.A = +FLT_MAX;
	minPosition.B = +FLT_MAX;
	minPosition.C = +FLT_MAX;
	minPosition.U = +FLT_MAX;
	minPosition.V = +FLT_MAX;
	minPosition.W = +FLT_MAX;

	maxPosition.X = -FLT_MAX;
	maxPosition.Y = -FLT_MAX;
	maxPosition.Z = -FLT_MAX;
	maxPosition.A = -FLT_MAX;
	maxPosition.B = -FLT_MAX;
	maxPosition.C = -FLT_MAX;
	maxPosition.U = -FLT_MAX;
	maxPosition.V = -FLT_MAX;
	maxPosition.W = -FLT_MAX;

	for(size_t i = 0; i < positions.GetCount(); i++){
		if(positions[i].XFlag){
			if(positions[i].X > maxPosition.X) maxPosition.X = positions[i].X;
			if(positions[i].X < minPosition.X) minPosition.X = positions[i].X;
		}
		if(positions[i].YFlag){
			if(positions[i].Y > maxPosition.Y) maxPosition.Y = positions[i].Y;
			if(positions[i].Y < minPosition.Y) minPosition.Y = positions[i].Y;
		}
		if(positions[i].ZFlag){
			if(positions[i].Z > maxPosition.Z) maxPosition.Z = positions[i].Z;
			if(positions[i].Z < minPosition.Z) minPosition.Z = positions[i].Z;
		}
		if(positions[i].AFlag){
			if(positions[i].A > maxPosition.A) maxPosition.A = positions[i].A;
			if(positions[i].A < minPosition.A) minPosition.A = positions[i].A;
		}
		if(positions[i].BFlag){
			if(positions[i].B > maxPosition.B) maxPosition.B = positions[i].B;
			if(positions[i].B < minPosition.B) minPosition.B = positions[i].B;
		}
		if(positions[i].CFlag){
			if(positions[i].C > maxPosition.C) maxPosition.C = positions[i].C;
			if(positions[i].C < minPosition.C) minPosition.C = positions[i].C;
		}
		if(positions[i].UFlag){
			if(positions[i].U > maxPosition.U) maxPosition.U = positions[i].U;
			if(positions[i].U < minPosition.U) minPosition.U = positions[i].U;
		}
		if(positions[i].VFlag){
			if(positions[i].V > maxPosition.V) maxPosition.V = positions[i].V;
			if(positions[i].V < minPosition.V) minPosition.V = positions[i].V;
		}
		if(positions[i].WFlag){
			if(positions[i].W > maxPosition.W) maxPosition.W = positions[i].W;
			if(positions[i].W < minPosition.W) minPosition.W = positions[i].W;
		}
	}
}

void ToolPath::Paint(void) const
{
	::glBegin(GL_LINE_STRIP);
	::glNormal3f(0, 0, 1);
	for(size_t i = 0; i < positions.GetCount(); i++){
		if(positions[i].IsCutting())
			::glColor3f(colorCutting.x, colorCutting.y, colorCutting.z);
		else
			::glColor3f(colorMoving.x, colorMoving.y, colorMoving.z);
		::glVertex3f(positions[i].X, positions[i].Y, positions[i].Z);
	}
	::glEnd();
}

ToolPath ToolPath::SafetyBlock(void)
{
	ToolPath tp;
	tp.positions.Add(GCodeBlock(_T("G90 (set absolute distance mode)")));
	tp.positions.Add(GCodeBlock(_T("G80 (cancel modal motion)")));
	tp.positions.Add(
			GCodeBlock(_T("G40 (cutter radius compensation in XY plane)")));
	tp.positions.Add(GCodeBlock(_T("G54 (coordinate system 1 active)")));
	tp.positions.Add(GCodeBlock(_T("G21 (length units: mm)")));
	tp.positions.Add(GCodeBlock(_T("G17 (work in XY plane)")));
	tp.positions.Add(GCodeBlock(_T("G50 (cancel scaling function)")));
	tp.positions.Add(GCodeBlock(_T("G94 (per minute feed)")));
	tp.positions.Add(GCodeBlock(_T("G64 (continuous path control mode)")));
	tp.positions.Add(GCodeBlock(_T("G49 (disable tool length compensation)")));
	tp.positions.Add(GCodeBlock(_T("G80 (disable modal motion)")));
	tp.positions.Add(GCodeBlock(_T("G61 (exact path mode)")));
	return tp;
}

ToolPath ToolPath::EndBlock(void)
{
	ToolPath tp;
	tp.positions.Add(GCodeBlock(_T("M5 (stop spindel)")));
	tp.positions.Add(
			GCodeBlock(
					_T("G4 P3 (wait for 3 seconds for the spindle to stop)")));
	tp.positions.Add(GCodeBlock(_T("M2 (end of programm)")));
	return tp;
}

void ToolPath::CleanPath(const double tolerance)
{
	ArrayOfGCodeBlock temp;
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
	unsigned char lastGCode = positions[lastWritten].Motion();
//	unsigned char gCode;
	size_t i;
	for(i = 1; i < positions.GetCount(); i++){
		bool isOnLine = true;
		bool isSameSort = true;
		unsigned char gCode = positions[i].Motion();
		if(gCode != lastGCode) isSameSort = false;
		if(lastGCode != 0 && lastGCode != 1) isSameSort = false;

		if(isSameSort){
			const double gx = positions[i].X - positions[lastWritten].X;
			const double gy = positions[i].Y - positions[lastWritten].Y;
			const double gz = positions[i].Z - positions[lastWritten].Z;
			const double dg = gx * gx + gy * gy + gz * gz;

			if(dg > 0.0){

				for(size_t j = lastWritten + 1; j < i; j++){
					const double px = positions[j].X - positions[lastWritten].X;
					const double py = positions[j].Y - positions[lastWritten].Y;
					const double pz = positions[j].Z - positions[lastWritten].Z;
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
				lastGCode = positions[lastWritten].Motion();
			}
		}
		if(!isSameSort){
			if(lastWritten < i){
				temp.Add(positions[i]);
				lastWritten = i;
				lastGCode = positions[lastWritten].Motion();
			}
		}
	}
	if(lastWritten < i - 1) temp.Add(positions[i - 1]);
	positions = temp;
}

void ToolPath::DiffPath(const double tolerance)
{
	if(positions.GetCount() < 1) return;
	positions[0].XFlag = true;
	positions[0].YFlag = true;
	positions[0].ZFlag = true;
	positions[0].AFlag = true;
	positions[0].BFlag = true;
	positions[0].CFlag = true;
	positions[0].UFlag = true;
	positions[0].VFlag = true;
	positions[0].WFlag = true;
	positions[0].IFlag = true;
	positions[0].JFlag = true;
	positions[0].KFlag = true;
	positions[0].RFlag = true;
	GCodeBlock oldPos = positions[0];

	for(size_t i = 1; i < positions.GetCount(); i++){
		GCodeBlock newPos = positions[i];
		positions[i].XFlag = (fabs(oldPos.X - positions[i].X) > tolerance);
		positions[i].YFlag = (fabs(oldPos.Y - positions[i].Y) > tolerance);
		positions[i].ZFlag = (fabs(oldPos.Z - positions[i].Z) > tolerance);
		positions[i].AFlag = (fabs(oldPos.A - positions[i].A) > tolerance);
		positions[i].BFlag = (fabs(oldPos.B - positions[i].B) > tolerance);
		positions[i].CFlag = (fabs(oldPos.C - positions[i].C) > tolerance);
		positions[i].UFlag = (fabs(oldPos.U - positions[i].U) > tolerance);
		positions[i].VFlag = (fabs(oldPos.V - positions[i].V) > tolerance);
		positions[i].WFlag = (fabs(oldPos.W - positions[i].W) > tolerance);
		positions[i].RFlag = (fabs(oldPos.R - positions[i].R) > tolerance);

		if(oldPos.G[1] == positions[i].G[1]) positions[i].G[1] = -1;

		oldPos = newPos;
	}
}

bool ToolPath::WriteToFile(wxTextFile &f)
{
	for(size_t i = 0; i < positions.GetCount(); i++)
		f.AddLine(positions[i].GetCode(), wxTextFileType_Dos);
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
		_T("ReadGCodeFile: Can't open ") + fileName.GetFullPath() + _T(" !");
		return false;
	}

	if(file.Eof()){
		info = _T("ReadGCodeFile: File is empty!");
		return false;
	}

	wxString temp;
	temp = file.GetFirstLine();
	if(temp.IsEmpty()){
		info = _T("ReadGCodeFile: File is empty!");
		return false;
	}

	positions.Clear();
	GCodeBlock pos;
	pos = GCodeBlock(temp);
	if(!temp.IsEmpty() && pos.error.IsEmpty()) positions.Add(pos);
	while(!file.Eof()){
		temp = file.GetNextLine();
		pos = GCodeBlock(temp);
		if(!temp.IsEmpty() && pos.error.IsEmpty()) positions.Add(pos);
	}
	file.Close();
	info.Empty();
	return true;
}
