///////////////////////////////////////////////////////////////////////////////
// Name               : TreeSetup.h
// Purpose            : Takes care of the treeview in the mainframe
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.01.2015
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

#ifndef TREESETUP_H_
#define TREESETUP_H_

/*!\class TreeSetup
 * \brief Takes care of the treeview in the mainframe
 *
 * This class sets up the treeview in the main window. This is an extra class, because the
 * treeview is quite complicated to program. To prevent these functions from cluttering up the
 * already well filled main frame class, this classs collects all functionality concerning the
 * tree view.
 *
 * The TreeView is filles by the Update function with objects derived of TreeItem. This class
 * identifies the item clicked upon.
 *
 * This class provides a minimal interface to the outside. The whole ugly mess is hidden
 * in the depth of these private functions.
 */

#include <stddef.h>
#include <wx/string.h>
#include <wx/thread.h>
//#include <wx/treebase.h>
#include <wx/treectrl.h>

#include "../project/Selection.h"
#include "TreeItem.h"

class FrameMain;

class TreeSetup {
public:
	TreeSetup(FrameMain * parent, wxTreeCtrl * tree);
	virtual ~TreeSetup();

	void Update(void); ///< Populate the wxTreeView with all items from the Project. Also update the view.
	void SelectonToTree(const Selection &sel); ///< Set the selection in the tree to the selection marked in the Project.
	Selection TreeToSelection(void); ///< Update the "selected" variables in the Project from the selection in the tree.

//	int GetFirstSelectedObject(void);
//	int GetFirstSelectedWorkpiece(void);
//	int GetFirstSelectedRun(void);
//	int GetFirstSelectedToolpath(void);
//
//	int GetWorkpieceFromLink(int linkNr);
//	int GetObjectFromLink(int linkNr);

private:
	void Reset(void);
	void SetAtLevel(int level, const wxString& name, TreeItem::itemtype type,
			size_t ID);
	void FinishLevel(int level, bool autoExpand = false);

	bool GetSelection(void);
	void SetSelection(bool selection = true);

	wxMutex loopGuard; ///< Breaks update loops. Tree updates variable updates tree updates variable updates ...

	bool levelModified;
	wxTreeItemIdValue cookie;
	wxTreeItemId * id;

	wxTreeItemId groupObjects;
	wxTreeItemId groupRun;
	wxTreeItemId groupGenerator;

	size_t maxId;
	int currentLevel;

	FrameMain * parent;
	wxTreeCtrl * tree;
};

#endif /* TREESETUP_H_ */
