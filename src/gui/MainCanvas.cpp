///////////////////////////////////////////////////////////////////////////////
// Name               : MainCanvas.cpp
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "MainCanvas.h"

MainCanvas::MainCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
	OpenGLCanvas(parent, id, pos, size, style, name)
{
	machine = NULL;
	geometry = NULL;
	stockMaterial = NULL;
}

MainCanvas::~MainCanvas()
{
}

void MainCanvas::InsertMachine(Machine* machine)
{
	this->machine = machine;
}
void MainCanvas::InsertGeometry(ArrayOfGeometry* geometry)
{
	this->geometry = geometry;
}

void MainCanvas::InsertStockMaterial(StockMaterial* stockMaterial)
{
	this->stockMaterial = stockMaterial;
}

void MainCanvas::RenderCoordinateSystem(void)
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

void MainCanvas::Render()
{
	RenderCoordinateSystem();
	if(machine != NULL && machine->IsInitialized()) machine->Paint();
	if(geometry != NULL) {
		size_t i;
		for(i=0;i<geometry->GetCount();i++)
		geometry->Item(i).Paint();
	}
	if(stockMaterial != NULL) stockMaterial->Paint();
}
