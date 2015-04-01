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
///////////////////////////////////////////////////////////////////////////////

#ifndef TOOL_H_
#define TOOL_H_

/*!\class Tool
 * \brief Definition of a tool
 *
 *
 *  Various Stuff:
 *
 *	SFM = Surface Feet per Minute = edge speed of the tool
 *	450 - 650 for HSS cutters
 *
 *
 *
 */

#include "ToolElement.h"

#include "../3D/Vector3.h"

#include <wx/string.h>
#include <wx/xml/xml.h>
#include <wx/dynarray.h>
#include <wx/txtstrm.h>

class Tool {
	// Constructor / Destructor
public:
	Tool();
	virtual ~Tool();

	// Member variables
public:
	wxString toolName;
	wxString comment;
	double shaftDiameter;
	double shaftLength;
	double maxSpeed;
	double feedCoefficient;
	unsigned int nrOfTeeth;
	ArrayOfToolElement elements;
	ArrayOfToolContourElement contour;
	int slot;
	static unsigned int resolution;

	// Methods
public:
	void ToStream(wxTextOutputStream & stream);
	bool FromStream(wxTextInputStream & stream);

	void GenerateContour(void);

	float GetPositiveLength(void) const;
	float GetNegativeLength(void) const;
	float GetMaxDiameter(void) const;

	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(Tool, ArrayOfTool);

#endif /* TOOL_H_ */
