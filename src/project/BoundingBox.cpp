///////////////////////////////////////////////////////////////////////////////
// Name               : BoundingBox.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.06.2011
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


#include "BoundingBox.h"

#include <GL/gl.h>
#include <float.h>

BoundingBox::BoundingBox()
{
	color.Set(0.3, 0.3, 0.3);
	alpha = 0.5;

	this->Reset();
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::Reset(void)
{
	xmax = ymax = zmax = -DBL_MAX;
	xmin = ymin = zmin = DBL_MAX;
}

void BoundingBox::Insert(Geometry &geometry)
{
	size_t i, j;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		for(j = 0; j < 3; j++){
			if(geometry.triangles[i].p[j].x > xmax) xmax
					= geometry.triangles[i].p[j].x;
			if(geometry.triangles[i].p[j].x < xmin) xmin
					= geometry.triangles[i].p[j].x;
			if(geometry.triangles[i].p[j].y > ymax) ymax
					= geometry.triangles[i].p[j].y;
			if(geometry.triangles[i].p[j].y < ymin) ymin
					= geometry.triangles[i].p[j].y;
			if(geometry.triangles[i].p[j].z > zmax) zmax
					= geometry.triangles[i].p[j].z;
			if(geometry.triangles[i].p[j].z < zmin) zmin
					= geometry.triangles[i].p[j].z;
		}
	}
}

void BoundingBox::Paint(void)
{

	float overlap = 0.1;

	if(xmax < xmin) return;
	if(ymax < ymin) return;
	if(zmax < zmin) return;

	::glBegin(GL_QUADS);

	::glColor4f(color.x, 0, 0, alpha);

	::glNormal3f(1, 0, 0);
	::glVertex3f(xmax, ymax + overlap, zmax + overlap);
	::glVertex3f(xmax, ymin - overlap, zmax + overlap);
	::glVertex3f(xmax, ymin - overlap, zmin - overlap);
	::glVertex3f(xmax, ymax + overlap, zmin - overlap);

	::glNormal3f(-1, 0, 0);
	::glVertex3f(xmin, ymax + overlap, zmax + overlap);
	::glVertex3f(xmin, ymax + overlap, zmin - overlap);
	::glVertex3f(xmin, ymin - overlap, zmin - overlap);
	::glVertex3f(xmin, ymin - overlap, zmax + overlap);

	::glColor4f(0, color.y, 0, alpha);
	::glNormal3f(0, 1, 0);
	::glVertex3f(xmax + overlap, ymax, zmax + overlap);
	::glVertex3f(xmax + overlap, ymax, zmin - overlap);
	::glVertex3f(xmin - overlap, ymax, zmin - overlap);
	::glVertex3f(xmin - overlap, ymax, zmax + overlap);

	::glNormal3f(0, -1, 0);
	::glVertex3f(xmax + overlap, ymin, zmax + overlap);
	::glVertex3f(xmin - overlap, ymin, zmax + overlap);
	::glVertex3f(xmin - overlap, ymin, zmin - overlap);
	::glVertex3f(xmax + overlap, ymin, zmin - overlap);

	::glColor4f(0, 0, color.z, alpha);
	::glNormal3f(0, 0, 1);
	::glVertex3f(xmax + overlap, ymax + overlap, zmax);
	::glVertex3f(xmin - overlap, ymax + overlap, zmax);
	::glVertex3f(xmin - overlap, ymin - overlap, zmax);
	::glVertex3f(xmax + overlap, ymin - overlap, zmax);

	::glNormal3f(0, 0, -1);
	::glVertex3f(xmax + overlap, ymax + overlap, zmin);
	::glVertex3f(xmax + overlap, ymin - overlap, zmin);
	::glVertex3f(xmin - overlap, ymin - overlap, zmin);
	::glVertex3f(xmin - overlap, ymax + overlap, zmin);

	::glEnd();

	::glPopMatrix();

}
