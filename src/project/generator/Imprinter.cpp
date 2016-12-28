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
///////////////////////////////////////////////////////////////////////////////

#include "Imprinter.h"

#include <float.h>
#include <math.h>

ImprinterElement::ImprinterElement()
{
}
ImprinterElement::~ImprinterElement()
{
}
bool ImprinterElement::IsVisible(void)
{
	return (up > down);
}

void ImprinterElement::Swap(ImprinterElement& b)
{
//	std::swap(this,&b);
	ImprinterElement temp = *this;
	*this = b;
	b = temp;
}

Imprinter::Imprinter(const double sizeX, const double sizeY, const double sizeZ,
		const double resolutionX, const double resolutionY)
{
	field = NULL;
	nx = ny = N = 0;
	sx = sy = sz = 0.0;
	rx = ry = 1.0;

	refresh = true;

	displayListGenerated = false;
	displayListIndex = 0;

	// Elements to show for debugging
	displayAboveUp = false;
	displayAboveDown = false;
	displayField = false;
	displayBelowUp = false;
	displayBelowDown = false;
	this->SetupBox(sizeX, sizeY, sizeZ, resolutionX, resolutionY);
}

Imprinter& Imprinter::operator=(const Imprinter &b)
{
	// Check for self-assignment!
	if(this == &b) // Same object?
	return *this; // Yes, so skip assignment, and just return *this.

	if(this->N != b.N){
		if(this->field != NULL) delete[] this->field;

		if(b.N > 0){
			this->N = b.N;
			this->field = new ImprinterElement[this->N];
		}
	}
	this->rx = b.rx;
	this->ry = b.ry;
	this->nx = b.nx;
	this->ny = b.ny;
	this->sx = b.sx;
	this->sy = b.sy;
	this->sz = b.sz;
	this->colorNormal = b.colorNormal;
	this->colorTodo = b.colorTodo;
	this->colorUnscratched = b.colorUnscratched;
	this->displayField = b.displayField;
	this->displayAboveDown = b.displayAboveDown;
	this->displayBelowUp = b.displayBelowUp;
	this->displayAboveUp = b.displayAboveUp;
	this->displayBelowDown = b.displayBelowDown;

	if(b.N > 0){
		for(size_t i = 0; i < b.N; i++)
			this->field[i] = b.field[i];
	}
	refresh = true;
	return *this;
}

Imprinter::Imprinter(const Imprinter& ip)
{
	this->field = NULL;
	this->nx = this->ny = this->N = 0;
	this->sx = this->sy = this->sz = 0.0;
	this->rx = this->ry = 1.0;
	this->colorNormal = ip.colorNormal;
	this->colorTodo = ip.colorTodo;
	this->colorUnscratched = ip.colorUnscratched;
	this->displayListGenerated = false;
	this->displayListIndex = 0;
	this->displayField = ip.displayField;

	this->displayAboveDown = ip.displayAboveDown;
	this->displayBelowUp = ip.displayBelowUp;
	this->displayAboveUp = ip.displayAboveUp;
	this->displayBelowDown = ip.displayBelowDown;

	this->refresh = true;

	if(ip.N == 0) return;
	this->SetupBox(ip.sx, ip.sy, ip.sz, ip.rx, ip.ry);
	for(size_t i = 0; i < this->N; i++)
		this->field[i] = ip.field[i];
}

Imprinter::~Imprinter()
{
	if(displayListGenerated){
		::glDeleteLists(displayListIndex, 1);
	}

	if(field != NULL) delete[] field;
}

bool Imprinter::SetupField(const size_t sizeX, const size_t sizeY,
		const double resolutionX, const double resolutionY)
{
	if(field != NULL) delete[] field;
	field = NULL;

	if(sizeX < 1) return false;
	if(sizeY < 1) return false;
	if(resolutionX <= 0.0) return false;
	if(resolutionY <= 0.0) return false;

	rx = resolutionX;
	ry = resolutionY;
	nx = sizeX;
	ny = sizeY;

	sx = (double) nx * rx;
	sy = (double) ny * ry;
	N = nx * ny;

	field = new ImprinterElement[N];
	refresh = true;
	return true;
}

void Imprinter::ClearField(void)
{
	if(field != NULL) delete[] field;
	field = NULL;
	nx = ny = N = 0;
	refresh = true;
}

