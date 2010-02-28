/*
 * MachineFrame.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#ifndef MACHINEFRAME_H_
#define MACHINEFRAME_H_

#include "gui.h"
#include "../simulator/Machine.h"

//#include "OpenGLCanvas.h"
#include <wx/splitter.h>

class MachineFrame:public GUIMachineFrame {
	// Constructor/ Destructor
public:
	MachineFrame(wxWindow* parent);
	virtual ~MachineFrame();

	// Member Variables
private:
	Machine* machine;
	wxString fileName;

	// Methods
public:
	void SetController(Control3D *control);
	void OnChangeStereo3D(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);
	void OnLoadMachine(wxCommandEvent &event);
	void OnReloadMachine(wxCommandEvent &event);
};

#endif /* MACHINEFRAME_H_ */
