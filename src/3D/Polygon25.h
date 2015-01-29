///////////////////////////////////////////////////////////////////////////////
// Name               : Polygon3.h
// Purpose            : Contains a 2.5D polygon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.07.2011
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

#ifndef POLYGON25_H_
#define POLYGON25_H_

/*!\class Polygon3
 * \brief ...
 *
 * ...
 */

#include "Polygon3.h"
#include <wx/dynarray.h>

class Polygon25:public Polygon3 {
public:
	Polygon25();
	virtual ~Polygon25();

	// Methods
public:
	double GetLengthXY(void) const;
	void PolygonFillHoles(void);
	void PolygonSmooth(void);
	void PolygonExpand(double r);
	void PolygonDiminish(double r);
	bool IsElementInside(const Vector3 v);
	double DistanceToElement(const size_t elementInPolygon, const double x,
			const double y, const double vx, const double vy) const;
	double DistanceToPolygon(const Polygon25 &polygon, double vx,
			double vy) const;
	void RotatePolygonStart(double x, double y);
};
WX_DECLARE_OBJARRAY(Polygon25, ArrayOfPolygon25);

#endif /* POLYGON25_H_ */
