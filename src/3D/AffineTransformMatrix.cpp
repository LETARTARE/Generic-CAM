///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.cpp
// Purpose            : A class to store a 3D affine transform matrix and provide operations upon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 22.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "AffineTransformMatrix.h"

#include "OpenGLMaterial.h"
#include "Vector3.h"

#include <wx/chartype.h>
#include <wx/string.h>
#include <wx/tokenzr.h>
#include <wx/txtstrm.h>

#include <stdint.h>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "OpenGL.h"

AffineTransformMatrix::AffineTransformMatrix()
{
	side = rhs;
	SetIdentity();
}

AffineTransformMatrix::AffineTransformMatrix(const Vector3& ex,
		const Vector3& ey, const Vector3& ez, const Vector3& origin)
{
	a[0] = ex.x;
	a[1] = ex.y;
	a[2] = ex.z;
	a[3] = 0.0;
	a[4] = ey.x;
	a[5] = ey.y;
	a[6] = ey.z;
	a[7] = 0.0;
	a[8] = ez.x;
	a[9] = ez.y;
	a[10] = ez.z;
	a[11] = 0.0;
	a[12] = tx = origin.x;
	a[13] = ty = origin.y;
	a[14] = tz = origin.z;
	a[15] = 1.0;
	rx = ry = rz = 0.0;
	sx = sy = sz = 1.0;
	side = ((ex * ey).Dot(ez) > 0)? rhs : lhs;
}

void AffineTransformMatrix::SetOrientation(orientation side)
{
	this->side = side;
}

AffineTransformMatrix::orientation AffineTransformMatrix::GetOrientation(
		void) const
{
	return side;
}

AffineTransformMatrix::orientation AffineTransformMatrix::CheckOrientation(
		void) const
{
	const double x = a[1] * a[6] - a[2] * a[5];
	const double y = a[2] * a[4] - a[0] * a[6];
	const double z = a[0] * a[5] - a[1] * a[4];
	const double c = x * a[8] + y * a[9] + z * a[10];
	return (c >= 0.0)? rhs : lhs;
}

void AffineTransformMatrix::UpdateOrientation(void)
{
	side = CheckOrientation();
}

void AffineTransformMatrix::SetIdentity()
{
	rx = ry = rz = 0.0;
	tx = ty = tz = 0.0;
	sx = sy = sz = 1.0;
	for(uint_fast8_t i = 0; i < 16; i++)
		a[i] = 0;
	a[0] = 1.0;
	a[5] = 1.0;
	a[10] = (side == rhs)? 1.0 : -1.0;
	a[15] = 1.0;
}

void AffineTransformMatrix::ResetRotationAndScale(void)
{
	rx = ry = rz = 0.0;
	sx = sy = sz = 1.0;
	for(uint_fast8_t i = 0; i < 12; ++i)
		a[i] = 0;
	a[0] = 1.0;
	a[5] = 1.0;
	a[10] = (side == rhs)? 1.0 : -1.0;
	a[15] = 1.0;
}

void AffineTransformMatrix::Set(AffineTransformMatrix const& b)
{
	if(this == &b) return;
	for(uint_fast8_t i = 0; i < 16; i++)
		a[i] = b.a[i];
	TakeMatrixApart();
}

double& AffineTransformMatrix::operator [](unsigned char index)
{
	if(index >= 16) throw(std::range_error(
	__FILE__ " operator[] - Out of range."));
	return a[index];
}

double AffineTransformMatrix::operator [](unsigned char index) const
{
	if(index >= 16) throw(std::range_error(
	__FILE__ " operator[] - Out of range."));
	return a[index];
}

void AffineTransformMatrix::SetOrigin(const Vector3& origin)
{
	a[12] = tx = origin.x;
	a[13] = ty = origin.y;
	a[14] = tz = origin.z;
}

void AffineTransformMatrix::SetEx(const Vector3& ex)
{
	a[0] = ex.x;
	a[1] = ex.y;
	a[2] = ex.z;
}

