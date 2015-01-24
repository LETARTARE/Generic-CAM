///////////////////////////////////////////////////////////////////////////////
// Name               : MainCanvas.h
// Purpose            : Main 3D display
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MAINCANVAS_H_
#define MAINCANVAS_H_

/*!\class MainCanvas
 * \brief Main 3D display
 */

#include "../3D/OpenGLCanvas.h"
#include "../project/Project.h"

class MainCanvas:public OpenGLCanvas {
	// Constructor / Destructor
public:
	MainCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			0, const wxString& name = _T(""));
	virtual ~MainCanvas();

	// Member Variables
private:

	Project* project;

	Geometry* geometry;
	Machine* machine;

	bool displayCoordinateSystem;

	// Methods
public:
	void InsertProject(Project* project);
	void InsertMachine(Machine* machine);
	void InsertGeometry(Geometry* geometry);

	void RenderCoordinateSystem(AffineTransformMatrix *matrix = NULL);
	void Render();
};

#endif /* MAINCANVAS_H_ */
