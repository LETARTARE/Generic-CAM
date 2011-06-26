///////////////////////////////////////////////////////////////////////////////
// Name               : Vector3.h
// Purpose            : A 3D vector class with support functions.
// Thread Safe        : Yes
// Platform dependent : No
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

/*!\class Vector3
 * \brief Contains a vector in 3D space
 */

#ifndef _CVECTOR3_H_
#define _CVECTOR3_H_

#include <cmath>
#include <wx/dynarray.h>

class Vector3 {
public:
	Vector3(float px = 0, float py = 0, float pz = 0) :
		x(px), y(py), z(pz)
	{
	}

	~Vector3(void);
public:
	float x;
	float y;
	float z;

	//!Calculate the absolut length of a vector.
	float Abs();

	//	void operator=(const Vector3& a){x=a.x;y=a.y;z=a.z;};

	//! Overloaded operator for vector addition.
	Vector3 operator+(const Vector3& a)
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}


	//! Overloaded operator for vector addition.
	Vector3 operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return Vector3(x, y, z);
	}
	//! Overloaded operator for vector subtraction.
	Vector3 operator-(const Vector3& a)
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
	//! Overloaded operator for vector subtraction.
	Vector3 operator-=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return Vector3(x, y, z);
	}
	//! Overloaded operator for vector negation.
	Vector3 operator-()
	{
		return Vector3(-x, -y, -z);
	}
	/*!\brief Overloaded operator for vector product.
	 *
	 * This function calculates the vector product
	 * \f[
	 * \vec{c}=\left\{
	 * \begin{array}{c}
	 * \vec{a}_y \cdot \vec{b}_z - \vec{a}_z \cdot \vec{b}_y \\
	 * \vec{a}_z \cdot \vec{b}_x - \vec{a}_x \cdot \vec{b}_z \\
	 * \vec{a}_x \cdot \vec{b}_y - \vec{a}_y \cdot \vec{b}_x
	 * \end{array}
	 * \right\}
	 * \f].
	 */
	Vector3 operator*(const Vector3& b)
	{
		return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	//! Overloaded operator for scalar product.
	Vector3 operator*(const float &b)
	{
		return Vector3(x * b, y * b, z * b);
	}
	//!Overloaded operator for vector product.
	Vector3 operator*=(const Vector3& b)
	{
		Vector3 a = *(this);
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
		return Vector3(x, y, z);
	}
	//! Overloaded operator for scalar product.
	Vector3 operator*=(const float &b)
	{
		x *= b;
		y *= b;
		z *= b;
		return Vector3(x, y, z);
	}


	//! Calculates the dot product (inner product) of two vectors.
	float Dot(const Vector3& b)
	{
		return (x * b.x + y * b.y + z * b.z);
	}


	//! Overloaded operator for scalar division.
	Vector3 operator/(const float &b)
	{
		return Vector3(x / b, y / b, z / b);
	}
	//! Overloaded operator for scalar division.
	Vector3 operator/=(const float &b)
	{
		x /= b;
		y /= b;
		z /= b;
		return Vector3(x, y, z);
	}

	//! Zeros a vector.
	void Zero(void);

	//! Sets the vector to the given coordinates.
	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//! Swap the vector with a given vector.
	void Swap(Vector3& b);

	//! Normalizes the length of a vector.
	Vector3 Normalize(void);
};
WX_DECLARE_OBJARRAY(Vector3, ArrayOfVector3)
;

#endif // _CVECTOR3_H_
