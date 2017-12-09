///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.h
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

#ifndef OPENGLCANVAS_H_
#define OPENGLCANVAS_H_

/*!\class OpenGLCanvas
 * \ingroup View3D
 * \brief Extended wxGLCanvas
 *
 * Provides features like:
 *  * Mouse movement
 *  * 6-DOF controller support
 *  * Object picking
 *  * Stereo 3D (Anaglyph- and Shutterglasses)
 */

#include "../Config.h"
#ifdef _USE_6DOFCONTROLLER
#include "../controller/Control3D.h"
#include <wx/timer.h>
#endif
#ifdef _USE_3DPICKING
#include "OpenGLPick.h"
#endif
#include "AffineTransformMatrix.h"
#include <wx/glcanvas.h>
#include <GL/gl.h>

enum Stereo3DType {
	stereoOff = 0, //!< No stereo effect
	stereoAnaglyph, //!< Stereoeffect using colored glasses
	stereoShutter //!< Stereoeffect using shutter-glasses
};

enum RotationType {
	rotateTrackball, //!< Use trackball style mouse control.
	rotateInterwoven, //!< Rotate around the object using interwoven mouse movements.
	rotateTurntable //!< Rotate the object like a turntable. X rotates always around the Z axis, while Y rotates around the X axis.
};

class OpenGLCanvas:public wxGLCanvas {
	// Constructor / Destructor
public:
	OpenGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0,
			const wxString& name = _T("OpenGLCanvas"));
	virtual ~OpenGLCanvas();

	// Member Variables
public:
	Stereo3DType stereoMode;
	float eyeDistance;
	float focalDistance;
	unsigned char backgroundGrayLevel;
	unsigned char rightEyeR;
	unsigned char rightEyeG;
	unsigned char rightEyeB;
	unsigned char leftEyeR;
	unsigned char leftEyeG;
	unsigned char leftEyeB;

	RotationType rotationMode;
	AffineTransformMatrix rotmat;
	AffineTransformMatrix transmat;

protected:
	float scale;
	float turntableX;
	float turntableY;
	float unitAtOrigin;

private:
	bool isInitialized;
	GLuint m_gllist;

#ifdef _USE_6DOFCONTROLLER
	Control3D* control; //!< Link to 6DOF-controller
	wxTimer timer; //!< Timer for polling the controller
#endif

	int x; //!< Startpoint for mouse dragging
	int y; //!< Startpoint for mouse dragging
	int w; //!< Width of viewport
	int h; //!< Height of viewport

	// Methods
public:
#ifdef _USE_6DOFCONTROLLER
	void SetController(Control3D& control);
#endif

	virtual void Render();
	virtual void InitGL();
	virtual void SetupLighting();

#ifdef _USE_3DPICKING
	bool OnPick(OpenGLPick &result, int x, int y);
	bool OnPick(OpenGLPick &result, wxPoint pos);
#endif
protected:

	void OnPaint(wxPaintEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnMouseEvent(wxMouseEvent& event);
#ifdef _USE_6DOFCONTROLLER
	void OnTimer(wxTimerEvent& event);
#endif
};

#endif /* OPENGLCANVAS_H_ */
