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

#include "Geometry.h"
#include "OpenGLMaterial.h"
#include "Polygon3.h"
#include "Triangle.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "OpenGL.h"

Hull::Edge::Edge()
{
	va = 0;
	vb = 0;
	ta = 0;
	tb = 0;
	trianglecount = 0;
	group = 0;
	sharp = false;
}

size_t Hull::Edge::OtherVertex(size_t n) const
{
	if(va == n) return vb;
	return va;
}

size_t Hull::Edge::OtherTriangle(size_t n) const
{
	if(ta == n) return tb;
	return ta;
}

bool Hull::Edge::AttachTriangle(size_t index)
{
	if(trianglecount == 0){
		ta = index;
		trianglecount++;
		return true;
	}
	if(trianglecount == 1){
		tb = index;
		trianglecount++;
		return false;
	}
	if(trianglecount < 255) trianglecount++;
	return false;
}

Hull::Triangle::Triangle()
{
	va = 0;
	vb = 0;
	vc = 0;
	ea = 0;
	eb = 0;
	ec = 0;
	group = 0;
}

int Hull::Triangle::Direction(size_t i1, size_t i2) const
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
	paintTriangles = true;
	paintEdges = true;
	paintVertices = false;
	paintNormals = false;
	smooth = false;
	paintSelected = false;
}

Hull::~Hull()
{
}

void Hull::Clear(void)
{
	v.clear();
	vn.clear();
	e.clear();
	t.clear();
	openedges.clear();
	openvertices.clear();
	selected.clear();
	matrix.SetIdentity();
}

void Hull::SetEpsilon(double newEpsilon)
{
	epsilon = newEpsilon;
	epsilon2 = newEpsilon * newEpsilon;
}

void Hull::Paint(void) const
{

	if(paintTriangles){
		PaintTriangles();
	}
	if(paintEdges){
		PaintEdges();
	}
	if(paintVertices){
		PaintVertices();
	}
	if(paintSelected){
		PaintSelected();
	}
}

void Hull::PaintTriangles(const std::set <size_t>&sel, bool invert) const
{
	const double normalscale = 0.1;
	::glPushMatrix();
	matrix.GLMultMatrix();
//	OpenGLMaterial::EnableColors();
	GLuint group = 0;
	bool skip = false;
	glPushName(group);
	glBegin(GL_TRIANGLES);
	if(smooth){
		for(size_t i = 0; i < t.size(); ++i){

			if(t[i].group != group){
				group = (GLuint) (t[i].group % ((size_t) -1));
				skip = ((!invert && sel.find(group) == sel.end())
						|| (invert && sel.find(group) != sel.end()));
				if(skip) continue;

				glEnd();
				glLoadName(group);
				glBegin(GL_TRIANGLES);
			}
			if(skip) continue;
			glNormal3f(vn[t[i].va].x, vn[t[i].va].y, vn[t[i].va].z);
			glVertex3f(v[t[i].va].x, v[t[i].va].y, v[t[i].va].z);
			glNormal3f(vn[t[i].vb].x, vn[t[i].vb].y, vn[t[i].vb].z);
			glVertex3f(v[t[i].vb].x, v[t[i].vb].y, v[t[i].vb].z);
			glNormal3f(vn[t[i].vc].x, vn[t[i].vc].y, vn[t[i].vc].z);
			glVertex3f(v[t[i].vc].x, v[t[i].vc].y, v[t[i].vc].z);
		}

	}else{
		for(size_t i = 0; i < t.size(); ++i){
			if(t[i].group != group){
				group = (GLuint) (t[i].group % ((size_t) -1));
				skip = ((!invert && sel.find(t[i].group) == sel.end())
						|| (invert && sel.find(t[i].group) != sel.end()));
				if(skip) continue;
				glEnd();
				glLoadName(group);
				glBegin(GL_TRIANGLES);
			}
			if(skip) continue;

//			glColor3f(0.5 + cos(2 * M_PI / 20.0 * t[i].group) * 0.5,
//					0.5
//							+ cos(
//									2 * M_PI / 20.0 * t[i].group
//											+ M_PI * 2.0 / 3.0) * 0.5,
//					0.5
//							+ cos(
//									2 * M_PI / 20.0 * t[i].group
//											+ M_PI * 4.0 / 3.0) * 0.5);
			glNormal3f(t[i].n.x, t[i].n.y, t[i].n.z);
			glVertex3f(v[t[i].va].x, v[t[i].va].y, v[t[i].va].z);
			glVertex3f(v[t[i].vb].x, v[t[i].vb].y, v[t[i].vb].z);
			glVertex3f(v[t[i].vc].x, v[t[i].vc].y, v[t[i].vc].z);
		}
	}
	glEnd();
	glPopName();

	if(paintNormals){

		glBegin(GL_LINES);
		for(size_t i = 0; i < t.size(); ++i){
			glNormal3f(t[i].n.x, t[i].n.y, t[i].n.z);
			const Vector3 center = (v[t[i].va] + v[t[i].vb] + v[t[i].vc]) / 3;
			glVertex3f(center.x, center.y, center.z);
			glVertex3f(center.x + t[i].n.x * normalscale,
					center.y + t[i].n.y * normalscale,
					center.z + t[i].n.z * normalscale);
		}
		glEnd();
	}
	glPopMatrix();
}

