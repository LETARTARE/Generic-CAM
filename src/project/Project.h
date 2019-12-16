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

#include "../Config.h"

#include "Object.h"

#include <wx/filename.h>
#include <wx/string.h>
#include <wx/defs.h>
#include <map>

#include <stddef.h>
#include <wx/docview.h>

#include "../3D/BoundingBox.h"
#include "Run.h"
#include "Selection.h"
//
//#if wxUSE_STD_IOSTREAM
//typedef wxSTD istream DocumentIstream;
//typedef wxSTD ostream DocumentOstream;
//#else // !wxUSE_STD_IOSTREAM
//typedef wxInputStream DocumentIstream;
//typedef wxOutputStream DocumentOstream;
//#endif // wxUSE_STD_IOSTREAM/!wxUSE_STD_IOSTREAM

class Project:public wxDocument {
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
	friend class CommandRunRemove;

public:
	Project();
	virtual ~Project();

public:

//	bool processToolpath;
//	bool interruptProcessing;

// Granularity
//	double resX;
//	double resY;
	//TODO Make the granularity a parameter.

	// Methods
public:
	void Clear(void);
	void Update(void);

	bool Has(const Selection &sel) const;
	bool Has(const Selection::Type type, const size_t ID) const;

	bool DoSaveDocument(const wxString& file);
	bool DoOpenDocument(const wxString& file);
	//TODO Remove the functions below and join them into the functions above
	bool Load(wxFileName fileName);
	bool Save(wxFileName fileName);

	bool GenerateToolpaths(void); ///< Direct generation of all toolpaths.
	bool SaveToolpath(wxFileName fileName, int runNr);

	void Paint(const OpenGLMaterial &face, const OpenGLMaterial &edge,
			const Selection &sel) const;
	void PaintPick(void) const;

	BoundingBox GetBBox(const Selection & selected) const;

	size_t GetMaxObjectID(void) const;
	size_t GetMaxRunID(void) const;

	std::set <size_t> GetAllObjectIDs(void) const;
	const Object & GetObject(size_t ID) const;

	std::set <size_t> GetAllRunIDs(void) const;
	const Run & GetRun(size_t ID) const;

private:

	std::map <size_t, Object> objects; //!< Loaded objects
	size_t maxObjectID;
	std::map <size_t, Run> run; //!< Loaded objects
	size_t maxRunID;

#if(_GENERICCAM_USEMULTITHREADING == 1)
	wxMutex mtx_project;
	wxMutex mtx_generator;
#endif

DECLARE_DYNAMIC_CLASS(Project)
	;
};

#endif /* PROJECT_H_ */
