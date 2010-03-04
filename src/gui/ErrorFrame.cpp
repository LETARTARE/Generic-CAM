//============================================================================
// Name        : ErrorFrame.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 04.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ErrorFrame.h"
#include <wx/log.h>

ErrorFrame::ErrorFrame(wxWindow* parent) :
	GUIErrorFrame(parent)
{
}

ErrorFrame::~ErrorFrame()
{
}

void ErrorFrame::SetText(wxString text)
{
	this->m_textCtrl->SetValue(text);
}
void ErrorFrame::OnClose(wxCommandEvent &event)
{
	Close();
}
