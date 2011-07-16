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

void Target::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("target"));
	//		nodeObject->AddProperty(_T("name"), objectName);
	parentNode->InsertChild(nodeObject, NULL);


	// Insert new matrix
	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			matrix.ToString());
	temp->InsertChild(temp2, NULL);


	// Insert outline
	//	size_t i;
	//	for(i = 0; i < triangles.GetCount(); i++){
	//		temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("tri"));
	//		nodeObject->InsertChild(temp, NULL);
	//		temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
	//				triangles[i].ToString());
	//		temp->InsertChild(temp2, NULL);
	//	}
}

bool Target::FromXml(wxXmlNode* node)
{
	if(node->GetName() != _T("target")) return false;
	//	objectName = node->GetPropVal(_T("name"), _T(""));


	wxXmlNode *temp = node->GetChildren();

	while(temp != NULL){
		if(temp->GetName() == _T("matrix")) matrix.FromString(
				temp->GetNodeContent());
		temp = temp->GetNext();
	}
	return true;
}

void Target::InsertObject(Object &object, AffineTransformMatrix &shift)
{
	InitImprinting();
	size_t i;
	for(i = 0; i < object.geometries.GetCount(); i++){
		InsertGeometrie(&(object.geometries[i]), shift);
	}
	FinishImprint();
}

//Moves on the outside
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

// Moves on the inside
int Target::NextDir(int sx, int sy, double height, int olddir)
{
	int d = (olddir + 5) % 8;

	char c;
	for(c = 0; c < 8; c++){
		switch(d){
		case 0:
			if(IsFilledAbove(sx + 1, sy + 0, height)) return d;
			break;
		case 1:
			if(IsFilledAbove(sx + 1, sy + 1, height)) return d;
			break;
		case 2:
			if(IsFilledAbove(sx + 0, sy + 1, height)) return d;
			break;
		case 3:
			if(IsFilledAbove(sx - 1, sy + 1, height)) return d;
			break;
		case 4:
			if(IsFilledAbove(sx - 1, sy + 0, height)) return d;
			break;
		case 5:
			if(IsFilledAbove(sx - 1, sy - 1, height)) return d;
			break;
		case 6:
			if(IsFilledAbove(sx + 0, sy - 1, height)) return d;
			break;
		case 7:
			if(IsFilledAbove(sx + 1, sy - 1, height)) return d;
			break;
		}
		d = (d + 1) % 8;
	}
	return -1;
}

// On the outside
const Polygon3 Target::GeneratePolygon(int stx, int sty)
{
	Polygon3 temp;

	while(!IsVisible(stx + 1, sty)){
		stx++;
		if(stx + 2 >= nx){
			stx = -1;
			sty++;
			if(sty >= ny) break;
		}
	}

	temp.Close();
	if(sty == ny) return temp;

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
			return temp;
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

	PolygonFillHoles(temp);
	PolygonSmooth(temp);

	return temp;
}

//On the inside
const Polygon3 Target::GeneratePolygon(int stx, int sty, double height)
{
	Polygon3 temp;

	while(!IsFilledAbove(stx + 1, sty, height)){
		stx++;
		if(stx + 2 >= nx){
			stx = -1;
			sty++;
			if(sty >= ny) break;
		}
	}

	temp.Close();
	if(sty == ny) return temp;
	stx++;
	int x = stx;
	int y = sty;
	int dir = 0;

	do{

		temp.InsertPoint((double) x * rx, (double) y * ry, height);
		dir = NextDir(x, y, height, dir);

		if(dir == -1){
			wxLogError(_T("Target::GeneratePolygon: Lost wall contact!"));
			return temp;
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


	//PolygonFillHoles(polygons.GetCount() - 1);
	//PolygonSmooth(polygons.GetCount() - 1);
	return temp;
}

void Target::PolygonFillHoles(Polygon3 &polygon)
{
	//TODO: This is crude! Find a better way.
	size_t i;
	size_t nrp;
	double m;
	m = 0.0;
	nrp = 0;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		if(polygon.elements[i].z > -0.5){
			nrp++;
			m += polygon.elements[i].z;
		}
	}
	if(nrp == 0) return;
	m /= (double) nrp;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		if(polygon.elements[i].z < -0.5){
			polygon.elements[i].z = m;
		}
	}
}

void Target::PolygonSmooth(Polygon3 &polygon)
{
	size_t i;
	Vector3 d;
	ArrayOfVector3 temp;
	temp = polygon.elements;

	for(i = 0; i < polygon.elements.GetCount(); i++){
		if(i > 0)
			d = polygon.elements[i - 1];
		else
			d = polygon.elements[polygon.elements.GetCount() - 1];
		d += polygon.elements[i];
		if(i + 1 < polygon.elements.GetCount())
			d += polygon.elements[i + 1];
		else
			d += polygon.elements[0];
		polygon.elements[i] = d / 3;
	}
}

void Target::PolygonDropTarget(Polygon3 &polygon, Target &tool)
{
	size_t i;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		this->FoldLower(round(polygon.elements[i].x / rx), round(
				polygon.elements[i].y / ry), polygon.elements[i].z, tool);
	}
}

void Target::PolygonDrop(Polygon3 &polygon, double level)
{
	size_t i;
	double d;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		d = this->GetLevel(polygon.elements[i].x, polygon.elements[i].y);
		polygon.elements[i].z -= level;
		if(d >= 0.0){
			if(d > polygon.elements[i].z) polygon.elements[i].z = d;
		}
	}
}

void Target::PolygonExpand(Polygon3 &polygon, double r)
{
	if(polygon.elements.GetCount() < 2) return;
	size_t i;
	Vector3 o, n, d;
	o = polygon.elements[0];
	for(i = 1; i < polygon.elements.GetCount(); i++){
		n = polygon.elements[i];
		o = n - o;
		o.Normalize();
		d.x = o.y;
		d.y = -o.x;
		d.z = o.z;
		o = n;
		polygon.elements[i] = n + d * r;
	}
}

void Target::PolygonDiminish(Polygon3 &polygon, double r)
{
	PolygonExpand(polygon, -r);
}

void Target::AddSupport(Polygon3 &polygon, double distance, double height,
		double width, double slotWidth)
{

	if(polygon.elements.GetCount() < 2) return;

	double dc = -distance / 2;
	size_t i;
	Vector3 o, v, h, p;
	Vector3 a, b, c, d;


	// Limit polygon range
	for(i = 0; i < polygon.elements.GetCount(); i++){
		if(polygon.elements[i].z >= sz - (height / 2)) polygon.elements[i].z
				= sz - (height / 2) - 0.0001;
		if(polygon.elements[i].z <= (height / 2)) polygon.elements[i].z
				= (height / 2) + 0.0001;
	}

	o = polygon.elements[0];
	for(i = 1; i < polygon.elements.GetCount(); i++){
		p = polygon.elements[i];
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


	//	::glPushMatrix();
	//	::glMultMatrixd(matrix.a);
	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
	toolpath.Paint();
	outline.Paint();


	//	::glPopMatrix();
}