void Hull::PaintEdges(const std::set <size_t>&sel, bool invert) const
{
	const double normalscale = 0.1;
	glPushMatrix();
	matrix.GLMultMatrix();
	GLuint group = 0;
	bool skip = false;
	glPushName(group);
	glBegin(GL_LINES);
	if(smooth){
		for(size_t i = 0; i < e.size(); ++i){
			if(e[i].group != group){
				group = (GLuint) (e[i].group % ((size_t) -1));
				skip = ((!invert && sel.find(group) == sel.end())
						|| (invert && sel.find(group) != sel.end()));
				if(skip) continue;
				glEnd();
				glLoadName(group);
				glBegin(GL_LINES);
			}
			if(skip) continue;
			if(!e[i].sharp) continue;
			glNormal3f(vn[e[i].va].x, vn[e[i].va].y, vn[e[i].va].z);
			glVertex3f(v[e[i].va].x, v[e[i].va].y, v[e[i].va].z);
			glNormal3f(vn[e[i].vb].x, vn[e[i].vb].y, vn[e[i].vb].z);
			glVertex3f(v[e[i].vb].x, v[e[i].vb].y, v[e[i].vb].z);
		}
	}else{
		for(size_t i = 0; i < e.size(); ++i){
			if(e[i].group != group){
				group = (GLuint) (e[i].group % ((size_t) -1));
				skip = ((!invert && sel.find(group) == sel.end())
						|| (invert && sel.find(group) != sel.end()));
				if(skip) continue;
				glEnd();
				glLoadName(group);
				glBegin(GL_LINES);
			}
			if(skip) continue;
			if(!e[i].sharp) continue;

//			glColor3f(0.5 + cos(2 * M_PI / 20.0 * e[i].group) * 0.5,
//					0.5
//							+ cos(
//									2 * M_PI / 20.0 * e[i].group
//											+ M_PI * 2.0 / 3.0) * 0.5,
//					0.5
//							+ cos(
//									2 * M_PI / 20.0 * e[i].group
//											+ M_PI * 4.0 / 3.0) * 0.5);

			glNormal3f(e[i].n.x, e[i].n.y, e[i].n.z);
			glVertex3f(v[e[i].va].x, v[e[i].va].y, v[e[i].va].z);
			glVertex3f(v[e[i].vb].x, v[e[i].vb].y, v[e[i].vb].z);
		}
	}
	glEnd();
	glPopName();

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
	glPopMatrix();
}

void Hull::PaintVertices(void) const
{

	const double normalscale = 0.1;
	glPushMatrix();
	matrix.GLMultMatrix();
	for(size_t i = 0; i < v.size(); ++i){
		glPushName(i);
		glBegin(GL_POINTS);
		glNormal3f(vn[i].x, vn[i].y, vn[i].z);
		glVertex3f(v[i].x, v[i].y, v[i].z);
		glEnd();
		glPopName();
	}

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
	glPopMatrix();
}

void Hull::PaintSelected(void) const
{
	glPushMatrix();
	matrix.GLMultMatrix();
	glPointSize(10);
	glBegin(GL_POINTS);
	for(std::set <size_t>::iterator n = selected.begin(); n != selected.end();
			++n){
		size_t i = *n;
		glNormal3f(vn[i].x, vn[i].y, vn[i].z);
		glVertex3f(v[i].x, v[i].y, v[i].z);
	}
	glEnd();
	glPointSize(1);
	glPopMatrix();
}

bool Hull::IsClosed(void) const
{
	return (openedges.empty() && openvertices.empty());
}

