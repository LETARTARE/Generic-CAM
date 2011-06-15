///////////////////////////////////////////////////////////////////////////////
// Name               : Workpiece.cpp
// Purpose            : The workpiece.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.03.2010
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


#include "Workpiece.h"

#include <GL/gl.h>

Workpiece::Workpiece()
{
	field = NULL;
	sx = sy = sz = 0;
	rx = ry = 0.0;
}

Workpiece::~Workpiece()
{
	if(field != NULL) delete[] field;
}

void Workpiece::Paint() const
{
	if(field == NULL) return;

}

void Workpiece::SetupBox(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	if(field != NULL) delete[] field;

	rx = resolutionX;
	ry = resolutionY;
	sx = sizeX;
	sy = sizeY;
	sz = sizeZ;
	nx = round(sx / rx);
	ny = round(sy / ry);
	N = nx * ny;

	field = new float[N];
	for(size_t i = 0; i < N; i++)
		field[i] = sz;
}
