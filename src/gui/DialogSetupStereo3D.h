///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupStereo3D.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.01.2015
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

#ifndef DIALOGSETUPSTEREO3D_H_
#define DIALOGSETUPSTEREO3D_H_

/*!\class DialogSetupStereo3D
 * \brief Dialog to setup stereo 3d anaglyph glasses
 */

#include "../StdInclude.h"

#include "guiSetupStereo3D.h"

#include <wx/event.h>

class DisplaySettings;

class DialogSetupStereo3D:public GUISetupStereo3D {
public:
	DialogSetupStereo3D(wxWindow* parent, DisplaySettings * settings);

private:
	DisplaySettings * settings;

	// Methods
public:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:
	void OnXClose(wxCloseEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnColorChanged(wxColourPickerEvent& event);
	void OnSwap(wxCommandEvent& event);
	void OnTextChange(wxCommandEvent& event);
};

#endif /* DIALOGSETUPSTEREO3D_H_ */
