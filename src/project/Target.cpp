///////////////////////////////////////////////////////////////////////////////
// Name               : Target.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.07.2011
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


#include "Target.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTarget)

#include <GL/gl.h>

Target::Target()
{
}

Target::~Target()
{
}

void Target::InsertObject(Object *object, AffineTransformMatrix shift)
{
	InitImprinting();
	size_t i;
	for(i = 0; i < object->geometries.GetCount(); i++){
		InsertGeometrie(&(object->geometries[i]), shift);
	}
	FinishImprint();
}

int Target::NextDir(int sx, int sy, double height, int olddir)
{
	int d = (olddir + 4) % 8;

	char c;
	for(c = 0; c < 8; c++){
		switch(d){
		case 0:
			if(IsFilledAbove(sx + 1, sy + 1, height)) return d;
			break;
		case 1:
			if(IsFilledAbove(sx + 0, sy + 1, height)) return d;
			break;
		case 2:
			if(IsFilledAbove(sx - 1, sy + 1, height)) return d;
			break;
		case 3:
			if(IsFilledAbove(sx - 1, sy + 0, height)) return d;
			break;
		case 4:
			if(IsFilledAbove(sx - 1, sy - 1, height)) return d;
			break;
		case 5:
			if(IsFilledAbove(sx + 0, sy - 1, height)) return d;
			break;
		case 6:
			if(IsFilledAbove(sx + 1, sy - 1, height)) return d;
			break;
		case 7:
			if(IsFilledAbove(sx + 1, sy + 0, height)) return d;
			break;
		}

		d = (d + 1) % 8;
	}
	return olddir;
}

void Target::GeneratePolygon(int sx, int sy, double height)
{
	while(!IsFilledAbove(sx + 1, sy, height)){
		sx++;
		if(sx + 2 >= nx){
			sx = -1;
			sy++;
			if(sy >= ny) break;
		}
	}

	Polygon3 temp;
	temp.Clear();

	int x = sx;
	int y = sy;
	int dir = 0;

	do{
		temp.InsertPoint((double) x * rx, (double) y * ry, 0.0);
		dir = NextDir(x, y, height, dir);
		switch(dir){
		case 0:
			x++;
			break;
		case 1:
			x++;
			y++;
			break;
		case 2:
			y++;
			break;
		case 3:
			x--;
			y++;
			break;
		case 4:
			x--;
			break;
		case 5:
			x--;
			y--;
			break;
		case 6:
			y--;
			break;
		case 7:
			x++;
			y--;
			break;
		}
	}while(x != sx || y != sy);

	temp.matrix.TranslateLocal(0, 0, height);
	polygons.Add(temp);

}

void Target::Paint(void)
{
	Imprinter::Paint();
	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);

	size_t i;
	for(i = 0; i < polygons.GetCount(); i++){
		polygons[i].Paint();
	}

	::glPopMatrix();
}

