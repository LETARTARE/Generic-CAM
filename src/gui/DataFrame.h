//============================================================================
// Name        : DataFrame.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef DATAFRAME_H_
#define DATAFRAME_H_

#include "gui.h"
#include "../3D/Geometry.h"
#include <wx/filename.h>

class DataFrame:public GUIDataFrame {
	// Constructor/ Destructor
public:
	DataFrame(wxWindow* parent);
	virtual ~DataFrame();

	// Member Variables
private:
	wxFileName fileName;
	Geometry geometry;

	// Methods
public:
	void SetController(Control3D& control);
	void OnChangeStereo3D(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnLoadSTLData(wxCommandEvent& event);
};

#endif /* DATAFRAME_H_ */