bool Hull::IsEmpty(void) const
{
	return (v.size() == 0);
}

bool Hull::LoadObj(std::string filename)
{
	std::ifstream in(filename.c_str(), std::ifstream::in | std::ios::binary);
	if(!in.good()){
		return false;
	}
	in >> *this;
	return true;
}

std::istream& operator>>(std::istream &in, Hull &hull)
{
	// The state machine to parse the input stream of a Wavefront .obj file:

//		digraph{ rankdir=LR
//			0 -> 0 [label="\\r \\n \\s"]
//
//			0 -> 1 [label="g m o s u #"]
//			1 -> 1
//			1 -> 0 [label="\\r \\n"]
//
//			0 -> 2 [label="v"]
//			2 -> 3 [label="t n"]
//
//			{2,3} -> 4 -> 4[label="\\s"]
//
//			{2,3,4} -> 5 [label="+ -"]
//			{2,3,4,5} -> 6 -> 6[label="0-9"]
//
//			{2,3,4,5,6} -> 7 [label=", ."]
//
//			7 -> 8 -> 8[label="0-9"]
//
//			{6,7,8} -> 9 [label="e E"]
//			9 -> 10 [label="+ -"]
//			{9,10} -> {10} [label="0-9"]
//
//			{6,7,8,9,10} -> 4 [label="\\s"]
//			{4,6,7,8,10} -> 0 [label="\\r \\n"]
//
//
//			0 -> 11 [label="f"]
//			11 -> 12 -> 12 [label="\\s"]
//
//			{11,12,14,18} -> 13 -> 13 [label="0-9"]
//
//			13 -> 14 -> 14 [label="\\s"]
//			{13,14} -> 15 [label="/"]
//			15 -> 16 -> 16 [label="\\s"]
//
//			{15,16} -> 17 -> 17 [label="0-9"]
//
//			17 -> 18 -> 18 [label="\\s"]
//			{15,16,17,18} -> 19 [label="/"]
//			19 -> 20 -> 20 [label="\\s"]
//
//			{19,20} -> 21 -> 21 [label="0-9"]
//
//			21 -> 12 [label="\\s"]
//			{12,13,14,17,18,21} -> 0 [label="\\r \\n"]
//			}

	const size_t buffersize = 1048576;

	char *buffer = new char[buffersize];
	if(buffer == NULL) throw(std::runtime_error(
			"operator>>(std::istream &in, Hull &hull) - Out of memory."));
	size_t charsread;

	hull.Clear();

	int_fast8_t state = 0;
	char command = 0;
	std::vector <double> value;
	std::vector <int> index_v;
	std::vector <int> index_t;
	std::vector <int> index_n;
	std::vector <Vector3> tempnormals;
	double tempvalue;
	int tempindex;
	double factor = 1.0;
	bool negative = false;
	bool exponentnegative = false;
	int exponent = 0;
	do{
		in.read(buffer, buffersize);
		charsread = in.gcount();

		for(size_t n = 0; n < charsread; ++n){
			const char c = buffer[n];

			// State changes according to the graph above
			int_fast8_t nextstate = -1;
			switch(state){
			case 0:
				if(c == '\r' || c == '\n' || c == ' ' || c == '\t') nextstate =
						0;
				if(c == 'g' || c == 'm' || c == 'o' || c == 's' || c == 'u'
						|| c == '#') nextstate = 1;
				if(c == 'v') nextstate = 2;
				if(c == 'f') nextstate = 11;
				break;
			case 1:
				if(c == '\r' || c == '\n')
					nextstate = 0;
				else
					nextstate = 1;
				break;
			case 2:
				if(c == 't' || c == 'n') nextstate = 3;
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '+' || c == '-') nextstate = 5;
				if(c >= '0' && c <= '9') nextstate = 6;
				if(c == ',' || c == '.') nextstate = 7;
				break;
			case 3:
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '+' || c == '-') nextstate = 5;
				if(c >= '0' && c <= '9') nextstate = 6;
				if(c == ',' || c == '.') nextstate = 7;

				break;
			case 4:
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '+' || c == '-') nextstate = 5;
				if(c >= '0' && c <= '9') nextstate = 6;
				if(c == ',' || c == '.') nextstate = 7;
				if(c == '\r' || c == '\n') nextstate = 0;
				break;
			case 5:
				if(c >= '0' && c <= '9') nextstate = 6;
				if(c == ',' || c == '.') nextstate = 7;
				break;
			case 6:
				if(c >= '0' && c <= '9') nextstate = 6;
				if(c == ',' || c == '.') nextstate = 7;
				if(c == 'e' || c == 'E') nextstate = 9;
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '\r' || c == '\n') nextstate = 0;
				break;
			case 7:
				if(c >= '0' && c <= '9') nextstate = 8;
				if(c == 'e' || c == 'E') nextstate = 9;
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '\r' || c == '\n') nextstate = 0;
				break;
			case 8:
				if(c >= '0' && c <= '9') nextstate = 8;
				if(c == 'e' || c == 'E') nextstate = 9;
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '\r' || c == '\n') nextstate = 0;
				break;
			case 9:
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c == '+' || c == '-') nextstate = 10;
				if(c >= '0' && c <= '9') nextstate = 10;
				break;
			case 10:
				if(c >= '0' && c <= '9') nextstate = 10;
				if(c == ' ' || c == '\t') nextstate = 4;
				if(c == '\r' || c == '\n') nextstate = 0;
				break;
			case 11:
				if(c == ' ' || c == '\t') nextstate = 12;
				if(c >= '0' && c <= '9') nextstate = 13;
				break;
			case 12:
				if(c == ' ' || c == '\t') nextstate = 12;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 13;
				break;
			case 13:
				if(c == ' ' || c == '\t') nextstate = 14;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 13;
				if(c == '/') nextstate = 15;
				break;
			case 14:
				if(c == ' ' || c == '\t') nextstate = 14;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 13;
				if(c == '/') nextstate = 15;
				break;
			case 15:
				if(c == ' ' || c == '\t') nextstate = 16;
				if(c >= '0' && c <= '9') nextstate = 17;
				if(c == '/') nextstate = 19;
				break;
			case 16:
				if(c == ' ' || c == '\t') nextstate = 16;
				if(c >= '0' && c <= '9') nextstate = 17;
				if(c == '/') nextstate = 19;
				break;
			case 17:
				if(c == ' ' || c == '\t') nextstate = 18;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 17;
				if(c == '/') nextstate = 19;
				break;
			case 18:
				if(c == ' ' || c == '\t') nextstate = 18;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 13;
				if(c == '/') nextstate = 19;
				break;
			case 19:
				if(c == ' ' || c == '\t') nextstate = 20;
				if(c >= '0' && c <= '9') nextstate = 21;
				break;
			case 20:
				if(c == ' ' || c == '\t') nextstate = 20;
				if(c >= '0' && c <= '9') nextstate = 21;
				break;
			case 21:
				if(c == ' ' || c == '\t') nextstate = 12;
				if(c == '\r' || c == '\n') nextstate = 0;
				if(c >= '0' && c <= '9') nextstate = 21;
				break;
			default:
				delete[] buffer;
				throw(std::logic_error(
						"__FILE__ : LoadObj: Statemachine has invalid state."));
			}

			if(nextstate == -1){
				// Parsing error in file, maybe broken file or not a Wavefron OBJ file.
				// Normally at every node in the graph there should be a next node, if the
				// fileformat is valid.
				delete[] buffer;
				std::ostringstream temp;
				temp
						<< "operator>>(std::istream &in, Hull &hull) - Error in file @ ";
				temp << n << " (" << charsread << ")";
				throw(std::runtime_error(temp.str()));
			}

			// Actions associated with the state changes
			if(state == 0 && nextstate == 2){
				command = 'v';
				tempvalue = 0.0;
				factor = 1.0;
				negative = false;
				exponent = 0;
				exponentnegative = false;
			}
			if(state == 2 && nextstate == 3) command = c;
			if(nextstate == 5) negative = (c == '-');
			if(nextstate == 6 || nextstate == 8) tempvalue = tempvalue * 10
					+ (double) (c - '0');
			if(nextstate == 8) factor /= 10;
			if(nextstate == 10){
				if(state == 9) exponentnegative = (c == '-');
				if(c >= '0' && c <= '9'){
					if(state == 10) exponent *= 10;
					exponent += (int) (c - '0');
				}
			}
			if((nextstate == 4 || nextstate == 0) && state >= 6 && state <= 10){
				double val = (negative? -tempvalue : tempvalue) * factor;
				if(exponent != 0){
					if(exponentnegative) exponent = -exponent;
					val *= exp(M_LN10 * (double) exponent);
				}
				value.push_back(val);
				tempvalue = 0.0;
				factor = 1.0;
				negative = false;
				exponent = 0;
				exponentnegative = false;
			}
			if(nextstate == 0 && state >= 4 && state <= 10){
				const double x = (value.size() > 0)? value[0] : 0.0;
				const double y = (value.size() > 1)? value[1] : 0.0;
				const double z = (value.size() > 2)? value[2] : 0.0;
				if(command == 'v') hull.v.push_back(Vector3(x, y, z));
				if(command == 'n') tempnormals.push_back(Vector3(x, y, z));
				// Ignore 't' for now. Texturecoordinates are not interpreted yet.
				value.clear();
			}

			if(state == 0 && nextstate == 11){
				command = 'f';
				tempindex = 0;
			}
			if(nextstate == 13 || nextstate == 17 || nextstate == 21) tempindex =
					tempindex * 10 + (int) (c - '0');
			if(state == 13 && nextstate != 13){
				index_v.push_back(tempindex - 1);
				tempindex = 0;
			}
			if(state == 17 && nextstate != 17){
				index_t.push_back(tempindex - 1);
				tempindex = 0;
			}
			if(state == 21 && nextstate != 21){
				index_n.push_back(tempindex - 1);
				tempindex = 0;
			}
			if(state >= 11 && nextstate == 0){

				if(index_v.size() >= 3){
					Hull::Triangle tempt;
					tempt.va = index_v[0];
					tempt.vb = index_v[1];
					tempt.vc = index_v[2];
					tempt.ea = hull.FindEdge(tempt.va, tempt.vb);
					tempt.eb = hull.FindEdge(tempt.vb, tempt.vc);
					tempt.ec = hull.FindEdge(tempt.vc, tempt.va);
					tempt.n = tempnormals[index_n[0]];

					size_t tindex = hull.t.size();
					hull.t.push_back(tempt);
					if(!hull.e[tempt.ea].AttachTriangle(tindex)) hull.openedges.erase(
							tempt.ea);
					if(!hull.e[tempt.eb].AttachTriangle(tindex)) hull.openedges.erase(
							tempt.eb);
					if(!hull.e[tempt.ec].AttachTriangle(tindex)) hull.openedges.erase(
							tempt.ec);
				}
				index_v.clear();
				index_t.clear();
				index_n.clear();
			}

			state = nextstate;
		}
	}while(charsread == buffersize);
	delete[] buffer;

	// Calculate missing normals
	hull.vn.assign(hull.v.size(), Vector3(0, 0, 0));
	for(size_t i = 0; i < hull.e.size(); ++i){
		if(hull.e[i].trianglecount == 0) continue;
		Vector3 temp = hull.t[hull.e[i].ta].n;
		if(hull.e[i].trianglecount > 1) temp += hull.t[hull.e[i].tb].n;
		temp.Normalize();
		hull.e[i].n = temp;
		hull.vn[hull.e[i].va] += temp;
		hull.vn[hull.e[i].vb] += temp;
	}
	for(size_t i = 0; i < hull.vn.size(); ++i)
		hull.vn[i].Normalize();

	return in;
}

