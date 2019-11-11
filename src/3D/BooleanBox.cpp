///////////////////////////////////////////////////////////////////////////////
// Name               : BooleanBox.cpp
// Purpose            : Boolean operations on a small number of cubes
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "BooleanBox.h"

#include <GL/gl.h>
#include <wx/log.h>

#include "Vector3.h"

BooleanBox::BooleanBox()
{
	bufferSizeIntersect = 10;
	bufferSizeOccupied = 1000;
	pX = new float[bufferSizeIntersect];
	pY = new float[bufferSizeIntersect];
	pZ = new float[bufferSizeIntersect];
	occupied = new bool[bufferSizeOccupied];
	SetSize(1.0, 1.0, 1.0);
}

BooleanBox::BooleanBox(float sx, float sy, float sz)
{
	bufferSizeIntersect = 10;
	bufferSizeOccupied = 1000;
	pX = new float[bufferSizeIntersect];
	pY = new float[bufferSizeIntersect];
	pZ = new float[bufferSizeIntersect];
	occupied = new bool[bufferSizeOccupied];

	SetSize(sx, sy, sz);
}

BooleanBox::BooleanBox(float x1, float y1, float z1, float x2, float y2,
		float z2)
{
	bufferSizeIntersect = 10;
	bufferSizeOccupied = 1000;
	pX = new float[bufferSizeIntersect];
	pY = new float[bufferSizeIntersect];
	pZ = new float[bufferSizeIntersect];
	occupied = new bool[bufferSizeOccupied];

	if(x1 > x2) std::swap(x1, x2);
	if(y1 > y2) std::swap(y1, y2);
	if(z1 > z2) std::swap(z1, z2);

	SetSize(x2 - x1, y2 - y1, z2 - z1);
	matrix.TranslateGlobal(x1, y1, z1);
}

BooleanBox::BooleanBox(const BooleanBox& other)
{
	nx = other.nx;
	ny = other.ny;
	nz = other.nz;

	bufferSizeIntersect = other.bufferSizeIntersect;
	if(bufferSizeIntersect <= nx) bufferSizeIntersect = nx + 1;
	if(bufferSizeIntersect <= ny) bufferSizeIntersect = ny + 1;
	if(bufferSizeIntersect <= nz) bufferSizeIntersect = nz + 1;

	// If the content of the box is copied anyway, this can also be used
	// to keep the buffers from overflowing.
	bufferSizeIntersect += 10;

	pX = new float[bufferSizeIntersect];
	pY = new float[bufferSizeIntersect];
	pZ = new float[bufferSizeIntersect];

	for(unsigned int n = 0; n <= other.nx; n++)
		pX[n] = other.pX[n];
	for(unsigned int n = 0; n <= other.ny; n++)
		pY[n] = other.pY[n];
	for(unsigned int n = 0; n <= other.nz; n++)
		pZ[n] = other.pZ[n];

	bufferSizeOccupied = other.bufferSizeOccupied;
	if(bufferSizeOccupied < (nx * ny * nz)) bufferSizeOccupied = nx * ny * nz;

	// The +1000 should be something cubic, but then it would get very big very fast.
	// I intend to use this class only for a handfull of boxes.
	bufferSizeOccupied += 1000;

	occupied = new bool[bufferSizeOccupied];
	const unsigned int N = nx * ny * nz;
	for(unsigned int n = 0; n < N; n++)
		occupied[n] = other.occupied[n];
}

