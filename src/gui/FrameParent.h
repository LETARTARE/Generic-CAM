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

#ifndef _FRAMEPARENT_H_
#define _FRAMEPARENT_H_

/*!\class FrameParent
 * \brief Parentframe for the application
 *
 * Parent frame for the SDI application.
 */

#include "../Config.h"

#include <wx/config.h>
#include <wx/docview.h>
#include <wx/event.h>
#include <wx/help.h>
#include <wx/string.h>
#include <wx/timer.h>

#ifdef _USE_6DOFCONTROLLER
#include "../controller/Control3D.h"
#endif
#ifdef _USE_MIDI
#include "../controller/MidiPort.h"
#include "DialogSetupMidi.h"
#endif
#include "SettingsStereo3D.h"
#include "DialogSetupStereo3D.h"
#include "CollectionUnits.h"
#include "DialogSetupUnits.h"

class FrameParent:public wxDocParentFrame {
public:
	FrameParent(wxDocManager *manager, wxConfig* config, wxFrame *parent,
			wxWindowID id, const wxString& title);
	virtual ~FrameParent();

public:
	void OnChangeLanguage(wxCommandEvent& event);
	void OnSetupStereo3D(wxCommandEvent& event);

#ifdef _USE_6DOFCONTROLLER
	void OnSetupController(wxCommandEvent& event);
#endif
#ifdef _USE_MIDI
	void OnSetupMidi(wxCommandEvent& event);
#endif
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
	SettingsStereo3D settingsStereo3D;
	CollectionUnits units;

#ifdef _USE_6DOFCONTROLLER
	Control3D control;
#endif
#ifdef _USE_MIDI
	DialogSetupMidi* dialogSetupMidi;
	MidiPort midi;
#endif

	wxTimer timer; ///> Animation timer
	float t;
	float dt;

wxDECLARE_EVENT_TABLE();
};

#endif /* _FRAMEPARENT_H_ */
