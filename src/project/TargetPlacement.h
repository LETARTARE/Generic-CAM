///////////////////////////////////////////////////////////////////////////////
// Name               : TargetPlacement.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 20.07.2011
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


#ifndef TARGETPLACEMENT_H_
#define TARGETPLACEMENT_H_

/*!\class TargetPlacement
 * \brief ...
 *
 * ...
 */

#include <wx/dynarray.h>
#include <wx/xml/xml.h>

#include "../generator/Polygon25.h"

class TargetPlacement {
	// Constructor/ Destructor
public:
	TargetPlacement();
	virtual ~TargetPlacement();
	//Member variables:
public:
	AffineTransformMatrix matrix;
	Polygon25 outLine;

	bool isFlipped;
	bool isMovable;
	bool isKeepout;

	size_t targetNumber;

	//Methods:
public:
	void Clear(void);

	void SetKeepout(double x, double y, double sizex, double sizey);

	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(TargetPlacement, ArrayOfTargetPlacement)
;
#endif /* TARGETPLACEMENT_H_ */