BooleanBox& BooleanBox::operator =(const BooleanBox &other)
{
	if(&other == this) return *this;
	nx = other.nx;
	ny = other.ny;
	nz = other.nz;
	bufferSizeIntersect = other.bufferSizeIntersect;
	if(bufferSizeIntersect <= nx) bufferSizeIntersect = nx + 1;
	if(bufferSizeIntersect <= ny) bufferSizeIntersect = ny + 1;
	if(bufferSizeIntersect <= nz) bufferSizeIntersect = nz + 1;

	// If the content of the box is copied anyway, this can also be used
	// to keep the buffers from overflowing.
	bufferSizeIntersect += 10;
	if(pX != NULL) delete[] pX;
	pX = new float[bufferSizeIntersect];
	if(pY != NULL) delete[] pY;
	pY = new float[bufferSizeIntersect];
	if(pZ != NULL) delete[] pZ;
	pZ = new float[bufferSizeIntersect];

	for(unsigned int n = 0; n <= other.nx; n++)
		pX[n] = other.pX[n];
	for(unsigned int n = 0; n <= other.ny; n++)
		pY[n] = other.pY[n];
	for(unsigned int n = 0; n <= other.nz; n++)
		pZ[n] = other.pZ[n];

	bufferSizeOccupied = other.bufferSizeOccupied;
	if(bufferSizeOccupied < (nx * ny * nz)) bufferSizeOccupied = nx * ny * nz;

	// The +1000 should be something cubic, but then it would get very big very fast.
	// I intend to use this class only for a handfull of boxes.
	bufferSizeOccupied += 1000;

	if(occupied != NULL) delete[] occupied;
	occupied = new bool[bufferSizeOccupied];
	const unsigned int N = nx * ny * nz;
	for(unsigned int n = 0; n < N; n++)
		occupied[n] = other.occupied[n];
	return *this;
}

BooleanBox::~BooleanBox()
{
	delete[] pX;
	delete[] pY;
	delete[] pZ;
	delete[] occupied;
}

void BooleanBox::SizeUpIntersect(unsigned int newSize)
{
	if(newSize < 2) return;
	float * tempX = new float[newSize];
	float * tempY = new float[newSize];
	float * tempZ = new float[newSize];
	unsigned int h;
	h = bufferSizeIntersect;
	if(h > newSize) h = newSize;
	for(unsigned int n = 0; n < h; n++){
		tempX[n] = pX[n];
		tempY[n] = pY[n];
		tempZ[n] = pZ[n];
	}
	delete[] pX;
	delete[] pY;
	delete[] pZ;
	pX = tempX;
	pY = tempY;
	pZ = tempZ;
	bufferSizeIntersect = newSize;

	unsigned int n = (newSize - 1) * (newSize - 1) * (newSize - 1);
	if(n > bufferSizeOccupied) SizeUpOccupied(n);
}

void BooleanBox::SizeUpOccupied(unsigned int newSize)
{

	bool * temp = new bool[newSize];
	unsigned int h;
	h = bufferSizeOccupied;
	if(h > newSize) h = newSize;
	for(unsigned int n = 0; n < h; n++)
		temp[n] = occupied[n];
	delete[] occupied;
	occupied = temp;
	bufferSizeOccupied = newSize;
}

