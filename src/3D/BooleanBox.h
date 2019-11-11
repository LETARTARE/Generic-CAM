///////////////////////////////////////////////////////////////////////////////
// Name               : BooleanBox.h
// Purpose            : Boolean operations on a small number of cubes
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef BOOLEANBOX_H_
#define BOOLEANBOX_H_

/*!\class BooleanBox
 * \brief Boolean operations on a small number of cubes
 *
 * Boolean operations are performed on axis aligned boxes. This is like a
 * simple precursor of the octree class, but very fast. It only works on
 * axis aligned cubes.
 *
 * \todo Garbage collector to simplify internal representation after several operations.
 */

#include "AffineTransformMatrix.h"

class BooleanBox {
public:
	BooleanBox();
	BooleanBox(const BooleanBox& other); //!< Copy constructor
	BooleanBox& operator=(const BooleanBox& other); ///< Assignment operator
	BooleanBox(float sx, float sy, float sz);
	BooleanBox(float x1, float y1, float z1, float x2, float y2, float z2);
	virtual ~BooleanBox();

	AffineTransformMatrix matrix;

	/*!\brief Translate BoundingBox by matrix
	 *
	 * Only the translatory components are used.
	 * @param matrix AffineTransformMatrix
	 */
	void Translate(const AffineTransformMatrix &matrix);

	/*!\brief Paint box in Open GL*/
	void Paint(bool flipNormals = false) const;

	/*!\brief Axis-align the cube
	 * Rotations at 90 degrees are OK.
	 */
	void NormalizeMatrix(void);

	/*!\brief Resize the box
	 * Sets up a new box without cutouts.
	 * @param sx Width
	 * @param sy Length
	 * @param sz Height
	 */
	void SetSize(float sx, float sy, float sz);

	/*!\brief Boolean operation subtract
	 * -= does a boolean operation on two of the boxes. The
	 * matrices in each box are used to align them.
	 */
	BooleanBox& operator-=(const BooleanBox& rhs);

private:
	unsigned int nx;
	unsigned int ny;
	unsigned int nz;
	unsigned int bufferSizeIntersect;
	unsigned int bufferSizeOccupied;
	float * pX;
	float * pY;
	float * pZ;
	bool * occupied;

	void SizeUpIntersect(unsigned int newSize);
	void SizeUpOccupied(unsigned int newSize);

};

#endif /* BOOLEANBOX_H_ */
