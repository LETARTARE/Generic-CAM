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

#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIMainFrame(parent), objectFrame(parent), stockFrame(parent), toolboxFrame(
				parent), animationFrame(parent)
{

	long style = tree->GetWindowStyle() ^ wxTR_NO_LINES;
	tree->SetWindowStyle(style);

	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			true);
	logWindow->Show();

	// Setup configuration
	this->config = config;
	this->locale = locale;

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
	timer.Start(100);

	m_canvas->Connect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);

	selectedTargetPosition = 0;

	// Connect the project to the 3D canvas
	m_canvas->InsertProject(&project);

	TransferDataToWindow();
}

MainFrame::~MainFrame()
{
	// Disconnect events
	m_canvas->Disconnect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL,
			this);

	// Write back the configuration

	// Save the configuration of the 6DOF controller
	control.WriteConfigTo(config);

	// Save the size of the mainframe
	int w, h;
	GetClientSize(&w, &h);
	config->Write(_T("MainFrameWidth"), (long) w);
	config->Write(_T("MainFrameHeight"), (long) h);

	delete config; // config is written back on deletion of object
}

bool MainFrame::TransferDataToWindow(void)
{
	// Populate the treeview
	SetupTree();

	//TODO: Review the stereomode
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
	return true;
}

bool MainFrame::TransferDataFromWindow(void)
{
	m_canvas->stereoMode = m_menuView->IsChecked(wxID_VIEWSTEREO3D);
	return true;
}

void MainFrame::SetupTree(void)
{
//	tree->DeleteAllItems();
//
//	//TreeItemData* tid;
//
//	wxTreeItemId rootId = tree->AddRoot(_T("TreeRoot"));
//
//	wxTreeItemId treeIdProject;
//
//	wxTreeItemId treeIdObject;
//	wxTreeItemId treeIdGeometry;
//	wxTreeItemId treeIdStock;
//	wxTreeItemId treeIdMachine;
//	wxTreeItemId treeIdToolbox;
//	wxTreeItemId treeIdRun;
//	wxTreeItemId treeIdRun2;
//
//	wxTreeItemId treeIdToolpath;
//
//	size_t i, j, k;
//	for(i = 0; i < project.GetCount(); i++){
//		treeIdProject = tree->AppendItem(rootId,
//		_("Project: ") + project[i].name);
//
//		treeIdStock = tree->AppendItem(treeIdProject,
//		_("Stock material: ") + project[i].stock.name);
//
//		for(j = 0; j < project[i].stock.stockMaterials.GetCount(); j++){
//			tree->AppendItem(treeIdStock,
//					project[i].stock.stockMaterials[j].materialName);
//		}
//
//		for(j = 0; j < project[i].objects.GetCount(); j++){
//			treeIdObject = tree->AppendItem(treeIdProject,
//			_("Object: ") + project[i].objects[j].fileName.GetName());
//			for(k = 0; k < project[i].objects[j].geometries.GetCount(); k++){
//				{
//					tree->AppendItem(treeIdObject,
//							project[i].objects[j].geometries[k].objectName);
//				}
//			}
//		}
//
//		treeIdMachine = tree->AppendItem(treeIdProject,
//		_("Machine: ") + project[i].machine.fileName.GetName());
//
//		treeIdToolbox = tree->AppendItem(treeIdProject,
//		_("Toolbox: ") + project[i].toolbox.fileName.GetName());
//		for(j = 0; j < project[i].toolbox.tools.GetCount(); j++){
//			tree->AppendItem(treeIdToolbox,
//					project[i].toolbox.tools[j].toolName);
//		}
//
//		treeIdRun = tree->AppendItem(treeIdProject, _("Run:"));
//		for(j = 0; j < project[i].runs.GetCount(); j++){
//			treeIdRun2 = tree->AppendItem(treeIdRun,
//					project[i].runs[j].runName);
//
//			tree->AppendItem(treeIdRun2, _("Stock material"));
//			tree->AppendItem(treeIdRun2, _("Target"));
//			treeIdToolpath = tree->AppendItem(treeIdRun2, _("Toolpath"));
//		}
//
//	}
//
//	//	for(i = 0; i < doc->geometry.Count(); i++){
//	//		tid = new TreeItemData;
//	//		tid->nr = i;
//	//		tid->dataType = TreeItemData::geometry;
//	//		tree->AppendItem(treeIdGeometry, doc->geometry[i].objectName, -1, -1,
//	//				tid);
//	//	}
//
//	tree->ExpandAll();
}

