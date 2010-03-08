/*
 * MachineFrame.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachineFrame.h"
#include "ErrorFrame.h"
#include <wx/log.h>

MachineFrame::MachineFrame(wxWindow* parent) :
	GUIMachineFrame(parent)
{


	//	canvas = new OpenGLCanvas(this, wxID_ANY, wxDefaultPosition,
	//			wxDefaultSize);
	//If we have a parentframe with a OpenGL-Canvas use this:
	//canvas = new OpenGLCanvas( this, parent->canvas, wxID_ANY, wxDefaultPosition, wxDefaultSize );;

	//	m_canvas->MakeTest();


	//	this->Layout();


	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MachineFrame::OnTimer),
			NULL, this);

	timer.Start(300);

	machine = new Machine;
	m_canvas->InsertMachine(machine);
}

MachineFrame::~MachineFrame()
{
	delete machine;
}

void MachineFrame::SetController(Control3D* control)
{
	m_canvas->SetController(control);
}

void MachineFrame::OnChangeStereo3D(wxCommandEvent &event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

void MachineFrame::OnClose(wxCommandEvent &event)
{
	Close();
}

void MachineFrame::OnLoadMachine(wxCommandEvent &event)
{
	wxFileDialog
			dialog(
					this,
					_("Open..."),
					_T(""),
					_T(""),
					_("Machine Descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();

		OnReloadMachine(event);


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}

void MachineFrame::OnReloadMachine(wxCommandEvent &event)
{
	if(fileName.empty()) return;

	wxTextFile file(fileName);
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

	machine->SetMachineDescription(temp);
	if(!machine->textOut.IsEmpty()){
		//wxLogMessage(_T("Displaying some text in ErrorFrame!"));
		//TODO: Don't open a new errorframe, if the old one is not closed.
		ErrorFrame* error = new ErrorFrame(this);
		error->SetText(machine->textOut);
		error->Show();
	}
}

void MachineFrame::OnTimer(wxTimerEvent& event)
{
	//TODO: Do some animation...

	machine->Assemble();
	this->Refresh();

}

