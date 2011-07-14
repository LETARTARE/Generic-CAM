///////////////////////////////////////////////////////////////////////////////
// Name               : ObjectFrame.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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


#include "ObjectFrame.h"
#include <math.h>

ObjectFrame::ObjectFrame(wxWindow* parent) :
	GUIObjectFrame(parent)
{
	linkedProject = NULL;

}

ObjectFrame::~ObjectFrame()
{
}

void ObjectFrame::InsertProject(Project *project)
{
	linkedProject = project;
	TransferDataToWindow();
}

bool ObjectFrame::TransferDataToWindow(void)
{
	if(linkedProject == NULL) return false;

	size_t i;
	m_comboBox->Clear();
	if(linkedProject->objects.GetCount() > 0){
		for(i = 0; i < linkedProject->objects.GetCount(); i++)
			m_comboBox->Append(linkedProject->objects[i].fileName.GetName());
		m_comboBox->Enable();
	}else{
		m_comboBox->Append(_("No objects in project!"));
		m_comboBox->Enable(false);
	}
	m_comboBox->SetSelection(linkedProject->activeObject);

	Unit temp = linkedProject->Distance;

	m_textCtrlSizeX->SetValue(
			wxString::Format(
					_T("%.3f"),
					temp.FromSI(
							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeX())));
	m_textCtrlSizeY->SetValue(
			wxString::Format(
					_T("%.3f"),
					temp.FromSI(
							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeY())));
	m_textCtrlSizeZ->SetValue(
			wxString::Format(
					_T("%.3f"),
					temp.FromSI(
							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeZ())));

	m_staticTextUnitX->SetLabel(temp.GetOtherName());
	m_staticTextUnitY->SetLabel(temp.GetOtherName());
	m_staticTextUnitZ->SetLabel(temp.GetOtherName());
	m_staticTextUnitX2->SetLabel(temp.GetOtherName());
	m_staticTextUnitY2->SetLabel(temp.GetOtherName());
	m_staticTextUnitZ2->SetLabel(temp.GetOtherName());

	return true;
}
bool ObjectFrame::TransferDataFromWindow(void)
{

	return true;
}

void ObjectFrame::OnClose(wxCommandEvent& event)
{
	Close();
}

void ObjectFrame::OnOpen(wxCommandEvent& event)
{
}
void ObjectFrame::OnReLoad(wxCommandEvent& event)
{
}
void ObjectFrame::OnSaveAs(wxCommandEvent& event)
{
}
void ObjectFrame::OnUpdate(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();

	size_t i;
	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++)
		linkedProject->objects[linkedProject->activeObject].geometries[i].CalculateNormals();

	this->GetParent()->Refresh();

	TransferDataToWindow();
}
void ObjectFrame::OnMultiplyByTen(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;
	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++)
		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.ScaleGlobal(
				10, 10, 10);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();

}
void ObjectFrame::OnDivideByTen(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;
	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++)
		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.ScaleGlobal(
				0.1, 0.1, 0.1);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnScalePercent(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	double scale;
	m_textCtrlPercent->GetValue().ToDouble(&scale);

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++)
		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.ScaleGlobal(
				scale / 100, scale / 100, scale / 100);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::ScaleUnitX(wxCommandEvent& event)
{
}
void ObjectFrame::OnScalePercentX(wxCommandEvent& event)
{
}
void ObjectFrame::OnScaleUnitY(wxCommandEvent& event)
{
}
void ObjectFrame::OnScalePercentY(wxCommandEvent& event)
{
}
void ObjectFrame::OnScaleUnitZ(wxCommandEvent& event)
{
}
void ObjectFrame::OnScalePercentZ(wxCommandEvent& event)
{
}

void ObjectFrame::OnYMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(0, -M_PI_2, 0);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();

}
void ObjectFrame::OnXMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(-M_PI_2, 0, 0);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnYPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(0, M_PI_2, 0);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnZMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(0, 0, -M_PI_2);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnZPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(0, 0, M_PI_2);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnXPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix
				*= AffineTransformMatrix::RotateXYZ(M_PI_2, 0, 0);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

void ObjectFrame::OnAlignWithStock(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	double shiftX =
			-linkedProject->objects[linkedProject->activeObject].bbox.xmin;
	double shiftY =
			-linkedProject->objects[linkedProject->activeObject].bbox.ymin;
	double shiftZ =
			-linkedProject->objects[linkedProject->activeObject].bbox.zmin;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.TranslateGlobal(
				shiftX, shiftY, shiftZ);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnAlignWithMiddle(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	double shiftX =
			-linkedProject->objects[linkedProject->activeObject].bbox.xmin;
	double shiftY =
			-linkedProject->objects[linkedProject->activeObject].bbox.ymin;
	double shiftZ =
			-linkedProject->objects[linkedProject->activeObject].bbox.zmin;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.TranslateGlobal(
				shiftX, shiftY, shiftZ);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void ObjectFrame::OnAlignWithTop(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	size_t i;

	double shiftX =
			-linkedProject->objects[linkedProject->activeObject].bbox.xmin;
	double shiftY =
			-linkedProject->objects[linkedProject->activeObject].bbox.ymin;
	double shiftZ =
			-linkedProject->objects[linkedProject->activeObject].bbox.zmin;

	for(i = 0; i
			< linkedProject->objects[linkedProject->activeObject].geometries.GetCount(); i++){

		linkedProject->objects[linkedProject->activeObject].geometries[i].matrix.TranslateGlobal(
				shiftX, shiftY, shiftZ);
	}
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

