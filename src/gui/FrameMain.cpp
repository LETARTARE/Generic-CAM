///////////////////////////////////////////////////////////////////////////////
// Name               : FrameMain.cpp
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

#include "../StdInclude.h"
#include "../Config.h"

#include "FrameMain.h"

#include <wx/generic/textdlgg.h>

#include "FrameParent.h"

#include "DialogTestGCode.h"
#include "DialogToolpathGenerator.h"
#include "DialogJobSetup.h"
#include "DialogSetupPaths.h"
#include "DialogObjectTransformation.h"
#include "DialogPostProcess.h"
#include "DialogToolbox.h"
#include "DialogAnimation.h"

//#include "../project/generator/ToolpathGeneratorThread.h"
//#include "../project/command/CommandWorkpieceRename.h"
//#include "../project/command/CommandWorkpieceDelete.h"
#include "../project/command/CommandProjectRename.h"
#include "../project/command/CommandObjectLoad.h"
#include "../project/command/CommandObjectRemove.h"
#include "../project/command/CommandObjectRename.h"
#include "../project/command/CommandObjectTransform.h"
#include "../project/command/CommandRunAdd.h"
#include "../project/command/CommandRunRename.h"
#include "../project/command/CommandRunRemove.h"

#include "DnDFile.h"

#include "../math/MathParser.h"
#include "../project/command/CommandRunGeneratorAdd.h"
#include "../project/command/CommandRunGeneratorDelete.h"
#include "../project/command/CommandRunGeneratorRename.h"
#include "../project/generator/GeneratorFactory.h"
#include "../project/ProjectView.h"
#include "IDs.h"

#ifndef __WIN32__
#include "../icon/logo32.xpm"
#include "../icon/logo48.xpm"
#include "../icon/logo64.xpm"
#include "../icon/logo128.xpm"
#endif

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include <wx/busyinfo.h>
#include <wx/utils.h>
#include <wx/icon.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/splash.h>
#ifdef __LINUX
#include <unistd.h>
#endif

wxBEGIN_EVENT_TABLE(FrameMain, wxDocChildFrame) EVT_MENU(ID_TOGGLESTEREO3D, FrameMain::OnViewStereo3DToggle)
EVT_MENU(ID_SETUPPATHS, FrameMain::OnPathSetup)
EVT_MENU(ID_PROJECTRENAME, FrameMain::OnProjectRename)
EVT_MENU(ID_OBJECTLOAD, FrameMain::OnObjectLoad)
EVT_MENU(ID_OBJECTRENAME, FrameMain::OnObjectRename)
EVT_MENU(ID_OBJECTMODIFY, FrameMain::OnObjectModify)
EVT_MENU(ID_OBJECTDELETE, FrameMain::OnObjectDelete)
EVT_MENU(ID_OBJECTFLIPNORMALS, FrameMain::OnObjectFlipNormals)
EVT_MENU(ID_RUNRENAME, FrameMain::OnRunRename)
EVT_MENU(ID_RUNMODIFY, FrameMain::OnCAMSetup)
EVT_MENU(ID_RUNDELETE, FrameMain::OnRunDelete)
EVT_MENU_RANGE(ID_GENERATORADDTYPE,ID_GENERATORADDTYPE+100, FrameMain::OnGeneratorAdd)
EVT_MENU(ID_GENERATORMODIFY, FrameMain::OnGeneratorEdit)
EVT_MENU(ID_GENERATORRENAME, FrameMain::OnGeneratorRename)
EVT_MENU(ID_GENERATORDELETE, FrameMain::OnGeneratorDelete)
EVT_MENU(ID_TOOLPATHGENERATE, FrameMain::OnToolpathGenerate)
EVT_MENU(ID_TOOLPATHEXPORT, FrameMain::OnCAMPostProcessExport)

wxEND_EVENT_TABLE()

FrameMain::FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
		wxDocParentFrame* parent) :
		GUIFrameMain(doc, view, parent)
{
#ifndef __WIN32__
	//TODO: Check, why the icon is not working under Windows / Code::Blocks.
	wxIconBundle logo;
	logo.AddIcon(wxIcon(logo32_xpm));
	logo.AddIcon(wxIcon(logo48_xpm));
	logo.AddIcon(wxIcon(logo64_xpm));
	logo.AddIcon(wxIcon(logo128_xpm));
	SetIcons(logo);
#endif

	this->config = config;

	FrameParent* parentframe = wxStaticCast(parent, FrameParent);
	Project* project = wxStaticCast(GetDocument(), Project);
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);

	filepaths.Load(config);

	// Load the default tools into a new project.
	// (Has to be done from here, because the set paths are
	// only known at this point.)
	wxDir dir(filepaths.lastToolboxDirectory);
	if(dir.IsOpened()){
		wxString filename;
		bool cont = dir.GetFirst(&filename, _T("*.json"));
		while(cont){
			if(filename.CmpNoCase(_T("local.json")) == 0){
				wxString fullfilename = dir.GetNameWithSep() + filename;
				project->LoadDefaultTools(fullfilename);
				break;
			}
			cont = dir.GetNext(&filename);
		}
	}

	doc->GetDocumentManager()->FileHistoryAddFilesToMenu(&menuRecentFiles);
	doc->GetCommandProcessor()->Initialize();

	tree = new TreeSetup(this, m_tree);

	m_canvas->SetDropTarget(new DnDFile(project, this));
	m_tree->SetDropTarget(new DnDFile(project, this));

	m_canvas->SetController(parentframe->control);
	m_canvas->InsertProjectView(projectview); // Connect the project to the 3D canvas

	// Get the setting from the parentframe and add them to the main canvas of this window.
	parentframe->settingsStereo3D.WriteToCanvas(m_canvas);

