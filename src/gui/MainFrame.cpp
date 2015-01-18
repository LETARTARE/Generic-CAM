///////////////////////////////////////////////////////////////////////////////
// Name               : MainFrame.cpp
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

#include "MainFrame.h"

#include <unistd.h>

#include "DialogAbout.h"
#include "DialogSetup6DOFController.h"
#include "DialogSetupUnits.h"

#include "../languages.h"
#include "../command/CommandProjectRename.h"
#include "../command/CommandObjectLoad.h"
#include "../command/CommandObjectDelete.h"
#include "../command/CommandObjectRename.h"
#include "../command/CommandObjectTransform.h"
#include "../command/CommandWorkpieceRename.h"
#include "../command/CommandWorkpieceRemove.h"
#include "../command/CommandRunAdd.h"
#include "../command/CommandRunRename.h"
#include "../command/CommandRunRemove.h"

#include "IDs.h"
#include "wx/icon.h"
#ifndef __WIN32__
#include "../icon/logo32.xpm"
#include "../icon/logo48.xpm"
#include "../icon/logo64.xpm"
#include "../icon/logo128.xpm"
#endif

#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>
#include <wx/dir.h>

MainFrame::MainFrame(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIMainFrame(parent)
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

	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			true);

// Setup configuration
	this->config = config;
	this->locale = locale;

	// Read variables
	config->Read(_T("LastProjectDirectory"), &lastProjectDirectory);
	config->Read(_T("LastObjectDirectory"), &lastObjectDirectory);
	config->Read(_T("LastMachineDirectory"), &lastMachineDirectory);
	config->Read(_T("LastStockDirectory"), &lastStockDirectory);
	config->Read(_T("LastToolboxDirectory"), &lastToolboxDirectory);

	// Set the window size according to the config file
	int w, h;
	w = config->Read(_T("MainFrameWidth"), 600);
	h = config->Read(_T("MainFrameHeight"), 400);
	SetClientSize(w, h);

	control.GetConfigFrom(config);
	m_canvas->SetController(control);

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL,
			this);
	timer.Start(1000); // ms

	this->Connect(ID_SELECTOBJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MainFrame::ObjectSelect));

	this->Connect(ID_UPDATE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MainFrame::Update));

	m_canvas->Connect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);

	selectedTargetPosition = 0;

	commandProcessor.SetEditMenu(m_menuEdit);
	commandProcessor.Initialize();
	commandProcessor.MarkAsSaved();

	// Connect the project to the 3D canvas
	m_canvas->InsertProject(&project);

	dialogObjectModification = new DialogObjectTransformation(this, &project,
			&commandProcessor, &settings);
	dialogStockOverview = new DialogStockMaterial(this, &project,
			&commandProcessor, &settings);
	dialogStockSetup = new DialogWorkpiece(this, &project, &commandProcessor);
	dialogRun = new DialogRun(this, &project, &commandProcessor, &settings);
	dialogDebugger = new DialogMachineDebugger(this, &project, &settings);
	dialogToolbox = new DialogToolbox(this, &project, &commandProcessor,
			&settings);
	dialogAnimation = new DialogAnimation(this, &project);

	tree = new TreeSetup(m_tree, &project);

	TransferDataToWindow();
}

MainFrame::~MainFrame()
{
	// Disconnect events
	m_canvas->Disconnect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL,
			this);
	this->Disconnect(ID_SELECTOBJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MainFrame::ObjectSelect));
	this->Disconnect(ID_UPDATE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MainFrame::Update));

	// Write back the configuration
	config->Write(_T("LastProjectDirectory"), lastProjectDirectory);
	config->Write(_T("LastObjectDirectory"), lastObjectDirectory);
	config->Write(_T("LastMachineDirectory"), lastMachineDirectory);
	config->Write(_T("LastStockDirectory"), lastStockDirectory);
	config->Write(_T("LastToolboxDirectory"), lastToolboxDirectory);

	// Save the size of the mainframe
	int w, h;
	GetClientSize(&w, &h);
	config->Write(_T("MainFrameWidth"), (long) w);
	config->Write(_T("MainFrameHeight"), (long) h);

	// Save the configuration of the 6DOF controller
	control.WriteConfigTo(config);

	delete config; // config is written back on deletion of object
}

