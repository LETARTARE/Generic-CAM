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

#include <stdint.h>
#include <math.h>
#include "OpenGL.h"

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
	tri.p[0].Set(0.15, 0.1, 0.3);
	tri.p[1].Set(0.5, 0.15, 0.2);
	tri.p[2].Set(0.2, 0.5, 0.1);

	InsertTriangle(tri);

	tri.p[0].Set(0.15, 0.1, 0.3);
	tri.p[1].Set(0.5, 0.15, 0.2);
	tri.p[2].Set(0.2, 0.5, 0.4);

	InsertTriangle(tri);

}

OctreeGenerator::~OctreeGenerator()
{
	if(root != NULL) delete (root);
}

void OctreeGenerator::Paint()
{

	::glBegin(GL_TRIANGLES);
	Triangle tri;
	tri.p[0].Set(0.15, 0.1, 0.3);
	tri.p[1].Set(0.5, 0.15, 0.2);
	tri.p[2].Set(0.2, 0.5, 0.1);
	tri.CalculateNormal();
	::glColor3b(120, 50, 50);
	tri.Paint(true, false);

	tri.p[0].Set(0.15, 0.1, 0.3);
	tri.p[1].Set(0.5, 0.15, 0.2);
	tri.p[2].Set(0.2, 0.5, 0.4);
	tri.CalculateNormal();
	::glColor3b(120, 50, 50);
	tri.Paint(true, false);

	::glEnd();

	if(root != NULL) root->Paint();
}

void OctreeGenerator::InsertTriangle(Triangle tri)
{
	if(root == NULL) return;

	BoundingBox bb;
	bb.Clear();
	bb.Insert(tri);
	Vector3 temp(0, 0, 0);

	double cubeSize = pow(2.0, root->depth) * root->cellSize;

	tri.CalculateNormal();

	CheckTriangle(root->tree, tri, temp, cubeSize, bb, root->depth);

//	TriangleInt64 temp;
//	unsigned char i;
//	for(i = 0; i < 3; i++){
//		temp.p[i].x = llround(tri.p[i].x / scale);
//		temp.p[i].y = llround(tri.p[i].y / scale);
//		temp.p[i].z = llround(tri.p[i].z / scale);
//	}

//	root->tree->InsertTriangle(tri, bb);
}

//void OctreeGenerator::InsertTriangle(TriangleInt64 &tri)
//{
//
//	// Generate a bounding box around the triangle.
//	tri.bbmin = tri.p[0];
//	tri.bbmax = tri.p[0];
//
//	if(tri.p[1].x < tri.bbmin.x) tri.bbmin.x = tri.p[1].x;
//	if(tri.p[1].y < tri.bbmin.y) tri.bbmin.y = tri.p[1].y;
//	if(tri.p[1].z < tri.bbmin.z) tri.bbmin.z = tri.p[1].z;
//	if(tri.p[2].x < tri.bbmin.x) tri.bbmin.x = tri.p[2].x;
//	if(tri.p[2].y < tri.bbmin.y) tri.bbmin.y = tri.p[2].y;
//	if(tri.p[2].z < tri.bbmin.z) tri.bbmin.z = tri.p[2].z;
//
//	if(tri.p[1].x > tri.bbmax.x) tri.bbmax.x = tri.p[1].x;
//	if(tri.p[1].y > tri.bbmax.y) tri.bbmax.y = tri.p[1].y;
//	if(tri.p[1].z > tri.bbmax.z) tri.bbmax.z = tri.p[1].z;
//	if(tri.p[2].x > tri.bbmax.x) tri.bbmax.x = tri.p[2].x;
//	if(tri.p[2].y > tri.bbmax.y) tri.bbmax.y = tri.p[2].y;
//	if(tri.p[2].z > tri.bbmax.z) tri.bbmax.z = tri.p[2].z;
//
//// Calculate the normal vector of the triangle.
////	tri.CalculateNormal();
//
////	Vector3 pos(0, 0, 0);
//
////	if(tree != NULL) tree->CheckTriangle(&tri, pos);
//}

void OctreeGenerator::CheckTriangle(OctreeCell * base, const Triangle tri,
		const Vector3 pos, float scale, BoundingBox & bb, unsigned char depth)
{
	// Check for intersection
	if(CheckIntersection(tri, pos, scale, bb)){
		if(depth > 1){
			depth--;
			base->Split();

			scale /= 2.0;
			Vector3 temp = pos;

			temp.x = pos.x - scale / 2;
			temp.y = pos.y - scale / 2;
			temp.z = pos.z - scale / 2;
			CheckTriangle(base->sub[0], tri, temp, scale, bb, depth);
			temp.x = pos.x + scale / 2;
			CheckTriangle(base->sub[1], tri, temp, scale, bb, depth);
			temp.x = pos.x - scale / 2;
			temp.y = pos.y + scale / 2;
			CheckTriangle(base->sub[2], tri, temp, scale, bb, depth);
			temp.x = pos.x + scale / 2;
			CheckTriangle(base->sub[3], tri, temp, scale, bb, depth);
			temp.x = pos.x - scale / 2;
			temp.y = pos.y - scale / 2;
			temp.z = pos.z + scale / 2;
			CheckTriangle(base->sub[4], tri, temp, scale, bb, depth);
			temp.x = pos.x + scale / 2;
			CheckTriangle(base->sub[5], tri, temp, scale, bb, depth);
			temp.x = pos.x - scale / 2;
			temp.y = pos.y + scale / 2;
			CheckTriangle(base->sub[6], tri, temp, scale, bb, depth);
			temp.x = pos.x + scale / 2;
			CheckTriangle(base->sub[7], tri, temp, scale, bb, depth);
		}else{
			base->isSolid = true;
		}
	}
}

