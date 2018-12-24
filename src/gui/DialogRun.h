///////////////////////////////////////////////////////////////////////////////
// Name               : DialogRun.h
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

#ifndef DIALOGRUN_H_
#define DIALOGRUN_H_

/*!\class DialogRun
 * \brief ...
 *
 * ...
 */

#include "../StdInclude.h"
#include "../project/Project.h"
#include "../project/ToolBox.h"
#include "DisplaySettings.h"
#include "gui.h"
#include <wx/cmdproc.h>

class DialogRun:public GUIRun {
public:
	DialogRun(wxWindow* parent);
	virtual ~DialogRun();

private:
	bool loopGuard;

	// Methods
public:

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
private:
	Project* GetProject(void);
	int GetSelected(void);

	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnRunSelect(wxCommandEvent& event);
	void OnWorkpieceSelect(wxCommandEvent& event);
	void OnRotate(wxCommandEvent& event);
	void OnMachineLoad(wxCommandEvent& event);
	void OnToolRemove(wxCommandEvent& event);
	void OnToolAdd(wxCommandEvent& event);
};

#endif /* DIALOGRUN_H_ */
