///////////////////////////////////////////////////////////////////////////////
// Name               : Workpiece.cpp
// Purpose            : The workpiece.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.03.2010
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

#include "Workpiece.h"

#include <GL/gl.h>
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfWorkpiece)

Workpiece::Workpiece()
{
	selected = false;
}

Workpiece::Workpiece(const StockMaterial &material) :
		StockMaterial(material)
{
	selected = false;
	box.SetSize(material.sx, material.sy, material.sz);
}

Workpiece::~Workpiece()
{
}

void Workpiece::Paint(const ArrayOfObject &objects) const
{

	AffineTransformMatrix tempMatrix;

	for(size_t j = 0; j < placements.GetCount(); j++){
		size_t objectNr = placements[j].objectNr;

		float x = placements[j].matrix.a[12];
		float y = placements[j].matrix.a[13];
		float d = placements[j].slotWidth;

		::glPushMatrix();
		::glMultMatrixd(placements[j].matrix.a);

		tempMatrix = AffineTransformMatrix::Identity();
		//				tempMatrix *= objects[objectNr].matrix;
		tempMatrix.TranslateGlobal(-objects[objectNr].bbox.xmin,
				-objects[objectNr].bbox.ymin, -objects[objectNr].bbox.zmin);
		::glMultMatrixd(tempMatrix.a);
		objects[objectNr].Paint();
		::glPopMatrix();
	}

	if(glIsEnabled(GL_COLOR_MATERIAL)){
		glColor3f(color.x, color.y, color.z);
		box.Paint();
		StockMaterial::Paint(0.2, false);
	}else{
		box.Paint();
		StockMaterial::PaintWireBox();
	}

}

void Workpiece::Refresh(ArrayOfObject& objects)
{
	box.SetSize(sx, sy, sz);

	for(size_t j = 0; j < placements.GetCount(); j++){
		size_t objectNr = placements[j].objectNr;

		float x = placements[j].matrix.a[12];
		float y = placements[j].matrix.a[13];
		float d = placements[j].slotWidth;

		box -= BooleanBox(x - d, y - d, 0,
				x + objects[objectNr].bbox.GetSizeX() + d,
				y + objects[objectNr].bbox.GetSizeY() + d, sz);
	}
}
