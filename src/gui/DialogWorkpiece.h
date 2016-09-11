///////////////////////////////////////////////////////////////////////////////
// Name               : DialogWorkpiece.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : wx-config needs option "adv"
// Author             : Tobias Schaefer
// Created            : 14.01.2015
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

#ifndef DIALOGWORKPIECE_H_
#define DIALOGWORKPIECE_H_

/*!\class DialogWorkpiece
 * \brief ...
 *
 * ...
 */

#include "../project/Project.h"
#include "../project/StockFile.h"
#include "gui.h"
#include <wx/cmdproc.h>


class DialogWorkpiece:public GUIWorkpiece {
public:
	DialogWorkpiece(wxWindow* parent, Project * project, StockFile * stock,
			wxCommandProcessor * commandProcessor);

	Project* project;
	StockFile* stock;
	wxCommandProcessor * commandProcessor;

	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnManageStock(wxCommandEvent& event);
	void OnAddStock(wxCommandEvent& event);
	void OnDBLClick(wxGridEvent& event);
	void OnSize(wxSizeEvent& event);
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

};

#endif /* DIALOGWORKPIECE_H_ */
