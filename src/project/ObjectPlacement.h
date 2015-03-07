///////////////////////////////////////////////////////////////////////////////
// Name               : ObjectPlacement.h
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
///////////////////////////////////////////////////////////////////////////////

#ifndef OBJECTPLACEMENT_H_
#define OBJECTPLACEMENT_H_

/*!\class ObjectPlacement
 * \brief ...
 *
 * ...
 */

#include <stddef.h>
#include <wx/dynarray.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "../3D/AffineTransformMatrix.h"
#include "../3D/BoundingBox.h"
#include "../3D/Polygon25.h"
#include "Object.h"

class ArrayOfObject;

class ObjectPlacement {
public:
	ObjectPlacement();
	virtual ~ObjectPlacement();

public:
	bool selected;
	bool modified;

	AffineTransformMatrix matrix;
	size_t objectNr;

	Polygon25 outline;

	BoundingBox bbox;

	//	// Slot around Objects
	double slotWidth;
	bool useContour;
	//	double supportDistance;
	//	double supportWidth;
	//	double supportHeight;
	//	double middleY;
	//	double offsetX;

	bool isMovable;
	bool isKeepout;

	//Methods:
public:
	void Clear(void);
	void Update(const ArrayOfObject &objects);

	void ToStream(wxTextOutputStream & stream);
	bool FromStream(wxTextInputStream & stream);

//	void SetKeepout(double x, double y, double sizex, double sizey);

//	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(ObjectPlacement, ArrayOfObjectPlacement);
#endif /* OBJECTPLACEMENT_H_ */
