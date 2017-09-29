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

#include "FrameMain.h"

#include "../controller/DialogSetup6DOFController.h"
#include "DialogAbout.h"
#include "DialogSetupUnits.h"
#include "DialogTestGCode.h"

#include "../project/generator/ToolpathGeneratorThread.h"
#include "../project/command/CommandProjectRename.h"
#include "../project/command/CommandObjectLoad.h"
#include "../project/command/CommandObjectDelete.h"
#include "../project/command/CommandObjectRename.h"
#include "../project/command/CommandObjectTransform.h"
#include "../project/command/CommandWorkpieceRename.h"
#include "../project/command/CommandWorkpieceDelete.h"
#include "../project/command/CommandRunAdd.h"
#include "../project/command/CommandRunRename.h"
#include "../project/command/CommandRunRemove.h"

#include "DnDFile.h"

#include "MathParser.h"
#include "../languages.h"
#include "IDs.h"

#ifndef __WIN32__
#include "../icon/logo32.xpm"
#include "../icon/logo48.xpm"
#include "../icon/logo64.xpm"
#include "../icon/logo128.xpm"
#endif

#include <wx/icon.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include <wx/dir.h>
#include <unistd.h>

FrameMain::FrameMain(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIMain(parent)
{

//	MathParser x;
//	x.SetString(_T("1,000 * 15 mA"));

	selectedTargetPosition = 0;

#ifndef __WIN32__
	//TODO: Check, why the icon is not working under Windows / Code::Blocks.
	wxIconBundle logo;
	logo.AddIcon(wxIcon(logo32_xpm));
	logo.AddIcon(wxIcon(logo48_xpm));
	logo.AddIcon(wxIcon(logo64_xpm));
	logo.AddIcon(wxIcon(logo128_xpm));
	SetIcons(logo);
#endif

	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			false);

// Setup configuration
	this->config = config;
	this->locale = locale;

	settings.GetConfigFrom(config);
	// Set the window size according to the config file
	int w, h;
	w = config->Read(_T("MainFrameWidth"), 600);
	h = config->Read(_T("MainFrameHeight"), 400);
	SetClientSize(w, h);
	control.GetConfigFrom(config);

	m_fileHistory = new wxFileHistory();
	m_fileHistory->UseMenu(m_menuProjectRecent);
	m_fileHistory->AddFilesToMenu(m_menuProjectRecent);
	m_fileHistory->Load(*config);

	m_canvas->SetDropTarget(new DnDFile(&project, this));
	m_tree->SetDropTarget(new DnDFile(&project, this));

	m_canvas->SetController(control);

	this->Connect(ID_UPDATESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateSimulation));

	this->Connect(ID_REFRESHALL, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshAll));
	this->Connect(ID_REFRESHMAINGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMainGUI));
	this->Connect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Refresh3DView));

	this->Connect(wxID_FILE1, wxID_FILE9, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::OnProjectLoadRecent));

	//TODO: Why is the KeyDown event connected to the canvas?
	m_canvas->Connect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(FrameMain::OnKeyDown), NULL, this);

	commandProcessor.SetEditMenu(m_menuEdit);
	commandProcessor.Initialize();
	commandProcessor.MarkAsSaved();

	m_helpController = new wxHelpController;
	m_helpController->Initialize(_T("./doc/help/genericcam.hhp"));

	dialogObjectTransformation = new DialogObjectTransformation(this, &project,
			&commandProcessor, &settings);
	dialogStockMaterial = new DialogStockMaterial(this, &project, &stock,
			&settings);
	dialogWorkpiece = new DialogWorkpiece(this, &project, &stock,
			&commandProcessor);
	dialogPlacement = new DialogPlacement(this, &project, &commandProcessor,
			&settings);
	dialogRun = new DialogRun(this, &project, &toolbox, &commandProcessor,
			&settings);
	dialogDebugger = new DialogMachineDebugger(this, &settings, &midi);
	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settings);
	dialogSetupMidi = new DialogSetupMidi(this, &midi);
	dialogToolbox = new DialogToolbox(this, &project, &toolbox, &settings);
	dialogToolpathGenerator = new DialogToolpathGenerator(this, &project,
			&commandProcessor, &settings);
	dialogAnimation = new DialogAnimation(this, &project);

	wxString dialect;
	config->Read(_T("GCodeDialect"), &dialect, _T("RS274NGC"));
	m_menuDialect->Check(ID_DIALECT_RS274NGC,
			dialect.CmpNoCase(_T("RS274NGC")) == 0);
	m_menuDialect->Check(ID_DIALECT_FANUCM,
			dialect.CmpNoCase(_T("FanucM")) == 0);

	// Connect the project to the 3D canvas
	m_canvas->InsertProject(&project);
	settings.WriteToCanvas(m_canvas);
	tree = new TreeSetup(m_tree, &project);

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
			this);

	dt = 50e-3; // s
	timer.Start(round(dt * 1000.0)); // ms

	m_canvas->display = CanvasMain::displayObjects;

	TransferDataToWindow();
}

