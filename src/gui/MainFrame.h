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
	// Methods
private:

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSelectMachine(wxCommandEvent& event);
	void OnSelectData(wxCommandEvent& event);
	void OnSetupController(wxCommandEvent &event);

};

#endif /* MAINFRAME_H_ */
