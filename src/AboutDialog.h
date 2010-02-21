/*
 * AboutDialog.h
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */

#ifndef ABOUTDIALOG_H_
#define ABOUTDIALOG_H_

#include "StdInclude.h"
#include "gui/gui.h"

class AboutDialog:public GUIAboutDialog {
	// Constructor/ Destructor
public:
	AboutDialog(wxWindow* parent);
	virtual ~AboutDialog();

	// Member variables
private:


	// Methods
private:

	void OnClose(wxCommandEvent& event);
};

#endif /* ABOUTDIALOG_H_ */
