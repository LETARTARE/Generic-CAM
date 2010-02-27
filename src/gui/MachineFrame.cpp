/*
 * MachineFrame.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachineFrame.h"

MachineFrame::MachineFrame(wxWindow* parent) :
	GUIMachineFrame(parent)
{


	//	canvas = new OpenGLCanvas(this, wxID_ANY, wxDefaultPosition,
	//			wxDefaultSize);
	//If we have a parentframe with a OpenGL-Canvas use this:
	//canvas = new OpenGLCanvas( this, parent->canvas, wxID_ANY, wxDefaultPosition, wxDefaultSize );;

	//	m_canvas->MakeTest();


	//	this->Layout();

	machine = new Machine;
}

MachineFrame::~MachineFrame()
{
	delete machine;
}

void MachineFrame::SetController(Control3D* control)
{
	m_canvas->SetController(control);
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
		wxTextFile file(dialog.GetPath());
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

		machine->InsertMachineDescription(temp);


		//ctrlTextEdit->SetValue(temp);
		//fname.Assign(dialog.GetPath());
		//ctrlTextEdit->SetModified(false);
		//SetWindowTitle();

	}
}
