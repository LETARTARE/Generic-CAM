///////////////////////////////////////////////////////////////////////////////
// Name               : TargetDialog.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.07.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#ifndef TARGETDIALOG_H_
#define TARGETDIALOG_H_

#include "../StdInclude.h"
#include "gui.h"

/*!\class TargetDialog
 * \brief ...
 *
 * ...
 */

class TargetDialog:public GUITargetDialog {
	// Constructor/ Destructor

public:
	TargetDialog(wxWindow* parent);
	virtual ~TargetDialog();
	// Member variables
private:
	Project* linkedProject;

	// Methods
public:
	void InsertProject(Project *project);


private:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
	void OnClose(wxCommandEvent& event);

	void OnFromStock(wxCommandEvent& event);
	void OnGenerate(wxCommandEvent& event);


};

#endif /* TARGETDIALOG_H_ */
