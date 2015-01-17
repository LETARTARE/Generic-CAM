///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineControl.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.01.2015
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

#ifndef DIALOGMACHINECONTROL_H_
#define DIALOGMACHINECONTROL_H_

/*!\class DialogMachineControl
 * \brief ...
 *
 * ...
 */

#include "../project/Project.h"
#include "DisplaySettings.h"
#include "gui.h"

class DialogMachineControl:public GUIMachineControl {
public:
	DialogMachineControl(wxWindow * parent, Project * project,
			DisplaySettings * settings);

	Project* project;
	DisplaySettings * settings;

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:

protected:
	
	void OnClose(wxCloseEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnTrack(wxScrollEvent& event);
	void OnTextChanged(wxCommandEvent& event);
};

#endif /* DIALOGMACHINECONTROL_H_ */
