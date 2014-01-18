///////////////////////////////////////////////////////////////////////////////
// Name               : OctreeInt64.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 09.06.2013
// Copyright          : (C) 2013 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "OctreeGenerator.h"

VectorInt64::VectorInt64()
{
	x = y = z = 0;
}

VectorInt64& VectorInt64::operator=(const VectorInt64 &rhs)
{
	// Check for self-assignment!
	if(this == &rhs) // Same object?
	return *this; // Yes, so skip assignment, and just return *this.
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

TriangleInt64::TriangleInt64()
{
}

OctreeGenerator::OctreeGenerator()
{
	root = new Octree();

	root->tree->SetColor(1.0, 1.0, 0.0); // Yellow cubes.
	// Test triangle:
	Triangle tri;
	tri.p[0].Set(0.15, 0.1, 0.1);
	tri.p[1].Set(0.5, 0.1, 0.1);
	tri.p[2].Set(0.15, 0.5, 0.1);

	InsertTriangle(tri);
}

OctreeGenerator::~OctreeGenerator()
{
	if(root != NULL) delete (root);
}

void OctreeGenerator::Paint()
{
	if(root != NULL) root->Paint();
}

void OctreeGenerator::InsertTriangle(Triangle tri)
{

	bb.Reset();
	bb.Insert(tri);

//	TriangleInt64 temp;
//	unsigned char i;
//	for(i = 0; i < 3; i++){
//		temp.p[i].x = llround(tri.p[i].x / scale);
//		temp.p[i].y = llround(tri.p[i].y / scale);
//		temp.p[i].z = llround(tri.p[i].z / scale);
//	}

	root->tree->InsertTriangle(tri, bb);
}

void OctreeGenerator::InsertTriangle(TriangleInt64 &tri)
{

	// Generate a bounding box around the triangle.
	tri.bbmin = tri.p[0];
	tri.bbmax = tri.p[0];

	if(tri.p[1].x < tri.bbmin.x) tri.bbmin.x = tri.p[1].x;
	if(tri.p[1].y < tri.bbmin.y) tri.bbmin.y = tri.p[1].y;
	if(tri.p[1].z < tri.bbmin.z) tri.bbmin.z = tri.p[1].z;
	if(tri.p[2].x < tri.bbmin.x) tri.bbmin.x = tri.p[2].x;
	if(tri.p[2].y < tri.bbmin.y) tri.bbmin.y = tri.p[2].y;
	if(tri.p[2].z < tri.bbmin.z) tri.bbmin.z = tri.p[2].z;

	if(tri.p[1].x > tri.bbmax.x) tri.bbmax.x = tri.p[1].x;
	if(tri.p[1].y > tri.bbmax.y) tri.bbmax.y = tri.p[1].y;
	if(tri.p[1].z > tri.bbmax.z) tri.bbmax.z = tri.p[1].z;
	if(tri.p[2].x > tri.bbmax.x) tri.bbmax.x = tri.p[2].x;
	if(tri.p[2].y > tri.bbmax.y) tri.bbmax.y = tri.p[2].y;
	if(tri.p[2].z > tri.bbmax.z) tri.bbmax.z = tri.p[2].z;

// Calculate the normal vector of the triangle.
	tri.CalculateNormal();

	Vector3 pos(0, 0, 0);

//	if(tree != NULL) tree->CheckTriangle(&tri, pos);
}

