///////////////////////////////////////////////////////////////////////////////
// Name               : FlipDrillPattern.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 20.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef FLIPDRILLPATTERN_H_
#define FLIPDRILLPATTERN_H_

/*!\class FlipDrillPattern
 * \ingroup document
 * \brief Pattern for flipping the workpiece
 *
 * The for alignment of two-sided workpieces, a drillpattern is put on the top of the workpiece.
 * The same pattern is drilled into the base of the machine. This allows for simple turning-over
 * of the workpiece.
 *
 */

#include "../3D/Polygon25.h"
#include "Tool.h"
#include "ToolPath.h"

#include <wx/string.h>
#include <wx/dynarray.h>

class DrillPosition {
public:
	DrillPosition();
	float x;
	float y;
	float depth;
	float diameter;
};
WX_DECLARE_OBJARRAY(DrillPosition, ArrayOfDrillPosition);

class FlipDrillPattern {
public:
	FlipDrillPattern();
	wxString name;
	ArrayOfDrillPosition position;
	ToolPath toolpath;
	Polygon25 outLine;

public:
	void Paint(void) const;
private:

	void SetupDrill(Tool &tool, double diameter, double depth);
};
WX_DECLARE_OBJARRAY(FlipDrillPattern, ArrayOfFlipDrillPattern);

#endif /* FLIPDRILLPATTERN_H_ */
