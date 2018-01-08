///////////////////////////////////////////////////////////////////////////////
// Name               : ObjectPlacement.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 20.07.2011
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

#include "ObjectPlacement.h"

#include "../project/Project.h"

#include <GL/gl.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfObjectPlacement)

ObjectPlacement::ObjectPlacement()
{
	parent = NULL;
	refObject = 0;
	selected = false;
//	modified = false;
//	isMovable = true;
//	isKeepout = false;
//	objectNr = 0;

	cornerX = 0;
	cornerY = 0;

	useContour = false;
	slotWidth = 0.01; // 1 cm

}

ObjectPlacement::~ObjectPlacement()
{
}

void ObjectPlacement::Clear(void)
{
	refObject = 0;
	slotWidth = 0.01;
	matrix.SetIdentity();

	outline.Clear();

//	isMovable = true;
//	isKeepout = false;
}

void ObjectPlacement::Update(void)
{
	BoundingBox::Clear();

	const Workpiece * wp = parent;
	if(wp == NULL) return;
	const Project * pr = wp->parent;
	if(pr == NULL) return;

	if(refObject >= pr->objects.GetCount()) return;

//	outline.Clear();
	for(size_t n = 0; n < pr->objects[refObject].geometries.GetCount(); n++){
		BoundingBox::Insert(pr->objects[refObject].geometries[n],
				matrix * pr->objects[refObject].matrix);
	}

	const float dx = cornerX - xmin;
	const float dy = cornerY - ymin;

	matrix.TranslateGlobal(dx, dy, 0);
	xmin += dx;
	xmax += dx;
	ymin += dy;
	ymax += dy;

	xmin -= slotWidth;
	ymin -= slotWidth;
//	zmin -= slotWidth;
	xmax += slotWidth;
	ymax += slotWidth;
//	zmax += slotWidth;

//	outline.InsertPoint(0, 0, 0);
//	outline.InsertPoint(bbox.GetSizeX(), 0, 0);
//	outline.InsertPoint(bbox.GetSizeX(), bbox.GetSizeY(), 0);
//	outline.InsertPoint(0, bbox.GetSizeY(), 0);
//	outline.Close();
}

void ObjectPlacement::ToStream(wxTextOutputStream& stream)
{
	stream << _T("ObjectRef: ");
	stream << wxString::Format(_T("%zu"), refObject);
	stream << endl;
	stream << _T("Matrix: ");
	matrix.ToStream(stream);
	stream << endl;
	stream << _T("Corner: ") << cornerX << _T(" ") << cornerY << endl;
	stream << _T("Parameter: ");
	stream << slotWidth << _T(" ");
	stream << (useContour? 1 : 0) << _T(" ");
//	stream << (isMovable? 1 : 0) << _T(" ");
//	stream << (isKeepout? 1 : 0);
	stream << endl;
}

bool ObjectPlacement::FromStream(wxTextInputStream& stream)
{
	wxString temp;
	temp = stream.ReadWord();
	if(temp.Cmp(_T("ObjectRef:")) != 0) return false;
	refObject = stream.Read32S();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Matrix:")) != 0) return false;
	matrix.FromStream(stream);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Corner:")) != 0) return false;
	stream >> cornerX;
	stream >> cornerY;
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Parameter:")) != 0) return false;
	stream >> slotWidth;
	useContour = (stream.Read8() == 1);
//	isMovable = (stream.Read8() == 1);
//	isKeepout = (stream.Read8() == 1);
	return true;
}

//void ObjectPlacement::SetKeepout(double x, double y, double sizex, double sizey)
//{
//	matrix.SetIdentity();
//	matrix.TranslateGlobal(x, y, 0.0);
//	outline.Clear();
//	outline.InsertPoint(0.0, 0.0, 0.0);
//	outline.InsertPoint(sizex, 0.0, 0.0);
//	outline.InsertPoint(sizex, sizey, 0.0);
//	outline.InsertPoint(0.0, sizey, 0.0);
//	outline.Close();
//	isMovable = false;
//	isKeepout = true;
//}

//void ObjectPlacement::Paint(void) const
//{
//	::glPushMatrix();
//	::glMultMatrixd(matrix.a);
//	outline.Paint();
//	::glPopMatrix();
//}
