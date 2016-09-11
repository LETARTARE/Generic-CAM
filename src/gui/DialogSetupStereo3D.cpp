///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupStereo3D.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.01.2015
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

#include "DialogSetupStereo3D.h"

#include "../gui/DisplaySettings.h"
#include "../gui/CanvasStereoTest.h"
#include "../gui/Unit.h"
#include "../gui/IDs.h"

#include "../StdInclude.h"

DialogSetupStereo3D::DialogSetupStereo3D(wxWindow* parent,
		DisplaySettings * settings) :
		GUISetupStereo3D(parent)
{
	this->settings = settings;
	
	m_canvas->stereoMode = stereoAnaglyph;
	TransferDataToWindow();
}

bool DialogSetupStereo3D::TransferDataToWindow(void)
{

	m_sliderLR->SetValue(settings->leftEyeR);
	m_sliderLG->SetValue(settings->leftEyeG);
	m_sliderLB->SetValue(settings->leftEyeB);

	m_sliderRR->SetValue(settings->rightEyeR);
	m_sliderRG->SetValue(settings->rightEyeG);
	m_sliderRB->SetValue(settings->rightEyeB);

	m_colourPickerLeft->SetColour(
			wxColour(settings->leftEyeR, settings->leftEyeG,
					settings->leftEyeB));
	m_colourPickerRight->SetColour(
			wxColour(settings->rightEyeR, settings->rightEyeG,
					settings->rightEyeB));

	m_textCtrlLR->SetValue(wxString::Format(_T("%u"), settings->leftEyeR));
	m_textCtrlLG->SetValue(wxString::Format(_T("%u"), settings->leftEyeG));
	m_textCtrlLB->SetValue(wxString::Format(_T("%u"), settings->leftEyeB));

	m_textCtrlRR->SetValue(wxString::Format(_T("%u"), settings->rightEyeR));
	m_textCtrlRG->SetValue(wxString::Format(_T("%u"), settings->rightEyeG));
	m_textCtrlRB->SetValue(wxString::Format(_T("%u"), settings->rightEyeB));

	m_sliderEyeDistance->SetValue(
			(int) round((settings->eyeDistance * 1000.0)));
	m_sliderFocalDistance->SetValue(
			(int) round((settings->focalDistance * 50.0)));

	m_textCtrlEyeDistance->SetValue(
			settings->Distance.TextFromSI(settings->eyeDistance, 1));
	m_textCtrlFocalDistance->SetValue(
			settings->Distance.TextFromSI(settings->focalDistance, 1));

	m_staticTextUnitEyeDistance->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitFocalDistance->SetLabel(settings->Distance.GetOtherName());

	settings->WriteToCanvas(m_canvas);
	m_canvas->Refresh();
	return true;
}

bool DialogSetupStereo3D::TransferDataFromWindow(void)
{
	return true;
}

void DialogSetupStereo3D::OnXClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogSetupStereo3D::OnScroll(wxScrollEvent& event)
{
	switch(event.GetId()){
	case ID_COLORLR:
		settings->leftEyeR = m_sliderLR->GetValue();
		settings->rightEyeR = 0;
		break;
	case ID_COLORLG:
		settings->leftEyeG = m_sliderLG->GetValue();
		settings->rightEyeG = 0;
		break;
	case ID_COLORLB:
		settings->leftEyeB = m_sliderLB->GetValue();
		settings->rightEyeB = 0;
		break;

	case ID_COLORRR:
		settings->rightEyeR = m_sliderRR->GetValue();
		settings->leftEyeR = 0;
		break;
	case ID_COLORRG:
		settings->rightEyeG = m_sliderRG->GetValue();
		settings->leftEyeG = 0;
		break;
	case ID_COLORRB:
		settings->rightEyeB = m_sliderRB->GetValue();
		settings->leftEyeB = 0;
		break;

	case ID_EYEDISTANCE:
		settings->eyeDistance = ((float) m_sliderEyeDistance->GetValue())
				/ 1000.0;
		break;
	case ID_FOCALDISTANCE:
		settings->focalDistance = ((float) m_sliderFocalDistance->GetValue())
				/ 50.0;
		break;

	}

	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}

void DialogSetupStereo3D::OnColorChanged(wxColourPickerEvent& event)
{
	wxColour temp;
	switch(event.GetId()){
	case ID_COLORLEFT:
		temp = m_colourPickerLeft->GetColour();
		settings->leftEyeR = temp.Red();
		settings->leftEyeG = temp.Green();
		settings->leftEyeB = temp.Blue();
		if(settings->leftEyeR > 10)
			settings->rightEyeR = 0;
		else
			settings->leftEyeR = 0;
		if(settings->leftEyeG > 10)
			settings->rightEyeG = 0;
		else
			settings->leftEyeG = 0;
		if(settings->leftEyeB > 10)
			settings->rightEyeB = 0;
		else
			settings->leftEyeB = 0;
		break;
	case ID_COLORRIGHT:
		temp = m_colourPickerRight->GetColour();
		settings->rightEyeR = temp.Red();
		settings->rightEyeG = temp.Green();
		settings->rightEyeB = temp.Blue();
		if(settings->rightEyeR > 10)
			settings->leftEyeR = 0;
		else
			settings->rightEyeR = 0;
		if(settings->rightEyeG > 10)
			settings->leftEyeG = 0;
		else
			settings->rightEyeG = 0;
		if(settings->rightEyeB > 10)
			settings->leftEyeB = 0;
		else
			settings->rightEyeB = 0;
		break;
	}
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}

void DialogSetupStereo3D::OnTextChange(wxCommandEvent& event)
{
	long temp;
	event.GetString().ToLong(&temp);

	switch(event.GetId()){
	case ID_TEXTLR:
		settings->leftEyeR = temp;
		if(settings->leftEyeR > 0) settings->rightEyeR = 0;
		break;
	case ID_TEXTLG:
		settings->leftEyeG = temp;
		if(settings->leftEyeG > 0) settings->rightEyeG = 0;
		break;
	case ID_TEXTLB:
		settings->leftEyeB = temp;
		if(settings->leftEyeB > 0) settings->rightEyeB = 0;
		break;
	case ID_TEXTRR:
		settings->rightEyeR = temp;
		if(settings->rightEyeR > 0) settings->leftEyeR = 0;
		break;
	case ID_TEXTRG:
		settings->rightEyeG = temp;
		if(settings->rightEyeG > 0) settings->leftEyeG = 0;
		break;
	case ID_TEXTRB:
		settings->rightEyeB = temp;
		if(settings->rightEyeB > 0) settings->leftEyeB = 0;
		break;
	case ID_EYEDISTANCE:
		settings->eyeDistance = settings->Distance.SIFromString(
				event.GetString());
		break;
	case ID_FOCALDISTANCE:
		settings->focalDistance = settings->Distance.SIFromString(
				event.GetString());
		break;
	}
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}

void DialogSetupStereo3D::OnSwap(wxCommandEvent& event)
{
	std::swap(settings->leftEyeR, settings->rightEyeR);
	std::swap(settings->leftEyeG, settings->rightEyeG);
	std::swap(settings->leftEyeB, settings->rightEyeB);
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
}
