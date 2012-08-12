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

OctreeElement::OctreeElement(bool isSolid)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
		sub[i] = NULL;
	hasSubElements = false;
	this->isSolid = isSolid;
	color.Set(1.0, 1.0, 1.0);
	sdx = sdy = sdz = -1.0; // -1 = No subdivision detected.
}

OctreeElement::~OctreeElement()
{
	unsigned char i;
	for(i = 0; i < 8; i++){
		if(sub[i] != NULL) delete sub[i];
	}
}

void OctreeElement::Split(void)
{
	if(hasSubElements) return;
	unsigned char i;
	for(i = 0; i < 8; i++){
		sub[i] = new OctreeElement(this->isSolid);
		sub[i]->color = this->color;
	}
	hasSubElements = true;
}

bool OctreeElement::CheckIntersection(Triangle *tri, Vector3 pos, float scale)
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
		a = ((pos.x - tri->p[0].x) * tri->n[0].x) + ((pos.y - tri->p[0].y)
				* tri->n[0].y) + ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos2.x - tri->p[0].x) * tri->n[0].x) + ((pos2.y - tri->p[0].y)
				* tri->n[0].y) + ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 1:
		a = ((pos2.x - tri->p[0].x) * tri->n[0].x) + ((pos.y - tri->p[0].y)
				* tri->n[0].y) + ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos.x - tri->p[0].x) * tri->n[0].x) + ((pos2.y - tri->p[0].y)
				* tri->n[0].y) + ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 2:
		a = ((pos.x - tri->p[0].x) * tri->n[0].x) + ((pos2.y - tri->p[0].y)
				* tri->n[0].y) + ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos2.x - tri->p[0].x) * tri->n[0].x) + ((pos.y - tri->p[0].y)
				* tri->n[0].y) + ((pos2.z - tri->p[0].z) * tri->n[0].z);
		break;
	case 3:
		a = ((pos2.x - tri->p[0].x) * tri->n[0].x) + ((pos2.y - tri->p[0].y)
				* tri->n[0].y) + ((pos.z - tri->p[0].z) * tri->n[0].z);
		b = ((pos.x - tri->p[0].x) * tri->n[0].x) + ((pos.y - tri->p[0].y)
				* tri->n[0].y) + ((pos2.z - tri->p[0].z) * tri->n[0].z);
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
	t0 = tri->p[0] - pos -scale/2;
	t1 = tri->p[1] - pos -scale/2;
	t2 = tri->p[2] - pos -scale/2;

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
		if(minp > r/2 || maxp < -r/2) return false;



	temp.Set(0, -f2.z, f2.y);


	temp.Set(f2.z, 0, -f2.x);


	temp.Set(-f2.y, f2.x, 0);


	return true;
}

void OctreeElement::CheckTriangle(Triangle *tri, Vector3 pos, uint32_t scale)
{
	// Check for intersection
	if(CheckIntersection(tri, pos, (float) scale)){
		if(scale > 1){
			this->Split();

			scale >>= 1;
			Vector3 temp = pos;

			this->sub[0]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x + scale;
			this->sub[1]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x;
			temp.y = pos.y + scale;
			this->sub[2]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x + scale;
			this->sub[3]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x;
			temp.y = pos.y;
			temp.z = pos.z + scale;
			this->sub[4]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x + scale;
			this->sub[5]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x;
			temp.y = pos.y + scale;
			this->sub[6]->CheckTriangle(tri, temp, scale);
			temp.x = pos.x + scale;
			this->sub[7]->CheckTriangle(tri, temp, scale);
		}else{

			this->isSolid = true;
		}
	}
}

