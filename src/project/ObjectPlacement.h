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
 * \ingroup document
 * \brief Placement of an object
 *
 * Placement of an object in the workpiece. This also containc slicing information. One object thus can have
 * more than one placement. (This is why this a separate class.)
 */

#include "Object.h"
#include "../3D/BoundingBox.h"
#include "../3D/Polygon25.h"
#include "../3D/AffineTransformMatrix.h"

#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/dynarray.h>
#include <stddef.h>

class Workpiece;

class ObjectPlacement:public BoundingBox {
public:
	ObjectPlacement();
	virtual ~ObjectPlacement();

public:
	size_t refObject;

	AffineTransformMatrix matrix;

	//TODO: Remove the "selected" flag.
	bool selected;
//	bool modified;
//	bool isMovable;
//	bool isKeepout;
//	BoundingBox bbox;

// Slot around Objects
	bool useContour;
	double slotWidth;
	Polygon25 outline;
	Workpiece * parent; //!< Pointer back to the Workpiece this ObjectPlacement belongs to.

	float cornerX;
	float cornerY;

//Methods:
public:
	void Clear(void);

	void ToStream(wxTextOutputStream & stream);
	bool FromStream(wxTextInputStream & stream);

	void Update(void);
//	void SetKeepout(double x, double y, double sizex, double sizey);
//	void Paint(void) const;

};
WX_DECLARE_OBJARRAY(ObjectPlacement, ArrayOfObjectPlacement);

#endif /* OBJECTPLACEMENT_H_ */
