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
 * Stores the min and max values of Vector3 s, Triangle s, other BoundingBox es and Geometry.
 */

class BoundingBox {
	// Constructor / Destructor
public:
	BoundingBox();
	BoundingBox(float x1, float y1, float z1, float x2, float y2, float z2);

	// Member variables
public:
	Vector3 color;
	float alpha;

	double xmin, xmax;
	double ymin, ymax;
	double zmin, zmax;

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

	//! Insert a single Triangle.
	void Insert(const Triangle& tri);

	//! Check ich the box is empty.
	bool IsEmpty(void) const;

	/*!\brief Check if the box has zero volume.
	 * This function checks if all points inserted are the same point.
	 * This is not the same as a check for IsEmpty.
	 */
	bool IsVolumeZero(void) const;

	//! Get the volume of the box.
	double GetVolume(void) const;

	//! Returns the size in x direction.
	double GetSizeX(void)
	{
		if(xmax < xmin) return 0.0;
		return xmax - xmin;
	}

	//! Returns the size in x direction.
	double GetSizeY(void)
	{
		if(ymax < ymin) return 0.0;
		return ymax - ymin;
	}

	//! Returns the size in x direction.
	double GetSizeZ(void)
	{
		if(zmax < zmin) return 0.0;
		return zmax - zmin;
	}

	//! Put the box into a textstream.
	void ToStream(wxTextOutputStream & stream);

	//! Read a box from a textstream.
	bool FromStream(wxTextInputStream & stream);

	//! Paint the box in OpenGL.
	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(BoundingBox, ArrayOfBoundingBox);

#endif /* BOUNDINGBOX_H_ */