void Hull::SaveObj(std::string filename) const
{
	std::ofstream out(filename.c_str(), std::ofstream::out);
	out << *this;
}

std::ostream& operator<<(std::ostream &out, const Hull &hull)
{
	for(size_t i = 0; i < hull.v.size(); ++i)
		out << "v " << hull.v[i].x << " " << hull.v[i].y << " " << hull.v[i].z
				<< "\n";
	for(size_t i = 0; i < hull.vn.size(); ++i)
		out << "vn " << hull.vn[i].x << " " << hull.vn[i].y << " "
				<< hull.vn[i].z << "\n";
	out << "s off\n";
	for(size_t i = 0; i < hull.t.size(); ++i)
		out << "f " << hull.t[i].va + 1 << "//" << hull.t[i].va + 1 << " "
				<< hull.t[i].vb + 1 << "//" << hull.t[i].vb + 1 << " "
				<< hull.t[i].vc + 1 << "//" << hull.t[i].vc + 1 << "\n";
	return out;
}

void Hull::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	std::transform(v.begin(), v.end(), v.begin(), matrix);
	for(size_t i = 0; i < vn.size(); i++)
		vn[i] = matrix.TransformNoShift(vn[i]);
	for(size_t i = 0; i < e.size(); i++)
		e[i].n = matrix.TransformNoShift(e[i].n);
	for(size_t i = 0; i < t.size(); i++)
		t[i].n = matrix.TransformNoShift(t[i].n);

	if(matrix.CheckOrientation() == AffineTransformMatrix::lhs){
		for(size_t i = 0; i < t.size(); i++){
			std::swap(t[i].va, t[i].vb);
			std::swap(t[i].eb, t[i].ec);
		}
	}
}