bool MainFrame::TransferDataToWindow(void)
{
	// Populate the treeview
	tree->Update();

	//TODO: Review the stereomode
	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
	m_toolBar->ToggleTool(ID_DISPLAYMACHINE, project.displayMachine);
	m_toolBar->ToggleTool(ID_DISPLAYMATERIAL, project.displayGeometry);
	m_menuView->Check(ID_LOGSHOW, logWindow->GetFrame()->IsShown());

	wxString temp = _T("Generic CAM - ");
	if(commandProcessor.IsDirty()) temp += _T("* ");
	temp += project.name;
	this->SetTitle(temp);

	dialogObjectModification->TransferDataToWindow();
	dialogStockOverview->TransferDataToWindow();
	dialogStockSetup->TransferDataToWindow();
	dialogRun->TransferDataToWindow();

	Refresh();
	return true;
}

bool MainFrame::TransferDataFromWindow(void)
{
	m_canvas->stereoMode = m_menuView->IsChecked(ID_VIEWSTEREO3D);
	project.displayMachine = m_toolBar->GetToolState(ID_DISPLAYMACHINE);
	project.displayGeometry = m_toolBar->GetToolState(ID_DISPLAYMATERIAL);

	return true;
}

void MainFrame::Update(wxCommandEvent& event)
{
	TransferDataToWindow();
}

size_t MainFrame::GetFreeSystemMemory()
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
	//TODO: Change this to available memory.
	return status.ullTotalPhys;
#endif
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
//	t += 0.100;
//	simulator.Step(t);
//	simulator.machine.Assemble();
//	this->Refresh();

	wxString temp;
	temp = wxString::Format(_T("Free RAM: %lu MB"),
			GetFreeSystemMemory() / 1024 / 1024);
	m_statusBar->SetStatusText(temp, 1);
}

void MainFrame::OnKeyDown(wxKeyEvent& event)
{
	int k = event.GetKeyCode();

	if(k == WXK_ESCAPE){
		this->Close();
	}

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

void MainFrame::On3DSelect(wxMouseEvent& event)
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

void MainFrame::OnBeginLabelEdit(wxTreeEvent& event)
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

void MainFrame::OnEndLabelEdit(wxTreeEvent& event)
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

void MainFrame::OnActivateRightClickMenu(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	wxMenu menu(_T(""));

	if(data->dataType == itemProject){
		menu.Append(ID_PROJECTRENAME, wxT("&Rename Project"));
		menu.AppendSeparator();
		menu.Append(wxID_OPEN, wxT("&Load Project"));
		menu.Append(wxID_SAVE, wxT("&Save Project"));
		menu.Append(wxID_SAVEAS, wxT("&Load Project As ..."));
	}

	if(data->dataType == itemGroupObject){
		menu.Append(ID_OBJECTLOAD, wxT("&Load Object"));
		menu.Append(ID_OBJECTMODIFY, wxT("&Show Object Dialog"));
	}

	if(data->dataType == itemObject){
		menu.Append(ID_OBJECTMODIFY, wxT("&Modify Object"));
		menu.Append(ID_OBJECTFLIPNORMALS, wxT("&Flip Normals"));
		menu.Append(ID_OBJECTRENAME, wxT("&Rename Object"));
		menu.Append(ID_OBJECTDELETE, wxT("&Delete Object"));
		menu.Append(ID_OBJECTLOAD, wxT("&Load Object"));
	}

	if(data->dataType == itemGroupWorkpiece){
		menu.Append(ID_STOCKORGANIZE, wxT("&Organize Stock"));
		menu.Append(ID_WORKPIECEADD, wxT("&Add Workpiece"));
		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
	}
	if(data->dataType == itemWorkpiece){
		menu.Append(ID_WORKPIECEADD, wxT("&Add Workpiece"));
		menu.Append(ID_WORKPIECEDELETE, wxT("&Delete Workpiece"));
		menu.Append(ID_WORKPIECEDELETEUNUSED, wxT("Delete &unused Workpieces"));
	}

	if(data->dataType == itemGroupRun){
		menu.Append(ID_RUNADD, wxT("&Add Run"));
		menu.Append(ID_RUNEDIT, wxT("&Setup Run"));
	}

	if(data->dataType == itemRun){
		menu.Append(ID_RUNADD, wxT("&Add Run"));
		menu.Append(ID_RUNEDIT, wxT("&Setup Run"));
		menu.Append(ID_RUNDELETE, wxT("&Delete Run"));
	}

	if(menu.GetMenuItemCount() > 0) PopupMenu(&menu, event.GetPoint());
}

void MainFrame::OnActivate(wxTreeEvent& event)
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
	if(data->dataType == itemGroupRun){
		wxCommandEvent menuEvent(wxEVT_COMMAND_MENU_SELECTED, ID_RUNEDIT);
		ProcessEvent(menuEvent);
	}
}