size_t Imprinter::MemoryUsageInBytes(void) const
{
	return N * sizeof(ImprinterElement);
}

void Imprinter::Refresh()
{
	refresh = true;
}

void Imprinter::Paint() const
{
	if(field == NULL) return;

	if(!displayListGenerated){
		displayListIndex = ::glGenLists(1);
		displayListGenerated = true;
		refresh = true;
	}

	const double rx2 = rx / 2.0;
	const double ry2 = ry / 2.0;

	if(!refresh){
		::glCallList(displayListIndex);
		return;
	}
	::glNewList(displayListIndex, GL_COMPILE_AND_EXECUTE);

	if(field != NULL){
		if(displayField){
			::glColor3f(colorNormal.x, colorNormal.y, colorNormal.z);
			::glBegin(GL_QUADS);
			size_t p = 0;
			double py = 0.0;
			for(size_t j = 0; j < ny; j++){
				double px = 0.0;
				for(size_t i = 0; i < nx; i++){

					if(field[p].IsVisible() || false){
						glNormal3f(0, 0, 1);
						glVertex3f(px, py, field[p].up);
						glVertex3f(px + rx, py, field[p].up);
						glVertex3f(px + rx, py + ry, field[p].up);
						glVertex3f(px, py + ry, field[p].up);

						glNormal3f(0, 0, -1);
						glVertex3f(px, py, field[p].down);
						glVertex3f(px, py + ry, field[p].down);
						glVertex3f(px + rx, py + ry, field[p].down);
						glVertex3f(px + rx, py, field[p].down);
					}
					px += rx;
					p++;
				}
				py += ry;
			}
			::glEnd();
		}
		if(displayAboveDown){

			::glColor3f(0.0, 0.0, 0.9);
			::glNormal3f(0, 0, 1);

			::glBegin(GL_LINES);

			size_t p = 0;
			double py = ry2;
			for(size_t j = 0; j < ny; j++){
				double px = rx2;
				for(size_t i = 0; i < nx; i++){

					if(i > 0){
						glVertex3f(px, py, field[p].aboveDown);
						glVertex3f(px - rx, py, field[p - 1].aboveDown);
					}
					if(j > 0){
						glVertex3f(px, py, field[p].aboveDown);
						glVertex3f(px, py - ry, field[p - nx].aboveDown);
					}
					px += rx;
					p++;
				}
				py += ry;
			}
			::glEnd();
		}
		if(displayBelowUp){

			::glColor3f(0.0, 0.9, 0.0);
			::glNormal3f(0, 0, 1);

			::glBegin(GL_LINES);

			size_t p = 0;
			double py = ry2;
			for(size_t j = 0; j < ny; j++){
				double px = rx2;
				for(size_t i = 0; i < nx; i++){

					if(i > 0){
						glVertex3f(px, py, field[p].belowUp);
						glVertex3f(px - rx, py, field[p - 1].belowUp);
					}
					if(j > 0){
						glVertex3f(px, py, field[p].belowUp);
						glVertex3f(px, py - ry, field[p - nx].belowUp);
					}
					px += rx;
					p++;
				}
				py += ry;
			}
			::glEnd();
		}
		if(displayAboveUp){

			::glColor3f(0.0, 0.9, 0.0);
			::glNormal3f(0, 0, 1);

			::glBegin(GL_LINES);

			size_t p = 0;
			double py = ry2;
			for(size_t j = 0; j < ny; j++){
				double px = rx2;
				for(size_t i = 0; i < nx; i++){
					if(i > 0){
						glVertex3f(px, py, field[p].aboveUp);
						glVertex3f(px - rx, py, field[p - 1].aboveUp);
					}
					if(j > 0){
						glVertex3f(px, py, field[p].aboveUp);
						glVertex3f(px, py - ry, field[p - nx].aboveUp);
					}
					px += rx;
					p++;
				}
				py += ry;
			}
			::glEnd();
		}
		if(displayBelowDown){

			::glColor3f(0.9, 0.0, 0.0);
			::glNormal3f(0, 0, 1);

			::glBegin(GL_LINES);

			size_t p = 0;
			double py = ry2;
			for(size_t j = 0; j < ny; j++){
				double px = rx2;
				for(size_t i = 0; i < nx; i++){
					if(i > 0){
						glVertex3f(px, py, field[p].belowDown);
						glVertex3f(px - rx, py, field[p - 1].belowDown);
					}
					if(j > 0){
						glVertex3f(px, py, field[p].belowDown);
						glVertex3f(px, py - ry, field[p - nx].belowDown);
					}
					px += rx;
					p++;
				}
				py += ry;
			}
			::glEnd();
		}
	}

	::glEndList();
	refresh = false;
}