void AffineTransformMatrix::SetEy(const Vector3& ey)
{
	a[4] = ey.x;
	a[5] = ey.y;
	a[6] = ey.z;
}

void AffineTransformMatrix::SetEz(const Vector3& ez)
{
	a[8] = ez.x;
	a[9] = ez.y;
	a[10] = ez.z;
}

void AffineTransformMatrix::CalculateEx(void)
{
	if(side == rhs){
		a[0] = a[5] * a[10] - a[6] * a[9];
		a[1] = a[6] * a[8] - a[4] * a[10];
		a[2] = a[4] * a[9] - a[5] * a[8];
	}else{
		a[0] = a[9] * a[6] - a[10] * a[5];
		a[1] = a[10] * a[4] - a[8] * a[6];
		a[2] = a[8] * a[5] - a[9] * a[4];
	}
}

void AffineTransformMatrix::CalculateEy(void)
{
	if(side == rhs){
		a[4] = a[9] * a[2] - a[10] * a[1];
		a[5] = a[10] * a[0] - a[8] * a[2];
		a[6] = a[8] * a[1] - a[9] * a[0];
	}else{
		a[4] = a[1] * a[10] - a[2] * a[9];
		a[5] = a[2] * a[8] - a[0] * a[10];
		a[6] = a[0] * a[9] - a[1] * a[8];
	}
}

void AffineTransformMatrix::CalculateEz(void)
{
	if(side == rhs){
		a[8] = a[1] * a[6] - a[2] * a[5];
		a[9] = a[2] * a[4] - a[0] * a[6];
		a[10] = a[0] * a[5] - a[1] * a[4];
	}else{
		a[8] = a[5] * a[2] - a[6] * a[1];
		a[9] = a[6] * a[0] - a[4] * a[2];
		a[10] = a[4] * a[1] - a[5] * a[0];
	}
}

AffineTransformMatrix AffineTransformMatrix::Normal(void) const
{
	const double v0 = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	const double v1 = a[4] * a[4] + a[5] * a[5] + a[6] * a[6];
	const double v2 = a[8] * a[8] + a[9] * a[9] + a[10] * a[10];
	AffineTransformMatrix temp = *this;
	if(v0 > 0){
		const double sv0 = sqrt(v0);
		temp.a[0] /= sv0;
		temp.a[1] /= sv0;
		temp.a[2] /= sv0;
	}
	if(v1 > 0){
		const double sv1 = sqrt(v1);
		temp.a[4] /= sv1;
		temp.a[5] /= sv1;
		temp.a[6] /= sv1;
	}
	if(v2 > 0){
		const double sv2 = sqrt(v2);
		temp.a[8] /= sv2;
		temp.a[9] /= sv2;
		temp.a[10] /= sv2;
	}
	return temp;
}

void AffineTransformMatrix::Normalize(void)
{
	(*this) = (*this).Normal();
}

Vector3 AffineTransformMatrix::GetOrigin(void) const
{
	return Vector3(a[12], a[13], a[14]);
}

Vector3 AffineTransformMatrix::GetEx(void) const
{
	return Vector3(a[0], a[1], a[2]);
}

Vector3 AffineTransformMatrix::GetEy(void) const
{
	return Vector3(a[4], a[5], a[6]);
}

Vector3 AffineTransformMatrix::GetEz(void) const
{
	return Vector3(a[8], a[9], a[10]);
}

