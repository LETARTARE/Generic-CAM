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
#include <algorithm>
#include <stdexcept>

#include "Geometry.h"
#include "Polygon3.h"
#include "Triangle.h"

Hull::Edge::Edge()
{
	va = 0;
	vb = 0;
	ta = 0;
	tb = 0;
	trianglecount = 0;
}

size_t Hull::Edge::OtherTriangle(size_t n)
{
	if(ta == n) return tb;
	return ta;
}

Hull::Triangle::Triangle()
{
	va = 0;
	vb = 0;
	vc = 0;
	ea = 0;
	eb = 0;
	ec = 0;
}

int Hull::Triangle::Direction(size_t i1, size_t i2)
{
	if((i1 == va && i2 == vb) || (i1 == vb && i2 == vc)
			|| (i1 == vc && i2 == va)) return 1;
	if((i1 == vb && i2 == va) || (i1 == vc && i2 == vb)
			|| (i1 == va && i2 == vc)) return -1;
	return 0;
}

Hull::Hull()
{
	SetEpsilon(1e-6); // 1 um
	paintTriangles = false;
	paintEdges = true;
	paintVertices = false;
	paintNormals = false;
	smooth = true;
	paintSelected = true;
}

Hull::~Hull()
{
}

void Hull::Clear(void)
{
	v.clear();
	e.clear();
	t.clear();
	openedges.clear();
	openvertices.clear();
	selected.clear();
}

void Hull::SetEpsilon(double newEpsilon)
{
	epsilon = newEpsilon;
	epsilon2 = newEpsilon * newEpsilon;
}

void Hull::Paint(void) const
{
	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	const double normalscale = 0.1;

	if(paintTriangles){
		::glBegin(GL_TRIANGLES);
		if(smooth){
			for(size_t i = 0; i < t.size(); ++i){
				glNormal3f(vn[t[i].va].x, vn[t[i].va].y, vn[t[i].va].z);
				glVertex3f(v[t[i].va].x, v[t[i].va].y, v[t[i].va].z);
				glNormal3f(vn[t[i].vb].x, vn[t[i].vb].y, vn[t[i].vb].z);
				glVertex3f(v[t[i].vb].x, v[t[i].vb].y, v[t[i].vb].z);
				glNormal3f(vn[t[i].vc].x, vn[t[i].vc].y, vn[t[i].vc].z);
				glVertex3f(v[t[i].vc].x, v[t[i].vc].y, v[t[i].vc].z);
			}
		}else{
			for(size_t i = 0; i < t.size(); ++i){
				glNormal3f(t[i].n.x, t[i].n.y, t[i].n.z);
				glVertex3f(v[t[i].va].x, v[t[i].va].y, v[t[i].va].z);
				glVertex3f(v[t[i].vb].x, v[t[i].vb].y, v[t[i].vb].z);
				glVertex3f(v[t[i].vc].x, v[t[i].vc].y, v[t[i].vc].z);
			}
		}
		::glEnd();
		if(paintNormals){

			glBegin(GL_LINES);
			for(size_t i = 0; i < t.size(); ++i){
				glNormal3f(t[i].n.x, t[i].n.y, t[i].n.z);
				const Vector3 center = (v[t[i].va] + v[t[i].vb] + v[t[i].vc])
						/ 3;
				glVertex3f(center.x, center.y, center.z);
				glVertex3f(center.x + t[i].n.x * normalscale,
						center.y + t[i].n.y * normalscale,
						center.z + t[i].n.z * normalscale);
			}
			glEnd();
		}
	}
	if(paintEdges){
		::glBegin(GL_LINES);
		if(smooth){
			for(size_t i = 0; i < e.size(); ++i){
				glNormal3f(vn[e[i].va].x, vn[e[i].va].y, vn[e[i].va].z);
				glVertex3f(v[e[i].va].x, v[e[i].va].y, v[e[i].va].z);
				glNormal3f(vn[e[i].vb].x, vn[e[i].vb].y, vn[e[i].vb].z);
				glVertex3f(v[e[i].vb].x, v[e[i].vb].y, v[e[i].vb].z);
			}
		}else{
			for(size_t i = 0; i < e.size(); ++i){
				glNormal3f(e[i].n.x, e[i].n.y, e[i].n.z);
				glVertex3f(v[e[i].va].x, v[e[i].va].y, v[e[i].va].z);
				glVertex3f(v[e[i].vb].x, v[e[i].vb].y, v[e[i].vb].z);
			}
		}
		::glEnd();

		if(paintNormals){
			glBegin(GL_LINES);
			for(size_t i = 0; i < e.size(); ++i){
				glNormal3f(e[i].n.x, e[i].n.y, e[i].n.z);
				const Vector3 center = (v[e[i].va] + v[e[i].vb]) / 2;
				glVertex3f(center.x, center.y, center.z);
				glVertex3f(center.x + e[i].n.x * normalscale,
						center.y + e[i].n.y * normalscale,
						center.z + e[i].n.z * normalscale);
			}
			glEnd();
		}
	}

	if(paintVertices){
		::glBegin(GL_POINTS);
		for(size_t i = 0; i < v.size(); ++i){
			glNormal3f(vn[i].x, vn[i].y, vn[i].z);
			glVertex3f(v[i].x, v[i].y, v[i].z);
		}
		::glEnd();
		if(paintNormals){
			glBegin(GL_LINES);
			for(size_t i = 0; i < v.size(); ++i){
				glNormal3f(vn[i].x, vn[i].y, vn[i].z);
				glVertex3f(v[i].x, v[i].y, v[i].z);
				glVertex3f(v[i].x + vn[i].x * normalscale,
						v[i].y + vn[i].y * normalscale,
						v[i].z + vn[i].z * normalscale);
			}
			glEnd();
		}

	}

	if(paintSelected){
		::glPointSize(10);
		::glBegin(GL_POINTS);
		for(std::set <size_t>::iterator n = selected.begin();
				n != selected.end(); ++n){
			size_t i = *n;
			glNormal3f(vn[i].x, vn[i].y, vn[i].z);
			glVertex3f(v[i].x, v[i].y, v[i].z);
		}
		::glEnd();
		::glPointSize(1);
	}

	::glPopMatrix();
}

