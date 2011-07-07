///////////////////////////////////////////////////////////////////////////////
// Name               : Imprinter.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.07.2011
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "Imprinter.h"
#include <float.h>
#include <GL/gl.h>

ImprinterElement::ImprinterElement()
{
}
ImprinterElement::~ImprinterElement()
{
}

Imprinter::Imprinter(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	field = NULL;
	this->SetupBox(sizeX, sizeY, sizeZ, resolutionX, resolutionY);
}

Imprinter::Imprinter(const Imprinter& ip)
{
	this->field = NULL;
	if(ip.N == 0) return;
	this->SetupBox(ip.sx, ip.sy, ip.sz, ip.rx, ip.ry);
	size_t i;
	for(i = 0; i < this->N; i++)
		this->field[i] = ip.field[i];
	this->colorNormal = ip.colorNormal;
	this->colorTodo = ip.colorTodo;
	this->colorUnscratched = ip.colorUnscratched;
	this->matrix = ip.matrix;
}

Imprinter::~Imprinter()
{
	if(field != NULL) delete[] field;
}

void Imprinter::SetupBox(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	if(field != NULL) delete[] field;
	field = NULL;

	if(sizeX <= 0.0) return;
	if(sizeY <= 0.0) return;
	if(sizeZ <= 0.0) return;

	sx = sizeX;
	sy = sizeY;
	sz = sizeZ;

	if(resolutionX <= 0.0) return;
	if(resolutionY <= 0.0) return;

	rx = resolutionX;
	ry = resolutionY;

	nx = round(sx / rx);
	ny = round(sy / ry);

	if(nx <= 3) return;
	if(nx <= 3) return;

	N = nx * ny;


	// Every element describes the middle of a rx*ry sized element.
	field = new ImprinterElement[N];
	for(size_t i = 0; i < N; i++){
		field[i].upperLimit = sz;
		field[i].lowerLimit = 0.0;
	}

	colorNormal.Set(0.8, 0.4, 0.0);
	colorTodo.Set(0, 0, 0.8);
	colorUnscratched.Set(0.0, 0.8, 0.1);
}

void Imprinter::SetSphere(double radius, const double resolutionX,
		const double resolutionY)
{
	SetupBox(radius * 2, radius * 2, radius * 2, resolutionX, resolutionY);
}
void Imprinter::SetCylinder(double radius, double height,
		const double resolutionX, const double resolutionY)
{
	SetupBox(radius * 2, radius * 2, height, resolutionX, resolutionY);
}
void Imprinter::SetDisc(double radius, const double resolutionX,
		const double resolutionY)
{
	SetupBox(radius * 2, radius * 2, 0, resolutionX, resolutionY);
}
void Imprinter::FoldRaise(const Imprinter *b)
{

}
void Imprinter::FoldReplace(const Imprinter *b)
{

}
void Imprinter::FlipX(void)
{

}
void Imprinter::FlipY(void)
{

}
void Imprinter::Rot90(void)
{

}
void Imprinter::Rot180(void)
{

}
void Imprinter::Rot270(void)
{

}

size_t Imprinter::MemoryUsageInBytes(void)
{
	return N * sizeof(ImprinterElement);
}

void Imprinter::InitImprinting(void)
{
	for(size_t i = 0; i < N; i++){
		field[i].upperLimit = 0.0;
		field[i].lowerLimit = sz;
		field[i].upperLimitUpside = FLT_MAX;
		field[i].lowerLimitUpside = FLT_MAX;
		field[i].upperLimitDownside = -FLT_MAX;
		field[i].lowerLimitDownside = -FLT_MAX;
	}
}

