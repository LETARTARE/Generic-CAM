///////////////////////////////////////////////////////////////////////////////
// Name               : MainFrame.cpp
// Purpose            : The main window.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

#include "AboutDialog.h"
#include "Control6DOFDialog.h"
#include "UnitDialog.h"
#include "TargetDialog.h"

#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{


	//	wxBoxSizer* bSizer1;
	//		bSizer1 = new wxBoxSizer( wxVERTICAL );
	//
	//		m_canvas = new MachineCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//		bSizer1->Add( m_canvas, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );


	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			true);
	logWindow->Show();


	// Setup configuration
	config = new wxConfig(_T("GenericCAM"));
	control.GetConfigFrom(config);

	m_canvas->SetController(control);

	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL,
			this);

	timer.Start(100);

	m_canvas->Connect(wxID_ANY, wxEVT_KEY_DOWN,
			wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);

	selectedTargetPosition = 0;

	Project *temp = new Project;
	project.Add(temp);
	activeProject = 0;


	//	m_canvas->InsertGeometry(&(project[activeProject].geometry));
	//	m_canvas->InsertMachine(&(project[activeProject].machine));
	m_canvas->InsertProject(&(project[activeProject]));

	SetupTree();

	stockFrame = new StockFrame(this);

}

MainFrame::~MainFrame()
{
	control.WriteConfigTo(config);
	delete config; // config is written back to file (automagically)
}

void MainFrame::OnCreateProject(wxCommandEvent& event)
{
	//	Project temp;
	//	project.Add(temp);
	project[0].ClearProject();
	SetupTree();
	this->Refresh();

}
void MainFrame::OnLoadProject(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open Project..."), _T(""), _T(""), _(
			"Generic CAM Project (*.prj)|*.prj|All Files|*.*"), wxFD_OPEN
			| wxFD_FILE_MUST_EXIST);

	if(lastObjectFileName.IsOk()) dialog.SetFilename(
			lastObjectFileName.GetFullPath());
	if(dialog.ShowModal() == wxID_OK){

		fileName = dialog.GetPath();
		project[activeProject].Load(fileName);
	}
	SetupTree();
	this->Refresh();

}

void MainFrame::LoadProject(wxString fileName)
{
	wxFileName file;
	file = fileName;
	project[activeProject].Load(file);
	project[activeProject].GenerateTargets();
	project[activeProject].GenerateToolPath();
	SetupTree();
	this->Refresh();
}

void MainFrame::OnSaveProject(wxCommandEvent& event)
{
	if(!project[activeProject].fileName.IsOk()) OnSaveProjectAs(event);

	wxFileName fileName;
	wxFileDialog dialog(this, _("Save Project..."), _T(""), _T(""), _(
			"Generic CAM Project (*.prj)|*.prj|All Files|*.*"), wxFD_SAVE
			| wxFD_OVERWRITE_PROMPT);
	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		project[activeProject].Save(fileName);

	}
}
void MainFrame::OnSaveProjectAs(wxCommandEvent &event)
{
	wxFileName fileName;
	wxFileDialog dialog(this, _("Save Project As..."), _T(""), _T(""), _(
			"Generic CAM Project (*.prj)|*.prj|All Files|*.*"), wxFD_SAVE
			| wxFD_OVERWRITE_PROMPT);
	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		project[activeProject].Save(fileName);
	}
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnLoadObject(wxCommandEvent& event)
{
	wxFileName fileName;
	wxFileDialog
			dialog(
					this,
					_("Open..."),
					_T(""),
					_T(""),
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
			project[activeProject].objects.Add(temp);
		}
		SetupTree();
		this->Refresh();
	}
}

void MainFrame::OnModifyObject(wxCommandEvent& event)
{
	objectFrame = new ObjectFrame(this);
	objectFrame->InsertProject(&(project[activeProject]));
	objectFrame->Show(true);
}

void MainFrame::OnGenerateTargets(wxCommandEvent& event)
{
	TargetDialog temp(this);
	temp.InsertProject(&(project[activeProject]));
	temp.ShowModal();
}

