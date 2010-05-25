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
	unsigned int i, j;

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

	// Splitting of the contour in convex elements.
	while(n < tool.contour.Count()){
		if(tool.contour[n].isCutting || workOnNonCutting){
			object++;

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
				if(fabs(tool.contour[n - 1].p2.x) > epsilon){
					temp = new ToolContourElement;
					temp->p1.x = tool.contour[n - 1].p2.x;
					temp->p1.z = tool.contour[n - 1].p2.z;
					temp->p2.x = 0;
					temp->p2.z = tool.contour[n - 1].p2.z;
					contour.Add(temp);
				}


				// Generate mesh:

				if(contour.Count() >= 2){

					GtsVertex *v0;
					GtsVertex *v1;
					GtsVertex *v2;
					GtsEdge *e0;
					GtsEdge *e1;
					GtsEdge *e2;

					GtsVertex* v[resolution];
					GtsEdge* e[resolution];

					Vector3 t;


					// Cutting angles of the top cap:

					a2 = 45.0 / 180*M_PI;
					a = 90.0 / 180*M_PI;

					int n1, n2;
					n1 = (int) floor((float) resolution / 2 / M_PI * (a2 - a));
					n2 = (int) floor((float) resolution / 2 / M_PI * (a2 + a));

					if(n2 > (int) resolution) n2 -= resolution;
					if(n1 < 0) n1 += resolution;


					// Top cap:
					// Generate center vertex

					if((n1 <= n2 && n1 <= 0 && 0 <= n2) || (n1 > n2 && n1 > 0
							&& 0 > n2)){
						t = position0.Transform(contour[0].p1);
					}else{
						t = position1.Transform(contour[0].p1);
					}
					v0 = gts_vertex_new(s->vertex_class, t.x, t.y, t.z);
					// Generate edge ring and surfaces
					for(j = 0; j < resolution; j++){
						t.Set(contour[0].p2.x * cc[j], contour[0].p2.x * ss[j],
								contour[0].p2.z);

						if((n1 <= n2 && n1 <= (int) j && (int) j <= n2) || (n1
								> n2 && n1 > (int) j && (int) j > n2)){
							t = position0.Transform(t);
						}else{
							t = position1.Transform(t);
						}
						v[j] = gts_vertex_new(s->vertex_class, t.x, t.y, t.z);

						if(j == 0){
							e0 = gts_edge_new(s->edge_class, v0, v[0]);
							e2 = e0;
						}else{
							e1 = e2;
							e2 = gts_edge_new(s->edge_class, v0, v[j]);
							e[j - 1] = gts_edge_new(s->edge_class, v[j - 1],
									v[j]);
							gts_surface_add_face(s, gts_face_new(s->face_class,
									e2, e[j - 1], e1));
						}
					}
					e[j - 1] = gts_edge_new(s->edge_class, v[j - 1], v[0]);
					gts_surface_add_face(s, gts_face_new(s->face_class, e0, e[j
							- 1], e2));


					// Middle elements:
					for(i = 1; i < contour.Count() - 1; i++){
						// First vertex
						if((n1 <= n2 && n1 <= 0 && 0 <= n2) || (n1 > n2 && n1
								> 0 && 0 > n2)){
							t = position0.Transform(contour[i].p2);
						}else{
							t = position1.Transform(contour[i].p2);
						}

						v0 = gts_vertex_new(s->vertex_class, t.x, t.y, t.z);
						v2 = v0;


						// First edge
						e0 = gts_edge_new(s->edge_class, v[0], v2);
						e2 = e0;

						for(j = 0; j < resolution - 1; j++){
							v1 = v2;
							t.Set(contour[i].p2.x * cc[j + 1], contour[i].p2.x
									* ss[j + 1], contour[i].p2.z);
							if((n1 <= n2 && n1 <= (int) j && (int) j <= n2)
									|| (n1 > n2 && n1 > (int) j && (int) j > n2)){
								t = position0.Transform(t);
							}else{
								t = position1.Transform(t);
							}
							v2 = gts_vertex_new(s->vertex_class, t.x, t.y, t.z);


							// Generate 1st triangle
							e1 = e2;
							e2 = gts_edge_new(s->edge_class, v[j + 1], v1);

							gts_surface_add_face(s, gts_face_new(s->face_class,
									e2, e1, e[j]));


							// Generate 2nd triangle
							e1 = e2;
							e2 = gts_edge_new(s->edge_class, v[j + 1], v2);

							e[j] = gts_edge_new(s->edge_class, v1, v2);

							gts_surface_add_face(s, gts_face_new(s->face_class,
									e1, e2, e[j]));

							v[j + 1] = v2;
						}
						// Generate 1st triangle
						e1 = e2;
						e2 = gts_edge_new(s->edge_class, v[0], v2);
						gts_surface_add_face(s, gts_face_new(s->face_class, e2,
								e1, e[j]));


						// Generate 2nd triangle
						e[j] = gts_edge_new(s->edge_class, v2, v0);
						gts_surface_add_face(s, gts_face_new(s->face_class, e2,
								e0, e[j]));
						v[0] = v0;
					}

					// Bottom cap:
					// Generate center vertex

					if((n1 <= n2 && n1 <= 0 && 0 <= n2) || (n1 > n2 && n1 > 0
							&& 0 > n2)){
						t = position0.Transform(contour[i].p2);
					}else{
						t = position1.Transform(contour[i].p2);
					}

					v0 = gts_vertex_new(s->vertex_class, t.x, t.y, t.z);
					e0 = gts_edge_new(s->edge_class, v[0], v0);
					e2 = e0;
					// Generate surfaces
					for(j = 0; j < resolution - 1; j++){
						e1 = e2;
						e2 = gts_edge_new(s->edge_class, v[j + 1], v0);
						gts_surface_add_face(s, gts_face_new(s->face_class, e2,
								e1, e[j]));
					}
					gts_surface_add_face(s, gts_face_new(s->face_class, e0, e2,
							e[j]));
				}
			}
		}
	}
}
