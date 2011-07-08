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
#include <wx/log.h>
#include <wx/string.h>

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

int Target::NextDir(int sx, int sy, int olddir)
{
	int d = (olddir + 3) % 8;

	char c;
	for(c = 0; c < 8; c++){
		switch(d){
		case 0:
			if(!IsVisible(sx + 1, sy + 0)) return d;
			break;
		case 1:
			if(!IsVisible(sx + 1, sy + 1)) return d;
			break;
		case 2:
			if(!IsVisible(sx + 0, sy + 1)) return d;
			break;
		case 3:
			if(!IsVisible(sx - 1, sy + 1)) return d;
			break;
		case 4:
			if(!IsVisible(sx - 1, sy + 0)) return d;
			break;
		case 5:
			if(!IsVisible(sx - 1, sy - 1)) return d;
			break;
		case 6:
			if(!IsVisible(sx + 0, sy - 1)) return d;
			break;
		case 7:
			if(!IsVisible(sx + 1, sy - 1)) return d;
			break;
		}

		d--;
		if(d <= -1) d = 7;
	}
	return -1;
}

int Target::NextDir(int sx, int sy, double height, int olddir)
{
	int d = (olddir + 3) % 8;

	char c;
	for(c = 0; c < 8; c++){
		switch(d){
		case 0:
			if(!IsFilledAbove(sx + 1, sy + 0, height)) return d;
			break;
		case 1:
			if(!IsFilledAbove(sx + 1, sy + 1, height)) return d;
			break;
		case 2:
			if(!IsFilledAbove(sx + 0, sy + 1, height)) return d;
			break;
		case 3:
			if(!IsFilledAbove(sx - 1, sy + 1, height)) return d;
			break;
		case 4:
			if(!IsFilledAbove(sx - 1, sy + 0, height)) return d;
			break;
		case 5:
			if(!IsFilledAbove(sx - 1, sy - 1, height)) return d;
			break;
		case 6:
			if(!IsFilledAbove(sx + 0, sy - 1, height)) return d;
			break;
		case 7:
			if(!IsFilledAbove(sx + 1, sy - 1, height)) return d;
			break;
		}

		d--;
		if(d <= -1) d = 7;
	}
	return -1;
}

void Target::GeneratePolygon(int stx, int sty)
{
	while(!IsVisible(stx + 1, sty)){
		stx++;
		if(stx + 2 >= nx){
			stx = -1;
			sty++;
			if(sty >= ny) break;
		}
	}

	Polygon3 temp;
	temp.Clear();
	temp.Close();
	if(sty == ny) return;

	int x = stx;
	int y = sty;
	int dir = 4;
	double z = -1.0;

	do{

		temp.InsertPoint((double) x * rx, (double) y * ry, z);
		dir = NextDir(x, y, dir);


		//		if(x == 100 && y == 66){
		//			int i, j;
		//			wxString temp;
		//			for(j = -3; j <= 3; j++){
		//				temp = wxString::Format(_T("y %3i:"), j);
		//				for(int i = -3; i <= 3; i++){
		//					if(IsVisible(x + i, y + j))
		//						temp += _T("X ");
		//					else
		//						temp += _T(". ");
		//				}
		//				wxLogMessage(temp);
		//
		//			}
		//			i = i + 1;
		//		}

		if(dir == -1){
			wxLogError(_T("Target::GeneratePolygon: Lost wall contact!"));
			return;
		}

		switch(dir){
		case 0:
			z = GetMeanLevel(x + 1, y + 1);
			x++;
			break;
		case 1:
			z = GetMeanLevel(x + 0, y + 1);
			x++;
			y++;
			break;
		case 2:
			z = GetMeanLevel(x - 1, y + 1);
			y++;
			break;
		case 3:
			z = GetMeanLevel(x - 1, y + 0);
			x--;
			y++;
			break;
		case 4:
			z = GetMeanLevel(x - 1, y - 1);
			x--;
			break;
		case 5:
			z = GetMeanLevel(x + 0, y - 1);
			x--;
			y--;
			break;
		case 6:
			z = GetMeanLevel(x + 1, y - 1);
			y--;
			break;
		case 7:
			z = GetMeanLevel(x + 1, y + 0);
			x++;
			y--;
			break;
		}
	}while(x != stx || y != sty);

	polygons.Add(temp);
	PolygonFillHoles(polygons.GetCount() - 1);
	PolygonSmooth(polygons.GetCount() - 1);
}

bool Target::GeneratePolygon(int stx, int sty, double height)
{
	while(!IsFilledAbove(stx + 1, sty, height)){
		stx++;
		if(stx + 2 >= nx){
			stx = -1;
			sty++;
			if(sty >= ny) break;
		}
	}

	Polygon3 temp;
	temp.Clear();
	temp.Close();
	if(sty == ny) return false;

	int x = stx;
	int y = sty;
	int dir = 4;

	do{

		temp.InsertPoint((double) x * rx, (double) y * ry, height);
		dir = NextDir(x, y, height, dir);

		if(dir == -1){
			wxLogError(_T("Target::GeneratePolygon: Lost wall contact!"));
			return false;
		}

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
	}while(x != stx || y != sty);

	polygons.Add(temp);
	//PolygonFillHoles(polygons.GetCount() - 1);
	//PolygonSmooth(polygons.GetCount() - 1);
	return true;
}