void MainFrame::OnLoadMachine(wxCommandEvent& event)
{
	wxFileDialog
			dialog(
					this,
					_("Open machine description..."),
					_T(""),
					_T(""),
					_(
							"Machine descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		project[activeProject].machine.Load(dialog.GetPath());
		project[activeProject].Assemble();


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();
		if(!project[activeProject].machine.textOut.IsEmpty()){
			//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
			//TODO: Don't open a new errorframe, if the old one is not closed.
			ErrorFrame* error = new ErrorFrame(this);
			error->SetText(project[activeProject].machine.textOut);
			error->Show();
		}
		SetupTree();
		this->Refresh();
	}
}

void MainFrame::OnReloadMachine(wxCommandEvent& event)
{

	project[activeProject].machine.ReLoad();
	project[activeProject].Assemble();


	//	if(!simulator.machine.fileName.IsOk()) return;
	//	simulator.machine.ReLoad();
	if(!project[activeProject].machine.textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.
		ErrorFrame* error = new ErrorFrame(this);
		error->SetText(project[activeProject].machine.textOut);
		error->Show();
	}
	//	t = 0;
	this->Refresh();
}

void MainFrame::OnEditToolbox(wxCommandEvent& event)
{
	toolboxFrame = new ToolboxFrame(this);

	toolboxFrame->SetController(control);
	toolboxFrame->InsertProject(&(project[activeProject]));
	toolboxFrame->Show(true);
}

void MainFrame::OnLoadToolbox(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""), _(
			"Toolbox (*.xml)|*.xml|All files|*.*"), wxFD_OPEN
			| wxFD_FILE_MUST_EXIST);
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


	wxFileDialog dialog(this, _("Save toolbox..."), _T(""), _T(""), _(
			"Toolbox (*.xml)|*.xml|All files|*.*"), wxFD_SAVE
			| wxFD_OVERWRITE_PROMPT);
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
	stockFrame->InsertProject(&(project[activeProject]));
	stockFrame->Show(true);
}
void MainFrame::OnGenerateToolpath(wxCommandEvent& event)
{
	project[activeProject].GenerateToolPath();
	this->Refresh();
}
void MainFrame::OnFlipRun(wxCommandEvent& event)
{
	project[activeProject].FlipRun();
	this->Refresh();
}
void MainFrame::OnPrepareMachinebed(wxCommandEvent& event)
{
	project[activeProject].SetupMachineBed();
	project[activeProject].CollectToolPath();
	this->Refresh();
}

