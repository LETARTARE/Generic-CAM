///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.cpp
// Purpose            : Class providing wxWidgets with an OpenGL canvas with extra functions.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   : -lopengl32 -lglu
// Author             : Tobias Schaefer
// Created            : 13.09.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////
#include "OpenGLCanvas.h"
#include <wx/wx.h>
#ifdef __WXMAC__
#include "OpenGL/glu.h"
//#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
//#include <GL/gl.h>
#endif
#define TIMER_OPENGLCANVAS 1902
//TODO: Change this to this->Connect(...) calls.
BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
EVT_SIZE(OpenGLCanvas::OnSize)
EVT_PAINT (OpenGLCanvas::OnPaint)
EVT_ERASE_BACKGROUND (OpenGLCanvas::OnEraseBackground)
EVT_ENTER_WINDOW( OpenGLCanvas::OnEnterWindow )
EVT_MOUSE_EVENTS(OpenGLCanvas::OnMouseEvent)
EVT_TIMER(TIMER_OPENGLCANVAS, OpenGLCanvas::OnTimer)
END_EVENT_TABLE()

static int wx_gl_attribs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 24, 0};

//wxGLCanvas(parent, wxID_ANY ,wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"));

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
	wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size, style
			| wxFULL_REPAINT_ON_RESIZE, name, wx_gl_attribs)
{


	// int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

	isInitialized = false;
	m_gllist = 0;
	x = y = 0;

	control = NULL;

	stereoMode = false;


	//TODO: Rewrite this to support multiple instances!
	timer.SetOwner(this, TIMER_OPENGLCANVAS);
	timer.Start(100);
}

OpenGLCanvas::~OpenGLCanvas()
{
}

void OpenGLCanvas::SetController(Control3D& control)
{
	this->control = &control;
	//wxLogMessage(_T("OpenGLCanvas: Controller inserted!"));
}

void OpenGLCanvas::OnEnterWindow(wxMouseEvent& WXUNUSED(event) )
{
	SetFocus();
}

void OpenGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event) )
{
	if(!IsShown()) return;

#ifndef __WXMOTIF__
	if(!GetContext()) return;
#endif

	wxGLCanvas::SetCurrent();
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


	// <a>


	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
	int w, h;
	GetClientSize(&w, &h);


#ifndef __WXMOTIF__
	if(GetContext())
#endif
	{
		SetCurrent();
		::glViewport(0, 0, (GLint) w, (GLint) h);
		GLdouble ar = (GLdouble) w / (GLdouble) h; // Perspective neu bestimmen
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(45, ar, 0.01, 10);
		::glMatrixMode(GL_MODELVIEW);
	}

	//</a>


	if(stereoMode){
		glDrawBuffer(GL_BACK_LEFT);
		glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
		::glPushMatrix();
		//::glRotatef();
		::glTranslatef(0.1, 0, 0);
	}

	::glTranslatef(0.0, 0, -1);
	::glMultMatrixd(transmat.a);
	::glMultMatrixd(rotmat.a);


//	float specReflection[] = { 0.8f, 0.0f, 0.8f, 1.0f };
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
//	glMateriali(GL_FRONT, GL_SHININESS, 96);



	//	if(m_gllist == 0){
	//		m_gllist = glGenLists(1); // Make one (1) empty display list.
	//		glNewList(m_gllist, GL_COMPILE_AND_EXECUTE);
	Render();
	//		glEndList();
	//	}else{
	//		glCallList(m_gllist);
	//	}

	if(stereoMode){
		glDrawBuffer(GL_BACK_RIGHT);
		::glPopMatrix();
		glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);

		::glTranslatef(-0.1, 0, -10);

		::glMultMatrixd(transmat.a);
		::glMultMatrixd(rotmat.a);

		glClear(GL_DEPTH_BUFFER_BIT);

		Render();
		//glCallList(m_gllist);

	}

	glFlush();
	SwapBuffers();

}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
	// this is also necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);

	this->Refresh();
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

	//	GLfloat attenuation[] =
	//		{1.0f, -0.01f, -.000001f};
	//::glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation, 0);


	::glEnable(GL_COLOR_MATERIAL);
	::glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//::glBlendFunc(GL_ONE, GL_ONE); // for Stereo Mode

	::glEnable(GL_BLEND);
	::glEnable(GL_POINT_SMOOTH);
	::glEnable(GL_DEPTH_TEST);
	SetupLighting();
	this->Refresh();

}

void OpenGLCanvas::SetupLighting() // Eine Lampe in die Szene setzen
{
	GLfloat ambient0[] =
		{0.4f, 0.4f, 0.4f};
	GLfloat diffuse0[] =
		{0.7f, 0.7f, 0.7f};
	GLfloat specular0[] =
		{0.9f, 0.9f, 0.9f};
	GLfloat position0[] =
		{-10, 20, 50, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHT0); // ... und anschalten

	::glEnable(GL_LIGHTING);
}

void OpenGLCanvas::OnMouseEvent(wxMouseEvent& event)
{
	if(event.ButtonDown(wxMOUSE_BTN_RIGHT) || event.ButtonDown(
			wxMOUSE_BTN_MIDDLE)){
		x = event.m_x;
		y = event.m_y;
	}
	if(event.Dragging() && event.RightIsDown()){
		rotmat = AffineTransformMatrix::RotateXY(event.m_x - x, event.m_y - y,
				0.5) * rotmat;
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}

	if(event.Dragging() && event.MiddleIsDown()){
		float dx = (float) (event.m_x - x) / 1000.0;
		float dy = (float) (event.m_y - y) / 1000.0;
		transmat.TranslateGlobal(dx, -dy, 0);
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}

	int x = event.GetWheelRotation();
	if(x != 0){
		transmat.TranslateGlobal(0, 0, (float) -x / 1000.0);
		this->Refresh();
	}

}

void OpenGLCanvas::OnTimer(wxTimerEvent& event)
{
	if(control == NULL) return;

	control->Pump();
	if(control->IsIdle())return;
	rotmat = AffineTransformMatrix::RotateInterwoven(
			(float) control->GetAxis(3) / 1000.0, (float) control->GetAxis(4)
					/ 1000.0, (float) control->GetAxis(5) / 1000.0) * rotmat;
	transmat.TranslateGlobal((float) control->GetAxis(0) / 1000.0,
			(float) control->GetAxis(1) / 1000.0, (float) control->GetAxis(2)
					/ 1000.0);
	//rotmat.RotateXY(1,0,1);
	if(control->GetButton(0)){
		rotmat.SetIdentity();
		transmat.SetIdentity();
	}
	this->Refresh();
}

void OpenGLCanvas::Render()
{
	::glPushMatrix();

	GLfloat x = 1.0;
	GLfloat y = 0.5;
	GLfloat z = 2.0;

	GLfloat t = sqrt(x * x + y * y + z * z);
	GLfloat nx = x / t;
	GLfloat ny = y / t;
	GLfloat nz = z / t;




	::glBegin(GL_QUADS);
	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);
	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);

	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);

	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);
	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);

	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);

	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);
	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);

	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);

	::glEnd();

	::glPopMatrix();
}
