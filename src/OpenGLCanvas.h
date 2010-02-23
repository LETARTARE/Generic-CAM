/*
 * OpenGLCanvas.h
 *
 *  Created on: 13.09.2008
 *      Author: Tobias Schaefer
 */

#ifndef OPENGLCANVAS_H_
#define OPENGLCANVAS_H_

#include "StdInclude.h"
#include "Config.h"
#include "AffineTransformMatrix.h"
#include "controller/Control3D.h"
#include <wx/glcanvas.h>

class OpenGLCanvas:public wxGLCanvas {
	//friend class ChildFrame;
	// Constructor / Destructor
public:
	OpenGLCanvas(wxWindow *parent,
			wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = 0,
			const wxString& name = _T("OpenGLCanvas"));
	virtual ~OpenGLCanvas();

	// Member Variables
public:

private:
	bool isInitialized;
	GLuint m_gllist;

	AffineTransformMatrix rotmat;
	Control3D* control;
	wxTimer timer;
	int x,y;

	unsigned char stereoMode;


	// Methods

public:
	void SetController(Control3D *control);

	virtual void Render();
	virtual void InitGL();
	virtual void SetupLighting();

	// ?
	//void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	//void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);



protected:
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
    void OnMouseEvent(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif /* OPENGLCANVAS_H_ */
