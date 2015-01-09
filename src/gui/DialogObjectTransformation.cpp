///////////////////////////////////////////////////////////////////////////////
// Name               : DialogObjectTransformation.cpp
// Purpose            : Dialog for manipulating objects
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
///////////////////////////////////////////////////////////////////////////////

#include "DialogObjectTransformation.h"
#include <math.h>

DialogObjectTransformation::DialogObjectTransformation(wxWindow* parent,
		Project * project, wxCommandProcessor * commandProcessor,
		DisplaySettings * settings) :
		GUIObjectTransformation(parent)
{
	linkedProject = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
	TransferDataToWindow();
}

DialogObjectTransformation::~DialogObjectTransformation()
{
}

bool DialogObjectTransformation::TransferDataToWindow(void)
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
//	m_comboBox->SetSelection(linkedProject->activeObject);
//
//	m_textCtrlSizeX->SetValue(
//			wxString::Format(_T("%.3f"),
//					settings->Distance.FromSI(
//							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeX())));
//	m_textCtrlSizeY->SetValue(
//			wxString::Format(_T("%.3f"),
//					settings->Distance.FromSI(
//							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeY())));
//	m_textCtrlSizeZ->SetValue(
//			wxString::Format(_T("%.3f"),
//					settings->Distance.FromSI(
//							linkedProject->objects[linkedProject->activeObject].bbox.GetSizeZ())));

	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitX2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ2->SetLabel(settings->Distance.GetOtherName());

	return true;
}
bool DialogObjectTransformation::TransferDataFromWindow(void)
{
	return true;
}

//void DialogObjectTransformation::OnUpdate(wxCommandEvent& event)
//{
//	if(linkedProject == NULL) return;
//	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
//	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
//
//	size_t i;
//	for(i = 0;
//			i
//					< linkedProject->objects[linkedProject->activeObject].geometries.GetCount();
//			i++)
//		linkedProject->objects[linkedProject->activeObject].geometries[i].CalculateNormals();
//
//	this->GetParent()->Refresh();
//
//	TransferDataToWindow();
//}

void DialogObjectTransformation::OnOpen(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnReLoad(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnSaveAs(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnClose(wxCommandEvent& event)
{
	this->Show(false);
}
void DialogObjectTransformation::OnClose(wxCloseEvent& event)
{
	this->Show(false);
}

void DialogObjectTransformation::OnSelectObject(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMultiplyByTen(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix.ScaleGlobal(10,
			10, 10);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();

}
void DialogObjectTransformation::OnDivideByTen(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix.ScaleGlobal(0.1,
			0.1, 0.1);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void DialogObjectTransformation::OnScalePercent(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;

	double scale;
	m_textCtrlPercent->GetValue().ToDouble(&scale);

	linkedProject->objects[linkedProject->activeObject].matrix.ScaleGlobal(
			scale / 100, scale / 100, scale / 100);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

void DialogObjectTransformation::OnYMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;

	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(0, -M_PI_2, 0);

	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();

}
void DialogObjectTransformation::OnXMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;

	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(-M_PI_2, 0, 0);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void DialogObjectTransformation::OnYPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(0, M_PI_2, 0);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void DialogObjectTransformation::OnZMinus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(0, 0, -M_PI_2);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}
void DialogObjectTransformation::OnZPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(0, 0, M_PI_2);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

void DialogObjectTransformation::OnXPlus(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;
	linkedProject->objects[linkedProject->activeObject].matrix *=
			AffineTransformMatrix::RotateXYZ(M_PI_2, 0, 0);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

void DialogObjectTransformation::OnAlignWithStock(wxCommandEvent& event)
{
	if(linkedProject == NULL) return;
	if(linkedProject->activeObject >= linkedProject->objects.GetCount()) return;

	double shiftX =
			-linkedProject->objects[linkedProject->activeObject].bbox.xmin;
	double shiftY =
			-linkedProject->objects[linkedProject->activeObject].bbox.ymin;
	double shiftZ =
			-linkedProject->objects[linkedProject->activeObject].bbox.zmin;

	linkedProject->objects[linkedProject->activeObject].matrix.TranslateGlobal(
			shiftX, shiftY, shiftZ);
	linkedProject->objects[linkedProject->activeObject].UpdateBoundingBox();
	this->GetParent()->Refresh();
	TransferDataToWindow();
}

void DialogObjectTransformation::ScaleUnitX(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnScalePercentX(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnScaleUnitY(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnScalePercentY(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnScaleUnitZ(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnScalePercentZ(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnFlipX(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnFlipY(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnFlipZ(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveZUp(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveYUp(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveXDown(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveXUp(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveYDown(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnMoveZDown(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnAlignWithTop(wxCommandEvent& event)
{
}

void DialogObjectTransformation::OnAlignWithMiddle(wxCommandEvent& event)
{
}
