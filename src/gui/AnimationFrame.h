///////////////////////////////////////////////////////////////////////////////
// Name               : AnimationFrame.h
// Purpose            : A window displaying the animation controls.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.07.2011
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
//$LastChangedDate: 2010-05-22 01:40:18 +0200 (Sa, 22. Mai 2010) $
//$Revision: 45 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#ifndef ANIMATIONFRAME_H_
#define ANIMATIONFRAME_H_

#include "gui.h"

class AnimationFrame:public GUIAnimationFrame {
	// Constructor/ Destructor
public:
	AnimationFrame(wxWindow* parent);
	virtual ~AnimationFrame();

	// Member Variables
public:
	Project* linkedProject;

	// Methods
public:
	void InsertProject(Project *project);

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
	void OnClose(wxCommandEvent &event);

	void OnLast(wxCommandEvent& event);
	void OnBegin(wxCommandEvent& event);
	void OnPlayStop(wxCommandEvent& event);
	void OnEnd(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);

};

#endif /* ANIMATIONFRAME_H_ */
