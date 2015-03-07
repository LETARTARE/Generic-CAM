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
	modified = false;
	hasRunningGenerator = false;
}

Workpiece::Workpiece(const StockMaterial &material) :
		StockMaterial(material)
{
	selected = false;
	modified = false;
	hasRunningGenerator = false;
	box.SetSize(material.sx, material.sy, material.sz);
}

Workpiece::~Workpiece()
{
}

void Workpiece::Paint(const ArrayOfObject &objects) const
{

	AffineTransformMatrix tempMatrix;

	for(size_t j = 0; j < placements.GetCount(); j++){
		size_t objNr = placements[j].objectNr;

		float x = placements[j].matrix.a[12];
		float y = placements[j].matrix.a[13];
		float z = placements[j].matrix.a[14];

		tempMatrix = AffineTransformMatrix::Identity();
		tempMatrix.TranslateLocal(-placements[j].bbox.xmin,
				-placements[j].bbox.ymin, -placements[j].bbox.zmin);
		tempMatrix.TranslateLocal(x, y, z);
		tempMatrix *= placements[j].matrix;

		::glPushMatrix();
		::glMultMatrixd(tempMatrix.a);
		objects[objNr].Paint();
		::glPopMatrix();
		placements[j].outline.matrix.a[12] = x;
		placements[j].outline.matrix.a[13] = y;
		placements[j].outline.matrix.a[14] = 0;
		placements[j].outline.Paint();
	}

//	if(glIsEnabled(GL_COLOR_MATERIAL)){
//		glColor3f(color.x, color.y, color.z);
//		box.Paint();
//		StockMaterial::Paint(0.2, false);
//	}else{
//		box.Paint();
//		StockMaterial::PaintWireBox();
//	}

}

void Workpiece::Update(ArrayOfObject& objects)
{
	box.SetSize(sx, sy, sz);

	for(size_t j = 0; j < placements.GetCount(); j++){
		placements[j].Update(objects);

		float x = placements[j].matrix.a[12];
		float y = placements[j].matrix.a[13];
		float d = placements[j].slotWidth;

		box -= BooleanBox(x - d, y - d, 0,
				x + placements[j].bbox.GetSizeX() + d,
				y + placements[j].bbox.GetSizeY() + d, sz);
	}
}

void Workpiece::SortTargets(void)
{
//	size_t i, j;
//	double dmin, d;
//	Polygon25 temp, temp2;
//
//	for(i = 0; i < placements.GetCount(); i++){
//		if(placements[i].isMovable){
//			wxLogMessage(wxString::Format(_T("Moving Target %u:"), i));
//
//			temp = placements[i].outLine;
//			temp.ApplyTransformation(placements[i].matrix);
//
//			dmin = +DBL_MAX;
//			for(j = i; j > 0; j--){
//				temp2 = placements[j - 1].outLine;
//				temp2.ApplyTransformation(placements[j - 1].matrix);
//				d = temp.DistanceToPolygon(temp2, -1.0, 0.0);
//				if(d < dmin){
//					dmin = d;
//
//					wxLogMessage(wxString::Format(
//							_T("To Target %u: d= %.3f m"), j - 1, d));
//				}
//			}
//			if(dmin < 1.0){
//				placements[i].matrix.TranslateGlobal(-dmin, 0.0, 0.0);
//			}
//		}
//	}

}
void Workpiece::ToStream(wxTextOutputStream& stream)
{
	stream << _T("Stockmaterial:") << endl;
	StockMaterial::ToStream(stream);
	stream << _T("Placements: ");
	stream << wxString::Format(_T("%u"), placements.GetCount());
	stream << endl;
	size_t n;
	for(n = 0; n < placements.GetCount(); n++){
		placements[n].ToStream(stream);
	}

}

bool Workpiece::FromStream(wxTextInputStream& stream)
{
	wxString temp = stream.ReadLine();
	if(temp.Cmp(_T("Stockmaterial:")) != 0) return false;
	bool flag = StockMaterial::FromStream(stream);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Placements:")) != 0) return false;
	size_t N = stream.Read32();
	size_t n;
	flag = true;
	ObjectPlacement placement;
	placements.Clear();
	for(n = 0; n < N; n++){
		flag = placement.FromStream(stream);
		if(!flag) break;
		placements.Add(placement);
	}
	return flag;
}
