///////////////////////////////////////////////////////////////////////////////
// Name               : DialogAnimation.h
// Purpose            : A window displaying the animation controls.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.07.2011
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
///////////////////////////////////////////////////////////////////////////////

#ifndef ANIMATIONFRAME_H_
#define ANIMATIONFRAME_H_

#include "../StdInclude.h"
#include "gui.h"

#include "../project/generator/DexelTarget.h"
#include <wx/timer.h>

class DialogAnimation:public GUIAnimation {
	// Constructor/ Destructor
public:
	DialogAnimation(wxWindow *parent, Project *project);
	virtual ~DialogAnimation();

	bool TransferDataToWindow(void);

	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnSelectToolpath(wxCommandEvent& event);
	void OnChangeSimulation(wxCommandEvent& event);
	void OnChangeTime(wxCommandEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnTimer(wxTimerEvent& event);

	void OnFirst(wxCommandEvent& event);
	void OnPrev(wxCommandEvent& event);
	void OnPlayStop(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);
	void OnLast(wxCommandEvent& event);

private:
	void PositionSlider(void);
	int GetSelectedRun(void);
	void InitSimulation(void);
	wxString SecondsToTC(const double t);

	// Member Variables
public:
	Project* project;
	Run* run;
	MachineSimulator* simulator;

	DexelTarget model;

	bool simulateWorkpiece;

private:
	bool loopGuard;
	wxTimer timer;
};

#endif /* ANIMATIONFRAME_H_ */