bool OctreeGenerator::CheckIntersection(const Triangle tri, const Vector3 pos,
		float scale, BoundingBox & bb)
{

	Vector3 pos1(pos.x - scale / 2, pos.y - scale / 2, pos.z - scale / 2);
	Vector3 pos2(pos.x + scale / 2, pos.y + scale / 2, pos.z + scale / 2);

	// Test the bounding boxes against each other.
	if(bb.xmax < pos1.x || bb.ymax < pos1.y || bb.zmax < pos1.z) return false;
	if(bb.xmin > pos2.x || bb.ymin > pos2.y || bb.zmin > pos2.z) return false;

	// Test the triangle's normal vector against the diagonal of the octree cell
	// that aligns best with the normal vector.

	// Find the main diagonal of the octree cell.
	unsigned int dir = 0;
	if(tri.n[0].x > 0) dir += 1;
	if(tri.n[0].y > 0) dir += 2;
	if(tri.n[0].z > 0) dir += 4;
	if(dir > 3) dir = 7 - dir;
//TODO: dir needs only to be calculated once for every triangle.

	float a, b;
	Vector3 tempa, tempb;
	switch(dir){
	case 0:
		a = ((pos1.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos1.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos1.z - tri.p[0].z) * tri.n[0].z);
		b = ((pos2.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos2.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos2.z - tri.p[0].z) * tri.n[0].z);
		break;
	case 1:
		a = ((pos2.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos1.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos1.z - tri.p[0].z) * tri.n[0].z);
		b = ((pos1.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos2.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos2.z - tri.p[0].z) * tri.n[0].z);
		break;
	case 2:
		a = ((pos1.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos2.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos1.z - tri.p[0].z) * tri.n[0].z);
		b = ((pos2.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos1.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos2.z - tri.p[0].z) * tri.n[0].z);
		break;
	case 3:
		a = ((pos2.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos2.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos1.z - tri.p[0].z) * tri.n[0].z);
		b = ((pos1.x - tri.p[0].x) * tri.n[0].x)
				+ ((pos1.y - tri.p[0].y) * tri.n[0].y)
				+ ((pos2.z - tri.p[0].z) * tri.n[0].z);
		break;
	}
	// Test if the current cube is above or below the plane of the triangle.
	if((a > 0 && b > 0) || (a < 0 && b < 0)) return false;

	// Test for the triangle shape itself.

	Vector3 f0, f1, f2;
	f0 = tri.p[1] - tri.p[0];
	f1 = tri.p[2] - tri.p[1];
	f2 = tri.p[0] - tri.p[2];

	Vector3 temp;
	float p0, p1, p2;
	float minp, maxp, r;
	Vector3 t0, t1, t2;

	t0 = tri.p[0] - pos;
	t1 = tri.p[1] - pos;
	t2 = tri.p[2] - pos;

	if(!IsAlign(0, -f0.z, f0.y, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(0, -f1.z, f1.y, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(0, -f2.z, f2.y, &t0, &t1, &t2, scale)) return false;

	if(!IsAlign(f0.z, 0, -f0.x, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(f1.z, 0, -f1.x, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(f2.z, 0, -f2.x, &t0, &t1, &t2, scale)) return false;

	if(!IsAlign(-f0.y, f0.x, 0, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(-f1.y, f1.x, 0, &t0, &t1, &t2, scale)) return false;
	if(!IsAlign(-f2.y, f2.x, 0, &t0, &t1, &t2, scale)) return false;

	return true;
}

bool OctreeGenerator::IsAlign(float tempx, float tempy, float tempz,
		Vector3 *t0, Vector3 *t1, Vector3 *t2, float scale)
{
	float p0 = tempx * t0->x + tempy * t0->y + tempz * t0->z;
	float p1 = tempx * t1->x + tempy * t1->y + tempz * t1->z;
	float p2 = tempx * t2->x + tempy * t2->y + tempz * t2->z;
	float maxp = p0;
	float minp = p0;
	if(p1 < minp) minp = p1;
	if(p2 < minp) minp = p2;
	if(p1 > maxp) maxp = p1;
	if(p2 > maxp) maxp = p2;
	float r = fabs(tempx) * scale / 2 + fabs(tempy) * scale / 2
			+ fabs(tempz) * scale / 2;
	if(minp > r || maxp < -r) return false;
	return true;
}