FrameMain::~FrameMain()
{
	// Disconnect events
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
			this);
	m_canvas->Disconnect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(FrameMain::OnKeyDown), NULL, this);
	this->Disconnect(wxID_FILE1, wxID_FILE9, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::OnProjectLoadRecent));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Refresh3DView));
	this->Disconnect(ID_REFRESHMAINGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMainGUI));
	this->Disconnect(ID_REFRESHALL, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshAll));

	this->Disconnect(ID_UPDATESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateSimulation));

	// Save the configuration of the 6DOF controller
	control.WriteConfigTo(config);

	// Save the size of the mainframe
	int w, h;
	GetClientSize(&w, &h);
	config->Write(_T("MainFrameWidth"), (long) w);
	config->Write(_T("MainFrameHeight"), (long) h);

	wxString dialect = _T("RS274NGC");
	if(m_menuDialect->IsChecked(ID_DIALECT_FANUCM)) dialect = _T("FanucM");
	config->Write(_T("GCodeDialect"), dialect);

	delete m_helpController;
	settings.WriteConfigTo(config);
	m_fileHistory->Save(*config);
	delete m_fileHistory;
	delete config; // config is written back on deletion of object
}

bool FrameMain::TransferDataToWindow(void)
{
	// Populate the treeview
	tree->Update();

//	m_menuToolpath->Check(ID_GENERATORAUTOMATIC, project.processToolpath);
	m_menuSettings->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	//TODO: Reactivate
//	m_toolBar->ToggleTool(ID_DISPLAYMACHINE, project.displayMachine);
//	m_toolBar->ToggleTool(ID_DISPLAYMATERIAL, project.displayGeometry);

	wxString temp = _T("Generic CAM - ");
	if(commandProcessor.IsDirty()) temp += _T("* ");
	temp += project.name;
	this->SetTitle(temp);

//	m_canvas->displayAnimation = dialogAnimation->IsShown();

	dialogObjectTransformation->TransferDataToWindow();
	dialogStockMaterial->TransferDataToWindow();
	dialogWorkpiece->TransferDataToWindow();
	dialogPlacement->TransferDataToWindow();
	dialogToolbox->TransferDataToWindow();
	dialogRun->TransferDataToWindow();
	dialogDebugger->TransferDataToWindow();
	dialogToolpathGenerator->TransferDataToWindow();
	dialogAnimation->TransferDataToWindow();
	dialogSetupStereo3D->TransferDataToWindow();

	Refresh();
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

void FrameMain::RefreshAll(wxCommandEvent& event)
{
	settings.WriteToCanvas(m_canvas);
	TransferDataToWindow();
}

void FrameMain::RefreshMainGUI(wxCommandEvent& event)
{
	tree->UpdateSelection();
	Refresh();
}

void FrameMain::Refresh3DView(wxCommandEvent& event)
{
	settings.WriteToCanvas(m_canvas);
	m_canvas->Refresh();
}

void FrameMain::UpdateSimulation(wxCommandEvent& event)
{
	m_canvas->Refresh();
}

size_t FrameMain::GetFreeSystemMemory()
{
#ifdef __UNIX__
	long pages = sysconf(_SC_AVPHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
#endif
#ifdef __WIN__
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	//TODO: Change this to return available memory.
	return status.ullTotalPhys;
#endif
}

void FrameMain::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}

void FrameMain::OnTimer(wxTimerEvent& event)
{
	t += dt;

	wxString temp;
//	temp = wxString::Format(_T("Free RAM: %lu MB"),
//			GetFreeSystemMemory() / 1024 / 1024);
//
//	m_statusBar->SetStatusText(temp, 1);

	temp = wxString::Format(_T("x: %4u y: %4u  - %4u %4u %4u %4u"), m_canvas->x,
			m_canvas->y, m_canvas->c0, m_canvas->ct1, m_canvas->ct2,
			m_canvas->ct3);
	m_statusBar->SetStatusText(temp, 1);

//	if(project.processToolpath){
//		if(project.GenerateToolpaths()) TransferDataToWindow();
//	}
}

void FrameMain::OnKeyDown(wxKeyEvent& event)
{
	int k = event.GetKeyCode();

//	if(k == WXK_ESCAPE){
//		this->Close();
//	}

// Select placement
//	if(k == WXK_NUMPAD_ADD
//			&& selectedTargetPosition
//					< project.run[0].placements.GetCount() - 1) selectedTargetPosition++;
//	if(k == WXK_NUMPAD_SUBTRACT && selectedTargetPosition > 0) selectedTargetPosition--;

//	if(selectedTargetPosition
//			< project.run[0].placements.GetCount()
//			&& project.run[0].placements[selectedTargetPosition].isMovable){
//
//		if(k == WXK_UP) project.run[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.0, 0.001, 0.0);
//		if(k == WXK_DOWN) project.run[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.0, -0.001, 0.0);
//		if(k == WXK_RIGHT) project.run[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.001, 0.0, 0.0);
//		if(k == WXK_LEFT) project.run[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				-0.001, 0.0, 0.0);
//
//		if(k == WXK_PAGEUP){
//			AffineTransformMatrix temp;
//			temp = AffineTransformMatrix::RotateXYZ(0.0, 0.0, M_PI / 16);
//			project.run[0].placements[selectedTargetPosition].matrix =
//					project.run[0].placements[selectedTargetPosition].matrix
//							* temp;
//		}
//		if(k == WXK_PAGEDOWN){
//			AffineTransformMatrix temp;
//			temp = AffineTransformMatrix::RotateXYZ(0.0, 0.0, -M_PI / 16);
//			project.run[0].placements[selectedTargetPosition].matrix =
//					project.run[0].placements[selectedTargetPosition].matrix
//							* temp;
//		}
//
//		m_statusBar->SetStatusText(_T("Dummy text..."));
//
//		this->Refresh();
//	}

	event.Skip();
}

void FrameMain::On3DSelect(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	OpenGLPick result;
	m_canvas->OnPick(result, x, y);

	size_t n;
	if(result.HasHits()){
		result.SortByNear();
		if(result.Get(0, 0) == 1 && result.Get(0, 1) > 0){
			size_t id = result.Get(0, 1) - 1;
			for(n = 0; n < project.objects.GetCount(); n++)
				project.objects[n].selected = (n == id);
			tree->UpdateSelection();
			Refresh();
		}
	}
}

void FrameMain::On3DDClick(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	OpenGLPick result;
	m_canvas->OnPick(result, x, y);
	if(result.HasHits()){
		result.SortByNear();
		if(result.Get(0, 0) == 1){
//	       <...>
		}
	}

}

void FrameMain::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	if(data->dataType == itemProject) return;
	if(data->dataType == itemObject) return;
	if(data->dataType == itemWorkpiece) return;
	if(data->dataType == itemRun) return;

// Stop editing, if it cannot be changed.
	event.Veto();
}

