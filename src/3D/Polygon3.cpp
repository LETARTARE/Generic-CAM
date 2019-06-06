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

#include <algorithm>
#include <float.h>
#include <GL/gl.h>

Polygon3::Polygon3()
{
	isClosed = false;
	showDots = true;
	calcNormals = true;
}

Polygon3::~Polygon3()
{
}
void Polygon3::Clear(void)
{
	elements.clear();
}

void Polygon3::InsertPoint(double x, double y, double z)
{
	elements.push_back(Vector3(x, y, z));
}

void Polygon3::InsertPoint(const Vector3& x)
{
	elements.push_back(x);
}

Polygon3& Polygon3::operator +=(const Vector3& a)
{
	this->elements.push_back(a);
	return *this;
}

const Polygon3 Polygon3::operator +(const Vector3& a) const
{
	Polygon3 temp = *this;
	temp.elements.push_back(a);
	return temp;
}

Polygon3 & Polygon3::operator+=(const Polygon3 &a)
{
	this->elements.insert(this->elements.end(), a.elements.begin(),
			a.elements.end());
//	for(size_t i = 0; i < a.elements.size(); i++){
//		const Vector3 temp = a.elements[i];
//		this->elements.push_back(temp);
//	}
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
	std::reverse(elements.begin(), elements.end());
}

void Polygon3::RemoveZeroLength(void)
{
	size_t k = elements.size();
	for(size_t i = 0; i < k; i++){
		const size_t j = (i + 1) % k;
		const Vector3 temp = elements[i] - elements[j];
		if(temp.Abs() < FLT_EPSILON){
			elements.erase(elements.begin() + i);
			i--;
			k--;
		}
	}
}

void Polygon3::ApplyTransformation(void)
{
	for(size_t i = 0; i < elements.size(); i++)
		elements[i] = matrix.Transform(elements[i]);
	matrix.SetIdentity();
}

void Polygon3::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	for(size_t i = 0; i < elements.size(); i++)
		elements[i] = matrix.Transform(elements[i]);
}

double Polygon3::GetLength(void) const
{
	if(elements.size() <= 1) return 0.0;
	double d = 0.0;
	Vector3 temp = elements[0];
	for(size_t i = 1; i < elements.size(); ++i){
		d += (temp - elements[i]).Abs();
		temp = elements[i];
	}
	if(isClosed) d += (temp - elements[0]).Abs();
	return d;
}

void Polygon3::Resample(unsigned int N)
{
	const size_t M = elements.size();
	if(M <= 1) return;

	// Determine complete length
	double Lmax = 0.0;
	for(size_t n = 1; n < M; n++)
		Lmax += (elements[n] - elements[n - 1]).Abs();

	const double dL = Lmax / (double) (isClosed? N : (N - 1));

	// Prepare replacement vector
	std::vector <Vector3> temp(N);

	double L = 0.0;
	temp[0] = elements[0];

	double L0 = 0.0;
	size_t m = 0;
	Vector3 S = elements[m + 1] - elements[m];
	double s = S.Abs();
	Vector3 ds(0, 0, 0);
	if(s > 1e-9) ds = S / s;
	double L1 = L0 + s;

	// Interpolate
	for(size_t n = 0; n < N; ++n){
		L += dL;

		while(L0 < L){
			L0 = L1;
			m++;
			S = elements[(m + 1) % M] - elements[m % M];
			s = S.Abs();
			L1 += s;
		}
		if(s > 1e-9)
			ds = S / s;
		else
			ds.Zero();
		temp[n] = elements[m % M] + ds * (L - L0);
	}
	// Adjust the last vector perfectly, if the polygon is not closed.
	if(!isClosed) temp[N - 1] = elements[M - 1];
	// Copy temp to elements. Swap needs constant time and temp is destructed anyway.
	elements.swap(temp);
}

