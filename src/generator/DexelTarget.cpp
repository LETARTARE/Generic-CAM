///////////////////////////////////////////////////////////////////////////////
// Name               : DexelTarget.cpp
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
///////////////////////////////////////////////////////////////////////////////

#include "DexelTarget.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfDexelTarget)

#include <GL/gl.h>
#include <wx/log.h>
#include <float.h>
#include <math.h>
#include <wx/string.h>

DexelTarget::DexelTarget()
{
}

DexelTarget::~DexelTarget()
{
}

void DexelTarget::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("target"));
	//		nodeObject->AddProperty(_T("name"), objectName);
	parentNode->InsertChild(nodeObject, NULL);

	// Insert new matrix
	//	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
	//	nodeObject->InsertChild(temp, NULL);
	//	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
	//			matrix.ToString());
	//	temp->InsertChild(temp2, NULL);

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

bool DexelTarget::FromXml(wxXmlNode* node)
{
	if(node->GetName() != _T("target")) return false;
	//	objectName = node->GetPropVal(_T("name"), _T(""));

	wxXmlNode *temp = node->GetChildren();

	while(temp != NULL){
		//		if(temp->GetName() == _T("matrix")) matrix.FromString(
		//				temp->GetNodeContent());
		temp = temp->GetNext();
	}
	return true;
}

void DexelTarget::InsertObject(Object &object)
{
	InitImprinting();
	size_t i;
	for(i = 0; i < object.geometries.GetCount(); i++){
		InsertGeometrie(&(object.geometries[i]), object.matrix);
	}
	FinishImprint();
}

//Moves on the outside
int DexelTarget::NextDir(int sx, int sy, int olddir)
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
int DexelTarget::NextDir(int sx, int sy, double height, int olddir)
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
const Polygon25 DexelTarget::GeneratePolygon(int stx, int sty)
{
	Polygon25 temp;

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

		if(dir == -1){
			wxLogError(_T("DexelTarget::GeneratePolygon: Lost wall contact!"));
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

	temp.PolygonFillHoles();
	temp.PolygonSmooth();

	return temp;
}

void DexelTarget::DocumentField(int x, int y, double height)
{
	int i, j;
	wxString tp;
	for(j = -3; j <= 3; j++){
		tp = wxString::Format(_T("x:%3i y%3i:"), x, y - j);
		for(int i = -3; i <= 3; i++){
			if(IsFilledAbove(x + i, y - j, height))
				tp += _T("# ");
			else
				tp += _T("_ ");
		}
		wxLogMessage(tp);
	}
}

//On the inside
const Polygon25 DexelTarget::GeneratePolygon(int stx, int sty, double height)
{
	Polygon25 temp;

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
			wxLogError(_T("DexelTarget::GeneratePolygon: Lost wall contact!"));
			DocumentField(x, y, height);
			this->field[x + y * nx].upperLimit = -0.0001;
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

	//temp.PolygonFillHoles();
	//temp.PolygonSmooth();
	return temp;
}

const Polygon25 DexelTarget::GenerateConvexOutline(void)
{
	Vector3 temp;
	Polygon25 temp1, temp2;
	size_t i, j, k;

	size_t *left;
	size_t *right;

	size_t first = this->ny;
	size_t last = this->ny;

	left = new size_t[this->ny];
	right = new size_t[this->ny];

	for(i = 0; i < this->ny; i++){
		left[i] = this->nx - 1;
		right[i] = 0;
	}

	size_t p = 0;
	for(j = 0; j < ny; j++){
		for(i = 0; i < nx; i++){
			if(field[p].IsVisible()){
				if(i < left[j]) left[j] = i;
				if(i > right[j]) right[j] = i;
				if(first == this->ny) first = j;
				last = j;
			}
			p++;
		}
	}

	//	for(i = first; i <= last; i++){
	//		temp1.InsertPoint(left[i] * this->rx, i * this->ry, 0.03);
	//	}
	temp1.Close(true);

	if(first == this->ny){
		delete[] left;
		delete[] right;
		return temp1;
	}

	temp2.InsertPoint(right[first] * this->rx, first * this->ry, 0.0);

	double d, dmax;

	i = first;
	temp1.InsertPoint(left[i] * this->rx, i * this->ry, 0.0);
	while(i < last){
		dmax = DBL_MAX;
		k = i;
		for(j = i + 1; j <= last; j++){
			d = (double) ((double) left[j] - (double) left[k])
					/ ((double) j - (double) k);
			if(d < dmax){
				i = j;
				dmax = d;
			}
		}
		temp1.InsertPoint(left[i] * this->rx, i * this->ry, 0.0);
	}

	i = first;
	temp2.InsertPoint(right[i] * this->rx, i * this->ry, 0.0);
	while(i < last){
		dmax = -DBL_MAX;
		k = i;
		for(j = i + 1; j <= last; j++){
			d = (double) ((double) right[j] - (double) right[k])
					/ ((double) j - (double) k);
			if(d > dmax){
				i = j;
				dmax = d;
			}
		}
		temp2.InsertPoint(right[i] * this->rx, i * this->ry, 0.0);
	}

	temp1.Reverse();
	temp1 += temp2;
	temp1.RemoveZeroLength();

	delete[] left;
	delete[] right;

	return temp1;
}

void DexelTarget::PolygonDropDexelTarget(Polygon3 &polygon, DexelTarget &tool)
{
	size_t i;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		this->FoldLower(round(polygon.elements[i].x / rx),
				round(polygon.elements[i].y / ry), polygon.elements[i].z, tool);
	}
}

