///////////////////////////////////////////////////////////////////////////////
// Name               : Polygon3.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.07.2011
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

#include "Polygon3.h"

#include <wx/arrimpl.cpp>
#include <GL/gl.h>
#include <float.h>

WX_DEFINE_OBJARRAY(ArrayOfPolygon3)

Polygon3::Polygon3()
{
	isClosed = false;
	showDots = true;
	color.Set(0.8, 0.8, 0.8);
}

Polygon3::~Polygon3()
{
}
void Polygon3::Clear(void)
{
	elements.Clear();
}

void Polygon3::InsertPoint(double x, double y, double z)
{
	Vector3 temp(x, y, z);
	elements.Add(temp);
}

void Polygon3::InsertPoint(const Vector3& x)
{
	elements.Add(x);
}

Polygon3 & Polygon3::operator+=(const Polygon3 &a)
{
	Vector3 temp;
	size_t i;
	for(i = 0; i < a.elements.GetCount(); i++){
		temp = a.elements[i];
		this->elements.Add(temp);
	}
	return *this;
}

const Polygon3 Polygon3::operator+(const Polygon3 &a) const
{
	Polygon3 temp = *this;
	temp += a;
	return temp;
}

void Polygon3::Close(bool close)
{
	isClosed = close;
}

void Polygon3::Reverse(void)
{
	size_t i;
	size_t j = elements.GetCount();
	for(i = 0; i < (j / 2); i++){
		elements[i].Swap(elements[j - i - 1]);
	}
}

void Polygon3::RemoveZeroLength(void)
{
	size_t i, j, k;
	Vector3 temp;
	k = elements.GetCount();
	for(i = 0; i < k; i++){
		j = (i + 1) % k;
		temp = elements[i] - elements[j];
		if(temp.Abs() < FLT_EPSILON){
			elements.RemoveAt(i);
			i--;
			k--;
		}
	}

}

void Polygon3::ApplyTransformation(void)
{
	size_t i;
	for(i = 0; i < elements.GetCount(); i++)
		elements[i] = matrix.Transform(elements[i]);
	matrix.SetIdentity();
}

void Polygon3::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	for(i = 0; i < elements.GetCount(); i++)
		elements[i] = matrix.Transform(elements[i]);
}

double Polygon3::GetLength(void) const
{
	if(elements.GetCount() <= 1) return 0.0;
	double d = 0.0;
	size_t i;
	Vector3 temp, temp2;

	temp = elements[0];
	for(i = 1; i < elements.GetCount(); i++){
		temp2 = temp - elements[i];
		d += temp2.Abs();
		temp = elements[i];
	}
	if(isClosed){
		temp2 = temp - elements[0];
		d += temp2.Abs();
	}
	return d;
}

void Polygon3::Resample(unsigned int N)
{
	unsigned int M = elements.GetCount();
	if(M <= 1) return;

	// Determine complete length
	double L = 0.0;
	size_t n;
	for(n = 1; n < M; n++)
		L += (elements[n] - elements[n - 1]).Abs();

	double dL = L / (double) (N - 1);

	ArrayOfVector3 temp;

	size_t p = 0;
	double L0 = 0;
	double L1 = L0 + (elements[1] - elements[0]).Abs();
	for(n = 0; n < N; n++){
		L = dL * (double) n;
		while(L > L1 && p < M - 1){
			p++;
			L0 = L1;
			L1 = L0 + (elements[p + 1] - elements[p]).Abs();
		}
		temp.Add(
				elements[p]
						+ (elements[p + 1] - elements[p])
								* ((L - L0) / (L1 - L0)));
	}
	elements.Empty();
	elements = temp;
}

void Polygon3::Filter(unsigned int N)
{
	N = (N - N % 2) / 2;

	size_t n, m, q;
	size_t M = elements.GetCount();
	Vector3 temp;
	ArrayOfVector3 newelements;
	for(m = 0; m < M; m++){
		q = m;
		if((M - m - 1) < q) q = M - m - 1;
		if(q > N) q = N;
		temp.Zero();
		for(n = m - q; n <= m + q; n++)
			temp += elements[n];
		temp /= (q * 2 + 1);
		newelements.Add(temp);
	}
	elements.Empty();
	elements = newelements;
}

void Polygon3::Paint() const
{
	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glColor3f(color.x, color.y, color.z);
	::glNormal3f(0, 0, 1);

	if(isClosed)
		::glBegin(GL_LINE_LOOP);
	else
		::glBegin(GL_LINE_STRIP);
	size_t i;
	for(i = 0; i < elements.GetCount(); i++)
		::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
	::glEnd();

	if(showDots){
		::glBegin(GL_POINTS);
		for(i = 0; i < elements.GetCount(); i++)
			::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
		::glEnd();
	}

	::glPopMatrix();
}
