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

#include "DialogAbout.h"
#include "DialogSetup6DOFController.h"
#include "DialogSetupUnits.h"

#include "../languages.h"
#include "../command/commandObjectLoad.h"
#include "../command/commandObjectTransform.h"
#include "../command/commandObjectRename.h"
#include "../command/commandObjectDelete.h"
#include "../command/commandProjectRename.h"

#include "IDs.h"

#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>
#include <wx/dir.h>

MainFrame::MainFrame(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIMainFrame(parent)
{

	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			true);
	logWindow->Show();

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
	timer.Start(100); // ms

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

	objectFrame = new DialogObjectTransformation(this, &project,
			&commandProcessor, &settings);
	stockFrame = new DialogStockMaterial(this);
	toolboxFrame = new DialogToolbox(this);
	animationFrame = new DialogAnimation(this);
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

	wxString temp = _T("Generic CAM - ");
	if(commandProcessor.IsDirty()) temp += _T("* ");
	temp += project.name;
	this->SetTitle(temp);

	objectFrame->TransferDataToWindow();

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

void MainFrame::OnCreateProject(wxCommandEvent& event)
{
//	Project temp;
//	project.Add(temp);
	project.Clear();
	commandProcessor.ClearCommands();
	commandProcessor.MarkAsSaved();

	TransferDataToWindow();
}

void MainFrame::OnProjectRename(wxCommandEvent& event)
{
	wxTextEntryDialog dialog(this, _("Enter new project name:"),
			_T("Rename Project"), project.name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project.name) return;

		commandProjectRename * command = new commandProjectRename(
		_("Project renamed to ") + dialog.GetValue(), &project,
				dialog.GetValue());
		commandProcessor.Submit(command);
		TransferDataToWindow();
	}
}

void MainFrame::OnLoadProject(wxCommandEvent& event)
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

void MainFrame::OnSaveProject(wxCommandEvent& event)
{
	if(!project.fileName.IsOk()) OnSaveProjectAs(event);
	project.Save(project.fileName);
	commandProcessor.MarkAsSaved();
	TransferDataToWindow();
}

void MainFrame::OnSaveProjectAs(wxCommandEvent &event)
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
					new commandObjectLoad(
							(_("Load Object: ") + fileName.GetName()),
							&project, paths[n]));
			if(n == 0) lastObjectDirectory = fileName.GetPath();
		}
		TransferDataToWindow();
	}
}

void MainFrame::OnObjectModify(wxCommandEvent& event)
{
	objectFrame->Show(true);
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
				new commandObjectRename(
				_("Object renamed to ") + dialog.GetValue(), &project, i,
						dialog.GetValue()));
		TransferDataToWindow();
	}
}

void MainFrame::OnObjectDelete(wxCommandEvent& event)
{
	TransferDataFromWindow();
	int i = tree->GetFirstSelectedObject();
	if(i < 0 || i >= project.objects.GetCount()) return;
	commandProcessor.Submit(
			new commandObjectDelete(
			_("Object ") + project.objects[i].name + _(" deleted."),
					&project, i));
	TransferDataToWindow();
}

void MainFrame::OnLoadMachine(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"Machine descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		project.machine.Load(dialog.GetPath());
		project.Assemble();

		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();
		if(!project.machine.textOut.IsEmpty()){
			//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
			//TODO: Don't open a new errorframe, if the old one is not closed.

			printf(project.machine.textOut.ToAscii());
//			ErrorFrame* error = new ErrorFrame(this);
//			error->SetText(project.machine.textOut);
//			error->Show();
		}
		TransferDataToWindow();
	}
}

void MainFrame::OnReloadMachine(wxCommandEvent& event)
{

	project.machine.ReLoad();
	project.Assemble();

//	if(!simulator.machine.fileName.IsOk()) return;
//	simulator.machine.ReLoad();
	if(!project.machine.textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.
		printf(project.machine.textOut.ToAscii());
//		ErrorFrame* error = new ErrorFrame(this);
//		error->SetText(project.machine.textOut);
//		error->Show();
	}
//	t = 0;
	TransferDataToWindow();
}

