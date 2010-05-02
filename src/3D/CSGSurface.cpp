///////////////////////////////////////////////////////////////////////////////
// Name               : CSGSurface.cpp
// Purpose            : Wrapper for Constructive Solid Geometry.
// Thread Safe        : Yes
// Platform dependend : No
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "CSGSurface.h"
#include <GL/gl.h>
#include <math.h>

CSGSurface::CSGSurface()
{
	s = gts_surface_new(gts_surface_class(), gts_face_class(),
			gts_edge_class(), gts_vertex_class());
}

CSGSurface::~CSGSurface()
{
	gts_object_destroy(GTS_OBJECT (s));
}

bool CSGSurface::SelfTest()
{
	if(!gts_surface_is_orientable(s)){
		fprintf(stderr, "surface is not orientable\n");
		return false;
	}
	if(!gts_surface_is_closed(s)){
		fprintf(stderr, "surface is not closed\n");
		return false;
	}
	if(gts_surface_is_self_intersecting(s)){
		fprintf(stderr, "surface is self-intersecting\n");
		return false;
	}
	return true;
}

void CSGSurface::Statistics(void)
{

	gts_surface_print_stats(s, stderr);
}

void CSGSurface::Paint()
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

	GtsSurfaceStats st;
	gts_surface_stats(s, &st);
	g_assert(st.n_incompatible_faces == 0 && st.n_non_manifold_edges == 0);

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

void CSGSurface::AddBox(const double sizeX, const double sizeY,
		const double sizeZ)
{
	// This is so ugly. gts expects closed surfaces, i.e. no overlapping edges and lines.
	GtsVertex *v0 = gts_vertex_new(s->vertex_class, 0, 0, 0);
	GtsVertex *v1 = gts_vertex_new(s->vertex_class, sizeX, 0, 0);
	GtsVertex *v2 = gts_vertex_new(s->vertex_class, sizeX, sizeY, 0);
	GtsVertex *v3 = gts_vertex_new(s->vertex_class, 0, sizeY, 0);
	GtsVertex *v4 = gts_vertex_new(s->vertex_class, 0, 0, sizeZ);
	GtsVertex *v5 = gts_vertex_new(s->vertex_class, sizeX, 0, sizeZ);
	GtsVertex *v6 = gts_vertex_new(s->vertex_class, sizeX, sizeY, sizeZ);
	GtsVertex *v7 = gts_vertex_new(s->vertex_class, 0, sizeY, sizeZ);

	GtsEdge *e00 = gts_edge_new(s->edge_class, v4, v1);
	GtsEdge *e01 = gts_edge_new(s->edge_class, v1, v0);
	GtsEdge *e02 = gts_edge_new(s->edge_class, v1, v3);
	GtsEdge *e03 = gts_edge_new(s->edge_class, v3, v2);
	GtsEdge *e04 = gts_edge_new(s->edge_class, v6, v7);
	GtsEdge *e05 = gts_edge_new(s->edge_class, v6, v4);
	GtsEdge *e06 = gts_edge_new(s->edge_class, v5, v4);
	GtsEdge *e07 = gts_edge_new(s->edge_class, v5, v6);
	GtsEdge *e08 = gts_edge_new(s->edge_class, v6, v1);
	GtsEdge *e09 = gts_edge_new(s->edge_class, v2, v1);
	GtsEdge *e10 = gts_edge_new(s->edge_class, v4, v7);
	GtsEdge *e11 = gts_edge_new(s->edge_class, v4, v3);
	GtsEdge *e12 = gts_edge_new(s->edge_class, v3, v0);
	GtsEdge *e13 = gts_edge_new(s->edge_class, v4, v0);
	GtsEdge *e14 = gts_edge_new(s->edge_class, v7, v3);
	GtsEdge *e15 = gts_edge_new(s->edge_class, v6, v3);
	GtsEdge *e16 = gts_edge_new(s->edge_class, v6, v2);
	GtsEdge *e17 = gts_edge_new(s->edge_class, v5, v1);


	// A closed box made from triangles.
	gts_surface_add_face(s, gts_face_new(s->face_class, e00, e17, e06));
	gts_surface_add_face(s, gts_face_new(s->face_class, e13, e01, e00));
	gts_surface_add_face(s, gts_face_new(s->face_class, e12, e02, e01));
	gts_surface_add_face(s, gts_face_new(s->face_class, e02, e03, e09));
	gts_surface_add_face(s, gts_face_new(s->face_class, e05, e04, e10));
	gts_surface_add_face(s, gts_face_new(s->face_class, e07, e05, e06));
	gts_surface_add_face(s, gts_face_new(s->face_class, e07, e17, e08));
	gts_surface_add_face(s, gts_face_new(s->face_class, e08, e09, e16));
	gts_surface_add_face(s, gts_face_new(s->face_class, e10, e14, e11));
	gts_surface_add_face(s, gts_face_new(s->face_class, e13, e11, e12));
	gts_surface_add_face(s, gts_face_new(s->face_class, e04, e15, e14));
	gts_surface_add_face(s, gts_face_new(s->face_class, e15, e16, e03));
}

