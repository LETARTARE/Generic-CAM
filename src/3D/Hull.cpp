///////////////////////////////////////////////////////////////////////////////
// Name               : Hull.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.06.2011
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

#include "Hull.h"

#include <GL/gl.h>
#include <wx/log.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfHullEdge);
WX_DEFINE_OBJARRAY(ArrayOfHullTriangle);
WX_DEFINE_OBJARRAY(ArrayOfHull);

HullEdge::HullEdge()
{
	n.Set(0, 0, 1);
}

HullEdge::~HullEdge()
{
}

HullTriangle::HullTriangle()
{
	n.Set(0, 0, 1);
}

HullTriangle::~HullTriangle()
{
}

Hull::Hull()
{
	visible = true;
	paintTriangles = false;
	paintEdges = true;
	paintVertices = true;

}

Hull::~Hull()
{
}

void Hull::Clear(void)
{
	v.Clear();
	e.Clear();
	t.Clear();
}

void Hull::Paint(void) const
{
	size_t i;
	if(!visible) return;

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	if(paintTriangles){
		::glBegin(GL_TRIANGLES);
		::glColor3f(color.x, color.y, color.z);
		for(i = 0; i < t.GetCount(); i++){
			glNormal3f(t[i].n.x, t[i].n.y, t[i].n.z);
			glVertex3f(v[t[i].va].x, v[t[i].va].y, v[t[i].va].z);
			glVertex3f(v[t[i].vb].x, v[t[i].vb].y, v[t[i].vb].z);
			glVertex3f(v[t[i].vc].x, v[t[i].vc].y, v[t[i].vc].z);
		}
		::glEnd();
	}

	if(paintEdges){

		::glBegin(GL_LINES);
		::glColor3f(color.x / 2, color.y / 2, color.z / 2);
		for(i = 0; i < e.GetCount(); i++){
			glNormal3f(e[i].n.x, e[i].n.y, e[i].n.z);
			glVertex3f(v[e[i].va].x, v[e[i].va].y, v[e[i].va].z);
			glVertex3f(v[e[i].vb].x, v[e[i].vb].y, v[e[i].vb].z);
		}
		::glEnd();
	}

	if(paintVertices){

		::glBegin(GL_POINTS);
		::glColor3f(color.x * 2, color.y * 2, color.z * 2);
		//::glNormal3f(0.0, 0.0, 1.0);
		for(i = 0; i < v.GetCount(); i++){
			glVertex3f(v[i].x, v[i].y, v[i].z);
		}
		::glEnd();
	}
	::glPopMatrix();
}

void Hull::CopyFrom(const Geometry &geometry)
{
	Clear();
	CopyTrianglesFrom(geometry);
	this->matrix = geometry.matrix;
	this->objectName = geometry.name;
	this->visible = geometry.visible;
	this->color = geometry.color;
	wxLogMessage(wxString::Format(_T("V: %u E: %u T: %u"), v.GetCount(),
			e.GetCount(), t.GetCount()));
}

void Hull::CopyTrianglesFrom(const Geometry &geometry)
{
	size_t i;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		AddTriangleWithNormals(geometry.triangles[i].p[0],
				geometry.triangles[i].p[1], geometry.triangles[i].p[2],
				geometry.triangles[i].n[0], geometry.triangles[i].n[1],
				geometry.triangles[i].n[2]);
	}
}

void Hull::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	for(i = 0; i < v.GetCount(); i++){
		v[i] = matrix.Transform(v[i]);
	}
	for(i = 0; i < e.GetCount(); i++){
		e[i].n = matrix.TransformNoShift(e[i].n);
	}
	for(i = 0; i < t.GetCount(); i++){
		t[i].n = matrix.TransformNoShift(t[i].n);
	}
}
void Hull::ApplyTransformation(void)
{
	size_t i;
	for(i = 0; i < v.GetCount(); i++){
		v[i] = this->matrix.Transform(v[i]);
	}
	for(i = 0; i < e.GetCount(); i++){
		e[i].n = this->matrix.TransformNoShift(e[i].n);
	}
	for(i = 0; i < t.GetCount(); i++){
		t[i].n = this->matrix.TransformNoShift(t[i].n);
	}
}

double Hull::DiffSquareAndAdd(const Vector3 &a, const Vector3 &b)
{
	double t1 = a.x - b.x;
	double t2 = a.y - b.y;
	double t3 = a.z - b.z;
	return t1 * t1 + t2 * t2 + t3 * t3;
}

