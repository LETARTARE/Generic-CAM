///////////////////////////////////////////////////////////////////////////////
// Name               : BoundingBox.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.06.2011
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

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <wx/dynarray.h>
#include <wx/txtstrm.h>

#include "Geometry.h"

/*!\class BoundingBox
 * \brief Bounding Box aligned with x,y,z
 *
 * Stores the min and max values of Vector3%s, Triangle%s, other BoundingBox%es and Geometry.
 */

class BoundingBox {
	// Constructor / Destructor
public:
	BoundingBox();
	BoundingBox(float x1, float y1, float z1, float x2, float y2, float z2);

	// Member variables
public:
	double xmin, xmax;
	double ymin, ymax;
	double zmin, zmax;

	bool displayBox; ///< Show a box (default: true)
	bool displaySides; ///< Display the sides of the box as overlapping single colored planes. The colors are the 1st, 2nd and 3rd component of the color variable.

	Vector3 color; ///< Color for displaying as box
	float alpha; ///< Alphy value

	float overlap; ///< Length of the overlap (absolute value)

	// Methods
public:
	//! Reset the BoundingBox.
	void Clear(void);

	//! Insert a Geometry object into the box.
	void Insert(const Geometry& geometry, const AffineTransformMatrix& matrix);

	//! Insert a single vector.
	void Insert(const Vector3& point);

	//! Insert another BoungingBox.
	void Insert(const BoundingBox& bbox);

	BoundingBox& operator+=(const BoundingBox& rhs);
	const BoundingBox operator+(const BoundingBox& rhs) const;

	//! Insert a single Triangle.
	void Insert(const Triangle& tri);

	/*!\brief Transform BoundingBox by matrix
	 *
	 * @param matrix AffineTransformMatrix
	 */
	void Transform(const AffineTransformMatrix matrix);

	//! Check if the box is empty, i.e. nothing was inserted.
	bool IsEmpty(void) const;

	/*!\brief Check if the box has zero volume.
	 * This function checks if the box has no thickness in any direction.
	 * This is not the same as a check for IsEmpty.
	 */
	bool IsVolumeZero(void) const;

	void SetSize(float sx, float sy, float sz, float origx = 0.0, float origy =
			0.0, float origz = 0.0);

	//! Get the volume of the box.
	double GetVolume(void) const;

	//! Returns the size in x direction.
	double GetSizeX(void) const
	{
		if(xmax < xmin) return 0.0;
		return xmax - xmin;
	}

	//! Returns the size in x direction.
	double GetSizeY(void) const
	{
		if(ymax < ymin) return 0.0;
		return ymax - ymin;
	}

	//! Returns the size in x direction.
	double GetSizeZ(void) const
	{
		if(zmax < zmin) return 0.0;
		return zmax - zmin;
	}

	//! Put the box into a textstream.
	void ToStream(wxTextOutputStream & stream) const;

	//! Read a box from a textstream.
	bool FromStream(wxTextInputStream & stream);

	//! Paint the box in OpenGL.
	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(BoundingBox, ArrayOfBoundingBox);

#endif /* BOUNDINGBOX_H_ */
