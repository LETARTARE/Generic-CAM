///////////////////////////////////////////////////////////////////////////////
// Name               : Quadtree.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.05.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Quadtree.h"

#include <stddef.h>
#include <wx/defs.h>
#include <cmath>

#include "Triangle.h"
#include "Vector3.h"

Quadtree::QuadtreeCell::QuadtreeCell()
{
	sub = NULL;
	top = 0.0;
	bot = 0.0;
	minTop = 0.0;
	maxBot = 0.0;
	bbTop = 0.0;
	bbBot = 0.0;
	SetColor(1.0, 1.0, 1.0);
}

Quadtree::QuadtreeCell::~QuadtreeCell()
{
	if(sub != NULL) delete[] sub;
}

void Quadtree::QuadtreeCell::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Quadtree::QuadtreeCell::Split()
{
	if(sub != NULL) return;

	sub = new QuadtreeCell[4];

	unsigned char i;
	for(i = 0; i < 4; i++){

		sub[i].top = this->top;
		sub[i].bot = this->bot;
		sub[i].minTop = this->minTop;
		sub[i].maxBot = this->maxBot;
		sub[i].bbTop = this->top;
		sub[i].bbBot = this->bot;

		sub[i].r = this->r;
		sub[i].g = this->g;
		sub[i].b = this->b;
	}
}

void Quadtree::QuadtreeCell::InsertTriangle(const Triangle & triangle,
		const BoundingBox & bb, const Vector3 & position, const float cubeSize,
		const unsigned char depth)
{

	if(CheckIntersection(triangle, position, cubeSize, bb)){
		// Check for intersection
		if(depth > 1){

			Split();

			Vector3 temp;

			temp.x = position.x - cubeSize / 4;
			temp.y = position.y - cubeSize / 4;
			sub[0].InsertTriangle(triangle, bb, temp, cubeSize / 2, depth - 1);
			temp.x = position.x + cubeSize / 4;
			temp.y = position.y - cubeSize / 4;
			sub[1].InsertTriangle(triangle, bb, temp, cubeSize / 2, depth - 1);
			temp.x = position.x - cubeSize / 4;
			temp.y = position.y + cubeSize / 4;
			sub[2].InsertTriangle(triangle, bb, temp, cubeSize / 2, depth - 1);
			temp.x = position.x + cubeSize / 4;
			temp.y = position.y + cubeSize / 4;
			sub[3].InsertTriangle(triangle, bb, temp, cubeSize / 2, depth - 1);
		}else{

			Vector3 temp = position;
			temp.z = 1.0;
			float s = temp.Dot(triangle.n[1]);
			float t = temp.Dot(triangle.n[2]);
			if(s > 0 && s < 1 && t > 0 && t < 1 && s + t < 1){

				top = triangle.p[0].z
						- (position.x - triangle.p[0].x) * triangle.n[0].x
								/ triangle.n[0].z
						- (position.y - triangle.p[0].y) * triangle.n[0].y
								/ triangle.n[0].z;
			}
		}
	}

}

bool Quadtree::QuadtreeCell::CheckIntersection(const Triangle & tri,
		const Vector3 & pos, const float & quadSize,
		const BoundingBox & bb) const
{

	Vector3 pos1(pos.x - quadSize / 2, pos.y - quadSize / 2, 0.0);
	Vector3 pos2(pos.x + quadSize / 2, pos.y + quadSize / 2, 0.0);

	// Test the bounding boxes against each other.
	if(bb.xmax < pos1.x || bb.ymax < pos1.y) return false;
	if(bb.xmin > pos2.x || bb.ymin > pos2.y) return false;
	return true;
}

bool Quadtree::QuadtreeCell::Clean(void)
{
	if(sub == 0) return true;

	bool flag = true;
	unsigned char i;
	for(i = 0; i < 4; i++){
		if(sub[i].sub != NULL){
			if(!sub[i].Clean()) flag = false;
		}
	}
	if(!flag) return false;

	float rTop = sub[0].top;
	float rBot = sub[0].bot;
	this->top = sub[0].top;
	this->bot = sub[0].bot;

	for(i = 1; i < 4; i++){
		if(sub[i].top != rTop || sub[i].bot != rBot) flag = false;
		if(sub[i].top > this->top) this->top = sub[i].top;
		if(sub[i].bot < this->bot) this->bot = sub[i].bot;
	}
	if(!flag) return false;

	delete[] sub;
	sub = NULL;
	return true;
}

