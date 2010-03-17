//============================================================================
// Name        : DataCanvas.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "DataCanvas.h"

DataCanvas::DataCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	geometry = NULL;
}

DataCanvas::~DataCanvas()
{
	// TODO Auto-generated destructor stub
}

void DataCanvas::InsertData(Geometry* data)
{
	geometry = data;
}

void DataCanvas::Render()
{
	if(geometry != NULL) geometry->Paint();
}
