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
#include <math.h>

ImprinterElement::ImprinterElement()
{
}
ImprinterElement::~ImprinterElement()
{
}
bool ImprinterElement::IsVisible(void)
{
	return (upperLimit > lowerLimit);
}
void ImprinterElement::Set(const ImprinterElement& b)
{
	this->lowerLimitUpside = b.lowerLimitUpside;
	this->upperLimitUpside = b.upperLimitUpside;
	this->lowerLimit = b.lowerLimit;
	this->upperLimit = b.upperLimit;
	this->lowerLimitDownside = b.lowerLimitDownside;
	this->upperLimitDownside = b.upperLimitDownside;
}

void ImprinterElement::Swap(ImprinterElement& b)
{
	ImprinterElement temp;
	temp.Set(*this);
	this->Set(b);
	b.Set(temp);
}

Imprinter::Imprinter(const double sizeX, const double sizeY,
		const double sizeZ, const double resolutionX, const double resolutionY)
{
	field = NULL;
	nx = ny = N = 0;
	sx = sy = sz = 0.0;
	rx = ry = 1.0;

	displayBox = false;
	displayListGenerated = false;
	this->SetupBox(sizeX, sizeY, sizeZ, resolutionX, resolutionY);
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
	this->displayBox = ip.displayBox;
	this->displayListGenerated = false;

	if(ip.N == 0) return;
	this->SetupBox(ip.sx, ip.sy, ip.sz, ip.rx, ip.ry);
	size_t i;
	for(i = 0; i < this->N; i++)
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
	return true;
}

void Imprinter::ClearField(void)
{
	if(field != NULL) delete[] field;
	field = NULL;
	nx = ny = N = 0;
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
	if(N > 0){
		size_t i;
		for(i = 0; i < N; i++)
			this->field[i] = b.field[i];
	}
	return *this;
}

Imprinter & Imprinter::operator+=(const Imprinter &a)
{
	if(this->N != a.N) return *this;
	size_t i;
	for(i = 0; i < N; i++){
		if(!(this->field[i].IsVisible())) this->field[i] = a.field[i];
	}
	return *this;
}

const Imprinter Imprinter::operator+(const Imprinter& a) const
{
	Imprinter temp = *this;
	temp += a;
	return temp;
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
	if(nx < 1) return false;

	if(!SetupField(nx, ny, resolutionX, resolutionY)) return false;

	sx = sizeX;
	sy = sizeY;
	sz = sizeZ;


	// Every element describes the middle of a rx*ry sized element.
	for(size_t i = 0; i < N; i++){
		field[i].upperLimit = sz;
		field[i].lowerLimit = 0.0;
	}

	colorNormal.Set(0.8, 0.4, 0.0);
	colorTodo.Set(0, 0, 0.8);
	colorUnscratched.Set(0.0, 0.8, 0.1);
	return true;
}

void Imprinter::SetupSphere(double radius, const double resolutionX,
		const double resolutionY)
{
	size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;

	sz = radius;

	double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t i, j, p;
	double px, py;
	double d;
	p = 0;
	py = ry / 2;
	for(j = 0; j < ny; j++){
		px = rx / 2;
		for(i = 0; i < nx; i++){
			d = (px - centerX) * (px - centerX) + (py - centerY) * (py
					- centerY);
			d = radius * radius - d;
			if(d >= 0.0)
				d = sqrt(d);
			else
				d = 0;
			field[p].upperLimit = d;
			field[p].lowerLimit = -d;

			px += rx;
			p++;
		}
		py += ry;
	}

}
void Imprinter::SetupCylinder(double radius, double height,
		const double resolutionX, const double resolutionY)
{
	size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;
	sz = height;
	double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t i, j, p;
	double px, py;
	double d;
	p = 0;
	py = ry / 2;
	for(j = 0; j < ny; j++){
		px = rx / 2;
		for(i = 0; i < nx; i++){
			d = (px - centerX) * (px - centerX) + (py - centerY) * (py
					- centerY);
			if(d <= radius * radius){
				field[p].upperLimit = height;
				field[p].lowerLimit = 0.0;
			}else{
				field[p].upperLimit = 0.0;
				field[p].lowerLimit = sz;

			}
			px += rx;
			p++;
		}
		py += ry;
	}
}
void Imprinter::SetupDisc(double radius, const double resolutionX,
		const double resolutionY)
{
	size_t cellsX = ceil(radius / resolutionX) * 2 + 1;
	size_t cellsY = ceil(radius / resolutionY) * 2 + 1;
	if(!SetupField(cellsX, cellsY, resolutionX, resolutionY)) return;

	sz = 5 * FLT_EPSILON;

	double centerX = (ceil(radius / resolutionX) + 0.5) * rx;
	double centerY = (ceil(radius / resolutionY) + 0.5) * ry;

	size_t i, j, p;
	double px, py;
	double d;
	p = 0;
	py = ry / 2;
	for(j = 0; j < ny; j++){
		px = rx / 2;
		for(i = 0; i < nx; i++){
			d = (px - centerX) * (px - centerX) + (py - centerY) * (py
					- centerY);
			if(d <= radius * radius){
				field[p].upperLimit = 5 * FLT_EPSILON;
				field[p].lowerLimit = 0.0;
			}else{
				field[p].upperLimit = 0.0;
				field[p].lowerLimit = sz;
			}
			px += rx;
			p++;
		}
		py += ry;
	}
}