AffineTransformMatrix& AffineTransformMatrix::operator*=(
		const AffineTransformMatrix& b)
{
	//Generated with this code:
	//php -r'for($i=0;$i<4;$i++){for($j=0;$j<4;$j++){printf("this->a[%u]=",$i*4+$j);for($k=0;$k<4;$k++){printf("c[%u]*b.a[%u]%s",$k*4+$j,$i*4+$k,($k==3)?";\r\n":"+");}}}'

	// The php code generates all combinations.
	// The axiom code optimizes it a little more, because b.a[3], b.a[7] and b.a[11] are
	// zero and b.a[15] is one.

	// Axiom:
	// this:=matrix([[c[0],c[4],c[8],c[12]],[c[1],c[5],c[9],c[13]],[c[2],c[6],c[10],c[14]],[0,0,0,1]]);
	// b:=matrix([[ba[0],ba[4],ba[8],ba[12]],[ba[1],ba[5],ba[9],ba[13]],[ba[2],ba[6],ba[10],ba[14]],[0,0,0,1]]);

	double c[16];
	for(uint_fast8_t i = 0; i < 16; i++)
		c[i] = this->a[i];

	this->a[0] = c[0] * b.a[0] + c[4] * b.a[1] + c[8] * b.a[2];
	this->a[1] = c[1] * b.a[0] + c[5] * b.a[1] + c[9] * b.a[2];
	this->a[2] = c[2] * b.a[0] + c[6] * b.a[1] + c[10] * b.a[2];
	this->a[3] = 0;

	this->a[4] = c[0] * b.a[4] + c[4] * b.a[5] + c[8] * b.a[6];
	this->a[5] = c[1] * b.a[4] + c[5] * b.a[5] + c[9] * b.a[6];
	this->a[6] = c[2] * b.a[4] + c[6] * b.a[5] + c[10] * b.a[6];
	this->a[7] = 0;

	this->a[8] = c[0] * b.a[8] + c[4] * b.a[9] + c[8] * b.a[10];
	this->a[9] = c[1] * b.a[8] + c[5] * b.a[9] + c[9] * b.a[10];
	this->a[10] = c[2] * b.a[8] + c[6] * b.a[9] + c[10] * b.a[10];
	this->a[11] = 0;

	this->a[12] = c[0] * b.a[12] + c[4] * b.a[13] + c[8] * b.a[14] + c[12];
	this->a[13] = c[1] * b.a[12] + c[5] * b.a[13] + c[9] * b.a[14] + c[13];
	this->a[14] = c[2] * b.a[12] + c[6] * b.a[13] + c[10] * b.a[14] + c[14];
	this->a[15] = 1;

	return *this;
}

const AffineTransformMatrix AffineTransformMatrix::operator*(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c *= b;
	return c;
}

AffineTransformMatrix& AffineTransformMatrix::operator/=(
		const AffineTransformMatrix& b)
{
	(*this) = (*this) * (b.Inverse());
	return *this;
}

const AffineTransformMatrix AffineTransformMatrix::operator/(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c /= b;
	return c;
}

const AffineTransformMatrix AffineTransformMatrix::Inverse() const
{
	//Axiom code:
	// )set fortran optlevel 2
	// )set output fortran on
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// inverse(R)

	const double T11 = (a[0] * a[5] + (-a[1] * a[4])) * a[10]
			+ ((-a[0] * a[6]) + a[2] * a[4]) * a[9]
			+ (a[1] * a[6] + (-a[2] * a[5])) * a[8];
	// T11 is the determinant of the matrix. This can
	// not be zero for a correct transformation matrix.
	if(T11 == 0.0) throw(std::logic_error(
	__FILE__ " Inverse() - Matrix is broken and cannot be inverted."));

	const double T12 = a[4] * a[9];
	const double T13 = a[5] * a[8];
	const double T14 = a[4] * a[10];
	const double T15 = a[6] * a[8];
	const double T16 = a[5] * a[10];
	const double T17 = a[6] * a[9];
	const double T18 = a[0] * a[9];
	const double T19 = a[1] * a[8];
	const double T21 = a[0] * a[10];
	const double T22 = a[2] * a[8];
	const double T24 = a[1] * a[10];
	const double T25 = a[2] * a[9];
	const double T27 = a[1] * a[6] + (-a[2] * a[5]);
	const double T28 = (-a[0] * a[6]) + a[2] * a[4];
	const double T29 = a[0] * a[5] + (-a[1] * a[4]);
	const double T30 = a[0] * a[5];
	const double T31 = a[1] * a[4];
	const double T32 = a[0] * a[6];
	const double T33 = a[2] * a[4];
	const double T34 = a[1] * a[6];
	const double T35 = a[2] * a[5];

	AffineTransformMatrix b;

	b.a[0] = (T16 - T17) / T11;
	b.a[4] = (-T14 + T15) / T11;
	b.a[8] = (T12 - T13) / T11;
	b.a[12] =
			((-T12 + T13) * a[14] + (T14 - T15) * a[13] + (-T16 + T17) * a[12])
					/ T11;
	b.a[1] = (-T24 + T25) / T11;
	b.a[5] = (T21 - T22) / T11;
	b.a[9] = (-T18 + T19) / T11;
	b.a[13] =
			((T18 - T19) * a[14] + (-T21 + T22) * a[13] + (-T25 + T24) * a[12])
					/ T11;
	b.a[2] = T27 / T11;
	b.a[6] = T28 / T11;
	b.a[10] = T29 / T11;
	b.a[14] =
			((-T30 + T31) * a[14] + (T32 - T33) * a[13] + (-T34 + T35) * a[12])
					/ T11;
	b.a[3] = 0;
	b.a[7] = 0;
	b.a[11] = 0;
	b.a[15] = 1;
	return b;
}

