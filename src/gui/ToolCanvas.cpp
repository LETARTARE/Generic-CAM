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
	if(tool != NULL){

		unsigned int i, j;
		const unsigned int N = 32;

		float ss[N + 1], cc[N + 1];
		for(i = 0; i <= N; i++){
			ss[i] = sin(2* M_PI / N * i);
			cc[i] = cos(2* M_PI / N * i);
		}

		::glEnable(GL_RESCALE_NORMAL);
		::glScalef(scaleFactor, scaleFactor, scaleFactor);

		for(i = 0; i < tool->contour.Count(); i++){
			::glBegin(GL_QUAD_STRIP);
			for(j = 0; j <= N; j++){
				::glNormal3f(cc[j] * tool->contour[i].n1.x, ss[j]
						* tool->contour[i].n1.x, tool->contour[i].n1.z);
				::glVertex3f(cc[j] * tool->contour[i].p1.x, ss[j]
						* tool->contour[i].p1.x, tool->contour[i].p1.z);
				::glNormal3f(cc[j] * tool->contour[i].n2.x, ss[j]
						* tool->contour[i].n2.x, tool->contour[i].n2.z);
				::glVertex3f(cc[j] * tool->contour[i].p2.x, ss[j]
						* tool->contour[i].p2.x, tool->contour[i].p2.z);
			}
			::glEnd();
		}
		::glDisable(GL_RESCALE_NORMAL);
	}
}

// This should happen in a derived class:
//void OpenGLCanvas::InsertGeometry(Document* doc)
//{
//	SetCurrent();
//	::glNewList(m_gllist, GL_COMPILE);
//
//	std::list <Geometry *>::iterator pg;
//	for(pg = doc->objectGeometry.begin(); pg != doc->objectGeometry.end(); ++pg){
//		(*pg)->Paint();
//	}
//	std::list <Source *>::iterator ps;
//	for(ps = doc->objectSource.begin(); ps != doc->objectSource.end(); ++ps){
//		(*ps)->Paint();
//	}
//	std::list <Connector *>::iterator pc;
//	for(pc = doc->objectConnector.begin(); pc != doc->objectConnector.end(); ++pc){
//		(*pc)->Paint();
//	}
//	std::list <Result *>::iterator pr;
//	for(pr = doc->objectResult.begin(); pr != doc->objectResult.end(); ++pr){
//		(*pr)->Paint();
//	}
//
//	::glEndList();
//}
