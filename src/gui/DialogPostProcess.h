///////////////////////////////////////////////////////////////////////////////
// Name               : DialogPostProcess.h
// Purpose            : Dialog for exporting toolpaths
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_GUI_DIALOGPOSTPROCESS_H_
#define SRC_GUI_DIALOGPOSTPROCESS_H_

#include "gui.h"

#include "../project/post/CollectionPostProcessor.h"
#include "../project/Selection.h"

#include <wx/event.h>

class DialogPostProcess:public GUIPostProcess {
public:
	DialogPostProcess(wxWindow* parent);

	CollectionPostProcessor postprocessors;

	void SetSelection(const Selection &selection);
	bool SelectionIsOK(void) const;
	bool TransferDataToWindow(void);

	void OnXClose(wxCloseEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnPropertyGridChange(wxPropertyGridEvent &event);
	void OnRefresh(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
private:
	void UpdateParameter(void);
	Selection selected;
};

#endif /* SRC_GUI_DIALOGPOSTPROCESS_H_ */