//	m_statusprogress = new wxGauge(m_statusBar, wxID_ANY, 100, wxPoint(60, 3),
//			wxSize(60, m_statusBar->GetSize().GetHeight() - 6), wxGA_SMOOTH,
//			wxDefaultValidator);
//	m_statusprogress->SetValue(25);

	selectRequestRequester = NULL;
	selectRequestMulti = false;
	selectRequestID = 0;

	dialogObjectTransformation = new DialogObjectTransformation(this);
	dialogJobSetup = new DialogJobSetup(this);
	dialogToolpathGenerator = new DialogToolpathGenerator(this);
	dialogAnimation = new DialogAnimation(this);
	dialogPostProcess = new DialogPostProcess(this);
	dialogToolbox = new DialogToolbox(this);

//	dialogDebugger = new DialogMachineDebugger(this);
//#ifdef _USE_MIDI
//	dialogDebugger->SetMidiPort(parentframe->midi);
//#endif
//	dialogToolbox = new DialogToolbox(this);
//	dialogAnimation = new DialogAnimation(this);

	wxAcceleratorEntry entries[6];
	entries[0].Set(0, WXK_F1, wxID_HELP);
	entries[1].Set(wxACCEL_CTRL, (int) 'Z', wxID_UNDO);
	entries[2].Set(wxACCEL_CTRL, (int) 'Y', wxID_REDO);
	entries[3].Set(wxACCEL_CTRL, (int) 'Q', wxID_EXIT);
	entries[4].Set(wxACCEL_CTRL, (int) '3', ID_TOGGLESTEREO3D);
	entries[5].Set(wxACCEL_NORMAL, WXK_F2, wxID_ABOUT);
	wxAcceleratorTable accel(6, entries);
	this->SetAcceleratorTable(accel);

	TransferDataToWindow();
//	std::cout << "FrameMain::FrameMain - leaving function.\n";
}

FrameMain::~FrameMain()
{
	printf("FrameMain: Destructor called\n");
//	m_splitter->Destroy();
	filepaths.Save(config);
}

FrameParent* FrameMain::GetParentFrame(void)
{
	return wxStaticCast(GetParent(), FrameParent);
}

size_t FrameMain::GetFreeSystemMemory()
{
#ifdef __LINUX
	long pages = sysconf(_SC_AVPHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
#endif
#ifdef __WIN
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	//TODO: Change this to return available memory.
	return status.ullTotalPhys;
#endif
}

bool FrameMain::TransferDataToWindow(bool updatetree)
{
	if(updatetree){
		// Populate the treeview
		tree->Update();
	}
	Selection temp = tree->TreeToSelection();

//	m_menuToolpath->Check(ID_GENERATORAUTOMATIC, project.processToolpath);
//	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
//	m_toolBar->ToggleTool(ID_DISPLAYMACHINE, project.displayMachine);
//	m_toolBar->ToggleTool(ID_DISPLAYMATERIAL, project.displayGeometry);

//	wxString temp = _T("Generic CAM - ");
//	if(commandProcessor.IsDirty()) temp += _T("* ");
//	temp += project.name;
//	this->SetTitle(temp);

//	m_canvas->displayAnimation = dialogAnimation->IsShown();

	if(temp.IsType(Selection::Object)){
		dialogObjectTransformation->SetSelection(temp);
	}
	dialogObjectTransformation->TransferDataToWindow();

	if(temp.IsType(Selection::Run) && temp.Size() >= 1){
		dialogJobSetup->SetRunID(temp[0]);
		dialogPostProcess->SetRunGenerator(temp[0]);
	}
	dialogJobSetup->TransferDataToWindow();

	if(temp.IsBaseType(Selection::BaseRun) && temp.IsType(Selection::Generator)
			&& temp.Size() >= 1){
		dialogToolpathGenerator->SetRunGenerator(temp.GetBaseID(), temp[0]);
		dialogPostProcess->SetRunGenerator(temp.GetBaseID(), temp[0]);
	}
	dialogToolpathGenerator->TransferDataToWindow();

//	dialogToolbox->TransferDataToWindow();
//	dialogDebugger->TransferDataToWindow();

//	dialogAnimation->TransferDataToWindow();

//	Refresh();
	return true;
}

bool FrameMain::TransferDataFromWindow(void)
{
//	m_canvas->stereoMode =
//			m_menuView->IsChecked(ID_VIEWSTEREO3D)? stereoAnaglyph : stereoOff;
//	project.displayMachine = m_toolBar->GetToolState(ID_DISPLAYMACHINE);
//	project.displayGeometry = m_toolBar->GetToolState(ID_DISPLAYMATERIAL);

	return true;
}

void FrameMain::OnProjectNew(wxRibbonButtonBarEvent& event)
{
	printf("New\n");
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_NEW);
	ProcessEvent(menuEvent);
}

void FrameMain::OnProjectOpen(wxRibbonButtonBarEvent& event)
{
	printf("Open\n");
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_OPEN);
	ProcessEvent(menuEvent);
}

void FrameMain::OnProjectOpenMenu(wxRibbonButtonBarEvent& event)
{
	event.PopupMenu(&menuRecentFiles);
}

void FrameMain::ProjectLoad(wxString fileName)
{

}

void FrameMain::OnProjectSave(wxRibbonButtonBarEvent& event)
{
	printf("Save\n");
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_SAVE);
	ProcessEvent(menuEvent);
}

void FrameMain::OnProjectSaveMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(wxID_SAVE, wxT("Save"));
	menu.Append(wxID_SAVEAS, wxT("Save as ..."));
	menu.Append(wxID_REVERT, wxT("Revert"));
	menu.Append(wxID_REVERT_TO_SAVED, wxT("Revert to saved"));
	event.PopupMenu(&menu);
}

void FrameMain::OnProjectRename(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxTextEntryDialog dialog(this, _("Enter new project name:"),
			_T("Rename Project"), project->GetTitle());
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project->GetTitle()) return;

		CommandProjectRename * command = new CommandProjectRename(
		_("Project renamed to ") + dialog.GetValue(), project,
				dialog.GetValue());
		project->GetCommandProcessor()->Submit(command);
		TransferDataToWindow();
	}
}

void FrameMain::OnViewPreferencesMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(ID_SETUPUNITS, _("Setup &Units") + wxT("\tCtrl+U"));
	menu.Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
	menu.Append(ID_SETUPLANGUAGE, _T("Change Language"));
	menu.Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
	menu.Append(ID_SETUPPATHS, _("Setup &Paths"));
