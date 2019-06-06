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
#include "FrameParent.h"

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

#include "../math/MathParser.h"
#include "../project/ProjectView.h"
#include "IDs.h"

#ifndef __WIN32__
#include "../icon/logo32.xpm"
#include "../icon/logo48.xpm"
#include "../icon/logo64.xpm"
#include "../icon/logo128.xpm"
#endif

#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include <wx/busyinfo.h>
#include <wx/utils.h>
#include <wx/icon.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <unistd.h>

FrameMain::FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
		wxDocParentFrame* parent) :
		GUIFrameMain(doc, view, parent)
{
	this->config = config;

	selectedTargetPosition = 0;

	FrameParent* parentframe = wxStaticCast(parent, FrameParent);
	Project* project = wxStaticCast(GetDocument(), Project);

#ifndef __WIN32__
	//TODO: Check, why the icon is not working under Windows / Code::Blocks.
	wxIconBundle logo;
	logo.AddIcon(wxIcon(logo32_xpm));
	logo.AddIcon(wxIcon(logo48_xpm));
	logo.AddIcon(wxIcon(logo64_xpm));
	logo.AddIcon(wxIcon(logo128_xpm));
	SetIcons(logo);
#endif

	// Set the window size according to the config file
	int w, h;
	w = config->Read(_T("MainFrameWidth"), 600);
	h = config->Read(_T("MainFrameHeight"), 400);
	SetClientSize(w, h);

	m_menuFile->Append(wxID_NEW);
	m_menuFile->Append(wxID_OPEN);
	m_menuFile->Append(wxID_REVERT_TO_SAVED);
	wxMenu* m_menuRecent = new wxMenu();
	m_menuFile->Append(
			new wxMenuItem(m_menuFile, wxID_ANY, _("&Recently opened"),
					wxEmptyString, wxITEM_NORMAL, m_menuRecent));
	doc->GetDocumentManager()->FileHistoryAddFilesToMenu(m_menuRecent);
	m_menuFile->Append(wxID_SAVE);
	m_menuFile->Append(wxID_SAVEAS);
	m_menuFile->AppendSeparator();
	m_menuFile->Append(ID_PROJECTRENAME, _("&Rename project"));
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_PRINT);
	m_menuFile->Append(wxID_PREVIEW);
	m_menuFile->Append(wxID_PRINT_SETUP, _("Print Setup..."));
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_CLOSE);
	m_menuFile->Append(wxID_EXIT);

	m_menuEdit->Append(wxID_UNDO);
	m_menuEdit->Append(wxID_REDO);
	doc->GetCommandProcessor()->SetEditMenu(m_menuEdit);
	doc->GetCommandProcessor()->Initialize();

	m_menuPreferences->Append(ID_SETUPLANGUAGE, _T("Change Language"));
	m_menuPreferences->Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
	m_menuPreferences->Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
	m_menuPreferences->Append(ID_SETUPMIDI, _("Setup &MIDI"));
	m_menuPreferences->Append(ID_SETUPUNITS,
	_("Setup &Units") + wxT("\tCtrl+U"));

	m_menuHelp->AppendSeparator();
	m_menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	m_menuHelp->Append(wxID_ABOUT);

	tree = new TreeSetup(m_tree, project);

	m_canvas->SetDropTarget(new DnDFile(project, this));
	m_tree->SetDropTarget(new DnDFile(project, this));

	m_canvas->SetController(parentframe->control);
	m_canvas->InsertProject(project); // Connect the project to the 3D canvas
	parentframe->settingsStereo3D.WriteToCanvas(m_canvas);

	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			false);

	dialogObjectTransformation = new DialogObjectTransformation(this);
	dialogStockMaterial = new DialogStockMaterial(this);
	dialogWorkpiece = new DialogWorkpiece(this);
	dialogPlacement = new DialogPlacement(this);
	dialogRun = new DialogRun(this);
	dialogDebugger = new DialogMachineDebugger(this);
#ifdef _USE_MIDI
	dialogDebugger->SetMidiPort(parentframe->midi);