void AffineTransformMatrix::Invert(void)
{
	(*this) = (*this).Inverse();
}

AffineTransformMatrix AffineTransformMatrix::Identity()
{
	AffineTransformMatrix a;
	return a;
}

AffineTransformMatrix AffineTransformMatrix::RotationAroundVector(
		Vector3 const& vector, double const& phi)
{
	const double c = cos(phi);
	const double s = sin(phi);
	const double t = 1 - c;

	Vector3 v(vector);
	v.Normalize();

	AffineTransformMatrix a;

	a.a[0] = t * v.x * v.x + c;
	a.a[1] = t * v.x * v.y + s * v.z;
	a.a[2] = t * v.x * v.z - s * v.y;

	a.a[4] = t * v.x * v.y - s * v.z;
	a.a[5] = t * v.y * v.y + c;
	a.a[6] = t * v.y * v.z + s * v.x;

	a.a[8] = t * v.x * v.z + s * v.y;
	a.a[9] = t * v.y * v.z - s * v.x;
	a.a[10] = t * v.z * v.z + c;

	return a;
}

AffineTransformMatrix AffineTransformMatrix::RotationXY(int const& x,
		int const& y, double const& scale)
{

	const double dx = (double) x / scale;
	const double dy = (double) y / scale;

	const double dist = sqrt(dx * dx + dy * dy);

	AffineTransformMatrix a;

	if(dist > 0.001){
		const double ang = -atan2(dy, dx);

		const double coy = cos(dist / 100);
		const double siy = sin(dist / 100);
		const double coz = cos(ang);
		const double siz = sin(ang);

		a.a[0] = coz * coz * coy + siz * siz;
		a.a[1] = coz * siz * coy - coz * siz;
		a.a[2] = -coz * siy;
		a.a[4] = siz * coz * coy - coz * siz;
		a.a[5] = siz * siz * coy + coz * coz;
		a.a[6] = -siz * siy;
		a.a[8] = coz * siy;
		a.a[9] = siz * siy;
		a.a[10] = coy;
	}
	return a;
}

AffineTransformMatrix AffineTransformMatrix::RotationXYZ(double const& x,
		double const& y, double const& z)
{
	AffineTransformMatrix a;

	//Axiom code:
	// Rx := matrix[[1,0,0,0],[0,cox,-six,0],[0,six,cox,0],[0,0,0,1]]
	// Ry := matrix[[coy,0,siy,0],[0,1,0,0],[-siy,0,coy,0],[0,0,0,1]]
	// Rz := matrix[[coz,-siz,0,0],[siz,coz,0,0],[0,0,1,0],[0,0,0,1]]
	// Rz*Ry*Rx

	const double six = sin(x);
	const double siy = sin(y);
	const double siz = sin(z);
	const double cox = cos(x);
	const double coy = cos(y);
	const double coz = cos(z);

	a.a[0] = coy * coz;
	a.a[1] = coy * siz;
	a.a[2] = -siy;

	a.a[4] = -cox * siz + coz * six * siy;
	a.a[5] = six * siy * siz + cox * coz;
	a.a[6] = coy * six;

	a.a[8] = six * siz + cox * coz * siy;
	a.a[9] = cox * siy * siz - coz * six;
	a.a[10] = cox * coy;

	return a;
}