void FrameMain::OnEndLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	wxString newName = event.GetLabel();
	if(newName.IsEmpty()){
		event.Veto();
		return;
	}

	if(data->dataType == itemProject){
		if(newName == project.name) return;
		commandProcessor.Submit(
				new CommandProjectRename(_("Project renamed to ") + newName,
						&project, newName));
		TransferDataToWindow();
		return;
	};

	if(data->dataType == itemObject){
		if(newName == project.objects[data->nr].name) return;
		commandProcessor.Submit(
				new CommandObjectRename(_("Object renamed to ") + newName,
						&project, data->nr, newName));
		TransferDataToWindow();
		return;
	};

	if(data->dataType == itemWorkpiece){
		if(newName == project.workpieces[data->nr].name) return;
		commandProcessor.Submit(
				new CommandWorkpieceRename(_("Workpiece renamed to ") + newName,
						&project, data->nr, newName));
		TransferDataToWindow();
		return;
	};

	if(data->dataType == itemRun){
		if(newName == project.run[data->nr].name) return;
		commandProcessor.Submit(
				new CommandRunRename(_("Run renamed to ") + newName, &project,
						data->nr, newName));
		TransferDataToWindow();
		return;
	};

	event.Veto();
}

void FrameMain::OnActivateRightClickMenu(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

//	wxLogMessage(_T("RKMenu: %i - %i"), (int)data->dataType, (int)data->nr);

	wxMenu menu(_T(""));

	if(data->dataType == itemProject){

		menu.Append(wxID_OPEN, wxT("&Load Project"));
		menu.Append(wxID_SAVE, wxT("&Save Project"));
		menu.Append(wxID_SAVEAS, wxT("Save Project &As ..."));
		menu.Append(ID_PROJECTRENAME, wxT("&Rename Project"));
	}

	if(data->dataType == itemGroupObject){
		menu.Append(ID_OBJECTLOAD, wxT("&Load Object"));
		menu.AppendSeparator();
		menu.Append(ID_OBJECTMODIFY, wxT("&Modify Object"));
	}

	if(data->dataType == itemObject){
		menu.Append(ID_OBJECTMODIFY, wxT("&Modify Object"));
		menu.AppendSeparator();
		menu.Append(ID_OBJECTFLIPNORMALS, wxT("&Flip Normals"));
		menu.Append(ID_OBJECTRENAME, wxT("&Rename Object"));
		menu.Append(ID_OBJECTDELETE, wxT("&Delete Object"));
		menu.Append(ID_OBJECTLOAD, wxT("&Load Object"));
	}

	if(data->dataType == itemGroupWorkpiece){
		menu.Append(ID_WORKPIECEADD, wxT("&Add Workpiece (and Objects)"));
		menu.AppendSeparator();
		menu.Append(ID_STOCKORGANIZE, wxT("&Organize Stock"));
		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
	}
	if(data->dataType == itemWorkpiece){
		menu.Append(ID_WORKPIECESETUP, wxT("&Setup Workpiece"));
		menu.AppendSeparator();
		menu.Append(ID_WORKPIECEADD, wxT("&Add Objects to Workpiece"));
		menu.Append(ID_WORKPIECEDELETE, wxT("&Delete Workpiece"));
		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
	}

	if(data->dataType == itemGroupRun){
		menu.Append(ID_RUNADD, wxT("&Add Run"));
		menu.AppendSeparator();
		menu.Append(ID_RUNEDIT, wxT("&Setup Run"));
	}

	if(data->dataType == itemMachine){
		menu.Append(ID_MACHINELOAD, wxT("Load &Machine"));
		menu.Append(ID_GENERATORSETUP, wxT("Setup &Generators"));
		menu.AppendSeparator();
		menu.Append(ID_MACHINERELOAD, wxT("&Reload Machine"));
	}

	if(data->dataType == itemRun){
		menu.Append(ID_RUNEDIT, wxT("&Setup Run"));
		menu.Append(ID_GENERATORSETUP, wxT("Setup &Generator"));
		menu.AppendSeparator();
		menu.Append(ID_TOOLPATHSAVE, wxT("Save &Toolpath"));
		menu.AppendSeparator();
		menu.Append(ID_RUNADD, wxT("&Add Run"));
		menu.Append(ID_RUNDELETE, wxT("&Delete Run"));
	}

	if(data->dataType == itemToolpath){
		menu.Append(ID_GENERATORSETUP, wxT("Setup &Generator"));
		menu.AppendSeparator();
		menu.Append(ID_TOOLPATHSAVE, wxT("Save &Toolpath"));
	}

	if(menu.GetMenuItemCount() > 0) PopupMenu(&menu, event.GetPoint());
}

