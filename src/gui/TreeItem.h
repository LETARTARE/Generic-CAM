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

#include <wx/treectrl.h>

enum ItemDataType {
	itemUnknown = 0, ///> Default
	itemProject,
	itemGroupObject,
	itemObject,
	itemSubObject,
	itemGroupWorkpiece,
	itemWorkpiece,
	itemPlacement,
	itemObjectLink,
	itemGroupRun,
	itemRun,
	itemRunWorkpiece,
	itemMachine,
	itemToolpath
};

class TreeItem:public wxTreeItemData {
public:

	TreeItem(ItemDataType dataType = itemUnknown, size_t nr = 0);

	ItemDataType dataType;
	size_t nr;
};

#endif /* TREEITEM_H_ */
