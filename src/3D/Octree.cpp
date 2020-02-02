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
///////////////////////////////////////////////////////////////////////////////

#include "Octree.h"

#include <stddef.h>
#include <math.h>
#include "OpenGL.h"

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

//void OctreeCell::InsertTriangle(const Triangle tri, const BoundingBox bb)
//{
//
//}
//

void OctreeCell::Paint()
{

	if(hasSubElements){
		::glPushMatrix();
		::glScalef(0.5, 0.5, 0.5);

		::glTranslatef(-0.5, -0.5, -0.5);
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

		::glPushMatrix();

		::glScalef(0.5, 0.5, 0.5);

		// This is just some debugging switch...
		if(1 == 1){

			if(isSolid){
				::glColor3f(this->r, this->g, this->b);

				::glBegin(GL_QUADS);

				::glNormal3i(1, 0, 0);
				::glVertex3i(1, 1, 1);
				::glVertex3i(1, -1, 1);
				::glVertex3i(1, -1, -1);
				::glVertex3i(1, 1, -1);

				::glNormal3i(-1, 0, 0);
				::glVertex3i(-1, 1, 1);
				::glVertex3i(-1, 1, -1);
				::glVertex3i(-1, -1, -1);
				::glVertex3i(-1, -1, 1);

				::glNormal3i(0, 1, 0);
				::glVertex3i(1, 1, 1);
				::glVertex3i(1, 1, -1);
				::glVertex3i(-1, 1, -1);
				::glVertex3i(-1, 1, 1);

				::glNormal3i(0, -1, 0);
				::glVertex3i(1, -1, 1);
				::glVertex3i(-1, -1, 1);
				::glVertex3i(-1, -1, -1);
				::glVertex3i(1, -1, -1);

				::glNormal3i(0, 0, 1);
				::glVertex3i(1, 1, 1);
				::glVertex3i(-1, 1, 1);
				::glVertex3i(-1, -1, 1);
				::glVertex3i(1, -1, 1);

				::glNormal3i(0, 0, -1);
				::glVertex3i(1, 1, -1);
				::glVertex3i(1, -1, -1);
				::glVertex3i(-1, -1, -1);
				::glVertex3i(-1, 1, -1);

				::glEnd();
			}
		}else{
			::glBegin(GL_LINES);

			::glColor3b(100, 0, 0);
			::glNormal3i(1, 0, 0);
			::glVertex3i(-1, -1, -1);
			::glVertex3i(1, -1, -1);

			::glColor3b(0, 100, 0);
			::glNormal3i(0, 1, 0);
			::glVertex3i(-1, -1, -1);
			::glVertex3i(-1, 1, -1);

			::glColor3b(0, 0, 100);
			::glNormal3i(0, 0, 1);
			::glVertex3i(-1, -1, -1);
			::glVertex3i(-1, -1, 1);
			::glEnd();
		}

		::glPopMatrix();
	}
}

Octree::Octree()
{
	tree = new OctreeCell(false);
	displayListGenerated = false;
	displayListIndex = 0;
	depth = 10;
	cellSize = 0.005;
	refresh = false;
}

Octree::~Octree()
{
	if(tree != NULL) delete tree;
}

void Octree::Paint()
{
	if(tree == NULL) return;

	double cubeSize = pow(2.0, depth) * cellSize;

//#if defined __WIN32__
	::glEnable(GL_NORMALIZE);
//#else
//	::glEnable(GL_RESCALE_NORMAL);
//#endif

	::glPushMatrix();

	if(!displayListGenerated){
		displayListIndex = ::glGenLists(1);
		displayListGenerated = true;
		refresh = true;
	}

	if(refresh){
		::glNewList(displayListIndex, GL_COMPILE_AND_EXECUTE);

		::glScalef(cubeSize, cubeSize, cubeSize);

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

