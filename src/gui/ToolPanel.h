//============================================================================
// Name        : ToolPanel.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLPANEL_H_
#define TOOLPANEL_H_

#include <wx/panel.h>
#include <wx/dcclient.h>

#include "../simulator/Tool.h"

class ToolPanel:public wxPanel {
	// Costructor/ Destructor
public:
	ToolPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			wxTAB_TRAVERSAL);
	virtual ~ToolPanel();

	// Member Variables
public:

private:
	Tool* tool;

	//Methods
public:

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent &event);

	void OnMotion(wxMouseEvent& event);
	void OnLeftDown(wxMouseEvent& event);

	void InsertTool(Tool* t);

};

#endif /* TOOLPANEL_H_ */
