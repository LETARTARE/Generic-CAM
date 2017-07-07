///////////////////////////////////////////////////////////////////////////////
// Name               : DnDFile.h
// Purpose            : Drag&Drop target for files
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.06.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef DNDFILE_H_
#define DNDFILE_H_

/*!\class DnDFile
 * \brief Drag&Drop target for files
 *
 * This target is associated with the treeview and the main 3D window (from FrameMain).
 * It receives files (filenames). According to the type, it either issues a object load
 * command (*.stl, *.gts, *.dxf) or loads a project (*.zip, *.prj).
 */

#include "FrameMain.h"
#include "../project/Project.h"
#include <wx/dnd.h>

class DnDFile:public wxFileDropTarget {
public:
	DnDFile(Project *project, FrameMain* parent);
	virtual bool OnDropFiles(wxCoord x, wxCoord y,
			const wxArrayString& filenames);

private:
	Project* project;
	FrameMain* parent;
};

#endif /* DNDFILE_H_ */