#ifdef _USE_MIDI
	menu.Append(ID_SETUPMIDI, _("Setup &MIDI"));
#endif
	event.PopupMenu(&menu);
}

void FrameMain::OnPathSetup(wxCommandEvent& event)
{
	DialogSetupPaths dialog(this, &filepaths);
	dialog.ShowModal();
	dialog.UpdateCollection(&filepaths);
}

void FrameMain::OnViewStereo3DToggle(wxCommandEvent& event)
{
//	printf("Toggle Stereo3D\n");
	if(m_canvas->stereoMode == stereoOff){
		m_canvas->stereoMode = stereoAnaglyph;
	}else{
		m_canvas->stereoMode = stereoOff;
	}
	m_ribbonButtonBarView->ToggleButton(ID_TOGGLESTEREO3D,
			m_canvas->stereoMode != stereoOff);
	Refresh();
}

void FrameMain::OnUndo(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_UNDO);
	ProcessEvent(menuEvent);
}

void FrameMain::OnRedo(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_REDO);
	ProcessEvent(menuEvent);
}

void FrameMain::OnObjectLoad(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent temp(event);
	OnObjectLoad(temp);
}

void FrameMain::OnObjectLoad(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();

	wxFileName fileName;
	wxFileDialog dialog(this, _("Load Object..."), _T(""), _T(""),
			_(
					"All supported files (*.obj; *.dxf; *.stl; *.gts)|*.obj;*.dxf;*DXF;*.stl;*.STL;*.gts;*.GTS|Wavefront OBJ Files (*.obj)|*.obj;*.OBJ|DXF Files (*.dxf)|*.dxf;*.DXF|Stereolithography files (STL files) (*.stl)|*.stl;*.STL|GTS files (*.gts)|*.gts;*.GTS|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

	if(wxDir::Exists(filepaths.lastObjectDirectory)){
		dialog.SetDirectory(filepaths.lastObjectDirectory);
	}else{
		if(wxDir::Exists(filepaths.lastProjectDirectory)){
			dialog.SetDirectory(filepaths.lastProjectDirectory);
		}
	}

	if(dialog.ShowModal() == wxID_OK){
		wxArrayString paths;
		dialog.GetPaths(paths);
		for(size_t n = 0; n < paths.GetCount(); ++n){
			fileName = paths[n];
			cmdProc->Submit(
					new CommandObjectLoad(
							(_("Load Object: ") + fileName.GetName()),
							project, paths[n]));
			if(n == paths.GetCount() - 1) filepaths.lastObjectDirectory =
					fileName.GetPath();
		}
		TransferDataToWindow();
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
		ProcessEvent(menuEvent);
	}
}

void FrameMain::OnObjectRename(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
//	TransferDataFromWindow();

	Selection temp = tree->TreeToSelection();
	if(!temp.IsType(Selection::Object) || !project->Has(temp)
			|| temp.Size() != 1) return;

	const size_t ID = temp[0];

	wxTextEntryDialog dialog(this, _("Enter new name:"),
	_T("Rename Object ") + project->Get3DObject(ID).name,
			project->Get3DObject(ID).name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project->Get3DObject(ID).name) return;
		cmdProc->Submit(
				new CommandObjectRename(
				_("Object renamed to ") + dialog.GetValue(), project, ID,
						dialog.GetValue()));
		TransferDataToWindow();
	}
}

void FrameMain::OnObjectModify(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent temp(event);
	OnObjectModify(temp);
}

void FrameMain::OnObjectModify(wxCommandEvent& event)
{
	dialogObjectTransformation->Show();
	dialogObjectTransformation->TransferDataToWindow();
	dialogObjectTransformation->Raise();
}

void FrameMain::OnObjectDelete(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();

	Selection temp = tree->TreeToSelection();
	if(!temp.IsType(Selection::Object) || !project->Has(temp)
			|| temp.Size() != 1) return;

	for(std::set <size_t>::iterator it = temp.begin(); it != temp.end(); ++it){
		cmdProc->Submit(
				new CommandObjectRemove(
						_(
								"Object ") + project->Get3DObject(*it).name + _(" deleted."),
						project, *it));
	}
	TransferDataToWindow();
}

void FrameMain::OnObjectFlipNormals(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent temp(event);
	OnObjectFlipNormals(temp);
}
void FrameMain::OnObjectFlipNormals(wxCommandEvent& event)
{
	Selection temp = tree->TreeToSelection();
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor* cmdProc = project->GetCommandProcessor();

	if(!temp.IsType(Selection::Object) || !project->Has(temp)) return;

	for(std::set <size_t>::const_iterator it = temp.begin(); it != temp.end();
			++it){
		AffineTransformMatrix matrix = project->Get3DObject(*it).matrix;
		CommandObjectTransform * command = new CommandObjectTransform(
				project->Get3DObject(*it).name + _(": Flipped normal vectors"),
				project, *it, false, false, false, true, matrix);
		cmdProc->Submit(command);
	}
	Refresh();
}

void FrameMain::OnCAMSetup(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent temp(event);
	OnCAMSetup(temp);
}
void FrameMain::OnCAMSetup(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor* cmdProc = project->GetCommandProcessor();
	Selection temp = tree->TreeToSelection();

	if(!temp.IsType(Selection::Run)){
		wxString newName = wxString::Format(_T("Run %zu"),
				project->GetMaxRunID() + 1);
		size_t objID;
		if(temp.IsType(Selection::Object)){
			objID = temp[0];
			newName += _(" - Object: ") + project->Get3DObject(objID).name;
		}else{
			objID = 0;
		}
		if(cmdProc->Submit(
				new CommandRunAdd(_("Adding run ") + newName, project, newName,
						objID))){
//			dialogJobSetup->SetRunID(project->maxRunID);
			tree->SelectonToTree(
					Selection(Selection::Run, project->GetMaxRunID()));
		}
	}

	dialogJobSetup->Show();
	dialogJobSetup->TransferDataToWindow();
}

void FrameMain::OnRunRename(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	Selection temp = tree->TreeToSelection();

	if(!temp.IsType(Selection::Run) || !project->Has(temp) || temp.Size() != 1) return;
	const size_t ID = temp[0];

	wxTextEntryDialog dialog(this, _("Enter new name:"),
	_T("Rename Run ") + project->GetRun(ID).name,
			project->GetRun(ID).name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project->GetRun(ID).name) return;
		cmdProc->Submit(
				new CommandRunRename(
				_("Run renamed to ") + dialog.GetValue(), project, ID,
						dialog.GetValue()));
		TransferDataToWindow();
	}
}

