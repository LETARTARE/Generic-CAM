/*
 * MainFrame.cpp
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */
#include "MainFrame.h"
#include "AboutDialog.h"
#include "MachineFrame.h"
#include "Control6DOFDialog.h"

MainFrame::MainFrame(wxWindow* parent) :
	GUIMainFrame(parent)
{

	// Setup configuration
	config = new wxConfig(_T("GenericCAM"));
	control.GetConfigFrom(config);


//	//TODO: Next 2 Lines for debugging. Delete!
//	MachineFrame* machineFrame = new MachineFrame(this);
//	machineFrame->Show();



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

void MainFrame::OnSelectMachine(wxCommandEvent& event)
{
	MachineFrame* machineFrame = new MachineFrame(this);

	machineFrame->Show(true);
}

void MainFrame::OnSetupController(wxCommandEvent &event)
{
	Control6DOFDialog temp(this);
	temp.SetupWith(&control);
	temp.ShowModal();
}
