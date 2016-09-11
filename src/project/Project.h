///////////////////////////////////////////////////////////////////////////////
// Name               : Project.h
// Purpose            : Defines a Generic CAM Project.
// Thread Safe        : No
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

/*!\class Project
 * \ingroup document
 * \brief Holds the data of a project.
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
 * \todo: Rewrite the XML load/store to LUA script store/load.
 */

#include "../Config.h"

#include "Run.h"
#include "Workpiece.h"
#include "Object.h"

#include <wx/filename.h>
#include <wx/string.h>
#include <wx/defs.h>

#include <stddef.h>

class Project {
public:
	Project();
	virtual ~Project();

public:
	// Project properties
	wxFileName fileName;
	wxString name;

	ArrayOfObject objects; //!> Loaded objects
	ArrayOfWorkpiece workpieces; //!> Workpieces with objects
	ArrayOfRun run; //!> Machine runs on workpieces

	// Loaded and constructed items
//	bool processToolpath;
//	bool interruptProcessing;
	// Experimental stuff:
	//	OctreeGenerator octree;
	//	Quadtree quadtree;

	// For target generator
	//	double resolution;

//	DisplayType displayType;
//
//	bool displayGeometry;
//	bool displayMachine;
//	bool displayStock;
//	bool displayBoundingBox;
//	bool displayTargets;
//	bool displayToolpath;
//	bool displayOutLines;

	// Methods
public:
	void Clear(void);

	bool Load(wxFileName fileName);
	bool Save(wxFileName fileName);

	void LoadPattern(wxFileName filename);

	void Paint(void);

	void Update(void);

//	void PropagateChanges(void);
//	size_t ToolpathToGenerate(void);
//	bool ToolpathGenerate(void);
//	bool GenerateToolpaths(void);

//	wxString TollPathGenerateCurrent(void);

//	size_t generator_workpieceNr;
//	size_t generator_runNr;
//	size_t generator_toolpathNr;

#if(_GENERICCAM_USEMULTITHREADING == 1)
	wxMutex mtx_project;
	wxMutex mtx_generator;
#endif

};

#endif /* PROJECT_H_ */
