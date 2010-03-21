//============================================================================
// Name        : ToolCanvas.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 17.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ToolCanvas.h"

ToolCanvas::ToolCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	tool = NULL;

}

ToolCanvas::~ToolCanvas()
{
}

void ToolCanvas::InsertTool(Tool* t)
{
	tool = t;
}

void ToolCanvas::RenderCoordinateSystem(void)
{
	glBegin(GL_LINES);

	glColor3b(255, 0, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3b(0, 255, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(0, -1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);

	glColor3b(0, 0, 255);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -1);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);

	glEnd();
}

void ToolCanvas::Render()
{
	float scaleFactor = 50.0;
	RenderCoordinateSystem();
	::glEnable(GL_RESCALE_NORMAL);
	::glScalef(scaleFactor, scaleFactor, scaleFactor);
	if(tool != NULL) tool->Paint();
	::glDisable(GL_RESCALE_NORMAL);
}