void Imprinter::Empty(void)
{
	for(size_t i = 0; i < N; i++){
		field[i].up = 0;
		field[i].down = sz;
	}
	refresh = true;
}

void Imprinter::InitImprinting(void)
{
	for(size_t i = 0; i < N; i++){
		field[i].aboveUp = FLT_MAX;
		field[i].aboveDown = FLT_MAX;
		field[i].up = -FLT_MAX;
		field[i].down = FLT_MAX;
		field[i].belowUp = -FLT_MAX;
		field[i].belowDown = -FLT_MAX;
	}
	refresh = true;
}

void Imprinter::InsertTriangle(Vector3 a, Vector3 b, Vector3 c, face_t facetype)
{
	double maxz = sz;

	// Sort Vertices by y
	if(a.y > b.y) a.Swap(b);
	if(b.y > c.y) b.Swap(c);
	if(a.y > b.y) a.Swap(b);

	const double rx2 = rx / 2.0;
	const double ry2 = ry / 2.0;

	// Project triangle geometry
	int ay = ceil((a.y - ry2) / ry); // Starting Point
	int by = ceil((b.y - ry2) / ry); // Middle Point
	int cy = floor((c.y - ry2) / ry); // End Point

	if(cy < ay) return; // Triangle completely between two grid lines.

	// Limit points to mapped area
	// If triangle completely outside of mapped area, return.
	if(ay < 0) ay = 0;
	if(ay >= (int) ny) return;
	if(by < 0) by = 0;
	if(by >= (int) ny) by = ny - 1;
	if(cy < 0) return;
	if(cy >= (int) ny) cy = ny - 1;

	// Starting positions and increments (l = long, s = short)
	double lx = a.x;
	double lz = a.z;

	double dlx, dlz;
	if(a.y < c.y){
		dlx = (c.x - a.x) / (c.y - a.y);
		dlz = (c.z - a.z) / (c.y - a.y);
	}else{
		dlx = 0.0;
		dlz = 0.0;
	}

	double sx = a.x;
	double sz = a.z;

	double dsx, dsz;
	if(a.y < b.y){
		dsx = (b.x - a.x) / (b.y - a.y);
		dsz = (b.z - a.z) / (b.y - a.y);
	}else{
		dsx = 0.0;
		dsz = 0.0;
	}

	// Shift starting position onto grid.
	double shift = (ay * ry + ry2 - a.y);
	assert(shift >= 0.0);
	assert(shift < 1.0);

	lx += shift * dlx;
	lz += shift * dlz;
	sx += shift * dsx;
	sz += shift * dsz;

	int px1, px2;
	double xz;
	double dxz;
	double tempX;

	// Loop over y:
	for(int i = ay; i <= cy; i++){
		// Switch to middle point.
		if((i * ry + ry2) > b.y){
			sx = b.x;
			sz = b.z;
			if(b.y < c.y){
				dsx = (c.x - b.x) / (c.y - b.y);
				dsz = (c.z - b.z) / (c.y - b.y);
			}else{
				dsx = 0.0;
				dsz = 0.0;
			}

			shift = (i * ry + ry2 - b.y);
			assert(shift >= 0.0);
			sx += shift * dsx;
			sz += shift * dsz;
		}
		// Move along x-axis.
		if(lx > sx){
			px1 = ceil((sx - rx2) / rx);
			px2 = floor((lx - rx2) / rx);
			xz = sz;
			dxz = (lz - sz) / (lx - sx);
			tempX = sx;
		}else{
			px1 = ceil((lx - rx2) / rx);
			px2 = floor((sx - rx2) / rx);
			xz = lz;
			if(sx == lx){
				dxz = 0.0;
			}else{
				dxz = (sz - lz) / (sx - lx);
			}
			tempX = lx;
		}
		// Limit to the inside of the field.
		if(px2 < 0 || px1 >= (int) nx){
			sx += dsx * ry;
			sz += dsz * ry;
			lx += dlx * ry;
			lz += dlz * ry;
			continue;
		}
		if(px1 < 0) px1 = 0;
		if(px2 >= (int) nx) px2 = nx - 1;

		// Shift z-level
		xz += dxz * (px1 * rx + rx2 - tempX);

		// Loop over x:
		for(int j = px1; j <= px2; j++){

			switch(facetype){
			case Imprinter::facing_down:

				if(xz >= maxz && xz < field[i * nx + j].aboveDown){
					field[i * nx + j].aboveDown = xz;
				}
				if(xz <= 0.0 && xz > field[i * nx + j].belowDown){
					field[i * nx + j].belowDown = xz;
				}
				if(xz >= 0.0 && xz <= maxz && xz < field[i * nx + j].down){
					field[i * nx + j].down = xz;
				}
				break;

			case Imprinter::facing_up:

				if(xz >= maxz && xz < field[i * nx + j].aboveUp){
					field[i * nx + j].aboveUp = xz;
				}
				if(xz <= 0.0 && xz > field[i * nx + j].belowUp){
					field[i * nx + j].belowUp = xz;
				}
				if(xz >= 0.0 && xz <= maxz && xz > field[i * nx + j].up){
					field[i * nx + j].up = xz;
				}
				break;

			case Imprinter::facing_side: // Side (nz==0)
				//TODO: Ignore this case?
				break;

			default:
				if(xz > field[i * nx + j].up) field[i * nx + j].up = xz;
				if(xz < field[i * nx + j].down) field[i * nx + j].down = xz;
				break;
			}
			xz += dxz * rx;
		}
		lx += dlx * ry;
		lz += dlz * ry;
		sx += dsx * ry;
		sz += dsz * ry;
	}
	refresh = true;
}

