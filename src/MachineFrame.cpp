/*
 * MachineFrame.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachineFrame.h"

MachineFrame::MachineFrame(wxWindow* parent):GUIMachineFrame(parent)
{

//	canvas = new OpenGLCanvas(this, wxID_ANY, wxDefaultPosition,
//			wxDefaultSize);
	//If we have a parentframe with a OpenGL-Canvas use this:
	//canvas = new OpenGLCanvas( this, parent->canvas, wxID_ANY, wxDefaultPosition, wxDefaultSize );;

//	m_canvas->MakeTest();


//	this->Layout();

//
}

MachineFrame::~MachineFrame()
{

}


void MachineFrame::OnClose(wxCommandEvent &event)
{
	Close();
}
