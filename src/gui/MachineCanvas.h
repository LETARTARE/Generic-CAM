//============================================================================
// Name        : MachineCanvas.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 23.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================

#ifndef MACHINECANVAS_H_
#define MACHINECANVAS_H_

#include "../3D/OpenGLCanvas.h"
#include "../simulator/Machine.h"

class MachineCanvas:public OpenGLCanvas {
	// Constructor / Destructor
public:
	MachineCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0, const wxString& name =
					_T(""));
	virtual ~MachineCanvas();

	// Member Variables
private:
	Machine* machine;

	// Methods
public:
	void InsertMachine(Machine& m);
	void RenderCoordinateSystem(void);
	void Render();
};

#endif /* MACHINECANVAS_H_ */
