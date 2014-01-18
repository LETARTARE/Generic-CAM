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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include "../3D/Vector3.h"
#include "../3D/Geometry.h"
#include "../3D/Surface.h"

/*!\class BoundingBox
 * \brief ...
 *
 * ...
 */

class BoundingBox {
	// Constructor / Destructor
public:
	BoundingBox();
	virtual ~BoundingBox();

	// Member variables
public:
	Vector3 color;
	float alpha;

	double xmin, xmax;
	double ymin, ymax;
	double zmin, zmax;

	// Methods
public:

	void Reset(void);
	void Insert(const Geometry &geometry, AffineTransformMatrix &matrix);
	void Insert(Surface &surface);
	void Insert(const Triangle tri);

	bool IsEmpty(void) const;
	bool IsVolumeZero(void) const;
	double GetVolume(void)const;

	double GetSizeX(void)
	{
		if(xmax < xmin) return 0.0;
		return xmax - xmin;
	}
	double GetSizeY(void)
	{
		if(ymax < ymin) return 0.0;
		return ymax - ymin;
	}
	double GetSizeZ(void)
	{
		if(zmax < zmin) return 0.0;
		return zmax - zmin;
	}

	void Paint(void);
};

#endif /* BOUNDINGBOX_H_ */
