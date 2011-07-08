///////////////////////////////////////////////////////////////////////////////
// Name               : ToolPath.h
// Purpose            : Describing the boundary of the volume to be cut away.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.03.2010
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


#include "ToolPath.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfToolPath)

#include <wx/log.h>
#include <GL/gl.h>

ToolPath::ToolPath()
{
	colorMoving.Set(0.3, 0.8, 0.3);
	colorCutting.Set(0.8, 0.3, 0.3);
}

ToolPath::~ToolPath()
{
}

void ToolPath::Paint(void)
{

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_LINE_STRIP);
	::glNormal3f(0, 0, 1);
	size_t i;
	for(i = 0; i < positions.GetCount(); i++){

		if(positions[i].isCutting)
			::glColor3f(colorCutting.x, colorCutting.y, colorCutting.z);
		else
			::glColor3f(colorMoving.x, colorMoving.y, colorMoving.z);

		::glVertex3f(positions[i].axisX, positions[i].axisY, positions[i].axisZ);
	}

	::glEnd();
	::glPopMatrix();
}
