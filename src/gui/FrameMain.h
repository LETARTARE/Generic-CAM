///////////////////////////////////////////////////////////////////////////////
// Name               : FrameMain.h
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

/*!\class FrameMain
 * \brief Main window
 *
 * This classs takes care of the main window. It contains a lot of file juggling for all the dialogs.
 * The manipulation of the project itself is done via wxCommand classes. These are passed to the
 * commandProcessor which executes them. The commandProcessor enables Undo/Redo behaviour.
 */

#include "gui.h"

#include "TreeSetup.h"
#include "CollectionFilepaths.h"

#include "../project/Project.h"

#include <wx/help.h>
#include <wx/docview.h>
#include <wx/config.h>
#include <wx/cmdproc.h>

//#include "DialogMachineDebugger.h"
//#include "DialogToolbox.h"
//#include "DialogAnimation.h"
class FrameParent;
class DialogJobSetup;
class DialogToolpathGenerator;
class DialogObjectTransformation;
class DialogAnimation;
class DialogToolbox;
class DialogPostProcess;

class FrameMain:public GUIFrameMain {
	friend class DnDFile;
	friend class ProjectView;
	// Constructor/ Destructor
public:
	FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
			wxDocParentFrame* parent);
	virtual ~FrameMain();

	// Member variables
public:
	CollectionFilepaths filepaths;

protected:
	TreeSetup* tree;

private:
	wxConfig* config;

	wxMenu menuRecentFiles;
//	wxGauge * m_statusprogress;

// Pointers to all the windows.
	DialogObjectTransformation * dialogObjectTransformation;
	DialogJobSetup * dialogJobSetup;

//	DialogMachineDebugger * dialogDebugger;
//	DialogToolbox * dialogToolbox;
	DialogToolpathGenerator * dialogToolpathGenerator;
	DialogAnimation * dialogAnimation;
	DialogToolbox * dialogToolbox;
	DialogPostProcess * dialogPostProcess;

private:
	wxMutex loopguard;

	std::set <Selection> selectRequests;
	wxFrame * selectRequestRequester;
	size_t selectRequestID;
	bool selectRequestMulti;
	Selection oldSelection;

// Methods
public:
	void RequestSelection(wxFrame* requester, size_t ID, bool multiselect,
			Selection selection0, Selection selection1, Selection selection2);
	void RequestSelection(wxFrame* requester, size_t ID, bool multiselect,
			Selection selection0, Selection selection1);
	void RequestSelection(wxFrame* requester, size_t ID, bool multiselect,
			Selection selection0);
	void AnswerSelection(const Selection &selection);

	void ProjectLoad(wxString fileName); ///> Load a project from the command line
	bool TransferDataToWindow(bool updatetree = true);
	bool TransferDataFromWindow(void);

	FrameParent* GetParentFrame(void);

