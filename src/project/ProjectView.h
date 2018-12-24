/*
 * ProjectView.h
 *
 *  Created on: 21.12.2018
 *      Author: toby
 */

#ifndef SRC_PROJECT_PROJECTVIEW_H_
#define SRC_PROJECT_PROJECTVIEW_H_

#include <stddef.h>
#include <wx/docview.h>
#include <wx/object.h>
#include <wx/event.h>

#include "StockFile.h"
#include "ToolBox.h"

class ProjectView:public wxView {
public:
	ProjectView();
	virtual ~ProjectView();

	bool OnCreate(wxDocument* doc, long flags);
	void OnDraw(wxDC *dc);
	void OnUpdate(wxView *sender, wxObject *hint = NULL);
	void OnUpdate3D(void);
	void OnUpdateTree(wxCommandEvent& event);

	bool OnClose(bool deleteWindow = true);

public:
	// Supplies
	StockFile stock;
	ToolBox toolbox;

	wxDECLARE_EVENT_TABLE();
	DECLARE_DYNAMIC_CLASS(ProjectView);
};

#endif /* SRC_PROJECT_PROJECTVIEW_H_ */
