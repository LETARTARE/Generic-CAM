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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "StockMaterial.h"
#include <GL/gl.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfStockMaterial)

StockMaterial::StockMaterial()
{
	materialName = _T("Default");
	x = 0.700;
	y = 0.450;
	z = 0.020;
	maxSpeed = 10000;
	maxFeedrate = 0.05;
	thermalConductivity = 100;
	ignitionTemperature = 280 + 273.15;
	color.Set(1.0, 0.8, 0.1);
}

StockMaterial::~StockMaterial()
{
}

void StockMaterial::Paint(void)
{

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_QUADS);

	::glColor3f(color.x, color.y, color.z);

	::glNormal3f(1, 0, 0);
	::glVertex3f(x, y, z);
	::glVertex3f(x, 0, z);
	::glVertex3f(x, 0, 0);
	::glVertex3f(x, y, 0);

	::glNormal3f(-1, 0, 0);
	::glVertex3f(0, y, z);
	::glVertex3f(0, y, 0);
	::glVertex3f(0, 0, 0);
	::glVertex3f(0, 0, z);

	::glNormal3f(0, 1, 0);
	::glVertex3f(x, y, z);
	::glVertex3f(x, y, 0);
	::glVertex3f(0, y, 0);
	::glVertex3f(0, y, z);

	::glNormal3f(0, -1, 0);
	::glVertex3f(x, 0, z);
	::glVertex3f(0, 0, z);
	::glVertex3f(0, 0, 0);
	::glVertex3f(x, 0, 0);

	::glNormal3f(0, 0, 1);
	::glVertex3f(x, y, z);
	::glVertex3f(0, y, z);
	::glVertex3f(0, 0, z);
	::glVertex3f(x, 0, z);

	::glNormal3f(0, 0, -1);
	::glVertex3f(x, y, 0);
	::glVertex3f(x, 0, 0);
	::glVertex3f(0, 0, 0);
	::glVertex3f(0, y, 0);

	::glEnd();

	::glPopMatrix();

}
