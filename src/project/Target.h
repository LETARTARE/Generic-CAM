///////////////////////////////////////////////////////////////////////////////
// Name               : Target.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.07.2011
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


#ifndef TARGET_H_
#define TARGET_H_

/*!\class Target
 * \brief ...
 *
 * ...
 */

#include "../generator/Imprinter.h"
#include <wx/dynarray.h>
#include <wx/xml/xml.h>

#include "Object.h"
#include "../generator/Polygon25.h"
#include "../simulator/ToolPath.h"
#include "../machine/Tool.h"
//#include <cstddef>

class Target:public Imprinter {
	// Constructor/ Destructor
public:
	Target();
	virtual ~Target();

	//Member variables:
public:
	//double shiftZ;
	Polygon25 outLine;
	Polygon25 supportLine;

	ToolPath toolpath;
	ToolPath toolpathFlipped;

	//Methods:
public:
	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

	void InsertObject(Object &object);

	int NextDir(int sx, int sy, double height, int olddir);
	int NextDir(int sx, int sy, int olddir);
	const Polygon25 GeneratePolygon(int sx, int sy, double height);
	const Polygon25 GeneratePolygon(int sx, int sy);
	const Polygon25 GenerateConvexOutline(void);

	// Polygon3 Methods

	void PolygonDropTarget(Polygon3 &polygon, Target &tool);
	void PolygonDrop(Polygon3 &polygon, double level);
	void FillOutsidePolygon(Polygon3 &polygon);

	void SetupDrill(Tool &tool, double diameter, double depth);

	void AddSupport(Polygon3 &polygon, double distance, double height,
			double width, double slotWidth);

	void Simulate(void);

	void Paint(void);
};
WX_DECLARE_OBJARRAY(Target, ArrayOfTarget)
;

#endif /* TARGET_H_ */