void BooleanBox::Paint(bool flipNormals) const
{
	const unsigned int hx = 1;
	const unsigned int hy = nx;
	const unsigned int hz = nx * ny;

	::glPushMatrix();
	matrix.GLMultMatrix();

	::glBegin(GL_QUADS);

	if(flipNormals){
		unsigned int n = 0;
		for(unsigned int iz = 0; iz < nz; iz++){
			for(unsigned int iy = 0; iy < ny; iy++){
				for(unsigned int ix = 0; ix < nx; ix++){
					if(!occupied[n]){
						n++;
						continue;
					}

					// X-
					if(ix == 0 || !occupied[n - hx]){
						::glNormal3f(1, 0, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
					}
					// X+
					if(ix == nx - 1 || !occupied[n + hx]){
						::glNormal3f(-1, 0, 0);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
					}

					// Y-
					if(iy == 0 || !occupied[n - hy]){
						::glNormal3f(0, 1, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
					}
					// Y+
					if(iy == ny - 1 || !occupied[n + hy]){
						::glNormal3f(0, -1, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
					}

					// Z-
					if(iz == 0 || !occupied[n - hz]){
						::glNormal3f(0, 0, 1);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
					}
					// Z+
					if(iz == nz - 1 || !occupied[n + hz]){
						::glNormal3f(0, 0, -1);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
					}
					n++;
				}
			}
		}

	}else{
		unsigned int n = 0;
		for(unsigned int iz = 0; iz < nz; iz++){
			for(unsigned int iy = 0; iy < ny; iy++){
				for(unsigned int ix = 0; ix < nx; ix++){
					if(!occupied[n]){
						n++;
						continue;
					}
					// X-
					if(ix == 0 || !occupied[n - hx]){
						::glNormal3f(-1, 0, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
					}
					// X+
					if(ix == nx - 1 || !occupied[n + hx]){
						::glNormal3f(1, 0, 0);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
					}
					// Y-
					if(iy == 0 || !occupied[n - hy]){
						::glNormal3f(0, -1, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
					}
					// Y+
					if(iy == ny - 1 || !occupied[n + hy]){
						::glNormal3f(0, 1, 0);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
					}
					// Z-
					if(iz == 0 || !occupied[n - hz]){
						::glNormal3f(0, 0, -1);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 0]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 0]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 0]);
					}
					// Z+
					if(iz == nz - 1 || !occupied[n + hz]){
						::glNormal3f(0, 0, 1);
						::glVertex3f(pX[ix + 0], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 0], pZ[iz + 1]);
						::glVertex3f(pX[ix + 1], pY[iy + 1], pZ[iz + 1]);
						::glVertex3f(pX[ix + 0], pY[iy + 1], pZ[iz + 1]);
					}
					n++;
				}
			}
		}
	}
	::glEnd();
	::glPopMatrix();
}

void BooleanBox::NormalizeMatrix(void)
{
	// TODO: Implement this.
	// Change the matrix so that is diagonal except for the elements
	// in 12, 13 and 14 which describe the translation.
	// Also flip and scale the axis accordingly. Reformat the
	// occupied array as well.
}

void BooleanBox::SetSize(float sx, float sy, float sz)
{
	nx = 1;
	ny = 1;
	nz = 1;
	pX[0] = 0;
	pX[1] = sx;
	pY[0] = 0;
	pY[1] = sy;
	pZ[0] = 0;
	pZ[1] = sz;
	occupied[0] = true;
}

