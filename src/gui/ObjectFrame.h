///////////////////////////////////////////////////////////////////////////////
// Name               : ObjectFrame.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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


#ifndef OBJECTFRAME_H_
#define OBJECTFRAME_H_

#include "gui.h"
#include "../project/Project.h"

/*!\class ObjectFrame
 * \brief ...
 *
 * ...
 */

class ObjectFrame:public GUIObjectFrame {
	// Constructor/ Destructor
public:
	ObjectFrame(wxWindow* parent);
	virtual ~ObjectFrame();

	// Member Variables

	Project* linkedProject;

	// Methods
public:
	void InsertProject(Project *project);

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void OnClose(wxCommandEvent& event);
};

#endif /* OBJECTFRAME_H_ */
