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

#include "../math/MatlabFile.h"
#include "../math/MatlabMatrix.h"

#include <algorithm>
#include <float.h>
#include "OpenGL.h"


Polygon3::Polygon3()
{
	isClosed = false;
	dotSize = 0;
	method = byCenter;
}

void Polygon3::Clear(void)
{
	elements.clear();
	normals.clear();
	isClosed = false;
}

void Polygon3::InsertPoint(double x, double y, double z)
{
	elements.push_back(Vector3(x, y, z));
}

void Polygon3::InsertPoint(const Vector3& x)
{
	elements.push_back(x);
}

void Polygon3::InsertPoint(double x, double y, double z, double nx, double ny,
		double nz)
{
	elements.push_back(Vector3(x, y, z));
	normals.push_back(Vector3(nx, ny, nz));
}

void Polygon3::InsertPoint(const Vector3& x, const Vector3& n)
{
	elements.push_back(x);
	normals.push_back(n);
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
	const size_t N = elements.size();
	elements.insert(elements.end(), a.elements.begin(), a.elements.end());
	const bool hasNormals = !normals.empty() | !a.normals.empty();
	if(hasNormals && normals.empty()) normals.assign(N, Vector3());
	if(hasNormals && a.normals.empty()){
		normals.resize(elements.size(), Vector3());
	}else{
		normals.insert(normals.end(), a.normals.begin(), a.normals.end());
	}
	if(hasNormals && elements.size() != normals.size()) throw(std::logic_error(
	__FILE__": operator+= The count normals and elements do not match."));
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

bool Polygon3::IsClosed(void) const
{
	return isClosed;
}

size_t Polygon3::Size(void) const
{
	return elements.size();
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

double Polygon3::GetArea(void) const
{
	Vector3 temp;
	const size_t N = elements.size();
	for(size_t n = 1; n < N; ++n)
		temp += (elements[n] * elements[n - 1]);
	temp += (elements[0] * elements[N - 1]);
	return temp.Abs() / 2.0;
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

Vector3& Polygon3::operator [](size_t index)
{
	return elements[index];
}

const Vector3& Polygon3::operator [](size_t index) const
{
	return elements[index];
}

Polygon3& Polygon3::operator *=(const double val)
{
	for(size_t n = 0; n < elements.size(); ++n)
		elements[n] *= val;
	return *this;
}

const Polygon3 Polygon3::operator *(const double val)
{
	Polygon3 temp = *this;
	temp *= val;
	return temp;
}

Polygon3& Polygon3::operator /=(const double val)
{
	for(size_t n = 0; n < elements.size(); ++n)
		elements[n] /= val;
	return *this;
}

const Polygon3 Polygon3::operator /(const double val)
{
	Polygon3 temp = *this;
	temp /= val;
	return temp;
}

void Polygon3::ApplyTransformation(void)
{
	for(size_t i = 0; i < elements.size(); i++)
		elements[i] = matrix.Transform(elements[i]);
	if(!normals.empty()){
		for(size_t i = 0; i < elements.size(); i++)
			normals[i] = matrix.TransformNoShift(normals[i]);
	}
	matrix.SetIdentity();
}

void Polygon3::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	for(size_t i = 0; i < elements.size(); i++)
		elements[i] = matrix.Transform(elements[i]);
	if(!normals.empty()){
		for(size_t i = 0; i < elements.size(); i++)
			normals[i] = matrix.TransformNoShift(normals[i]);
	}
}

void Polygon3::RemoveZeroLength(void)
{
	const bool hasNormals = !normals.empty();
	size_t k = elements.size();
	for(size_t i = 0; i < k; i++){
		const size_t j = (i + 1) % k;
		const Vector3 temp = elements[i] - elements[j];
		if(temp.Abs() < FLT_EPSILON){
			elements.erase(elements.begin() + i);
			if(hasNormals) normals.erase(normals.begin() + i);
			i--;
			k--;
		}
	}
}

void Polygon3::Reverse(void)
{
	std::reverse(elements.begin(), elements.end());
	if(!normals.empty()) std::reverse(normals.begin(), normals.end());
}

void Polygon3::Resample(unsigned int Nnew)
{
	size_t N = elements.size();
	if(N <= 1) return;

	// Lazy solution: Upon resampling, the normals are removed.
	normals.clear();

	if(isClosed){
		// If the polygon is a closed loop, add the first element as the last one,
		// resample and throw away the last one again afterwards.
		elements.push_back(elements[0]);
		N++;
		Nnew++;
	}

	// Determine complete length
	double Lmax = 0.0;
	for(size_t n = 1; n < N; n++)
		Lmax += (elements[n] - elements[n - 1]).Abs();

	// Prepare replacement vector
	std::vector <Vector3> temp(Nnew);
	temp[0] = elements[0];
	temp[Nnew - 1] = elements[N - 1];

	// Interpolate
	double L0 = 0.0;
	size_t n = 1;
	Vector3 S = elements[n] - elements[n - 1];
	double s = S.Abs();
	double L1 = L0 + s;

	Vector3 dS(0, 0, 0);
	if(s > 1e-9) dS = S / s;

	const double dLnew = Lmax / (double) (Nnew - 1);
	double Lnew = 0;

	for(size_t nnew = 1; nnew < (Nnew - 1); ++nnew){
		Lnew += dLnew;

		while(L1 < Lnew){
			L0 = L1;
			n++;
			S = elements[n] - elements[n - 1];
			s = S.Abs();
			if(s > 1e-9)
				dS = S / s;
			else
				dS.Zero();
			L1 += s;
		}

		if(s > 1e-9)
			temp[nnew] = elements[n - 1] + dS * (Lnew - L0);
		else
			temp[nnew] = elements[n - 1];
	}

	if(isClosed) temp.pop_back();
	// Copy temp to elements. Swap needs constant time and temp is destructed anyway.
	elements.swap(temp);
}

void Polygon3::Filter(unsigned int N)
{
	normals.clear();
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

void Polygon3::InitNormals(void)
{
	normals.assign(elements.size(), Vector3());
}

void Polygon3::ClearNormals(void)
{
	normals.clear();
}

Vector3& Polygon3::Normal(size_t index)
{
	return normals[index];
}

const Vector3& Polygon3::Normal(size_t index) const
{
	return normals[index];
}

void Polygon3::CalculateNormals(void)
{
	normals = pCalculateNormals();
}

std::vector <Vector3> Polygon3::pCalculateNormals(void) const
{
	std::vector <Vector3> normals;

	const size_t N = elements.size();
	normals.resize(N);

	switch(method){
	case byCenter:
	{
		Vector3 temp = GetCenter();
		for(size_t n = 0; n < N; ++n)
			normals[n] = (elements[n] - temp).Normal();
		break;
	}
	case byBends:
	{
		std::vector <double> L(N);
		for(size_t n = 0; n < (N - 1); ++n)
			L[n] = (elements[n + 1] - elements[n]).Abs();
		L[N - 1] = (elements[0] - elements[N - 1]).Abs();
		for(size_t n = 1; n < (N - 1); ++n)
			normals[n] = ((elements[n] - elements[n - 1]) * L[n]
					- (elements[n + 1] - elements[n]) * L[n - 1]).Normal();
		if(isClosed){
			normals[0] = ((elements[0] - elements[N - 1]) * L[0]
					- (elements[1] - elements[0]) * L[N - 1]).Normal();
			normals[N - 1] = ((elements[N - 1] - elements[N - 2]) * L[N - 1]
					- (elements[0] - elements[N - 1]) * L[N - 2]).Normal();
		}else{
			Vector3 temp = elements[1] - elements[0];
			normals[0] = (normals[1] - (temp * normals[1].Dot(temp))).Normal();
			temp = elements[N - 1] - elements[N - 2];
			normals[N - 1] =
					(normals[N - 2] - (temp * normals[N - 2].Dot(temp))).Normal();
		}
		break;
	}
	}
	return normals;
}

void Polygon3::Export(std::string filename) const
{
	MatlabMatrix Mx("x", elements.size());
	MatlabMatrix My("y", elements.size());
	MatlabMatrix Mz("z", elements.size());
	for(size_t n = 0; n < elements.size(); ++n){
		Mx[n] = elements[n].x;
		My[n] = elements[n].y;
		Mz[n] = elements[n].z;
	}
	MatlabFile mf(filename);
	mf.WriteMatrix(Mx);
	mf.WriteMatrix(My);
	mf.WriteMatrix(Mz);
	mf.Close();
}

void Polygon3::Paint(bool withNormals, double normalLength) const
{
	::glPushMatrix();
	matrix.GLMultMatrix();

	const bool hasNormals = !normals.empty();
	std::vector <Vector3> normals;
	if(withNormals){
		if(hasNormals){
			normals = this->normals;
		}else{
			normals = pCalculateNormals();
		}
	}
	if(withNormals){
		if(isClosed)
			::glBegin(GL_LINE_LOOP);
		else
			::glBegin(GL_LINE_STRIP);

		for(size_t i = 0; i < elements.size(); i++){
			::glNormal3f(normals[i].x, normals[i].y, normals[i].z);
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

	if(normalLength > 0.0){
		::glBegin(GL_LINES);
		if(withNormals){
			for(size_t i = 0; i < elements.size(); i++){
				::glNormal3f(normals[i].x, normals[i].y, normals[i].z);
				::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
				::glVertex3f(elements[i].x + normals[i].x * normalLength,
						elements[i].y + normals[i].y * normalLength,
						elements[i].z + normals[i].z * normalLength);
			}
		}else{
			for(size_t i = 0; i < elements.size(); i++){
				::glVertex3f(elements[i].x, elements[i].y, elements[i].z);
				::glVertex3f(elements[i].x + normals[i].x * normalLength,
						elements[i].y + normals[i].y * normalLength,
						elements[i].z + normals[i].z * normalLength);
			}
		}
		::glEnd();
	}

	if(dotSize > 0){
		::glPointSize(dotSize);
		::glBegin(GL_POINTS);
		if(withNormals){
			for(size_t i = 0; i < elements.size(); i++){
				::glNormal3f(normals[i].x, normals[i].y, normals[i].z);
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