#endif

	dialogToolbox = new DialogToolbox(this);
	dialogToolpathGenerator = new DialogToolpathGenerator(this);
	dialogAnimation = new DialogAnimation(this);

	wxString dialect;
	config->Read(_T("GCodeDialect"), &dialect, _T("RS274NGC"));
	m_menuDialect->Check(ID_DIALECT_RS274NGC,
			dialect.CmpNoCase(_T("RS274NGC")) == 0);
	m_menuDialect->Check(ID_DIALECT_FANUCM,
			dialect.CmpNoCase(_T("FanucM")) == 0);

	m_canvas->display = CanvasMain::displayObjects;

	this->Connect(ID_PROJECTRENAME, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::OnProjectRename));

	this->Connect(ID_UPDATESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateSimulation));

	TransferDataToWindow();
}

FrameMain::~FrameMain()
{
	printf("FrameMain: Destructor called\n");
	// Disconnect events

	this->Disconnect(ID_UPDATESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateSimulation));

	this->Disconnect(ID_PROJECTRENAME, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::OnProjectRename));

	// Save the size of the mainframe
	int w, h;
	GetClientSize(&w, &h);
	config->Write(_T("MainFrameWidth"), (long) w);
	config->Write(_T("MainFrameHeight"), (long) h);

	wxString dialect = _T("RS274NGC");
	if(m_menuDialect->IsChecked(ID_DIALECT_FANUCM)) dialect = _T("FanucM");
	config->Write(_T("GCodeDialect"), dialect);
}

FrameParent* FrameMain::GetParentFrame(void)
{
	return wxStaticCast(GetParent(), FrameParent);
}

