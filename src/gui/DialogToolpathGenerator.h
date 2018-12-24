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
#include "../project/generator/GeneratorCollection.h"
#include "DisplaySettings.h"
#include "gui.h"
#include <wx/cmdproc.h>

class DialogToolpathGenerator:public GUIToolpathGenerator {
public:
	DialogToolpathGenerator(wxWindow* parent);
	virtual ~DialogToolpathGenerator();

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void UndoChanges(void);

	void OnXClose(wxCloseEvent& event);
	void OnSelectRun(wxCommandEvent& event);
	void OnSelectToolpath(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	void OnChangeText(wxCommandEvent& event);
	void OnSelectArea(wxCommandEvent& event);
	void OnSelectTool(wxCommandEvent& event);
	void OnPageChanged(wxChoicebookEvent& event);
	void OnUpdate(wxCommandEvent& event);
	void OnResetChanges(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);

private:
	Project* GetProject(void);
	GeneratorCollection gc;
	int GetGeneratorNr(int runNr, int toolpathNr);

	int currentRun;
	int currentToolpath;
	BoundingBox box;
	float marginSides;
	float marginBelow;
	size_t slotNr;
	float freeHeight;

	bool loopGuard;
};

#endif /* DIALOGTOOLPATHGENERATOR_H_ */
