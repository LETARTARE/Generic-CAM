//============================================================================
// Name        : Workpiece.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 29.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "Workpiece.h"
#include <GL/gl.h>
#include <math.h>
Workpiece::Workpiece()
{
	s = gts_surface_new(gts_surface_class(), gts_face_class(),
			gts_edge_class(), gts_vertex_class());

	AddBox(0.4, 0.3, 0.1);
}

Workpiece::~Workpiece()
{
	delete s;
}
void Workpiece::AddTriangle(const Vector3 &p0, const Vector3 &p1,
		const Vector3 &p2)
{
	GtsVertex *v0 = gts_vertex_new(gts_vertex_class(), p0.x, p0.y, p0.z);
	GtsVertex *v1 = gts_vertex_new(gts_vertex_class(), p1.x, p1.y, p1.z);
	GtsVertex *v2 = gts_vertex_new(gts_vertex_class(), p2.x, p2.y, p2.z);
	GtsEdge *e0 = gts_edge_new(gts_edge_class(), v0, v1);
	GtsEdge *e1 = gts_edge_new(gts_edge_class(), v1, v2);
	GtsEdge *e2 = gts_edge_new(gts_edge_class(), v2, v0);
	gts_surface_add_face(s, gts_face_new(s->face_class, e0, e1, e2));
}

void Workpiece::AddQuad(const Vector3 &p0, const Vector3 &p1,
		const Vector3 &p2, const Vector3 &p3)
{
	AddTriangle(p0, p1, p2);
	AddTriangle(p2, p3, p0);
}
void Workpiece::AddBox(const double sizeX, const double sizeY,
		const double sizeZ)
{
	Vector3 v0(0, 0, 0);
	Vector3 v1(+sizeX, 0, 0);
	Vector3 v2(+sizeX, +sizeY, 0);
	Vector3 v3(0, +sizeY, 0);
	Vector3 v4(0, 0, +sizeZ);
	Vector3 v5(+sizeX, 0, +sizeZ);
	Vector3 v6(+sizeX, +sizeY, +sizeZ);
	Vector3 v7(0, +sizeY, +sizeZ);

	AddQuad(v0, v3, v2, v1);
	AddQuad(v1, v2, v6, v5);
	AddQuad(v4, v5, v6, v7);
	AddQuad(v0, v4, v7, v3);
	AddQuad(v2, v3, v7, v6);
	AddQuad(v1, v5, v4, v0);
}

void Workpiece::Paint()
{
	GSList * strips = NULL;
	GSList * i;
	GSList * j;
	GtsTriangle * t;
	GtsPoint *p1;
	GtsPoint *p2;
	GtsPoint *p3;
	gdouble x, y, z;
	double d;
	strips = gts_surface_strip(s);
	i = strips;

	::glBegin(GL_TRIANGLES);
	while(i){
		j = (GSList *) i->data;
		while(j){
			t = (GtsTriangle *) j->data;
			p1 = GTS_POINT (GTS_SEGMENT (t->e1)->v1);
			p2 = GTS_POINT (GTS_SEGMENT (t->e1)->v2);
			p3 = GTS_POINT (gts_triangle_vertex (t));
			gts_triangle_normal(t, &x, &y, &z);
			d = sqrt(x * x + y * y + z * z);
			if(d == 0) d = 1;
			glNormal3d(x / d, y / d, z / d);
			glVertex3d(p1->x, p1->y, p1->z);
			glVertex3d(p2->x, p2->y, p2->z);
			glVertex3d(p3->x, p3->y, p3->z);
			j = j->next;
		}
		i = i->next;
	}
	::glEnd();
}
