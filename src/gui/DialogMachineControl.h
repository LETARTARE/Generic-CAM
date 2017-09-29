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

#include <wx/timer.h>
#include "../controller/MidiPort.h"
#include "../StdInclude.h"
#include "../project/Project.h"
#include "DisplaySettings.h"
#include "gui.h"

class DialogMachineControl:public GUIMachineControl {
public:
	DialogMachineControl(wxWindow * parent, DisplaySettings * settings, MidiPort * midi);
	virtual ~DialogMachineControl();


	DisplaySettings * settings;

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	double X, Y, Z;
	double A, B, C;
	double U, V, W;

	float groupXYZLimit;
	float groupABCLimit;
	float groupUVWLimit;

	unsigned int sliderSteps;
	unsigned int pageSize;
	unsigned int lineSize;

	MidiPort * midi;
	wxTimer timer;

private:
	bool TransferDataToWindowSliders(void);
	bool TransferDataFromWindowSliders(void);
	bool TransferDataToWindowTextbox(void);

protected:
	
	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnZero(wxMouseEvent& event);
	void OnTrack(wxScrollEvent& event);
	void OnTextChanged(wxCommandEvent& event);

	void OnTimer(wxTimerEvent& event);

};

#endif /* DIALOGMACHINECONTROL_H_ */
