///////////////////////////////////////////////////////////////////////////////
// Name               : MainFrame.h
// Purpose            : Main window
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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
///////////////////////////////////////////////////////////////////////////////

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

/*!\class MainFrame
 * \brief Main window
 * This classs takes care of the main window. It contains a lot of file juggling for all the dialogs.
 * The manipulation of the project itself is done via wxCommand classes. These are passed to the
 * commandProcessor which executes them. The commandProcessor enables Undo/Redo behaviour.
 */

#include "../Config.h"
#include "../StdInclude.h"

#include "gui.h"

#include "DialogToolbox.h"
#include "DialogObjectTransformation.h"
#include "DialogStockMaterial.h"
#include "DialogAnimation.h"

#include "TreeSetup.h"

#include "Unit.h"
#include "../controller/Control3D.h"
#include "../project/Project.h"

#include <wx/config.h>
#include <wx/log.h>
#include <wx/cmdproc.h>


class MainFrame:public GUIMainFrame {
	// Constructor/ Destructor
public:
	MainFrame(wxWindow* parent, wxLocale* locale, wxConfig* config);
	virtual ~MainFrame();

	// Member variables
private:

	wxConfig *config;
	wxLocale *locale;
	Control3D control;
	wxLogWindow* logWindow;

	wxCommandProcessor commandProcessor;

	Project project; ///> Link to the project

	wxString lastProjectDirectory;
	wxString lastObjectDirectory;
	wxString lastMachineDirectory;
	wxString lastToolboxDirectory;
	wxString lastStockDirectory;

	size_t selectedTargetPosition;

	Unit Tolerance;
	Unit Distance;
	Unit LinearSpeed;
	Unit RotationalSpeed;

	TreeSetup tree;

	// Pointers to all the windows.
	DialogObjectTransformation objectFrame;
	DialogStockMaterial stockFrame;
	DialogToolbox toolboxFrame;
	DialogAnimation animationFrame;

	wxTimer timer; ///> Animation timer
	float t; // TODO: Make a seperate animation class

	// Methods
public:
	void LoadProject(wxString fileName); ///> Load a project from the command line

private:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void OnTimer(wxTimerEvent& event);
	void OnKeyDown(wxKeyEvent& event);

	void OnCreateProject(wxCommandEvent& event);
	void OnLoadProject(wxCommandEvent& event);
	void OnSaveProject(wxCommandEvent& event);
	void OnSaveProjectAs(wxCommandEvent& event);

	void OnQuit(wxCommandEvent& event);

	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);

	void OnLoadObject(wxCommandEvent& event);
	void OnModifyObject(wxCommandEvent& event);

	void OnLoadMachine(wxCommandEvent& event);
	void OnReloadMachine(wxCommandEvent& event);

	void OnEditToolbox(wxCommandEvent& event);
	void OnLoadToolbox(wxCommandEvent& event);
	void OnSaveToolbox(wxCommandEvent& event);

	void OnEditStock(wxCommandEvent& event);

	void OnGenerateToolpath(wxCommandEvent& event);
	void OnRecollectToolpath(wxCommandEvent& event);
	void OnCleanToolpath(wxCommandEvent& event);
	void OnFlipRun(wxCommandEvent& event);
	void OnPrepareMachinebed(wxCommandEvent& event);

	void OnLoadGCodes(wxCommandEvent& event);
	void OnSaveGCodes(wxCommandEvent& event);

	void OnChangeLanguage(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent& event);
	void OnChangeStereo3D(wxCommandEvent& event);
	void OnSetupUnits(wxCommandEvent& event);

	void OnShowAnimationControl(wxCommandEvent& event);

	void OnAbout(wxCommandEvent& event);

	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnActivateRightClickMenu(wxTreeEvent& event);
	void OnSelectionChanged(wxTreeEvent& event);

	void OnUpdateVisibility(wxCommandEvent& event);

};

#endif /* MAINFRAME_H_ */
