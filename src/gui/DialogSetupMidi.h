///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupMidi.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.09.2017
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

#ifndef SRC_GUI_DIALOGSETUPMIDI_H_
#define SRC_GUI_DIALOGSETUPMIDI_H_

/*!\class DialogSetupMidi
 * \brief ...
 *
 * ...
 */

#include "../StdInclude.h"
#include "../controller/MidiPort.h"
#include <wx/timer.h>

#include "gui.h"

class DialogSetupMidi:public GUISetupMidi {
public:
	DialogSetupMidi(wxWindow* parent, MidiPort &midi);
	virtual ~DialogSetupMidi();

private:
	MidiPort* midi;

	wxTimer timer;

	// Methods
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
	void OnTimer(wxTimerEvent& event);

	void OnCloseX(wxCloseEvent& event);
	void OnSelect(wxCommandEvent& event);
	void OnRefresh(wxCommandEvent& event);
	void OnCycle(wxCommandEvent& event);
	void OnConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnClear(wxMouseEvent& event);
};

#endif /* SRC_GUI_DIALOGSETUPMIDI_H_ */