size_t Hull::AddTriangle(const Vector3 &a, const Vector3 &b,
		const Vector3 &c)
{
	size_t i;

	size_t nva, nvb, nvc;
	size_t nea, neb, nec;
	size_t nt;

	bool xva = false;
	bool xvb = false;
	bool xvc = false;
	bool xea = false;
	bool xeb = false;
	bool xec = false;
	bool xt = false;

	double epsilon = 0.0001;
	double epsilon2 = epsilon * epsilon;

	HullEdge tempe;
	HullTriangle tempt;

	for(i = 0; i < v.GetCount(); i++){
		if(DiffSquareAndAdd(v[i], a) <= epsilon2){
			nva = i;
			xva = true;
			break;
		}
	}
	if(!xva){
		v.Add(a);
		nva = v.GetCount() - 1;
	}

	for(i = 0; i < v.GetCount(); i++){
		if(DiffSquareAndAdd(v[i], b) <= epsilon2){
			nvb = i;
			xvb = true;
			break;
		}
	}
	if(!xvb){
		v.Add(b);
		nvb = v.GetCount() - 1;
	}

	for(i = 0; i < v.GetCount(); i++){
		if(DiffSquareAndAdd(v[i], c) <= epsilon2){
			nvc = i;
			xvc = true;
			break;
		}
	}
	if(!xvc){
		v.Add(c);
		nvc = v.GetCount() - 1;
	}

	for(i = 0; i < e.GetCount(); i++){
		if((e[i].va == nva && e[i].vb == nvb) || (e[i].va == nvb && e[i].vb
				== nva)){
			nea = i;
			xea = true;
			break;
		}
	}
	if(!xea){
		tempe.va = nva;
		tempe.vb = nvb;
		e.Add(tempe);
		nea = e.GetCount() - 1;
	}

	for(i = 0; i < e.GetCount(); i++){
		if((e[i].va == nvb && e[i].vb == nvc) || (e[i].va == nvc && e[i].vb
				== nvb)){
			neb = i;
			xeb = true;
			break;
		}
	}
	if(!xeb){
		tempe.va = nvb;
		tempe.vb = nvc;
		e.Add(tempe);
		neb = e.GetCount() - 1;
	}

	for(i = 0; i < e.GetCount(); i++){
		if((e[i].va == nvc && e[i].vb == nva) || (e[i].va == nva && e[i].vb
				== nvc)){
			nec = i;
			xec = true;
			break;
		}
	}
	if(!xec){
		tempe.va = nvc;
		tempe.vb = nva;
		e.Add(tempe);
		nec = e.GetCount() - 1;
	}
	for(i = 0; i < t.GetCount(); i++){
		if((t[i].va == nva && t[i].vb == nvb && t[i].vc == nvc) || (t[i].va
				== nva && t[i].vb == nvc && t[i].vc == nvb) || (t[i].va == nvb
				&& t[i].vb == nvc && t[i].vc == nva) || (t[i].va == nvb
				&& t[i].vb == nva && t[i].vc == nvc) || (t[i].va == nvc
				&& t[i].vb == nva && t[i].vc == nvb) || (t[i].va == nvc
				&& t[i].vb == nvb && t[i].vc == nva)){
			nt = i;
			xt = true;
			break;
		}
	}
	if(!xt){
		tempt.va = nva;
		tempt.vb = nvb;
		tempt.vc = nvc;
		tempt.ea = nea;
		tempt.eb = neb;
		tempt.ec = nec;

		t.Add(tempt);
		nt = t.GetCount() - 1;
	}
	return nt;
}

size_t Hull::AddTriangleTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const AffineTransformMatrix &transformMatrix)
{
	size_t nt = AddTriangle(matrix.Transform(a), matrix.Transform(b),
			matrix.Transform(c));
	return nt;
}
size_t Hull::AddTriangleWithNormals(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &na, const Vector3 &nb,
		const Vector3 &nc)
{
	size_t nt = AddTriangle(a, b, c);
	t[nt].n = (na + nb + nc) / 3;
	return nt;
}
size_t Hull::AddTriangleWithNormal(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &n)
{
	size_t nt = AddTriangle(a, b, c);
	t[nt].n = n;
	return nt;
}

void Hull::AddQuad(const Vector3 &a, const Vector3 &b, const Vector3 &c,
		const Vector3 &d)
{
	AddTriangle(a, b, c);
	AddTriangle(a, c, d);
}
void Hull::AddQuadTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &d,
		const AffineTransformMatrix &transformMatrix)
{
	AddTriangle(matrix.Transform(a), matrix.Transform(b), matrix.Transform(c));
	AddTriangle(matrix.Transform(a), matrix.Transform(c), matrix.Transform(d));
}

void Hull::CalcNormals(void)
{
	size_t i;
	Vector3 temp;

	for(i = 0; i < t.GetCount(); i++){
		temp = (v[t[i].vb] - v[t[i].va]) * (v[t[i].vc] - v[t[i].vb]);
		temp.Normalize();
		t[i].n = temp;
	}
}