void FrameMain::OnRunDelete(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();

	Selection temp = tree->TreeToSelection();
	if(!temp.IsType(Selection::Run) || !project->Has(temp) || temp.Size() != 1) return;
	const size_t ID = temp[0];
	cmdProc->Submit(
			new CommandRunRemove(_("Remove run ") + project->GetRun(ID).name,
					project, ID));
	TransferDataToWindow();
}
void FrameMain::OnCAM2DMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(ID_GENERATORADDTYPE + 5, wxT("Outline Dexel"));
	menu.Append(ID_GENERATORADDTYPE + 7, wxT("Load from file"));
	event.PopupMenu(&menu);
}

void FrameMain::OnCAM3DMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(ID_GENERATORADDTYPE + 4, wxT("GeneratorTest"));
	menu.Append(ID_GENERATORADDTYPE + 3, wxT("AreaMillingDynamic"));
	menu.Append(ID_GENERATORADDTYPE + 6, wxT("Surface Dexel"));
	menu.Append(ID_GENERATORADDTYPE + 2, wxT("Drill Dexel"));
	event.PopupMenu(&menu);
}

void FrameMain::OnCAMDrilling(wxRibbonButtonBarEvent& event)
{
	OnGeneratorAdd(event);
}

void FrameMain::OnCAMMultiAxisMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(ID_GENERATORADDTYPE + 1, wxT("Area Grid Dexel"));
	event.PopupMenu(&menu);
}

void FrameMain::OnGeneratorAdd(wxCommandEvent& event)
{
	Selection sel = tree->TreeToSelection();
	if(sel.IsSetEmpty()) return;
	if(!sel.IsType(Selection::Run) && !sel.IsBaseType(Selection::BaseRun)) return;
	size_t runID = sel[0];
	if(sel.IsBaseType(Selection::BaseRun)) runID = sel.GetBaseID();

	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();

	Generator* generator = NULL;
	switch(event.GetId()){

	case ID_GENERATORADDTYPE + 1:
		generator = GeneratorFactory::NewGenerator(TYPE_GENERATORAREAGRID);
		break;
	case ID_GENERATORADDTYPE + 2:
		generator = GeneratorFactory::NewGenerator(TYPE_GENERATORDRILLDEXEL);
		break;
	case ID_GENERATORADDTYPE + 3:
		generator = GeneratorFactory::NewGenerator(
		TYPE_GENERATORAREAMILLINGDYNAMIC);
		break;
	case ID_GENERATORADDTYPE + 4:
		generator = GeneratorFactory::NewGenerator(
		TYPE_GENERATORTEST);
		break;
	case ID_GENERATORADDTYPE + 5:
		generator = GeneratorFactory::NewGenerator(TYPE_GENERATOROUTLINE);
		break;
	case ID_GENERATORADDTYPE + 6:
		generator = GeneratorFactory::NewGenerator(TYPE_GENERATORSURFACE);
		break;
	case ID_GENERATORADDTYPE + 7:
		generator = GeneratorFactory::NewGenerator(TYPE_GENERATORLOADFROMFILE);
		break;
	default:
		return;
	}
	generator->name = generator->GetTypeName();
	if(!cmdProc->Submit(
			new CommandRunGeneratorAdd(_("Add generator to run."), project,
					runID, generator))){
		// Generator was not added and need to be deleted again.
		delete generator;
		std::cout << "FrameMain::OnGeneratorAdd() - Adding failed.\n";
		return;
	}

	std::cout << "  \\-> Added generator #" << project->GetMaxGeneratorID()
			<< "\n";

	dialogToolpathGenerator->SetRunGenerator(runID,
			project->GetMaxGeneratorID());
	dialogToolpathGenerator->Show();
	dialogToolpathGenerator->Raise();
}

void FrameMain::OnGeneratorEdit(wxCommandEvent& event)
{
	dialogToolpathGenerator->Show();
	dialogToolpathGenerator->Raise();
}

void FrameMain::OnGeneratorRename(wxCommandEvent& event)
{
}
void FrameMain::OnGeneratorDelete(wxCommandEvent& event)
{
	Selection sel = tree->TreeToSelection();
	if(sel.IsSetEmpty()) return;
	if(!sel.IsType(Selection::Generator) || !sel.IsBaseType(Selection::BaseRun)) return;
	size_t runID = sel.GetBaseID();
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	cmdProc->Submit(
			new CommandRunGeneratorDelete(_("Deleting generator from run."),
					project, runID, sel[0]));
}

void FrameMain::OnCAMPostProcessSimulate(wxRibbonButtonBarEvent& event)
{
	dialogAnimation->Show();
	dialogAnimation->Raise();
}

void FrameMain::OnCAMPostProcessExport(wxRibbonButtonBarEvent& event)
{
	dialogPostProcess->Show();
	dialogPostProcess->Raise();
}

void FrameMain::OnCAMPostProcessExport(wxCommandEvent& event)
{
	dialogPostProcess->Show();
	dialogPostProcess->Raise();
}

void FrameMain::OnCAMToolsMeasure(wxRibbonButtonBarEvent& event)
{
}

void FrameMain::OnCAMManageTools(wxRibbonButtonBarEvent& event)
{
	dialogToolbox->Update();
	dialogToolbox->Show();
	dialogToolbox->Raise();
}

