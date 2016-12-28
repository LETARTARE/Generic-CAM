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

#include "AffineTransformMatrix.h"
#include "Vector3.h"

#include <wx/dynarray.h>

class Polygon3 {
	// Constructor / Destructor
public:
	Polygon3();
	virtual ~Polygon3();
	// Member variables
public:
	AffineTransformMatrix matrix; ///< Global Transformation of the polygon points
	Vector3 color; ///< OpenGL Color of the polygon
	ArrayOfVector3 elements; ///< Points that make up the polygon

	bool isClosed; ///< Boolean: Closed or open polygon
	bool showDots; ///< Show Dots (GL_POINTS) at the points of the polygon

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

	/*! \brief Reverse the direction of the polygon
	 */
	void Reverse(void);

	/*! \brief Remove all segments from the polygon, that have a length of zero
	 */
	void RemoveZeroLength(void);

	/*! \brief Apply the transformation matrix to the points in the polygon.
	 *
	 * The transformation matrix is reset to the identity matrix afterwards.
	 */
	void ApplyTransformation(void);

	/*! \brief Apply a AffineTransformMatrix to the points in the polygon
	 *
	 * The matrix belonging to the polygon itself stays unchanged.
	 * @param matrix AffineTransformMatrix with the transform operation
	 */
	void ApplyTransformation(const AffineTransformMatrix &matrix);

	/*! \brief Add the pointe of two Polygon3 together
	 *
	 * Both polygons are appended behind each other.
	 */
	Polygon3 & operator+=(const Polygon3 &a);

	/*! \brief Add another Polygon3 to this polygon
	 */
	const Polygon3 operator+(const Polygon3 &a) const;

	/*! \brief Returns the length of the polygon
	 */
	double GetLength(void) const;

	/*! \brief Resample the point in the polygon.
	 *
	 * The polygon is resampled into N even segments. This can be an over- or undersampling.
	 * @param N Number of segments
	 */
	void Resample(unsigned int N);

	/*! \brief MA Filter the polygon
	 *
	 * Use a simple MA FIR filter to filter the points of the polygon in all three dimensions.
	 * @param N length of the MA filter.
	 */
	void Filter(unsigned int N);

	/*! \brief Render the Polygon to OpenGL
	 */
	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(Polygon3, ArrayOfPolygon3);

#endif /* POLYGON3_H_ */
