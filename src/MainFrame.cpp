/*
 * MainFrame.cpp
 *
 *  Created on: 18.09.2009
 *      Author: toby
 */
#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{
	}

MainFrame::~MainFrame()
{

}

void MainFrame::OnAbout(wxCommandEvent& event)
{

}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}
