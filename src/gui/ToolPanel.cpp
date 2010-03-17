//============================================================================
// Name        : ToolPanel.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ToolPanel.h"
#include <wx/log.h>

ToolPanel::ToolPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style) :
	wxPanel(parent, id, pos, size, style)
{

	this->SetBackgroundColour(wxColour(128, 128, 128));

	tool = NULL;


	// Connect Events
	this->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler( ToolPanel::OnLeftDown ));
	this->Connect(wxEVT_MOTION, wxMouseEventHandler( ToolPanel::OnMotion ));
	this->Connect(wxEVT_PAINT, wxPaintEventHandler( ToolPanel::OnPaint ));
	this->Connect(wxEVT_SIZE, wxSizeEventHandler( ToolPanel::OnSize ));
}

ToolPanel::~ToolPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_LEFT_DOWN,
			wxMouseEventHandler( ToolPanel::OnLeftDown ));
	this->Disconnect(wxEVT_MOTION, wxMouseEventHandler( ToolPanel::OnMotion ));
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler( ToolPanel::OnPaint ));
	this->Disconnect(wxEVT_SIZE, wxSizeEventHandler( ToolPanel::OnSize ));
}

void ToolPanel::InsertTool(Tool* t)
{
	tool = t;
	this->Refresh();
}

void ToolPanel::OnSize(wxSizeEvent &event)
{
	this->Refresh();
}

void ToolPanel::OnPaint(wxPaintEvent& event)
{

	wxPaintDC dc(this);
	wxSize sz = GetClientSize();

	dc.SetPen(*wxBLACK_PEN);

	if(tool == NULL) return;

	int i;
	wxPoint temp;
	wxString text;
	wxBrush gold(wxColor(255, 255, 128), wxSOLID);

	wxBrush blueSpecial(*wxBLUE, wxBDIAGONAL_HATCH);
	wxBrush redSpecial(*wxRED, wxBDIAGONAL_HATCH);

	dc.SetTextForeground(wxColor(255, 255, 255));
	wxFont font(20, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetFont(font);

	float shift;


	//wxLogMessage((linkedField == NULL)? _T("NULL") : _T("not NULL"));


	//	text = wxString::Format(_T("%u elements in tool."), tool->elements.Count());
	//	dc.DrawText(text, 10, 10);
}

void ToolPanel::OnMotion(wxMouseEvent& event)
{
	if(tool == NULL) return;
}

void ToolPanel::OnLeftDown(wxMouseEvent& event)
{
	unsigned char i;
	wxPoint temp;
	float x;
	wxSize sz = GetClientSize();

	if(tool == NULL) return;

	for(i = 0; i < tool->elements.Count(); i++){
		//TODO: Send a message down the pipe, if an element was selected.
		//		if(temp.x != 0 || temp.y != 0){
		//			temp -= event.GetPosition();
		//			x = sqrt(temp.x * temp.x + temp.y * temp.y);
		//			if(x < d / 2.1){
		//				wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
		//				event.SetInt(i);
		//				GetEventHandler()->ProcessEvent(event);
		//				//wxLogMessage(wxString::Format(_T("Event sent! (%u) ID = %u"),i,GetId()));
		//			}
		//		}
	}
}