AffineTransformMatrix AffineTransformMatrix::RotationInterwoven(double const& x,
		double const& y, double const& z)
{
	const double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return AffineTransformMatrix::Identity();
	const Vector3 R(x / alpha, y / alpha, z / alpha);
	return AffineTransformMatrix::RotationAroundVector(R, alpha);
}

AffineTransformMatrix AffineTransformMatrix::RotationTrackball(const double& x1,
		const double& y1, const double& x2, const double& y2, const double& r)
{
	Vector3 r1(x1, y1, 0);
	r1 /= r;
	const double d1 = r1.Abs2();
	if(d1 >= 1.0){
		r1 /= sqrt(d1);
	}else{
		r1.z = sqrt(1 - d1);
	}
	Vector3 r2(x2, y2, 0);
	r2 /= r;
	const double d2 = r2.Abs2();
	if(d2 >= 1.0){
		r2 /= sqrt(d2);
	}else{
		r2.z = sqrt(1 - d2);
	}
	const Vector3 A = r1 * r2;
	const double alpha = asin(A.Abs());
	return AffineTransformMatrix::RotationAroundVector(A, alpha);
}

AffineTransformMatrix AffineTransformMatrix::RotationQuarternion(
		const double& w, const double& x, const double& y, const double& z)
{
	// Conversion formula from
	// https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion

	const double n = w * w + x * x + y * y + z * z;
	const double s = (fabs(n) < 1e-9)? (0) : (2.0 / n);
	const double wx = s * w * x;
	const double wy = s * w * y;
	const double wz = s * w * z;
	const double xx = s * x * x;
	const double xy = s * x * y;
	const double xz = s * x * z;
	const double yy = s * y * y;
	const double yz = s * y * z;
	const double zz = s * z * z;

	AffineTransformMatrix m;

	m.a[0] = 1.0 - (yy + zz);
	m.a[1] = xy + wz;
	m.a[2] = xz - wy;
	m.a[3] = 0;
	m.a[4] = xy - wz;
	m.a[5] = 1.0 - (xx + zz);
	m.a[6] = yz + wx;
	m.a[7] = 0;
	m.a[8] = xz + wy;
	m.a[9] = yz - wx;
	m.a[10] = 1.0 - (xx + yy);
	m.a[11] = 0;
	m.a[12] = 0;
	m.a[13] = 0;
	m.a[14] = 0;
	m.a[15] = 1.0;

	return m;
}

void AffineTransformMatrix::TranslateGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// T*this
	a[12] += x;
	a[13] += y;
	a[14] += z;
}

void AffineTransformMatrix::TranslateLocal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// this*T
	a[12] += x * a[0] + y * a[4] + z * a[8];
	a[13] += x * a[1] + y * a[5] + z * a[9];
	a[14] += x * a[2] + y * a[6] + z * a[10];
}

void AffineTransformMatrix::ScaleGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// S*this

	a[0] *= x;
	a[1] *= y;
	a[2] *= z;
	a[4] *= x;
	a[5] *= y;
	a[6] *= z;
	a[8] *= x;
	a[9] *= y;
	a[10] *= z;
	a[12] *= x;
	a[13] *= y;
	a[14] *= z;
}

void AffineTransformMatrix::ScaleLocal(const double& x, const double& y,
		const double& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// this*S

	a[0] *= x;
	a[1] *= x;
	a[2] *= x;
	a[4] *= y;
	a[5] *= y;
	a[6] *= y;
	a[8] *= z;
	a[9] *= z;
	a[10] *= z;
}

Vector3 AffineTransformMatrix::Transform(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12];
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13];
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14];
	return temp;
}

