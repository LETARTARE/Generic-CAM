///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasTool.h
// Purpose            : 3D Display of a tool.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   : -lopengl32 -lglu
// Author             : Tobias Schaefer
// Created            : 17.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef TOOLCANVAS_H_
#define TOOLCANVAS_H_

#include "../StdInclude.h"
#include "../project/Tool.h"
//#include "../project/generator/DexelTarget.h"
#include "../3D/OpenGLCanvas.h"

class CanvasTool:public OpenGLCanvas {
	// Constructor / Destructor
public:
	CanvasTool(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			0, const wxString& name = _T(""));
	virtual ~CanvasTool();

	// Member Variables
private:
	Tool* tool;
//	DexelTarget debug;
	// Methods
public:
	void InsertTool(Tool& t);
	void RenderCoordinateSystem(void);
	void Render();

};

#endif /* TOOLCANVAS_H_ */
