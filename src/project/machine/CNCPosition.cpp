///////////////////////////////////////////////////////////////////////////////
// Name               : MachinePosition.cpp
// Purpose            : The position of the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CNCPosition.h"

#include <wx/log.h>
#include <wx/arrimpl.cpp>

#include <math.h>
#include <locale.h>
#include <float.h>

WX_DEFINE_OBJARRAY(ArrayOfCNCPosition)

CNCPosition::CNCPosition(double x, double y, double z, double a, double b,
		double c, double u, double v, double w)
{
	X = x;
	Y = y;
	Z = z;
	A = a;
	B = b;
	C = c;
	U = u;
	V = v;
	W = w;

	t = 0.0;
	dt = 0.0;
}

CNCPosition::CNCPosition(const AffineTransformMatrix& matrix)
{

	// Maxima: Rotational matrices combined
	// [a0=coy*coz,a1=coy*siz,a2=-siy,a4=(-cox*siz)+coz*six*siy,a5=six*siy*siz+cox*coz,a6=coy*six,a8=six*siz+cox*coz*siy,a9=cox*siy*siz+(-coz*six),a10=cox*coy]

	const double a0 = matrix.a[0];
	const double a1 = matrix.a[1];
	const double a2 = matrix.a[2];
	const double a4 = matrix.a[4];
	const double a5 = matrix.a[5];
	const double a6 = matrix.a[6];
	const double a8 = matrix.a[8];
	const double a9 = matrix.a[9];
	const double a10 = matrix.a[10];

	const double siy = -a2;
	const double coy = (sqrt(a0 * a0 + a1 * a1) + sqrt(a6 * a6 + a10 * a10))
			/ 2.0;
	double cox;
	double six;
	double coz;
	double siz;

	// Singularity in matrix: System rotated exactly +/- 90 degres on the Y axis
	if(coy > FLT_EPSILON){
		cox = a10 / coy;
		six = a6 / coy;
		coz = a0 / coy;
		siz = a1 / coy;
	}else{
		cox = a5 - a8 / a2;
		six = -a9 - a4 / a2;
		coz = 1;
		siz = 0;
	}
	const double test = six * siy * siz + cox * coz;

	if(test * a5 >= 0){
		A = atan2(six, cox);
		B = atan2(siy, coy);
		C = atan2(siz, coz);
	}else{
		//TODO Trigger and test this condition
		A = atan2(-six, -cox);
		B = atan2(siy, -coy);
		C = atan2(-siz, -coz);
	}

	X = matrix.a[12];
	Y = matrix.a[13];
	Z = matrix.a[14];
	U = 0;
	V = 0;
	W = 0;

	t = 0.0;
	dt = 0.0;
}

CNCPosition::~CNCPosition()
{
}

double CNCPosition::AbsXYZ() const
{
	return sqrt(X * X + Y * Y + Z * Z);
}

double CNCPosition::AbsABC() const
{
	return sqrt(A * A + B * B + C * C);
}

double CNCPosition::AbsUVW() const
{
	return sqrt(U * U + V * V + W * W);
}

double CNCPosition::AbsXYZUVW() const
{
	return sqrt(X * X + Y * Y + Z * Z + U * U + V * V + W * W);
}

CNCPosition & CNCPosition::operator+=(const CNCPosition& a)
{
	this->X += a.X;
	this->Y += a.Y;
	this->Z += a.Z;
	this->A += a.A;
	this->B += a.B;
	this->C += a.C;
	this->U += a.U;
	this->V += a.V;
	this->W += a.W;
	return *this;
}

const CNCPosition CNCPosition::operator+(const CNCPosition &b) const
{
	CNCPosition temp = *this;
	temp += b;
	return temp;
}

CNCPosition & CNCPosition::operator-=(const CNCPosition& a)
{
	this->X -= a.X;
	this->Y -= a.Y;
	this->Z -= a.Z;
	this->A -= a.A;
	this->B -= a.B;
	this->C -= a.C;
	this->U -= a.U;
	this->V -= a.V;
	this->W -= a.W;
	return *this;
}

const CNCPosition CNCPosition::operator-(const CNCPosition &b) const
{
	CNCPosition temp = *this;
	temp -= b;
	return temp;
}

const CNCPosition CNCPosition::operator-() const
{
	CNCPosition temp(-this->X, -this->Y, -this->Z, -this->A, -this->B, -this->C,
			-this->U, -this->V, -this->W);
	return temp;
}

CNCPosition & CNCPosition::operator*=(const double &b)
{
	this->X *= b;
	this->Y *= b;
	this->Z *= b;
	this->A *= b;
	this->B *= b;
	this->C *= b;
	this->U *= b;
	this->V *= b;
	this->W *= b;
	return *this;
}

