///////////////////////////////////////////////////////////////////////////////
// Name               : StockMaterial.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "StockMaterial.h"

#include <GL/gl.h>
#include <math.h>
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfStockMaterial)

StockMaterial::StockMaterial()
{
	name = _T("Default");

	sx = 0.1;
	sy = 0.1;
	sz = 0.1;

	maxToolSpeed = 10000.0 / 60.0;
	maxFeedrate = 5.0 / 60.0;
	thermalConductivity = 100;
	ignitionTemperature = 280 + 273.15;

	color.Set(1.0, 0.8, 0.1);
	available = false;
}

StockMaterial::~StockMaterial()
{
}

void StockMaterial::Paint(float alpha, bool flipNormals) const
{
	::glBegin(GL_QUADS);

	::glColor4f(color.x, color.y, color.z, alpha);

	if(flipNormals){
		::glNormal3f(-1, 0, 0);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(sx, sy, 0);
		::glVertex3f(sx, 0, 0);
		::glVertex3f(sx, 0, sz);
	}else{
		::glNormal3f(1, 0, 0);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(sx, 0, sz);
		::glVertex3f(sx, 0, 0);
		::glVertex3f(sx, sy, 0);
	}
	if(flipNormals){
		::glNormal3f(1, 0, 0);
		::glVertex3f(0, sy, sz);
		::glVertex3f(0, 0, sz);
		::glVertex3f(0, 0, 0);
		::glVertex3f(0, sy, 0);
	}else{
		::glNormal3f(-1, 0, 0);
		::glVertex3f(0, sy, sz);
		::glVertex3f(0, sy, 0);
		::glVertex3f(0, 0, 0);
		::glVertex3f(0, 0, sz);
	}
	if(flipNormals){
		::glNormal3f(0, -1, 0);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(0, sy, sz);
		::glVertex3f(0, sy, 0);
		::glVertex3f(sx, sy, 0);
	}else{
		::glNormal3f(0, 1, 0);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(sx, sy, 0);
		::glVertex3f(0, sy, 0);
		::glVertex3f(0, sy, sz);
	}
	if(flipNormals){
		::glNormal3f(0, 1, 0);
		::glVertex3f(sx, 0, sz);
		::glVertex3f(sx, 0, 0);
		::glVertex3f(0, 0, 0);
		::glVertex3f(0, 0, sz);
	}else{
		::glNormal3f(0, -1, 0);
		::glVertex3f(sx, 0, sz);
		::glVertex3f(0, 0, sz);
		::glVertex3f(0, 0, 0);
		::glVertex3f(sx, 0, 0);
	}
	if(flipNormals){
		::glNormal3f(0, 0, -1);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(sx, 0, sz);
		::glVertex3f(0, 0, sz);
		::glVertex3f(0, sy, sz);
	}else{
		::glNormal3f(0, 0, 1);
		::glVertex3f(sx, sy, sz);
		::glVertex3f(0, sy, sz);
		::glVertex3f(0, 0, sz);
		::glVertex3f(sx, 0, sz);
	}
	if(flipNormals){
		::glNormal3f(0, 0, 1);
		::glVertex3f(sx, sy, 0);
		::glVertex3f(0, sy, 0);
		::glVertex3f(0, 0, 0);
		::glVertex3f(sx, 0, 0);
	}else{
		::glNormal3f(0, 0, -1);
		::glVertex3f(sx, sy, 0);
		::glVertex3f(sx, 0, 0);
		::glVertex3f(0, 0, 0);
		::glVertex3f(0, sy, 0);
	}
	::glEnd();
}

void StockMaterial::PaintWireBox(void) const
{
	GLfloat d = M_SQRT1_2;

	::glBegin(GL_LINES);
	::glColor3f(color.x, color.y, color.z);
	::glNormal3f(-d, -d, 0);
	::glVertex3f(0, 0, 0);
	::glVertex3f(0, 0, sz);
	::glNormal3f(d, -d, 0);
	::glVertex3f(sx, 0, 0);
	::glVertex3f(sx, 0, sz);
	::glNormal3f(d, d, 0);
	::glVertex3f(sx, sy, 0);
	::glVertex3f(sx, sy, sz);
	::glNormal3f(-d, d, 0);
	::glVertex3f(0, sy, 0);
	::glVertex3f(0, sy, sz);

	::glNormal3f(-d, 0, -d);
	::glVertex3f(0, 0, 0);
	::glVertex3f(0, sy, 0);
	::glNormal3f(-d, 0, d);
	::glVertex3f(0, 0, sz);
	::glVertex3f(0, sy, sz);
	::glNormal3f(d, 0, d);
	::glVertex3f(sx, 0, sz);
	::glVertex3f(sx, sy, sz);
	::glNormal3f(d, 0, -d);
	::glVertex3f(sx, 0, 0);
	::glVertex3f(sx, sy, 0);

	::glNormal3f(0, -d, -d);
	::glVertex3f(0, 0, 0);
	::glVertex3f(sx, 0, 0);
	::glNormal3f(0, d, -d);
	::glVertex3f(0, sy, 0);
	::glVertex3f(sx, sy, 0);
	::glNormal3f(0, d, d);
	::glVertex3f(0, sy, sz);
	::glVertex3f(sx, sy, sz);
	::glNormal3f(0, -d, d);
	::glVertex3f(0, 0, sz);
	::glVertex3f(sx, 0, sz);

	::glEnd();
}

void StockMaterial::ToStream(wxTextOutputStream& stream)
{
	Vector3 color;
	stream << _T("Name:") << endl;
	stream << name << endl;
	stream << _T("Size: ");
	stream << sx << _T(" ");
	stream << sy << _T(" ");
	stream << sz << endl;
	stream << _T("Parameter: ");
	stream << maxToolSpeed << _T(" ");
	stream << maxFeedrate << _T(" ");
	stream << thermalConductivity << _T(" ");
	stream << ignitionTemperature << endl;
	stream << _T("Color: ");
	stream << color.x << _T(" ");
	stream << color.y << _T(" ");
	stream << color.z << _T(" ");
	stream << endl;
}

bool StockMaterial::FromStream(wxTextInputStream& stream)
{
	wxString temp;
	temp = stream.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0) return false;
	name = stream.ReadLine();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Size:")) != 0) return false;
	stream >> sx;
	stream >> sy;
	stream >> sz;
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Parameter:")) != 0) return false;
	stream >> maxToolSpeed;
	stream >> maxFeedrate;
	stream >> thermalConductivity;
	stream >> ignitionTemperature;
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Color:")) != 0) return false;
	stream >> color.x;
	stream >> color.y;
	stream >> color.z;
	return true;
}