Vector3 AffineTransformMatrix::Transform(const double x, const double y,
		const double z) const
{
	Vector3 temp;
	temp.x = a[0] * x + a[4] * y + a[8] * z + a[12];
	temp.y = a[1] * x + a[5] * y + a[9] * z + a[13];
	temp.z = a[2] * x + a[6] * y + a[10] * z + a[14];
	return temp;
}

Vector3 AffineTransformMatrix::TransformNoShift(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],0],[a[1],a[5],a[9],0],[a[2],a[6],a[10],0],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z;
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z;
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z;
	return temp;
}

Vector3 AffineTransformMatrix::TransformNoShift(const double x, const double y,
		const double z) const
{
	Vector3 temp;
	temp.x = a[0] * x + a[4] * y + a[8] * z;
	temp.y = a[1] * x + a[5] * y + a[9] * z;
	temp.z = a[2] * x + a[6] * y + a[10] * z;
	return temp;
}

Vector3 AffineTransformMatrix::operator *(const Vector3& v) const
{
	return Transform(v);
}

Vector3 AffineTransformMatrix::operator ()(const Vector3 &v) const
{
	return Transform(v);
}

Vector3 AffineTransformMatrix::operator ()(const double x, const double y,
		const double z) const
{
	return Transform(x, y, z);
}