void Hull::ApplyTransformation(void)
{
	this->ApplyTransformation(this->matrix);
	this->matrix.SetIdentity();
}

void Hull::CopyFrom(const Geometry &geometry)
{
	Clear();
	AddTrianglesFrom(geometry);
	this->matrix = geometry.matrix;
//	wxLogMessage(
//			wxString::Format(_T("V: %u E: %u T: %u"), v.size(),
//					e.size(), t.size()));
}

void Hull::AddTrianglesFrom(const Geometry &geometry)
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

size_t Hull::Size(void) const
{
	return v.size();
}

Vector3 Hull::PlaneProjection(const Vector3& a, const Vector3& b, Vector3 n,
		double d)
{
	// Assume, that n is of length 1
	// Project a onto the normal vector of the plane, distance relative to the center
	const double sa = n.Dot(a) - d;
	const double sb = n.Dot(b) - d;
	if(sa - sb == 0) return (a + b) / 2;
	// Project the line from a to b onto the plane, return the intersecting point
	return (b * sa - a * sb) / (sa - sb);
}

Polygon3 Hull::IntersectPlane(Vector3 n, double d) const
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

		const Vector3 a = v[e[ne].va];
		const Vector3 b = v[e[ne].vb];
		const double sa = n.Dot(a) - d;
		const double sb = n.Dot(b) - d;
		const double f = (sa - sb == 0)? (0.5) : (sa / (sa - sb));

		temp.InsertPoint(a + (b - a) * f,
				(vn[e[ne].va] + (vn[e[ne].vb] - vn[e[ne].va]) * f).Normal());

