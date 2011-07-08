///////////////////////////////////////////////////////////////////////////////
// Name               : Project.h
// Purpose            : Defines a Generic CAM Project.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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


#ifndef PROJECT_H_
#define PROJECT_H_

#include "Object.h"
#include "Toolbox.h"
#include "../machine/Machine.h"
#include "../simulator/Workpiece.h"
#include "../simulator/ToolPath.h"

#include "Run.h"
#include "Target.h"
#include "Stock.h"
#include "Unit.h"

#include <wx/string.h>

#include <wx/dynarray.h>

/*!\class Project
 * \brief ...
 *
 * ...
 */

class Project {
	// Constructor / Destructor
public:
	Project();
	virtual ~Project();
	// Member variables
public:
	wxString projectName;

	ArrayOfObject objects;
	Machine machine;
	Toolbox toolbox;
	Stock stock;

	size_t activeObject;
	size_t activeStock;
	size_t activeTarget;

	ArrayOfTarget targets;
	ArrayOfRun run;
	ArrayOfToolPath toolpath;

	bool modified;

	bool displayGeometry;
	bool displayMachine;
	bool displayStock;
	bool displayWorkpiece;
	bool displayBoundingBox;
	bool displayTarget;
	bool displayToolpath;

	Unit Tolerance;
	Unit Distance;
	Unit LinearSpeed;
	Unit RotationalSpeed;

	// For target generator

	double resolution;

	double sliceThickness;
	double slotWidth;
	double supportDistance;
	double supportWidth;
	double supportHeight;
	double freeHeightAboveMaterial;

	double levelDrop;

	// Methods
public:

	void Paint(void);
	void Assemble(void);
	void GenerateTargets(void);
	void GenerateToolpath(size_t nrTarget);

};
WX_DECLARE_OBJARRAY(Project, ArrayOfProject)
;

#endif /* PROJECT_H_ */
