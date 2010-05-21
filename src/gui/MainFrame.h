///////////////////////////////////////////////////////////////////////////////
// Name               : MainFrame.h
// Purpose            : The main window.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include "../Config.h"
#include "../StdInclude.h"
#include "gui.h"
#include "../simulator/Machine.h"
#include "../simulator/MachineSimulator.h"
#include "../controller/Control3D.h"
#include <wx/config.h>
#include <wx/log.h>


class MainFrame:public GUIMainFrame {
	// Constructor/ Destructor
public:
	MainFrame(wxWindow* parent);
	virtual ~MainFrame();

	// Member variables
private:
	wxConfig *config;
	Control3D control;
	wxLogWindow* logWindow;

	MachineSimulator simulator;

	wxTimer timer;
	float t;

	// Methods
private:

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSelectDataFrame(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent &event);

	void OnChangeStereo3D(wxCommandEvent &event);
	void OnLoadMachine(wxCommandEvent &event);
	void OnReloadMachine(wxCommandEvent &event);
	void OnLoadToolbox(wxCommandEvent &event);
	void OnSaveToolbox(wxCommandEvent &event);
	void OnEditToolbox(wxCommandEvent& event);

	void OnLoadGCodes(wxCommandEvent &event);

	void OnTimer(wxTimerEvent& event);

};

#endif /* MAINFRAME_H_ */
