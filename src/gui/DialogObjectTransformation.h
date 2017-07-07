///////////////////////////////////////////////////////////////////////////////
// Name               : DialogObjectTransformation.h
// Purpose            : Dialog for manipulating objects
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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
///////////////////////////////////////////////////////////////////////////////

#ifndef DIALOGOBJECTTRANSFORMATION_H_
#define DIALOGOBJECTTRANSFORMATION_H_

/*!\class DialogObjectTransformation
 * \brief ...
 *
 * ...
 */

#include "../StdInclude.h"
#include "../project/Project.h"
#include "DisplaySettings.h"
#include "Unit.h"

#include "gui.h"

#include <wx/cmdproc.h>

class DialogObjectTransformation:public GUIObjectTransformation {
	// Constructor/ Destructor
public:
	DialogObjectTransformation(wxWindow* parent, Project * project,
			wxCommandProcessor * commandProcessor, DisplaySettings * settings);
	virtual ~DialogObjectTransformation();

	// Member Variables

	Project* project;
	DisplaySettings * settings;
	wxCommandProcessor * commandProcessor;

private:
	unsigned int c;

	bool scaleProportional;

	double scalePercent;
	double scalePercentX;
	double scalePercentY;
	double scalePercentZ;
	double scaleUnitX;
	double scaleUnitY;
	double scaleUnitZ;

	double moveStep;
	double rotateStep;

	// Methods
public:

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:

	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnChangeObjectColor(wxColourPickerEvent& event);
	void OnSelectObject(wxCommandEvent& event);
	void OnTransform(wxCommandEvent& event);
	void OnSetFactors(wxCommandEvent& event);
	void OnFlipNormals(wxCommandEvent& event);
};

#endif /* DIALOGOBJECTTRANSFORMATION_H_ */
