///////////////////////////////////////////////////////////////////////////////
// Name               : ToolPanel.h
// Purpose            : 2D view of a tool.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
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


#ifndef TOOLPANEL_H_
#define TOOLPANEL_H_

#include <wx/panel.h>
#include <wx/dcclient.h>

#include "../machine/Tool.h"

class ToolPanel:public wxPanel {
	// Costructor/ Destructor
public:
	ToolPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			wxTAB_TRAVERSAL);
	virtual ~ToolPanel();

	// Member Variables
public:

private:
	Tool* tool;

	//Methods
public:

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent &event);

	void OnMotion(wxMouseEvent& event);
	void OnLeftDown(wxMouseEvent& event);

	void InsertTool(Tool& t);

};

#endif /* TOOLPANEL_H_ */