void Target::PolygonFillHoles(size_t nr)
{
	//TODO: This is crude! Find a better way.
	size_t i;
	size_t nrp;
	double m;
	m = 0.0;
	nrp = 0;
	for(i = 0; i < polygons[nr].elements.GetCount(); i++){
		if(polygons[nr].elements[i].z > -0.5){
			nrp++;
			m += polygons[nr].elements[i].z;
		}
	}
	if(nrp == 0) return;
	m /= (double) nrp;
	for(i = 0; i < polygons[nr].elements.GetCount(); i++){
		if(polygons[nr].elements[i].z < -0.5){
			polygons[nr].elements[i].z = m;
		}
	}
}

void Target::PolygonSmooth(size_t nr)
{
	size_t i;
	Vector3 d;
	ArrayOfVector3 temp;
	temp = polygons[nr].elements;

	for(i = 0; i < temp.GetCount(); i++){
		if(i > 0)
			d = temp[i - 1];
		else
			d = temp[temp.GetCount() - 1];
		d += temp[i];
		if(i + 1 < temp.GetCount())
			d += temp[i + 1];
		else
			d += temp[0];
		polygons[nr].elements[i] = d / 3;
	}
}

void Target::PolygonDropTarget(size_t nrPolygon, Target* target)
{
	size_t i;
	for(i = 0; i < polygons[nrPolygon].elements.GetCount(); i++){
		FoldLower(round(polygons[nrPolygon].elements[i].x / rx), round(
				polygons[nrPolygon].elements[i].y / ry), polygons[nrPolygon].elements[i].z, target);
	}
}

void Target::PolygonDrop(size_t nrPolygon, double level)
{
	size_t i;
	double d;
	for(i = 0; i < polygons[nrPolygon].elements.GetCount(); i++){
		d = GetLevel(polygons[nrPolygon].elements[i].x,
				polygons[nrPolygon].elements[i].y);
		polygons[nrPolygon].elements[i].z -= level;
		if(d >= 0.0){
			if(d > polygons[nrPolygon].elements[i].z) polygons[nrPolygon].elements[i].z
					= d;
		}
	}
}

void Target::PolygonDiminish(size_t nrPolygon, double r)
{
	if(polygons[nrPolygon].elements.GetCount() < 2) return;

	size_t i;

	Vector3 o, n, d;

	o = polygons[nrPolygon].elements[0];
	for(i = 1; i < polygons[nrPolygon].elements.GetCount(); i++){
		n = polygons[nrPolygon].elements[i];
		o = n - o;
		o.Normalize();
		d.x = -o.y;
		d.y = o.x;
		d.z = o.z;
		o = n;

		polygons[nrPolygon].elements[i] = n + d * r;
	}
}

void Target::AddSupport(size_t polygonNr, double distance, double height,
		double width, double slotWidth)
{

	if(polygons[polygonNr].elements.GetCount() < 2) return;

	double dc = -distance / 2;
	size_t i;
	Vector3 o, v, h, p;
	Vector3 a, b, c, d;


	// Limit polygon range
	for(i = 0; i < polygons[polygonNr].elements.GetCount(); i++){
		if(polygons[polygonNr].elements[i].z >= sz - (height / 2)) polygons[polygonNr].elements[i].z
				= sz - (height / 2) - 0.0001;
		if(polygons[polygonNr].elements[i].z <= (height / 2)) polygons[polygonNr].elements[i].z
				= (height / 2) + 0.0001;
	}

	o = polygons[polygonNr].elements[0];
	for(i = 1; i < polygons[polygonNr].elements.GetCount(); i++){
		p = polygons[polygonNr].elements[i];
		h = o - p;
		o = p;
		h.z = 0.0;
		dc += h.Abs();
		if(dc > 0){
			h.Normalize();
			v.x = h.y;
			v.y = -h.x;
			v.z = 0.0;


			//TODO: Write a smarter algorithm!

			a = p + h * width / 2;
			d = p - h * width / 2;
			b = a + v * slotWidth;
			c = d + v * slotWidth;
			a = a - v * slotWidth;
			d = d - v * slotWidth;

			a.z += height / 2;
			b.z += height / 2;
			c.z += height / 2;
			d.z += height / 2;

			InsertTriangle(a, b, c, Target::facing_up);
			InsertTriangle(a, c, d, Target::facing_up);
			a.z -= height;
			b.z -= height;
			c.z -= height;
			d.z -= height;

			InsertTriangle(a, b, c, Target::facing_down);
			InsertTriangle(a, c, d, Target::facing_down);

			dc -= distance;
		}
	}

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

