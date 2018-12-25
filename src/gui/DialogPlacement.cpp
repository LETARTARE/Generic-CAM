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

#include "../project/command/CommandWorkpieceObjectTransform.h"
#include "FrameMain.h"
#include "FrameParent.h"
#include "IDs.h"

DialogPlacement::DialogPlacement(wxWindow* parent) :
		GUIPlacement(parent)
{
	m_menuPreferences->Append(ID_SETUPUNITS, _("Setup &Units") + wxT("\tCtrl+U"));
	FrameMain * frame = wxStaticCast(parent, FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	m_topview->InsertProject(project);
}

DialogPlacement::~DialogPlacement()
{
}

bool DialogPlacement::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	DisplaySettings* settings = &(frame->GetParentFrame()->settings);
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
			int obNr = project->workpieces[wpNr].placements[n].refObject;
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
						project->workpieces[wpNr].placements[plNr].cornerX));
		m_textCtrlY->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].cornerY));
		m_textCtrlZ->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.tz));
		m_textCtrlAngle->SetValue(
				settings->Angle.TextFromSI(
						project->workpieces[wpNr].placements[plNr].matrix.rz));
		m_sliderAngle->SetValue(
				(int) round(
						project->workpieces[wpNr].placements[plNr].matrix.rz
								* 180.0 / M_PI));
		m_textCtrlDistance->SetValue(
				settings->Distance.TextFromSI(
						project->workpieces[wpNr].placements[plNr].slotWidth));

		m_checkBoxContour->Enable();
		m_checkBoxContour->SetValue(
				project->workpieces[wpNr].placements[plNr].useContour);
	}else{
		m_textCtrlX->SetValue(_T(""));
		m_textCtrlY->SetValue(_T(""));
		m_textCtrlZ->SetValue(_T(""));
		m_textCtrlAngle->SetValue(_T(""));
		m_textCtrlDistance->SetValue(_T(""));
		m_sliderAngle->SetValue(0);
		m_checkBoxContour->SetValue(false);
		m_checkBoxContour->Enable(false);
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

void DialogPlacement::OnXClose(wxCloseEvent& event)
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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	int id = m_choiceWorkpiece->GetSelection() - 1;
	size_t n;
	for(n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == id);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnSelectObject(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	for(size_t n = 0; n < project->workpieces.GetCount(); n++)
		project->workpieces[n].selected = (n == wpNr);
	for(size_t n = 0; n < project->workpieces[wpNr].placements.GetCount(); n++)
		project->workpieces[wpNr].placements[n].selected = (n == plNr);

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
	TransferDataToWindow();

}

void DialogPlacement::OnChange(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	DisplaySettings* settings = &(frame->GetParentFrame()->settings);
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].refObject;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	float newX = project->workpieces[wpNr].placements[plNr].cornerX;
	float newY = project->workpieces[wpNr].placements[plNr].cornerY;
	temp.TakeMatrixApart();
	wxString description;
	float d;
	bool useContour = project->workpieces[wpNr].placements[plNr].useContour;
	double slotWidth = project->workpieces[wpNr].placements[plNr].slotWidth;
	switch(event.GetId()){
	case ID_POSX:
		d = settings->Distance.SIFromString(m_textCtrlX->GetValue());
		newX = d;
		description = _("Set X position: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_POSY:
		d = settings->Distance.SIFromString(m_textCtrlY->GetValue());
		newY = d;
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
		d -= temp.rz;
		temp *= AffineTransformMatrix::RotateAroundVector(Vector3(0, 0, 1), d);
		description = _("Rotate around Z: ")
				+ settings->Angle.TextFromSIWithUnit(d, 2);
		break;
	case ID_DISTANCE:
		slotWidth = settings->Distance.SIFromString(
				m_textCtrlDistance->GetValue());
		description = _("Set slotwidth to: ")
				+ settings->Distance.TextFromSIWithUnit(slotWidth, 2);
		break;
	case ID_FORMCONTOUR:
		useContour = m_checkBoxContour->GetValue();
		if(useContour)
			description = _("Object: Mill contour only");
		else
			description = _("Object: Mill everything");
		break;
	}
	cmdProc->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp, newX, newY, useContour, slotWidth));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnChangeSlider(wxScrollEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	DisplaySettings* settings = &(frame->GetParentFrame()->settings);
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].refObject;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	float newX = project->workpieces[wpNr].placements[plNr].cornerX;
	float newY = project->workpieces[wpNr].placements[plNr].cornerY;
	bool useContour = project->workpieces[wpNr].placements[plNr].useContour;
	double slotWidth = project->workpieces[wpNr].placements[plNr].slotWidth;
	temp.TakeMatrixApart();
	wxString description;
	float d;
	d = (float) m_sliderAngle->GetValue();
	d = d * M_PI / 180.0;
	d -= temp.rz;
	temp *= AffineTransformMatrix::RotateAroundVector(Vector3(0, 0, 1), d);
	description = _("Rotate around Z: ")
			+ settings->Angle.TextFromSIWithUnit(d, 2);
	cmdProc->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp, newX, newY, useContour, slotWidth));
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

Project* DialogPlacement::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}

void DialogPlacement::OnTransform(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	DisplaySettings* settings = &(frame->GetParentFrame()->settings);
	int wpNr = m_choiceWorkpiece->GetSelection() - 1;
	if(wpNr < 0) return;
	int plNr = m_choicePlacement->GetSelection() - 1;
	if(plNr < 0) return;
	int objNr = project->workpieces[wpNr].placements[plNr].refObject;
	if(objNr < 0) return;

	AffineTransformMatrix temp =
			project->workpieces[wpNr].placements[plNr].matrix;
	float newX = project->workpieces[wpNr].placements[plNr].cornerX;
	float newY = project->workpieces[wpNr].placements[plNr].cornerY;
	bool useContour = project->workpieces[wpNr].placements[plNr].useContour;
	double slotWidth = project->workpieces[wpNr].placements[plNr].slotWidth;
	temp.TakeMatrixApart();

	float d = 0.01;
	wxString description;

	switch(event.GetId()){
	case ID_MOVEXP:
		newX += d;
		description = _("Placement X+:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEXN:
		newX -= d;
		description = _("Placement X-: ")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEYP:
		newY += d;
		description = _("Placement Y+:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_MOVEYN:
		newY -= d;
		description = _("Placement Y-:")
				+ settings->Distance.TextFromSIWithUnit(d, 2);
		break;
	case ID_ALIGNTOP:
		temp.TranslateGlobal(0, 0,
				-temp.tz + project->workpieces[wpNr].GetSizeZ()
						- project->objects[objNr].bbox.GetSizeZ());
		description = _("Align with top");
		break;
	case ID_ALIGNMIDDLE:
		temp.TranslateGlobal(0, 0,
				-temp.tz + project->workpieces[wpNr].GetSizeZ() / 2.0
						- project->objects[objNr].bbox.GetSizeZ() / 2.0);
		description = _("Align with middle");
		break;
	case ID_ALIGNBOTTOM:
		temp.TranslateGlobal(0, 0, -temp.tz);
		description = _("Align with bottom");
		break;
	}

	cmdProc->Submit(
			new CommandWorkpieceObjectTransform(description, project, wpNr,
					plNr, temp, newX, newY, useContour, slotWidth));

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESH3DVIEW);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void DialogPlacement::OnSize(wxSizeEvent& event)
{
	event.Skip();
	m_topview->Refresh();
}