void Imprinter::Limit(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(field[i].lowerLimit < 0.0) field[i].lowerLimit = 0.0;
		if(field[i].upperLimit > sz) field[i].upperLimit = sz;
	}

}

void Imprinter::FoldRaise(const Imprinter &b)
{
	size_t i, j, p, ib, jb, pb, ph;
	size_t cx, cy;
	cx = b.nx / 2;
	cy = b.ny / 2;


	// Init
	for(i = 0; i < N; i++){
		field[i].upperLimitUpside = field[i].upperLimit;
		field[i].lowerLimitUpside = field[i].lowerLimit;

	}

	float h;

	p = 0;
	pb = 0;
	for(j = 0; j < ny; j++){
		for(i = 0; i < nx; i++){
			if(field[p].IsVisible()){
				pb = 0;
				for(jb = 0; jb < b.ny; jb++){
					for(ib = 0; ib < b.nx; ib++){
						if(b.field[pb].IsVisible()){
							if(ib + i >= cx && ib + i < nx + cx && jb + j >= cy
									&& jb + j < ny + cy){

								ph = i + ib - cx + (j + jb - cy) * nx;

								h = field[p].upperLimit
										+ b.field[pb].upperLimit;

								if(h > field[ph].upperLimitUpside) field[ph].upperLimitUpside
										= h;

								h = field[p].lowerLimit
										+ b.field[pb].lowerLimit;

								if(h < field[ph].lowerLimitUpside) field[ph].lowerLimitUpside
										= h;
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
	for(i = 0; i < N; i++){
		field[i].upperLimit = field[i].upperLimitUpside;
		field[i].lowerLimit = field[i].lowerLimitUpside;

	}

}
void Imprinter::FoldReplace(const Imprinter &b)
{
	size_t i, j, p, ib, jb, pb, ph;
	size_t cx, cy;
	cx = b.nx / 2;
	cy = b.ny / 2;


	// Init
	for(i = 0; i < N; i++){
		field[i].upperLimitUpside = field[i].upperLimit;
		field[i].lowerLimitUpside = field[i].lowerLimit;
	}

	p = 0;
	pb = 0;
	for(j = 0; j < ny; j++){
		for(i = 0; i < nx; i++){
			if(field[p].IsVisible()){
				pb = 0;
				for(jb = 0; jb < b.ny; jb++){
					for(ib = 0; ib < b.nx; ib++){
						if(b.field[pb].IsVisible()){
							if(ib + i >= cx && ib + i < nx + cx && jb + j >= cy
									&& jb + j < ny + cy){
								ph = i + ib - cx + (j + jb - cy) * nx;

								field[ph].upperLimitUpside
										= b.field[pb].upperLimit;
								field[ph].lowerLimitUpside
										= b.field[pb].lowerLimit;
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
	for(i = 0; i < N; i++){
		field[i].upperLimit = field[i].upperLimitUpside;
		field[i].lowerLimit = field[i].lowerLimitUpside;
	}

}

void Imprinter::FoldLower(int x, int y, double z, const Imprinter &b)
{
	size_t ib, jb, pb, ph;
	size_t cx, cy;
	cx = b.nx / 2;
	cy = b.ny / 2;

	pb = 0;
	for(jb = 0; jb < b.ny; jb++){
		for(ib = 0; ib < b.nx; ib++){
			if(b.field[pb].IsVisible()){
				if(ib + x >= cx && ib + x < nx + cx && jb + y >= cy && jb + y
						< ny + cy){
					ph = x + ib - cx + (y + jb - cy) * nx;

					if(field[ph].upperLimit > b.field[pb].lowerLimit + z){
						field[ph].upperLimit = b.field[pb].lowerLimit + z;
					}
					if(field[ph].upperLimit < field[ph].lowerLimit){
						field[ph].lowerLimit = sz;
						field[ph].upperLimit = 0.0;
					}
				}
			}
			pb++;
		}
	}
}
void Imprinter::HardInvert(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(field[i].IsVisible()){
			field[i].upperLimit = 0.0;
			field[i].lowerLimit = sz;
		}else{
			field[i].upperLimit = sz;
			field[i].lowerLimit = 0.0;
		}
	}
}

void Imprinter::MaxFilling(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(IsFilled(i)){
			field[i].upperLimit = sz;
			field[i].lowerLimit = 0.0;
		}else{
			field[i].upperLimit = 0.0;
			field[i].lowerLimit = sz;
		}
	}
}

bool Imprinter::IsFilled(int x, int y, double height)
{
	if(x < 0 || y < 0 || x >= nx || y >= ny) return false;
	size_t p = x + y * nx;
	if(field[p].lowerLimit <= height && field[p].upperLimit >= height) return true;
	return false;
}

bool Imprinter::IsFilledAbove(int x, int y, double height)
{
	if(x < 0 || y < 0 || x >= nx || y >= ny) return false;
	size_t p = x + y * nx;


	//	ImprinterElement temp;
	//	temp = field[p];

	if(field[p].upperLimit >= height) return true;
	return false;
}

bool Imprinter::IsFilled(size_t p, double height)
{
	if(p > N) return false;
	if(field[p].lowerLimit <= height && field[p].upperLimit >= height) return true;
	return false;
}
bool Imprinter::IsFilled(size_t p)
{
	if(p > N) return false;
	if(field[p].lowerLimit < field[p].upperLimit) return true;
	return false;
}

bool Imprinter::IsVisible(int x, int y)
{
	if(x < 0 || y < 0 || x >= nx || y >= ny) return false;
	size_t p = x + y * nx;
	if(field[p].lowerLimit <= field[p].upperLimit) return true;
	return false;
}

bool Imprinter::IsVisible(size_t p)
{
	if(p > N) return false;
	if(field[p].lowerLimit <= field[p].upperLimit) return true;
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

double Imprinter::GetMeanLevel(int x, int y)
{
	if(x < 0 || y < 0 || x >= nx || y >= ny) return -1.0;
	size_t p = x + y * nx;
	if(!field[p].IsVisible()) return -1.0;
	return (field[p].upperLimit + field[p].lowerLimit) / 2;
}
double Imprinter::GetMeanLevel(size_t p)
{
	if(p >= N) return -1.0;
	if(!field[p].IsVisible()) return -1.0;
	return (field[p].upperLimit + field[p].lowerLimit) / 2;
}
double Imprinter::GetLevel(double x, double y)
{
	int px, py;
	px = round(x / rx);
	py = round(y / ry);
	if(px < 0 || py < 0 || px >= nx || py >= ny) return -1.0;
	size_t p = px + py * nx;
	if(!field[p].IsVisible()) return -1.0;
	return field[p].lowerLimit;
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

void Imprinter::CleanOutlier(void)
{
	size_t i;
	size_t j;
	double sumu;
	double suml;
	double varu;
	double varl;

	double d;
	for(i = nx; i < (N - nx); i++){
		if(!IsSurrounded(i)){
			j = i - nx - 1;
			sumu = field[i].upperLimit + field[i + 1].upperLimit
					+ field[i + 2].upperLimit;
			suml = field[i].lowerLimit + field[i + 1].lowerLimit
					+ field[i + 2].lowerLimit;
			j += nx;
			sumu += field[i].upperLimit + field[i + 2].upperLimit;
			suml += field[i].lowerLimit + field[i + 2].lowerLimit;
			j += nx;
			sumu += field[i].upperLimit + field[i + 1].upperLimit
					+ field[i + 2].upperLimit;
			suml += field[i].lowerLimit + field[i + 1].lowerLimit
					+ field[i + 2].lowerLimit;

			sumu /= 8.0;
			suml /= 8.0;

			j = i - nx - 1;

			varu = fabs(field[i].upperLimit - sumu) + fabs(
					field[i + 1].upperLimit - sumu) + fabs(
					field[i + 2].upperLimit - sumu);
			varl = fabs(field[i].lowerLimit - suml) + fabs(
					field[i + 1].lowerLimit - suml) + fabs(
					field[i + 2].lowerLimit - suml);
			j += nx;
			varu += fabs(field[i].upperLimit - sumu) + fabs(
					field[i + 2].upperLimit - sumu);
			varl += fabs(field[i].lowerLimit - suml) + fabs(
					field[i + 2].lowerLimit - suml);
			j += nx;
			varu += fabs(field[i].upperLimit - sumu) + fabs(
					field[i + 1].upperLimit - sumu) + fabs(
					field[i + 2].upperLimit - sumu);
			varl += fabs(field[i].lowerLimit - suml) + fabs(
					field[i + 1].lowerLimit - suml) + fabs(
					field[i + 2].lowerLimit - suml);

			varu /= 8.0;
			varl /= 8.0;

			d = fabs(field[i].upperLimit - sumu);
			d -= varu;

			if(fabs(d) > 0.001){
				field[i].upperLimit = sumu;
			}

			d = fabs(field[i].lowerLimit - suml);
			d -= varl;
			if(fabs(d) > 0.001){
				field[i].lowerLimit = suml;
			}

		}
	}

}

void Imprinter::InvertTop(void)
{
	size_t i;
	for(i = 0; i < N; i++){
		if(field[i].IsVisible()){
			if(field[i].upperLimit >= sz - 0.0001){
				field[i].lowerLimit = sz;
				field[i].upperLimit = 0.0;

			}else{
				field[i].lowerLimit = field[i].upperLimit;
				field[i].upperLimit = sz;
			}
		}else{
			field[i].lowerLimit = 0.0;
			field[i].upperLimit = sz;
		}
	}
}

void Imprinter::InvertZ(void)
{
	size_t i;
	float temp;
	for(i = 0; i < N; i++){
		temp = field[i].upperLimit;
		field[i].upperLimit = sz - field[i].lowerLimit;
		field[i].lowerLimit = sz - temp;
	}
}

void Imprinter::FlipX(void)
{
	size_t i, j, p1, p2, c;

	c = ny / 2;
	for(j = 0; j < c; j++){
		p1 = j * nx;
		p2 = (ny - j - 1) * nx;
		for(i = 0; i < nx; i++){
			field[p1].Swap(field[p2]);
			p1++;
			p2++;
		}
	}
	InvertZ();
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

void Imprinter::InsertTriangle(Vector3 a, Vector3 b, Vector3 c, face_t facetype)
{
	double maxz = sz;


	// Sort Vertices by y
	if(a.y > b.y) a.Swap(b);
	if(b.y > c.y) b.Swap(c);
	if(a.y > b.y) a.Swap(b);


	// Project triangle geometry
	int ay = round(a.y / ry); // Starting Point
	int by = round(b.y / ry); // Middle Point
	int cy = round(c.y / ry); // End Point


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
		pxl = round(lx / rx);
		pxs = round(sx / rx);
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

			switch(facetype){

			case Imprinter::other:
				if(xz > field[i * nx + j].upperLimit) field[i * nx + j].upperLimit
						= xz;
				break;

			case Imprinter::facing_down:

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

			case Imprinter::facing_up: // Facing up

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
			case Imprinter::facing_side: // Side (nz==0)


				//TODO: Ignore this case?
				//				if(xz >= maxz){
				//					if(xz < field[i * nx + j].upperLimitUpside) field[i * nx
				//							+ j].upperLimitUpside = xz;
				//					if(xz < field[i * nx + j].lowerLimitUpside) field[i * nx
				//							+ j].lowerLimitUpside = xz;
				//
				//				}else{
				//					if(xz <= 0.0){
				//						if(xz > field[i * nx + j].upperLimitDownside) field[i
				//								* nx + j].upperLimitDownside = xz;
				//						if(xz > field[i * nx + j].lowerLimitDownside) field[i
				//								* nx + j].lowerLimitDownside = xz;
				//
				//					}else{
				//						if(xz > field[i * nx + j].upperLimit) field[i * nx + j].upperLimit
				//								= xz;
				//						if(xz < field[i * nx + j].lowerLimit) field[i * nx + j].lowerLimit
				//								= xz;
				//					}
				//				}

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

		if(!field[i].IsVisible()){
			field[i].lowerLimit = sz;
			field[i].upperLimit = 0.0;
		}
	}
}

void Imprinter::InsertGeometrie(const Geometry *geometry,
		AffineTransformMatrix shift)
{
	size_t i;
	AffineTransformMatrix m = geometry->matrix;
	m = shift * m;

	for(i = 0; i < geometry->triangles.GetCount(); i++){
		Triangle temp = geometry->triangles[i];
		temp.ApplyTransformation(m);

		if(temp.n[0].z < 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				Imprinter::facing_down);
		if(temp.n[0].z == 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				Imprinter::facing_side);
		if(temp.n[0].z > 0.0) InsertTriangle(temp.p[0], temp.p[1], temp.p[2],
				Imprinter::facing_up);

	}
}

void Imprinter::Paint()
{
	if(field == NULL) return;

	if(!displayListGenerated){
		displayListIndex = ::glGenLists(1);
		displayListGenerated = true;
		refresh = true;
	}

	if(refresh){
		::glNewList(displayListIndex, GL_COMPILE_AND_EXECUTE);

		if(field != NULL){

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
		}
		if(displayBox || true){

			double cornerLength = 0.3; // 30% of a side
			double dx = this->sx * cornerLength;
			double dy = this->sy * cornerLength;
			double dz = this->sz * cornerLength;

			::glColor3f(0.8, 0.8, 0.8);

			::glBegin(GL_LINES);

			glNormal3d(0, -M_SQRT2, -M_SQRT2);
			glVertex3d(0, 0, 0);
			glVertex3d(dx, 0, 0);
			glVertex3d(sx, 0, 0);
			glVertex3d(sx - dx, 0, 0);
			glNormal3d(0, M_SQRT2, -M_SQRT2);
			glVertex3d(0, sy, 0);
			glVertex3d(dx, sy, 0);
			glVertex3d(sx, sy, 0);
			glVertex3d(sx - dx, sy, 0);
			glNormal3d(0, M_SQRT2, M_SQRT2);
			glVertex3d(0, sy, sz);
			glVertex3d(dx, sy, sz);
			glVertex3d(sx, sy, sz);
			glVertex3d(sx - dx, sy, sz);
			glNormal3d(0, -M_SQRT2, M_SQRT2);
			glVertex3d(0, 0, sz);
			glVertex3d(dx, 0, sz);
			glVertex3d(sx, 0, sz);
			glVertex3d(sx - dx, 0, sz);

			glNormal3d(-M_SQRT2, 0, -M_SQRT2);
			glVertex3d(0, 0, 0);
			glVertex3d(0, dy, 0);
			glVertex3d(0, sy, 0);
			glVertex3d(0, sy - dy, 0);
			glNormal3d(M_SQRT2, 0, -M_SQRT2);
			glVertex3d(sx, 0, 0);
			glVertex3d(sx, dy, 0);
			glVertex3d(sx, sy, 0);
			glVertex3d(sx, sy - dy, 0);
			glNormal3d(M_SQRT2, 0, M_SQRT2);
			glVertex3d(sx, 0, sz);
			glVertex3d(sx, dy, sz);
			glVertex3d(sx, sy, sz);
			glVertex3d(sx, sy - dy, sz);
			glNormal3d(-M_SQRT2, 0, M_SQRT2);
			glVertex3d(0, 0, sz);
			glVertex3d(0, dy, sz);
			glVertex3d(0, sy, sz);
			glVertex3d(0, sy - dy, sz);

			glNormal3d(-M_SQRT2, -M_SQRT2, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, dz);
			glVertex3d(0, 0, sz);
			glVertex3d(0, 0, sz - dz);
			glNormal3d(M_SQRT2, -M_SQRT2, 0);
			glVertex3d(sx, 0, 0);
			glVertex3d(sx, 0, dz);
			glVertex3d(sx, 0, sz);
			glVertex3d(sx, 0, sz - dz);
			glNormal3d(M_SQRT2, M_SQRT2, 0);
			glVertex3d(sx, sy, 0);
			glVertex3d(sx, sy, dz);
			glVertex3d(sx, sy, sz);
			glVertex3d(sx, sy, sz - dz);
			glNormal3d(-M_SQRT2, M_SQRT2, 0);
			glVertex3d(0, sy, 0);
			glVertex3d(0, sy, dz);
			glVertex3d(0, sy, sz);
			glVertex3d(0, sy, sz - dz);

			::glEnd();

		}
		::glEndList();

		refresh = false;
	}else{
		::glCallList(displayListIndex);
	}
}