void DexelTarget::PolygonDrop(Polygon3 &polygon, double level)
{
	size_t i;
	double d;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		d = this->GetLevel(polygon.elements[i].x, polygon.elements[i].y);

		//		if(d >= 0)
		//			polygon.elements[i].z = d;
		//		else
		//			polygon.elements[i].z = 0.0;

		polygon.elements[i].z -= level;
		if(d >= 0.0){
			if(polygon.elements[i].z < d) polygon.elements[i].z = d;
		}else{
			if(polygon.elements[i].z < 0.0) polygon.elements[i].z = 0.0;
		}
	}
}

void DexelTarget::VectorDrop(double &x, double &y, double &z, double level)
{
	size_t i;
	double d;
	d = this->GetLevel(x, y);
	z -= level;
	if(d >= 0.0){
		if(z < d) z = d;
	}else{
		if(z < 0.0) z = 0.0;
	}
}

void DexelTarget::FillOutsidePolygon(Polygon3 &polygon)
{
	size_t *left;
	size_t *right;

	left = new size_t[this->ny];
	right = new size_t[this->ny];

	size_t i, j;
	for(i = 0; i < this->ny; i++){
		left[i] = this->nx;
		right[i] = 0;
	}

	int px, py;
	for(i = 0; i < polygon.elements.GetCount(); i++){
		//TODO: Change this to a real line algorithm.
		px = round(polygon.elements[i].x / this->rx);
		py = round(polygon.elements[i].y / this->ry);
		if(py >= 0 && py < this->ny){
			if(px < this->nx && px > right[py]) right[py] = px;
			if(px < left[py] && px >= 0) left[py] = px;
		}
	}

	size_t p = 0;
	for(i = 0; i < this->ny; i++){
		if(right[i] < left[i]) right[i] = left[i];
		for(j = 0; j < left[i]; j++){
			this->field[p + j].lowerLimit = 0.0;
			this->field[p + j].upperLimit = this->sz;
		}
		for(j = right[i]; j < this->nx; j++){
			this->field[p + j].lowerLimit = 0.0;
			this->field[p + j].upperLimit = this->sz;
		}
		p += this->nx;
	}
	delete[] left;
	delete[] right;
}

void DexelTarget::AddSupport(Polygon3 &polygon, double distance, double height,
		double width, double slotWidth)
{

	if(polygon.elements.GetCount() < 2) return;

	double dc = -distance / 2;
	size_t i;
	Vector3 o, v, h, p;
	Vector3 a, b, c, d;

	// Limit polygon range
	for(i = 0; i < polygon.elements.GetCount(); i++){
		if(polygon.elements[i].z >= sz - (height / 2)) polygon.elements[i].z =
				sz - (height / 2) - 0.0001;
		if(polygon.elements[i].z <= (height / 2)) polygon.elements[i].z =
				(height / 2) + 0.0001;
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

			InsertTriangle(a, b, c, DexelTarget::facing_up);
			InsertTriangle(a, c, d, DexelTarget::facing_up);
			a.z -= height;
			b.z -= height;
			c.z -= height;
			d.z -= height;

			InsertTriangle(a, b, c, DexelTarget::facing_down);
			InsertTriangle(a, c, d, DexelTarget::facing_down);

			dc -= distance;
		}
	}

}

