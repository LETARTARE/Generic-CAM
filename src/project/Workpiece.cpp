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

#include "Project.h"
#include <GL/gl.h>

Workpiece::Workpiece()
{
	parent = NULL;
	refObject = -1;
}

Workpiece::~Workpiece()
{
}

void Workpiece::Paint(void) const
{
//	AffineTransformMatrix tempMatrix;

	const Project* project = this->parent;
	if(project == NULL) return;
	glPushMatrix();
//	this->matrix.GLMultMatrix();

//	for(size_t j = 0; j < placements.GetCount(); j++){
////		const float x = placements[j].matrix.a[12];
////		const float y = placements[j].matrix.a[13];
////		const float z = placements[j].matrix.a[14];
////
////		tempMatrix = AffineTransformMatrix::Identity();
////		tempMatrix.TranslateLocal(-placements[j].box.xmin,
////				-placements[j].box.ymin, -placements[j].box.zmin);
////		tempMatrix.TranslateLocal(x, y, z);
////		tempMatrix *= placements[j].matrix;
//
//		ObjectPlacement* obpl = &(placements[j]);
//		Object* obj = &(project->objects[obpl->refObject]);
//		if(obj != NULL){
//			glPushMatrix();
//			obpl->matrix.GLMultMatrix();
//			obj->Paint(false);
//			glPopMatrix();
//		}
////		placements[j].outline.matrix.a[12] = x;
////		placements[j].outline.matrix.a[13] = y;
////		placements[j].outline.matrix.a[14] = 0;
////		placements[j].outline.Paint();
//
//	}

	glColor3f(color.x, color.y, color.z);
	if(glIsEnabled(GL_COLOR_MATERIAL)){
//		BoundingBox::Paint();
//		StockMaterial::Paint(0.2, false);
	}else{
//		BoundingBox::Paint();
//		StockMaterial::PaintWireBox();
	}

	//	BoundingBox::Paint();
//	if(refObject >= 0 && refObject < project->objects.GetCount()){
//		glColor4f(0.5, 0.5, 0.5, 0.5);
//		//		BoundingBox::Paint();
//		project->objects[refObject].Paint(false, geometryColorNone);
//	}else{
//		glColor4f(0.5, 0.5, 0.5, 1.0);
//		bbox.Paint();
//	}

	::glPopMatrix();
}

//void Workpiece::Update(void)
//{
//	const Project* project = this->parent;
//	if(project == NULL) return;
//
//	if(refObject >= 0 && refObject < project->objects.GetCount()){
//		SetSize(project->objects[refObject].bbox.GetSizeX(),
//				project->objects[refObject].bbox.GetSizeY(),
//				project->objects[refObject].bbox.GetSizeZ());
//		for(size_t j = 0; j < placements.GetCount(); j++){
//			placements[j].parent = this;
//			placements[j].Update();
//		}
//	}else{
//		bbox.SetSize(GetSizeX(), GetSizeY(), GetSizeZ());
//		for(size_t j = 0; j < placements.GetCount(); j++){
//			placements[j].parent = this;
//			placements[j].Update();
//			bbox -= BooleanBox(placements[j].xmin, placements[j].ymin, 0,
//					placements[j].xmax, placements[j].ymax, GetSizeZ());
//		}
//	}
//
//}

//void Workpiece::SortTargets(void)
//{
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
//}

//void Workpiece::ToStream(wxTextOutputStream& stream)
//{
//	stream << _T("Name:") << endl;
//	stream << name << endl;
//	stream << wxString::Format(_T("ObjectRef: %i"), refObject) << endl;
//	stream << _T("Matrix: ");
//	matrix.ToStream(stream);
//	stream << endl;
//	BoundingBox::ToStream(stream);
//	stream << _T("Placements: ");
//	stream << wxString::Format(_T("%zu"), placements.GetCount());
//	stream << endl;
//	for(size_t n = 0; n < placements.GetCount(); n++)
//		placements[n].ToStream(stream);
//}
//
//bool Workpiece::FromStream(wxTextInputStream& stream)
//{
////	wxString temp = stream.ReadLine();
////	if(temp.Cmp(_T("Stockmaterial:")) != 0) return false;
////	bool flag = StockMaterial::FromStream(stream);
//	wxString temp;
//	temp = stream.ReadLine();
//	if(temp.Cmp(_T("Name:")) != 0) return false;
//	name = stream.ReadLine();
//	temp = stream.ReadWord();
//	if(temp.Cmp(_T("ObjectRef:")) != 0) return false;
//	refObject = stream.Read32S();
//	temp = stream.ReadWord();
//	if(temp.Cmp(_T("Matrix:")) != 0) return false;
//	matrix.FromStream(stream);
//	BoundingBox::FromStream(stream);
//	temp = stream.ReadWord();
//	if(temp.Cmp(_T("Placements:")) != 0) return false;
//	size_t N = stream.Read32();
//	ObjectPlacement placement;
//	placements.Clear();
//	for(size_t n = 0; n < N; n++){
//		if(!placement.FromStream(stream)) return false;
//		placements.Add(placement);
//	}
//	return true;
//}
//
//Vector3 Workpiece::GetCenter(void) const
//{
//	Vector3 temp;
//	temp.x = (this->xmin + this->xmax) / 2.0;
//	temp.y = (this->ymin + this->ymax) / 2.0;
//	temp.z = this->zmin;
//	return temp;
//}
//
//void Workpiece::PrepareModel(void)
//{
////	BoundingBox tempArea = *workpiece;
////	tempArea.Transform(workpiecePlacement);
//	assert(parent!=NULL);
//
//	model.SetupBox(this->GetSizeX(), this->GetSizeY(), this->GetSizeZ(),
//			parent->resX, parent->resY);
//
//	if(refObject < 0 || refObject >= parent->objects.GetCount()){
//		// Provide a simple box.
//		model.Fill();
//	}else{
//		const Object* wpObject = &(parent->objects[refObject]);
//
//		AffineTransformMatrix tempMatrix;
//		tempMatrix.TranslateGlobal(-this->xmin, -this->ymin, -this->zmin);
////		tempMatrix *= workpiecePlacement;
//
//		model.InitImprinting();
//		model.InsertObject(*wpObject, tempMatrix);
//		model.FinishImprint();
//	}
//}