void FrameMain::OnCAMManagePostProcesses(wxRibbonButtonBarEvent& event)
{
}

void FrameMain::OnCAMManageMachines(wxRibbonButtonBarEvent& event)
{
}

void FrameMain::OnCAMToolsTestGCode(wxRibbonButtonBarEvent& event)
{
//	//TODO: When the units change the change is not immediately propagated into the TestGCode dialog.
	DialogTestGCode * dialog = new DialogTestGCode(this);
	dialog->Show();
	dialog->Raise();
}

void FrameMain::OnHelp(wxRibbonBarEvent& event)
{
//	printf("Help\n");
	wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_HELP);
	ProcessEvent(menuEvent);

}

void FrameMain::OnClose(wxCloseEvent& event)
{
	wxDocument* doc = this->GetDocument();
	wxList tempDocs = doc->GetDocumentManager()->GetDocuments();
	wxList tempViews = doc->GetViews();
//	Project* project = wxStaticCast(doc, Project);
//	project->StopAllThreads();

	printf("FrameMain: %lu docs, %lu views\n", tempDocs.GetCount(),
			tempViews.GetCount());

	if(tempDocs.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	if(tempViews.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	wxWindow* main = this->GetParent();
	printf("FrameMain: parent->Close()\n");
	main->Close(); // Exit app by closing main window, this will close this window as well.
}

void FrameMain::OnSize(wxSizeEvent& event)
{
//	printf("Size\n");
	event.Skip();
}

void FrameMain::RequestSelection(wxFrame* requester, size_t ID,
		bool multiselect, Selection selection0)
{
	std::cout << "--------------------------------\n";
	std::cout << "FrameMain::RequestSelection(.., " << ID << ", " << multiselect
			<< ", " << selection0.ToString() << ");\n";
	oldSelection = tree->TreeToSelection();
//	tree->SelectonToTree(Selection());
	this->selectRequestRequester = requester;
	this->selectRequestID = ID;
	this->selectRequestMulti = multiselect;
	this->selectRequests.clear();
	this->selectRequests.insert(selection0);
}

void FrameMain::RequestSelection(wxFrame* requester, size_t ID,
		bool multiselect, Selection selection0, Selection selection1)
{
	std::cout << "--------------------------------\n";
	std::cout << "FrameMain::RequestSelection(.., " << ID << ", " << multiselect
			<< ", " << selection0.ToString() << ", " << selection1.ToString()
			<< ");\n";
	oldSelection = tree->TreeToSelection();
//	tree->SelectonToTree(Selection());
	this->selectRequestRequester = requester;
	this->selectRequestID = ID;
	this->selectRequestMulti = multiselect;
	this->selectRequests.clear();
	this->selectRequests.insert(selection0);
	this->selectRequests.insert(selection1);
}

void FrameMain::RequestSelection(wxFrame* requester, size_t ID,
		bool multiselect, Selection selection0, Selection selection1,
		Selection selection2)
{
	std::cout << "--------------------------------\n";
	std::cout << "FrameMain::RequestSelection(.., " << ID << ", " << multiselect
			<< ", " << selection0.ToString() << ", " << selection1.ToString()
			<< ", " << selection2.ToString() << ");\n";
	oldSelection = tree->TreeToSelection();
//	tree->SelectonToTree(Selection());
	this->selectRequestRequester = requester;
	this->selectRequestID = ID;
	this->selectRequestMulti = multiselect;
	this->selectRequests.clear();
	this->selectRequests.insert(selection0);
	this->selectRequests.insert(selection1);
	this->selectRequests.insert(selection2);
}

void FrameMain::AnswerSelection(const Selection &selection)
{
	if(selectRequests.empty()){
		std::cout << "FrameMain::AnswerSelection(" << selection.ToString()
				<< ") without open requests;\n";
		return;
	}
	if(selectRequestRequester == NULL) return;

	std::cout << "FrameMain::AnswerSelection(" << selection.ToString()
			<< ");\n";

	if(selectRequestRequester == dialogJobSetup){
		if(oldSelection.IsType(Selection::Run) && oldSelection.Size() > 0){
			dialogJobSetup->SetRunID(oldSelection[0]);
		}
		dialogJobSetup->OnSelected(selectRequestID, selection);
	}
	if(selectRequestRequester == dialogToolpathGenerator){
		dialogToolpathGenerator->OnSelected(selectRequestID, selection);
	}
	std::cout << "in FrameMain::AnswerSelection -> Reset selection to "
			<< oldSelection.ToString() << "\n";
	tree->SelectonToTree(oldSelection);
	selectRequestRequester = NULL;
	selectRequests.clear();
	Refresh();
}

void FrameMain::OnChar(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_RETURN && !this->selectRequests.empty()){
		ProjectView * view = wxStaticCast(GetView(), ProjectView);
		AnswerSelection(view->selection);
		return;
	}
	if(event.GetKeyCode() == WXK_ESCAPE && !this->selectRequests.empty()){
		if(selectRequestRequester == dialogJobSetup){
			dialogJobSetup->OnSelected(selectRequestID, Selection());
		}
		selectRequestRequester = NULL;
		selectRequests.clear();
		tree->SelectonToTree(oldSelection);
		Refresh();
		return;
	}
	event.Skip();
}

void FrameMain::On3DMotion(wxMouseEvent& event)
{
	ProjectView* view = wxStaticCast(GetView(), ProjectView);
	if(selectRequests.empty()){
//		event.Skip();
//		return;
	}
	int x = event.GetX();
	int y = event.GetY();
	OpenGLPick result(4096);
	m_canvas->OnPick(result, x, y);

	Selection tempSelection = view->hover;
	view->hover.Clear();

	if(result.HasHits()){
		result.SortByNear();

		if(view->selection.IsSetEmpty()){
			view->hover.Add((Selection::BaseType) result.Get(0, 0),
					(size_t) result.Get(1, 0),
					(Selection::Type) result.Get(2, 0),
					(size_t) result.Get(3, 0));
		}else{
			for(size_t n = 0; n < result.GetCount(); ++n){
				size_t object = result.Get(1);
				Selection::Type type = (Selection::Type) result.Get(2);
				size_t ID = result.Get(3);
				if(view->selection.CanAdd(Selection::BaseObject, object, type)){
					view->hover.Add(Selection::BaseObject, object, type, ID);
				}
			}
		}
		if(tempSelection != view->hover) Refresh();
	}
	m_statusBar->SetStatusText(wxString(view->hover.ToString()));
	event.Skip();
}

void FrameMain::On3DSelect(wxMouseEvent& event)
{
	ProjectView * const view = wxStaticCast(GetView(), ProjectView);

//	if(selectRequests.empty()){
//		event.Skip();
//		return;
//	}
	std::cout << "FrameMain::On3DSelect(...);\n";
	int x = event.GetX();
	int y = event.GetY();
	OpenGLPick result(4096);
	m_canvas->OnPick(result, x, y);

	Selection temp;
	if(event.ShiftDown()) temp = view->selection;

	m_statusBar->SetStatusText(wxString(view->selection.ToString()), 1);

	if(!result.HasHits()) return;
	result.SortByNear();

	if(!selectRequests.empty()){
		bool hitfound = false;
		for(size_t n = 0; n < result.GetCount(); ++n){

			Selection temp2((Selection::BaseType) result.Get(0, n),
					(size_t) result.Get(1, n),
					(Selection::Type) result.Get(2, n),
					(size_t) result.Get(3, n));

			if(temp2.IsType(Selection::Axis)) temp2.SetBase(
					Selection::BaseNone);

			for(std::set <Selection>::iterator it = selectRequests.begin();
					it != selectRequests.end(); ++it){
				if(it->IsType(Selection::Object)){
					temp2 = Selection((Selection::Type) result.Get(0, n),
							(size_t) result.Get(1, n));
				}
				if(it->CanAdd(temp2) && temp.Add(temp2)){
					hitfound = true;
					break;
				}
			}
			if(hitfound) break;
		}

		if(temp.IsType(Selection::Object)){
			tree->SelectonToTree(temp);
		}
		view->selection = temp;
		if(!event.ShiftDown() && hitfound){
			AnswerSelection(temp);
		}
	}else{
		for(size_t n = 0; n < result.GetCount(); ++n){
			temp.Add((Selection::Type) result.Get(0, n),
					(size_t) result.Get(1, n));
		}
//		dialogObjectTransformation->SetSelection(temp);
		tree->SelectonToTree(temp);
	}

	m_statusBar->SetStatusText(wxString(view->selection.ToString()), 1);

	TransferDataToWindow();
	Refresh();
}

void FrameMain::OnSelectionChanged(wxTreeEvent& event)
{
	if(loopguard.TryLock() == wxMUTEX_BUSY) return;

//	wxTreeItemId id = event.GetItem();
//	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	ProjectView* view = wxStaticCast(GetView(), ProjectView);

	Selection treeSelection = tree->TreeToSelection();

	std::cout << "FrameMain::OnSelectionChanged(...) to "
			<< treeSelection.ToString();

	bool foundsomething = false;

	Selection clicked;
	for(std::set <Selection>::iterator request = selectRequests.begin();
			request != selectRequests.end(); ++request){
		if(!request->CanAdd(treeSelection.GetType())) continue;
		if(request->IsType(Selection::Object)) clicked.Add(treeSelection);
		foundsomething = true;
		break;
	}

	view->selection = treeSelection;

	if(foundsomething){
		AnswerSelection(clicked);
		loopguard.Unlock();
		std::cout << "\n";
		return;
	}
//	view->type = ProjectView::vIdle;
	if(treeSelection.IsType(Selection::Object)) view->type =
			ProjectView::vObject;
	if(treeSelection.IsType(Selection::Run)) view->type = ProjectView::vRun;
	if(treeSelection.IsType(Selection::Generator)) view->type =
			ProjectView::vGenerator;

	std::cout << " view->type = " << (int) view->type << ";\n";

	TransferDataToWindow(false);
	Refresh();
	loopguard.Unlock();
}

void FrameMain::OnSelectionChanging(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	if(data->type == TreeItem::itemProject) return;
	if(data->type == TreeItem::itemObject) return;
	if(data->type == TreeItem::itemSubObject) return;
	if(data->type == TreeItem::itemRun) return;
	if(data->type == TreeItem::itemGenerator) return;
	event.Veto();
}

void FrameMain::OnActivate(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	if(data->type == TreeItem::itemGroupObjects){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_OBJECTLOAD);
		ProcessEvent(menuEvent);
	}
	if(data->type == TreeItem::itemObject){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_OBJECTMODIFY);
		ProcessEvent(menuEvent);
	}
	if(data->type == TreeItem::itemGroupRun){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_RUNMODIFY);
		ProcessEvent(menuEvent);
	}

	if(data->type == TreeItem::itemRun){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_RUNMODIFY);
		ProcessEvent(menuEvent);
	}
	if(data->type == TreeItem::itemGenerator){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_GENERATORMODIFY);
		ProcessEvent(menuEvent);
	}
}