private:
	void UpdateSimulation(wxCommandEvent& event);

	size_t GetFreeSystemMemory();
	void OnClose(wxCloseEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnChar(wxKeyEvent& event);

	void OnPathSetup(wxCommandEvent& event);

	// --- Autogenerated ---

	void OnProjectNew(wxRibbonButtonBarEvent& event);
	void OnProjectOpen(wxRibbonButtonBarEvent& event);
	void OnProjectOpenMenu(wxRibbonButtonBarEvent& event);
	void OnProjectSave(wxRibbonButtonBarEvent& event);
	void OnProjectSaveMenu(wxRibbonButtonBarEvent& event);
	void OnViewPreferencesMenu(wxRibbonButtonBarEvent& event);
	void OnViewStereo3DToggle(wxCommandEvent& event);
	void OnUndo(wxRibbonButtonBarEvent& event);
	void OnRedo(wxRibbonButtonBarEvent& event);
	void OnHelp(wxRibbonBarEvent& event);

	void OnObjectLoad(wxRibbonButtonBarEvent& event);
	void OnObjectLoad(wxCommandEvent& event);
	void OnObjectModify(wxRibbonButtonBarEvent& event);
	void OnObjectModify(wxCommandEvent& event);
	void OnObjectFlipNormals(wxRibbonButtonBarEvent& event);
	void OnObjectFlipNormals(wxCommandEvent& event);

	void OnCAMSetup(wxRibbonButtonBarEvent& event);
	void OnCAMSetup(wxCommandEvent& event);

	void OnCAM2DMenu(wxRibbonButtonBarEvent& event);
	void OnCAM3DMenu(wxRibbonButtonBarEvent& event);
	void OnCAMDrilling(wxRibbonButtonBarEvent& event);
	void OnCAMMultiAxisMenu(wxRibbonButtonBarEvent& event);
	void OnCAMPostProcessSimulate(wxRibbonButtonBarEvent& event);
	void OnCAMPostProcessExport(wxRibbonButtonBarEvent& event);
	void OnCAMToolsMeasure(wxRibbonButtonBarEvent& event);
	void OnCAMToolsTestGCode(wxRibbonButtonBarEvent& event);
	void OnCAMManageTools(wxRibbonButtonBarEvent& event);
	void OnCAMManagePostProcesses(wxRibbonButtonBarEvent& event);
	void OnCAMManageMachines(wxRibbonButtonBarEvent& event);
	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnActivate(wxTreeEvent& event);
	void OnActivateRightClickMenu(wxTreeEvent& event);
	void OnSelectionChanged(wxTreeEvent& event);
	void OnSelectionChanging(wxTreeEvent& event);
	void On3DSelect(wxMouseEvent& event);
	void On3DMotion(wxMouseEvent& event);

	// --- End of autogenerated items ---

	void OnProjectRename(wxCommandEvent& event);
//	void OnObjectFlipNormals(wxCommandEvent& event);
//	void OnObjectLoad(wxCommandEvent& event);
	void OnObjectRename(wxCommandEvent& event);
	void OnObjectDelete(wxCommandEvent& event);
//	void OnStockEdit(wxCommandEvent& event);
//	void OnWorkpieceAdd(wxCommandEvent& event);
//	void OnWorkpieceSetup(wxCommandEvent& event);
//	void OnWorkpieceDelete(wxCommandEvent& event);
//	void OnWorkpieceDeleteUnused(wxCommandEvent& event);
//	void OnMachineLoad(wxCommandEvent& event);
//	void OnMachineReload(wxCommandEvent& event);
//	void OnMachineDebugger(wxCommandEvent& event);
//	void OnFlipDrillSetup(wxCommandEvent& event);
//	void OnToolboxEdit(wxCommandEvent& event);
//	void OnToolboxLoad(wxCommandEvent& event);
//	void OnToolboxSave(wxCommandEvent& event);
//	void OnRunEdit(wxCommandEvent& event);
	void OnRunRename(wxCommandEvent& event);
	void OnRunDelete(wxCommandEvent& event);
	void OnGeneratorAdd(wxCommandEvent& event);
	void OnGeneratorEdit(wxCommandEvent& event);
	void OnGeneratorRename(wxCommandEvent& event);
	void OnGeneratorDelete(wxCommandEvent& event);
	void OnToolpathGenerate(wxCommandEvent& event);
	void OnCAMPostProcessExport(wxCommandEvent& event);
//	void OnGeneratorSaveToolpath(wxCommandEvent& event);
//	void OnShowAnimationControl(wxCommandEvent& event);
//	void OnActivateStereo3D(wxCommandEvent& event);
//	void OnExtraWindowClose(wxCommandEvent& event);
//	void OnShowLogWindow(wxCommandEvent& event);
//	void OnViewSet(wxCommandEvent& event);
//	void OnTestGCode(wxCommandEvent& event);
//	void OnBeginLabelEdit(wxTreeEvent& event);
//	void OnEndLabelEdit(wxTreeEvent& event);
//	void OnActivate(wxTreeEvent& event);
//	void OnActivateRightClickMenu(wxTreeEvent& event);
//	void OnSelectionChanged(wxTreeEvent& event);
//	void OnSelectionChanging(wxTreeEvent& event);
//	void On3DDClick(wxMouseEvent& event);
//	void On3DSelect(wxMouseEvent& event);
//	void OnToolbarButton(wxCommandEvent& event);

wxDECLARE_EVENT_TABLE();
};

#endif /* MAINFRAME_H_ */
