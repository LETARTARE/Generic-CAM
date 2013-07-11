///////////////////////////////////////////////////////////////////////////////
// Name               : Octree.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.08.2011
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

#include "Octree.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfOctree)

#include <math.h>

Octree::Octree()
{
	tree = new OctreeInt64();

	scale = 1 / 30.0;

	// Test triangle:
	Triangle tri;
	tri.p[0].Set(0.15, 0.1, 0.1);
	tri.p[1].Set(0.5, 0.1, 0.1);
	tri.p[2].Set(0.15, 0.5, 0.1);

	InsertTriangle(tri);
}

Octree::~Octree()
{
	if(tree != NULL) delete tree;
}

void Octree::InsertTriangle(Triangle tri)
{

	TriangleInt64 temp;
	unsigned char i;
	for(i = 0; i < 3; i++){
		temp.p[i].x = llround(tri.p[i].x / scale);
		temp.p[i].y = llround(tri.p[i].y / scale);
		temp.p[i].z = llround(tri.p[i].z / scale);
	}

	tree->InsertTriangle(temp);
}

void Octree::Paint()
{
	if(tree == NULL) return;
	::glBegin(GL_TRIANGLES);
	Triangle tri;
	tri.p[0].Set(0.15, 0.1, 0.1);
	tri.p[1].Set(0.5, 0.1, 0.1);
	tri.p[2].Set(0.15, 0.5, 0.1);
	tri.CalculateNormal();
	::glColor3b(120, 50, 50);
	tri.Paint(true, false);
	::glEnd();

	::glPushMatrix();
	::glScalef(1048576.0 * scale, 1048576.0 * scale, 1048576.0 * scale);
	tree->Paint();
	::glPopMatrix();
}
