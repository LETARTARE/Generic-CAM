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

#include <wx/dynarray.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/xml/xml.h>

#include "../3D/AffineTransformMatrix.h"
#include "../3D/BoundingBox.h"
#include "../3D/Geometry.h"

/*!\class Object
 * \brief ...
 *
 * ...
 */

class Object {
	// Constructor / Destructor
public:
	Object();
	virtual ~Object();

	// Member variables
public:
	bool selected;

	AffineTransformMatrix matrix;

	wxFileName fileName;
	wxString name;

	ArrayOfGeometry geometries;
	BoundingBox bbox;

private:

	// Methods
public:

	void UpdateBoundingBox(void);
	void UpdateBoundingBox(AffineTransformMatrix const &matrix);
	void UpdateNormals(void);
	void Update(void);

	void Paint(void) const;

	bool LoadObject(wxFileName fileName);
	bool ReloadObject(void);

	void FlipX(void);
	void FlipY(void);
	void FlipZ(void);
	void FlipNormals(void);

	bool IsEmpty(void) const;

	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

private:
	void XMLRemoveAllChildren(wxXmlNode* node);
};
WX_DECLARE_OBJARRAY(Object, ArrayOfObject);

#endif /* OBJECT_H_ */
