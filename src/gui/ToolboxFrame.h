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

class ToolboxFrame:public GUIToolboxFrame {
	// Constructor/ Destructor

public:
	ToolboxFrame(wxWindow* parent);
	virtual ~ToolboxFrame();

	// Member Variables

	// Methods
public:
	void OnClose(wxCommandEvent &event);

};

#endif /* TOOLBOXFRAME_H_ */