void MainFrame::OnEditToolbox(wxCommandEvent& event)
{
	toolboxFrame->SetController(control);
	toolboxFrame->InsertProject(&(project));
	toolboxFrame->Show(true);
}

void MainFrame::OnLoadToolbox(wxCommandEvent& event)
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

void MainFrame::OnSaveToolbox(wxCommandEvent &event)
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

void MainFrame::OnEditStock(wxCommandEvent& event)
{
	stockFrame->InsertProject(&(project));
	stockFrame->Show(true);
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

		project.runs[0].WriteToFile(f);
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
	animationFrame->InsertProject(&project);
	animationFrame->Show(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	DialogAbout * dialog = new DialogAbout(this);
	dialog->Show();
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
//	t += 0.100;
//	simulator.Step(t);
//	simulator.machine.Assemble();
//this->Refresh();
}

void MainFrame::OnKeyDown(wxKeyEvent& event)
{
	int k = event.GetKeyCode();

	if(k == WXK_ESCAPE){
		this->Close();
	}

// Select placement
	if(k == WXK_NUMPAD_ADD
			&& selectedTargetPosition
					< project.runs[0].placements.GetCount() - 1) selectedTargetPosition++;
	if(k == WXK_NUMPAD_SUBTRACT && selectedTargetPosition > 0) selectedTargetPosition--;

//	if(selectedTargetPosition
//			< project.runs[0].placements.GetCount()
//			&& project.runs[0].placements[selectedTargetPosition].isMovable){
//
//		if(k == WXK_UP) project.runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.0, 0.001, 0.0);
//		if(k == WXK_DOWN) project.runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.0, -0.001, 0.0);
//		if(k == WXK_RIGHT) project.runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				0.001, 0.0, 0.0);
//		if(k == WXK_LEFT) project.runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
//				-0.001, 0.0, 0.0);
//
//		if(k == WXK_PAGEUP){
//			AffineTransformMatrix temp;
//			temp = AffineTransformMatrix::RotateXYZ(0.0, 0.0, M_PI / 16);
//			project.runs[0].placements[selectedTargetPosition].matrix =
//					project.runs[0].placements[selectedTargetPosition].matrix
//							* temp;
//		}
//		if(k == WXK_PAGEDOWN){
//			AffineTransformMatrix temp;
//			temp = AffineTransformMatrix::RotateXYZ(0.0, 0.0, -M_PI / 16);
//			project.runs[0].placements[selectedTargetPosition].matrix =
//					project.runs[0].placements[selectedTargetPosition].matrix
//							* temp;
//		}
//
//		m_statusBar->SetStatusText(_T("Dummy text..."));
//
//		this->Refresh();
//	}

	event.Skip();
}

void MainFrame::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);

	if(data->dataType == itemProject) return;
	if(data->dataType == itemObject) return;

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
				new commandProjectRename(_("Project renamed to ") + newName,
						&project, newName));
		TransferDataToWindow();
		return;
	};

	if(data->dataType == itemObject){
		if(newName == project.objects[data->nr].name) return;
		commandProcessor.Submit(
				new commandObjectRename(_("Object renamed to ") + newName,
						&project, data->nr, newName));
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

	if(data->dataType == itemObject){
		tree->UpdateVariables();
		objectFrame->TransferDataToWindow();
	}
}

void MainFrame::OnObjectFlipNormals(wxCommandEvent& event)
{
	size_t n;
	for(n = 0; n < project.objects.GetCount(); n++){
		if(project.objects[n].selected){
			AffineTransformMatrix matrix = project.objects[n].matrix;
			commandObjectTransform * command = new commandObjectTransform(
					project.objects[n].name + _(": Flipped normal vectors"),
					&project, n, false, false, false, true, matrix);
			commandProcessor.Submit(command);
		}
	}
	TransferDataToWindow();
}

void MainFrame::OnToolbarButton(wxCommandEvent& event)
{
	TransferDataFromWindow();
	TransferDataToWindow();
}
