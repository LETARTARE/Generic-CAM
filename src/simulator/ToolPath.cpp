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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "ToolPath.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfToolPath)

#include <wx/log.h>
#include <GL/gl.h>

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

void ToolPath::WriteToFile(wxTextFile &f)
{
	setlocale(LC_ALL,"C");

	f.AddLine(_T("G90 G80 G40 G54 G21 G17 G50 G94 G64 (safety block)"));

	f.AddLine(_T("G49 (disable tool length compensation)"));
	f.AddLine(_T("G80 (disable modal motion)"));
	f.AddLine(_T("G61 (exact path mode)"));

	f.AddLine(_T("F3000 (Feedrate mm/min)"));

	f.AddLine(_T("T1 M6 (Tool 1, Select tool)"));

	f.AddLine(_T("S10000 (Spindle speed rpm)"));
	f.AddLine(_T("M3 (Start spindel)"));
	f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"));

	size_t i;

	f.AddLine(positions[0].GenerateCommandXYZ());

	for(i = 1; i < positions.GetCount(); i++)
		f.AddLine(positions[i].GenerateCommandDiff(positions[i - 1]));

	f.AddLine(_T("M5 (Stop spindel)"));
	f.AddLine(_T("G4 P3 (Wait For Seconds, Parameter 3 Seconds)"));
	f.AddLine(_T("M2 (End programm)"));


	setlocale(LC_ALL,"");
}
