//============================================================================
// Name        : ToolboxFrame.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLBOXFRAME_H_
#define TOOLBOXFRAME_H_

#include "gui.h"
#include "../simulator/Toolbox.h"

class ToolboxFrame:public GUIToolboxFrame {
	// Constructor/ Destructor

public:
	ToolboxFrame(wxWindow* parent);
	virtual ~ToolboxFrame();

	// Member Variables

	Toolbox* linkedToolbox;

	unsigned int selectedTool;
	unsigned int selectedElement;


	// Methods
public:
	void OnClose(wxCommandEvent& event);
	void InsertToolBox(Toolbox& toolbox);
	void OnChangeStereo3D(wxCommandEvent& event);
	void UpdateDisplay(void);
	void SetController(Control3D& control);
};

#endif /* TOOLBOXFRAME_H_ */