void Imprinter::InsertGeometrie(const Geometry *geometry,
		const AffineTransformMatrix & shift)
{
	AffineTransformMatrix m = geometry->matrix;
	m = shift * m; // Premultiply the transformation globally.

	for(size_t i = 0; i < geometry->triangles.GetCount(); i++){
		Triangle temp = geometry->triangles[i];
		temp.ApplyTransformation(m);

//		InsertTriangle(temp.p[0], temp.p[1], temp.p[2], Imprinter::other);
//TODO: Test if normals should be recalculated. (E.g. for rotated objects)
		if(temp.n[0].z < 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				Imprinter::facing_down);
//		if(temp.n[0].z == 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
//				Imprinter::facing_side);
		if(temp.n[0].z > 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				Imprinter::facing_up);
	}
	refresh = true;
}

void Imprinter::FinishImprint(void)
{
	for(size_t i = 0; i < N; i++){

		if(field[i].aboveDown > field[i].aboveUp
				&& field[i].aboveUp < FLT_MAX / 2){
			field[i].up = sz;
		}
		if(field[i].belowDown > field[i].belowUp
				&& field[i].belowDown > -FLT_MAX / 2){
			field[i].down = 0.0;
		}
		if(field[i].up < -FLT_MAX / 2 && field[i].down <= sz){
			field[i].up = sz;
		}
		if(field[i].down > FLT_MAX / 2 && field[i].up >= 0.0){
			field[i].down = 0.0;
		}
		if(!field[i].IsVisible()){
			field[i].down = sz;
			field[i].up = 0.0;
		}
	}
	refresh = true;
}

bool Imprinter::SetupBox(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	if(field != NULL) delete[] field;
	field = NULL;

	if(sizeX <= 0.0) return false;
	if(sizeY <= 0.0) return false;
	if(sizeZ <= 0.0) return false;
	if(resolutionX <= 0.0) return false;
	if(resolutionY <= 0.0) return false;

	nx = round(sizeX / resolutionX);
	ny = round(sizeY / resolutionY);
	if(nx < 1) return false;
	if(ny < 1) return false;

	if(!SetupField(nx, ny, resolutionX, resolutionY)) return false;

	sx = sizeX;
	sy = sizeY;
	sz = sizeZ;

	// Every element describes the middle of a rx*ry sized element.
	for(size_t i = 0; i < N; i++){
		field[i].up = sz;
		field[i].down = 0.0;
	}

	colorNormal.Set(0.8, 0.4, 0.0);
	colorTodo.Set(0, 0, 0.8);
	colorUnscratched.Set(0.0, 0.8, 0.1);
	refresh = true;
	return true;
}

