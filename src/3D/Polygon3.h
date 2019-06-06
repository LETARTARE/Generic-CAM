///////////////////////////////////////////////////////////////////////////////
// Name               : Polygon3.h
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

#ifndef POLYGON3_H_
#define POLYGON3_H_

/*!\class Polygon3
 * \brief Polygon in 3D space.
 *
 * Loop of Vector3 objects that form a polygon.
 */

#include <stddef.h>
#include <vector>

#include "AffineTransformMatrix.h"
#include "Vector3.h"

class Polygon3 {
	// Constructor / Destructor
public:
	Polygon3();
	virtual ~Polygon3();
	// Member variables
public:
	AffineTransformMatrix matrix; ///< Global Transformation of the polygon points

	bool showDots; ///< Show Dots (GL_POINTS) at the points of the polygon
	bool calcNormals; ///< Calculate normals when sending to OpenGL

protected:
	bool isClosed; ///< Boolean: Closed or open polygon
	std::vector <Vector3> elements; ///< Points that make up the polygon

	// Methods
public:

	/*! \brief Clear all points from the Polygon
	 */
	void Clear(void);

	/*! \brief Insert a point at the end of the polygon using the coordinates x,y and z
	 */
	void InsertPoint(double x = 0.0, double y = 0.0, double z = 0.0);

	/*! \brief Insert a point at the end of the polygon using a Vector3 point
	 *
	 * @param x Vector3 point
	 */
	void InsertPoint(const Vector3 &x);

	/*! \brief Close (or open) the polygon to a cycle
	 *
	 * @param close Boolean: true (default) to close the polygon, false to open it.
	 */
	void Close(bool close = true);
	bool IsClosed(void) const;

	/*! \brief Reverse the direction of the polygon
	 */
	void Reverse(void);

	/*! \brief Remove all segments from the polygon, that have a length of zero
	 */
	void RemoveZeroLength(void);

	/*! \brief Apply the transformation matrix to the points in the polygon.
	 *
	 * The transformation matrix is reset to the identity matrix afterwards.
	 * This command results in no change on the output of the Paint command.
	 */
	void ApplyTransformation(void);

	/*! \brief Apply a AffineTransformMatrix to the points in the polygon
	 *
	 * The matrix belonging to the polygon itself stays unchanged.
	 * @param matrix AffineTransformMatrix with the transform operation
	 */
	void ApplyTransformation(const AffineTransformMatrix &matrix);

	/*! \brief Add the points of two Polygon3 together
	 *
	 * Both polygons are appended behind each other.
	 */
	Polygon3 & operator+=(const Polygon3 &a);

	/*! \brief Add another Polygon3 to this polygon
	 */
	const Polygon3 operator+(const Polygon3 &a) const;

	/*! \brief Add a Vector3 to a Polygon3
	 *
	 * Both polygons are appended behind each other.
	 */
	Polygon3 & operator+=(const Vector3 &a);

	/*! \brief Add a Vector3 to this polygon
	 */
	const Polygon3 operator+(const Vector3 &a) const;

	/*! \brief Returns the length of the polygon
	 */
	double GetLength(void) const;

	/*! \brief Get the number of elements
	 */
	size_t GetCount(void) const;

	/*! \brief Get the number of elements
	 */
	size_t Size(void) const;

	Vector3& operator[](size_t index);
	Vector3 operator[](size_t index) const;

	/*! \brief Get the center of the Polygon.
	 *
	 * This function integrates over the length of the polygon.
	 * This means, that the number of points on a line do not matter.
	 */
	Vector3 GetCenter(void) const;

	/*! \brief Get rotational axis
	 *
	 * This function calculates the axis of rotation of the polygon.
	 */
	Vector3 GetRotationalAxis(void) const;

	/*! \brief Returns a std::vector with all x values of the polygon.
	 *
	 * \note The datatype is converted from float to double upon export.
	 *
	 * @return std::vector \<double\> with all x values.
	 */
	std::vector <double> GetXVectorD(void) const;

	/*! \brief Returns a std::vector with all y values of the polygon.
	 *
	 * \note The datatype is converted from float to double upon export.
	 *
	 * @return std::vector \<double\> with all y values.
	 */
	std::vector <double> GetYVectorD(void) const;

	/*! \brief Returns a std::vector with all z values of the polygon.
	 *
	 * \note The datatype is converted from float to double upon export.
	 *
	 * @return std::vector \<double\> with all z values.
	 */
	std::vector <double> GetZVectorD(void) const;

	/*! \brief Resample the point in the polygon.
	 *
	 * The polygon is resampled into a polygon with N points. This can be an over- or undersampling of the original polygon.
	 * @param N New number of points
	 */
	void Resample(unsigned int N);

	/*! \brief Moving-average filter for the points of the polygon
	 *
	 * Use a simple MA FIR filter to filter the points of the polygon in all three dimensions.
	 * The filter length is choosen symmetric around the point filtered. E.g. if N = 3, the point
	 * n is averages to the mean value of n-1, n, n+1. For even numbers the extra point is take from the
	 * negative part. E.g. N = 4 results in the mean value of n-2, n-1, n, n+1.
	 *
	 *\todo: Revisit and check, if everything is implemented according to the description.
	 *
	 * @param N length of the MA filter.
	 */
	void Filter(unsigned int N);

	/*! \brief Render the Polygon to OpenGL
	 */
	void Paint(void) const;
};

#endif /* POLYGON3_H_ */
