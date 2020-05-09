///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasTool.cpp
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

#include "CanvasTool.h"
#include "../Config.h"

CanvasTool::CanvasTool(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
		OpenGLCanvas(parent, id, pos, size, style, name)
{
	tool = NULL;
}

CanvasTool::~CanvasTool()
{
}

void CanvasTool::InsertTool(Tool& t)
{
	tool = &t;
#ifdef _DEBUGMODE
	if(tool != NULL){
//		debug.SetupTool(*tool, 0.0001, 0.0001);
//		debug.NegateZ();
//		debug.displayField = true;
	} else{
//		debug.displayField = false;
	}
#endif
}

void CanvasTool::Render()
{
	if(tool == NULL) return;
	float scaleFactor = 5.0;

//#if defined (__WIN32__)
//	::glEnable(GL_NORMALIZE);
//#else
//	::glEnable( GL_RESCALE_NORMAL);
//#endif

	glScalef(scaleFactor, scaleFactor, scaleFactor);
	glColor3f(0.7, 0.7, 0.7);
	glRotatef(-90, 1, 0, 0);

	glTranslatef(0, 0, -(tool->GetFullLength() / 2.0));
	tool->Paint();
#ifdef _DEBUGMODE
//		if(debug.displayField){
//			glPushMatrix();
//			glTranslatef(0.01 + tool->GetMaxDiameter(), -debug.GetSizeY() / 2,
//					tool->GetToolLength());
//			debug.Paint();
//			glPopMatrix();
//		}
#endif

//#if defined (__WIN32__)
//	::glDisable(GL_NORMALIZE);
//#else
//	::glDisable(GL_RESCALE_NORMAL);
//#endif

}
