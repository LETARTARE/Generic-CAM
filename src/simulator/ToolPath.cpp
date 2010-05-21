///////////////////////////////////////////////////////////////////////////////
// Name               : ToolPath.h
// Purpose            : Describing the boundary of the volume to be cut away.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.03.2010
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


#include "ToolPath.h"

#include <wx/log.h>

ToolPath::ToolPath()
{

}

ToolPath::~ToolPath()
{
}

/** \brief Generate a closed surface of the volume, to be cut away.
 *
 * This function generates the surface by splitting the toolshape
 * in several convex part, extruden the parts and merging them
 * all together. This is done to get undercuts and xz- or yz- cuts
 * right.
 */
void ToolPath::Generate(Tool const& tool,
		AffineTransformMatrix const& position0,
		AffineTransformMatrix const& position1)
{
	this->Clear();

	AffineTransformMatrix motion;
	motion = position1 / position0;
	motion.TakeMatrixApart();
	//wxLogMessage(motion.ToString());

	// Direction of motion
	Vector3 m(motion.tx, motion.ty, motion.tz);
	m.Normalize();

	const unsigned int resolution = tool.resolution;
	unsigned int i,j;

	float ss[resolution + 1], cc[resolution + 1];
	for(i = 0; i <= resolution; i++){
		ss[i] = sin(2* M_PI / resolution * i);
		cc[i] = cos(2* M_PI / resolution * i);
	}

	unsigned int n = 0;
	unsigned int object = 0;

	const bool workOnNonCutting = true; //TODO: Use this as a flag later.
	const double epsilon = 1e-5; // = 10 µm
	const double epsilona = 1e-5; // = 10 µrad

	ArrayOfToolContourElement contour;
	ToolContourElement *temp;


	//z is positive in direction of the tooltip.
	//x is the radius.

	// Right hand coordinate system for tools:
	// x to the right, z to the bottom, y towards the viewer
	// The angles of a and a2 are in this case
	// counterclockwise around y.

	float a, a2; // Angles of ToolContourElement normals to the outside.

	float sx, sz, zx, zz; // Only for debugging.

	// Splitting of the contour in convex elements.
	while(n < tool.contour.Count()){
		if(tool.contour[n].isCutting || workOnNonCutting){
			object++;


			// Just for easier access while debugging.
			//TODO: Delete following lines later.
			sx = tool.contour[n].p1.x;
			sz = tool.contour[n].p1.z;
			zx = tool.contour[n].p2.x;
			zz = tool.contour[n].p2.z;

			a = atan2(tool.contour[n].p2.x - tool.contour[n].p1.x,
					tool.contour[n].p2.z - tool.contour[n].p1.z);
			if(a < (M_PI_2 + epsilona) && a > (-M_PI_2 - epsilona)){
				contour.Clear();


				// Extra top cap?.
				if(fabs(tool.contour[n].p1.x) > epsilon){
					temp = new ToolContourElement;
					temp->p1.x = 0;
					temp->p1.z = tool.contour[n].p1.z;
					temp->p2.x = tool.contour[n].p1.x;
					temp->p2.z = tool.contour[n].p1.z;
					contour.Add(temp);
					a = M_PI_2;
				}

				a2 = atan2(tool.contour[n].p2.x - tool.contour[n].p1.x,
						tool.contour[n].p2.z - tool.contour[n].p1.z);
				while(a2 < a + epsilon && a2 >= -M_PI_2 - epsilon
						&& (tool.contour[n].isCutting || workOnNonCutting)){

					if(tool.contour[n].p1.x >= epsilon || tool.contour[n].p2.x
							>= epsilon){
						temp = new ToolContourElement;
						temp->p1.x = tool.contour[n].p1.x;
						temp->p1.z = tool.contour[n].p1.z;
						temp->p2.x = tool.contour[n].p2.x;
						temp->p2.z = tool.contour[n].p2.z;
						contour.Add(temp);
						a = a2;
					}

					n++;
					if(n < tool.contour.Count()){
						a2 = atan2(tool.contour[n].p2.x - tool.contour[n].p1.x,
								tool.contour[n].p2.z - tool.contour[n].p1.z);
					}else{
						a2 = -M_PI;
					}
				}
				// Extra end cap?.
				if(fabs(tool.contour[n].p2.x) > epsilon){
					temp = new ToolContourElement;
					temp->p1.x = tool.contour[n].p2.x;
					temp->p1.z = tool.contour[n].p2.z;
					temp->p2.x = 0;
					temp->p2.z = tool.contour[n].p2.z;
					contour.Add(temp);
				}


				// Generate mesh!

				if(contour.Count()>=2){
					// Cutting angles of the top cap:

					GtsVertex *v0; //= gts_vertex_new(s->vertex_class, 0, 0, 0);
					GtsVertex *v1; //= gts_vertex_new(s->vertex_class, 0, 0, 0);
					GtsEdge *e0; //= gts_edge_new(s->edge_class, v4, v1);
					GtsEdge *e1; //= gts_edge_new(s->edge_class, v4, v1);
					GtsEdge *e2; //= gts_edge_new(s->edge_class, v4, v1);
										//gts_surface_add_face(s, gts_face_new(s->face_class, e00,
						//	e17, e06));
					GtsVertex* v[resolution];
					GtsEdge* e[resolution];

					Vector3 t;

					// Top cap
					t=position0.Transform(contour[0].p1);
					v0 = gts_vertex_new(s->vertex_class, t.x,t.y,t.z);
					for(j = 0; j < resolution; j++){
						t.Set(contour[0].p2.x*cc[j],contour[0].p2.x*ss[j],contour[0].p2.z);
						t=position0.Transform(t);
						v[j] = gts_vertex_new(s->vertex_class, t.x,t.y,t.z);

						if(j==0)
						{
							e0= gts_edge_new(s->edge_class, v0, v[0]);
							e2=e0;
						}else{
							e1=e2;
							e2=gts_edge_new(s->edge_class, v0, v[j]);
							e[j-1]=gts_edge_new(s->edge_class, v[j-1], v[j]);
							gts_surface_add_face(s, gts_face_new(s->face_class, e2,e[j-1], e1));
						}
					}
					e[j-1]=gts_edge_new(s->edge_class, v[j-1], v[0]);
					gts_surface_add_face(s, gts_face_new(s->face_class, e0,e[j-1], e2));





//					for(i = 0; i < contour.Count(); i++){
//						::glBegin(GL_QUAD_STRIP);
//						for(j = 0; j <= resolution; j++){
//							::glNormal3f(cc[j] * contour[i].n1.x, ss[j]
//									* contour[i].n1.x, contour[i].n1.z);
//							::glVertex3f(cc[j] * contour[i].p1.x, ss[j]
//									* contour[i].p1.x, contour[i].p1.z);
//							::glNormal3f(cc[j] * contour[i].n2.x, ss[j]
//									* contour[i].n2.x, contour[i].n2.z);
//							::glVertex3f(cc[j] * contour[i].p2.x, ss[j]
//									* contour[i].p2.x, contour[i].p2.z);
//						}
//						::glEnd();
//					}

				}

			}
		}

	}

}

//
//		for(i = 0; i < contour.Count(); i++){
//			::glBegin(GL_QUAD_STRIP);
//			for(j = 0; j <= resolution; j++){
//				::glNormal3f(cc[j] * contour[i].n1.x, ss[j] * contour[i].n1.x,
//						contour[i].n1.z);
//				::glVertex3f(cc[j] * contour[i].p1.x, ss[j] * contour[i].p1.x,
//						contour[i].p1.z);
//				::glNormal3f(cc[j] * contour[i].n2.x, ss[j] * contour[i].n2.x,
//						contour[i].n2.z);
//				::glVertex3f(cc[j] * contour[i].p2.x, ss[j] * contour[i].p2.x,
//						contour[i].p2.z);
//			}
//			::glEnd();
//		}


