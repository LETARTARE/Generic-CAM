/*
 * MachineFrame.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#ifndef MACHINEFRAME_H_
#define MACHINEFRAME_H_

#include "gui/gui.h"
#include <wx/log.h>
//#include "OpenGLCanvas.h"
#include <wx/splitter.h>

class MachineFrame:public GUIMachineFrame {
	// Constructor / Destructor
public:
	MachineFrame(wxWindow* parent);
	virtual ~MachineFrame();

	// Member Variables
	wxLogWindow* logWindow;

	void SetController(Control3D *control);


	// Methods
public:
	void OnClose(wxCommandEvent &event);
};

#endif /* MACHINEFRAME_H_ */
