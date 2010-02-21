/*
 * MainFrame.cpp
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */
#include "MainFrame.h"
#include "AboutDialog.h"

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{
}

MainFrame::~MainFrame()
{

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
