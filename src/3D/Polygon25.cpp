///////////////////////////////////////////////////////////////////////////////
// Name               : Polygon25.cpp
// Purpose            : Contains a 2.5D polygon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.07.2011
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

#include "Polygon25.h"

#include <wx/log.h>
#include <wx/arrimpl.cpp>
#include <GL/gl.h>
#include <float.h>

WX_DEFINE_OBJARRAY(ArrayOfPolygon25)

Polygon25::Polygon25()
{
}

Polygon25::~Polygon25()
{
}

double Polygon25::GetLengthXY(void) const
{
	if(elements.GetCount() <= 1) return 0.0;
	double d = 0.0;
	size_t i;
	Vector3 temp, temp2;

	temp = elements[0];
	for(i = 1; i < elements.GetCount(); i++){
		temp2 = temp - elements[i];
		temp2.z = 0;
		d += temp2.Abs();
		temp = elements[i];
	}
	if(isClosed){
		temp2 = temp - elements[0];
		temp2.z = 0;
		d += temp2.Abs();
	}
	return d;
}

void Polygon25::PolygonFillHoles(void)
{
	//TODO: This is crude! Find a better way.
	size_t i;
	size_t nrp;
	double m;
	m = 0.0;
	nrp = 0;
	for(i = 0; i < elements.GetCount(); i++){
		if(elements[i].z > -0.5){
			nrp++;
			m += elements[i].z;
		}
	}
	if(nrp == 0) return;
	m /= (double) nrp;
	for(i = 0; i < elements.GetCount(); i++){
		if(elements[i].z < -0.5){
			elements[i].z = m;
		}
	}
}

void Polygon25::PolygonSmooth(void)
{
	size_t i;
	Vector3 d;
	ArrayOfVector3 temp;
	temp = elements;

	for(i = 0; i < elements.GetCount(); i++){
		if(i > 0)
			d = elements[i - 1];
		else
			d = elements[elements.GetCount() - 1];
		d += elements[i];
		if(i + 1 < elements.GetCount())
			d += elements[i + 1];
		else
			d += elements[0];
		temp[i] = d / 3;
	}
	elements = temp;
}

void Polygon25::PolygonExpand(double r)
{
	if(elements.GetCount() < 2) return;
	size_t i;
	Vector3 o, n, d;
	o = elements[0];
	for(i = 1; i < elements.GetCount(); i++){
		n = elements[i];
		o = n - o;
		o.Normalize();
		d.x = o.y;
		d.y = -o.x;
		d.z = o.z;
		o = n;
		elements[i] = n + d * r;
	}
}

void Polygon25::PolygonDiminish(double r)
{
	this->PolygonExpand(-r);
}

bool Polygon25::IsElementInside(const Vector3 v)
{
	size_t i, j;

	bool flagTryY = false;
	size_t c = 0;

	for(i = 0; i < elements.GetCount(); i++){
		if(i < elements.GetCount() - 1)
			j = i + 1;
		else
			j = 0;
		// Test if line i-j is on v->X-Infty
		if(elements[i].y == v.y && elements[j].y == v.y){
			flagTryY = true;
			break;
		}
		if((elements[i].y <= v.y && elements[j].y >= v.y)
				|| (elements[i].y >= v.y && elements[j].y <= v.y)){
			double px = ((elements[j].x - elements[i].x) * v.y
					+ elements[i].x * elements[j].y
					- elements[i].y * elements[j].x)
					/ (elements[j].y - elements[i].y);
			if(px > v.x) c++;
		}
	}

	if(flagTryY){
		c = 0;
		for(i = 0; i < elements.GetCount(); i++){
			if(i < elements.GetCount() - 1)
				j = i + 1;
			else
				j = 0;
			// Test if line i-j is on v->Y-Infty
			if(elements[i].x == v.x && elements[j].x == v.x){
				return false;
			}
			if((elements[i].x <= v.x && elements[j].x >= v.x)
					|| (elements[i].x >= v.x && elements[j].x <= v.x)){
				double py = ((elements[j].y - elements[i].y) * v.x
						- elements[i].x * elements[j].y
						+ elements[i].y * elements[j].x)
						/ (elements[j].x - elements[i].x);
				if(py > v.y) c++;
			}
		}
	}
	if((c % 2) == 1) return true;
	return false;
}

double Polygon25::DistanceToElement(const size_t elementInPolygon,
		const double x, const double y, const double vx, const double vy) const
{
	double qx, qy, px, py;
	px = elements[elementInPolygon].x;
	py = elements[elementInPolygon].y;
	if(elementInPolygon + 1 == elements.GetCount()){
		qx = elements[0].x;
		qy = elements[0].y;
	}else{
		qx = elements[elementInPolygon + 1].x;
		qy = elements[elementInPolygon + 1].y;
	}

	// From axiom code:
	//	x1 := px+(qx-px)*r
	//	y1 := py+(qy-py)*r
	//	x2 := x+vx*s
	//	y2 := y+vy*s
	//	solve([x1=x2,y1=y2],[r,s])

	double denom = (qx - px) * vy + (-qy + py) * vx;
	if(denom == 0.0) return DBL_MAX;
	double r = (-vx * y + vy * x - px * vy + py * vx) / denom;
	double s = ((-qx + px) * y + (qy - py) * x - px * qy + py * qx) / denom;

	if((r < 0.0) || (r > 1.0)) return DBL_MAX;
	return s;
}

double Polygon25::DistanceToPolygon(const Polygon25 &polygon, double vx,
		double vy) const
{
	//TODO: Make this faster!
	size_t i, j;
	double dmin = DBL_MAX;
	double d;
	size_t n = polygon.elements.GetCount();
	if(!polygon.isClosed && (n > 0)) n--;
	for(i = 0; i < n; i++){
		//		wxLogMessage(wxString::Format(_T("to element %u."),i));
		for(j = 0; j < this->elements.GetCount(); j++){
			d = polygon.DistanceToElement(i, elements[j].x, elements[j].y, vx,
					vy);
			if(d < dmin) dmin = d;
		}
	}
	return dmin;
}

void Polygon25::RotatePolygonStart(double x, double y)
{

	if(elements.GetCount() == 0) return;

	size_t i;
	Vector3 t;
	double d;
	double dmin = DBL_MAX;
	size_t n = elements.GetCount();

	// Find element with minimal distance to (x,y)
	size_t nshift = 0;
	for(i = 0; i < n; i++){
		t = elements[i];
		d = (t.x - x) * (t.x - x) + (t.y - y) * (t.y - y);
		if(d < dmin){
			dmin = d;
			nshift = i;
		}
	}

	// Shift by -nshift (so nshift becomes 0)
	//	nshift = n - nshift;
	size_t j;
	ArrayOfVector3 temp;
	for(i = 0; i < n; i++){
		j = (i + nshift) % n;
		temp.Add(elements[j]);
	}
	elements = temp;
}
