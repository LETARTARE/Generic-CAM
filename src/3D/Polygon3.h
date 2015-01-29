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
 * \brief ...
 *
 * ...
 */

#include <wx/dynarray.h>
#include "Vector3.h"
#include "AffineTransformMatrix.h"

class Polygon3 {
	// Constructor / Destructor
public:
	Polygon3();
	virtual ~Polygon3();
	// Member variables
public:
	AffineTransformMatrix matrix;
	Vector3 color;
	ArrayOfVector3 elements;

	bool isClosed;

	// Methods
public:
	void Clear(void);
	void Close(bool close = true);
	void InsertPoint(double x = 0.0, double y = 0.0, double z = 0.0);
	void Reverse(void);
	void RemoveZeroLength(void);
	Polygon3 & operator+=(const Polygon3 &a);
	const Polygon3 operator+(const Polygon3 &a) const;
	void Paint(void) const;
	double GetLength(void) const;
	void ApplyTransformation(void);
	void ApplyTransformation(const AffineTransformMatrix &matrix);
};
WX_DECLARE_OBJARRAY(Polygon3, ArrayOfPolygon3);

#endif /* POLYGON3_H_ */
