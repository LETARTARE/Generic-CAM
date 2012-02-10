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
#include "Workpiece.h"
#include "ToolPath.h"

#include "Run.h"
#include "Target.h"
#include "Stock.h"
#include "Unit.h"

#include <wx/string.h>
#include <wx/xml/xml.h>

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
	wxFileName fileName;
	wxString projectName;

	Machine machine;

	Toolbox toolbox;
	Stock stock;

	size_t activeObject;
	size_t activeStock;
	size_t activeTarget;
	size_t activeRun;

	ArrayOfObject objects;
	ArrayOfTarget targets;
	ArrayOfRun runs;

	bool modified;

	bool displayGeometry;
	bool displayMachine;
	bool displayStock;
	bool displayWorkpiece;
	bool displayBoundingBox;
	bool displayRun;
	bool displayTargets;
	bool displayToolpath;
	bool displayOutLines;

	Unit Tolerance;
	Unit Distance;
	Unit LinearSpeed;
	Unit RotationalSpeed;

	// For target generator

	double resolution;

	// Slot around Objects
	double slotWidth;
	double supportDistance;
	double supportWidth;
	double supportHeight;




protected:
	wxXmlDocument doc;

	double middleY;
	double offsetX;



	// Methods
public:
	void ClearProject(void);
	void Paint(void);
	bool Save(wxFileName fileName);
	bool Load(wxFileName fileName);

	void Assemble(void);

	void GenerateToolPath(void);
	void CollectToolPath(void);

	size_t SetupMachineBed(bool flipped=false);
	void FlipRun(void);


	void InsertDrillGrid(Run &run, double sizex, double sizey, bool flipped =
			true);
	void GenerateTargets(void);

private:
	void XMLRemoveAllChildren(wxXmlNode* node);
};
WX_DECLARE_OBJARRAY(Project, ArrayOfProject)
;

#endif /* PROJECT_H_ */
