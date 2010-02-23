/*
 * MachineCanvas.h
 *
 *  Created on: 23.02.2010
 *      Author: toby
 */

#ifndef MACHINECANVAS_H_
#define MACHINECANVAS_H_

#include "OpenGLCanvas.h"

class MachineCanvas:public OpenGLCanvas {
public:
	MachineCanvas(wxWindow *parent,
			wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = 0,
			const wxString& name = _T("Machine Display"));
	virtual ~MachineCanvas();
};

#endif /* MACHINECANVAS_H_ */
