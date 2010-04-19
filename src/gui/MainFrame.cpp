/*
 * MainFrame.cpp
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */
#include "MainFrame.h"
#include "AboutDialog.h"
#include "Control6DOFDialog.h"
#include "ErrorFrame.h"
#include "DataFrame.h"
#include "ToolboxFrame.h"

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{
	logWindow = new wxLogWindow(this, _("Generic CAM - log window"), false,
			true);
	logWindow->Show();


	// Setup configuration
	config = new wxConfig(_T("GenericCAM"));
	control.GetConfigFrom(config);

	m_canvas->SetController(&control);

	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnTimer), NULL,
			this);

	simulator.InsertMachine(&machine);

	timer.Start(100);

	m_canvas->InsertMachine(&machine);

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

void MainFrame::OnChangeStereo3D(wxCommandEvent &event)
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

	dataFrame->SetController(&control);

	dataFrame->Show(true);
}

void MainFrame::OnSetupController(wxCommandEvent &event)
{
	Control6DOFDialog temp(this);
	temp.SetupWith(&control);
	temp.ShowModal();
}

void MainFrame::OnLoadMachine(wxCommandEvent &event)
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
		machineFileName.Assign(dialog.GetPath());
		OnReloadMachine(event);


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}

void MainFrame::OnReloadMachine(wxCommandEvent &event)
{
	if(!machineFileName.IsOk()) return;

	//TODO: Rewrite the next line, so that the machine knows its programs name not the mainframe.
	machine.programFile = machineFileName;

	wxTextFile file(machineFileName.GetFullPath());
	if(!file.Open(wxConvLocal)){
		if(!file.Open(wxConvFile)){
			wxLogError(_T("Opening of the file failed!"));
			return;
		}
	}
	wxString temp, str;

	for(str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()){
		temp += str + _T("\n");
	}

	machine.SetMachineDescription(temp);
	if(!machine.textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.
		ErrorFrame* error = new ErrorFrame(this);
		error->SetText(machine.textOut);
		error->Show();
	}
	t = 0;
}

void MainFrame::OnLoadToolbox(wxCommandEvent &event)
{
	wxFileDialog dialog(this, _("Open toolbox..."), _T(""), _T(""),
			_("Toolbox (*.xml)|*.xml|All files|*.*"), wxFD_OPEN
					| wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){

		toolboxFileName.Assign(dialog.GetPath());
		if(!machine.toolbox.LoadToolbox(toolboxFileName.GetFullPath())){
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


	//TODO: Build something like in this snippet.
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

	if(dialog.ShowModal() == wxID_OK){
		toolboxFileName = dialog.GetPath();

		if(!machine.toolbox.LoadToolbox(toolboxFileName.GetFullPath())){
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

	toolboxFrame->SetController(&control);
	toolboxFrame->InsertToolBox(&(machine.toolbox));
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
	machine.Assemble();
	this->Refresh();
}

