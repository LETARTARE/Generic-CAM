/*
 * Control6DOFDialog.h
 *
 *  Created on: 25.07.2009
 *      Author: toby
 */

#ifndef CONTROL6DOFDIALOG_H_
#define CONTROL6DOFDIALOG_H_

#include "../StdInclude.h"
#include "../Config.h"
#include "../controller/Control3D.h"
#include "gui.h"

class Control6DOFDialog:public GUIControl6DOFDialog {
	// Constructor / Destructor
public:
	Control6DOFDialog(wxWindow* parent);
	virtual ~Control6DOFDialog();

	// Member Variables
protected:
	Control3D* control;

private:
	wxTimer timer;

	// Member Functions
public:
	void InsertController(Control3D& control);


private:
	//TODO: The next function shouldn't be here!
	Control3D *GetControl()
	{
		return control;
	}
protected:
	void OnConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);

	void UpdateData();
};

#endif /* CONTROL6DOFDIALOG_H_ */