void FrameMain::OnActivate(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	if(data->dataType == itemGroupObject){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_OBJECTLOAD);
		ProcessEvent(menuEvent);
	}
	if(data->dataType == itemObject){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_OBJECTMODIFY);
		ProcessEvent(menuEvent);
	}
	if(data->dataType == itemGroupWorkpiece){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_WORKPIECEADD);
		ProcessEvent(menuEvent);
	}
	if(data->dataType == itemWorkpiece){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_WORKPIECESETUP);
		ProcessEvent(menuEvent);
	}
	if(data->dataType == itemGroupRun){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_RUNADD);
		ProcessEvent(menuEvent);
	}
	if(data->dataType == itemRun){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_RUNEDIT);
		ProcessEvent(menuEvent);
	}

	if(data->dataType == itemToolpath){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_GENERATORSETUP);
		ProcessEvent(menuEvent);
	}

}

void FrameMain::OnSelectionChanged(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	tree->UpdateVariables();

	if(data->dataType == itemRun){
		if(m_tree->IsSelected(id)){
			// Only allow one item selected at a time
			size_t n;
			for(n = 0; n < project.run.GetCount(); n++)
				project.run[n].Select(n == data->nr);
			tree->UpdateSelection();
		}
	}

	switch(data->dataType){
	case itemProject:
	case itemGroupObject:
	case itemObject:
	case itemSubObject:
		m_canvas->display = CanvasMain::displayObjects;
		break;
	case itemGroupWorkpiece:
	case itemWorkpiece:
	case itemPlacement:
	case itemObjectLink:
		m_canvas->display = CanvasMain::displayWorkpieces;
		break;
	case itemGroupRun:
	case itemRun:
	case itemRunWorkpiece:
	case itemMachine:
	case itemToolpath:
		m_canvas->display = CanvasMain::displayRun;
		break;
	}

	TransferDataToWindow();
}