void Imprinter::SetupSphere(double radius, const double resolutionX,
		const double resolutionY)
{
	const size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	const size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;

	sz = radius;

	const double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	const double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t p = 0;
	double py = ry / 2;
	for(size_t j = 0; j < ny; j++){
		double px = rx / 2;
		for(size_t i = 0; i < nx; i++){
			double d = (px - centerX) * (px - centerX)
					+ (py - centerY) * (py - centerY);
			d = radius * radius - d;
			if(d >= 0.0)
				d = sqrt(d);
			else
				d = 0;
			field[p].up = d;
			field[p].down = -d;

			px += rx;
			p++;
		}
		py += ry;
	}
	refresh = true;

}

void Imprinter::SetupCylinder(double radius, double height,
		const double resolutionX, const double resolutionY)
{
	const size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	const size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;
	sz = height;
	const double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	const double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t p = 0;
	double py = ry / 2;
	for(size_t j = 0; j < ny; j++){
		double px = rx / 2;
		for(size_t i = 0; i < nx; i++){
			const double d = (px - centerX) * (px - centerX)
					+ (py - centerY) * (py - centerY);
			if(d <= radius * radius){
				field[p].up = height;
				field[p].down = 0.0;
			}else{
				field[p].up = 0.0;
				field[p].down = sz;

			}
			px += rx;
			p++;
		}
		py += ry;
	}
	refresh = true;
}

void Imprinter::SetupDisc(double radius, const double resolutionX,
		const double resolutionY)
{
	const size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	const size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;

	sz = 5 * FLT_EPSILON;

	const double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	const double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t p = 0;
	double py = ry / 2;
	for(size_t j = 0; j < ny; j++){
		double px = rx / 2;
		for(size_t i = 0; i < nx; i++){
			const double d = (px - centerX) * (px - centerX)
					+ (py - centerY) * (py - centerY);
			if(d <= radius * radius){
				field[p].up = 5 * FLT_EPSILON;
				field[p].down = 0.0;
			}else{
				field[p].up = 0.0;
				field[p].down = sz;
			}
			px += rx;
			p++;
		}
		py += ry;
	}
	refresh = true;
}

bool Imprinter::IsFilled(int x, int y, double height)
{
	if(x < 0 || y < 0 || x >= (int) nx || y >= (int) ny) return false;
	size_t p = x + y * nx;
	if(field[p].down <= height && field[p].up >= height) return true;
	return false;
}

bool Imprinter::IsFilledAbove(int x, int y, double height)
{
	if(x < 0 || y < 0 || x >= (int) nx || y >= (int) ny) return false;
	size_t p = x + y * nx;

	//	ImprinterElement temp;
	//	temp = field[p];

	if(field[p].up >= height) return true;
	return false;
}

bool Imprinter::IsFilled(size_t p, double height)
{
	if(p > N) return false;
	if(field[p].down <= height && field[p].up >= height) return true;
	return false;
}

bool Imprinter::IsFilled(size_t p)
{
	if(p > N) return false;
	if(field[p].down < field[p].up) return true;
	return false;
}

bool Imprinter::IsVisible(int x, int y)
{
	if(x < 0 || y < 0 || x >= (int) nx || y >= (int) ny) return false;
	size_t p = x + y * nx;
	if(field[p].down <= field[p].up) return true;
	return false;
}

bool Imprinter::IsVisible(size_t p)
{
	if(p > N) return false;
	if(field[p].down <= field[p].up) return true;
	return false;
}

bool Imprinter::IsOnOuterBorder(size_t p)
{
	if(p < nx) return true;
	if(p >= N) return false;
	if(p >= N - nx) return true;
	size_t h = p % nx;
	if(h == 0) return true;
	if(h == nx - 1) return true;
	return false;
}

bool Imprinter::IsSurrounded(size_t p)
{
	if(IsOnOuterBorder(p)) return false;
	size_t i = p - nx - 1;
	if(!IsFilled(i++)) return false;
	if(!IsFilled(i++)) return false;
	if(!IsFilled(i++)) return false;
	i = i + nx - 3;
	if(!IsFilled(i++)) return false;
	i++;
	if(!IsFilled(i++)) return false;
	i = i + nx - 3;
	if(!IsFilled(i++)) return false;
	if(!IsFilled(i++)) return false;
	if(!IsFilled(i++)) return false;
	return true;
}

