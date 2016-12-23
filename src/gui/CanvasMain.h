///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasMain.h
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

/*!\class CanvasMain
 * \brief Main 3D display
 *
 *
 */

#include "../project/Project.h"

#include "../3D/OpenGLCanvas.h"

class CanvasMain:public OpenGLCanvas {
	// Constructor / Destructor
public:
	CanvasMain(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			0, const wxString& name = _T(""));
	virtual ~CanvasMain();

	// Member Variables
public:
	enum DisplayType {
		displayObjects, displayWorkpieces, displayRun
	};

	bool displayCoordinateSystem;

	DisplayType display;

	bool displayGeometry;
	bool displayMachine;
	bool displayStock;
	bool displayBoundingBox;
	bool displayTargets;
	bool displayToolpath;
	bool displayOutLines;

	int selectedObject;
	int selectedWorkpiece;
	int selectedRun;

	// Experimental stuff:
	// OctreeGenerator octree;
	// Quadtree quadtree;

private:
	Project* project;

public:
	unsigned int c0; ///< Counter for debugging. Remove on release.

	// Methods
public:
	void InsertProject(Project* project);
	void Render();

private:
	void RenderCoordinateSystem(AffineTransformMatrix *matrix = NULL);
};

#endif /* MAINCANVAS_H_ */