bool Hull::IsClosed(void) const
{
	return (openedges.empty() && openvertices.empty());
}

bool Hull::LoadObj(std::string filename)
{
	return false;
}

void Hull::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	std::transform(v.begin(), v.end(), v.begin(), matrix);

//	for(size_t i = 0; i < v.size(); i++)
//		v[i] = matrix.Transform(v[i]);

	for(size_t i = 0; i < vn.size(); i++)
		vn[i] = matrix.TransformNoShift(vn[i]);
	for(size_t i = 0; i < e.size(); i++)
		e[i].n = matrix.TransformNoShift(e[i].n);
	for(size_t i = 0; i < t.size(); i++)
		t[i].n = matrix.TransformNoShift(t[i].n);
}

void Hull::ApplyTransformation(void)
{
	std::transform(v.begin(), v.end(), v.begin(), matrix);
//	for(size_t i = 0; i < v.size(); i++)
//		v[i] = this->matrix.Transform(v[i]);
	for(size_t i = 0; i < vn.size(); i++)
		vn[i] = matrix.TransformNoShift(vn[i]);
	for(size_t i = 0; i < e.size(); i++)
		e[i].n = this->matrix.TransformNoShift(e[i].n);
	for(size_t i = 0; i < t.size(); i++)
		t[i].n = this->matrix.TransformNoShift(t[i].n);
}

void Hull::CopyFrom(const Geometry &geometry)
{
	Clear();
	CopyTrianglesFrom(geometry);
	this->matrix = geometry.matrix;
//	wxLogMessage(
//			wxString::Format(_T("V: %u E: %u T: %u"), v.size(),
//					e.size(), t.size()));
}

void Hull::CopyTrianglesFrom(const Geometry &geometry)
{
	for(size_t i = 0; i < geometry.triangles.size(); i++){
		AddTriangleWithNormals(geometry.triangles[i].p[0],
				geometry.triangles[i].p[1], geometry.triangles[i].p[2],
				geometry.triangles[i].n[0], geometry.triangles[i].n[1],
				geometry.triangles[i].n[2]);
	}
}

Vector3 Hull::GetCenter(void) const
{
	if(v.empty()) return Vector3();
	Vector3 temp;
	for(size_t i = 0; i < v.size(); ++i)
		temp += v[i];
	return (temp / v.size());
}

Vector3 Hull::PlaneProjection(const Vector3& a, const Vector3& b, Vector3 n,
		double d) const
{
	// Assume, that n is of length 1
	const double sa = n.Dot(a) - d;
	const double sb = n.Dot(b) - d;
	if(sa - sb == 0) return (a + b) / 2;
	return (b * sa - a * sb) / (sa - sb);
}

