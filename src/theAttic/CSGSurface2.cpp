///////////////////////////////////////////////////////////////////////////////
// Name               : CSGSurface.cpp
// Purpose            : Wrapper for Constructive Solid Geometry.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm -lgts
// Author             : Tobias Schaefer
// Created            : 15.04.2010
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
//$LastChangedDate: 2010-08-07 03:00:28 +0200 (Sa, 07 Aug 2010) $
//$Revision: 53 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#include "CSGSurface.h"

#include "../CSGLib/BooleanModeller.h"
#include "../CSGLib/Solid.h"
#include "../CSGLib/Color.h"
#include "../CSGLib/IntSet.h"
#include "../CSGLib/FaceSet.h"
#include "../CSGLib/VertexSet.h"
#include "../CSGLib/ColorSet.h"
#include "../CSGLib/Color.h"

#include <GL/gl.h>
#include <wx/debug.h>

#include <math.h>

CSGSurface::CSGSurface()
{
	solid = new Solid(new VectorSet(), new IntSet(), new ColorSet());
	solid->colors.AddColor(Color(100,100,10));
}

CSGSurface::~CSGSurface()
{
	wxASSERT(solid != NULL);
	delete solid;
}

void CSGSurface::Clear()
{
	wxASSERT(solid != NULL);
	delete solid;
	solid = new Solid(new VectorSet(), new IntSet(), new ColorSet());
	solid->colors.AddColor(Color(100,100,10));
}

bool CSGSurface::SelfTest()
{
	return true;
}

void CSGSurface::Statistics(void)
{

}

void CSGSurface::Paint() const
{

	::glPushMatrix();
	::glMultMatrixd(m.a);
	solid->Render();
	::glPopMatrix();

}

void CSGSurface::AddBox(const double sizeX, const double sizeY,
		const double sizeZ)
{


	//	Solid * pSolid = new Solid("box.txt", *m_Palette[m_nPaletteIndex], 0, 0, 0);

	solid->vertices.AddVector(Vector(0, 0, 0));
	solid->vertices.AddVector(Vector(sizeX, 0, 0));
	solid->vertices.AddVector(Vector(0, sizeY, 0));
	solid->vertices.AddVector(Vector(sizeX, sizeY, 0));
	solid->vertices.AddVector(Vector(0, 0, sizeZ));
	solid->vertices.AddVector(Vector(sizeX, 0, sizeZ));
	solid->vertices.AddVector(Vector(0, sizeY, sizeZ));
	solid->vertices.AddVector(Vector(sizeX, sizeY, sizeZ));

	solid->indices.AddInt(0);
	solid->indices.AddInt(2);
	solid->indices.AddInt(3);

	solid->indices.AddInt(3);
	solid->indices.AddInt(1);
	solid->indices.AddInt(0);

	solid->indices.AddInt(4);
	solid->indices.AddInt(5);
	solid->indices.AddInt(7);

	solid->indices.AddInt(7);
	solid->indices.AddInt(6);
	solid->indices.AddInt(4);

	solid->indices.AddInt(0);
	solid->indices.AddInt(1);
	solid->indices.AddInt(5);

	solid->indices.AddInt(5);
	solid->indices.AddInt(4);
	solid->indices.AddInt(0);

	solid->indices.AddInt(1);
	solid->indices.AddInt(3);
	solid->indices.AddInt(7);

	solid->indices.AddInt(7);
	solid->indices.AddInt(5);
	solid->indices.AddInt(1);

	solid->indices.AddInt(3);
	solid->indices.AddInt(2);
	solid->indices.AddInt(6);

	solid->indices.AddInt(6);
	solid->indices.AddInt(7);
	solid->indices.AddInt(3);

	solid->indices.AddInt(2);
	solid->indices.AddInt(0);
	solid->indices.AddInt(4);

	solid->indices.AddInt(4);
	solid->indices.AddInt(6);
	solid->indices.AddInt(2);


	// This is so ugly. gts expects closed surfaces, i.e. no overlapping edges and lines.
	//	GtsVertex *v0 = gts_vertex_new(s->vertex_class, 0, 0, 0);
	//	GtsVertex *v1 = gts_vertex_new(s->vertex_class, sizeX, 0, 0);
	//	GtsVertex *v2 = gts_vertex_new(s->vertex_class, sizeX, sizeY, 0);
	//	GtsVertex *v3 = gts_vertex_new(s->vertex_class, 0, sizeY, 0);
	//	GtsVertex *v4 = gts_vertex_new(s->vertex_class, 0, 0, sizeZ);
	//	GtsVertex *v5 = gts_vertex_new(s->vertex_class, sizeX, 0, sizeZ);
	//	GtsVertex *v6 = gts_vertex_new(s->vertex_class, sizeX, sizeY, sizeZ);
	//	GtsVertex *v7 = gts_vertex_new(s->vertex_class, 0, sizeY, sizeZ);
	//
	//	GtsEdge *e00 = gts_edge_new(s->edge_class, v4, v1);
	//	GtsEdge *e01 = gts_edge_new(s->edge_class, v1, v0);
	//	GtsEdge *e02 = gts_edge_new(s->edge_class, v1, v3);
	//	GtsEdge *e03 = gts_edge_new(s->edge_class, v3, v2);
	//	GtsEdge *e04 = gts_edge_new(s->edge_class, v6, v7);
	//	GtsEdge *e05 = gts_edge_new(s->edge_class, v6, v4);
	//	GtsEdge *e06 = gts_edge_new(s->edge_class, v5, v4);
	//	GtsEdge *e07 = gts_edge_new(s->edge_class, v5, v6);
	//	GtsEdge *e08 = gts_edge_new(s->edge_class, v6, v1);
	//	GtsEdge *e09 = gts_edge_new(s->edge_class, v2, v1);
	//	GtsEdge *e10 = gts_edge_new(s->edge_class, v4, v7);
	//	GtsEdge *e11 = gts_edge_new(s->edge_class, v4, v3);
	//	GtsEdge *e12 = gts_edge_new(s->edge_class, v3, v0);
	//	GtsEdge *e13 = gts_edge_new(s->edge_class, v4, v0);
	//	GtsEdge *e14 = gts_edge_new(s->edge_class, v7, v3);
	//	GtsEdge *e15 = gts_edge_new(s->edge_class, v6, v3);
	//	GtsEdge *e16 = gts_edge_new(s->edge_class, v6, v2);
	//	GtsEdge *e17 = gts_edge_new(s->edge_class, v5, v1);
	//
	//
	//	// A closed box made from triangles.
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e00, e17, e06));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e13, e01, e00));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e12, e02, e01));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e02, e03, e09));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e05, e04, e10));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e07, e05, e06));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e07, e17, e08));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e08, e09, e16));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e10, e14, e11));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e13, e11, e12));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e04, e15, e14));
	//	gts_surface_add_face(s, gts_face_new(s->face_class, e15, e16, e03));
}

