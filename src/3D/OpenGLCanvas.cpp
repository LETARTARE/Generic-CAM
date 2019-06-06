///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.cpp
// Purpose            : Class providing wxWidgets with an OpenGL canvas with extra functions
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
///////////////////////////////////////////////////////////////////////////////

#define GL_GLEXT_PROTOTYPES

#ifdef __WXMAC__
#include "OpenGL/glu.h"
//#include "OpenGL/gl.h"
#include "OpenGL/glext.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#endif

#include "OpenGLCanvas.h"

#include "../StdInclude.h"

static int wx_gl_attribs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE,
		24, 0};

OpenGLCanvas::OpenGLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
		: wxGLCanvas(parent, id, wx_gl_attribs, pos, size,
				style | wxFULL_REPAINT_ON_RESIZE, name), Light0(GL_LIGHT0)
{

	context = NULL;
	m_gllist = 0;
	w = h = 500;
	x = y = 250;
	unitAtOrigin = 400;

	turntableX = 0;
	turntableY = M_PI / 2;
	scale = 1.0;
	stereoMode = stereoOff;
	eyeDistance = 0.1;
	focalDistance = 1.0;
	backgroundGrayLevel = 102;
	rightEyeR = 0;
	rightEyeG = 77;
	rightEyeB = 102;
	leftEyeR = 179;
	leftEyeG = 0;
	leftEyeB = 0;

	rotationMode = rotateInterwoven;

	this->Connect(wxEVT_PAINT, wxPaintEventHandler(OpenGLCanvas::OnPaint), NULL,
			this);
	this->Connect(wxEVT_ENTER_WINDOW,
			wxMouseEventHandler(OpenGLCanvas::OnEnterWindow), NULL, this);
	this->Connect(wxEVT_MOTION, wxMouseEventHandler(OpenGLCanvas::OnMouseEvent),
	NULL, this);
	this->Connect(wxEVT_MOUSEWHEEL,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Connect(wxEVT_RIGHT_DOWN,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Connect(wxEVT_MIDDLE_DOWN,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Connect(wxEVT_RIGHT_DCLICK,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);

#ifdef _USE_6DOFCONTROLLER
	control = NULL;
	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(OpenGLCanvas::OnTimer), NULL,
			this);
	timer.Start(100);
#endif
}

OpenGLCanvas::~OpenGLCanvas()
{
#ifdef _USE_6DOFCONTROLLER
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(OpenGLCanvas::OnTimer),
	NULL, this);
#endif
	this->Disconnect(wxEVT_RIGHT_DCLICK,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Disconnect(wxEVT_MIDDLE_DOWN,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Disconnect(wxEVT_RIGHT_DOWN,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Disconnect(wxEVT_MOUSEWHEEL,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Disconnect(wxEVT_MOTION,
			wxMouseEventHandler(OpenGLCanvas::OnMouseEvent), NULL, this);
	this->Disconnect(wxEVT_ENTER_WINDOW,
			wxMouseEventHandler(OpenGLCanvas::OnEnterWindow), NULL, this);
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler(OpenGLCanvas::OnPaint),
	NULL, this);

	if(context != NULL) delete context;
}

#ifdef _USE_6DOFCONTROLLER
void OpenGLCanvas::SetController(Control3D& control)
{
	this->control = &control;
}
#endif

OpenGLCanvas::Context::Context(wxGLCanvas* canvas)
		: wxGLContext(canvas)
{
	SetCurrent(*canvas);


	printf("GL_VERSION: ");
	printf("%s", (char*) glGetString(GL_VERSION));
	printf("\n");
}

void OpenGLCanvas::OnEnterWindow(wxMouseEvent& WXUNUSED(event))
{
	SetFocus();
}

#ifdef _USE_6DOFCONTROLLER
void OpenGLCanvas::OnTimer(wxTimerEvent& event)
{
	if(control == NULL) return;

	control->Pump();
	if(control->IsIdle()) return;

	const float resRot = 2000;
	const float resMov = 5 * unitAtOrigin;

	rotmat = AffineTransformMatrix::RotationInterwoven(
			(float) control->GetAxis(3) / resRot,
			(float) control->GetAxis(4) / resRot,
			(float) control->GetAxis(5) / resRot) * rotmat;
	rotmat.TranslateGlobal((float) control->GetAxis(0) / resMov,
			(float) control->GetAxis(1) / resMov,
			(float) control->GetAxis(2) / resMov);

	//rotmat.RotateXY(1,0,1);
	if(control->GetButton(0)){
		rotmat.SetIdentity();
		transmat.SetIdentity();
	}
	this->Refresh();
}
#endif

void OpenGLCanvas::OnMouseEvent(wxMouseEvent& event)
{
	if(event.ButtonDown(wxMOUSE_BTN_RIGHT)
			|| event.ButtonDown(wxMOUSE_BTN_MIDDLE)){
		x = event.m_x;
		y = event.m_y;
	}
	if(event.ButtonDClick(wxMOUSE_BTN_RIGHT)){
		rotmat = AffineTransformMatrix::Identity();
		transmat = AffineTransformMatrix::Identity();
		turntableX = 0;
		turntableY = M_PI / 2;
		x = event.m_x;
		y = event.m_y;
		this->Refresh();
	}

	if(event.Dragging() && event.RightIsDown()){
		switch(rotationMode){
		case rotateTrackball:
			{
				const double r = (double) ((w < h)? w : h) / 2.2;
				rotmat = AffineTransformMatrix::RotationTrackball(
						(double) (x - w / 2), (double) (h / 2 - y),
						(double) (event.m_x - w / 2),
						(double) (h / 2 - event.m_y), r) * rotmat;
				break;
			}
		case rotateInterwoven:
			{
				rotmat = AffineTransformMatrix::RotationXY(event.m_x - x,
						event.m_y - y, 0.5) * rotmat;
				break;
			}
		case rotateTurntable:
			{
				rotmat = AffineTransformMatrix::RotationAroundVector(
						Vector3(1, 0, 0), -M_PI / 2);
				turntableX += (double) (event.m_x - x) / 100;
				turntableY += (double) (event.m_y - y) / 100;
				rotmat = AffineTransformMatrix::RotationAroundVector(
						Vector3(1, 0, 0), turntableY) * rotmat;
				rotmat = rotmat
						* AffineTransformMatrix::RotationAroundVector(
								Vector3(0, 0, 1), turntableX);
				break;
			}
		}
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}

	if(event.Dragging() && event.MiddleIsDown()){
		float movement = 1.0;
		if(unitAtOrigin > 1.0) movement = unitAtOrigin;
		const float dx = (float) (event.m_x - x) / movement;
		const float dy = (float) (event.m_y - y) / movement;
		rotmat.TranslateGlobal(dx, -dy, 0);
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}else{
		const int x = event.GetWheelRotation();
		if(x != 0){
			scale *= exp(-((float) x) / 1000.0);
			// rotmat.TranslateGlobal(0, 0, (float) -x / 1000.0);
			this->Refresh();
		}
	}

	if(event.Moving() || event.Dragging()) event.Skip();
}

void OpenGLCanvas::Init(void)
{
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
#if defined (__WIN32__)
	glEnable(GL_NORMALIZE);
#else
	glEnable(GL_RESCALE_NORMAL);
#endif
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Scaling for point clouds
	//	glMatrixMode(GL_PROJECTION);
	//	glFrustum( -0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
	// Is done in OnSize(...)
	//	GLfloat attenuation[] =
	//		{1.0f, -0.01f, -.000001f};
	//glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation, 0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ZERO); // disable alpha blending

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_LIGHTING);

	Light0.SetAmbient(0.2, 0.2, 0.2);
	Light0.SetDiffuse(0.6, 0.6, 0.6);
	Light0.SetSpecular(0.95, 0.95, 0.95);
	Light0.SetPosition(1, 0.4, 1);
	Light0.Enable();
	Light0.Update();
	Light0.moveWithCamera = true;

}
void OpenGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if(!IsShown()) return;
	wxPaintDC(this); // Set the clipping for this area

//#ifndef __WXMOTIF__
//	if(!GetContext()) return;
//#endif

	if(context == NULL){
		context = new Context(this);
		context->SetCurrent(*this); // Link OpenGL to this area
		Init();
	}
	context->SetCurrent(*this); // Link OpenGL to this area

	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)

	GetClientSize(&w, &h);
	glViewport(0, 0, (GLint) w, (GLint) h);

	//	float specReflection[] = { 0.8f, 0.0f, 0.8f, 1.0f };
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
	//	glMateriali(GL_FRONT, GL_SHININESS, 96);

	// Clear color and depth buffers
	glEnable(GL_COLOR_MATERIAL);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Background

	if(stereoMode == stereoAnaglyph){
		glEnable(GL_COLOR_MATERIAL);
		glColor3ub(backgroundGrayLevel, backgroundGrayLevel,
				backgroundGrayLevel);
		glDisable(GL_COLOR_MATERIAL);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glNormal3b(0, 0, 1);
	glBegin(GL_QUADS);
	glColor3ub(50, 50, 50);
	glVertex2i(1, 1);
	glVertex2i(0, 1);
	glColor3ub(50, 50, 255);
	glVertex2i(0, 0);
	glVertex2i(1, 0);
	glEnd();

	// Clear the depth buffer bit again. Now the rest of the
	// image is always painted in front of the background.
	glClear( GL_DEPTH_BUFFER_BIT);
//	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble ar = (GLdouble) w / (GLdouble) h; // Calculate perspective
	gluPerspective(45, ar, 0.01, 10);
	glMatrixMode(GL_MODELVIEW);

	glCullFace(GL_BACK);
	glLoadIdentity();

	if(stereoMode == stereoAnaglyph){
		glColorMask((leftEyeR == 0)? GL_FALSE : GL_TRUE,
				(leftEyeG == 0)? GL_FALSE : GL_TRUE,
				(leftEyeB == 0)? GL_FALSE : GL_TRUE, GL_TRUE);
		glEnable(GL_COLOR_MATERIAL);
		glColor3ub(leftEyeR, leftEyeG, leftEyeB);
		glDisable(GL_COLOR_MATERIAL);
	}
	if(stereoMode == stereoShutter){
		glDrawBuffer(GL_BACK_LEFT);
	}

	if(stereoMode != stereoOff){
		glRotatef(atan(eyeDistance / 2 / focalDistance) * 180.0 / M_PI, 0, 1,
				0);
		glTranslatef(eyeDistance / 2, 0, 0);
	}

	glTranslatef(0.0, 0.0, -focalDistance);
	glScalef(scale, scale, scale);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX1, winY1, winZ1;
	GLdouble winX2, winY2, winZ2;
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev( GL_PROJECTION_MATRIX, projection);
	glGetIntegerv( GL_VIEWPORT, viewport);
	gluProject(0, 0, 0, modelview, projection, viewport, &winX1, &winY1,
			&winZ1);
	gluProject(1, 0, 0, modelview, projection, viewport, &winX2, &winY2,
			&winZ2);
	unitAtOrigin = winX2 - winX1;

	glMultMatrixd(rotmat.a);
	glMultMatrixd(transmat.a);
	//	if(m_gllist == 0){
	//		m_gllist = glGenLists(1); // Make one (1) empty display list.
	//		glNewList(m_gllist, GL_COMPILE_AND_EXECUTE);

	Light0.Update(true);
	Render();

	//		glEndList();
	//	}else{
	//		glCallList(m_gllist);
	//	}

	if(stereoMode != stereoOff){
		glCullFace(GL_BACK);
		glLoadIdentity();
	}

	if(stereoMode == stereoAnaglyph){
		glColorMask((rightEyeR == 0)? GL_FALSE : GL_TRUE,
				(rightEyeG == 0)? GL_FALSE : GL_TRUE,
				(rightEyeB == 0)? GL_FALSE : GL_TRUE, GL_TRUE);
		glEnable(GL_COLOR_MATERIAL);
		glColor3ub(rightEyeR, rightEyeG, rightEyeB);
		glDisable(GL_COLOR_MATERIAL);
	}
	if(stereoMode == stereoShutter){
		glDrawBuffer(GL_BACK_RIGHT);
	}

	if(stereoMode != stereoOff){
		glClear(GL_DEPTH_BUFFER_BIT);
		glRotatef(-atan(eyeDistance / 2 / focalDistance) * 180.0 / M_PI, 0, 1,
				0);
		glTranslatef(-eyeDistance / 2, 0, 0);
		glTranslatef(0.0, 0.0, -focalDistance);
		glScalef(scale, scale, scale);
		glMultMatrixd(rotmat.a);
		glMultMatrixd(transmat.a);
		Light0.Update(true);
		Render();
		//glCallList(m_gllist);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	glFlush();
	SwapBuffers();

}
#ifdef _USE_3DPICKING
bool OpenGLCanvas::OnPick(OpenGLPick &result, int x, int y)
{
	return this->OnPick(result, wxPoint(x, y));
}

bool OpenGLCanvas::OnPick(OpenGLPick &result, wxPoint pos)
{
	if(!IsShown()) return false;
	//TODO: Test if needed:
	//wxClientDC(this); // Set the clipping for this area

//#ifndef __WXMOTIF__
//	if(!GetContext()) return false;
//#endif

	if(context == NULL) context = new Context(this);
	context->SetCurrent(*this); // Link OpenGL to this area
//	if(!isInitialized){
//		InitGL(); // Init OpenGL once, but after SetCurrent
//		isInitialized = true;
//	}
	int w, h;
	GetClientSize(&w, &h);
	glViewport(0, 0, (GLint) w, (GLint) h);

	glClear(GL_DEPTH_BUFFER_BIT);

	glSelectBuffer(result.GetBufferSize(), result.GetBuffer());
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0); // This value ends up as the label for the background.

	glMatrixMode(GL_PROJECTION);
	glCullFace(GL_BACK);
	glLoadIdentity();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(pos.x, viewport[3] - pos.y, 1, 1, viewport);

	GLdouble ar = (GLdouble) w / (GLdouble) h; // Calculate perspective
	gluPerspective(45, ar, 0.01, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -focalDistance);
	glScalef(scale, scale, scale);
	glMultMatrixd(rotmat.a);
	glMultMatrixd(transmat.a);

	RenderPick();
	glFlush();
	GLuint hits = glRenderMode(GL_RENDER);
	result.SetHits(hits);
	return (hits > 0);
}
#endif

void OpenGLCanvas::RenderPick(void)
{
	this->Render();
}

void OpenGLCanvas::Render()
{
	glPushMatrix();

	GLfloat x = 1.0;
	GLfloat y = 0.5;
	GLfloat z = 2.0;

	GLfloat t = sqrt(x * x + y * y + z * z);
	GLfloat nx = x / t;
	GLfloat ny = y / t;
	GLfloat nz = z / t;

	glBegin(GL_QUADS);
	glNormal3f(nx, ny, nz);
	glVertex3f(x, y, z);
	glNormal3f(nx, -ny, nz);
	glVertex3f(x, -y, z);
	glNormal3f(nx, -ny, -nz);
	glVertex3f(x, -y, -z);
	glNormal3f(nx, ny, -nz);
	glVertex3f(x, y, -z);

	glNormal3f(-nx, ny, nz);
	glVertex3f(-x, y, z);
	glNormal3f(-nx, ny, -nz);
	glVertex3f(-x, y, -z);
	glNormal3f(-nx, -ny, -nz);
	glVertex3f(-x, -y, -z);
	glNormal3f(-nx, -ny, nz);
	glVertex3f(-x, -y, z);

	glNormal3f(nx, ny, nz);
	glVertex3f(x, y, z);
	glNormal3f(nx, ny, -nz);
	glVertex3f(x, y, -z);
	glNormal3f(-nx, ny, -nz);
	glVertex3f(-x, y, -z);
	glNormal3f(-nx, ny, nz);
	glVertex3f(-x, y, z);

	glNormal3f(nx, -ny, nz);
	glVertex3f(x, -y, z);
	glNormal3f(-nx, -ny, nz);
	glVertex3f(-x, -y, z);
	glNormal3f(-nx, -ny, -nz);
	glVertex3f(-x, -y, -z);
	glNormal3f(nx, -ny, -nz);
	glVertex3f(x, -y, -z);

	glNormal3f(nx, ny, nz);
	glVertex3f(x, y, z);
	glNormal3f(-nx, ny, nz);
	glVertex3f(-x, y, z);
	glNormal3f(-nx, -ny, nz);
	glVertex3f(-x, -y, z);
	glNormal3f(nx, -ny, nz);
	glVertex3f(x, -y, z);

	glNormal3f(nx, ny, -nz);
	glVertex3f(x, y, -z);
	glNormal3f(nx, -ny, -nz);
	glVertex3f(x, -y, -z);
	glNormal3f(-nx, -ny, -nz);
	glVertex3f(-x, -y, -z);
	glNormal3f(-nx, ny, -nz);
	glVertex3f(-x, y, -z);

	glEnd();

	glPopMatrix();
}