Polygon3 Hull::IntersectPlane(Vector3 n, double d)
{
	n.Normalize();

	// Find edges
	std::set <size_t> edges;
	for(size_t i = 0; i < e.size(); ++i){
		const Vector3 a = v[e[i].va];
		const Vector3 b = v[e[i].vb];
		const double da = a.Dot(n);
		const double db = b.Dot(n);
		if((da > d && db <= d) || (da <= d && db > d)) edges.insert(i);
	}

	Polygon3 temp;
	// No intersection found
	if(edges.empty()) return temp;
	size_t ne = *(edges.begin());
	size_t nt = e[ne].ta;
	int dir = t[nt].Direction(e[ne].va, e[ne].vb);
	if(dir == 0) throw(std::logic_error(
			"Hull:IntersectPlane - Wrong triangle selected."));
	if(dir == -1) nt = e[ne].tb;
	while(!edges.empty()){
		temp.InsertPoint(PlaneProjection(v[e[ne].va], v[e[ne].vb], n, d));
		edges.erase(ne);

		if(edges.find(t[nt].ea) != edges.end()){
			ne = t[nt].ea;
			nt = e[ne].OtherTriangle(nt);
			continue;
		}
		if(edges.find(t[nt].eb) != edges.end()){
			ne = t[nt].eb;
			nt = e[ne].OtherTriangle(nt);
			continue;
		}
		if(edges.find(t[nt].ec) != edges.end()){
			ne = t[nt].ec;
			nt = e[ne].OtherTriangle(nt);
			continue;
		}
		break;
	}

//	for(std::set <size_t>::iterator it = edges.begin(); it != edges.end();
//			++it){
//
//	}

	temp.Close();
	return temp;
}

void Hull::CalcNormals(void)
{
	Vector3 temp;
	for(size_t i = 0; i < t.size(); ++i){
		temp = (v[t[i].vb] - v[t[i].va]) * (v[t[i].vc] - v[t[i].vb]);
		temp.Normalize();
		t[i].n = temp;
	}
	for(size_t i = 0; i < vn.size(); ++i)
		vn[i].Zero();
	for(size_t i = 0; i < e.size(); ++i){
		if(e[i].trianglecount == 0) continue;
		temp = t[e[i].ta].n;
		if(e[i].trianglecount > 1) temp += t[e[i].tb].n;
		temp.Normalize();
		const size_t a = e[i].va;
		const size_t b = e[i].vb;
		e[i].n = temp;
		vn[a] += temp;
		vn[b] += temp;
	}
	for(size_t i = 0; i < vn.size(); ++i)
		vn[i].Normalize();
	for(size_t i = 0; i < e.size(); ++i){
		if(e[i].trianglecount != 0) continue;
		temp = vn[e[i].va] + vn[e[i].vb];
		temp.Normalize();
	}
}

void Hull::FlipNormals(void)
{
	for(size_t i = 0; i < t.size(); ++i)
		t[i].n = -t[i].n;
	for(size_t i = 0; i < vn.size(); ++i)
		vn[i] = -vn[i];
	for(size_t i = 0; i < e.size(); ++i)
		e[i].n = -e[i].n;
}

size_t Hull::FindVertex(const Vector3& x)
{
	// Search open vertices
	for(std::set <size_t>::iterator it = openvertices.begin();
			it != openvertices.end(); ++it){
		const size_t i = *it;
		const double t1 = v[i].x - x.x;
		const double t2 = v[i].y - x.y;
		const double t3 = v[i].z - x.z;
		if((t1 * t1 + t2 * t2 + t3 * t3) <= epsilon2) return i;
	}

	// Search all vertices
	for(size_t i = 0; i < v.size(); ++i){
		const double t1 = v[i].x - x.x;
		const double t2 = v[i].y - x.y;
		const double t3 = v[i].z - x.z;
		if((t1 * t1 + t2 * t2 + t3 * t3) <= epsilon2) return i;
	}

	// Create new vertex
	v.push_back(x);
	vn.push_back(x);
	size_t index = v.size() - 1;
	openvertices.insert(index);
	return index;
}

size_t Hull::FindEdge(const size_t indexa, const size_t indexb)
{
	// Search open edges
	for(std::set <size_t>::iterator it = openedges.begin();
			it != openedges.end(); ++it){
		const size_t i = *it;
		if((e[i].va == indexa && e[i].vb == indexb)
				|| (e[i].va == indexb && e[i].vb == indexa)) return i;
	}

	// Search all edges
	for(size_t i = 0; i < e.size(); ++i){
		if((e[i].va == indexa && e[i].vb == indexb)
				|| (e[i].va == indexb && e[i].vb == indexa)) return i;
	}

	// Create new edge
	Hull::Edge temp;
	temp.va = indexa;
	temp.vb = indexb;
	e.push_back(temp);
	size_t index = e.size() - 1;
	openedges.insert(index);
	return index;
}

