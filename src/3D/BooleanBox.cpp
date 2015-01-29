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

	// Is the content of the box is copied anyway, this can also be used
	// to keep the buffers from overflowing.
	bufferSizeIntersect += 10;

	pX = new float[bufferSizeIntersect];
	pY = new float[bufferSizeIntersect];
	pZ = new float[bufferSizeIntersect];

	unsigned int n;
	for(n = 0; n <= other.nx; n++)
		pX[n] = other.pX[n];
	for(n = 0; n <= other.ny; n++)
		pY[n] = other.pY[n];
	for(n = 0; n <= other.nz; n++)
		pZ[n] = other.pZ[n];

	bufferSizeOccupied = other.bufferSizeOccupied;
	if(bufferSizeOccupied < (nx * ny * nz)) bufferSizeOccupied = nx * ny * nz;

	// The +1000 should be something cubic, but then it would get very big very fast.
	// I intend to use this class only for a handfull of boxes.
	bufferSizeOccupied += 1000;

	occupied = new bool[bufferSizeOccupied];
	unsigned int N = nx * ny * nz;
	for(n = 0; n < N; n++)
		occupied[n] = other.occupied[n];
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
	unsigned int n;
	float * tempX = new float[newSize];
	float * tempY = new float[newSize];
	float * tempZ = new float[newSize];
	unsigned int h;
	h = bufferSizeIntersect;
	if(h > newSize) h = newSize;
	for(n = 0; n < h; n++){
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

	n = (newSize - 1) * (newSize - 1) * (newSize - 1);
	if(n > bufferSizeOccupied) SizeUpOccupied(n);
}

void BooleanBox::SizeUpOccupied(unsigned int newSize)
{
	unsigned int n;
	bool * temp = new bool[newSize];
	unsigned int h;
	h = bufferSizeOccupied;
	if(h > newSize) h = newSize;
	for(n = 0; n < h; n++)
		temp[n] = occupied[n];
	delete[] occupied;
	occupied = temp;
	bufferSizeOccupied = newSize;
}

void BooleanBox::Paint(bool flipNormals) const
{
	unsigned int ix;
	unsigned int iy;
	unsigned int iz;
	unsigned int hx = 1;
	unsigned int hy = nx;
	unsigned int hz = nx * ny;

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_QUADS);

	unsigned int n = 0;
	if(flipNormals){
		for(iz = 0; iz < nz; iz++){
			for(iy = 0; iy < ny; iy++){
				for(ix = 0; ix < nx; ix++){
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
		for(iz = 0; iz < nz; iz++){
			for(iy = 0; iy < ny; iy++){
				for(ix = 0; ix < nx; ix++){
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

BooleanBox& BooleanBox::operator -=(const BooleanBox& rhs)
{
// Calculate relative position in x, y and z
	float mx = rhs.matrix.a[12] - matrix.a[12];
	float my = rhs.matrix.a[13] - matrix.a[13];
	float mz = rhs.matrix.a[14] - matrix.a[14];

	float eps = 1e-6; // = 1 um

// Add extra intersections...
	float rx, ry, rz;
	unsigned int n, m, i, j, ix, iy, iz;
// ... on the X axis:
	n = 0;
	for(m = 0; m <= rhs.nx; m++){
		rx = rhs.pX[m] + mx;
		if(rx > pX[nx] - eps) break;
		while(rx > pX[n + 1] - eps)
			n++;
		if(rx < pX[n] + eps) continue;

		if(nx + 1 >= bufferSizeIntersect) SizeUpIntersect(nx + 11);

		for(i = nx; i > n; i--)
			pX[i + 1] = pX[i];
		pX[n + 1] = rx;
		nx++;
		bool * temp = new bool[bufferSizeOccupied];
		i = 0;
		j = 0;
		for(iz = 0; iz < nz; iz++){
			for(iy = 0; iy < ny; iy++){
				for(ix = 0; ix < nx; ix++){
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
	for(m = 0; m <= rhs.ny; m++){
		ry = rhs.pY[m] + my;
		if(ry > pY[ny] - eps) break;
		while(ry > pY[n + 1] - eps)
			n++;
		if(ry < pY[n] + eps) continue;
		if(ny + 1 >= bufferSizeIntersect) SizeUpIntersect(ny + 11);
		for(i = ny; i > n; i--)
			pY[i + 1] = pY[i];
		pY[n + 1] = ry;
		ny++;
		bool * temp = new bool[bufferSizeOccupied];
		i = 0;
		j = 0;
		for(iz = 0; iz < nz; iz++){
			for(iy = 0; iy < ny; iy++){
				if(iy == n + 1) i -= nx;
				for(ix = 0; ix < nx; ix++){
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
	for(m = 0; m <= rhs.nz; m++){
		rz = rhs.pZ[m] + mz;
		if(rz > pZ[nz] - eps) break;
		while(rz > pZ[n + 1] - eps)
			n++;
		if(rz < pZ[n] + eps) continue;
		if(nz + 1 >= bufferSizeIntersect) SizeUpIntersect(nz + 11);
		for(i = nz; i > n; i--)
			pZ[i + 1] = pZ[i];
		pZ[n + 1] = rz;
		nz++;
		bool * temp = new bool[bufferSizeOccupied];
		i = 0;
		j = 0;
		for(iz = 0; iz < nz; iz++){
			if(iz == n + 1) i -= nx * ny;
			for(iy = 0; iy < ny; iy++){
				for(ix = 0; ix < nx; ix++){
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
	unsigned int jx, jy, jz;
	float ex, ey, ez;
	j = 0;
	for(jz = 0; jz < rhs.nz; jz++)
		for(jy = 0; jy < rhs.ny; jy++)
			for(jx = 0; jx < rhs.nx; jx++){
				if(!rhs.occupied[j]){
					j++;
					continue;
				}
				rx = rhs.pX[jx] + mx;
				ry = rhs.pY[jy] + my;
				rz = rhs.pZ[jz] + mz;
				ex = rhs.pX[jx + 1] + mx;
				ey = rhs.pY[jy + 1] + my;
				ez = rhs.pZ[jz + 1] + mz;
				i = 0;
				for(iz = 0; iz < nz; iz++){
					if(pZ[iz] < rz - eps || pZ[iz + 1] > ez + eps){
						i += nx * ny;
						continue;
					}
					for(iy = 0; iy < ny; iy++){
						if(pY[iy] < ry - eps || pY[iy + 1] > ey + eps){
							i += nx;
							continue;
						}
						for(ix = 0; ix < nx; ix++){
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
