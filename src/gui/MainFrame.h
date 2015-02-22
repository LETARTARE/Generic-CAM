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

#include "DisplaySettings.h"
#include "DialogObjectTransformation.h"
#include "DialogStockMaterial.h"
#include "DialogWorkpiece.h"
#include "DialogPlacement.h"
#include "DialogRun.h"
#include "DialogMachineDebugger.h"
#include "DialogToolbox.h"
#include "DialogAnimation.h"
#include "DialogSetupStereo3D.h"

#include "../controller/Control3D.h"
#include "../project/Project.h"

#include "TreeSetup.h"

#include <wx/config.h>
#include <wx/log.h>
#include <wx/cmdproc.h>

#include "DialogToolpathGenerator.h"

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
	TreeSetup * tree;
	wxCommandProcessor commandProcessor;

	Project project; ///> The project is instantiated here

	DisplaySettings settings;

	size_t selectedTargetPosition;

	// Pointers to all the windows.
	DialogObjectTransformation * dialogObjectTransformation;
	DialogStockMaterial * dialogStockMaterial;
	DialogWorkpiece * dialogWorkpiece;
	DialogPlacement * dialogPlacement;
	DialogRun * dialogRun;
	DialogMachineDebugger * dialogDebugger;
	DialogToolbox * dialogToolbox;
	DialogToolpathGenerator * dialogToolpathGenerator;
	DialogAnimation * dialogAnimation;
	DialogSetupStereo3D * dialogSetupStereo3D;

	wxTimer timer; ///> Animation timer
	float t; // TODO: Make a seperate animation class
	// Methods
public:
	void ProjectLoad(wxString fileName); ///> Load a project from the command line

private:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void UpdateTree(wxCommandEvent& event);
	void Update(wxCommandEvent& event);
	void UpdateCanvas(wxCommandEvent& event);

	size_t GetFreeSystemMemory();
	void OnTimer(wxTimerEvent& event);
	void OnKeyDown(wxKeyEvent& event);

	// --- Autogenerated ---
	void OnProjectNew(wxCommandEvent& event);
	void OnProjectRename(wxCommandEvent& event);
	void OnProjectLoad(wxCommandEvent& event);
	void OnProjectSave(wxCommandEvent& event);
	void OnProjectSaveAs(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnObjectModify(wxCommandEvent& event);
	void OnObjectFlipNormals(wxCommandEvent& event);
	void OnObjectLoad(wxCommandEvent& event);
	void OnObjectRename(wxCommandEvent& event);
	void OnObjectDelete(wxCommandEvent& event);
	void OnStockEdit(wxCommandEvent& event);
	void OnWorkpieceAdd(wxCommandEvent& event);
	void OnWorkpieceSetup(wxCommandEvent& event);
	void OnWorkpieceDelete(wxCommandEvent& event);
	void OnWorkpieceDeleteUnused(wxCommandEvent& event);
	void OnRunEdit(wxCommandEvent& event);
	void OnRunAdd(wxCommandEvent& event);
	void OnRunDelete(wxCommandEvent& event);
	void OnMachineLoad(wxCommandEvent& event);
	void OnMachineReload(wxCommandEvent& event);
	void OnMachineDebugger(wxCommandEvent& event);
	void OnFlipDrillSetup(wxCommandEvent& event);
	void OnToolboxEdit(wxCommandEvent& event);
	void OnToolboxLoad(wxCommandEvent& event);
	void OnToolboxSave(wxCommandEvent& event);
	void OnGeneratorSetup(wxCommandEvent& event);
	void OnGeneratorAutomatic(wxCommandEvent& event);
	void OnGeneratorRestart(wxCommandEvent& event);
	void OnGeneratorSaveToolpath(wxCommandEvent& event);
	void OnShowAnimationControl(wxCommandEvent& event);
	void OnChangeLanguage(wxCommandEvent& event);
	void OnActivateStereo3D(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent& event);
	void OnSetupStereo3D(wxCommandEvent& event);
	void OnSetupUnits(wxCommandEvent& event);
	void OnExtraWindowClose(wxCommandEvent& event);
	void OnShowLogWindow(wxCommandEvent& event);
	void OnViewSet(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnActivate(wxTreeEvent& event);
	void OnActivateRightClickMenu(wxTreeEvent& event);
	void OnSelectionChanged(wxTreeEvent& event);
	void OnSelectionChanging(wxTreeEvent& event);
	void On3DSelect(wxMouseEvent& event);
	void OnToolbarButton(wxCommandEvent& event);
	// --- End of autogenerated items ---

};

#endif /* MAINFRAME_H_ */