//		temp.InsertPoint(PlaneProjection(a, b, n, d));
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

	//TODO: If edges is not yet empty, there is more than a single loop in the cutting plane.
	// for(std::set <size_t>::iterator it = edges.begin(); it != edges.end(); ++it){
	//   ...
	// }

	temp.Close();
	return temp;
}

Vector3 Hull::IntersectArrow(Vector3 p0, Vector3 dir) const
{
	for(size_t i = 0; i < t.size(); ++i){
		const Vector3 a = v[t[i].va];
		const Vector3 b = v[t[i].vb];
		const Vector3 c = v[t[i].vc];
		// Check if point of (p0 + x*dir) lies inside the triangle
		if(((b - a) * (p0 - a)).Dot(dir) < 0) continue;
		if(((c - b) * (p0 - b)).Dot(dir) < 0) continue;
		if(((a - c) * (p0 - c)).Dot(dir) < 0) continue;
		// Find intersection point
		// solve((p0x+x*dirx)*nx + (p0y+x*diry)*ny + (p0z+x*dirz)*nz = ax*nx + ay*ny + az*nz, x);
		const double den = t[i].n.Dot(dir);
		const double x = t[i].n.Dot(a - p0) / den;
		return p0 + dir * x;
	}
	return Vector3();
}

void Hull::CalcNormals(void)
{
	// Start with triangle normals
	for(size_t i = 0; i < t.size(); ++i){
		Vector3 temp = (v[t[i].vb] - v[t[i].va]) * (v[t[i].vc] - v[t[i].vb]);
		temp.Normalize();
		t[i].n = temp;
	}
	// Zero vertex normals
	for(size_t i = 0; i < vn.size(); ++i)
		vn[i].Zero();
	for(size_t i = 0; i < e.size(); ++i){
		// For edges connected to triangles:
		if(e[i].trianglecount == 0) continue;
		// Average triangle normals to edge normals
		Vector3 temp = t[e[i].ta].n;
		if(e[i].trianglecount > 1) temp += t[e[i].tb].n;
		temp.Normalize();
		e[i].n = temp;
		// Propagate edge normals to vertex normals
		const size_t a = e[i].va;
		const size_t b = e[i].vb;
		vn[a] += temp;
		vn[b] += temp;
	}
	// Normalize all vertex normals
	for(size_t i = 0; i < vn.size(); ++i)
		vn[i].Normalize();
	// Use vertex normals for edges not belonging to triangles
	for(size_t i = 0; i < e.size(); ++i){
		if(e[i].trianglecount != 0) continue;
		Vector3 temp = vn[e[i].va] + vn[e[i].vb];
		temp.Normalize();
		e[i].n = temp;
	}
}

