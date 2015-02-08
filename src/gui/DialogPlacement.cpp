///////////////////////////////////////////////////////////////////////////////
// Name               : DialogPlacement.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.01.2015
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

#include "DialogPlacement.h"
#include "../command/CommandWorkpieceObjectTransform.h"
#include "IDs.h"

DialogPlacement::DialogPlacement(wxWindow* parent, Project* project,
		wxCommandProcessor* commandProcessor, DisplaySettings* settings) :
		GUIPlacement(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
	m_topview->InsertProject(project);
}

bool DialogPlacement::TransferDataToWindow(void)
{
	int wpNr = GetSelectedWorkpiece();
	int plNr = GetSelectedPlacement(wpNr);

	size_t n;
	m_choiceWorkpiece->Clear();
	m_choiceWorkpiece->Append(_T(""));
	for(n = 0; n < project->workpieces.GetCount(); n++)
		m_choiceWorkpiece->Append(project->workpieces[n].name);
	m_choiceWorkpiece->SetSelection(wpNr + 1);

	m_choicePlacement->Clear();
	m_choicePlacement->Append(_T(""));

	if(wpNr >= 0){
		for(n = 0; n < project->workpieces[wpNr].placements.GetCount(); n++){
			int obNr = project->workpieces[wpNr].placements[n].objectNr;
			if(obNr > -1){
				m_choicePlacement->Append(project->objects[obNr].name);
			}else{
				m_choicePlacement->Append(_T("?"));
			}
		}
	}
	m_choicePlacement->SetSelection(plNr + 1);

	if(wpNr >= 0 && plNr >= 0){
		project->workpieces[wpNr].placements[plNr].matrix.TakeMatrixApart();

		m_textCtrlX->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.tx));
		m_textCtrlY->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.ty));
		m_textCtrlZ->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.tz));
		m_textCtrlAngle->SetValue(
				settings->Angle.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.rz
								* 180.0 / M_PI));
		m_sliderAngle->SetValue(
				(int) round(project->workpieces[wpNr].placements[plNr].matrix.rz
						* 180.0 / M_PI));
		m_textCtrlDistance->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].slotWidth));

		m_radioBtnBox->Enable();
		m_radioBtnContour->Enable();
		if(project->workpieces[wpNr].placements[plNr].useContour){
			m_radioBtnContour->SetValue(true);
		}else{
			m_radioBtnBox->SetValue(true);
		}
	}else{
		m_textCtrlX->SetValue(_T(""));
		m_textCtrlY->SetValue(_T(""));
		m_textCtrlZ->SetValue(_T(""));
		m_textCtrlAngle->SetValue(_T(""));
		m_textCtrlDistance->SetValue(_T(""));
		m_sliderAngle->SetValue(0);
		m_radioBtnBox->SetValue(true);
		m_radioBtnBox->Enable(false);
		m_radioBtnContour->Enable(false);
	}

	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());
	m_staticTextunitAngle->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitDistance->SetLabel(settings->Distance.GetOtherName());

	Refresh();
	return true;
}

bool DialogPlacement::TransferDataFromWindow(void)
{
	return false;
}

void DialogPlacement::OnClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogPlacement::OnClose(wxCommandEvent& event)
{
	this->Hide();
}

void DialogPlacement::OnExtraAdd(wxCommandEvent& event)
{
}

int DialogPlacement::GetSelectedWorkpiece(void)
{
	size_t N = project->workpieces.GetCount();
	if(N == 0) return -1;
	size_t n;
	for(n = 0; n < N; n++){
		if(project->workpieces[n].selected) return n;
	}
	return -1;
}

int DialogPlacement::GetSelectedPlacement(int workpieceNr)
{
	if(workpieceNr < 0) return -1;
	size_t N = project->workpieces[workpieceNr].placements.GetCount();
	if(N == 0) return -1;
	size_t n;
	for(n = 0; n < N; n++){
		if(project->workpieces[workpieceNr].placements[n].selected) return n;
	}
	return -1;
}

void DialogPlacement::OnSelectWorkpiece(wxCommandEvent& event)
{
	int id = m_choiceWorkpiece->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == id);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHTREE);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnSelectObject(wxCommandEvent& event)
{
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == wpNr);
	for(n = 0; n < project->workpieces[wpNr].placements.GetCount(); n++)
		project->workpieces[wpNr].placements[n].selected = (n == plNr);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHTREE);
	ProcessEvent(selectEvent);
	TransferDataToWindow();

}

void DialogPlacement::OnChangePosition(wxCommandEvent& event)
{
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].objectNr;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	temp.TakeMatrixApart();
	wxString description;
	float d;
	switch(event.GetId()){
	case ID_POSX:
		d = settings->Distance.SIFromString(m_textCtrlX->GetValue());
		temp.TranslateGlobal(d - temp.tx, 0, 0);
		description = _("Set X position: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_POSY:
		d = settings->Distance.SIFromString(m_textCtrlY->GetValue());
		temp.TranslateGlobal(0, d - temp.ty, 0);
		description = _("Set Y position: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_POSZ:
		d = settings->Distance.SIFromString(m_textCtrlZ->GetValue());
		temp.TranslateGlobal(0, 0, d - temp.tz);
		description = _("Set Z position: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_ANGLE:
		d = settings->Angle.SIFromString(m_textCtrlAngle->GetValue());
		temp.rz = d * M_PI / 180.0;
		temp.PutMatrixTogether();
		description = _("Rotate around Z: ")
				+ settings->Angle.TextFromSIWithUnit(d, 2);
		break;
	}
	commandProcessor->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHDISPLAY);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnChangeSlider(wxScrollEvent& event)
{

	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].objectNr;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	temp.TakeMatrixApart();
	wxString description;
	float d;
	d = (float) m_sliderAngle->GetValue();
	temp.rz = d * M_PI / 180.0;
	temp.PutMatrixTogether();
	description = _("Rotate around Z: ")
			+ settings->Angle.TextFromSIWithUnit(d, 2);
	commandProcessor->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHDISPLAY);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnSelectForm(wxCommandEvent& event)
{
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHDISPLAY);
//	ProcessEvent(selectEvent);
//	TransferDataToWindow();
}

void DialogPlacement::OnTransform(wxCommandEvent& event)
{
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].objectNr;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	temp.TakeMatrixApart();

	float d = 0.01;
	wxString description;

	switch(event.GetId()){
	case ID_MOVEXP:
		temp.TranslateGlobal(d, 0, 0);
		description = _("Placement X+:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEXN:
		temp.TranslateGlobal(-d, 0, 0);
		description = _("Placement X-: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEYP:
		temp.TranslateGlobal(0, d, 0);
		description = _("Placement Y+:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEYN:
		temp.TranslateGlobal(0, -d, 0);
		description = _("Placement Y-:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_ALIGNTOP:
		temp.TranslateGlobal(0, 0,
				-temp.tz + project->workpieces[wpNr].sz
						- project->objects[objNr].bbox.GetSizeZ());
		description = _("Align with top");
		break;
	case ID_ALIGNMIDDLE:
		temp.TranslateGlobal(0, 0,
				-temp.tz + project->workpieces[wpNr].sz / 2.0
						- project->objects[objNr].bbox.GetSizeZ() / 2.0);
		description = _("Align with middle");
		break;
	case ID_ALIGNBOTTOM:
		temp.TranslateGlobal(0, 0, -temp.tz);
		description = _("Align with bottom");
		break;
	}

	commandProcessor->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp));

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHDISPLAY);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnSize(wxSizeEvent& event)
{
	event.Skip();
	m_topview->Refresh();
}