void DexelTarget::SetupDrill(Tool &tool, double diameter, double depth)
{
	this->ClearField();

	double d = diameter + 0.002;
	outLine.Clear();
	outLine.InsertPoint(-d, -d, 0.0);
	outLine.InsertPoint(d, -d, 0.0);
	outLine.InsertPoint(d, d, 0.0);
	outLine.InsertPoint(-d, d, 0.0);
	outLine.Close();

	double r = (diameter - 0.0061) / 2.0;
	MachinePosition temp;
	temp.axisZ = 0.004;
	toolpath.positions.Add(temp);
	temp.axisZ = 0.001;
	toolpath.positions.Add(temp);
	temp.isCutting = true;
	temp.axisZ = -0.001;
	temp.axisX = r;
	toolpath.positions.Add(temp);
	temp.isRotationPositiv = true;
	temp.radiusI = -r;
	while(temp.axisZ > 0.003 - depth){
		temp.axisZ -= 0.003;
		toolpath.positions.Add(temp);
	}
	temp.axisZ = -depth;
	toolpath.positions.Add(temp);
	toolpath.positions.Add(temp);
	temp.axisZ += 0.001;
	temp.axisX = 0.000;
	temp.radiusI = 0.000;
	temp.isCutting = false;
	toolpath.positions.Add(temp);
	temp.axisZ = 0.004;
	toolpath.positions.Add(temp);
}

void DexelTarget::Simulate(void)
{
	this->InitImprinting();
	this->HardInvert();
	Polygon3 temp;
	size_t i;
	for(i = 0; i < toolpath.positions.GetCount(); i++){
		temp.InsertPoint(toolpath.positions[i].axisX,
				toolpath.positions[i].axisY, toolpath.positions[i].axisZ + sz);
	}
	DexelTarget discTool;
	discTool.SetupDisc(0.003, rx, rx);
	this->PolygonDropDexelTarget(temp, discTool);
}

double DexelTarget::GetMinLevel(void)
{
	double d = FLT_MAX;
	size_t i;
	for(i = 0; i < N; i++)
		if(field[i].lowerLimit < d) d = field[i].lowerLimit;
	return d;
}

double DexelTarget::GetMaxUpsideLevel(int &x, int &y)
{
	double d = -FLT_MAX;
	size_t i;
	x = -1;
	y = -1;
	for(i = 0; i < N; i++)
		if(field[i].upperLimitUpside > d){
			d = field[i].upperLimitUpside;
			x = i % nx;
			y = floor(i / nx);
		}
	return d;
}