void FrameMain::OnSelectionChanging(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	if(data->dataType == itemProject) return;
	if(data->dataType == itemObject) return;
	if(data->dataType == itemWorkpiece) return;
	if(data->dataType == itemPlacement) return;
	if(data->dataType == itemRun) return;
	if(data->dataType == itemToolpath) return;

	event.Veto();
}

void FrameMain::OnToolbarButton(wxCommandEvent& event)
{
	TransferDataFromWindow();
	TransferDataToWindow();
}

void FrameMain::OnProjectNew(wxCommandEvent& event)
{
	// TODO: Multiple Project%s in one session
//	Project temp;
//	project.Add(temp);
	commandProcessor.ClearCommands();
	project.Clear();
	commandProcessor.MarkAsSaved();
	commandProcessor.SetMenuStrings();
	TransferDataToWindow();
	tree->UpdateSelection();
}

void FrameMain::OnProjectRename(wxCommandEvent& event)
{
	wxTextEntryDialog dialog(this, _("Enter new project name:"),
			_T("Rename Project"), project.name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project.name) return;

		CommandProjectRename * command = new CommandProjectRename(
		_("Project renamed to ") + dialog.GetValue(), &project,
				dialog.GetValue());
		commandProcessor.Submit(command);
		TransferDataToWindow();
	}
}

void FrameMain::ProjectLoad(wxString fileName)
{
	project.Load(fileName);

	commandProcessor.ClearCommands();
	commandProcessor.MarkAsSaved();
	TransferDataToWindow();
}

void FrameMain::OnProjectLoad(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open Project..."), _T(""), _T(""),
			_("Generic CAM Project (*.zip)|*.zip;*.ZIP|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings.lastProjectDirectory)){
		dialog.SetDirectory(settings.lastProjectDirectory);
	}

	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		m_fileHistory->AddFileToHistory(fileName.GetFullPath());
		if(project.Load(fileName)){
			settings.lastProjectDirectory = fileName.GetPath();
			TransferDataToWindow();
			tree->UpdateSelection();
		}
	}
}

void FrameMain::OnProjectLoadRecent(wxCommandEvent& event)
{
	wxString fileName(
			m_fileHistory->GetHistoryFile(event.GetId() - wxID_FILE1));
	if(!fileName.empty() && project.Load(fileName)){
		TransferDataToWindow();
		tree->UpdateSelection();
	}
}

void FrameMain::OnProjectSave(wxCommandEvent& event)
{
	if(!project.fileName.IsOk()) OnProjectSaveAs(event);
	if(project.Save(project.fileName)){
		commandProcessor.MarkAsSaved();
	}
	TransferDataToWindow();
}