void MainFrame::OnCreateProject(wxCommandEvent& event)
{
	//	Project temp;
	//	project.Add(temp);
	project.Clear();
	SetupTree();
	this->Refresh();
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
		SetupTree();
	}
	this->Refresh();
}

void MainFrame::LoadProject(wxString fileName)
{
	project.Load(fileName);
	SetupTree();
	this->Refresh();
}

void MainFrame::OnSaveProject(wxCommandEvent& event)
{
	if(!project.fileName.IsOk()) OnSaveProjectAs(event);
	project.Save(project.fileName);
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
	}
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnLoadObject(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open..."), _T(""), _T(""),
			_(
					"All supported files (*.dxf; *.stl; *.gts)|*.dxf;*.stl;*.gts|DXF Files (*.dxf)|*.dxf|Stereolithography files (STL files) (*.stl)|*.stl|GTS files (*.gts)|*.gts|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(lastObjectFileName.IsOk()) dialog.SetFilename(
			lastObjectFileName.GetFullPath());
	if(dialog.ShowModal() == wxID_OK){

		fileName = dialog.GetPath();
		lastObjectFileName = fileName;

		//wxLogMessage(_T("File Extension: ")+fileName.GetExt());

		Object temp;
		if(temp.LoadObject(fileName)){
			project.objects.Add(temp);
		}
		SetupTree();
		this->Refresh();
	}
}

void MainFrame::OnModifyObject(wxCommandEvent& event)
{
	objectFrame.InsertProject(&project);
	objectFrame.Show(true);
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
		SetupTree();
		this->Refresh();
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
	this->Refresh();
}

void MainFrame::OnEditToolbox(wxCommandEvent& event)
{
	toolboxFrame.SetController(control);
	toolboxFrame.InsertProject(&(project));
	toolboxFrame.Show(true);
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
	stockFrame.InsertProject(&(project));
	stockFrame.Show(true);
}
void MainFrame::OnGenerateToolpath(wxCommandEvent& event)
{
	project.GenerateToolPath();
	this->Refresh();
}
void MainFrame::OnRecollectToolpath(wxCommandEvent& event)
{
	project.CollectToolPath();
	this->Refresh();
}

void MainFrame::OnCleanToolpath(wxCommandEvent& event)
{
	//	project.CleanToolPath();
	this->Refresh();
}

void MainFrame::OnFlipRun(wxCommandEvent& event)
{
	project.FlipRun();
	this->Refresh();
}
void MainFrame::OnPrepareMachinebed(wxCommandEvent& event)
{
	project.SetupMachineBed();
	project.CollectToolPath();
	this->Refresh();
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
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
	this->Refresh();
}

void MainFrame::OnSetupUnits(wxCommandEvent& event)
{
	DialogSetupUnits temp(this);
	temp.ShowModal();
}

void MainFrame::OnShowAnimationControl(wxCommandEvent& event)
{
	animationFrame.InsertProject(&project);
	animationFrame.Show(true);
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
}
void MainFrame::OnEndLabelEdit(wxTreeEvent& event)
{
}
void MainFrame::OnActivateRightClickMenu(wxTreeEvent& event)
{
}
void MainFrame::OnSelectionChanged(wxTreeEvent& event)
{
}

void MainFrame::OnUpdateVisibility(wxCommandEvent& event)
{
	project.displayMachine = m_toolBar->GetToolState(wxID_DISPLAYMACHINE);
	project.displayGeometry = m_toolBar->GetToolState(wxID_DISPLAYMATERIAL);

	this->Refresh();

	event.Skip();
}