void OctreeElement::Paint()
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
				::glColor3f(color.x, color.y, color.z);
				::glBegin(GL_QUADS);

				::glNormal3f(1, 0, 0);
				::glVertex3f(1, 1, 1);
				::glVertex3f(1, 0, 1);
				::glVertex3f(1, 0, 0);
				::glVertex3f(1, 1, 0);

				::glNormal3f(-1, 0, 0);
				::glVertex3f(0, 1, 1);
				::glVertex3f(0, 1, 0);
				::glVertex3f(0, 0, 0);
				::glVertex3f(0, 0, 1);

				::glNormal3f(0, 1, 0);
				::glVertex3f(1, 1, 1);
				::glVertex3f(1, 1, 0);
				::glVertex3f(0, 1, 0);
				::glVertex3f(0, 1, 1);

				::glNormal3f(0, -1, 0);
				::glVertex3f(1, 0, 1);
				::glVertex3f(0, 0, 1);
				::glVertex3f(0, 0, 0);
				::glVertex3f(1, 0, 0);

				::glNormal3f(0, 0, 1);
				::glVertex3f(1, 1, 1);
				::glVertex3f(0, 1, 1);
				::glVertex3f(0, 0, 1);
				::glVertex3f(1, 0, 1);

				::glNormal3f(0, 0, -1);
				::glVertex3f(1, 1, 0);
				::glVertex3f(1, 0, 0);
				::glVertex3f(0, 0, 0);
				::glVertex3f(0, 1, 0);

				::glEnd();
			}
		}else{
			::glBegin(GL_LINES);

			::glColor3b(100, 0, 0);
			::glNormal3f(1, 0, 0);
			::glVertex3f(0, 0, 0);
			::glVertex3f(1, 0, 0);

			::glColor3b(0, 100, 0);
			::glNormal3f(0, 1, 0);
			::glVertex3f(0, 0, 0);
			::glVertex3f(0, 1, 0);

			::glColor3b(0, 0, 100);
			::glNormal3f(0, 0, 1);
			::glVertex3f(0, 0, 0);
			::glVertex3f(0, 0, 1);
			::glEnd();

		}

	}
}

Octree::Octree()
{
	root = new OctreeElement();
	root->color.Set(1.0, 1.0, 0.0); // Yellow cubes.
	maxDepth = 10; // 2m / (2^5) = 63cm
	displayListGenerated = false;


	// Test triangle:
	Triangle tri;
	tri.p[0].Set(0.15, 0.1, 0.1);
	tri.p[1].Set(0.5, 0.1, 0.1);
	tri.p[2].Set(0.15, 0.5, 0.1);

	InsertTriangle(tri);

}

Octree::~Octree()
{
	if(root != NULL) delete root;
}

void Octree::InsertTriangle(Triangle tri)
{

	uint32_t scale = (1 << maxDepth);
	tri.p[0] *= (scale / 2);
	tri.p[1] *= (scale / 2);
	tri.p[2] *= (scale / 2);


	// Generate a bounding box around the triangle.
	// (Do not use call by reference, for the triangle is changed in this function.)
	// tri.c[0] contains the min. corner of the box and tri.c[1] the max. corner.
	tri.c[0].x = tri.c[1].x = tri.p[0].x;
	tri.c[0].y = tri.c[1].y = tri.p[0].y;
	tri.c[0].z = tri.c[1].z = tri.p[0].z;

	if(tri.c[0].x > tri.p[1].x) tri.c[0].x = tri.p[1].x;
	if(tri.c[0].y > tri.p[1].y) tri.c[0].y = tri.p[1].y;
	if(tri.c[0].z > tri.p[1].z) tri.c[0].z = tri.p[1].z;
	if(tri.c[0].x > tri.p[2].x) tri.c[0].x = tri.p[2].x;
	if(tri.c[0].y > tri.p[2].y) tri.c[0].y = tri.p[2].y;
	if(tri.c[0].z > tri.p[2].z) tri.c[0].z = tri.p[2].z;

	if(tri.c[1].x < tri.p[1].x) tri.c[1].x = tri.p[1].x;
	if(tri.c[1].y < tri.p[1].y) tri.c[1].y = tri.p[1].y;
	if(tri.c[1].z < tri.p[1].z) tri.c[1].z = tri.p[1].z;
	if(tri.c[1].x < tri.p[2].x) tri.c[1].x = tri.p[2].x;
	if(tri.c[1].y < tri.p[2].y) tri.c[1].y = tri.p[2].y;
	if(tri.c[1].z < tri.p[2].z) tri.c[1].z = tri.p[2].z;


	// Calculate the normal vector of the triangle.
	tri.CalculateNormal();

	Vector3 pos(0, 0, 0);

	if(root != NULL) root->CheckTriangle(&tri, pos, scale);

}

void Octree::Paint()
{

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
		::glScalef(2.0, 2.0, 2.0);
		if(root != NULL) root->Paint();
		::glPopMatrix();


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
}