double AffineTransformMatrix::LocalX(const Vector3& v) const
{
	const double den = (a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return ((v.x - a[12]) * a[0] + (v.y - a[13]) * a[1] + (v.z - a[14]) * a[2])
			/ den;
}

double AffineTransformMatrix::LocalY(const Vector3& v) const
{
	const double den = (a[4] * a[4] + a[5] * a[5] + a[6] * a[6]);
	return ((v.x - a[12]) * a[4] + (v.y - a[13]) * a[5] + (v.z - a[14]) * a[6])
			/ den;
}

double AffineTransformMatrix::LocalZ(const Vector3& v) const
{
	const double den = (a[8] * a[8] + a[9] * a[9] + a[10] * a[10]);
	return ((v.x - a[12]) * a[8] + (v.y - a[13]) * a[9] + (v.z - a[14]) * a[10])
			/ den;
}

double AffineTransformMatrix::GlobalX(double x, double y, double z) const
{
	return a[0] * x + a[4] * y + a[8] * z + a[12];
}

double AffineTransformMatrix::GlobalY(double x, double y, double z) const
{
	return a[1] * x + a[5] * y + a[9] * z + a[13];
}

double AffineTransformMatrix::GlobalZ(double x, double y, double z) const
{
	return a[2] * x + a[6] * y + a[10] * z + a[14];
}

double AffineTransformMatrix::Distance(const AffineTransformMatrix& other) const
{
	double temp = 0.0;
	for(uint_fast8_t n = 0; n < 16; ++n)
		temp += (a[n] - other.a[n]) * (a[n] - other.a[n]);
	return sqrt(temp);

	// For future reference (did not work as expected):
	// If two matrices are identical, the matrix times the inverse of the other matrix
	// should result in the identity matrix.

	// A:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// B:=matrix([[b[0],b[4],b[8],b[12]],[b[1],b[5],b[9],b[13]],[b[2],b[6],b[10],b[14]],[0,0,0,1]])
	// I:=matrix([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])
	// R:=A*inverse(B)-I
	// trace(R*transpose(R))

	// Result: No improvements (speedup) when used in Inverse Kinematics. -> Kicked out
}

void AffineTransformMatrix::TakeMatrixApart(void)
{
	double b[16];

	tx = a[12];
	ty = a[13];
	tz = a[14];

	sx = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	sy = sqrt(a[4] * a[4] + a[5] * a[5] + a[6] * a[6]);
	sz = sqrt(a[8] * a[8] + a[9] * a[9] + a[10] * a[10]);

	if(fabs(sx) > 0.0){
		b[0] = a[0] / sx;
		b[1] = a[1] / sx;
		b[2] = a[2] / sx;
	}else{
		b[0] = 0.0;
		b[1] = 0.0;
		b[2] = 0.0;
	}
	if(fabs(sy) > 0.0){
		b[4] = a[4] / sy;
		b[5] = a[5] / sy;
		b[6] = a[6] / sy;
	}else{
		b[4] = 0.0;
		b[5] = 0.0;
		b[6] = 0.0;
	}
	if(fabs(sz) > 0.0){
		b[8] = a[8] / sz;
		b[9] = a[9] / sz;
		b[10] = a[10] / sz;
	}else{
		b[8] = 0.0;
		b[9] = 0.0;
		b[10] = 0.0;
	}

	if(fabs(b[0]) > 0.0 || fabs(b[1]) > 0.0){
		rz = atan2(b[1], b[0]);
	}else{
		rz = 0.0;
	}
	double coz = cos(rz);
	double siz = sin(rz);

	if(fabs(b[0]) > 0.0 || fabs(b[1]) > 0.0 || fabs(b[2]) > 0.0){
		ry = atan2(-b[2], sqrt(b[0] * b[0] + b[1] * b[1]));
	}else{
		ry = 0.0;
	}
	double coy = cos(ry);
	double siy = sin(ry);

	b[0] = b[5] * coy * siz - b[6] * siy + b[4] * coy * coz;
	b[1] = -b[4] * siz + b[5] * coz;
	b[2] = b[5] * siy * siz + b[4] * coz * siy + b[6] * coy;

	if(fabs(b[1]) > 0.0 || fabs(b[2]) > 0.0){
		rx = atan2(b[2], b[1]);
	}else{
		rx = 0.0;
	}
}

void AffineTransformMatrix::PutMatrixTogether(void)
{
	const double cox = cos(rx);
	const double six = sin(rx);
	const double coy = cos(ry);
	const double siy = sin(ry);
	const double coz = cos(rz);
	const double siz = sin(rz);

	// Matrix calculated with Axiom:
	//
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// S := matrix[[sx,0,0],[0,sy,0],[0,0,sz]]
	// Rz*Ry*Rx*S

	a[0] = coy * coz * sx;
	a[1] = coy * siz * sx;
	a[2] = -siy * sx;
	a[3] = 0.0;
	a[4] = (-cox * siz + coz * six * siy) * sy;
	a[5] = (six * siy * siz + cox * coz) * sy;
	a[6] = coy * six * sy;
	a[7] = 0.0;
	a[8] = (six * siz + cox * coz * siy) * sz;
	a[9] = (cox * siy * siz - coz * six) * sz;
	a[10] = cox * coy * sz;
	a[11] = 0.0;
	a[12] = tx;
	a[13] = ty;
	a[14] = tz;
	a[15] = 1.0;
}

wxString AffineTransformMatrix::ToString()
{
	TakeMatrixApart();
	wxString temp;
	temp += wxString::Format(_T("%f#%f#%f#"), tx, ty, tz);
	temp += wxString::Format(_T("%f#%f#%f#"), rx, ry, rz);
	temp += wxString::Format(_T("%f#%f#%f"), sx, sy, sz);
	return temp;
}

void AffineTransformMatrix::FromString(wxString const& string)
{
	wxStringTokenizer tkz(string, wxT("#"));
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		switch(tkz.CountTokens()){
		case 8:
			token.ToDouble(&tx);
			break;
		case 7:
			token.ToDouble(&ty);
			break;
		case 6:
			token.ToDouble(&tz);
			break;
		case 5:
			token.ToDouble(&rx);
			break;
		case 4:
			token.ToDouble(&ry);
			break;
		case 3:
			token.ToDouble(&rz);
			break;
		case 2:
			token.ToDouble(&sx);
			break;
		case 1:
			token.ToDouble(&sy);
			break;
		case 0:
			token.ToDouble(&sz);
			break;
		}
	}
	PutMatrixTogether();
}

void AffineTransformMatrix::ToStream(wxTextOutputStream& stream)const
{
	for(uint_fast8_t n = 0; n < 16; n++){
		if(n > 0) stream << _T(" ");
		stream.WriteDouble(a[n]);
	}
}

