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

//#include "../machine/MachinePosition.h"

#include <wx/log.h>
#include <wx/string.h>
#include <GL/gl.h>
#include <math.h>
#include <float.h>

DexelTarget::DexelTarget()
{
}

DexelTarget::~DexelTarget()
{
}

//void DexelTarget::ToXml(wxXmlNode* parentNode)
//{
//	wxXmlNode *temp, *temp2;
//	wxXmlNode *nodeObject = NULL;
//
//	nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("target"));
//	//		nodeObject->AddProperty(_T("name"), objectName);
//	parentNode->InsertChild(nodeObject, NULL);

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
//}

//bool DexelTarget::FromXml(wxXmlNode* node)
//{
//	if(node->GetName() != _T("target")) return false;
//	//	objectName = node->GetPropVal(_T("name"), _T(""));
//
//	wxXmlNode *temp = node->GetChildren();
//
//	while(temp != NULL){
//		//		if(temp->GetName() == _T("matrix")) matrix.FromString(
//		//				temp->GetNodeContent());
//		temp = temp->GetNext();
//	}
//	return true;
//}

void DexelTarget::InsertObject(const Object &object,
		const AffineTransformMatrix & shift)
{
	for(size_t i = 0; i < object.geometries.GetCount(); i++)
		InsertGeometrie(&(object.geometries[i]), shift * object.matrix);
}

void DexelTarget::SetupTool(const Tool &tool, const double resolutionX,
		const double resolutionY)
{
	const double radius = tool.GetMaxDiameter() / 2.0;
	const double depth = tool.GetPositiveLength();

	// Calculate the size to be odd, so there always a cell in the center.
	const size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	const size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;

	const double centerX = (ceil(radius / resolutionX) + 0.5) * this->rx;
	const double centerY = (ceil(radius / resolutionY) + 0.5) * this->ry;

	// Prefill the up-layer with the distance from the center
	// (speeds up the toolshape creation)
	size_t p = 0;
	double py = ry / 2;
	for(size_t j = 0; j < ny; j++){
		double px = rx / 2;
		for(size_t i = 0; i < nx; i++){
			double d = (px - centerX) * (px - centerX)
					+ (py - centerY) * (py - centerY);
			if(d >= 0.0)
				d = sqrt(d);
			else
				d = 0.0;
			field[p].up = d;
			field[p].down = FLT_MAX;
			px += rx;
			p++;
		}
		py += ry;
	}

	for(size_t i = 0; i < tool.contour.GetCount(); i++){
		const double dRadius = tool.contour[i].p2.x - tool.contour[i].p1.x;
		if(dRadius >= 0) continue;
		for(size_t j = 0; j < this->N; j++){
			if(field[j].up < tool.contour[i].p2.x
					|| field[j].up > tool.contour[i].p1.x) continue;
			// Linear interpolation for conic changes
			double d = (tool.contour[i].p2.z - tool.contour[i].p1.z)
					* (field[j].up - tool.contour[i].p1.x) / dRadius;
			d += tool.contour[i].p1.z;
			// Turn tool around, so that it is pointing in -Z direction, tip at 0.
			d = depth - d;
			if(d < field[j].down) field[j].down = d;
		}
	}

	// Put a square cap on top of the tool.
	for(size_t j = 0; j < this->N; j++)
		field[j].up = depth;

	refresh = true;
}

void DexelTarget::DocumentField(int x, int y, double height)
{
	wxString tp;
	for(int_fast8_t j = -3; j <= 3; j++){
		tp = wxString::Format(_T("x:%3i y%3i:"), x, y - j);
		for(int_fast8_t i = -3; i <= 3; i++){
			if(IsFilledAbove(x + i, y - j, height))
				tp += _T("# ");
			else
				tp += _T("_ ");
		}
		wxLogMessage(tp);
	}
}

