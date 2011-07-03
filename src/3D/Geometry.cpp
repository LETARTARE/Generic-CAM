///////////////////////////////////////////////////////////////////////////////
// Name               : Geometry.cpp
// Purpose            : Class for managing 3D geometry data.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "Geometry.h"
#include <GL/gl.h>
#include <wx/log.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfGeometry)

Geometry::Geometry()
{
	visible = true;
	color.Set(1, 1, 1);
}
Geometry::~Geometry()
{
}

void Geometry::Clear(void)
{
	triangles.Clear();
}

void Geometry::CopyFrom(const Geometry &geometry)
{
	Clear();
	CopyTrianglesFrom(geometry);
	this->matrix = geometry.matrix;
	this->objectName = geometry.objectName;
	this->visible = geometry.visible;
	this->color = geometry.color;
}

void Geometry::CopyTrianglesFrom(const Geometry &geometry)
{
	size_t i;
	Triangle temp;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		temp = geometry.triangles[i];
		this->triangles.Add(temp);
	}
}

void Geometry::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].p[0] = matrix.Transform(triangles[i].p[0]);
		triangles[i].p[1] = matrix.Transform(triangles[i].p[1]);
		triangles[i].p[2] = matrix.Transform(triangles[i].p[2]);
		triangles[i].n[0] = matrix.TransformNoShift(triangles[i].n[0]);
		triangles[i].n[1] = matrix.TransformNoShift(triangles[i].n[1]);
		triangles[i].n[2] = matrix.TransformNoShift(triangles[i].n[2]);
	}
}

void Geometry::ApplyTransformation(void)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].p[0] = this->matrix.Transform(triangles[i].p[0]);
		triangles[i].p[1] = this->matrix.Transform(triangles[i].p[1]);
		triangles[i].p[2] = this->matrix.Transform(triangles[i].p[2]);
		triangles[i].n[0] = this->matrix.TransformNoShift(triangles[i].n[0]);
		triangles[i].n[1] = this->matrix.TransformNoShift(triangles[i].n[1]);
		triangles[i].n[2] = this->matrix.TransformNoShift(triangles[i].n[2]);
	}
}

void Geometry::Paint(void) const
{
	if(!visible) return;
	size_t i;
	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_TRIANGLES);
	::glColor3f(color.x, color.y, color.z);
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].Paint();
	}
	::glEnd();
	::glPopMatrix();
}

void Geometry::AddTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddTriangleWithNormals(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &na, const Vector3 &nb,
		const Vector3 &nc)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->n[0] = na;
	tri->n[1] = nb;
	tri->n[2] = nc;
	triangles.Add(tri);
}

void Geometry::AddTriangleTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const AffineTransformMatrix &transformMatrix)
{
	Triangle* tri = new Triangle;
	tri->p[0] = transformMatrix.Transform(a);
	tri->p[1] = transformMatrix.Transform(b);
	tri->p[2] = transformMatrix.Transform(c);
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddQuad(const Vector3 &a, const Vector3 &b, const Vector3 &c,
		const Vector3 &d)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = a;
	tri0->p[1] = b;
	tri0->p[2] = c;
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = d;
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::AddQuadTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &d,
		const AffineTransformMatrix &transformMatrix)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = transformMatrix.Transform(a);
	tri0->p[1] = transformMatrix.Transform(b);
	tri0->p[2] = transformMatrix.Transform(c);
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = transformMatrix.Transform(d);
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::CalculateNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].CalculateNormal();
	}
}

void Geometry::FlipNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].n[0] *= -1;
		triangles[i].n[1] *= -1;
		triangles[i].n[2] *= -1;
	}
}

