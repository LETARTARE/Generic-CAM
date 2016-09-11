///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasMain.cpp
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

#include "CanvasMain.h"

CanvasMain::CanvasMain(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
		OpenGLCanvas(parent, id, pos, size, style, name)
{
	displayCoordinateSystem = true;

	project = NULL;
	machine = NULL;
	geometry = NULL;
}

CanvasMain::~CanvasMain()
{
}

void CanvasMain::InsertProject(Project* project)
{
	this->project = project;
}
void CanvasMain::InsertMachine(Machine* machine)
{
	this->machine = machine;
}
void CanvasMain::InsertGeometry(Geometry* geometry)
{
	this->geometry = geometry;
}

void CanvasMain::RenderCoordinateSystem(AffineTransformMatrix *matrix)
{
	::glPushMatrix();
	if(matrix != NULL) ::glMultMatrixd(matrix->a);

	GLfloat s = 0.1;
	GLfloat n = sqrt(2.0);
	GLfloat d = s / 10;

	glBegin(GL_LINES);

	glColor3f(1.0, 0, 0);
	glNormal3f(-s, 0, 0);
	glVertex3f(-s, 0, 0);
	glNormal3f(s, 0, 0);
	glVertex3f(s, 0, 0);

	glNormal3f(n, n, 0);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, d, 0);
	glNormal3f(n, -n, 0);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, -d, 0);
	glNormal3f(n, 0, n);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, 0, d);
	glNormal3f(n, 0, -n);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, 0, -d);

	glColor3f(0, 1.0, 0);
	glNormal3f(0, -s, 0);
	glVertex3f(0, -s, 0);
	glNormal3f(0, s, 0);
	glVertex3f(0, s, 0);

	glNormal3f(n, n, 0);
	glVertex3f(0, s, 0);
	glVertex3f(d, s - d, 0);
	glNormal3f(-n, n, 0);
	glVertex3f(0, s, 0);
	glVertex3f(-d, s - d, 0);
	glNormal3f(0, n, n);
	glVertex3f(0, s, 0);
	glVertex3f(0, s - d, d);
	glNormal3f(0, n, -n);
	glVertex3f(0, s, 0);
	glVertex3f(0, s - d, -d);

	glColor3f(0, 0, 1.0);
	glNormal3f(0, 0, -s);
	glVertex3f(0, 0, -s);
	glNormal3f(0, 0, s);
	glVertex3f(0, 0, s);

	glNormal3f(n, 0, n);
	glVertex3f(0, 0, s);
	glVertex3f(d, 0, s - d);
	glNormal3f(-n, 0, n);
	glVertex3f(0, 0, s);
	glVertex3f(-d, 0, s - d);
	glNormal3f(0, n, n);
	glVertex3f(0, 0, s);
	glVertex3f(0, d, s - d);
	glNormal3f(0, -n, n);
	glVertex3f(0, 0, s);
	glVertex3f(0, -d, s - d);

	::glEnd();
	::glPopMatrix();
}

void CanvasMain::Render()
{
	if(displayCoordinateSystem) RenderCoordinateSystem();
	if(project != NULL) project->Paint();
	if(machine != NULL) machine->Paint();
	if(geometry != NULL) geometry->Paint();
}