const CNCPosition CNCPosition::operator*(const double &b) const
{
	CNCPosition temp = *this;
	temp *= b;
	return temp;
}

CNCPosition & CNCPosition::operator/=(const double &b)
{
	this->X /= b;
	this->Y /= b;
	this->Z /= b;
	this->A /= b;
	this->B /= b;
	this->C /= b;
	this->U /= b;
	this->V /= b;
	this->W /= b;
	return *this;
}

const CNCPosition CNCPosition::operator/(const double &b) const
{
	CNCPosition temp = *this;
	temp /= b;
	return temp;
}

Vector3 CNCPosition::GetPosition(void) const
{
//	return Vector3(X, Y, Z);

// With XYZ and UVW:
	const double six = sin(A);
	const double cox = cos(A);
	const double siy = sin(B);
	const double coy = cos(B);
	const double siz = sin(C);
	const double coz = cos(C);
	return Vector3(
			(W * six + (-V * cox)) * siz + (V * coz * six + W * cox * coz) * siy
					+ U * coy * coz + X,
			((V * six + W * cox) * siy + U * coy) * siz + (-W * coz * six)
					+ V * cox * coz + Y,
			(-U * siy) + V * coy * six + W * cox * coy + Z);
}

Vector3 CNCPosition::GetNormal(void) const
{
	const double six = sin(A);
	const double cox = cos(A);
	const double siy = sin(B);
	const double coy = cos(B);
	const double siz = sin(C);
	const double coz = cos(C);

	//Vector calculated with Axiom:
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// V := matrix[[0],[0],[1]]

	// Rotate around X then Y then Z
	// Rz*Ry*Rx*V
	return Vector3(six * siz + cox * coz * siy, cox * siy * siz - coz * six,
			cox * coy);
}

AffineTransformMatrix CNCPosition::GetMatrix(void) const
{
	const double six = sin(A);
	const double cox = cos(A);
	const double siy = sin(B);
	const double coy = cos(B);
	const double siz = sin(C);
	const double coz = cos(C);

	//Matrix calculated with Axiom:
	// L := matrix[[1,0,0,U],[0,1,0,V],[0,0,1,W],[0,0,0,1]]
	// Rx := matrix[[1,0,0,0],[0,cox,-six,0],[0,six,cox,0],[0,0,0,1]]
	// Ry := matrix[[coy,0,siy,0],[0,1,0,0],[-siy,0,coy,0],[0,0,0,1]]
	// Rz := matrix[[coz,-siz,0,0],[siz,coz,0,0],[0,0,1,0],[0,0,0,1]]
	// G := matrix[[1,0,0,X],[0,1,0,Y],[0,0,1,Z],[0,0,0,1]]

	// Only considering XYZABC:
	// G*Rz*Ry*Rx

	AffineTransformMatrix temp;

//	temp.a[0] = coy * coz;
//	temp.a[1] = coy * siz;
//	temp.a[2] = -siy;
//	temp.a[3] = 0;
//	temp.a[4] = (-cox * siz) + coz * six * siy;
//	temp.a[5] = six * siy * siz + cox * coz;
//	temp.a[6] = coy * six;
//	temp.a[7] = 0;
//	temp.a[8] = six * siz + cox * coz * siy;
//	temp.a[9] = cox * siy * siz + (-coz * six);
//	temp.a[10] = cox * coy;
//	temp.a[11] = 0;
//	temp.a[12] = X;
//	temp.a[13] = Y;
//	temp.a[14] = Z;
//	temp.a[15] = 1;

	// Considering XYZABCUVW
	// G*Rz*Ry*Rx*L

	temp.a[0] = coy * coz;
	temp.a[1] = coy * siz;
	temp.a[2] = -siy;
	temp.a[3] = 0;
	temp.a[4] = (-cox * siz) + coz * six * siy;
	temp.a[5] = six * siy * siz + cox * coz;
	temp.a[6] = coy * six;
	temp.a[7] = 0;
	temp.a[8] = six * siz + cox * coz * siy;
	temp.a[9] = cox * siy * siz + (-coz * six);
	temp.a[10] = cox * coy;
	temp.a[11] = 0;
	temp.a[12] = (W * six + (-V * cox)) * siz
			+ (V * coz * six + W * cox * coz) * siy + U * coy * coz + X;
	temp.a[13] = ((V * six + W * cox) * siy + U * coy) * siz + (-W * coz * six)
			+ V * cox * coz + Y;
	temp.a[14] = (-U * siy) + V * coy * six + W * cox * coy + Z;
	temp.a[15] = 1;

	return temp;
}
