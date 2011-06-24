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

WorkpieceElement::WorkpieceElement()
{
}
WorkpieceElement::~WorkpieceElement()
{
}

Workpiece::Workpiece(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	field = NULL;
	this->SetupBox(sizeX, sizeY, sizeZ, resolutionX, resolutionY);
}

Workpiece::Workpiece(StockMaterial* material, const double resolution)
{
	field = NULL;
	this->SetupBox(material->x, material->y, material->y, resolution,
			resolution);
	this->matrix = material->matrix;
}

Workpiece::~Workpiece()
{
	if(field != NULL) delete[] field;
}

void Workpiece::SetupBox(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	if(field != NULL) delete[] field;
	field = NULL;

	if(sizeX <= 0.0) return;
	if(sizeY <= 0.0) return;
	if(sizeZ <= 0.0) return;

	sx = sizeX;
	sy = sizeY;
	sz = sizeZ;

	if(resolutionX <= 0.0) return;
	if(resolutionY <= 0.0) return;

	rx = resolutionX;
	ry = resolutionY;

	nx = round(sx / rx);
	ny = round(sy / ry);

	if(nx <= 3) return;
	if(nx <= 3) return;

	N = nx * ny;

	field = new WorkpieceElement[N];
	for(size_t i = 0; i < N; i++){
		field[i].upperLimit = sz;
		field[i].lowerLimit = 0.0;
	}

	colorNormal.Set(0.8, 0.4, 0.0);
	colorTodo.Set(0, 0, 0.8);
	colorUnscratched.Set(0.0, 0.8, 0.1);
}


void Workpiece::InsertTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{

}


void Workpiece::Paint() const
{
	if(field == NULL) return;

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);

	::glBegin(GL_QUADS);

	float dx = sx / nx;
	float dy = sy / ny;
	float dx2 = dx / 2;
	float dy2 = dy / 2;

	size_t i, j, p = 0;

	float px = 0.0, py = 0;
	for(j = 0; j < ny; j++){
		px = 0.0;
		for(i = 0; i < nx; i++){

			if(field[p].IsVisible()){
				glNormal3f(0, 0, 1);
				glVertex3f(px - dx2, py - dy2, field[p].upperLimit);
				glVertex3f(px + dx2, py - dy2, field[p].upperLimit);
				glVertex3f(px + dx2, py + dy2, field[p].upperLimit);
				glVertex3f(px - dx2, py + dy2, field[p].upperLimit);

				glNormal3f(0, 0, -1);
				glVertex3f(px - dx2, py - dy2, field[p].lowerLimit);
				glVertex3f(px + dx2, py - dy2, field[p].lowerLimit);
				glVertex3f(px + dx2, py + dy2, field[p].lowerLimit);
				glVertex3f(px - dx2, py + dy2, field[p].lowerLimit);
			}

			px += dx;
			p++;
		}
		py += dy;
	}

	::glEnd();
	::glPopMatrix();
}

