///////////////////////////////////////////////////////////////////////////////
// Name               : CSGSurface.h
// Purpose            : Wrapper for Constructive Solid Geometry.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm -lgts
// Author             : Tobias Schaefer
// Created            : 15.04.2010
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
//$LastChangedDate: 2010-08-07 03:00:28 +0200 (Sa, 07 Aug 2010) $
//$Revision: 53 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#ifndef CSGSURFACE_H_
#define CSGSURFACE_H_

#include "AffineTransformMatrix.h"

class BooleanModeller;
class Solid;
class Color;

/*!\class CSGSurface
 * \brief Wrapper class for the The GNU Triangulated Surface Library.
 *
 * To hide all the uglieness deep inside...
 */
class CSGSurface {
	// Constructor / Destructor
public:
	CSGSurface();
	virtual ~CSGSurface();
	// Member variables
public:

	Solid * solid;

protected:
	AffineTransformMatrix m;

	// Methods
public:

	void Clear();
	void Paint() const;

	void AddBox(const double sizeX, const double sizeY, const double sizeZ);
	void SetSphere(const double radius, const unsigned char subdivision = 3);

	void ScaleUniform(float scaleXYZ);
	void Scale(float scaleX, float scaleY, float scaleZ);
	void Rotate(float rotateX, float rotateY, float rotateZ);
	void Translate(float translateX = 0, float translateY = 0,
			float translateZ = 0);

	void BooleanRemove(const CSGSurface* surfaceToRemove);
	void BooleanAdd(const CSGSurface* surfaceToAdd);

	void InsertSurface(const CSGSurface* surface);

	bool SelfTest(void);
	void Statistics(void);

};

#endif /* CSGSURFACE_H_ */
