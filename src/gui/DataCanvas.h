//============================================================================
// Name        : DataCanvas.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef DATACANVAS_H_
#define DATACANVAS_H_

#include "../3D/OpenGLCanvas.h"
#include "../3D/Geometry.h"

class DataCanvas:public OpenGLCanvas {
public:
	DataCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0, const wxString& name =
					_T(""));

	Geometry *geometry;

	void InsertData(Geometry* data);
	virtual ~DataCanvas();
	void Render();
};

#endif /* DATACANVAS_H_ */