bool FrameMain::TransferDataToWindow(void)
{
	// Populate the treeview
	tree->Update();

//	m_menuToolpath->Check(ID_GENERATORAUTOMATIC, project.processToolpath);
	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	//TODO: Reactivate
//	m_toolBar->ToggleTool(ID_DISPLAYMACHINE, project.displayMachine);
//	m_toolBar->ToggleTool(ID_DISPLAYMATERIAL, project.displayGeometry);

//	wxString temp = _T("Generic CAM - ");
//	if(commandProcessor.IsDirty()) temp += _T("* ");
//	temp += project.name;
//	this->SetTitle(temp);

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

void FrameMain::On3DSelect(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	Project* project = wxStaticCast(GetDocument(), Project);
	OpenGLPick result;
	m_canvas->OnPick(result, x, y);

	size_t n;
	if(result.HasHits()){
		result.SortByNear();
		if(result.Get(0) == 1 && result.Get(1) > 0){
			size_t id = result.Get(1) - 1;
			for(n = 0; n < project->objects.GetCount(); n++)
				project->objects[n].selected = (n == id);
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
		if(result.Get(0) == 1){
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
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor* cmdProc = project->GetCommandProcessor();
	wxTreeItemId id = event.GetItem();
	TreeItem * data = (TreeItem*) m_tree->GetItemData(id);
	wxString newName = event.GetLabel();
	if(newName.IsEmpty()){
		event.Veto();
		return;
	}

	if(data->dataType == itemProject){
		if(newName == project->name) return;
		cmdProc->Submit(
				new CommandProjectRename(_("Project renamed to ") + newName,
						project, newName));
		return;
	};

	if(data->dataType == itemObject){
		if(newName == project->objects[data->nr].name) return;
		cmdProc->Submit(
				new CommandObjectRename(_("Object renamed to ") + newName,
						project, data->nr, newName));
		return;
	};

	if(data->dataType == itemWorkpiece){
		if(newName == project->workpieces[data->nr].name) return;
		cmdProc->Submit(
				new CommandWorkpieceRename(_("Workpiece renamed to ") + newName,
						project, data->nr, newName));
		return;
	};

	if(data->dataType == itemRun){
		if(newName == project->run[data->nr].name) return;
		cmdProc->Submit(
				new CommandRunRename(_("Run renamed to ") + newName, project,
						data->nr, newName));
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
	Project* project = wxStaticCast(GetDocument(), Project);

	tree->UpdateVariables();

	if(data->dataType == itemRun){
		if(m_tree->IsSelected(id)){
			// Only allow one item selected at a time
			size_t n;
			for(n = 0; n < project->run.GetCount(); n++)
				project->run[n].Select(n == data->nr);
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

void FrameMain::OnProjectRename(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxTextEntryDialog dialog(this, _("Enter new project name:"),
			_T("Rename Project"), project->name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project->name) return;

		CommandProjectRename * command = new CommandProjectRename(
		_("Project renamed to ") + dialog.GetValue(), project,
				dialog.GetValue());
		project->GetCommandProcessor()->Submit(command);
		TransferDataToWindow();
	}
}

void FrameMain::OnObjectLoad(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	wxFileName fileName;
	wxFileDialog dialog(this, _("Open Object..."), _T(""), _T(""),
			_(
					"All supported files (*.dxf; *.stl; *.gts)|*.dxf;*DXF;*.stl;*.STL;*.gts;*.GTS|DXF Files (*.dxf)|*.dxf;*.DXF|Stereolithography files (STL files) (*.stl)|*.stl;*.STL|GTS files (*.gts)|*.gts;*.GTS|All files|*.*"),
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

		size_t n;
		for(n = 0; n < paths.GetCount(); n++){
			fileName = paths[n];
			cmdProc->Submit(
					new CommandObjectLoad(
							(_("Load Object: ") + fileName.GetName()),
							project, paths[n]));
			if(n == 0) filepaths.lastObjectDirectory = fileName.GetPath();
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
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	int i = tree->GetFirstSelectedObject();
	if(i < 0 || i >= project->objects.GetCount()) return;
	wxTextEntryDialog dialog(this, _("Enter new name:"),
	_T("Rename Object ") + project->objects[i].name,
			project->objects[i].name);
	if(dialog.ShowModal() == wxID_OK){
		if(dialog.GetValue().IsEmpty()) return;
		if(dialog.GetValue() == project->objects[i].name) return;
		cmdProc->Submit(
				new CommandObjectRename(
				_("Object renamed to ") + dialog.GetValue(), project, i,
						dialog.GetValue()));
		TransferDataToWindow();
	}
}

void FrameMain::OnObjectDelete(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	tree->UpdateVariables();
	int i = tree->GetFirstSelectedObject();
	if(i < 0 || i >= project->objects.GetCount()) return;
	cmdProc->Submit(
			new CommandObjectDelete(
			_("Object ") + project->objects[i].name + _(" deleted."),
					project, i));
	TransferDataToWindow();
}

void FrameMain::OnObjectFlipNormals(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	size_t n;
	for(n = 0; n < project->objects.GetCount(); n++){
		if(project->objects[n].selected){
			AffineTransformMatrix matrix = project->objects[n].displayTransform
					* project->objects[n].matrix;
			CommandObjectTransform * command = new CommandObjectTransform(
					project->objects[n].name + _(": Flipped normal vectors"),
					project, n, false, false, false, true, matrix);
			cmdProc->Submit(command);
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
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	tree->UpdateVariables();
	size_t i;
	for(i = project->workpieces.GetCount(); i > 0; i--){
		if(project->workpieces[i - 1].selected){
			cmdProc->Submit(
					new CommandWorkpieceDelete(
							_("Remove workpiece ")
									+ project->workpieces[i - 1].name, project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnWorkpieceDeleteUnused(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	for(size_t i = project->workpieces.GetCount(); i > 0; i--){
		if(project->workpieces[i - 1].placements.GetCount() == 0){
			cmdProc->Submit(
					new CommandWorkpieceDelete(
							_("Remove workpiece ")
									+ project->workpieces[i - 1].name, project,
							i - 1));
		}
	}
	TransferDataToWindow();
}

void FrameMain::OnRunAdd(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	unsigned int i = project->run.GetCount() + 1;
	cmdProc->Submit(
			new CommandRunAdd(_("Add run"), project,
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
	Project* project = wxStaticCast(GetDocument(), Project);
	wxCommandProcessor * cmdProc = GetDocument()->GetCommandProcessor();
	TransferDataFromWindow();
	tree->UpdateVariables();
	for(size_t i = project->run.GetCount(); i > 0; i--){
		if(project->run[i - 1].selected){
			cmdProc->Submit(new CommandRunRemove(
			_("Remove run ") + project->run[i - 1].name, project, i - 1));
		}
	}
	TransferDataToWindow();
}
void FrameMain::OnMachineLoad(wxCommandEvent& event)
{
	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
	int selected = tree->GetFirstSelectedRun();
	if(selected < 0) return;

	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"All machine descriptions  (*.lua;*.zip)|*.lua;*.zip|Machine descriptions (LUA Files)  (*.lua)|*.lua|Packed Machine descriptions  (*.zip)|*.zip|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(filepaths.lastMachineDirectory)){
		dialog.SetDirectory(filepaths.lastMachineDirectory);
	}else{
		if(wxDir::Exists(filepaths.lastProjectDirectory)){
			dialog.SetDirectory(filepaths.lastProjectDirectory);
		}
	}
	Project* project = wxStaticCast(GetDocument(), Project);

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(project->run[selected].machine.Load(fileName)){
			filepaths.lastMachineDirectory = fileName.GetPath();
		}else{
			wxLogError
			(project->run[selected].machine.textOut);
		}
		TransferDataToWindow();
	}
}

void FrameMain::OnMachineReload(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	int selected = tree->GetFirstSelectedRun();
	if(selected < 0) return;
	if(!project->run[selected].machine.ReLoad()){
		wxLogError
		(project->run[selected].machine.textOut);
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
	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
	ProjectView* view = wxStaticCast(GetView(), ProjectView);
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if(wxDir::Exists(filepaths.lastToolboxDirectory)){
		dialog.SetDirectory(filepaths.lastToolboxDirectory);
	}else{
		if(wxDir::Exists(filepaths.lastProjectDirectory)){
			dialog.SetDirectory(filepaths.lastProjectDirectory);
		}
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(view->toolbox.LoadToolBox(fileName)){
			filepaths.lastToolboxDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnToolboxSave(wxCommandEvent &event)
{
	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
	ProjectView* view = wxStaticCast(GetView(), ProjectView);
	wxFileDialog dialog(this, _("Save toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if(view->toolbox.fileName.IsOk()){
		dialog.SetPath(view->toolbox.fileName.GetFullPath());
	}else{
		if(wxDir::Exists(filepaths.lastToolboxDirectory)){
			dialog.SetDirectory(filepaths.lastToolboxDirectory);
		}
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		if(view->toolbox.SaveToolBox(fileName)){
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
	FrameParent* parentframe = wxStaticCast(GetParent(), FrameParent);
	Project* project = wxStaticCast(GetDocument(), Project);
	const int runNr = tree->GetFirstSelectedRun();
	if(runNr < 0 || runNr >= project->run.GetCount()) return;

	wxFileDialog dialog(this, _("Save toolpath..."), _T(""), _T(""),
			_("G-Code file (*.nc)|*.nc|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(filepaths.lastToolpathDirectory)){
		dialog.SetDirectory(filepaths.lastToolpathDirectory);
	}
	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		filepaths.lastToolpathDirectory = fileName.GetPath();
		ToolPath::Dialect dialect = ToolPath::RS274NGC;
		if(m_menuDialect->IsChecked(ID_DIALECT_FANUCM)) dialect =
				ToolPath::FanucM;
		project->SaveToolpath(fileName, runNr, dialect);
	}
}

void FrameMain::OnActivateStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == stereoOff){
		m_canvas->stereoMode = stereoAnaglyph;
	}else{
		m_canvas->stereoMode = stereoOff;
	}
	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	TransferDataToWindow();
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
		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(-M_PI_2, 0, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWFRONT"), 1);
		break;
	case ID_VIEWBACK:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(M_PI_2, 0, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWBACK"), 1);
		break;
	case ID_VIEWLEFT:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, M_PI_2, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWLEFT"), 1);
		break;
	case ID_VIEWRIGHT:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, -M_PI_2, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWRIGHT"), 1);
		break;
	case ID_VIEWTOP:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_statusBar->SetStatusText(_T("ID_VIEWTOP"), 1);
		break;
	case ID_VIEWBOTTOM:
		m_canvas->rotmat = AffineTransformMatrix::Identity();
		m_canvas->rotmat *= AffineTransformMatrix::RotationXYZ(0, M_PI, 0);
		m_statusBar->SetStatusText(_T("ID_VIEWBOTTOM"), 1);
		break;
	}
	TransferDataToWindow();
}

void FrameMain::OnTestGCode(wxCommandEvent& event)
{
	//TODO: When the units change the change is not immediately propagated into the TestGCode dialog.
	DialogTestGCode * dialog = new DialogTestGCode(this);
	dialog->Show();
	dialog->Raise();
}
