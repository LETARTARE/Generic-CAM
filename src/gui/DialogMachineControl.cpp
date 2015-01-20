///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineControl.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogMachineControl.h"
#include "IDs.h"

#include <math.h>

DialogMachineControl::DialogMachineControl(wxWindow* parent,
		DisplaySettings * settings) :
		GUIMachineControl(parent)
{
	this->settings = settings;
	X = Y = Z = 0.0;
	A = B = C = 0.0;
	U = V = W = 0.0;

	groupXYZLimit = 1.0;
	groupABCLimit = 180.0;
	groupUVWLimit = 1.0;

	sliderSteps = 201;
	pageSize = 20;
	lineSize = 1;
}

void DialogMachineControl::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogMachineControl::OnScroll(wxScrollEvent& event)
{
	TransferDataFromWindowSliders();
	TransferDataToWindowTextbox();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogMachineControl::OnTrack(wxScrollEvent& event)
{
	TransferDataFromWindowSliders();
	TransferDataToWindowTextbox();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

bool DialogMachineControl::TransferDataToWindow(void)
{
	return TransferDataToWindowSliders() & TransferDataToWindowTextbox();
}

bool DialogMachineControl::TransferDataFromWindow(void)
{
	return TransferDataFromWindowSliders();
}

bool DialogMachineControl::TransferDataToWindowSliders(void)
{
	m_sliderX->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderY->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderZ->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderA->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderB->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderC->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderU->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderV->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderW->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);

	m_sliderX->SetPageSize(pageSize);
	m_sliderY->SetPageSize(pageSize);
	m_sliderZ->SetPageSize(pageSize);
	m_sliderA->SetPageSize(pageSize);
	m_sliderB->SetPageSize(pageSize);
	m_sliderC->SetPageSize(pageSize);
	m_sliderU->SetPageSize(pageSize);
	m_sliderV->SetPageSize(pageSize);
	m_sliderW->SetPageSize(pageSize);

	m_sliderX->SetLineSize(lineSize);
	m_sliderY->SetLineSize(lineSize);
	m_sliderZ->SetLineSize(lineSize);
	m_sliderA->SetLineSize(lineSize);
	m_sliderB->SetLineSize(lineSize);
	m_sliderC->SetLineSize(lineSize);
	m_sliderU->SetLineSize(lineSize);
	m_sliderV->SetLineSize(lineSize);
	m_sliderW->SetLineSize(lineSize);

	m_sliderX->SetValue(round((X / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderY->SetValue(round((Y / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderZ->SetValue(round((Z / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderA->SetValue(round((A / groupABCLimit) * (sliderSteps - 1) / 2));
	m_sliderB->SetValue(round((B / groupABCLimit) * (sliderSteps - 1) / 2));
	m_sliderC->SetValue(round((C / groupABCLimit) * (sliderSteps - 1) / 2));
	m_sliderU->SetValue(round((U / groupUVWLimit) * (sliderSteps - 1) / 2));
	m_sliderV->SetValue(round((V / groupUVWLimit) * (sliderSteps - 1) / 2));
	m_sliderW->SetValue(round((W / groupUVWLimit) * (sliderSteps - 1) / 2));
	return true;
}

bool DialogMachineControl::TransferDataFromWindowSliders(void)
{
	X = (float) m_sliderX->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;
	Y = (float) m_sliderY->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;
	Z = (float) m_sliderZ->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;

	A = (float) m_sliderA->GetValue() / ((sliderSteps - 1) / 2) * groupABCLimit;
	B = (float) m_sliderB->GetValue() / ((sliderSteps - 1) / 2) * groupABCLimit;
	C = (float) m_sliderC->GetValue() / ((sliderSteps - 1) / 2) * groupABCLimit;

	U = (float) m_sliderU->GetValue() / ((sliderSteps - 1) / 2) * groupUVWLimit;
	V = (float) m_sliderV->GetValue() / ((sliderSteps - 1) / 2) * groupUVWLimit;
	W = (float) m_sliderW->GetValue() / ((sliderSteps - 1) / 2) * groupUVWLimit;
	return true;
}

bool DialogMachineControl::TransferDataToWindowTextbox(void)
{
	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitA->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitB->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitC->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitU->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitV->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitW->SetLabel(settings->Distance.GetOtherName());

	m_textCtrlX->SetValue(settings->Distance.TextFromSI(X));
	m_textCtrlY->SetValue(settings->Distance.TextFromSI(Y));
	m_textCtrlZ->SetValue(settings->Distance.TextFromSI(Z));
	m_textCtrlA->SetValue(settings->Angle.TextFromSI(A, 1));
	m_textCtrlB->SetValue(settings->Angle.TextFromSI(B, 1));
	m_textCtrlC->SetValue(settings->Angle.TextFromSI(C, 1));
	m_textCtrlU->SetValue(settings->Distance.TextFromSI(U));
	m_textCtrlV->SetValue(settings->Distance.TextFromSI(V));
	m_textCtrlW->SetValue(settings->Distance.TextFromSI(W));
	return true;
}

void DialogMachineControl::OnZero(wxMouseEvent& event)
{
	switch(event.GetId()){
	case ID_AXISX:
		X = 0.0;
		break;
	case ID_AXISY:
		Y = 0.0;
		break;
	case ID_AXISZ:
		Z = 0.0;
		break;
	case ID_AXISA:
		A = 0.0;
		break;
	case ID_AXISB:
		B = 0.0;
		break;
	case ID_AXISC:
		C = 0.0;
		break;
	case ID_AXISU:
		U = 0.0;
		break;
	case ID_AXISV:
		V = 0.0;
		break;
	case ID_AXISW:
		W = 0.0;
		break;
	}
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogMachineControl::OnTextChanged(wxCommandEvent& event)
{
	switch(event.GetId()){
	case ID_TEXTX:
		m_textCtrlX->GetValue().ToDouble(&X);
		X = settings->Distance.ToSI(X);
		break;
	case ID_TEXTY:
		m_textCtrlY->GetValue().ToDouble(&Y);
		Y = settings->Distance.ToSI(Y);
		break;
	case ID_TEXTZ:
		m_textCtrlZ->GetValue().ToDouble(&Z);
		Z = settings->Distance.ToSI(Z);
		break;
	case ID_TEXTA:
		m_textCtrlA->GetValue().ToDouble(&A);
		A = settings->Angle.ToSI(A);
		break;
	case ID_TEXTB:
		m_textCtrlB->GetValue().ToDouble(&B);
		B = settings->Angle.ToSI(B);
		break;
	case ID_TEXTC:
		m_textCtrlC->GetValue().ToDouble(&C);
		C = settings->Angle.ToSI(C);
		break;
	case ID_TEXTU:
		m_textCtrlU->GetValue().ToDouble(&U);
		U = settings->Distance.ToSI(U);
		break;
	case ID_TEXTV:
		m_textCtrlV->GetValue().ToDouble(&V);
		V = settings->Distance.ToSI(V);
		break;
	case ID_TEXTW:
		m_textCtrlW->GetValue().ToDouble(&W);
		W = settings->Distance.ToSI(W);
		break;

	}
	TransferDataToWindowSliders();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}