void DexelTarget::GenerateDistanceMap(double height, bool invert)
{
	size_t i, j, k;
	if(invert){
		for(i = 0; i < N; i++){
			if(field[i].lowerLimit > height){
				field[i].upperLimitUpside = 0.000;
			}else{
				field[i].upperLimitUpside = -1.000;
			}
		}
	}else{
		for(i = 0; i < N; i++){
			if(field[i].upperLimit > height){
				field[i].upperLimitUpside = 0.000;
			}else{
				field[i].upperLimitUpside = -1.000;
			}
		}
	}

	for(i = 0; i < N; i++){
		if(field[i].upperLimitUpside < -0.5) // = inside of area
				{
			field[i].lowerLimitDownside = height - 0.0005;
			field[i].upperLimitDownside = 0.000;
		}else{
			field[i].lowerLimitDownside = -0.001;
			field[i].upperLimitDownside = -0.001;
		}
	}

	double d;
	double r2 = sqrt(rx * rx + ry * ry);

	bool flag = true;
	bool firstRound = true;

	while(flag){
		flag = false;
		for(i = 0; i < N; i++)
			field[i].lowerLimitUpside = field[i].upperLimitUpside;
		for(i = 0; i < N; i++){
			if(!IsOnOuterBorder(i)){
				if(field[i].lowerLimitUpside < -0.5){
					d = FLT_MAX;

					if(field[i + 1].lowerLimitUpside > -0.5
							&& field[i + 1].lowerLimitUpside + rx < d) d =
							field[i + 1].lowerLimitUpside + rx;
					if(field[i - 1].lowerLimitUpside > -0.5
							&& field[i - 1].lowerLimitUpside + rx < d) d =
							field[i - 1].lowerLimitUpside + rx;
					if(field[i + nx].lowerLimitUpside > -0.5
							&& field[i + nx].lowerLimitUpside + ry < d) d =
							field[i + nx].lowerLimitUpside + ry;
					if(field[i - nx].lowerLimitUpside > -0.5
							&& field[i - nx].lowerLimitUpside + ry < d) d =
							field[i - nx].lowerLimitUpside + ry;

					//					if(field[i + nx + 1].lowerLimitUpside > -0.5 && field[i
					//							+ nx + 1].lowerLimitUpside + r2 < d) d = field[i
					//							+ nx + 1].lowerLimitUpside + r2;
					//					if(field[i + nx - 1].lowerLimitUpside > -0.5 && field[i
					//							+ nx - 1].lowerLimitUpside + r2 < d) d = field[i
					//							+ nx - 1].lowerLimitUpside + r2;
					//					if(field[i - nx + 1].lowerLimitUpside > -0.5 && field[i
					//							- nx + 1].lowerLimitUpside + r2 < d) d = field[i
					//							- nx + 1].lowerLimitUpside + r2;
					//					if(field[i - nx - 1].lowerLimitUpside > -0.5 && field[i
					//							- nx - 1].lowerLimitUpside + r2 < d) d = field[i
					//							- nx - 1].lowerLimitUpside + r2;

					if(d < 1000.0){
						field[i].upperLimitUpside = d;
						flag = true;
					}

					// Mark outline in upperLimitDownside
					if(firstRound){
						if(d < 1000.0){
							field[i].upperLimitDownside = height;
						}
					}

				}
			}
		}
		firstRound = false;

	}

	for(i = 0; i < N; i++)
		field[i].upperLimitUpside += sz;

}

void DexelTarget::RaiseDistanceMap(double height, bool invert)
{
	size_t i, j, k;
	if(invert){
		for(i = 0; i < N; i++){
			if(field[i].lowerLimit > height){
				field[i].upperLimitUpside = 0.000;
			}else{
				field[i].upperLimitUpside = -1.000;
			}
		}
	}else{
		for(i = 0; i < N; i++){
			if(field[i].upperLimit > height){
				field[i].upperLimitUpside = 0.000;
			}else{
				field[i].upperLimitUpside = -1.000;
			}
		}
	}

	for(i = 0; i < N; i++){
		if(field[i].upperLimitUpside < -0.5) // = inside of area
				{
			if(field[i].lowerLimitDownside < 0.0) field[i].lowerLimitDownside =
					height - 0.0005;
			field[i].upperLimitDownside = 0.000;
		}
	}
	bool flag;
	for(i = 0; i < N; i++){
		if(!IsOnOuterBorder(i)){
			if(field[i].upperLimitUpside < -0.5){
				flag = false;
				if(field[i + 1].upperLimitUpside > -0.5) flag = true;
				if(field[i - 1].upperLimitUpside > -0.5) flag = true;
				if(field[i + nx].upperLimitUpside > -0.5) flag = true;
				if(field[i - nx].upperLimitUpside > -0.5) flag = true;

				// Mark outline in upperLimitDownside
				if(flag && field[i].lowerLimitDownside > 0.0){
					field[i].upperLimitDownside = height;
				}
			}
		}
	}
}

void DexelTarget::FoldLowerDistance(int x, int y, const DexelTarget &b)
{
	size_t ib, jb, pb, ph;
	size_t cx, cy;
	cx = b.nx / 2;
	cy = b.ny / 2;

	if(x >= 0 && x < nx && y >= 0 && y < ny){
		ph = x + nx * y;
		if(field[ph].upperLimitDownside > 0.0001){
			field[ph].upperLimitDownside = 0.0;
		}
	}
	pb = 0;
	for(jb = 0; jb < b.ny; jb++){
		for(ib = 0; ib < b.nx; ib++){
			if(b.field[pb].IsVisible()){
				if(ib + x >= cx && ib + x < nx + cx && jb + y >= cy
						&& jb + y < ny + cy){
					ph = x + ib - cx + (y + jb - cy) * nx;

					if(field[ph].lowerLimitDownside > 0.0001){
						field[ph].lowerLimitDownside = 0.0;
					}
				}
			}
			pb++;
		}
	}
}