void FrameMain::OnActivateRightClickMenu(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

//	wxLogMessage(_T("RKMenu: %i - %i"), (int)data->type, (int)data->nr);

	wxMenu menu(_T(""));

	if(data->type == TreeItem::itemProject){
		menu.Append(ID_PROJECTRENAME, wxT("&Rename Project"));
		menu.AppendSeparator();
		menu.Append(wxID_SAVE, wxT("&Save Project"));
		menu.Append(wxID_SAVEAS, wxT("Save Project &As ..."));
		menu.AppendSeparator();
		menu.Append(wxID_EXIT, wxT("&Quit"));

	}

	if(data->type == TreeItem::itemGroupObjects){
		menu.Append(ID_OBJECTLOAD, wxT("&Load Object"));
	}

	if(data->type == TreeItem::itemObject){
		menu.Append(ID_OBJECTMODIFY, wxT("&Modify Object"));
		menu.Append(ID_OBJECTFLIPNORMALS, wxT("&Flip Normals"));
		menu.Append(ID_OBJECTRENAME, wxT("&Rename Object"));
		menu.Append(ID_OBJECTDELETE, wxT("&Delete Object"));
		menu.AppendSeparator();
		menu.Append(ID_RUNMODIFY, wxT("&Add Run"));
	}

//	if(data->type == itemGroupWorkpiece){
//		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
//	}
//	if(data->type == itemWorkpiece){
//		menu.Append(ID_WORKPIECESETUP, wxT("&Setup Workpiece"));
//		menu.AppendSeparator();
//		menu.Append(ID_WORKPIECEDELETE, wxT("&Delete Workpiece"));
//		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
//	}

	if(data->type == TreeItem::itemGroupRun){
		tree->SelectonToTree(Selection());
		menu.Append(ID_RUNMODIFY, wxT("&Add Run"));
		menu.AppendSeparator();
		menu.Append(ID_TOOLPATHGENERATE, wxT("&Generate Toolpath"));
	}

	if(data->type == TreeItem::itemRun){
		menu.Append(ID_RUNMODIFY, wxT("&Edit Run"));
		menu.Append(ID_RUNRENAME, wxT("&Rename Run"));
		menu.Append(ID_RUNDELETE, wxT("&Delete Run"));
		menu.AppendSeparator();
		menu.Append(ID_TOOLPATHGENERATE, wxT("&Generate Toolpath"));
		menu.Append(ID_TOOLPATHEXPORT, wxT("E&xport Toolpaths"));
	}

	if(data->type == TreeItem::itemGenerator){
		menu.Append(ID_GENERATORMODIFY, wxT("&Edit Generator"));
		menu.Append(ID_GENERATORRENAME, wxT("&Rename Run"));
		menu.Append(ID_GENERATORDELETE, wxT("&Delete Generator"));
		menu.AppendSeparator();
		menu.Append(ID_TOOLPATHGENERATE, wxT("&Generate Toolpath"));
		menu.Append(ID_TOOLPATHEXPORT, wxT("E&xport Toolpath"));
	}

//	if(data->type == itemToolpath){
//		menu.Append(ID_GENERATORSETUP, wxT("Setup &Generator"));
//		menu.AppendSeparator();
//		menu.Append(ID_TOOLPATHSAVE, wxT("Save &Toolpath"));
//	}

	if(menu.GetMenuItemCount() > 0) PopupMenu(&menu); //, event.GetPoint());
}

