///////////////////////////////////////////////////////////////////////////////
// Name               : ToolboxFrame.h
// Purpose            : A window to edit tools in the toolbox.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#ifndef TOOLBOXFRAME_H_
#define TOOLBOXFRAME_H_

#include "gui.h"
#include "../project/Toolbox.h"

class ToolboxFrame:public GUIToolboxFrame {
	// Constructor/ Destructor

public:
	ToolboxFrame(wxWindow* parent);
	virtual ~ToolboxFrame();

	// Member Variables

	Toolbox* linkedToolbox;

	unsigned int selectedTool;
	unsigned int selectedElement;

	// Methods
public:
	void OnClose(wxCommandEvent& event);
	void InsertToolBox(Toolbox* toolbox);
	void OnChangeStereo3D(wxCommandEvent& event);
	void UpdateDisplay(bool direction = true);
	void SetController(Control3D& control);
};

#endif /* TOOLBOXFRAME_H_ */
