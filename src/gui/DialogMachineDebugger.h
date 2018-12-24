///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineDebugger.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.01.2015
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

#ifndef DIALOGMACHINEDEBUGGER_H_
#define DIALOGMACHINEDEBUGGER_H_

/*!\class DialogMachineDebugger
 * \brief ...
 *
 * ...
 */

#include "../controller/MidiPort.h"
#include "../project/Project.h"
#include "../project/machine/Machine.h"
#include "DialogMachineControl.h"
#include "DisplaySettings.h"
#include "gui.h"

class DialogMachineDebugger:public GUIMachineDebugger {
public:
	DialogMachineDebugger(wxWindow * parent,  MidiPort &midi);
	virtual ~DialogMachineDebugger();

	MidiPort * midi;

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:
	DialogMachineControl * machineControl;
	Machine machine;

protected:
	void Update(wxCommandEvent& event);

	void OnXClose(wxCloseEvent& event);
	void OnMachineLoad(wxCommandEvent& event);
	void OnMachineSave(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnScriptEvaluate(wxCommandEvent& event);
	void OnShowController(wxCommandEvent& event);
	void OnChangeStereo3D(wxCommandEvent& event);
};

#endif /* DIALOGMACHINEDEBUGGER_H_ */