double Imprinter::GetMeanLevel(int x, int y)
{
	if(x < 0 || y < 0 || x >= (int) nx || y >= (int) ny) return -1.0;
	size_t p = x + y * nx;
	if(!field[p].IsVisible()) return -1.0;
	return (field[p].up + field[p].down) / 2;
}

double Imprinter::GetMeanLevel(size_t p)
{
	if(p >= N) return -1.0;
	if(!field[p].IsVisible()) return -1.0;
	return (field[p].up + field[p].down) / 2;
}

double Imprinter::GetLevel(double x, double y)
{
	int px, py;
	px = round((x - rx / 2) / rx);
	py = round((y - ry / 2) / ry);
	if(px < 0 || py < 0 || px >= (int) nx || py >= (int) ny) return -1.0;
	size_t p = px + py * nx;
	if(!field[p].IsVisible()) return -1.0;
	return field[p].up;
}

Imprinter & Imprinter::operator+=(const Imprinter &a)
{
	if(this->N != a.N) return *this;
	assert(this->N == a.N);
	for(size_t i = 0; i < N; i++){
		if(!(this->field[i].IsVisible())) this->field[i] = a.field[i];
	}
	refresh = true;
	return *this;
}

const Imprinter Imprinter::operator+(const Imprinter& a) const
{
	Imprinter temp = *this;
	temp += a;
	return temp;
}

void Imprinter::CleanOutlier(void)
{
	//TODO: Check function, it adds outliers instead of removing them.
	return;
	size_t i;
	size_t j;
	double sumu;
	double suml;
	double varu;
	double varl;

	double d;
	for(i = nx; i < (N - nx); i++){
		if(IsSurrounded(i)){
			j = i - nx - 1;
			sumu = field[i].up + field[i + 1].up + field[i + 2].up;
			suml = field[i].down + field[i + 1].down + field[i + 2].down;
			j += nx;
			sumu += field[i].up + field[i + 2].up;
			suml += field[i].down + field[i + 2].down;
			j += nx;
			sumu += field[i].up + field[i + 1].up + field[i + 2].up;
			suml += field[i].down + field[i + 1].down + field[i + 2].down;

			sumu /= 8.0;
			suml /= 8.0;

			j = i - nx - 1;

			varu = fabs(field[i].up - sumu) + fabs(field[i + 1].up - sumu)
					+ fabs(field[i + 2].up - sumu);
			varl = fabs(field[i].down - suml) + fabs(field[i + 1].down - suml)
					+ fabs(field[i + 2].down - suml);
			j += nx;
			varu += fabs(field[i].up - sumu) + fabs(field[i + 2].up - sumu);
			varl += fabs(field[i].down - suml) + fabs(field[i + 2].down - suml);
			j += nx;
			varu += fabs(field[i].up - sumu) + fabs(field[i + 1].up - sumu)
					+ fabs(field[i + 2].up - sumu);
			varl += fabs(field[i].down - suml) + fabs(field[i + 1].down - suml)
					+ fabs(field[i + 2].down - suml);

			varu /= 8.0;
			varl /= 8.0;

			d = fabs(field[i].up - sumu);
			d -= varu;

			if(fabs(d) > 0.001){
				field[i].up = sumu;
			}

			d = fabs(field[i].down - suml);
			d -= varl;
			if(fabs(d) > 0.001){
				field[i].down = suml;
			}

		}
	}
	refresh = true;
}

void Imprinter::Limit(void)
{
	for(size_t i = 0; i < N; i++){
		if(field[i].down < 0.0) field[i].down = 0.0;
		if(field[i].up > sz) field[i].up = sz;
	}
	refresh = true;
}

void Imprinter::FoldRaise(const Imprinter &b)
{
	const size_t cx = b.nx / 2;
	const size_t cy = b.ny / 2;

	// Init
	for(size_t i = 0; i < N; i++){
		field[i].aboveDown = field[i].up;
		field[i].belowUp = field[i].down;
	}

	size_t p = 0;
	for(size_t j = 0; j < ny; j++){
		for(size_t i = 0; i < nx; i++){
			if(field[p].IsVisible()){
				size_t pb = 0;
				for(size_t jb = 0; jb < b.ny; jb++){
					for(size_t ib = 0; ib < b.nx; ib++){
						if(b.field[pb].IsVisible()){
							if(ib + i >= cx && ib + i < nx + cx && jb + j >= cy
									&& jb + j < ny + cy){

								const size_t ph = i + ib - cx
										+ (j + jb - cy) * nx;

								float h = field[p].up + b.field[pb].up;

								if(h > field[ph].aboveDown) field[ph].aboveDown =
										h;

								h = field[p].down + b.field[pb].down;

								if(h < field[ph].belowUp) field[ph].belowUp = h;
							}
						}
						pb++;
					}
				}
			}
			p++;
		}
	}

	// Finish
	for(size_t i = 0; i < N; i++){
		field[i].up = field[i].aboveDown;
		field[i].down = field[i].belowUp;
	}
	refresh = true;
}