void FrameMain::OnProjectSaveAs(wxCommandEvent &event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Save Project As..."), _T(""), _T(""),
			_("Generic CAM Project (*.zip)|*.zip|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(settings.lastProjectDirectory)){
		dialog.SetDirectory(settings.lastProjectDirectory);
	}

	if(project.fileName.IsOk()) dialog.SetFilename(
			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		if(fileName.GetExt().IsEmpty()) fileName.SetExt(_T("zip"));
		m_fileHistory->AddFileToHistory(fileName.GetFullPath());
		if(project.Save(fileName)){
			commandProcessor.MarkAsSaved();
			settings.lastProjectDirectory = project.fileName.GetPath();
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnQuit(wxCommandEvent& event)
{
	Close();
}

void FrameMain::OnUndo(wxCommandEvent& event)
{
	commandProcessor.Undo();
	dialogToolpathGenerator->UndoChanges();
	TransferDataToWindow();
}

void FrameMain::OnRedo(wxCommandEvent& event)
{
	commandProcessor.Redo();
	dialogToolpathGenerator->UndoChanges();
	TransferDataToWindow();
}

void FrameMain::OnObjectLoad(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open Object..."), _T(""), _T(""),
			_(
					"All supported files (*.dxf; *.stl; *.gts)|*.dxf;*DXF;*.stl;*.STL;*.gts;*.GTS|DXF Files (*.dxf)|*.dxf;*.DXF|Stereolithography files (STL files) (*.stl)|*.stl;*.STL|GTS files (*.gts)|*.gts;*.GTS|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

	if(wxDir::Exists(settings.lastObjectDirectory)){
		dialog.SetDirectory(settings.lastObjectDirectory);
	}else{
		if(wxDir::Exists(settings.lastProjectDirectory)){
			dialog.SetDirectory(settings.lastProjectDirectory);
		}
	}

	if(dialog.ShowModal() == wxID_OK){
		wxArrayString paths;
		dialog.GetPaths(paths);

		size_t n;
		for(n = 0; n < paths.GetCount(); n++){
			fileName = paths[n];
			commandProcessor.Submit(
					new CommandObjectLoad(
							(_("Load Object: ") + fileName.GetName()),
							&project, paths[n]));
			if(n == 0) settings.lastObjectDirectory = fileName.GetPath();
		}
		TransferDataToWindow();
	}
}

void FrameMain::OnObjectModify(wxCommandEvent& event)
{
	dialogObjectTransformation->Show(true);
	dialogObjectTransformation->Raise();
	TransferDataToWindow();
}

void FrameMain::OnObjectRename(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int i = tree->GetFirstSelectedObject();
	if(i < 0 || i >= project.objects.GetCount()) return;
	wxTextEntryDialog dialog(this, _("Enter new name:"),
	_T("Rename Object ") + project.objects[i].name,
			project.objects[i].name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project.objects[i].name) return;
		commandProcessor.Submit(
				new CommandObjectRename(
				_("Object renamed to ") + dialog.GetValue(), &project, i,
						dialog.GetValue()));
		TransferDataToWindow();
	}
}

void FrameMain::OnObjectDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tree->UpdateVariables();
	int i = tree->GetFirstSelectedObject();
	if(i < 0 || i >= project.objects.GetCount()) return;
	commandProcessor.Submit(
			new CommandObjectDelete(
			_("Object ") + project.objects[i].name + _(" deleted."),
					&project, i));
	TransferDataToWindow();
}

void FrameMain::OnObjectFlipNormals(wxCommandEvent& event)
{
	size_t n;
	for(n = 0; n < project.objects.GetCount(); n++){
		if(project.objects[n].selected){
			AffineTransformMatrix matrix = project.objects[n].displayTransform
					* project.objects[n].matrix;
			CommandObjectTransform * command = new CommandObjectTransform(
					project.objects[n].name + _(": Flipped normal vectors"),
					&project, n, false, false, false, true, matrix);
			commandProcessor.Submit(command);
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnStockEdit(wxCommandEvent& event)
{
	dialogStockMaterial->Show(true);
	dialogStockMaterial->Raise();
	dialogStockMaterial->Initialize();
	TransferDataToWindow();
}

void FrameMain::OnWorkpieceSetup(wxCommandEvent& event)
{
	dialogPlacement->Show(true);
	dialogPlacement->Raise();
	TransferDataToWindow();
}

void FrameMain::OnWorkpieceAdd(wxCommandEvent& event)
{
	dialogWorkpiece->Show(true);
	dialogWorkpiece->Raise();
	TransferDataToWindow();
}

void FrameMain::OnWorkpieceDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tree->UpdateVariables();
	size_t i;
	for(i = project.workpieces.GetCount(); i > 0; i--){
		if(project.workpieces[i - 1].selected){
			commandProcessor.Submit(
					new CommandWorkpieceDelete(
							_("Remove workpiece ")
									+ project.workpieces[i - 1].name, &project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnWorkpieceDeleteUnused(wxCommandEvent& event)
{
	TransferDataFromWindow();
	size_t i;
	for(i = project.workpieces.GetCount(); i > 0; i--){
		if(project.workpieces[i - 1].placements.GetCount() == 0){
			commandProcessor.Submit(
					new CommandWorkpieceDelete(
							_("Remove workpiece ")
									+ project.workpieces[i - 1].name, &project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnRunAdd(wxCommandEvent& event)
{
	unsigned int i = project.run.GetCount() + 1;
	commandProcessor.Submit(
			new CommandRunAdd(_("Add run"), &project,
					wxString::Format(_("Run #%u"), i)));
	TransferDataToWindow();
}

void FrameMain::OnRunEdit(wxCommandEvent& event)
{
	dialogRun->Show(true);
	dialogRun->Raise();
	TransferDataToWindow();
}

void FrameMain::OnRunDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tree->UpdateVariables();
	size_t i;
	for(i = project.run.GetCount(); i > 0; i--){
		if(project.run[i - 1].selected){
			commandProcessor.Submit(new CommandRunRemove(
			_("Remove run ") + project.run[i - 1].name, &project, i - 1));
		}
	}
	TransferDataToWindow();
}
void FrameMain::OnMachineLoad(wxCommandEvent& event)
{
	int selected = tree->GetFirstSelectedRun();
	if(selected < 0) return;

	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"All machine descriptions  (*.lua;*.zip)|*.lua;*.zip|Machine descriptions (LUA Files)  (*.lua)|*.lua|Packed Machine descriptions  (*.zip)|*.zip|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings.lastMachineDirectory)){
		dialog.SetDirectory(settings.lastMachineDirectory);
	}else{
		if(wxDir::Exists(settings.lastProjectDirectory)){
			dialog.SetDirectory(settings.lastProjectDirectory);
		}
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(project.run[selected].machine.Load(fileName)){
			settings.lastMachineDirectory = fileName.GetPath();
		}else{
			wxLogError
			(project.run[selected].machine.textOut);
		}
		TransferDataToWindow();
	}
}

void FrameMain::OnMachineReload(wxCommandEvent& event)
{
	int selected = tree->GetFirstSelectedRun();
	if(selected < 0) return;

	if(!project.run[selected].machine.ReLoad()){

		wxLogError
		(project.run[selected].machine.textOut);
	}
	TransferDataToWindow();
}

void FrameMain::OnMachineDebugger(wxCommandEvent& event)
{
	dialogDebugger->Show(true);
	dialogDebugger->Raise();
}

void FrameMain::OnFlipDrillSetup(wxCommandEvent& event)
{
}

void FrameMain::OnToolboxEdit(wxCommandEvent& event)
{
	dialogToolbox->Show(true);
	dialogToolbox->Raise();
	TransferDataToWindow();
}

void FrameMain::OnToolboxLoad(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if(wxDir::Exists(settings.lastToolboxDirectory)){
		dialog.SetDirectory(settings.lastToolboxDirectory);
	}else{
		if(wxDir::Exists(settings.lastProjectDirectory)){
			dialog.SetDirectory(settings.lastProjectDirectory);
		}
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(toolbox.LoadToolBox(fileName)){
			settings.lastToolboxDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnToolboxSave(wxCommandEvent &event)
{
	wxFileDialog dialog(this, _("Save toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if(toolbox.fileName.IsOk()){
		dialog.SetFilename(toolbox.fileName.GetFullPath());
	}else{
		if(wxDir::Exists(settings.lastToolboxDirectory)){
			dialog.SetDirectory(settings.lastToolboxDirectory);
		}
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		if(toolbox.SaveToolBox(fileName)){
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnGeneratorSetup(wxCommandEvent& event)
{
	dialogToolpathGenerator->Show();
	dialogToolpathGenerator->Raise();
	TransferDataToWindow();

}

void FrameMain::OnGeneratorStart(wxCommandEvent& event)
{

	project.GenerateToolpaths();

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

void FrameMain::OnGeneratorAutomatic(wxCommandEvent& event)
{
//	project.processToolpath = event.IsChecked();
//	TransferDataToWindow();
}

void FrameMain::OnGeneratorRestart(wxCommandEvent& event)
{
}

void FrameMain::OnGeneratorSaveToolpath(wxCommandEvent& event)
{
	const int runNr = tree->GetFirstSelectedRun();
	if(runNr < 0 || runNr >= project.run.GetCount()) return;

	wxFileDialog dialog(this, _("Save toolpath..."), _T(""), _T(""),
			_("G-Code file (*.nc)|*.nc|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(settings.lastToolpathDirectory)){
		dialog.SetDirectory(settings.lastToolpathDirectory);
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		settings.lastToolpathDirectory = fileName.GetPath();
		ToolPath::Dialect dialect = ToolPath::RS274NGC;
		if(m_menuDialect->IsChecked(ID_DIALECT_FANUCM)) dialect =
				ToolPath::FanucM;
		project.SaveToolpath(fileName, runNr, dialect);
	}
}

void FrameMain::OnChangeLanguage(wxCommandEvent& event)
{
	long lng =
			wxGetSingleChoiceIndex(
					_T(
							"Please choose language:\nChanges will take place after restart!"),
					_T("Language"), WXSIZEOF(langNames), langNames);
	if(lng >= 0) config->Write(_T("Language"), langNames[lng]);
	TransferDataToWindow();
}

void FrameMain::OnActivateStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == stereoOff){
		m_canvas->stereoMode = stereoAnaglyph;
	}else{
		m_canvas->stereoMode = stereoOff;
	}
	m_menuSettings->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	TransferDataToWindow();
}

void FrameMain::OnSetupController(wxCommandEvent& event)
{
	DialogSetup6DOFController temp(this);
	temp.InsertController(control);
	temp.ShowModal();
}

void FrameMain::OnSetupStereo3D(wxCommandEvent& event)
{
	dialogSetupStereo3D->Show(true);
	dialogSetupStereo3D->Raise();
}

void FrameMain::OnSetupMidi(wxCommandEvent& event)
{
	dialogSetupMidi->Show(true);
	dialogSetupMidi->Raise();
}

void FrameMain::OnSetupUnits(wxCommandEvent& event)
{
	DialogSetupUnits * temp = new DialogSetupUnits(this, &settings);
	temp->Show();
	temp->Raise();
}

void FrameMain::OnShowAnimationControl(wxCommandEvent& event)
{
	dialogAnimation->Show(true);
	dialogAnimation->Raise();
	TransferDataToWindow();
}

void FrameMain::OnExtraWindowClose(wxCommandEvent& event)
{
	dialogObjectTransformation->Show(false);
	dialogStockMaterial->Show(false);
	dialogWorkpiece->Show(false);
	dialogPlacement->Show(false);
	dialogRun->Show(false);
	dialogDebugger->Show(false);
	dialogToolbox->Show(false);
	dialogToolpathGenerator->Show(false);
	dialogAnimation->Show(false);
	dialogSetupStereo3D->Show(false);

	TransferDataToWindow();
}

void FrameMain::OnShowLogWindow(wxCommandEvent& event)
{
	logWindow->Show();
	logWindow->GetFrame()->Raise();
	TransferDataToWindow();
}

void FrameMain::OnViewSet(wxCommandEvent& event)
{
	switch(event.GetId()){
	case ID_VIEWFRONT:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotateXYZ(-M_PI_2, 0, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWFRONT"), 1);
		break;
	case ID_VIEWBACK:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotateXYZ(M_PI_2, 0, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWBACK"), 1);
		break;
	case ID_VIEWLEFT:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotateXYZ(0, M_PI_2, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWLEFT"), 1);
		break;
	case ID_VIEWRIGHT:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotateXYZ(0, -M_PI_2, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWRIGHT"), 1);
		break;
	case ID_VIEWTOP:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_statusBar->SetStatusText(_T("ID_VIEWTOP"), 1);
		break;
	case ID_VIEWBOTTOM:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotateXYZ(0, M_PI, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWBOTTOM"), 1);
		break;
	}
	TransferDataToWindow();
}

void FrameMain::OnHelp(wxCommandEvent& event)
{
	m_helpController->DisplayContents();
}

void FrameMain::OnTestGCode(wxCommandEvent& event)
{
	//TODO: When the units change the change is not immediately propagated into the TestGCode dialog.
	DialogTestGCode * dialog = new DialogTestGCode(this, &settings);
	dialog->Show();
	dialog->Raise();
}

void FrameMain::OnAbout(wxCommandEvent& event)
{
	DialogAbout * dialog = new DialogAbout(this);
	dialog->Show();
	dialog->Raise();
}

