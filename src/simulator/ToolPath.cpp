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
WX_DEFINE_OBJARRAY(ArrayOfGtsVertex)
WX_DEFINE_OBJARRAY(ArrayOfGtsEdge)

ToolPath::ToolPath()
{

}

ToolPath::~ToolPath()
{
}

void ToolPath::Generate(Tool const& tool,
		AffineTransformMatrix const& position1,
		AffineTransformMatrix const& position2)
{
	this->Clear();

	ArrayOfGtsVertex vert;
	ArrayOfGtsEdge edge;

	unsigned int i;
	unsigned int N;
	unsigned int object = 0;
	for(i = 0; i < tool.contour.Count(); i++){

	}


	//	unsigned int i, j;
	//
	//		float ss[resolution + 1], cc[resolution + 1];
	//		for(i = 0; i <= resolution; i++){
	//			ss[i] = sin(2* M_PI / resolution * i);
	//			cc[i] = cos(2* M_PI / resolution * i);
	//		}
	//
	//		for(i = 0; i < contour.Count(); i++){
	//			::glBegin(GL_QUAD_STRIP);
	//			for(j = 0; j <= resolution; j++){
	//				::glNormal3f(cc[j] * contour[i].n1.x, ss[j] * contour[i].n1.x,
	//						contour[i].n1.z);
	//				::glVertex3f(cc[j] * contour[i].p1.x, ss[j] * contour[i].p1.x,
	//						contour[i].p1.z);
	//				::glNormal3f(cc[j] * contour[i].n2.x, ss[j] * contour[i].n2.x,
	//						contour[i].n2.z);
	//				::glVertex3f(cc[j] * contour[i].p2.x, ss[j] * contour[i].p2.x,
	//						contour[i].p2.z);
	//			}
	//			::glEnd();
	//		}

}