void FrameMain::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	if(data->type == TreeItem::itemProject) return;
	if(data->type == TreeItem::itemObject) return;
	if(data->type == TreeItem::itemRun) return;
	if(data->type == TreeItem::itemGenerator) return;

// Stop editing, if it cannot be changed.
	event.Veto();
}

void FrameMain::OnEndLabelEdit(wxTreeEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor* cmdProc = project->GetCommandProcessor();
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	wxString newName = event.GetLabel();
	if(newName.IsEmpty()){
		event.Veto();
		return;
	}

	if(data->type == TreeItem::itemProject){
		if(newName == project->GetTitle()) return;
		cmdProc->Submit(new CommandProjectRename(
		_("Project renamed to ") + newName, project, newName));
		return;
	};

	if(data->type == TreeItem::itemObject){
		if(!project->Has(Selection::Object, data->ID)) return;
		if(newName == project->Get3DObject(data->ID).name) return;
		cmdProc->Submit(new CommandObjectRename(
		_("Object renamed to ") + newName, project, data->ID, newName));
		return;
	};

	if(data->type == TreeItem::itemRun){
		if(!project->Has(Selection::Run, data->ID)) return;
		if(newName == project->GetRun(data->ID).name) return;
		cmdProc->Submit(
				new CommandRunRename(_("Run renamed to ") + newName, project,
						data->ID, newName));
		return;
	};

	if(data->type == TreeItem::itemGenerator){
		size_t runID = dialogToolpathGenerator->GetRunID();
		size_t generatorID = data->ID;
		if(!project->Has(
				Selection(Selection::BaseRun, runID, Selection::Generator,
						generatorID))) return;
		if(newName == project->GetRun(runID).generators.at(generatorID)->name) return;
		cmdProc->Submit(
				new CommandRunGeneratorRename(
				_("Generator renamed to ") + newName, project, runID,
						generatorID, newName));
		return;
	};

	event.Veto();
}

void FrameMain::UpdateSimulation(wxCommandEvent& event)
{
	m_canvas->Refresh();
}

