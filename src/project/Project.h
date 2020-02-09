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
 * An GenericCAM project consists of the Object%s, Workpiece%s and Run%s.
 *
 * The linking of all parts of the project is describes in the \ref document document.
 *
 * \todo Rewrite to XML load/store for future backwards compatibility.
 */

#include "Selection.h"
#include "Object.h"
#include "Run.h"
#include "Tool.h"

#include <stddef.h>
#include <map>
#include <vector>

#include <wx/filename.h>
#include <wx/string.h>
#include <wx/docview.h>
#include <wx/defs.h>

#if wxUSE_STD_IOSTREAM
typedef wxSTD istream DocumentIstream;
typedef wxSTD ostream DocumentOstream;
#else // !wxUSE_STD_IOSTREAM
typedef wxInputStream DocumentIstream;
typedef wxOutputStream DocumentOstream;
#endif // wxUSE_STD_IOSTREAM/!wxUSE_STD_IOSTREAM

class Project:public wxDocument {
	friend class ProjectView;
	friend class CommandProjectRename;
	friend class CommandObjectLoad;
	friend class CommandObjectRename;
	friend class CommandObjectTransform;
	friend class CommandObjectRemove;
	friend class CommandRunAdd;
	friend class CommandRunRename;
	friend class CommandRunSetObject;
	friend class CommandRunSetCorrdinateSystem;
	friend class CommandRunSetStockType;
	friend class CommandRunSetStockObject;
	friend class CommandRunSetStockBox;
	friend class CommandRunSetStockOrigin;
	friend class CommandRunGeneratorAdd;
	friend class CommandRunGeneratorUpdate;
	friend class CommandRunGeneratorRename;
	friend class CommandRunGeneratorDelete;
	friend class CommandRunRemove;
	friend class CommandRunMachineLoad;

public:
	Project();
	virtual ~Project();

public:

//	bool processToolpath;
//	bool interruptProcessing;

// Granularity for Dexel - Simulator
	double minResolution;
	size_t maxCells;

	// Methods
public:
	void Update(void);

	bool Has(const Selection &sel) const;
	bool Has(const Selection::Type type, const size_t ID) const;

	bool DoSaveDocument(const wxString& file);
	bool DoOpenDocument(const wxString& file);

	//TODO Remove the functions below and join them into the functions above
	bool Load(wxFileName fileName);
	bool Save(wxFileName fileName);

	bool GenerateToolpaths(void);
	bool SaveToolpath(wxFileName fileName, int runNr);

	bool LoadDefaultTools(wxString fileName, bool loadAll = false);

	BoundingBox GetBBox(const Selection & selected) const;

	size_t GetMaxObjectID(void) const;
	size_t GetMaxRunID(void) const;
	size_t GetMaxGeneratorID(void) const;
	size_t GetToolCount(void) const;

	std::set <size_t> GetAllObjectIDs(void) const;
	std::set <size_t> GetAllRunIDs(void) const;
	std::set <size_t> GetAllGeneratorIDs(size_t runID) const;

	const Object & Get3DObject(size_t ID) const;
	const Run & GetRun(size_t ID) const;
	const Generator * GetGenerator(size_t runID, size_t ID);
	const std::vector <Tool> * GetTools(void) const;
	const std::map <size_t, Object> * GetObjects(void) const;
	const Tool & GetTool(size_t index) const;
private:

	std::map <size_t, Object> objects;
	std::map <size_t, Run> run;
	std::vector <Tool> tools;

	size_t maxObjectID;
	size_t maxRunID;
	size_t maxGeneratorID;

#if(_GENERICCAM_USEMULTITHREADING == 1)
	wxMutex mtx_project;
	wxMutex mtx_generator;
#endif

DECLARE_DYNAMIC_CLASS(Project);
};

#endif /* PROJECT_H_ */
