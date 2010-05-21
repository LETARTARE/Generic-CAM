///////////////////////////////////////////////////////////////////////////////
// Name               : Control6DOFDialog.h
// Purpose            : Setup dialog for 6DOF controller.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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


#ifndef CONTROL6DOFDIALOG_H_
#define CONTROL6DOFDIALOG_H_

#include "../StdInclude.h"
#include "../Config.h"
#include "../controller/Control3D.h"
#include "gui.h"

class Control6DOFDialog:public GUIControl6DOFDialog {
	// Constructor / Destructor
public:
	Control6DOFDialog(wxWindow* parent);
	virtual ~Control6DOFDialog();

	// Member Variables
protected:
	Control3D* control;

private:
	wxTimer timer;

	// Member Functions
public:
	void InsertController(Control3D& control);


private:
	//TODO: The next function shouldn't be here!
	Control3D *GetControl()
	{
		return control;
	}
protected:
	void OnConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);

	void UpdateData();
};

#endif /* CONTROL6DOFDIALOG_H_ */