void MainFrame::ObjectSelect(wxCommandEvent& event)
{
	size_t id = event.GetInt();
	size_t n;
	for(n = 0; n < project.objects.GetCount(); n++)
		project.objects[n].selected = (n == id);

	tree->UpdateSelection();
	Refresh();
}

void MainFrame::OnSelectionChanged(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	tree->UpdateVariables();

	if(data->dataType == itemObject){
		dialogObjectModification->TransferDataToWindow();
	}

}

void MainFrame::OnSelectionChanging(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	if(data->dataType == itemProject) return;
	if(data->dataType == itemObject) return;
	if(data->dataType == itemWorkpiece) return;
	if(data->dataType == itemRun) return;

	event.Veto();
}

void MainFrame::OnToolbarButton(wxCommandEvent& event)
{
	TransferDataFromWindow();
	TransferDataToWindow();
}

void MainFrame::OnProjectNew(wxCommandEvent& event)
{
//	Project temp;
//	project.Add(temp);
	project.Clear();
	commandProcessor.ClearCommands();
	commandProcessor.MarkAsSaved();
	commandProcessor.SetMenuStrings();
	TransferDataToWindow();
}

void MainFrame::OnProjectRename(wxCommandEvent& event)
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

void MainFrame::OnProjectLoad(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open Project..."), _T(""), _T(""),
			_("Generic CAM Project (*.prj; *.xml)|*.prj;*.xml|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		project.Load(fileName);
		TransferDataToWindow();
	}
}

void MainFrame::LoadProject(wxString fileName)
{
	project.Load(fileName);
	commandProcessor.ClearCommands();
	commandProcessor.MarkAsSaved();
	TransferDataToWindow();
}

void MainFrame::OnProjectSave(wxCommandEvent& event)
{
	if(!project.fileName.IsOk()) OnProjectSaveAs(event);
	project.Save(project.fileName);
	commandProcessor.MarkAsSaved();
	TransferDataToWindow();
}

