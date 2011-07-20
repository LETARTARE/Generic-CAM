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

Workpiece::Workpiece(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY) :
	Imprinter(sizeX, sizeY, sizeZ, resolutionX, resolutionY)
{
}

Workpiece::Workpiece(StockMaterial* material, const double resolution)
{
	this->SetupBox(material->x, material->y, material->y, resolution,
			resolution);
}

Workpiece::~Workpiece()
{

}

void Workpiece::SetupBox(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{

	Imprinter::SetupBox(sizeX, sizeY, sizeZ, resolutionX, resolutionY);

	colorNormal.Set(0.8, 0.4, 0.0);
	colorTodo.Set(0, 0, 0.8);
	colorUnscratched.Set(0.0, 0.8, 0.1);
}

void Workpiece::InsertTriangle(Vector3 a, Vector3 b, Vector3 c)
{
	Imprinter::InsertTriangle(a, b, c);
}

void Workpiece::Paint()
{
	Imprinter::Paint();
}

