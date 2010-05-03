///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.h
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


#ifndef OPENGLCANVAS_H_
#define OPENGLCANVAS_H_

#include "../StdInclude.h"
#include "../Config.h"
#include "AffineTransformMatrix.h"
#include "../controller/Control3D.h"
#include <wx/glcanvas.h>

/*!\class OpenGLCanvas
 * \brief Extending wxGLCanvas with some useful features.
 *
 *
 */
class OpenGLCanvas:public wxGLCanvas {
	//friend class ChildFrame;
	// Constructor / Destructor
public:
	OpenGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0, const wxString& name =
					_T("OpenGLCanvas"));
	virtual ~OpenGLCanvas();

	// Member Variables
public:
	unsigned char stereoMode;

private:
	bool isInitialized;
	GLuint m_gllist;

	AffineTransformMatrix rotmat;
	AffineTransformMatrix transmat;
	Control3D* control;
	wxTimer timer;
	int x, y;

	// Methods

public:
	void SetController(Control3D& control);

	virtual void Render();
	virtual void InitGL();
	virtual void SetupLighting();

	// ?
	//void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	//void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);


protected:
	void OnPaint(wxPaintEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnMouseEvent(wxMouseEvent& event);
	void OnTimer(wxTimerEvent& event);

DECLARE_EVENT_TABLE()
};

#endif /* OPENGLCANVAS_H_ */
