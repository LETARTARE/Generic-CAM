///////////////////////////////////////////////////////////////////////////////
// Name               : Vector3.h
// Purpose            : A 3D vector class with support functions.
// Thread Safe        : Yes
// Platform dependend : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 28.01.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#ifndef _CVECTOR3_H_
#define _CVECTOR3_H_

#include <cmath>

class Vector3 {
public:
	Vector3(float px = 0, float py = 0, float pz = 0) :
		x(px), y(py), z(pz)
	{
	}
	;
	~Vector3(void);
public:
	float x;
	float y;
	float z;

	float Abs();

	//	void operator=(const Vector3& a){x=a.x;y=a.y;z=a.z;};

	Vector3 operator+(const Vector3& a)
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}
	Vector3 operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return Vector3(x, y, z);
	}
	Vector3 operator-(const Vector3& a)
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
	Vector3 operator-=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return Vector3(x, y, z);
	}
	Vector3 operator-()
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 operator*(const Vector3& b)
	{
		return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	Vector3 operator*(const float &b)
	{
		return Vector3(x * b, y * b, z * b);
	}
	Vector3 operator*=(const Vector3& b)
	{
		Vector3 a = *(this);
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
		return Vector3(x, y, z);
	}
	Vector3 operator*=(const float &b)
	{
		x *= b;
		y *= b;
		z *= b;
		return Vector3(x, y, z);
	}
	Vector3 operator/(const float &b)
	{
		return Vector3(x / b, y / b, z / b);
	}
	Vector3 operator/=(const float &b)
	{
		x /= b;
		y /= b;
		z /= b;
		return Vector3(x, y, z);
	}
	void Zero(void);
	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3 Normalize(void);
};

#endif // _CVECTOR3_H_
