///////////////////////////////////////////////////////////////////////////////
// Name               : DialogToolWizard.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 30.12.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef DIALOGTOOLWIZARD_H_
#define DIALOGTOOLWIZARD_H_

/*!\class DialogToolWizard
 * \brief ...
 *
 * ...
 */

#include "../StdInclude.h"
#include "gui.h"

class DialogToolWizard:public GUIToolWizard {
public:
	DialogToolWizard(wxWindow* parent);
	virtual ~DialogToolWizard();

	virtual void OnAddTool(wxCommandEvent& event);
	virtual void OnSetShape(wxCommandEvent& event);
	virtual void OnClose(wxCommandEvent& event);

};

#endif /* DIALOGTOOLWIZARD_H_ */