void MainFrame::OnProjectSaveAs(wxCommandEvent &event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Save Project As..."), _T(""), _T(""),
			_("Generic CAM Project (*.prj; *.xml)|*.prj;*.xml|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(!project.fileName.IsOk()) dialog.SetFilename(
			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		project.Save(fileName);
		commandProcessor.MarkAsSaved();
		TransferDataToWindow();
	}
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnUndo(wxCommandEvent& event)
{
	commandProcessor.Undo();
	TransferDataToWindow();
}

void MainFrame::OnRedo(wxCommandEvent& event)
{
	commandProcessor.Redo();
	TransferDataToWindow();
}

void MainFrame::OnObjectLoad(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open..."), _T(""), _T(""),
			_(
					"All supported files (*.dxf; *.stl; *.gts)|*.dxf;*.stl;*.gts|DXF Files (*.dxf)|*.dxf|Stereolithography files (STL files) (*.stl)|*.stl|GTS files (*.gts)|*.gts|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

	if(wxDir::Exists(lastObjectDirectory)){
		dialog.SetDirectory(lastObjectDirectory);
	}else{
		if(wxDir::Exists(lastProjectDirectory)){
			dialog.SetDirectory(lastProjectDirectory);
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
			if(n == 0) lastObjectDirectory = fileName.GetPath();
		}
		TransferDataToWindow();
	}
}

void MainFrame::OnObjectModify(wxCommandEvent& event)
{
	dialogObjectModification->Show(true);
	TransferDataToWindow();
}

void MainFrame::OnObjectRename(wxCommandEvent& event)
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

void MainFrame::OnObjectDelete(wxCommandEvent& event)
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

void MainFrame::OnObjectFlipNormals(wxCommandEvent& event)
{
	size_t n;
	for(n = 0; n < project.objects.GetCount(); n++){
		if(project.objects[n].selected){
			AffineTransformMatrix matrix = project.objects[n].matrix;
			CommandObjectTransform * command = new CommandObjectTransform(
					project.objects[n].name + _(": Flipped normal vectors"),
					&project, n, false, false, false, true, matrix);
			commandProcessor.Submit(command);
		}
	}
	TransferDataToWindow();
}

void MainFrame::OnStockEdit(wxCommandEvent& event)
{
	dialogStockOverview->Show(true);
	dialogStockOverview->Initialize();
	TransferDataToWindow();
}

void MainFrame::OnWorkpieceAdd(wxCommandEvent& event)
{
	dialogStockSetup->Show(true);
	TransferDataToWindow();
}

void MainFrame::OnWorkpieceDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tree->UpdateVariables();
	size_t i;
	for(i = project.workpieces.GetCount(); i > 0; i--){
		if(project.workpieces[i - 1].selected){
			commandProcessor.Submit(
					new CommandWorkpieceRemove(
							_("Remove workpiece ")
									+ project.workpieces[i - 1].name, &project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void MainFrame::OnWorkpieceDeleteUnused(wxCommandEvent& event)
{
	TransferDataFromWindow();
	size_t i;
	for(i = project.workpieces.GetCount(); i > 0; i--){
		if(project.workpieces[i - 1].placements.GetCount() == 0){
			commandProcessor.Submit(
					new CommandWorkpieceRemove(
							_("Remove workpiece ")
									+ project.workpieces[i - 1].name, &project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void MainFrame::OnRunAdd(wxCommandEvent& event)
{
	commandProcessor.Submit(
			new CommandRunAdd(_("Add run"), &project, _T("Run")));
	TransferDataToWindow();
}

void MainFrame::OnRunEdit(wxCommandEvent& event)
{
	dialogRun->Show(true);
	TransferDataToWindow();
}

void MainFrame::OnRunDelete(wxCommandEvent& event)
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
void MainFrame::OnMachineLoad(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"Machine descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
//		project.machine.Load(dialog.GetPath());
		project.Assemble();

		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();
//		if(!project.machine.textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.

//			printf(project.machine.textOut.ToAscii());
//			ErrorFrame* error = new ErrorFrame(this);
//			error->SetText(project.machine.textOut);
//			error->Show();
	}
	TransferDataToWindow();
//}
}

void MainFrame::OnMachineReload(wxCommandEvent& event)
{

//	project.machine.ReLoad();
	project.Assemble();

//	if(!simulator.machine.fileName.IsOk()) return;
//	simulator.machine.ReLoad();
//	if(!project.machine.textOut.IsEmpty()){
//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
//TODO: Don't open a new errorframe, if the old one is not closed.
//		printf(project.machine.textOut.ToAscii());
//		ErrorFrame* error = new ErrorFrame(this);
//		error->SetText(project.machine.textOut);
//		error->Show();
//	}
//	t = 0;
	TransferDataToWindow();
}

void MainFrame::OnMachineDebugger(wxCommandEvent& event)
{
	dialogDebugger->Show(true);
}

void MainFrame::OnToolboxEdit(wxCommandEvent& event)
{
	dialogToolbox->Show(true);
	TransferDataToWindow();
}

void MainFrame::OnToolboxLoad(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxFileName fileName;
//	if(dialog.ShowModal() == wxID_OK){
//		fileName.Assign(dialog.GetPath());
//		if(!simulator.toolbox.LoadToolbox(fileName)){
//			wxLogError(_T("OnLoadToolbox: Opening of the toolbox failed!"));
//		}

//ctrlTextEdit->SetValue(temp);
//fname.Assign(dialog.GetPath());
//ctrlTextEdit->SetModified(false);
//SetWindowTitle();

//	}
}

void MainFrame::OnToolboxSave(wxCommandEvent &event)
{

//TODO: Build something like this in this snippet.
//	wxFileDialog
//			dialog(
//					this,
//					_("Save as..."),
//					fname.GetPath(),
//					fname.GetFullName(),
//					_("LUA Files  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
//					wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
//
//	if(dialog.ShowModal() == wxID_OK){
//		fname.Assign(dialog.GetPath());
//		SetWindowTitle();
//		DoSave();
//	}

	wxFileDialog dialog(this, _("Save toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	wxFileName fileName;
	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();

		//		if(!simulator.toolbox.LoadToolbox(fileName)){
		//			wxLogError(_T("OnLoadToolbox: Opening of the toolbox failed!"));
		//		}

		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}

void MainFrame::OnAddGenerator(wxCommandEvent& event)
{
}

void MainFrame::OnGenerateToolpath(wxCommandEvent& event)
{
	project.GenerateToolPath();
	TransferDataToWindow();
}
void MainFrame::OnRecollectToolpath(wxCommandEvent& event)
{
	project.CollectToolPath();
	TransferDataToWindow();
}

void MainFrame::OnCleanToolpath(wxCommandEvent& event)
{
//	project.CleanToolPath();
	TransferDataToWindow();
}

void MainFrame::OnFlipRun(wxCommandEvent& event)
{
	project.FlipRun();
	TransferDataToWindow();
}
void MainFrame::OnPrepareMachinebed(wxCommandEvent& event)
{
	project.SetupMachineBed();
	project.CollectToolPath();
	TransferDataToWindow();
}

void MainFrame::OnLoadGCodes(wxCommandEvent &event)
{
	wxFileDialog dialog(this, _("Open G-Code file..."), _T(""), _T(""),
			_(
					"G-Code File (*.tap *.cnc *.nc *.ngc *.txt)|*.tap;*.cnc;*.nc;*.ngc;*.txt|Text files (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

//	if(dialog.ShowModal() == wxID_OK){
//		simulator.ReadGCodeFile(dialog.GetPath());
//	}
	TransferDataToWindow();
}

void MainFrame::OnSaveGCodes(wxCommandEvent &event)
{
	wxFileDialog dialog(this, _("Save G-Code file..."), _T(""), _T(""),
			_(
					"G-Code File (*.tap *.cnc *.nc *.ngc *.txt)|*.tap;*.cnc;*.nc;*.ngc;*.txt|Text files (*.txt)|*.txt|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if(dialog.ShowModal() == wxID_OK){

		wxFileName fname;
		fname = dialog.GetPath();

		wxTextFile f;
		if(fname.FileExists()){
			f.Open(fname.GetFullPath());
			f.Clear();
		}else
			f.Create(fname.GetFullPath());

		project.run[0].WriteToFile(f);
		f.Write();
		f.Close();
		TransferDataToWindow();
	}
}

void MainFrame::OnChangeLanguage(wxCommandEvent& event)
{
	long lng =
			wxGetSingleChoiceIndex(
					_T(
							"Please choose language:\nChanges will take place after restart!"),
					_T("Language"), WXSIZEOF(langNames), langNames);
	config->Write(_T("Language"), langNames[lng]);
	TransferDataToWindow();
}

void MainFrame::OnSetupController(wxCommandEvent& event)
{
	DialogSetup6DOFController temp(this);
	temp.InsertController(control);
	temp.ShowModal();
}

void MainFrame::OnChangeStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
	TransferDataToWindow();
}

void MainFrame::OnSetupUnits(wxCommandEvent& event)
{
	DialogSetupUnits * temp = new DialogSetupUnits(this, &settings);
	temp->Show();
}

void MainFrame::OnShowAnimationControl(wxCommandEvent& event)
{
	dialogAnimation->Show(true);
	TransferDataToWindow();
}

void MainFrame::OnExtraWindowClose(wxCommandEvent& event)
{
	dialogObjectModification->Show(false);
	dialogStockOverview->Show(false);
	dialogStockSetup->Show(false);
	dialogRun->Show(false);
	dialogDebugger->Show(false);
	dialogToolbox->Show(false);
	dialogAnimation->Show(false);
	TransferDataToWindow();
}

void MainFrame::OnShowLogWindow(wxCommandEvent& event)
{
	logWindow->Show(!(logWindow->GetFrame()->IsShown()));
	TransferDataToWindow();
}

void MainFrame::OnViewSet(wxCommandEvent& event)
{
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	DialogAbout * dialog = new DialogAbout(this);
	dialog->Show();
}

