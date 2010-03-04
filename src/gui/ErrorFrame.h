//============================================================================
// Name        : ErrorFrame.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 04.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef ERRORFRAME_H_
#define ERRORFRAME_H_

#include "gui.h"

class ErrorFrame:public GUIErrorFrame {
	// Constructor/ Destructor
public:
	ErrorFrame(wxWindow* parent);
	virtual ~ErrorFrame();

	// Member Variables

	// Methods
public:
	void SetText(wxString text);
	void OnClose(wxCommandEvent &event);
};

#endif /* ERRORFRAME_H_ */