void CSGSurface::SetSphere(const double radius, const unsigned char subdivision)
{
}

void CSGSurface::ScaleUniform(float scaleXYZ)
{
}

void CSGSurface::Scale(float scaleX, float scaleY, float scaleZ)
{
}

void CSGSurface::Rotate(float rotateX, float rotateY, float rotateZ)
{
	double cox = cos(rotateX);
	double six = sin(rotateX);
	double coy = cos(rotateY);
	double siy = sin(rotateY);
	double coz = cos(rotateZ);
	double siz = sin(rotateZ);


	// Matrix calculated with Axiom:
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// Rz*Ry*Rx

	//	m[0][0] = coy * coz;
	//	m[1][0] = coy * siz;
	//	m[2][0] = -siy;
	//	m[0][1] = -cox * siz + coz * six * siy;
	//	m[1][1] = six * siy * siz + cox * coz;
	//	m[2][1] = coy * six;
	//	m[0][2] = six * siz + cox * coz * siy;
	//	m[1][2] = cox * siy * siz - coz * six;
	//	m[2][2] = cox * coy;

}

void CSGSurface::Translate(float translateX, float translateY, float translateZ)
{
	//	m[0][3] = translateX;
	//	m[1][3] = translateY;
	//	m[2][3] = translateZ;
	solid->Translate(Vector(translateX, translateY, translateZ));
}

void InsertSurface(const CSGSurface* surface)
{
}

void CSGSurface::BooleanRemove(const CSGSurface* surfaceToRemove)
{
	wxASSERT(solid != NULL); wxASSERT(surfaceToRemove->solid != NULL);

	BooleanModeller * modeller = new BooleanModeller(solid,
			surfaceToRemove->solid);
	Solid * result = modeller->getDifference();
	delete modeller;
	delete solid;
	solid = result;
	wxASSERT(solid != NULL);

}

void CSGSurface::BooleanAdd(const CSGSurface* surfaceToAdd)
{
}

