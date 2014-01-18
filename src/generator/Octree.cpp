///////////////////////////////////////////////////////////////////////////////
// Name               : Octree.cpp
// Purpose            : Contains an Octree and its support functions
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lgl
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

OctreeCell::OctreeCell(bool isSolid)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
		sub[i] = NULL;
	hasSubElements = false;
	this->isSolid = isSolid;
	SetColor(1.0, 1.0, 1.0);
}

OctreeCell::~OctreeCell()
{
	unsigned char i;
	for(i = 0; i < 8; i++){
		if(sub[i] != NULL) delete sub[i];
	}
}

void OctreeCell::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void OctreeCell::Split(void)
{
	if(hasSubElements) return;
	unsigned char i;
	for(i = 0; i < 8; i++){
		sub[i] = new OctreeCell(this->isSolid);
		sub[i]->r = this->r;
		sub[i]->g = this->g;
		sub[i]->b = this->b;
	}
	this->hasSubElements = true;
}

void OctreeCell::InsertTriangle(const Triangle tri, const BoundingBox bb)
{

}

void OctreeCell::CheckTriangle(const Triangle tri, const Vector3 pos)
{
	// Check for intersection
	if(CheckIntersection(tri, pos, (float) scale)){
		if(scale > 1){
			this->Split();

			scale >>= 1;
			Vector3 temp = pos;

			this->sub[0]->CheckTriangle(tri, temp);
			temp.x = pos.x + scale;
			this->sub[1]->CheckTriangle(tri, temp);
			temp.x = pos.x;
			temp.y = pos.y + scale;
			this->sub[2]->CheckTriangle(tri, temp);
			temp.x = pos.x + scale;
			this->sub[3]->CheckTriangle(tri, temp);
			temp.x = pos.x;
			temp.y = pos.y;
			temp.z = pos.z + scale;
			this->sub[4]->CheckTriangle(tri, temp);
			temp.x = pos.x + scale;
			this->sub[5]->CheckTriangle(tri, temp);
			temp.x = pos.x;
			temp.y = pos.y + scale;
			this->sub[6]->CheckTriangle(tri, temp);
			temp.x = pos.x + scale;
			this->sub[7]->CheckTriangle(tri, temp);
		}else{
			this->isSolid = true;
		}
	}
}
bool OctreeCell::CheckIntersection(const Triangle tri, const Vector3 pos)
{

	Vector3 pos2(pos.x + scale, pos.y + scale, pos.z + scale);

	// Test the bounding boxes against each other.
	if(tri->c[1].x < pos.x || tri->c[1].y < pos.y || tri->c[1].z < pos.z) return false;
	if(tri->c[0].x > pos2.x || tri->c[0].y > pos2.y || tri->c[0].z > pos2.z) return false;

	// Test the normal vector against the best connection inside the cube.
	// Main dir of the normal vector.
	unsigned int dir = 0;
	if(tri->n[0].x > 0) dir += 1;
	if(tri->n[0].y > 0) dir += 2;
	if(tri->n[0].z > 0) dir += 4;
	if(dir > 3) dir = 7 - dir;
	//TODO: dir needs only to be calculated once for every triangle.

	float a, b;
	Vector3 tempa, tempb;
	switch(dir){
	case 0:
		a = ((pos.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos2.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos2.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 1:
		a = ((pos2.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos2.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 2:
		a = ((pos.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos2.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos2.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 3:
		a = ((pos2.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos2.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos.x - tri->p[0].x) * tri->n[0].x)
				+ ((pos.y - tri->p[0].y) * tri->n[0].y)
				+ ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	}
	if((a > 0 && b > 0) || (a < 0 && b < 0)) return false;

	// Test for the triangle shape.
	Vector3 f0, f1, f2;
	f0 = tri->p[1] - tri->p[0];
	f1 = tri->p[2] - tri->p[1];
	f2 = tri->p[0] - tri->p[2];

	Vector3 temp;
	float p0, p1, p2;
	float minp, maxp, r;
	Vector3 t0, t1, t2;
	t0 = tri->p[0] - pos - scale / 2;
	t1 = tri->p[1] - pos - scale / 2;
	t2 = tri->p[2] - pos - scale / 2;

	temp.Set(0, -f0.z, f0.y);

	temp.Set(f0.z, 0, -f0.x);

	temp.Set(-f0.y, f0.x, 0);

	temp.Set(0, -f1.z, f1.y);

	temp.Set(f1.z, 0, -f1.x);

	temp.Set(-f1.y, f1.x, 0);

	p0 = temp.x * t0.x + temp.y * t0.y + temp.z * t0.z;
	p1 = temp.x * t1.x + temp.y * t1.y + temp.z * t1.z;
	p2 = temp.x * t2.x + temp.y * t2.y + temp.z * t2.z;
	maxp = p0;
	minp = p1;
	if(p1 < minp) minp = p1;
	if(p2 < minp) minp = p2;
	if(p1 > maxp) maxp = p1;
	if(p2 > maxp) maxp = p2;
	r = fabs(temp.x) + fabs(temp.y) + fabs(temp.z);
	r *= scale;
	if(minp > r / 2 || maxp < -r / 2) return false;

	temp.Set(0, -f2.z, f2.y);

	temp.Set(f2.z, 0, -f2.x);

	temp.Set(-f2.y, f2.x, 0);

	return true;
}

void OctreeCell::Paint()
{

	if(hasSubElements){
		::glPushMatrix();
		::glScalef(0.5, 0.5, 0.5);

		sub[0]->Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[1]->Paint();
		::glTranslatef(-1.0, 1.0, 0.0);
		sub[2]->Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[3]->Paint();
		::glTranslatef(-1.0, -1.0, 1.0);
		sub[4]->Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[5]->Paint();
		::glTranslatef(-1.0, 1.0, 0.0);
		sub[6]->Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[7]->Paint();

		::glPopMatrix();
	}else{

		// This is just some debugging switch...
		if(1 == 1){
			if(isSolid){
				::glColor3f(this->r, this->b, this->g);
				::glBegin(GL_QUADS);

				::glNormal3i(1, 0, 0);
				::glVertex3i(1, 1, 1);
				::glVertex3i(1, 0, 1);
				::glVertex3i(1, 0, 0);
				::glVertex3i(1, 1, 0);

				::glNormal3i(-1, 0, 0);
				::glVertex3i(0, 1, 1);
				::glVertex3i(0, 1, 0);
				::glVertex3i(0, 0, 0);
				::glVertex3i(0, 0, 1);

				::glNormal3i(0, 1, 0);
				::glVertex3i(1, 1, 1);
				::glVertex3i(1, 1, 0);
				::glVertex3i(0, 1, 0);
				::glVertex3i(0, 1, 1);

				::glNormal3i(0, -1, 0);
				::glVertex3i(1, 0, 1);
				::glVertex3i(0, 0, 1);
				::glVertex3i(0, 0, 0);
				::glVertex3i(1, 0, 0);

				::glNormal3i(0, 0, 1);
				::glVertex3i(1, 1, 1);
				::glVertex3i(0, 1, 1);
				::glVertex3i(0, 0, 1);
				::glVertex3i(1, 0, 1);

				::glNormal3i(0, 0, -1);
				::glVertex3i(1, 1, 0);
				::glVertex3i(1, 0, 0);
				::glVertex3i(0, 0, 0);
				::glVertex3i(0, 1, 0);

				::glEnd();
			}
		}else{
			::glBegin(GL_LINES);

			::glColor3b(100, 0, 0);
			::glNormal3i(1, 0, 0);
			::glVertex3i(0, 0, 0);
			::glVertex3i(1, 0, 0);

			::glColor3b(0, 100, 0);
			::glNormal3i(0, 1, 0);
			::glVertex3i(0, 0, 0);
			::glVertex3i(0, 1, 0);

			::glColor3b(0, 0, 100);
			::glNormal3i(0, 0, 1);
			::glVertex3i(0, 0, 0);
			::glVertex3i(0, 0, 1);
			::glEnd();
		}
	}
}

Octree::Octree()
{
	tree = new OctreeCell(false);
	scale = 1 / 30.0;
	displayListGenerated = false;
}

Octree::~Octree()
{
	if(tree != NULL) delete tree;
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

	if(!displayListGenerated){
		displayListIndex = ::glGenLists(1);
		displayListGenerated = true;
		refresh = true;
	}

	if(refresh){
		::glNewList(displayListIndex, GL_COMPILE_AND_EXECUTE);

#if defined __WIN32__
		::glEnable(GL_NORMALIZE);
#else
		::glEnable(GL_RESCALE_NORMAL);
#endif

		tree->Paint();

#if defined (__WIN32__)
		::glDisable(GL_NORMALIZE);
#else
		::glDisable(GL_RESCALE_NORMAL);
#endif

		::glEndList();
		refresh = false;
	}else{
		::glCallList(displayListIndex);
	}

	::glPopMatrix();
}