bool DexelTarget::FindNextDistance(int &x, int&y)
{
	size_t i, j, p;
	double d = FLT_MAX;
	double dc;
	int cx, cy;
	bool foundSomething = false;

	p = 0;
	for(j = 0; j < ny; j++)
		for(i = 0; i < nx; i++){
			if(field[p].lowerLimitDownside > 0.0001
					|| field[p].upperLimitDownside > 0.0001){
				dc = ((double) i - (double) x) * ((double) i - (double) x)
						+ ((double) j - (double) y) * ((double) j - (double) y);
				if(dc < d){
					cx = i;
					cy = j;
					d = dc;
					foundSomething = true;
				}
			}
			p++;
		}
	if(foundSomething){
		x = cx;
		y = cy;
	}
	return foundSomething;
}

bool DexelTarget::IsInsideWorkingArea(int x, int y)
{
	if(x < 0 || x >= nx) return false;
	if(y < 0 || y >= ny) return false;
	size_t p = x + y * nx;

	if(field[p].upperLimitDownside > -0.0001) return true;
	return false;

}

bool DexelTarget::HadBeenCut(int x, int y)
{
	if(x < 0 || x >= nx) return false;
	if(y < 0 || y >= ny) return false;
	size_t p = x + y * nx;

	//Outside working area ?
	if(field[p].upperLimitDownside < -0.0001) return false;

	//On border uncut?
	if(field[p].upperLimitDownside > -0.0) return false;

	//Material left?
	if(field[p].lowerLimitDownside > 0.0) return false;

	return true;
}

bool DexelTarget::HasToBeCut(int x, int y)
{
	if(x < 0 || x >= nx) return false;
	if(y < 0 || y >= ny) return false;
	size_t p = x + y * nx;
	if(field[p].lowerLimitDownside > 0.0001) return true;
	if(field[p].upperLimitDownside > 0.0001) return true;
	return false;
}

void DexelTarget::MoveInDir(int &x, int &y, int dir)
{
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
}

//Moves inside the matrial clockwise
int DexelTarget::NextDirReverseDistance(int sx, int sy, int olddir)
{
	int d = (olddir + 5) % 8;

	char c;
	bool isOutOfMaterial = HadBeenCut(sx, sy);
	for(c = 0; c < 16; c++){
		switch(d){
		case 0:
			if(HadBeenCut(sx + 1, sy + 0)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy + 0)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy + 0)) return d;

			break;
		case 1:
			if(HadBeenCut(sx + 1, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy + 1)) return d;
			break;
		case 2:
			if(HadBeenCut(sx + 0, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 0, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 0, sy + 1)) return d;
			break;
		case 3:
			if(HadBeenCut(sx - 1, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy + 1)) return d;
			break;
		case 4:
			if(HadBeenCut(sx - 1, sy + 0)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy + 0)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy + 0)) return d;
			break;
		case 5:
			if(HadBeenCut(sx - 1, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy - 1)) return d;
			break;
		case 6:
			if(HadBeenCut(sx + 0, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 0, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 0, sy - 1)) return d;
			break;
		case 7:
			if(HadBeenCut(sx + 1, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy - 1)) return d;
			break;
		}

		d = (d + 1) % 8;
	}
	return -1;
}

//Moves inside the material to be cut counter-clockwise
int DexelTarget::NextDirForwardDistance(int sx, int sy, int olddir)
{
	int d = (olddir + 3) % 8;

	bool isOutOfMaterial = HadBeenCut(sx, sy);

	char c;
	for(c = 0; c < 16; c++){
		switch(d){
		case 0:
			if(HadBeenCut(sx + 1, sy + 0)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy + 0)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy + 0)) return d;

			break;
		case 1:
			if(HadBeenCut(sx + 1, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy + 1)) return d;
			break;
		case 2:
			if(HadBeenCut(sx + 0, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 0, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 0, sy + 1)) return d;
			break;
		case 3:
			if(HadBeenCut(sx - 1, sy + 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy + 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy + 1)) return d;
			break;
		case 4:
			if(HadBeenCut(sx - 1, sy + 0)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy + 0)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy + 0)) return d;
			break;
		case 5:
			if(HadBeenCut(sx - 1, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx - 1, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx - 1, sy - 1)) return d;
			break;
		case 6:
			if(HadBeenCut(sx + 0, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 0, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 0, sy - 1)) return d;
			break;
		case 7:
			if(HadBeenCut(sx + 1, sy - 1)) isOutOfMaterial = true;
			if(isOutOfMaterial && HasToBeCut(sx + 1, sy - 1)) return d;
			if(isOutOfMaterial && !IsInsideWorkingArea(sx + 1, sy - 1)) return d;
			break;
		}

		d--;
		if(d <= -1) d = 7;
	}
	return -1;
}

