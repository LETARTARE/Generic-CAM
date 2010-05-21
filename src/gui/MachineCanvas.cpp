///////////////////////////////////////////////////////////////////////////////
// Name               : MachineCanvas.cpp
// Purpose            : 3D Display of the machine.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   : -lopengl32 -lglu
// Author             : Tobias Schaefer
// Created            : 23.02.2010
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


#include "MachineCanvas.h"

MachineCanvas::MachineCanvas(wxWindow *parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style,
		const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	machine = NULL;
}

MachineCanvas::~MachineCanvas()
{
}

void MachineCanvas::InsertMachine(Machine& m)
{
	machine = &m;
}

void MachineCanvas::RenderCoordinateSystem(void)
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

void MachineCanvas::Render()
{
	RenderCoordinateSystem();
	if(machine != NULL) machine->Paint();
}

// This should happen in a derived class:
//void OpenGLCanvas::InsertGeometry(Document* doc)
//{
//	SetCurrent();
//	::glNewList(m_gllist, GL_COMPILE);
//
//	std::list <Geometry *>::iterator pg;
//	for(pg = doc->objectGeometry.begin(); pg != doc->objectGeometry.end(); ++pg){
//		(*pg)->Paint();
//	}
//	std::list <Source *>::iterator ps;
//	for(ps = doc->objectSource.begin(); ps != doc->objectSource.end(); ++ps){
//		(*ps)->Paint();
//	}
//	std::list <Connector *>::iterator pc;
//	for(pc = doc->objectConnector.begin(); pc != doc->objectConnector.end(); ++pc){
//		(*pc)->Paint();
//	}
//	std::list <Result *>::iterator pr;
//	for(pr = doc->objectResult.begin(); pr != doc->objectResult.end(); ++pr){
//		(*pr)->Paint();
//	}
//
//	::glEndList();
//}
