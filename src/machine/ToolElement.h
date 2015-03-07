///////////////////////////////////////////////////////////////////////////////
// Name               : ToolElement.h
// Purpose            : Hold the description of an element of the toolshape.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
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
///////////////////////////////////////////////////////////////////////////////


#ifndef TOOLELEMENT_H_
#define TOOLELEMENT_H_

#include "../3D/Vector3.h"

#include <wx/dynarray.h>
#include <wx/string.h>
class ToolContourElement {
	// Constructor/ Destructor
public:
	ToolContourElement(bool cutting = false, bool partOfShaft = false);
	virtual ~ToolContourElement();

	// Member variables
public:
	Vector3 p1;
	Vector3 p2;
	Vector3 n1;
	Vector3 n2;
	bool isCutting;
	bool belongsToShaft;

	// Methods
public:
};
WX_DECLARE_OBJARRAY(ToolContourElement, ArrayOfToolContourElement)
;

class ToolElement {
	// Constructor / Destructor
public:
	ToolElement();
	ToolElement(const wxString & string);
	virtual ~ToolElement();

	// Member variables
public:
	float d;
	float h;
	float r;
	unsigned char t;
	bool cutting;

	// Methods
public:

	wxString ToString(void) const;
	void FromString(wxString const &string);

};
WX_DECLARE_OBJARRAY(ToolElement, ArrayOfToolElement)
;

#endif /* TOOLELEMENT_H_ */
