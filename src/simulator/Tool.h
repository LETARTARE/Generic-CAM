///////////////////////////////////////////////////////////////////////////////
// Name               : Tool.h
// Purpose            : A tool for the machine.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#ifndef TOOL_H_
#define TOOL_H_
#include "ToolElement.h"
#include "../3D/Vector3.h"
#include <wx/string.h>
#include <wx/dynarray.h>

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

WX_DECLARE_OBJARRAY(ToolElement, ArrayOfToolElement)
;
WX_DECLARE_OBJARRAY(ToolContourElement, ArrayOfToolContourElement)
;

class Tool {
	// Constructor/ Destructor
public:
	Tool();
	virtual ~Tool();

	// Member variables
public:
	wxString toolName;
	float shaftDiameter;
	float shaftLength;
	float maxSpeed;
	float feedCoefficient;
	unsigned int nrOfTeeth;
	wxString comment;
	ArrayOfToolElement elements;
	ArrayOfToolContourElement contour;
	unsigned int slot;
	const unsigned int resolution;

	// Methods
public:
	void GenerateContour(void);

	float GetPositiveLength(void);
	float GetNegativeLength(void);
	float GetMaxDiameter(void);

	void Paint(void);
};

#endif /* TOOL_H_ */
