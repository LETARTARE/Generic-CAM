//============================================================================
// Name        : ToolCanvas.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 17.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLCANVAS_H_
#define TOOLCANVAS_H_

#include "../3D/OpenGLCanvas.h"
#include "../simulator/Tool.h"

class ToolCanvas:public OpenGLCanvas {
	// Constructor / Destructor
public:
	ToolCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			0, const wxString& name = _T(""));
	virtual ~ToolCanvas();

	// Member Variables
private:
	Tool* tool;

	// Methods
public:
	void InsertTool(Tool& t);
	void RenderCoordinateSystem(void);
	void Render();

};

#endif /* TOOLCANVAS_H_ */
