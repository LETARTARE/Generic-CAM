/*
 * MachineCanvas.cpp
 *
 *  Created on: 23.02.2010
 *      Author: toby
 */

#include "MachineCanvas.h"

MachineCanvas::MachineCanvas(wxWindow *parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style,
		const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	machine = NULL;
}

MachineCanvas::~MachineCanvas()
{
}

void MachineCanvas::InsertMachine(Machine& m)
{
	machine = &m;
}

void MachineCanvas::RenderCoordinateSystem(void)
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

void MachineCanvas::Render()
{
	RenderCoordinateSystem();
	if(machine != NULL) machine->Paint();
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