void Quadtree::QuadtreeCell::Paint()
{

	if(sub != NULL){
		::glPushMatrix();
		::glScalef(0.5, 0.5, 1.0);

		::glTranslatef(-0.5, -0.5, 0.0);
		sub[0].Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[1].Paint();
		::glTranslatef(-1.0, 1.0, 0.0);
		sub[2].Paint();
		::glTranslatef(1.0, 0.0, 0.0);
		sub[3].Paint();
		::glPopMatrix();
	}else{

		::glPushMatrix();

		::glScalef(0.5, 0.5, 1.0);

		// This is just some debugging switch...
		if(1 == 1){

			if(top > bot){
				::glColor3f(this->r, this->g, this->b);

				::glBegin(GL_QUADS);

				::glNormal3i(0, 0, 1);
				::glVertex3f(-1, -1, top);
				::glVertex3f(1, -1, top);
				::glVertex3f(1, 1, top);
				::glVertex3f(-1, 1, top);

				::glNormal3i(0, 0, -1);
				::glVertex3f(-1, -1, bot);
				::glVertex3f(-1, 1, bot);
				::glVertex3f(1, 1, bot);
				::glVertex3f(1, -1, bot);

				::glEnd();
			}
		}else{
			::glBegin(GL_LINE_LOOP);
			::glNormal3i(0, 0, 1);
			::glColor3b(100, 0, 0);
			::glVertex3f(-1, -1, top);
			::glVertex3f(1, -1, top);
			::glVertex3f(1, 1, top);
			::glVertex3f(-1, 1, top);
			::glEnd();
			::glBegin(GL_LINES);
			::glNormal3i(1, 1, 0);
			::glColor3b(0, 100, 0);
			::glVertex3f(0, 0, 0);
			::glVertex3f(0, 0, top);
			::glNormal3i(-1, -1, 0);
			::glColor3b(100, 0, 0);
			::glVertex3f(-0.1, -0.1, 0);
			::glVertex3f(-0.1, -0.1, bot);
			::glEnd();
		}

		::glPopMatrix();
	}
}

Quadtree::Quadtree()
{
	tree = new QuadtreeCell();
	displayListGenerated = false;
	displayListIndex = 0;
	depth = 18;
	cellSize = 0.01;
	refresh = false;

	triangle.p[0].Set(0.1, 0.1, 0.1);
	triangle.p[1].Set(0.5, 0.3, 0.2);
	triangle.p[2].Set(0.25, 0.4, 0.3);
	triangle.CalculateNormal();
	InsertTriangle(triangle);

	triangle.p[0].Set(0.1, 0.1, 0.1);
	triangle.p[1].Set(-0.5, -0.3, 0.0);
	triangle.p[2].Set(0.25, 0.4, 0.2);
	triangle.CalculateNormal();
	InsertTriangle(triangle);

	triangle.p[0].Set(-0.4, 0.5, -0.1);
	triangle.p[1].Set(-0.5, -0.3, 0.0);
	triangle.p[2].Set(0.25, 0.4, 0.2);
	triangle.CalculateNormal();
	InsertTriangle(triangle);

	tree->Clean();

}

Quadtree::~Quadtree()
{
	if(tree != NULL) delete tree;

}

void Quadtree::InsertTriangle(Triangle tri)
{
	if(tree == NULL) return;

	BoundingBox bb;
	bb.Clear();
	bb.Insert(tri);

	float cubeSize = pow(2.0, depth) * cellSize;

	tri.CalculateNormal();

// Remove vertical triangles.
	if(fabs(tri.n[0].z) < 1e-6) return;

	float h = tri.p[0].x * (tri.p[2].y - tri.p[1].y)
			+ tri.p[1].x * (tri.p[0].y - tri.p[2].y)
			+ tri.p[2].x * (tri.p[1].y - tri.p[0].y);
	if(fabs(h) < 1e-6) return;

	tri.n[1].x = (tri.p[0].y - tri.p[2].y) / h;
	tri.n[1].y = (tri.p[2].x - tri.p[0].x) / h;
	tri.n[1].z = (tri.p[0].x * tri.p[2].y - tri.p[0].y * tri.p[2].x) / h;

	tri.n[2].x = (tri.p[1].y - tri.p[0].y) / h;
	tri.n[2].y = (tri.p[0].x - tri.p[1].x) / h;
	tri.n[2].z = (tri.p[0].y * tri.p[1].x - tri.p[0].x * tri.p[1].y) / h;

	Vector3 temp(0.0, 0.0, 0.0);
	tree->InsertTriangle(tri, bb, temp, cubeSize, depth);

//	TriangleInt64 temp;
//	unsigned char i;
//	for(i = 0; i < 3; i++){
//		temp.p[i].x = llround(triangle.p[i].x / scale);
//		temp.p[i].y = llround(triangle.p[i].y / scale);
//		temp.p[i].z = llround(triangle.p[i].z / scale);
//	}

//	root->tree->InsertTriangle(triangle, bb);
}

void Quadtree::Paint(void)
{
	if(tree == NULL) return;

	double cubeSize = pow(2.0, depth) * cellSize;

//#if defined __WIN32__
	::glEnable(GL_NORMALIZE);
//#else
//	::glEnable(GL_RESCALE_NORMAL);
//#endif

	::glBegin(GL_TRIANGLES);
	this->triangle.Paint();
	::glEnd();

	::glPushMatrix();

	if(!displayListGenerated){
		displayListIndex = ::glGenLists(1);
		displayListGenerated = true;
		refresh = true;
	}

	if(refresh){
		::glNewList(displayListIndex, GL_COMPILE_AND_EXECUTE);

		::glScalef(cubeSize, cubeSize, 1.0);

		tree->Paint();

		::glEndList();
		refresh = false;
	}else{
		::glCallList(displayListIndex);
	}

	::glPopMatrix();

//#if defined (__WIN32__)
	::glDisable(GL_NORMALIZE);
//#else
//	::glDisable(GL_RESCALE_NORMAL);
//#endif
}

