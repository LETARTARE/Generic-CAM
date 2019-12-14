///////////////////////////////////////////////////////////////////////////////
// Name               : DialogJobSetup.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.11.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_GUI_DIALOGJOBSETUP_H_
#define SRC_GUI_DIALOGJOBSETUP_H_

/*!\class DialogJobSetup
 * \brief ...
 *
 * ...
 */

#include "gui.h"

class DialogJobSetup:public GUIJobSetup {
public:
	DialogJobSetup(wxWindow* parent);
	virtual ~DialogJobSetup();

	void SetRunID(size_t runID);

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void OnXClose(wxCloseEvent& event);
	void OnSelect(wxCommandEvent& event);
	bool OnSelected(size_t ID, Selection selection);
	void OnGetSizeFromObject(wxCommandEvent& event);

private:
	size_t runID;
};

#endif /* SRC_GUI_DIALOGJOBSETUP_H_ */
