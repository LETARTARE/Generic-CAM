/*
 * OpenGLCanvas.cpp
 *
 *  Created on: 13.09.2008
 *      Author: toby
 */

#include "OpenGLCanvas.h"



#include <wx/wx.h>
#include <GL/glu.h>
#include <wx/glcanvas.h>

#define TIMER_OPENGLCANVAS 902

//TODO: Change this to .Connect(...) calls.
BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
EVT_SIZE(OpenGLCanvas::OnSize)
EVT_PAINT (OpenGLCanvas::OnPaint)
EVT_ERASE_BACKGROUND (OpenGLCanvas::OnEraseBackground)
EVT_ENTER_WINDOW( OpenGLCanvas::OnEnterWindow )
EVT_MOUSE_EVENTS(OpenGLCanvas::OnMouseEvent)
EVT_TIMER(TIMER_OPENGLCANVAS, OpenGLCanvas::OnTimer)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
		wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size, style
		| wxFULL_REPAINT_ON_RESIZE, name)
{
	isInitialized = false;
	m_gllist = 0;
	x = y = 0;

	control = NULL;

	stereoMode = 0;

	//TODO: Rewrite this to support multiple instances!
	timer.SetOwner(this,TIMER_OPENGLCANVAS);
	timer.Start(100);
}

//OpenGLCanvas::OpenGLCanvas(wxWindow *parent, const OpenGLCanvas *other,
//    wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
//    const wxString& name )
//    : wxGLCanvas(parent, other->GetContext(), id, pos, size, style|wxFULL_REPAINT_ON_RESIZE , name)
//{
//    m_init = false;
//    m_gllist = other->m_gllist; // share display list
//}

OpenGLCanvas::~OpenGLCanvas()
{

}

void OpenGLCanvas::SetController(Control3D *control)
{
	this->control = control;

	wxLogMessage(_T("Got a controller!"));

}

void OpenGLCanvas::Render()
{

#ifndef __WXMOTIF__
	if( !GetContext()) return;
#endif

	SetCurrent();
	wxPaintDC(this);

	// Init OpenGL once, but after SetCurrent
	if(!isInitialized){
		InitGL();
		isInitialized = true;
	}

	glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();



	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDrawBuffer(GL_BACK);
	/* clear color and depth buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(stereoMode == 1){
		glDrawBuffer(GL_BACK_LEFT);
		glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);

		::glPushMatrix();
		//::glRotatef();

		::glTranslatef(0.1, 0, 0);
	}
	::glTranslatef(0.0, 0, -10);
	::glMultMatrixd(rotmat.a);

	if(m_gllist == 0){
		m_gllist = glGenLists(1); // Make one (1) empty display list.
		glNewList(m_gllist, GL_COMPILE_AND_EXECUTE);
		glEndList();
	}else{
		glCallList(m_gllist);
	}

	if(stereoMode == 1){
		glDrawBuffer(GL_BACK_RIGHT);
		::glPopMatrix();
		glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);

		::glTranslatef(-0.1, 0, -10);

		::glMultMatrixd(rotmat.a);

		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		glCallList(m_gllist);

	}

	glFlush();
	SwapBuffers();
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



void OpenGLCanvas::OnEnterWindow(wxMouseEvent& WXUNUSED(event) )
{
	SetFocus();
}

void OpenGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event) )
{
	Render();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
	// this is also necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);

	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
	int w, h;
	GetClientSize( &w, &h);
#ifndef __WXMOTIF__
	if(GetContext())
#endif
	{
		SetCurrent();
		::glViewport(0, 0, (GLint) w, (GLint) h);
		GLdouble ar = (GLdouble) w / (GLdouble) h; // Perspective neu bestimmen
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(45, ar, 1, 200);
		::glMatrixMode(GL_MODELVIEW);
	}
	this->Update();
}

void OpenGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
	// Do nothing, to avoid flashing.
}

void OpenGLCanvas::InitGL()
{
	SetCurrent();

	/* set viewing projection */
//	glMatrixMode(GL_PROJECTION);
//	glFrustum( -0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
// Is done in OnSize(...)

	GLfloat attenuation[] = {1.0f, -0.01f, -.000001f};
	//::glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation, 0);

	::glEnable(GL_POINT_SMOOTH);
	::glEnable(GL_DEPTH_TEST);
	::glEnable(GL_LIGHTING);
	SetupLighting();
}

void OpenGLCanvas::SetupLighting()	// Eine Lampe in die Szene setzen
{
	GLfloat ambient0[]  = {0.5f, 0.5f, 0.5f};
	GLfloat diffuse0[]  = {0.8f, 0.8f, 0.8f};
	GLfloat specular0[] = {0.9f, 0.9f, 0.9f};
	GLfloat position0[] = {-10, 20, 50, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHT0);	// ... und anschalten
}

void OpenGLCanvas::OnMouseEvent(wxMouseEvent& event)
{
	if(event.ButtonDown(wxMOUSE_BTN_RIGHT))
	{
		x=event.m_x;
		y=event.m_y;
	}
	if(event.Dragging())
	{
		rotmat.RotateByMouse(event.m_x-x,event.m_y-y,0.5);
		x=event.m_x;
		y=event.m_y;

		this->Refresh();
	}

}

void OpenGLCanvas::OnTimer(wxTimerEvent& event)
{
	if(control != NULL){

		control->Pump();
		rotmat.RotateByTrackball((float) control->GetAxis(3) / 50.0,
				(float) control->GetAxis(4) / 50.0,
				(float) control->GetAxis(5) / 50.0);
		rotmat.TranslateByTrackball((float) control->GetAxis(0) / 1000.0,
				(float) control->GetAxis(1) / 1000.0,
				(float) control->GetAxis(2) / 1000.0);
		//rotmat.RotateByMouse(1,0,1);
		if(control->GetButton(0)){
			rotmat.Identity();
		}
	}
	this->Refresh();
}