void Imprinter::FoldReplace(const Imprinter &b)
{
	const size_t cx = b.nx / 2;
	const size_t cy = b.ny / 2;

	// Init
	for(size_t i = 0; i < N; i++){
		field[i].aboveDown = field[i].up;
		field[i].belowUp = field[i].down;
	}

	size_t p = 0;
	size_t pb = 0;
	for(size_t j = 0; j < ny; j++){
		for(size_t i = 0; i < nx; i++){
			if(field[p].IsVisible()){
				pb = 0;
				for(size_t jb = 0; jb < b.ny; jb++){
					for(size_t ib = 0; ib < b.nx; ib++){
						if(b.field[pb].IsVisible()){
							if(ib + i >= cx && ib + i < nx + cx && jb + j >= cy
									&& jb + j < ny + cy){
								const size_t ph = i + ib - cx
										+ (j + jb - cy) * nx;
								field[ph].aboveDown = b.field[pb].up;
								field[ph].belowUp = b.field[pb].down;
							}
						}
						pb++;
					}
				}
			}
			p++;
		}
	}

	// Finish
	for(size_t i = 0; i < N; i++){
		field[i].up = field[i].aboveDown;
		field[i].down = field[i].belowUp;
	}
	refresh = true;
}

void Imprinter::FoldLower(int x, int y, double z, const Imprinter &b)
{
	const size_t cx = b.nx / 2;
	const size_t cy = b.ny / 2;

	size_t pb = 0;
	for(size_t jb = 0; jb < b.ny; jb++){
		for(size_t ib = 0; ib < b.nx; ib++){
			if(b.field[pb].IsVisible()){
				if(ib + x >= cx && ib + x < nx + cx && jb + y >= cy
						&& jb + y < ny + cy){
					const size_t ph = x + ib - cx + (y + jb - cy) * nx;

					if(field[ph].up > b.field[pb].down + z){
						field[ph].up = b.field[pb].down + z;
					}
					if(field[ph].up < field[ph].down){
						field[ph].down = sz;
						field[ph].up = 0.0;
					}
				}
			}
			pb++;
		}
	}
	refresh = true;
}

void Imprinter::HardInvert(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(field[i].IsVisible()){
			field[i].up = 0.0;
			field[i].down = sz;
		}else{
			field[i].up = sz;
			field[i].down = 0.0;
		}
	}
	refresh = true;
}

void Imprinter::MaxFilling(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(IsFilled(i)){
			field[i].up = sz;
			field[i].down = 0.0;
		}else{
			field[i].up = 0.0;
			field[i].down = sz;
		}
	}
	refresh = true;
}

void Imprinter::InvertTop(void)
{
	for(size_t i = 0; i < N; i++){
		if(field[i].IsVisible()){
			if(field[i].up >= sz - 0.0001){
				field[i].down = sz;
				field[i].up = 0.0;

			}else{
				field[i].down = field[i].up;
				field[i].up = sz;
			}
		}else{
			field[i].down = 0.0;
			field[i].up = sz;
		}
	}
	refresh = true;
}

void Imprinter::InvertZ(void)
{
	for(size_t i = 0; i < N; i++){
		float temp = field[i].up;
		field[i].up = sz - field[i].down;
		field[i].down = sz - temp;
	}
	refresh = true;
}

void Imprinter::FlipX(void)
{
	if(field == NULL) return;
	const size_t c = ny / 2;
	for(size_t j = 0; j < c; j++){
		size_t p1 = j * nx;
		size_t p2 = (ny - j - 1) * nx;
		for(size_t i = 0; i < nx; i++){
			field[p1].Swap(field[p2]);
			p1++;
			p2++;
		}
	}
	InvertZ();
	refresh = true;
}

//void Imprinter::FlipY(void)
//{
//	throw("Imprinter::FlipY - not implemented.");
//	//TODO: Write FlipY
//}
