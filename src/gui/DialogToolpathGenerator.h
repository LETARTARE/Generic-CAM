///////////////////////////////////////////////////////////////////////////////
// Name               : DialogToolpathGenerator.h
// Purpose            : Dialog to add, update and delete toolpath generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.02.2015
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

#ifndef DIALOGTOOLPATHGENERATOR_H_
#define DIALOGTOOLPATHGENERATOR_H_

/*!\class DialogToolpathGenerator
 * \brief Dialog to add, update and delete toolpath generators.
 *
 * A lot of dynamic casting is done in this dialog class. The parameters hidden
 * in the derived classes, the parent class does not know about.
 */

#include "../StdInclude.h"
#include "../project/Project.h"
#include "gui.h"
#include <wx/thread.h>

class DialogToolpathGenerator:public GUIToolpathGenerator {
public:
	DialogToolpathGenerator(wxWindow* parent);
	virtual ~DialogToolpathGenerator();

	void SetRunGenerator(size_t runID, size_t generatorID);
	size_t GetRunID(void) const;
	bool TransferDataToWindow(bool updateGeneratorPanel = false);
	bool TransferDataFromWindow(Generator * generator) const;

	bool UpdateGenerator(void);

	void OnXClose(wxCloseEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnSelectArea(wxCommandEvent& event);
	void OnSelectTool(wxCommandEvent& event);
	void OnTextEnter(wxCommandEvent& event);
	bool OnSelected(size_t ID, Selection selection);
	void OnUpdate(wxCommandEvent& event);
private:
	size_t runID;
	size_t generatorID;
	Generator * localGenerator;

	Selection bufferarea;

	wxMutex loopguard;
};

#endif /* DIALOGTOOLPATHGENERATOR_H_ */
