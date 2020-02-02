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

#include <float.h>
#include <stdint.h>
#include "OpenGL.h"

Polygon25::Polygon25()
{
}

Polygon25::~Polygon25()
{
}

double Polygon25::GetLengthXY(void) const
{
	if(elements.size() <= 1) return 0.0;
	double d = 0.0;
	size_t i;
	Vector3 temp, temp2;

	temp = elements[0];
	for(i = 1; i < elements.size(); i++){
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
	for(i = 0; i < elements.size(); i++){
		if(elements[i].z > -0.5){
			nrp++;
			m += elements[i].z;
		}
	}
	if(nrp == 0) return;
	m /= (double) nrp;
	for(i = 0; i < elements.size(); i++){
		if(elements[i].z < -0.5){
			elements[i].z = m;
		}
	}
}

void Polygon25::PolygonSmooth(void)
{
	std::vector <Vector3> temp = elements;

	for(size_t i = 0; i < elements.size(); i++){
		Vector3 d;
		if(i == 0)
			d = elements[elements.size() - 1];
		else
			d = elements[i - 1];
		d += elements[i];
		if(i + 1 < elements.size())
			d += elements[i + 1];
		else
			d += elements[0];
		temp[i] = d / 3;
	}
	elements = temp;
}

void Polygon25::PolygonExpand(double r)
{
	if(elements.size() < 2) return;
	size_t i;
	Vector3 o, n, d;
	o = elements[0];
	for(i = 1; i < elements.size(); i++){
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

bool Polygon25::IsElementInside(const Vector3 &v) const
{
	// Using the Jordan Polygon Theorem

	int_fast8_t c = 1;
	size_t E = elements.size();
	for(size_t i = 0; i < E; i++){
		Vector3 p0 = elements[i];
		Vector3 p1;
		if(i + 1 == E)
			p1 = elements[0];
		else
			p1 = elements[i + 1];
		if(v.y == p0.y && v.y == p1.y){
			if((p0.x <= v.x && v.x <= p1.x) || (p0.x >= v.x && v.x >= p1.x)){
				c = 0;
				break;
			}
			continue;
		}
		if(p0.y > p1.y){
			float h = p0.x;
			p0.x = p1.x;
			p1.x = h;
			h = p0.y;
			p0.y = p1.y;
			p1.y = h;
		}
		if(v.x == p0.x && v.y == p0.y){
			c = 0;
			break;
		}
		if(v.y <= p0.y || v.y > p1.y) continue;
		const float delta = (p0.x - v.x) * (p1.y - v.y)
				- (p0.y - v.y) * (p1.x - v.x);
		if(delta > 0){
			c = -c;
			continue;
		}
		if(delta < 0) continue;
		c = 0;
		break;
	}
	if(c <= 0) return true;
	return false;
}

bool Polygon25::IsPolygonInside(const Polygon25& other) const
{
	for(size_t i = 0; i < other.elements.size(); i++){
		if(!IsElementInside(other.elements[i])){
			return false;
		}
	}
	return true;
}

void Polygon25::SortPolygonsFromOutside(std::vector <Polygon25> *array)
{
	const int N = array->size();
	if(N == 0) return;
	std::vector <Polygon25> temp;
	temp.push_back(array->operator [](0));
	for(int i = 1; i < N; i++){
		int pos = -1;
		const int M = temp.size();
		for(int j = M; j > 0; j--){
			if(temp[j - 1].IsPolygonInside(array->operator [](i))){
				pos = j - 1;
				break;
			}
		}
		if(pos == -1) temp.insert(temp.begin(), array->operator [](i));
		if(pos >= 0 && pos < M - 1) temp.insert(temp.begin() + pos + 1,
				array->operator [](i));
		if(pos >= M - 1) temp.push_back(array->operator [](i));
	}
	*array = temp;
}

double Polygon25::DistanceToElement(const size_t elementInPolygon,
		const double x, const double y, const double vx, const double vy) const
{
	double qx, qy, px, py;
	px = elements[elementInPolygon].x;
	py = elements[elementInPolygon].y;
	if(elementInPolygon + 1 == elements.size()){
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
	size_t n = polygon.elements.size();
	if(!polygon.isClosed && (n > 0)) n--;
	for(i = 0; i < n; i++){
		//		wxLogMessage(wxString::Format(_T("to element %u."),i));
		for(j = 0; j < this->elements.size(); j++){
			d = polygon.DistanceToElement(i, elements[j].x, elements[j].y, vx,
					vy);
			if(d < dmin) dmin = d;
		}
	}
	return dmin;
}

void Polygon25::RotatePolygonStart(double x, double y)
{

	if(elements.size() == 0) return;

	size_t i;
	Vector3 t;
	double d;
	double dmin = DBL_MAX;
	size_t n = elements.size();

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
	std::vector <Vector3> temp;
	for(i = 0; i < n; i++){
		j = (i + nshift) % n;
		temp.push_back(elements[j]);
	}
	elements = temp;
}
