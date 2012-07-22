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
WX_DEFINE_OBJARRAY(ArrayOfOctreeElement)

OctreeElement::OctreeElement(bool isSolid)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
		sub[i] = NULL;
	hasSubElements = false;
	this->isSolid = isSolid;
	colorNormal.Set(1.0, 1.0, 0.0);
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
		sub[i] = new OctreeElement(isSolid);
	}
	hasSubElements = true;
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

		if(isSolid){
			::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
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
	}
}

Octree::Octree()
{
	root = new OctreeElement(true);

	root->Split();
	root->sub[0]->isSolid = false;

	displayListGenerated = false;
}

Octree::~Octree()
{
	if(root != NULL) delete root;
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
		if(root != NULL) root->Paint();
		::glEndList();
		refresh = false;
	}else{
		::glCallList(displayListIndex);
	}
}