//void FrameMain::OnMachineLoad(wxCommandEvent& event)
//{
////	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
////	int selected = tree->GetFirstSelectedRun();
////	if(selected < 0) return;
////
////	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
////			_(
////					"All machine descriptions  (*.lua;*.zip)|*.lua;*.zip|Machine descriptions (LUA Files)  (*.lua)|*.lua|Packed Machine descriptions  (*.zip)|*.zip|Text files  (*.txt)|*.txt|All files|*.*"),
////			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
////
////	if(wxDir::Exists(filepaths.lastMachineDirectory)){
////		dialog.SetDirectory(filepaths.lastMachineDirectory);
////	}else{
////		if(wxDir::Exists(filepaths.lastProjectDirectory)){
////			dialog.SetDirectory(filepaths.lastProjectDirectory);
////		}
////	}
////	Project* project = wxStaticCast(GetDocument(), Project);
////
////	if(dialog.ShowModal() == wxID_OK){
////		wxFileName fileName(dialog.GetPath());
////		if(project->GetRun(selected).machine.Load(fileName)){
////			filepaths.lastMachineDirectory = fileName.GetPath();
////		}else{
////			wxLogError
////			(project->GetRun(selected).machine.textOut);
////		}
////		TransferDataToWindow();
////	}
//}
//
//void FrameMain::OnMachineReload(wxCommandEvent& event)
//{
////	Project* project = wxStaticCast(GetDocument(), Project);
////	int selected = tree->GetFirstSelectedRun();
////	if(selected < 0) return;
////	if(!project->GetRun(selected).machine.ReLoad()){
////		wxLogError
////		(project->GetRun(selected).machine.textOut);
////	}
////	TransferDataToWindow();
//}
//
//void FrameMain::OnMachineDebugger(wxCommandEvent& event)
//{
////	dialogDebugger->Show(true);
////	dialogDebugger->Raise();
//}
//
//void FrameMain::OnFlipDrillSetup(wxCommandEvent& event)
//{
//}
//
//void FrameMain::OnToolboxEdit(wxCommandEvent& event)
//{
////	dialogToolbox->Show(true);
////	dialogToolbox->Raise();
////	TransferDataToWindow();
//}
//
//void FrameMain::OnToolboxLoad(wxCommandEvent& event)
//{
////	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
////	ProjectView* view = wxStaticCast(GetView(), ProjectView);
////	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
////			_("Toolbox (*.xml)|*.xml|All files|*.*"),
////			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
////	if(wxDir::Exists(filepaths.lastToolboxDirectory)){
////		dialog.SetDirectory(filepaths.lastToolboxDirectory);
////	}else{
////		if(wxDir::Exists(filepaths.lastProjectDirectory)){
////			dialog.SetDirectory(filepaths.lastProjectDirectory);
////		}
////	}
////	if(dialog.ShowModal() == wxID_OK){
////		wxFileName fileName(dialog.GetPath());
////		if(view->toolbox.LoadToolBox(fileName)){
////			filepaths.lastToolboxDirectory = fileName.GetPath();
////			TransferDataToWindow();
////		}
////	}
//}
//
//void FrameMain::OnToolboxSave(wxCommandEvent &event)
//{
////	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
////	ProjectView* view = wxStaticCast(GetView(), ProjectView);
////	wxFileDialog dialog(this, _("Save toolbox..."), _T(""), _T(""),
////			_("Toolbox (*.xml)|*.xml|All files|*.*"),
////			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
////	if(view->toolbox.fileName.IsOk()){
////		dialog.SetPath(view->toolbox.fileName.GetFullPath());
////	}else{
////		if(wxDir::Exists(filepaths.lastToolboxDirectory)){
////			dialog.SetDirectory(filepaths.lastToolboxDirectory);
////		}
////	}
////	if(dialog.ShowModal() == wxID_OK){
////		wxFileName fileName;
////		fileName = dialog.GetPath();
////		if(view->toolbox.SaveToolBox(fileName)){
////			TransferDataToWindow();
////		}
////	}
//}
//
//void FrameMain::OnGeneratorSetup(wxCommandEvent& event)
//{
////	dialogToolpathGenerator->Show();
////	dialogToolpathGenerator->Raise();
////	TransferDataToWindow();
//}
//
void FrameMain::OnToolpathGenerate(wxCommandEvent& event)
{
#ifndef _DEBUGMODE
	wxWindowDisabler disableAll;
	wxBusyInfo wait(_("Generating Toolpaths..."), this);
#endif
	Project* project = wxStaticCast(GetDocument(), Project);
	project->GenerateToolpaths();

//	project.PropagateChanges();
//
//	size_t count = 0;
//	size_t maxNr = project.ToolpathToGenerate();
//
//	wxProgressDialog dialog(_T("Generating Toolpaths"), _T(""), maxNr, this);
//	dialog.Show();
//
//	count++;
//	while(project.ToolpathGenerate()){
//		dialog.Update(count, project.TollPathGenerateCurrent());
//	}

	TransferDataToWindow();
}
//
//void FrameMain::OnGeneratorAutomatic(wxCommandEvent& event)
//{
////	project.processToolpath = event.IsChecked();
////	TransferDataToWindow();
//}
//
//void FrameMain::OnGeneratorRestart(wxCommandEvent& event)
//{
//}

//void FrameMain::OnActivateStereo3D(wxCommandEvent& event)
//{
////	if(m_canvas->stereoMode == stereoOff){
////		m_canvas->stereoMode = stereoAnaglyph;
////	}else{
////		m_canvas->stereoMode = stereoOff;
////	}
////	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
////	TransferDataToWindow();
//}
//
//void FrameMain::OnShowAnimationControl(wxCommandEvent& event)
//{
////	dialogAnimation->Show(true);
////	dialogAnimation->Raise();
////	TransferDataToWindow();
//}
//
//void FrameMain::OnExtraWindowClose(wxCommandEvent& event)
//{
////	dialogObjectTransformation->Show(false);
////	dialogDebugger->Show(false);
////	dialogToolbox->Show(false);
////	dialogToolpathGenerator->Show(false);
////	dialogAnimation->Show(false);
////
////	TransferDataToWindow();
//}
//
//void FrameMain::OnShowLogWindow(wxCommandEvent& event)
//{
//	logWindow->Show();
//	logWindow->GetFrame()->Raise();
//	TransferDataToWindow();
//}
//
//void FrameMain::OnViewSet(wxCommandEvent& event)
//{
////	switch(event.GetId()){
////	case ID_VIEWFRONT:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(-M_PI_2, 0, 0);
////		m_statusBar->SetStatusText(_T("ID_VIEWFRONT"), 1);
////		break;
////	case ID_VIEWBACK:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(M_PI_2, 0, 0);
////		m_statusBar->SetStatusText(_T("ID_VIEWBACK"), 1);
////		break;
////	case ID_VIEWLEFT:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, M_PI_2, 0);
////		m_statusBar->SetStatusText(_T("ID_VIEWLEFT"), 1);
////		break;
////	case ID_VIEWRIGHT:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, -M_PI_2, 0);
////		m_statusBar->SetStatusText(_T("ID_VIEWRIGHT"), 1);
////		break;
////	case ID_VIEWTOP:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_statusBar->SetStatusText(_T("ID_VIEWTOP"), 1);
////		break;
////	case ID_VIEWBOTTOM:
////		m_canvas->rotmat = AffineTransformMatrix::Identity();
////		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, M_PI, 0);
////		m_statusBar->SetStatusText(_T("ID_VIEWBOTTOM"), 1);
////		break;
////	}
////	TransferDataToWindow();
//}
//