size_t Hull::AddTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
	const size_t nva = FindVertex(a);
	const size_t nvb = FindVertex(b);
	const size_t nvc = FindVertex(c);

	const size_t nea = FindEdge(nva, nvb);
	const size_t neb = FindEdge(nvb, nvc);
	const size_t nec = FindEdge(nvc, nva);

	for(size_t i = 0; i < t.size(); ++i){
		if((t[i].va == nva && t[i].vb == nvb && t[i].vc == nvc)
				|| (t[i].va == nva && t[i].vb == nvc && t[i].vc == nvb)
				|| (t[i].va == nvb && t[i].vb == nvc && t[i].vc == nva)
				|| (t[i].va == nvb && t[i].vb == nva && t[i].vc == nvc)
				|| (t[i].va == nvc && t[i].vb == nva && t[i].vc == nvb)
				|| (t[i].va == nvc && t[i].vb == nvb && t[i].vc == nva)) return i;
	}

	// Add new triangle
	Hull::Triangle tempt;
	tempt.va = nva;
	tempt.vb = nvb;
	tempt.vc = nvc;
	tempt.ea = nea;
	tempt.eb = neb;
	tempt.ec = nec;
	t.push_back(tempt);
	size_t index = t.size() - 1;

	e[nea].trianglecount++;
	e[neb].trianglecount++;
	e[nec].trianglecount++;
	bool flag = false;
	if(e[nea].trianglecount == 1) e[nea].ta = index;
	if(e[nea].trianglecount == 2){
		e[nea].tb = index;
		openedges.erase(nea);
		flag = true;
	}
	if(e[neb].trianglecount == 1) e[neb].ta = index;
	if(e[neb].trianglecount == 2){
		e[neb].tb = index;
		openedges.erase(neb);
		flag = true;
	}
	if(e[nec].trianglecount == 1) e[nec].ta = index;
	if(e[nec].trianglecount == 2){
		e[nec].tb = index;
		openedges.erase(nec);
		flag = true;
	}
	if(flag){
		bool foundedge = false;
		for(std::set <size_t>::iterator it = openedges.begin();
				it != openedges.end(); ++it){
			const size_t i = *it;
			if(e[i].va == nva || e[i].vb == nva){
				foundedge = true;
				break;
			}
		}
		if(!foundedge) openvertices.erase(nva);
		foundedge = false;
		for(std::set <size_t>::iterator it = openedges.begin();
				it != openedges.end(); ++it){
			const size_t i = *it;
			if(e[i].va == nvb || e[i].vb == nvb){
				foundedge = true;
				break;
			}
		}
		if(!foundedge) openvertices.erase(nvb);
		foundedge = false;
		for(std::set <size_t>::iterator it = openedges.begin();
				it != openedges.end(); ++it){
			const size_t i = *it;
			if(e[i].va == nvc || e[i].vb == nvc){
				foundedge = true;
				break;
			}
		}
		if(!foundedge) openvertices.erase(nvc);
	}
	return index;
}

size_t Hull::AddTriangleTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const AffineTransformMatrix &transformMatrix)
{
	size_t nt = AddTriangle(transformMatrix.Transform(a),
			transformMatrix.Transform(b), transformMatrix.Transform(c));
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
	AddTriangle(transformMatrix.Transform(a), transformMatrix.Transform(b),
			transformMatrix.Transform(c));
	AddTriangle(transformMatrix.Transform(a), transformMatrix.Transform(c),
			transformMatrix.Transform(d));
}

size_t Hull::SelectAll(void)
{
	const size_t n0 = selected.size();
	for(size_t n = 0; n < v.size(); ++n)
		selected.insert(n);
	return selected.size() - n0;
}

size_t Hull::UnselectAll(void)
{
	const size_t n0 = selected.size();
	selected.clear();
	return n0;
}

size_t Hull::SelectByPlane(Vector3 n, double d)
{
	const size_t n0 = selected.size();
	for(size_t i = 0; i < v.size(); ++i){
		const double temp = v[i].Dot(n);
		if(temp >= d) selected.insert(i);
	}
	return selected.size() - n0;
}

size_t Hull::UnselectByPlane(Vector3 n, double d)
{
	const size_t n0 = selected.size();
	for(size_t i = 0; i < v.size(); ++i){
		const double temp = v[i].Dot(n);
		if(temp >= d) selected.erase(i);
	}
	return n0 - selected.size();
}

size_t Hull::SelectByNormal(Vector3 n, double limit)
{
	const size_t n0 = selected.size();
	for(size_t i = 0; i < v.size(); ++i){
		const double temp = vn[i].Dot(n);
		if(temp >= limit) selected.insert(i);
	}
	return selected.size() - n0;
}

size_t Hull::UnselectByNormal(Vector3 n, double limit)
{
	const size_t n0 = selected.size();
	for(size_t i = 0; i < v.size(); ++i){
		const double temp = vn[i].Dot(n);
		if(temp >= limit) selected.erase(i);
	}
	return n0 - selected.size();
}

size_t Hull::CountSelected(void) const
{
	return selected.size();
}