void DexelTarget::DocumentField(int x, int y)
{
	int i, j;
	wxString tp;
	for(j = -3; j <= 3; j++){
		tp = wxString::Format(_T("x:%3i y%3i:"), x, y - j);
		for(int i = -3; i <= 3; i++){
			if(HasToBeCut(x + i, y - j))
				tp += _T("X ");
			else
				if(IsInsideWorkingArea(x + i, y - j))
					tp += _T("_ ");
				else
					tp += _T("0 ");
		}
		wxLogMessage(tp);
	}
}

bool DexelTarget::FindStartCutting(int &x, int &y)
{
	int sx = x;
	int sy = y;

	int dx = x;
	int dy = y;

	size_t N = 1000 * 4;

	if(dx == 54 && dy == 49){
		DocumentField(dx, dy);
		//return false;
	}

	int hx, hy;

	if(!HasToBeCut(x, y)){
		wxLogMessage(
				_T("FindStartCutting::Test started in a place not to be cut!"));
		return false;
	}
	char dir = 0;

	while(true) // TODO: Restructure this loop! A while(true)! Yeah right! goto is evil!
	{

		dir = NextDirReverseDistance(sx, sy, dir);

		if(dir == -1) // Wall contact lost
				{
			wxLogMessage(_T("FindStartCutting::Wall contact lost!"));
			return false;
		}

		N--;
		if(N == 0) // Wall contact lost
				{
			wxLogMessage(_T("FindStartCutting:: Timeout!"));
			return false;
		}

		hx = sx;
		hy = sy;
		MoveInDir(hx, hy, dir);

		if(hx == x && hy == y) // Full circle
				{
			return true;
		}

		if(!IsInsideWorkingArea(hx, hy)) // Start of cut found
				{
			x = sx;
			y = sy;
			return true;
		}
		sx = hx;
		sy = hy;

	}
	return false;
}

Polygon25 DexelTarget::FindCut(int &x, int &y)
{
	Polygon25 temp;
	Polygon25 temp2;

	int sx = x;
	int sy = y;
	int hx, hy;

	size_t N = 1000 * 4;

	double rx2 = rx / 2;
	double ry2 = ry / 2;

	temp.InsertPoint((double) x * rx + rx2, (double) y * ry + ry2, 0.002);

	if(!HasToBeCut(x, y)){
		wxLogMessage(_T("FindCut::Test started in a place not to be cut!"));
		return temp;
	}

	char dir = 0;
	while(true) // TODO: Restructure this loop! A while(true)! Yeah right! goto is evil!
	{
		dir = NextDirForwardDistance(sx, sy, dir);

		if(dir == -1) // Wall contact lost
				{
			wxLogMessage(_T("FindCut::Wall contact lost!"));
			return temp;
		}

		N--;
		if(N == 0) // Wall contact lost
				{
			wxLogMessage(_T("FindCut:: Timeout!"));

			size_t i;
			for(i = 0; i < 5; i++){
				temp2.elements.Add(temp.elements[i]);
			}
			return temp2;
		}

		hx = sx;
		hy = sy;
		MoveInDir(hx, hy, dir);

		if(hx == x && hy == y) // Full circle
				{
			return temp;
		}

		if(!IsInsideWorkingArea(hx, hy)) // End of cut found
				{
			x = sx;
			y = sy;
			return temp;
		}

		sx = hx;
		sy = hy;

		temp.InsertPoint((double) sx * rx + rx2, (double) sy * ry + ry2, 0.002);

	}

	return temp;
}

void DexelTarget::Paint(void)
{
	Imprinter::Paint();
	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
	toolpath.Paint();
	::glColor3f(0.5, 0.5, 0.5);
	supportLine.Paint();
	::glColor3f(0.9, 0.9, 0.1);
	outLine.Paint();

}