void DexelTarget::DocumentField(int x, int y)
{
	wxString tp;
	for(int_fast8_t j = -3; j <= 3; j++){
		tp = wxString::Format(_T("x:%3i y%3i:"), x, y - j);
		for(int_fast8_t i = -3; i <= 3; i++){
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

void DexelTarget::Paint(void) const
{
	Imprinter::Paint();
	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
//	toolpath.Paint();
	::glColor3f(0.5, 0.5, 0.5);
	supportLine.Paint();
	::glColor3f(0.9, 0.9, 0.1);
	outLine.Paint();
}

void DexelTarget::Simulate(const ToolPath &toolpath, const Tool &tool)
{
	DexelTarget toolShape;
	toolShape.SetupTool(tool, GetSizeRX(), GetSizeRY());
	this->InitImprinting();
	this->HardInvert();
	Polygon3 temp;
	for(size_t i = 0; i < toolpath.positions.GetCount(); i++){
		temp.InsertPoint(toolpath.positions[i].X, toolpath.positions[i].Y,
				toolpath.positions[i].Z);
	}
	this->PolygonCutInTarget(temp, toolShape);
}

double DexelTarget::GetMinLevel(void)
{
	double d = FLT_MAX;
	for(size_t i = 0; i < N; i++)
		if(field[i].down < d) d = field[i].down;
	return d;
}

double DexelTarget::GetMaxUpsideLevel(int &x, int &y)
{
	double d = -FLT_MAX;
	x = -1;
	y = -1;
	for(size_t i = 0; i < N; i++)
		if(field[i].aboveDown > d){
			d = field[i].aboveDown;
			x = i % nx;
			y = floor(i / nx);
		}
	return d;
}

bool DexelTarget::IsInsideWorkingArea(int x, int y)
{
	if(x < 0 || x >= (int) nx) return false;
	if(y < 0 || y >= (int) ny) return false;
	size_t p = x + y * nx;

	if(field[p].aboveUp > -0.0001) return true;
	return false;

}

bool DexelTarget::HadBeenCut(int x, int y)
{
	if(x < 0 || x >= (int) nx) return false;
	if(y < 0 || y >= (int) ny) return false;
	size_t p = x + y * nx;

	//Outside working area ?
	if(field[p].aboveUp < -0.0001) return false;

	//On border uncut?
	if(field[p].aboveUp > -0.0) return false;

	//Material left?
	if(field[p].belowDown > 0.0) return false;

	return true;
}

bool DexelTarget::HasToBeCut(int x, int y)
{
	if(x < 0 || x >= (int) nx) return false;
	if(y < 0 || y >= (int) ny) return false;
	size_t p = x + y * nx;
	if(field[p].belowDown > 0.0001) return true;
	if(field[p].aboveUp > 0.0001) return true;
	return false;
}

int DexelTarget::NextDir(int sx, int sy, int olddir)
{
	int d = (olddir + 3) % 8;

	for(uint_fast8_t c = 0; c < 8; c++){
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

	for(uint_fast8_t c = 0; c < 8; c++){
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

const Polygon25 DexelTarget::GeneratePolygon(int stx, int sty)
{
	Polygon25 temp;

	while(!IsVisible(stx + 1, sty)){
		stx++;
		if(stx + 2 >= (int) nx){
			stx = -1;
			sty++;
			if(sty >= (int) ny) break;
		}
	}

	temp.Close();
	if(sty == (int) ny) return temp;

	int x = stx;
	int y = sty;
	int dir = 4;
	double z = -1.0;

	do{
		temp.InsertPoint((((double) x) + 0.5) * rx, (((double) y) + 0.5) * ry,
				z);
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

//On the inside
const Polygon25 DexelTarget::GeneratePolygon(int stx, int sty, double height)
{
	Polygon25 temp;

	while(!IsFilledAbove(stx + 1, sty, height)){
		stx++;
		if(stx + 2 >= (int) nx){
			stx = -1;
			sty++;
			if(sty >= (int) ny) break;
		}
	}

	temp.Close();
	if(sty == (int) ny) return temp;
	stx++;
	int x = stx;
	int y = sty;
	int dir = 0;

	// Return, if only a single pixel was found.
	if(IsStandAlone(x + y * nx, height)){
		temp.InsertPoint((((double) x) + 0.5) * rx, (((double) y) + 0.5) * ry,
				height);
		return temp;
	}

	do{

		temp.InsertPoint((((double) x) + 0.5) * rx, (((double) y) + 0.5) * ry,
				height);
		dir = NextDir(x, y, height, dir);

		if(dir == -1){
			wxLogError(_T("DexelTarget::GeneratePolygon: Lost wall contact!"));
			DocumentField(x, y, height);
			this->field[x + y * nx].up = -0.0001;
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

	temp2.InsertPoint(((double) right[first] + 0.5) * this->rx,
			((double) first + 0.5) * this->ry, 0.0);

	double d, dmax;

	i = first;
	temp1.InsertPoint(((double) left[i] + 0.5) * this->rx,
			((double) i + 0.5) * this->ry, 0.0);
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
		temp1.InsertPoint(((double) left[i] + 0.5) * this->rx,
				((double) i + 0.5) * this->ry, 0.0);
	}

	i = first;
	temp2.InsertPoint(((double) right[i] + 0.5) * this->rx,
			((double) i + 0.5) * this->ry, 0.0);
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
		temp2.InsertPoint(((double) right[i] + 0.5) * this->rx,
				((double) i + 0.5) * this->ry, 0.0);
	}

	temp1.Reverse();
	temp1 += temp2;
	temp1.RemoveZeroLength();

	delete[] left;
	delete[] right;

	return temp1;
}

void DexelTarget::GenerateDistanceMap(double height, bool invert)
{
	for(size_t i = 0; i < N; i++){
		field[i].aboveUp = 0;
		field[i].aboveDown = sz;
		field[i].belowUp = sz;
		field[i].belowDown = 0;
	}
	if(invert){
		for(size_t i = 0; i < N; i++){
			if(field[i].down > height){
				field[i].aboveDown = 0.000;
			}else{
				field[i].aboveDown = -1.000;
			}
		}
	}else{
		for(size_t i = 0; i < N; i++){
			if(field[i].up > height){
				field[i].aboveDown = 0.000;
			}else{
				field[i].aboveDown = -1.000;
			}
		}
	}

	for(size_t i = 0; i < N; i++){
		if(field[i].aboveDown < -0.5) // = inside of area
				{
			field[i].belowDown = height - 0.0005;
			field[i].aboveUp = 0.000;
		}else{
			field[i].belowDown = -0.001;
			field[i].aboveUp = -0.001;
		}
	}

	const double r2 = sqrt(rx * rx + ry * ry);

	bool flag = true;
	bool firstRound = true;

	while(flag){
		flag = false;
		for(size_t i = 0; i < N; i++)
			field[i].belowUp = field[i].aboveDown;
		for(size_t i = 0; i < N; i++){
			if(!IsOnOuterBorder(i)){
				if(field[i].belowUp < -0.5){
					double d = FLT_MAX;

					if(field[i + 1].belowUp > -0.5
							&& field[i + 1].belowUp + rx < d) d =
							field[i + 1].belowUp + rx;
					if(field[i - 1].belowUp > -0.5
							&& field[i - 1].belowUp + rx < d) d =
							field[i - 1].belowUp + rx;
					if(field[i + nx].belowUp > -0.5
							&& field[i + nx].belowUp + ry < d) d =
							field[i + nx].belowUp + ry;
					if(field[i - nx].belowUp > -0.5
							&& field[i - nx].belowUp + ry < d) d =
							field[i - nx].belowUp + ry;

					//					if(field[i + nx + 1].belowUp > -0.5 && field[i
					//							+ nx + 1].belowUp + r2 < d) d = field[i
					//							+ nx + 1].belowUp + r2;
					//					if(field[i + nx - 1].belowUp > -0.5 && field[i
					//							+ nx - 1].belowUp + r2 < d) d = field[i
					//							+ nx - 1].belowUp + r2;
					//					if(field[i - nx + 1].belowUp > -0.5 && field[i
					//							- nx + 1].belowUp + r2 < d) d = field[i
					//							- nx + 1].belowUp + r2;
					//					if(field[i - nx - 1].belowUp > -0.5 && field[i
					//							- nx - 1].belowUp + r2 < d) d = field[i
					//							- nx - 1].belowUp + r2;

					if(d < 1000.0){
						field[i].aboveDown = d;
						flag = true;
					}

					// Mark outline in aboveUp
					if(firstRound){
						if(d < 1000.0){
							field[i].aboveUp = height;
						}
					}

				}
			}
		}
		firstRound = false;

	}

	for(size_t i = 0; i < N; i++)
		field[i].aboveDown += sz;

}

void DexelTarget::FoldLowerDistance(int x, int y, const DexelTarget &b)
{
	size_t ib, jb, pb, ph;
	size_t cx, cy;
	cx = b.nx / 2;
	cy = b.ny / 2;

	if(x >= 0 && x < nx && y >= 0 && y < ny){
		ph = x + nx * y;
		if(field[ph].aboveUp > 0.0001){
			field[ph].aboveUp = 0.0;
		}
	}
	pb = 0;
	for(jb = 0; jb < b.ny; jb++){
		for(ib = 0; ib < b.nx; ib++){
			if(b.field[pb].IsVisible()){
				if(ib + x >= cx && ib + x < nx + cx && jb + y >= cy
						&& jb + y < ny + cy){
					ph = x + ib - cx + (y + jb - cy) * nx;

					if(field[ph].belowDown > 0.0001){
						field[ph].belowDown = 0.0;
					}
				}
			}
			pb++;
		}
	}
}

void DexelTarget::RaiseDistanceMap(double height, bool invert)
{
	if(invert){
		for(size_t i = 0; i < N; i++){
			if(field[i].down > height){
				field[i].aboveDown = 0.000;
			}else{
				field[i].aboveDown = -1.000;
			}
		}
	}else{
		for(size_t i = 0; i < N; i++){
			if(field[i].up > height){
				field[i].aboveDown = 0.000;
			}else{
				field[i].aboveDown = -1.000;
			}
		}
	}

	for(size_t i = 0; i < N; i++){
		if(field[i].aboveDown < -0.5) // = inside of area
				{
			if(field[i].belowDown < 0.0) field[i].belowDown = height - 0.0005;
			field[i].aboveUp = 0.000;
		}
	}
	for(size_t i = 0; i < N; i++){
		if(!IsOnOuterBorder(i)){
			if(field[i].aboveDown < -0.5){
				bool flag = false;
				if(field[i + 1].aboveDown > -0.5) flag = true;
				if(field[i - 1].aboveDown > -0.5) flag = true;
				if(field[i + nx].aboveDown > -0.5) flag = true;
				if(field[i - nx].aboveDown > -0.5) flag = true;

				// Mark outline in aboveUp
				if(flag && field[i].belowDown > 0.0){
					field[i].aboveUp = height;
				}
			}
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
			if(field[p].belowDown > 0.0001 || field[p].aboveUp > 0.0001){
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

	while(true){

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

	const double rx2 = rx / 2;
	const double ry2 = ry / 2;

	temp.InsertPoint((double) x * rx + rx2, (double) y * ry + ry2, 0.002);

	if(!HasToBeCut(x, y)){
		wxLogMessage(_T("FindCut::Test started in a place not to be cut!"));
		return temp;
	}

	char dir = 0;
	while(true){
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
void DexelTarget::PolygonCutInTarget(Polygon3 &polygon, DexelTarget &tool)
{
	if(polygon.GetCount() == 0) return;
	int px = floor(polygon.elements[0].x / rx);
	int py = floor(polygon.elements[0].y / ry);
	double pz = polygon.elements[0].z;
	this->ShiftDown(px, py, pz, tool);
	if(polygon.GetCount() == 1) return;
	for(size_t i = 1; i < polygon.elements.GetCount(); i++){
		const double dx = polygon.elements[i].x - polygon.elements[i - 1].x;
		const double dy = polygon.elements[i].y - polygon.elements[i - 1].y;
		const double dz = polygon.elements[i].z - polygon.elements[i - 1].z;
		const int nx = abs(floor(polygon.elements[i].x / rx) - px);
		const int ny = abs(floor(polygon.elements[i].y / ry) - py);
		if(nx > ny){
			const double rz = dz / (double) nx;
			const int cx = dx >= 0? 1 : -1;
			const int cy = dy >= 0? 1 : -1;
			int b = 0;
			for(size_t n = 0; n < nx; n++){
				px += cx;
				b += ny;
				if(b > nx){
					b -= nx;
					py += cy;
				}
				pz += rz;
				this->ShiftDown(px, py, pz, tool);
			}

		}else{
			const double rz = dz / (double) ny;
			const int cx = dx >= 0? 1 : -1;
			const int cy = dy >= 0? 1 : -1;
			int b = 0;
			for(size_t n = 0; n < ny; n++){
				py += cy;
				b += nx;
				if(b > ny){
					b -= ny;
					px += cx;
				}
				pz += rz;
				this->ShiftDown(px, py, pz, tool);
			}
		}
		px = floor(polygon.elements[i].x / rx);
		py = floor(polygon.elements[i].y / ry);
		pz = polygon.elements[i].z;
	}
}

void DexelTarget::PolygonPunchThroughTarget(Polygon3& polygon, double level,
		DexelTarget& tool)
{
	for(size_t i = 0; i < polygon.elements.GetCount(); i++){
		this->TouchErase(round(polygon.elements[i].x / rx - 0.5),
				round(polygon.elements[i].y / ry - 0.5), polygon.elements[i].z,
				level, tool);
	}
}

void DexelTarget::PolygonDropOntoTarget(Polygon3 &polygon, double level)
{
	for(size_t i = 0; i < polygon.elements.GetCount(); i++){
		const double d = this->GetLevel(polygon.elements[i].x,
				polygon.elements[i].y);
		if(d < level){
			polygon.elements[i].z = level;
		}else{
			polygon.elements[i].z = d;
		}
	}
}

void DexelTarget::VectorDropOntoTarget(double &x, double &y, double &z,
		double level)
{
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
		//TODO: Change this to a Bresenham algorithm.
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
			this->field[p + j].down = 0.0;
			this->field[p + j].up = this->sz;
		}
		for(j = right[i]; j < this->nx; j++){
			this->field[p + j].down = 0.0;
			this->field[p + j].up = this->sz;
		}
		p += this->nx;
	}
	delete[] left;
	delete[] right;
}

void DexelTarget::MarkOutline(void)
{
	for(size_t n = 0; n < N; n++){
		if(IsOnOuterBorder(n)){
			field[n].up = sz;
			field[n].down = 0.0;
		}
	}
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

//Moves inside the matrial clockwise
//Moves inside the material to be cut counter-clockwise