void MainFrame::OnLoadGCodes(wxCommandEvent &event)
{
	wxFileDialog
			dialog(
					this,
					_("Open G-Code file..."),
					_T(""),
					_T(""),
					_(
							"G-Code File (*.tap *.cnc *.nc *.ncd *.txt)|*.tap;*.cnc;*.nc;*.ncd;*.txt|Text files (*.txt)|*.txt|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);


	//	if(dialog.ShowModal() == wxID_OK){
	//		simulator.ReadGCodeFile(dialog.GetPath());
	//	}
}

void MainFrame::OnSaveGCodes(wxCommandEvent &event)
{
	wxFileDialog
			dialog(
					this,
					_("Save G-Code file..."),
					_T(""),
					_T(""),
					_(
							"G-Code File (*.tap *.cnc *.nc *.ncd *.txt)|*.tap;*.cnc;*.nc;*.ncd;*.txt|Text files (*.txt)|*.txt|All files|*.*"),
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

		project[activeProject].runs[0].WriteToFile(f);
		f.Write();
		f.Close();
	}
}

void MainFrame::OnSetupController(wxCommandEvent& event)
{
	Control6DOFDialog temp(this);
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
	UnitDialog temp(this);
	temp.ShowModal();
}

void MainFrame::OnShowAnimationControl(wxCommandEvent& event)
{
	animationFrame = new AnimationFrame(this);
	animationFrame->InsertProject(&(project[activeProject]));
	animationFrame->Show(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	AboutDialog* dialog = new AboutDialog(this);
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


	// Select placement
	if(k == WXK_NUMPAD_ADD && selectedTargetPosition
			< project[activeProject].runs[0].placements.GetCount() - 1) selectedTargetPosition++;
	if(k == WXK_NUMPAD_SUBTRACT && selectedTargetPosition > 0) selectedTargetPosition--;

	if(selectedTargetPosition
			< project[activeProject].runs[0].placements.GetCount()
			&& project[activeProject].runs[0].placements[selectedTargetPosition].isMovable){

		if(k == WXK_UP) project[activeProject].runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
				0.0, 0.001, 0.0);
		if(k == WXK_DOWN) project[activeProject].runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
				0.0, -0.001, 0.0);
		if(k == WXK_RIGHT) project[activeProject].runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
				0.001, 0.0, 0.0);
		if(k == WXK_LEFT) project[activeProject].runs[0].placements[selectedTargetPosition].matrix.TranslateGlobal(
				-0.001, 0.0, 0.0);

		this->Refresh();
	}

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

void MainFrame::SetupTree(void)
{
	tree->DeleteAllItems();

	size_t i, j, k;
	//TreeItemData* tid;

	wxTreeItemId rootId = tree->AddRoot(_T("TreeRoot"));

	wxTreeItemId treeIdProject;

	wxTreeItemId treeIdObject;
	wxTreeItemId treeIdGeometry;
	wxTreeItemId treeIdStock;
	wxTreeItemId treeIdMachine;
	wxTreeItemId treeIdToolbox;
	wxTreeItemId treeIdRun;
	wxTreeItemId treeIdRun2;

	wxTreeItemId treeIdToolpath;

	for(i = 0; i < project.GetCount(); i++){
		treeIdProject = tree->AppendItem(rootId, _("Project: ")
				+ project[i].projectName);

		for(j = 0; j < project[i].objects.GetCount(); j++){
			treeIdObject = tree->AppendItem(treeIdProject, _("Object: ")
					+ project[i].objects[j].fileName.GetName());
			for(k = 0; k < project[i].objects[j].geometries.GetCount(); k++){
				{
					tree->AppendItem(treeIdObject,
							project[i].objects[j].geometries[k].objectName);
				}
			}
		}
		treeIdStock = tree->AppendItem(treeIdProject, _("Stock material: ")
				+ project[i].stock.fileName.GetName());
		for(j = 0; j < project[i].stock.stockMaterials.GetCount(); j++){
			tree->AppendItem(treeIdStock,
					project[i].stock.stockMaterials[j].materialName);
		}

		treeIdMachine = tree->AppendItem(treeIdProject, _("Machine: ")
				+ project[i].machine.fileName.GetName());

		treeIdToolbox = tree->AppendItem(treeIdProject, _("Toolbox: ")
				+ project[i].toolbox.fileName.GetName());
		for(j = 0; j < project[i].toolbox.tools.GetCount(); j++){
			tree->AppendItem(treeIdToolbox,
					project[i].toolbox.tools[j].toolName);
		}

		treeIdRun = tree->AppendItem(treeIdProject, _("Run:"));
		for(j = 0; j < project[i].runs.GetCount(); j++){
			treeIdRun2
					= tree->AppendItem(treeIdRun, project[i].runs[j].runName);

			tree->AppendItem(treeIdRun2, _("Stock material"));
			tree->AppendItem(treeIdRun2, _("Target"));
			treeIdToolpath = tree->AppendItem(treeIdRun2, _("Toolpath"));
		}

	}


	//	for(i = 0; i < doc->geometry.Count(); i++){
	//		tid = new TreeItemData;
	//		tid->nr = i;
	//		tid->dataType = TreeItemData::geometry;
	//		tree->AppendItem(treeIdGeometry, doc->geometry[i].objectName, -1, -1,
	//				tid);
	//	}


	tree->ExpandAll();
}

