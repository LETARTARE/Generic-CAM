///////////////////////////////////////////////////////////////////////////////
// Name               : ToolCanvas.cpp
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "ToolCanvas.h"

ToolCanvas::ToolCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	tool = NULL;

}

ToolCanvas::~ToolCanvas()
{
}

void ToolCanvas::InsertTool(Tool& t)
{
	tool = &t;
}

void ToolCanvas::RenderCoordinateSystem(void)
{
	glBegin(GL_LINES);

	glColor3b(255, 0, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3b(0, 255, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(0, -1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);

	glColor3b(0, 0, 255);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -1);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);

	glEnd();
}

void ToolCanvas::Render()
{
	float scaleFactor = 50.0;
	RenderCoordinateSystem();
	::glEnable(GL_RESCALE_NORMAL);
	::glScalef(scaleFactor, scaleFactor, scaleFactor);
	if(tool != NULL) tool->Paint();
	::glDisable(GL_RESCALE_NORMAL);
}