void AffineTransformMatrix::FromStream(wxTextInputStream& stream)
{
	for(uint_fast8_t n = 0; n < 16; n++)
		stream >> a[n];
	TakeMatrixApart();
}

void AffineTransformMatrix::GLMultMatrix(void) const
{
	glMultMatrixd(a);
}

void AffineTransformMatrix::Paint(const double scale) const
{
	OpenGLMaterial matX(0.8, 0.0, 0.0, 0.8);
	OpenGLMaterial matY(0.0, 0.8, 0.0, 0.8);
	OpenGLMaterial matZ(0.0, 0.0, 0.8, 0.8);

	const double len = scale;
	const double rad = 0.133 * scale;
	const uint_fast8_t N = 4;
	{
		matX.UseMaterial();
		const Vector3 v = this->TransformNoShift(len, 0, 0);
		const Vector3 n = this->TransformNoShift(1, 0, 0);
		glBegin(GL_LINES);
		glNormal3f(-n.x, -n.y, -n.z);
		glVertex3f(a[12] - v.x, a[13] - v.y, a[14] - v.z);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(a[12] + v.x, a[13] + v.y, a[14] + v.z);
		glEnd();
	}
	{
		matY.UseMaterial();
		const Vector3 v = this->TransformNoShift(0, len, 0);
		const Vector3 n = this->TransformNoShift(0, 1, 0);
		glBegin(GL_LINES);
		glNormal3f(-n.x, -n.y, -n.z);
		glVertex3f(a[12] - v.x, a[13] - v.y, a[14] - v.z);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(a[12] + v.x, a[13] + v.y, a[14] + v.z);
		glEnd();
	}
	{
		matZ.UseMaterial();
		const Vector3 v = this->TransformNoShift(0, 0, len);
		const Vector3 n = this->TransformNoShift(0, 0, 1);
		glBegin(GL_LINES);
		glNormal3f(-n.x, -n.y, -n.z);
		glVertex3f(a[12] - v.x, a[13] - v.y, a[14] - v.z);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(a[12] + v.x, a[13] + v.y, a[14] + v.z);
		glEnd();
	}

	const double n0 = cos(M_PI_4);
	const double n1 = sin(M_PI_4);
	{
		matX.UseMaterial();
		glBegin(GL_LINES);
		const Vector3 p0 = this->Transform(len, 0, 0);
		for(uint_fast8_t i = 0; i < N; ++i){
			const double a = 2 * M_PI / N * (double) i;
			const double c = cos(a);
			const double s = sin(a);
			const Vector3 p = this->Transform(len - rad, rad * c, rad * s);
			const Vector3 n = this->TransformNoShift(n0, c * n1, s * n1);
			glNormal3d(n.x, n.y, n.z);
			glVertex3d(p0.x, p0.y, p0.z);
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
	}
	{
		matY.UseMaterial();
		glBegin(GL_LINES);
		const Vector3 p0 = this->Transform(0, len, 0);
		for(uint_fast8_t i = 0; i < N; ++i){
			const double a = 2 * M_PI / N * (double) i;
			const double c = cos(a);
			const double s = sin(a);
			const Vector3 p = this->Transform(rad * s, len - rad, rad * c);
			const Vector3 n = this->TransformNoShift(s * n1, n0, c * n1);
			glNormal3d(n.x, n.y, n.z);
			glVertex3d(p0.x, p0.y, p0.z);
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
	}
	{
		matZ.UseMaterial();
		glBegin(GL_LINES);
		const Vector3 p0 = this->Transform(0, 0, len);
		for(uint_fast8_t i = 0; i < N; ++i){
			const double a = 2 * M_PI / N * (double) i;
			const double c = cos(a);
			const double s = sin(a);
			const Vector3 p = this->Transform(rad * c, rad * s, len - rad);
			const Vector3 n = this->TransformNoShift(c * n1, s * n1, n0);
			glNormal3d(n.x, n.y, n.z);
			glVertex3d(p0.x, p0.y, p0.z);
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
	}
	OpenGLMaterial::EnableColors();
}