void Polygon3::Filter(unsigned int N)
{
	N = (N - N % 2) / 2;
	const size_t M = elements.size();
	std::vector <Vector3> newelements(M);
	for(size_t m = 0; m < M; ++m){
		size_t q = m;
		if((M - m - 1) < q) q = M - m - 1;
		if(q > N) q = N;
		Vector3 temp;
		for(size_t n = m - q; n <= m + q; n++)
			temp += elements[n];
		temp /= (q * 2 + 1);
		newelements.push_back(temp);
	}

	elements.swap(newelements);
}

Vector3 Polygon3::GetCenter(void) const
{
	const size_t N = elements.size();
	if(N == 0) return Vector3();
	if(N == 1) return elements[0];
	Vector3 temp;
	double D = 0.0;
	for(size_t i = 0; i < N - 1; ++i){
		const double d = (elements[i] - elements[i + 1]).Abs();
		temp += (elements[i] + elements[i + 1]) / 2 * d;
		D += d;
	}
	if(isClosed){
		const double d = (elements[N - 1] - elements[0]).Abs();
		temp += (elements[N - 1] + elements[0]) / 2 * d;
		D += d;
	}
	if(D <= 0.0) return Vector3();
	return temp / D;
}

Vector3 Polygon3::GetRotationalAxis(void) const
{
	const size_t N = elements.size();
	if(N < 3) return Vector3();
	const Vector3 center = GetCenter();
	Vector3 temp;
	for(size_t i = 0; i < N - 1; ++i)
		temp += (elements[i] - center) * (elements[i + 1] - elements[i]);
	if(isClosed){
		temp += (elements[N - 1] - center) * (elements[0] - elements[N - 1]);
	}
	temp.Normalize();
	return temp;
}

bool Polygon3::IsClosed(void) const
{
	return isClosed;
}

void Polygon3::Paint() const
{
	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	if(calcNormals){
		const Vector3 center = GetCenter();
		if(isClosed)
			::glBegin(GL_LINE_LOOP);
		else
			::glBegin(GL_LINE_STRIP);

		for(size_t i = 0; i < elements.size(); i++){
			Vector3 temp = elements[i] - center;
			temp.Normalize();
			::glNormal3f(temp.x, temp.y, temp.z);
			::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
		}
		::glEnd();
	}else{
		::glNormal3f(0, 0, 1);
		if(isClosed)
			::glBegin(GL_LINE_LOOP);
		else
			::glBegin(GL_LINE_STRIP);
		for(size_t i = 0; i < elements.size(); i++)
			::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
		::glEnd();
	}
	if(showDots){
		::glPointSize(3);
		::glBegin(GL_POINTS);
		if(calcNormals){
			const Vector3 center = GetCenter();
			for(size_t i = 0; i < elements.size(); i++){
				Vector3 temp = elements[i] - center;
				temp.Normalize();
				::glNormal3f(temp.x, temp.y, temp.z);
				::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
			}
		}else{
			for(size_t i = 0; i < elements.size(); i++)
				::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
		}
		::glEnd();
		::glPointSize(1);
	}
	::glPopMatrix();
}

size_t Polygon3::GetCount(void) const
{
	return elements.size();
}

std::vector <double> Polygon3::GetXVectorD(void) const
{
	const size_t N = elements.size();
	std::vector <double> temp(N);
	for(size_t n = 0; n < N; ++n)
		temp[n] = (double) elements[n].x;
	return temp;
}

std::vector <double> Polygon3::GetYVectorD(void) const
{
	const size_t N = elements.size();
	std::vector <double> temp(N);
	for(size_t n = 0; n < N; ++n)
		temp[n] = (double) elements[n].y;
	return temp;
}

std::vector <double> Polygon3::GetZVectorD(void) const
{
	const size_t N = elements.size();
	std::vector <double> temp(N);
	for(size_t n = 0; n < N; ++n)
		temp[n] = (double) elements[n].z;
	return temp;
}

size_t Polygon3::Size(void) const
{
	return elements.size();
}

Vector3& Polygon3::operator [](size_t index)
{
	return elements[index];
}

Vector3 Polygon3::operator [](size_t index) const
{
	return elements[index];
}
