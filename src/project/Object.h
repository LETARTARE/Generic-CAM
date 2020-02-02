///////////////////////////////////////////////////////////////////////////////
// Name               : Object.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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

#ifndef OBJECT_H_
#define OBJECT_H_

/*!\class Object
 * \ingroup document
 * \brief 3D Object to manufacture
 *
 * Please note, that the object has two AffineTransformMatrix. One
 * only captures rotation and scale, the other one is used to arrange
 * the objects when only the objects are displayed. It starts off as
 * the postion, the object was loaded in.
 */

#include "../3D/Hull.h"
#include "../3D/BoundingBox.h"
#include "../3D/AffineTransformMatrix.h"
#include "../3D/OpenGLMaterial.h"
#include "Selection.h"

#include <wx/txtstrm.h>
#include <wx/filename.h>
#include <wx/string.h>

class Object {
	// Constructor / Destructor
public:
	Object();
	virtual ~Object();

	// Member variables
public:
	wxString name;
	wxFileName fileName;

	AffineTransformMatrix matrix; //!< Transformation (rotation and scaling) of the object in the positive quadrant next to the origin.

	Hull geometry;
	BoundingBox bbox;

	bool show; //!< An object can hide, e.g. if derived objects exist
	bool selectable; //!< If marked as not selectable, it cannot be selected.

private:

	// Methods
public:
	void Update(void);

	bool LoadObject(wxFileName fileName);
	bool ReloadObject(void);

	void FlipX(void);
	void FlipY(void);
	void FlipZ(void);
	void FlipNormals(void);

	bool IsEmpty(void) const;

	void ToStream(wxTextOutputStream & stream, size_t objID) const;
	bool FromStream(wxTextInputStream & stream);

	void Paint(const OpenGLMaterial &face, const OpenGLMaterial &edge,
			const Selection& sel) const;
	void PaintPick(void) const;

};

#endif /* OBJECT_H_ */
