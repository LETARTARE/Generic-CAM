///////////////////////////////////////////////////////////////////////////////
// Name               : FrameParent.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.10.2017
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

#ifndef SRC_GUI_FRAMEPARENT_H_
#define SRC_GUI_FRAMEPARENT_H_

/*!\class FrameParent
 * \brief Parentframe for the application
 *
 * Parent frame for the SDI application.
 */

#include <wx/config.h>
#include <wx/docview.h>
#include <wx/event.h>
#include <wx/help.h>
#include <wx/string.h>
#include <wx/timer.h>

#include "../controller/Control3D.h"
#include "../controller/MidiPort.h"
#include "DisplaySettings.h"

#include "../controller/DialogSetup6DOFController.h"
#include "DialogSetupMidi.h"
#include "DialogSetupStereo3D.h"
#include "DialogSetupUnits.h"

class FrameParent:public wxDocParentFrame {
public:
	FrameParent(wxDocManager *manager, wxConfig* config, wxFrame *parent,
			wxWindowID id, const wxString& title);
	virtual ~FrameParent();

public:
	void OnChangeLanguage(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent& event);
	void OnSetupStereo3D(wxCommandEvent& event);
	void OnSetupMidi(wxCommandEvent& event);
	void OnSetupUnits(wxCommandEvent& event);

	void OnRefreshAll(wxCommandEvent& event);
	void OnRefreshAll3D(wxCommandEvent& event);
	void OnRefreshView(wxCommandEvent& event);
	void OnRefreshView3D(wxCommandEvent& event);

	void OnTimer(wxTimerEvent& event);

	void OnAbout(wxCommandEvent& WXUNUSED(event));
	void OnHelp(wxCommandEvent& WXUNUSED(event));

public:
	wxConfig* config;

	wxHelpController* m_helpController;
	DialogSetupStereo3D * dialogSetupStereo3D;
	DialogSetupMidi * dialogSetupMidi;
	DisplaySettings settings;

	Control3D control;
	MidiPort midi;

	wxTimer timer; ///> Animation timer
	float t;
	float dt;

wxDECLARE_EVENT_TABLE();
};

#endif /* SRC_GUI_FRAMEPARENT_H_ */
