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
 * Vector of Vector3 objects that form a polygon. The polygon may be closed.
 * The points of the polygon may have optional normal vectors.
 * Normal vectors can be (re-)calculated.
 */

#include <stddef.h>
#include <vector>

#include "AffineTransformMatrix.h"
#include "Vector3.h"

class Polygon3 {
	// Constructor / Destructor
public:
	Polygon3();

	// Member variables
public:

	AffineTransformMatrix matrix; ///< Global Transformation of the polygon points

	size_t dotSize; ///< If > 0, dots (GL_POINTS) of this size are shown at the vertices
	enum normalCalculation {
		byCenter, ///< Calculate normals with respect to the center of the polygon
		byBends ///< Calculate normals by examining the bends in the polygon
	};
protected:
	std::vector <Vector3> elements; ///< Points that make up the polygon
	bool isClosed; ///< Boolean: Closed or open polygon

	std::vector <Vector3> normals; ///< One normal per vertex
	normalCalculation method;

	// Methods
public:

	void Clear(void); ///< Clear all points from the Polygon

	void InsertPoint(double x = 0.0, double y = 0.0, double z = 0.0); ///< Insert a point at the end of the polygon
	void InsertPoint(const Vector3 &x); ///< Insert a point at the end of the polygon
	void InsertPoint(double x, double y, double z, double nx, double ny,
			double nz); ///< Insert a point with normal at the end of the polygon
	void InsertPoint(const Vector3 &x, const Vector3 &n); ///< Insert a point with normal at the end of the polygon

	Polygon3 & operator+=(const Polygon3 &a); ///< Append another Polygon3 to this one
	const Polygon3 operator+(const Polygon3 &a) const; ///< Append two Polygon3%s

	Polygon3 & operator+=(const Vector3 &a); ///< Add a Vector3 to this Polygon3
	const Polygon3 operator+(const Vector3 &a) const; ///< Add a Vector3 to a Polygon3

	/*! \brief Close (or open) the polygon to a cyclic polygon
	 * @param close Boolean: true (default) to close the polygon, false to open it.
	 */
	void Close(bool close = true);
	bool IsClosed(void) const;

	void Reverse(void); ///< Reverse the direction of the polygon

	void RemoveZeroLength(void); ///< Remove all segments from the polygon, that have a length of zero

	/*! \brief Apply the transformation matrix to the points in the polygon.
	 *
	 * The transformation matrix is reset to the identity matrix afterwards.
	 * This command results in no change on the output of the Paint command.
	 */
	void ApplyTransformation(void);

	/*! \brief Apply an AffineTransformMatrix to the points in the polygon
	 *
	 * The matrix belonging to the polygon itself stays unchanged.
	 * @param matrix AffineTransformMatrix with the transform operation
	 */
	void ApplyTransformation(const AffineTransformMatrix &matrix);

	Polygon3 & operator/=(const double val);
	const Polygon3 operator/(const double val);
	Polygon3 & operator*=(const double val);
	const Polygon3 operator*(const double val);

	/*! \brief Returns the length of the polygon
	 */
	double GetLength(void) const;

	/*! \brief Get the number of elements
	 */
	size_t Size(void) const;

	Vector3& operator[](size_t index);
	const Vector3& operator[](size_t index) const;
	Vector3& Normal(size_t index);
	const Vector3& Normal(size_t index) const;

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

	/*! \brief Calculates the area of the polygon
	 *
	 * This function assumes the polygon is closed and uses the vectorproduct to calculate the area of the polygon.
	 */
	double GetArea(void) const;

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
	void Resample(unsigned int Nnew);

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

	/*! \brief Init the normal vector
	 * This function is needed, if the normals will be set externally. If CalculateAndStoreNormals is called,
	 * the vector is initialized as well.
	 */
	void InitNormals(void); ///< Prepare the normal vector for each vertex.
	void CalculateNormals(void); ///< Calculate normals once and store them. (InitNormals not needed.)
	void ClearNormals(void); ///< Clear the normal storage.

	void Export(std::string filename) const; ///< Export as a Matlab/Octave .mat file.

	void Paint(bool withNormals = true, double normalLength = -1) const; ///< Render the Polygon to OpenGL
private:
	std::vector <Vector3> pCalculateNormals(void) const; ///< Extra private function, because const.
};

#endif /* POLYGON3_H_ */
