//============================================================================
// Name        : ToolboxFrame.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ToolboxFrame.h"

ToolboxFrame::ToolboxFrame(wxWindow* parent) :
	GUIToolboxFrame(parent)
{
}

ToolboxFrame::~ToolboxFrame()
{
}

void ToolboxFrame::OnClose(wxCommandEvent &event)
{
	Close();
}