void Hull::CalcGroups(void)
{
	// Every edge that connects two triangles that are oriented
	// more than 25 degrees relative to each other is considered
	// a sharp edge.
	//TODO: Make this a parameter in the import settings.
	const float sharplimit = cos(25.0 / 180.0 * M_PI);

	// Set sharp edges based on enclosed angle
	for(size_t i = 0; i < e.size(); ++i){
		if(e[i].trianglecount <= 1){
			e[i].sharp = true;
		}else{
			if(t[e[i].ta].n.Dot(t[e[i].tb].n) < sharplimit){
				e[i].sharp = true;
			}else{
				e[i].sharp = false;
			}
		}
	}

	// Reset all triangle to group 0
	for(size_t i = 0; i < t.size(); ++i)
		t[i].group = 0;

	size_t currentGroup = 0;

	for(size_t i = 0; i < t.size(); ++i){
		if(t[i].group != 0) continue;

		++currentGroup;
		std::set <size_t> checklist;
		checklist.insert(i);
		while(!checklist.empty()){
			size_t j = *(checklist.begin());
			{
				const size_t k = t[j].ea;
				if(!e[k].sharp && e[k].trianglecount >= 2){
					size_t p = e[k].OtherTriangle(j);
					if(t[p].group == 0) checklist.insert(p);
				}
			}
			{
				const size_t k = t[j].eb;
				if(!e[k].sharp && e[k].trianglecount >= 2){
					size_t p = e[k].OtherTriangle(j);
					if(t[p].group == 0) checklist.insert(p);
				}
			}
			{
				const size_t k = t[j].ec;
				if(!e[k].sharp && e[k].trianglecount >= 2){
					size_t p = e[k].OtherTriangle(j);
					if(t[p].group == 0) checklist.insert(p);
				}
			}
			t[j].group = currentGroup;
			checklist.erase(j);
		}

	}

	// Count the number of sharp edges ending or starting in each vertex.
	// Store the first two sharp edges connecting to a vertex.
	std::vector <size_t> vecount;
	std::vector <size_t> vea;
	std::vector <size_t> veb;
	vecount.assign(v.size(), 0);
	vea.resize(v.size());
	veb.resize(v.size());
	for(size_t n = 0; n < e.size(); ++n){
		if(!e[n].sharp) continue;
		const size_t ja = e[n].va;
		const size_t jb = e[n].vb;
		vecount[ja]++;
		if(vecount[ja] == 1) vea[ja] = n;
		if(vecount[ja] == 2) veb[ja] = n;
		vecount[jb]++;
		if(vecount[jb] == 1) vea[jb] = n;
		if(vecount[jb] == 2) veb[jb] = n;
	}

	// Reset all edges to group 0
	for(size_t n = 0; n < e.size(); ++n)
		e[n].group = 0;

	// Assign groups
	currentGroup = 0;
	for(size_t n = 0; n < e.size(); ++n){
		if(e[n].group != 0 || !e[n].sharp) continue;
		currentGroup++;
		e[n].group = currentGroup;

		// Forward pass
		{
			size_t m = n;
			size_t i = e[m].va;
			while(vecount[i] == 2){
				if(vea[i] == m){
					m = veb[i];
				}else{
					m = vea[i];
				}
				if(e[m].group != 0) break;
				i = e[m].OtherVertex(i);
				e[m].group = currentGroup;
			}
		}
		// Backward pass
		{
			size_t m = n;
			size_t i = e[m].vb;
			while(vecount[i] == 2){
				if(veb[i] == m){
					m = vea[i];
				}else{
					m = veb[i];
				}
				if(e[m].group != 0) break;
				i = e[m].OtherVertex(i);
				e[m].group = currentGroup;
			}
		}
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

size_t Hull::Select(std::set <size_t>& select)
{
	selected = select;
	std::set <size_t>::iterator n = selected.upper_bound(v.size());
	if(n != selected.end()) selected.erase(n, selected.end());
	return selected.size();
}

const Vector3& Hull::operator [](size_t index) const
{
	return v[index];
}

Vector3& Hull::operator [](size_t index)
{
	return v[index];
}
