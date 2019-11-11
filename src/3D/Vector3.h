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
///////////////////////////////////////////////////////////////////////////////

/*!\class Vector3
 * \ingroup Base3D
 * \brief Vector in 3D space
 *
 * (This class has lots of inlining code in the header to execute fast.)
 */

// http://www.parashift.com/c++-faq-lite/operator-overloading.html
#ifndef _CVECTOR3_H_
#define _CVECTOR3_H_

#include <math.h>
#include <wx/string.h>
#include <ostream>

class Vector3 {
	// Constructor / Destructor:
public:
	Vector3(float px = 0.0, float py = 0.0, float pz = 0.0)
			: x(px), y(py), z(pz)
	{
	}
	Vector3(wxString string);

	// Member variables:
public:
	float x;
	float y;
	float z;

	// Methods:
public:
	wxString ToString(void) const;
	void FromString(wxString const& string);

	//! Calculate the absolut length of a vector.
	inline float Abs() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	//! Calculate the squared absolut length of a vector.
	inline float Abs2() const
	{
		return x * x + y * y + z * z;
	}

	//! Overloaded operator for vector addition.
	Vector3& operator+=(const Vector3& a)
	{
		this->x += a.x;
		this->y += a.y;
		this->z += a.z;
		return *this;
	}

	//! Overloaded operator for vector addition.
	const Vector3 operator+(const Vector3& a) const
	{
		Vector3 temp = *this;
		temp += a;
		return temp;
	}

	//! Overloaded operator for vector subtraction.
	Vector3& operator-=(const Vector3& a)
	{
		this->x -= a.x;
		this->y -= a.y;
		this->z -= a.z;
		return *this;
	}

	//! Overloaded operator for vector subtraction.
	const Vector3 operator-(const Vector3& a) const
	{
		Vector3 temp = *this;
		temp -= a;
		return temp;
	}

	//! Overloaded operator for vector negation.
	const Vector3 operator-() const
	{
		Vector3 temp(-this->x, -this->y, -this->z);
		return temp;
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
	//!Overloaded operator for vector product.
	Vector3& operator*=(const Vector3& b)
	{
		Vector3 a = *(this);
		this->x = a.y * b.z - a.z * b.y;
		this->y = a.z * b.x - a.x * b.z;
		this->z = a.x * b.y - a.y * b.x;
		return *this;
	}

	//! Overloaded operator for scalar product.
	Vector3& operator*=(const float b)
	{
		this->x *= b;
		this->y *= b;
		this->z *= b;
		return *this;
	}

	//! Overloaded operator for vector product.
	const Vector3 operator*(const Vector3& b) const
	{
		Vector3 temp = *this;
		temp *= b;
		return temp;
	}

	//! Overloaded operator for scalar product.
	const Vector3 operator*(const float b) const
	{
		Vector3 temp = *this;
		temp *= b;
		return temp;
	}

	//! Calculates the dot product (inner product) of two vectors.
	float Dot(const Vector3& b) const
	{
		return (x * b.x + y * b.y + z * b.z);
	}

	//! Overloaded operator for scalar division.
	Vector3& operator/=(const float b)
	{
		this->x /= b;
		this->y /= b;
		this->z /= b;
		return *this;
	}

	//! Overloaded operator for scalar division.
	const Vector3 operator/(const float b) const
	{
		Vector3 temp = *this;
		temp /= b;
		return temp;
	}

	//! Comparison operator equality.
	bool operator==(const Vector3& b) const;

	//! Comparison operator inequality.
	bool operator!=(const Vector3& b) const
	{
		return !(*this == b);
	}

	friend std::ostream &operator<<(std::ostream &output, const Vector3 &v)
	{
		output << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		return output;
	}

	//! Zeros the vector.
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

	//! Returns a normal length vector (without changing the original vector)
	Vector3 Normal(void) const;

	//! Normalizes the length of a vector.
	void Normalize(void);

	/*! \brief Generate an orthogonal vector
	 *
	 * Generates an arbitrary vector that is garanteed orthogonal to this vector.
	 */
	Vector3 Orthogonal(void) const;
};

#endif // _CVECTOR3_H_
