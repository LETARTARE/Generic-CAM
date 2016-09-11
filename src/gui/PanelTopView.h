///////////////////////////////////////////////////////////////////////////////
// Name               : PanelTopView.h
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

#ifndef PANELTOPVIEW_H_
#define PANELTOPVIEW_H_

/*!\class PanelTopView
 * \brief ...
 *
 * ...
 */

#include "../project/Project.h"
#include <wx/panel.h>
#include <wx/gdicmn.h>

class PanelTopView:public wxPanel {
public:
	PanelTopView(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style =
			wxTAB_TRAVERSAL);
	virtual ~PanelTopView();
	// Member Variables
public:

private:
	Project * project;

	//Methods
public:
	void InsertProject(Project * project);

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent &event);

	void OnMotion(wxMouseEvent& event);
	void OnLeftDown(wxMouseEvent& event);

private:
	int GetFirstSelectedWorkpiece();

};

#endif /* PANELTOPVIEW_H_ */