void Imprinter::InsertTriangle(Vector3 a, Vector3 b, Vector3 c, char strategy)
{
	double maxz = sz;


	// Sort Vertices by y
	if(a.y > b.y) a.Swap(b);
	if(b.y > c.y) b.Swap(c);
	if(a.y > b.y) a.Swap(b);


	// Project triangle geometry
	int ay = floor(a.y / ry); // Starting Point
	int by = floor(b.y / ry); // Middle Point
	int cy = floor(c.y / ry); // End Point


	double lx, lz;
	double sx, sz;
	double dlx, dlz;
	double dsx, dsz;


	// Starting positions;
	lx = a.x;
	lz = a.z;
	if(ay == by){
		sx = b.x;
		sz = b.z;
	}else{
		sx = a.x;
		sz = a.z;
	}

	// Increments
	if(ay < cy){
		dlx = (c.x - a.x) / (cy - ay);
		dlz = (c.z - a.z) / (cy - ay);
	}else{
		dlx = 0.0;
		dlz = 0.0;
	}
	if(ay == by){
		if(by < cy){
			dsx = (c.x - b.x) / (cy - by);
			dsz = (c.z - b.z) / (cy - by);
		}else{
			dsx = 0.0;
			dsz = 0.0;
		}
	}else{
		dsx = (b.x - a.x) / (by - ay);
		dsz = (b.z - a.z) / (by - ay);
	}

	// Limit to 0 .. (ny-1)
	if(ay < 0){
		lx = a.x - dlx * ay;
		lz = a.z - dlz * ay;
		// by smaller 0?
		if(by < 0){
			// Calculate new increment
			if(by < cy){
				dsx = (c.x - b.x) / (cy - by);
				dsz = (c.z - b.z) / (cy - by);
			}else{
				dsx = 0.0;
				dsz = 0.0;
			}
			sx = b.x - dsx * by;
			sz = b.z - dsz * by;
		}else{
			sx = a.x - dsx * ay;
			sz = a.z - dsz * ay;
		}
		ay = 0;
	}
	int ey = cy;
	if(ey >= ny) ey = ny - 1;

	int i, j;

	int pxl, pxs;
	double xz;
	double dxz;


	// Loop over y:
	for(i = ay; i <= ey; i++){
		pxl = floor(lx / rx);
		pxs = floor(sx / rx);
		if(pxl > pxs){
			j = pxl;
			pxl = pxs;
			pxs = j;

			xz = sz;
			dxz = (lz - sz) / (pxs - pxl);
		}else{
			xz = lz;
			if(pxs == pxl){
				dxz = 0;
			}else{
				dxz = (sz - lz) / (pxs - pxl);
			}
		}

		// Limit to the inside of the field.
		if(pxl < 0){
			xz -= dxz * pxl;
			pxl = 0;
		}
		if(pxs >= nx) pxs = nx - 1;


		// Loop over x:
		for(j = pxl; j <= pxs; j++){

			switch(strategy){

			case 1:
				if(xz > field[i * nx + j].upperLimit) field[i * nx + j].upperLimit
						= xz;
				break;

			case 2: // Facing down


				if(xz >= maxz){
					if(xz < field[i * nx + j].lowerLimitUpside) field[i * nx
							+ j].lowerLimitUpside = xz;

				}else{
					if(xz <= 0.0){
						if(xz > field[i * nx + j].lowerLimitDownside) field[i
								* nx + j].lowerLimitDownside = xz;

					}else{
						if(xz < field[i * nx + j].lowerLimit) field[i * nx + j].lowerLimit
								= xz;
					}
				}

				break;

			case 3: // Facing up

				if(xz >= maxz){
					if(xz < field[i * nx + j].upperLimitUpside) field[i * nx
							+ j].upperLimitUpside = xz;

				}else{
					if(xz <= 0.0){
						if(xz > field[i * nx + j].upperLimitDownside) field[i
								* nx + j].upperLimitDownside = xz;

					}else{
						if(xz > field[i * nx + j].upperLimit) field[i * nx + j].upperLimit
								= xz;
					}
				}

				break;
			case 4: // Side (nz==0)
				//TODO: Ignore this case?
				break;

			default:
				field[i * nx + j].upperLimit = xz;
				break;
			}

			xz += dxz;
		}

		lx += dlx;
		lz += dlz;
		sx += dsx;
		sz += dsz;


		// Switch to the second short edge
		if(i == by){
			if(by < cy){
				dsx = (c.x - b.x) / (cy - by);
				dsz = (c.z - b.z) / (cy - by);
			}else{
				dsx = 0.0;
				dsz = 0.0;
			}
			sx = b.x;
			sz = b.z;
		}
	}
}

void Imprinter::FinishImprint(void)
{
	for(size_t i = 0; i < N; i++){


		//		if(field[i].upperLimit < field[i].lowerLimit)// Inside is switched
		//		{
		if(field[i].lowerLimitDownside > field[i].upperLimitDownside
				&& field[i].lowerLimitDownside > -FLT_MAX / 2){
			field[i].lowerLimit = 0.0;
		}
		if(field[i].upperLimitUpside < field[i].lowerLimitUpside
				&& field[i].upperLimitUpside < FLT_MAX / 2){
			field[i].upperLimit = sz;
		}
		//		}else{
		//
		//
		//
		//
		//		}
	}
}

void Imprinter::InsertGeometrie(const Geometry *geometry, double shiftZ)
{
	size_t i;
	AffineTransformMatrix m = geometry->matrix;
	m.TranslateGlobal(0, 0, -shiftZ);

	for(i = 0; i < geometry->triangles.GetCount(); i++){
		Triangle temp = geometry->triangles[i];
		temp.ApplyTransformation(m);

		if(temp.n[0].z < 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2], 2);
		if(temp.n[0].z == 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				4);
		if(temp.n[0].z > 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2], 3);

	}
}

void Imprinter::Paint() const
{
	if(field == NULL) return;

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
	::glBegin(GL_QUADS);

	size_t i, j, p = 0;

	float px = 0.0, py = 0;
	for(j = 0; j < ny; j++){
		px = 0.0;
		for(i = 0; i < nx; i++){

			if(field[p].IsVisible()){
				glNormal3f(0, 0, 1);
				glVertex3f(px, py, field[p].upperLimit);
				glVertex3f(px + rx, py, field[p].upperLimit);
				glVertex3f(px + rx, py + ry, field[p].upperLimit);
				glVertex3f(px, py + ry, field[p].upperLimit);

				glNormal3f(0, 0, -1);
				glVertex3f(px, py, field[p].lowerLimit);
				glVertex3f(px + rx, py, field[p].lowerLimit);
				glVertex3f(px + rx, py + ry, field[p].lowerLimit);
				glVertex3f(px, py + ry, field[p].lowerLimit);
			}

			px += rx;
			p++;
		}
		py += ry;
	}

	::glEnd();
	::glPopMatrix();
}