void CSGSurface::SetSphere(const double radius, const unsigned char subdivision)
{
	gts_surface_generate_sphere(s, subdivision);
	ScaleUniform(radius);
}

void CSGSurface::ScaleUniform(float scaleXYZ)
{
	GtsMatrix * m;
	m = gts_matrix_identity(NULL);
	m[0][0] = m[1][1] = m[2][2] = scaleXYZ;
	gts_surface_foreach_vertex(s, (GtsFunc) gts_point_transform, m);
	gts_matrix_destroy(m);
}

void CSGSurface::Scale(float scaleX, float scaleY, float scaleZ)
{
	GtsMatrix * m;
	m = gts_matrix_identity(NULL);
	m[0][0] = scaleX;
	m[1][1] = scaleY;
	m[2][2] = scaleZ;
	gts_surface_foreach_vertex(s, (GtsFunc) gts_point_transform, m);
	gts_matrix_destroy(m);
}

void CSGSurface::Rotate(float rotateX, float rotateY, float rotateZ)
{
	double cox = cos(rotateX);
	double six = sin(rotateX);
	double coy = cos(rotateY);
	double siy = sin(rotateY);
	double coz = cos(rotateZ);
	double siz = sin(rotateZ);

	GtsMatrix * m;
	m = gts_matrix_identity(NULL);


	// Matrix calculated with Axiom:
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// Rz*Ry*Rx

	m[0][0] = coy * coz;
	m[1][0] = coy * siz;
	m[2][0] = -siy;
	m[0][1] = -cox * siz + coz * six * siy;
	m[1][1] = six * siy * siz + cox * coz;
	m[2][1] = coy * six;
	m[0][2] = six * siz + cox * coz * siy;
	m[1][2] = cox * siy * siz - coz * six;
	m[2][2] = cox * coy;

	gts_surface_foreach_vertex(s, (GtsFunc) gts_point_transform, m);
	gts_matrix_destroy(m);
}

void CSGSurface::Translate(float translateX, float translateY, float translateZ)
{
	GtsMatrix * m;
	m = gts_matrix_identity(NULL);
	m[0][3] = translateX;
	m[1][3] = translateY;
	m[2][3] = translateZ;
	gts_surface_foreach_vertex(s, (GtsFunc) gts_point_transform, m);
	gts_matrix_destroy(m);
}

static void prepend_triangle_bbox(GtsTriangle * t, GSList ** bboxes)
{
	*bboxes = g_slist_prepend(*bboxes, gts_bbox_triangle(gts_bbox_class(), t));
}