BooleanBox& BooleanBox::operator -=(const BooleanBox &rhs)
{
	// Calculate relative position in x, y and z
	const float mx = rhs.matrix[12] - matrix[12];
	const float my = rhs.matrix[13] - matrix[13];
	const float mz = rhs.matrix[14] - matrix[14];

	const float eps = 1e-6; // = 1 um

	// Add extra intersections...
	// ... on the X axis:
	unsigned int n = 0;
	for(unsigned int m = 0; m <= rhs.nx; m++){
		const float rx = rhs.pX[m] + mx;
		if(rx > pX[nx] - eps) break;
		while(rx > pX[n + 1] - eps)
			n++;
		if(rx < pX[n] + eps) continue;

		if(nx + 1 >= bufferSizeIntersect) SizeUpIntersect(nx + 11);

		for(unsigned int i = nx; i > n; i--)
			pX[i + 1] = pX[i];
		pX[n + 1] = rx;
		nx++;
		bool * temp = new bool[bufferSizeOccupied];
		unsigned int i = 0;
		unsigned int j = 0;
		for(unsigned int iz = 0; iz < nz; iz++){
			for(unsigned int iy = 0; iy < ny; iy++){
				for(unsigned int ix = 0; ix < nx; ix++){
					if(ix == n + 1) i--;
					temp[j] = occupied[i];
					i++;
					j++;
				}
			}
		}
		delete[] occupied;
		occupied = temp;
	}
	// ... on the Y axis:
	n = 0;
	for(unsigned int m = 0; m <= rhs.ny; m++){
		const float ry = rhs.pY[m] + my;
		if(ry > pY[ny] - eps) break;
		while(ry > pY[n + 1] - eps)
			n++;
		if(ry < pY[n] + eps) continue;
		if(ny + 1 >= bufferSizeIntersect) SizeUpIntersect(ny + 11);
		for(unsigned int i = ny; i > n; i--)
			pY[i + 1] = pY[i];
		pY[n + 1] = ry;
		ny++;
		bool * temp = new bool[bufferSizeOccupied];
		unsigned int i = 0;
		unsigned int j = 0;
		for(unsigned int iz = 0; iz < nz; iz++){
			for(unsigned int iy = 0; iy < ny; iy++){
				if(iy == n + 1) i -= nx;
				for(unsigned int ix = 0; ix < nx; ix++){
					temp[j] = occupied[i];
					i++;
					j++;
				}
			}
		}
		delete[] occupied;
		occupied = temp;
	}
	// ... on the Z axis:
	n = 0;
	for(unsigned int m = 0; m <= rhs.nz; m++){
		const float rz = rhs.pZ[m] + mz;
		if(rz > pZ[nz] - eps) break;
		while(rz > pZ[n + 1] - eps)
			n++;
		if(rz < pZ[n] + eps) continue;
		if(nz + 1 >= bufferSizeIntersect) SizeUpIntersect(nz + 11);
		for(unsigned int i = nz; i > n; i--)
			pZ[i + 1] = pZ[i];
		pZ[n + 1] = rz;
		nz++;
		bool * temp = new bool[bufferSizeOccupied];
		unsigned int i = 0;
		unsigned int j = 0;
		for(unsigned int iz = 0; iz < nz; iz++){
			if(iz == n + 1) i -= nx * ny;
			for(unsigned int iy = 0; iy < ny; iy++){
				for(unsigned int ix = 0; ix < nx; ix++){
					temp[j] = occupied[i];
					i++;
					j++;
				}
			}
		}
		delete[] occupied;
		occupied = temp;
	}

	// Do the boolean operation
	unsigned int j = 0;
	for(unsigned int jz = 0; jz < rhs.nz; jz++)
		for(unsigned int jy = 0; jy < rhs.ny; jy++)
			for(unsigned int jx = 0; jx < rhs.nx; jx++){
				if(!rhs.occupied[j]){
					j++;
					continue;
				}
				const float rx = rhs.pX[jx] + mx;
				const float ry = rhs.pY[jy] + my;
				const float rz = rhs.pZ[jz] + mz;
				const float ex = rhs.pX[jx + 1] + mx;
				const float ey = rhs.pY[jy + 1] + my;
				const float ez = rhs.pZ[jz + 1] + mz;
				unsigned int i = 0;
				for(unsigned int iz = 0; iz < nz; iz++){
					if(pZ[iz] < rz - eps || pZ[iz + 1] > ez + eps){
						i += nx * ny;
						continue;
					}
					for(unsigned int iy = 0; iy < ny; iy++){
						if(pY[iy] < ry - eps || pY[iy + 1] > ey + eps){
							i += nx;
							continue;
						}
						for(unsigned int ix = 0; ix < nx; ix++){
							if(pX[ix] < rx - eps || pX[ix + 1] > ex + eps){
								i++;
								continue;
							}
							occupied[i] = false;
							i++;
						}
					}
				}
				j++;
			}

//	wxString y;
//	for(i = 0; i < (nx * ny * nz); i++)
//		if(occupied[i])
//			y += _T("#");
//		else
//			y += _T("_");
//
//	y += _T("  ");
//	for(i = 0; i <= nx; i++)
//		y += wxString::Format(_T("%4.1f"), pX[i]);
//
//	y += _T("  ");
//	for(i = 0; i <= ny; i++)
//		y += wxString::Format(_T("%4.1f"), pY[i]);
//
//	y += _T("  ");
//	for(i = 0; i <= nz; i++)
//		y += wxString::Format(_T("%4.1f"), pZ[i]);
//
//	wxLogMessage(y);

	return *this;
}

void BooleanBox::Translate(const AffineTransformMatrix &matrix)
{
	Vector3 temp = matrix.GetOrigin();
	this->matrix.TranslateGlobal(temp.x, temp.y, temp.z);
}
