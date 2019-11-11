///////////////////////////////////////////////////////////////////////////////
// Name               : Tool.h
// Purpose            : A tool for the machine
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

#include "../3D/Vector3.h"

#include <wx/xml/xml.h>
#include <wx/txtstrm.h>
#include <wx/string.h>
#include <wx/dynarray.h>

class ToolContourElement {
public:
	ToolContourElement(bool cutting = false, bool partOfShaft = false);
	virtual ~ToolContourElement();
	Vector3 p1;
	Vector3 p2;
	Vector3 n1;
	Vector3 n2;
	bool isCutting;
	bool belongsToShaft;
};
WX_DECLARE_OBJARRAY(ToolContourElement, ArrayOfToolContourElement);

class ToolElement {
public:
	ToolElement();
	ToolElement(const wxString & string);
	virtual ~ToolElement();
	float d;
	float h;
	float r;
	//TODO Change the type to an enum.
	unsigned char t;
	bool cutting;

	wxString ToString(void) const;
	void FromString(wxString const &string);
};
WX_DECLARE_OBJARRAY(ToolElement, ArrayOfToolElement);

class Tool {
	friend class DexelTarget;
//	friend class DialogToolbox;
	friend class PanelTool;
	// Constructor / Destructor
public:
	Tool();
	virtual ~Tool();

	// Member variables
public:
	//TODO: Rename to "name":
	wxString toolName;
	int slotNr;
	wxString comment;
	double shaftDiameter;
	double shaftLength;
	double maxSpeed;
	double feedCoefficient;
	unsigned int nrOfTeeth;
	ArrayOfToolElement elements;

private:
	ArrayOfToolContourElement contour;

	// Methods
public:
	void Clear(void);

	float GetToolLength(void) const; ///< Total length of the tool outside the chuck. (Distance between Controlled-Point and Gauge-Point).
	float GetNegativeLength(void) const; ///< Length of the part, that disappears in the chuck.
	float GetMaxDiameter(void) const; ///< Maximum diameter of the tool.
	float GetCuttingDepth(void) const; ///< Length measured from the tip of the tool, that can cut.

	void GenerateContour(void);

	void ToStream(wxTextOutputStream & stream);
	bool FromStream(wxTextInputStream & stream);

	void Paint(void) const;
};
WX_DECLARE_OBJARRAY(Tool, ArrayOfTool);

#endif /* TOOL_H_ */