void CSGSurface::BooleanRemove(const CSGSurface* surfaceToRemove)
{
	// This here is copied and modified from set.c.
	// set.c is part of the gts-examples.

	// check surfaces
	g_assert(gts_surface_is_orientable(s));
	g_assert(gts_surface_is_orientable(surfaceToRemove->s));
	g_assert(!gts_surface_is_self_intersecting(s));
	g_assert(!gts_surface_is_self_intersecting(surfaceToRemove->s));

	GtsSurfaceInter * si;

	GNode * tree1;
	GNode * tree2;

	gboolean is_open1, is_open2;

	gboolean closed = TRUE;


	// build bounding boxes for first surface
	//bboxes = NULL;
	//gts_surface_foreach_face(s, (GtsFunc) prepend_triangle_bbox, &bboxes);
	// build bounding box tree for first surface
	//tree1 = gts_bb_tree_new(bboxes);
	tree1 = gts_bb_tree_surface(s);
	// free list of bboxes
	//g_slist_free(bboxes);
	is_open1 = gts_surface_volume(s) < 0.? TRUE : FALSE;


	// build bounding boxes for second surface
	//bboxes = NULL;
	//gts_surface_foreach_face(surfaceToRemove->s,
	//		(GtsFunc) prepend_triangle_bbox, &bboxes);
	// build bounding box tree for second surface
	//tree2 = gts_bb_tree_new(bboxes);
	tree2 = gts_bb_tree_surface(surfaceToRemove->s);


	// free list of bboxes
	//g_slist_free(bboxes);
	is_open2 = gts_surface_volume(surfaceToRemove->s) < 0.? TRUE : FALSE;

	if(is_open1){
		fprintf(stderr, "set: surface 1 is open\r\n");
	}
	if(is_open2){
		fprintf(stderr, "set: surface 2 is open\r\n");
	}

	si = gts_surface_inter_new(gts_surface_inter_class(), s,
			surfaceToRemove->s, tree1, tree2, is_open1, is_open2);
	g_assert(gts_surface_inter_check(si, &closed));

	if(!closed){
		fprintf(stderr,
				"set: the intersection of the surfaces is not a closed curve\r\n");
		return;
	}

	//	s1out2 = gts_surface_new(gts_surface_class(), gts_face_class(),
	//			gts_edge_class(), gts_vertex_class());


	//	s1in2 = gts_surface_new(gts_surface_class(), gts_face_class(),
	//			gts_edge_class(), gts_vertex_class());
	//	s2out1 = gts_surface_new(gts_surface_class(), gts_face_class(),
	//			gts_edge_class(), gts_vertex_class());
	//	s2in1 = gts_surface_new(gts_surface_class(), gts_face_class(),
	//			gts_edge_class(), gts_vertex_class());


	GtsSurface * temp;
	temp = gts_surface_new(gts_surface_class(), gts_face_class(),
			gts_edge_class(), gts_vertex_class());


	// Generate new surface s
	//gts_surface_inter_boolean(si, temp, GTS_1_OUT_2);

	gts_surface_inter_boolean(si, temp, GTS_1_OUT_2);
	gts_surface_inter_boolean(si, temp, GTS_2_IN_1);
	gts_surface_foreach_face(si->s2, (GtsFunc) gts_triangle_revert, NULL);
	gts_surface_foreach_face(surfaceToRemove->s, (GtsFunc) gts_triangle_revert,
			NULL);

	gts_object_destroy(GTS_OBJECT (s));
	s = temp;

	gts_bb_tree_destroy(tree1, TRUE);
	gts_bb_tree_destroy(tree2, TRUE);
	gts_object_destroy(GTS_OBJECT (si));


	//	if(closed){
	//		GtsSurfaceStats st1out2, st1in2, st2out1, st2in1;
	//		gpointer data[3];
	//		guint nf = 0;
	//		gdouble a, ain, aout;
	//
	//		gts_surface_inter_boolean(si, s1out2, GTS_1_OUT_2);
	//		gts_surface_inter_boolean(si, s1in2, GTS_1_IN_2);
	//		gts_surface_inter_boolean(si, s2out1, GTS_2_OUT_1);
	//		gts_surface_inter_boolean(si, s2in1, GTS_2_IN_1);
	//
	//		gts_surface_stats(s1out2, &st1out2);
	//		fprintf(stderr, "----------- 1 out 2 -----------\n");
	//		gts_surface_print_stats(s1out2, stderr);
	//		g_assert(st1out2.n_incompatible_faces == 0
	//				&& st1out2.n_non_manifold_edges == 0);
	//	}
}

void CSGSurface::BooleanAdd(const CSGSurface* surfaceToAdd)
{
	// This here is copied and modified from set.c.
	// set.c is part of the gts-examples.

	// check surfaces
	g_assert(gts_surface_is_orientable(s));
	g_assert(gts_surface_is_orientable(surfaceToAdd->s));
	g_assert(!gts_surface_is_self_intersecting(s));
	g_assert(!gts_surface_is_self_intersecting(surfaceToAdd->s));

	GtsSurfaceInter * si;

	GNode * tree1;
	GNode * tree2;

	gboolean is_open1, is_open2;

	gboolean closed = TRUE;


	// build bounding boxes for first surface
	tree1 = gts_bb_tree_surface(s);
	is_open1 = gts_surface_volume(s) < 0.? TRUE : FALSE;


	// build bounding boxes for second surface
	tree2 = gts_bb_tree_surface(surfaceToAdd->s);
	is_open2 = gts_surface_volume(surfaceToAdd->s) < 0.? TRUE : FALSE;

	if(is_open1) fprintf(stderr, "set: surface 1 is open\r\n");

	if(is_open2) fprintf(stderr, "set: surface 2 is open\r\n");

	si = gts_surface_inter_new(gts_surface_inter_class(), s, surfaceToAdd->s,
			tree1, tree2, is_open1, is_open2);
	g_assert(gts_surface_inter_check(si, &closed));

	if(!closed){
		fprintf(stderr,
				"set: the intersection of the surfaces is not a closed curve\r\n");
		return;
	}

	GtsSurface * temp;
	temp = gts_surface_new(gts_surface_class(), gts_face_class(),
			gts_edge_class(), gts_vertex_class());


	// Generate new surface s
	//gts_surface_inter_boolean(si, temp, GTS_1_OUT_2);

	gts_surface_inter_boolean(si, temp, GTS_1_OUT_2);
	gts_surface_inter_boolean(si, temp, GTS_2_OUT_1);
	//	gts_surface_foreach_face(si->s2, (GtsFunc) gts_triangle_revert, NULL);
	//	gts_surface_foreach_face(surfaceToAdd->s, (GtsFunc) gts_triangle_revert,
	//			NULL);
	//	gts_surface_foreach_face(si->s1, (GtsFunc) gts_triangle_revert, NULL);
	//	gts_surface_foreach_face(s, (GtsFunc) gts_triangle_revert,
	//			NULL);

	gts_object_destroy(GTS_OBJECT (s));
	s = temp;

	gts_bb_tree_destroy(tree1, TRUE);
	gts_bb_tree_destroy(tree2, TRUE);
	gts_object_destroy(GTS_OBJECT (si));
}

