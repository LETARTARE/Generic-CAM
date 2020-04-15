///////////////////////////////////////////////////////////////////////////////
// Name               : TreeItem.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.12.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef TREEITEM_H_
#define TREEITEM_H_

/*!\class TreeItem
 * \brief Items for the TreeSetup
 *
 * This class is used to identify the objects in the TreeView. Each item has
 * a ItemDataType and a number. This is used to identify which part of the tree
 * has been click upon.
 *
 */

#include <wx/treectrl.h>

class TreeItem:public wxTreeItemData {
public:
	enum itemtype {
		itemUnknown = 0,
		itemObject = 1,
		itemRun = 2,
		itemGenerator,
		itemSubObject,
		itemGroupObjects,
		itemGroupRun,
		itemProject
	};

	TreeItem(itemtype type = itemUnknown, size_t ID = 0);

	itemtype type;
	size_t ID;
};

#endif /* TREEITEM_H_ */
