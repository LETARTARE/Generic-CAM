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
///////////////////////////////////////////////////////////////////////////////

#ifndef PROJECT_H_
#define PROJECT_H_

#include "Object.h"
#include "StockFile.h"
#include "Workpiece.h"
#include "Run.h"
#include "Toolbox.h"
#include "ToolPath.h"

#include "../3D/OctreeGenerator.h"
#include "../3D/Quadtree.h"
#include "../machine/Machine.h"

#include <stddef.h>
#include <wx/defs.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/xml/xml.h>

/*!\class Project
 * \brief Holds the data for an project.
 *
 * An GenericCAM project consists of
 * - one or more objects (may be modified, sliced, inverted into mold forms, ect.)
 * - one or more pieces of stock material
 * - one or more run
 *    - a machine (with setup)
 *    - a toolbox for the machine (at least one tool)
 *    - toolpath generators
 *    - generated toolpaths
 *
 */

class Project {
	// Constructor / Destructor
public:
	Project();
	virtual ~Project();
	// Member variables
public:
	wxFileName fileName;
	wxString name;

	ArrayOfObject objects;
	StockFile stock;
	ArrayOfWorkpiece workpieces;
	ArrayOfRun run;

	//TODO: Does the toolbox belong to the settings/config file?
	Toolbox toolbox;

	OctreeGenerator octree;
	Quadtree quadtree;

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
	void Clear(void);
	bool Load(wxFileName fileName);
	bool Save(wxFileName fileName);

	void Paint(void);



	void GenerateToolPath(void);
	void CollectToolPath(void);

	size_t SetupMachineBed(bool flipped = false);
	void FlipRun(void);

	void InsertDrillGrid(Run &run, double sizex, double sizey, bool flipped =
			true);
	void GenerateTargets(void);

private:
	void XMLRemoveAllChildren(wxXmlNode* node);
};

#endif /* PROJECT_H_ */
