///////////////////////////////////////////////////////////////////////////////
// Name               : DialogPlacement.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.01.2015
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

#ifndef DIALOGPLACEMENT_H_
#define DIALOGPLACEMENT_H_

/*!\class DialogPlacement
 * \brief ...
 *
 * ...
 */

#include "../project/Project.h"
#include "DisplaySettings.h"
#include "gui.h"

#include <wx/wx.h>
#include <wx/cmdproc.h>

class DialogPlacement:public GUIPlacement {
public:
	DialogPlacement(wxWindow* parent, Project * project,
			wxCommandProcessor * commandProcessor, DisplaySettings * settings);

private:
	Project* project;
	DisplaySettings * settings;
	wxCommandProcessor * commandProcessor;

	// Methods
public:

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

protected:
	int GetSelectedWorkpiece(void);
	int GetSelectedPlacement(int workpieceNr);

	void OnXClose(wxCloseEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnExtraAdd(wxCommandEvent& event);
	void OnSelectWorkpiece(wxCommandEvent& event);
	void OnSelectObject(wxCommandEvent& event);
	void OnChangePosition(wxCommandEvent& event);
	void OnChangeSlider(wxScrollEvent& event);
	void OnSelectForm(wxCommandEvent& event);
	void OnTransform(wxCommandEvent& event);

};

#endif /* DIALOGPLACEMENT_H_ */
