/*
 * MainFrame.h
 *
 *  Created on: 18.09.2009
 *      Author: Tobias Schaefer
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include "../Config.h"
#include "../StdInclude.h"
#include "gui.h"
#include "../simulator/Machine.h"
#include "../simulator/MachineSimulator.h"
#include "../controller/Control3D.h"
#include <wx/config.h>
#include <wx/log.h>

class MainFrame:public GUIMainFrame {
	// Constructor/ Destructor
public:
	MainFrame(wxWindow* parent);
	virtual ~MainFrame();

	// Member variables
private:
	wxConfig *config;
	Control3D control;
	wxLogWindow* logWindow;

	Machine machine;
	MachineSimulator simulator;
	wxString machineFileName;

	wxTimer timer;
	float t;

	// Methods
private:

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSelectDataFrame(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent &event);

	void OnChangeStereo3D(wxCommandEvent &event);
	void OnLoadMachine(wxCommandEvent &event);
	void OnReloadMachine(wxCommandEvent &event);
	void OnTimer(wxTimerEvent& event);

};

#endif /* MAINFRAME_H_ */
