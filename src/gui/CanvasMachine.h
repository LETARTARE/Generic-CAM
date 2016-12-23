///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasMachine.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 21.12.2016
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

#ifndef CANVASMACHINE_H_
#define CANVASMACHINE_H_

/*!\class CanvasMachine
 * \brief Canvas to display a Machine
 *
 * Canvas displaying a Machine. It is used for debugging purposes.
 */

#include "../project/machine/Machine.h"
#include "../3D/OpenGLCanvas.h"

#include <wx/string.h>

class CanvasMachine:public OpenGLCanvas {
public:
	CanvasMachine(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0,
			const wxString& name = _T(""));
	virtual ~CanvasMachine();

private:
	Machine* machine;

	// Methods
public:
	void InsertMachine(Machine* machine);
	void Render();
};

#endif /* CANVASMACHINE_H_ */
