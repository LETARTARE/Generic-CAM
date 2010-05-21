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
#include "ErrorFrame.h"
#include "DataFrame.h"
#include "ToolboxFrame.h"

#include <wx/filename.h>

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{
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

	m_canvas->InsertMachine(simulator.machine);
}

MainFrame::~MainFrame()
{
	control.WriteConfigTo(config);
	delete config; // config is written back to file (automagically)
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	AboutDialog* dialog = new AboutDialog(this);

	dialog->Show();
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnChangeStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

void MainFrame::OnSelectDataFrame(wxCommandEvent& event)
{
	DataFrame* dataFrame = new DataFrame(this);

	dataFrame->SetController(control);

	dataFrame->Show(true);
}

void MainFrame::OnSetupController(wxCommandEvent& event)
{
	Control6DOFDialog temp(this);
	temp.InsertController(control);
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
					_("Machine descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		simulator.machine.fileName.Assign(dialog.GetPath());
		OnReloadMachine(event);


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}

void MainFrame::OnReloadMachine(wxCommandEvent& event)
{
	if(!simulator.machine.fileName.IsOk()) return;
	simulator.machine.ReLoadDescription();
	if(!simulator.machine.textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.
		ErrorFrame* error = new ErrorFrame(this);
		error->SetText(simulator.machine.textOut);
		error->Show();
	}
	t = 0;
}

void MainFrame::OnLoadToolbox(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"), wxFD_OPEN
					| wxFD_FILE_MUST_EXIST);
	wxFileName fileName;
	if(dialog.ShowModal() == wxID_OK){
		fileName.Assign(dialog.GetPath());
		if(!simulator.toolbox.LoadToolbox(fileName)){
			wxLogError(_T("OnLoadToolbox: Opening of the toolbox failed!"));
		}


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
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
			_("Toolbox (*.xml)|*.xml|All files|*.*"), wxFD_OPEN
					| wxFD_FILE_MUST_EXIST);
	wxFileName fileName;
	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();

		if(!simulator.toolbox.LoadToolbox(fileName)){
			wxLogError(_T("OnLoadToolbox: Opening of the toolbox failed!"));
		}


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}

void MainFrame::OnEditToolbox(wxCommandEvent& event)
{
	ToolboxFrame* toolboxFrame = new ToolboxFrame(this);

	toolboxFrame->SetController(control);
	toolboxFrame->InsertToolBox(simulator.toolbox);
	toolboxFrame->Show(true);
}

void MainFrame::OnLoadGCodes(wxCommandEvent &event)
{
	wxFileDialog
			dialog(
					this,
					_("Open G-Code file..."),
					_T(""),
					_T(""),
					_("G-Code File (*.tap *.cnc *.nc *.ncd *.txt)|*.tap;*.cnc;*.nc;*.ncd;*.txt|Text files (*.txt)|*.txt|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		simulator.ReadGCodeFile(dialog.GetPath());
	}
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
	t += 0.100;
	simulator.Step(t);
	simulator.machine.Assemble();
	this->Refresh();
}
