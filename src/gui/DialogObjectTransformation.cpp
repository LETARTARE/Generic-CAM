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
#include "IDs.h"
#include <wx/event.h>

#include "../command/CommandObjectTransform.h"

DialogObjectTransformation::DialogObjectTransformation(wxWindow* parent,
		Project * project, wxCommandProcessor * commandProcessor,
		DisplaySettings * settings) :
		GUIObjectTransformation(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;

	scaleProportional = true;
	scalePercent = 1;
	scalePercentX = 1;
	scalePercentY = 1;
	scalePercentZ = 1;
	scaleUnitX = 1;
	scaleUnitY = 1;
	scaleUnitZ = 1;
	moveStep = 0.05;
	rotateStep = 90;

	c = 0;
}

DialogObjectTransformation::~DialogObjectTransformation()
{
}

bool DialogObjectTransformation::TransferDataToWindow(void)
{
	if(!this->IsShown()) return false;
	if(project == NULL) return false;

	// Update Selection box
	size_t n;
	int selection = -1;
	m_choiceObjectSelection->Clear();
	for(n = 0; n < project->objects.GetCount(); n++){
		m_choiceObjectSelection->Append(project->objects[n].name);
		if(project->objects[n].selected){
			if(selection == -1)
				selection = n;
			else
				selection = -2;
		}
	}
	if(n == 0) m_choiceObjectSelection->Append(_("No objects in project!"));
	m_choiceObjectSelection->Enable(n > 0);

	if(selection == -2){
		m_choiceObjectSelection->Append(_("Multiple objects selected."));
		m_choiceObjectSelection->SetSelection(n);
	}
	if(selection >= 0) m_choiceObjectSelection->SetSelection(selection);

	// Update Units

	if(selection >= 0){
		m_textCtrlSizeX->SetValue(
				wxString::Format(_T("%.3f"),
						settings->Distance.FromSI(
								project->objects[selection].bbox.GetSizeX())));
		m_textCtrlSizeY->SetValue(
				wxString::Format(_T("%.3f"),
						settings->Distance.FromSI(
								project->objects[selection].bbox.GetSizeY())));
		m_textCtrlSizeZ->SetValue(
				wxString::Format(_T("%.3f"),
						settings->Distance.FromSI(
								project->objects[selection].bbox.GetSizeZ())));
	}else{
		m_textCtrlSizeX->SetValue(_T("---"));
		m_textCtrlSizeY->SetValue(_T("---"));
		m_textCtrlSizeZ->SetValue(_T("---"));
	}

	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitX2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ2->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitMove->SetLabel(settings->Distance.GetOtherName());

	m_textCtrlScaleUnitX->SetValue(
			wxString::Format(_T("%.3f"),
					settings->Distance.FromSI(scaleUnitX)));
	m_textCtrlScaleUnitY->SetValue(
			wxString::Format(_T("%.3f"),
					settings->Distance.FromSI(scaleUnitY)));
	m_textCtrlScaleUnitZ->SetValue(
			wxString::Format(_T("%.3f"),
					settings->Distance.FromSI(scaleUnitZ)));

	m_textCtrlScalePercent->SetValue(
			wxString::Format(_T("%.1f"), scalePercent * 100));
	m_textCtrlScalePercentX->SetValue(
			wxString::Format(_T("%.1f"), scalePercentX * 100));
	m_textCtrlScalePercentY->SetValue(
			wxString::Format(_T("%.1f"), scalePercentY * 100));
	m_textCtrlScalePercentZ->SetValue(
			wxString::Format(_T("%.1f"), scalePercentZ * 100));

	m_textCtrlMoveStep->SetValue(
			wxString::Format(_T("%.3f"), settings->Distance.FromSI(moveStep)));
	m_textCtrlRotateStep->SetValue(wxString::Format(_T("%.1f"), rotateStep));

	m_checkBoxScaleProportionally->SetValue(scaleProportional);

//	c++;
//	wxLogMessage(
//			wxString::Format(_T("Transfer: %u - Selection: %i"), c, selection));

	this->Refresh();
	return true;
}
bool DialogObjectTransformation::TransferDataFromWindow(void)
{
	m_textCtrlScalePercent->GetValue().ToDouble(&scalePercent);
	m_textCtrlScalePercentX->GetValue().ToDouble(&scalePercentX);
	m_textCtrlScalePercentY->GetValue().ToDouble(&scalePercentY);
	m_textCtrlScalePercentZ->GetValue().ToDouble(&scalePercentZ);
	m_textCtrlScaleUnitX->GetValue().ToDouble(&scaleUnitX);
	m_textCtrlScaleUnitY->GetValue().ToDouble(&scaleUnitY);
	m_textCtrlScaleUnitZ->GetValue().ToDouble(&scaleUnitZ);

	m_textCtrlMoveStep->GetValue().ToDouble(&moveStep);
	m_textCtrlRotateStep->GetValue().ToDouble(&rotateStep);

	scaleProportional = m_checkBoxScaleProportionally->GetValue();

	moveStep = settings->Distance.ToSI(moveStep);
	scaleUnitX = settings->Distance.ToSI(scaleUnitX);
	scaleUnitY = settings->Distance.ToSI(scaleUnitY);
	scaleUnitZ = settings->Distance.ToSI(scaleUnitZ);

	scalePercent /= 100;
	scalePercentX /= 100;
	scalePercentY /= 100;
	scalePercentZ /= 100;

	return true;
}

void DialogObjectTransformation::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}
void DialogObjectTransformation::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogObjectTransformation::OnSelectObject(wxCommandEvent& event)
{
	int n = m_choiceObjectSelection->GetSelection();
	// Return if "Multiple objects selected." was selected again.
	if(n >= project->objects.GetCount()) return;

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_SELECTOBJECT);
	selectEvent.SetInt(n);
	ProcessEvent(selectEvent);
}

void DialogObjectTransformation::OnTransform(wxCommandEvent& event)
{
	if(project == NULL) return;
	TransferDataFromWindow();

	AffineTransformMatrix newMatrix;
	wxString description; // of the command executed (for the Undo/Redo menu)
	CommandObjectTransform * command;

	size_t n;
	bool flipNormals = false;
	bool flipX = false;
	bool flipY = false;
	bool flipZ = false;

	// Calculate a common bounding box of all selected objects.
	BoundingBox bbox;
	for(n = 0; n < project->objects.GetCount(); ++n){
		if(!project->objects[n].selected) continue;
		bbox.Insert(project->objects[n].bbox);
	}

	// Generate the commands for the modifications
	for(n = 0; n < project->objects.GetCount(); ++n){
		if(!project->objects[n].selected) continue;

		description.Empty();
		newMatrix = project->objects[n].matrix; // Copy old to new for a start

		switch(event.GetId()){
		case ID_MULTTEN:
			description = project->objects[n].name + _T(": * 10");
			newMatrix.ScaleGlobal(10, 10, 10);
			break;
		case ID_DIVTEN:
			description = project->objects[n].name + _T(": / 10");
			newMatrix.ScaleGlobal(0.1, 0.1, 0.1);
			break;
		case ID_SCALEPERCENT:
			description = project->objects[n].name
					+ wxString::Format(_T(": scale by %.1f %%"),
							scalePercent * 100);
			newMatrix.ScaleGlobal(scalePercent, scalePercent, scalePercent);
			break;
		case ID_SCALEPERCENTX:
			description = project->objects[n].name
					+ wxString::Format(_T(": scale X by %.1f %%"),
							scalePercentX * 100);
			newMatrix.ScaleGlobal(scalePercentX, 1, 1);
			break;
		case ID_SCALEPERCENTY:
			description = project->objects[n].name
					+ wxString::Format(_T(": scale Y by %.1f %%"),
							scalePercentY * 100);
			newMatrix.ScaleGlobal(1, scalePercentY, 1);
			break;
		case ID_SCALEPERCENTZ:
			description = project->objects[n].name
					+ wxString::Format(_T(": scale Z by %.1f %%"),
							scalePercentZ * 100);
			newMatrix.ScaleGlobal(1, 1, scalePercentZ);
			break;

		case ID_FLIPX:
			description = project->objects[n].name
					+ wxString::Format(_T(": mirroring along X axis"));
			flipNormals = true;
			flipX = true;
			break;
		case ID_FLIPY:
			description = project->objects[n].name
					+ wxString::Format(_T(": mirroring along Y axis"));
			flipNormals = true;
			flipY = true;
			break;
		case ID_FLIPZ:
			description = project->objects[n].name
					+ wxString::Format(_T(": mirroring along Z axis"));
			flipNormals = true;
			flipZ = true;
			break;

		case ID_MOVEXP:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along X by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(moveStep));
			newMatrix.TranslateGlobal(moveStep, 0, 0);
			break;
		case ID_MOVEXN:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along X by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(-moveStep));
			newMatrix.TranslateGlobal(-moveStep, 0, 0);
			break;
		case ID_MOVEYP:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along Y by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(moveStep));
			newMatrix.TranslateGlobal(0, moveStep, 0);
			break;
		case ID_MOVEYN:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along Y by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(-moveStep));
			newMatrix.TranslateGlobal(0, -moveStep, 0);
			break;
		case ID_MOVEZP:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along Z by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(moveStep));
			newMatrix.TranslateGlobal(0, 0, moveStep);
			break;
		case ID_MOVEZN:
			description = project->objects[n].name
					+ wxString::Format(
							_T(": move along Z by %.3f ")
									+ settings->Distance.GetOtherName(),
							settings->Distance.FromSI(-moveStep));
			newMatrix.TranslateGlobal(0, 0, -moveStep);
			break;

		case ID_ALIGNTOP:
			if(bbox.IsVolumeZero()) break;
			description = project->objects[n].name
					+ wxString::Format(_T(": align top"));
			newMatrix.TranslateGlobal(0, 0, -bbox.zmax);
			break;
		case ID_ALIGNMIDDLE:
			if(bbox.IsVolumeZero()) break;
			description = project->objects[n].name
					+ wxString::Format(_T(": align middle"));
			newMatrix.TranslateGlobal(0, 0, -(bbox.zmax + bbox.zmin) / 2.0);
			break;
		case ID_ALIGNBOTTOM:
			if(bbox.IsVolumeZero()) break;
			description = project->objects[n].name
					+ wxString::Format(_T(": align bottom"));
			newMatrix.TranslateGlobal(0, 0, -bbox.zmin);
			break;

		case ID_ROTATEXP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around X by %.0f degree"),
							rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(rotateStep * M_PI / 180,
							0, 0);
			break;
		case ID_ROTATEXN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around X by %.0f degree"),
							-rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(-rotateStep * M_PI / 180,
							0, 0);
			break;
		case ID_ROTATEYP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Y by %.0f degree"),
							rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(0,
							rotateStep * M_PI / 180, 0);
			break;
		case ID_ROTATEYN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Y by %.0f degree"),
							-rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(0,
							-rotateStep * M_PI / 180, 0);
			break;
		case ID_ROTATEZP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Z by %.0f degree"),
							rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(0, 0,
							rotateStep * M_PI / 180);
			break;
		case ID_ROTATEZN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Z by %.0f degree"),
							-rotateStep);
			newMatrix = newMatrix
					* AffineTransformMatrix::RotateXYZ(0, 0,
							-rotateStep * M_PI / 180);
			break;
		}

		if(!description.IsEmpty()){

			command = new CommandObjectTransform(description, project, n, flipX,
					flipY, flipZ, flipNormals, newMatrix);
			commandProcessor->Submit(command);
		}else{
			wxLogMessage(
					wxString::Format(
							_T(
									"Unknown ID_... (=%i) in DialogObjectTransformation::OnTransform(...)"),
							event.GetId()));
		}
	}

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}

void DialogObjectTransformation::OnSetFactors(wxCommandEvent& event)
{
	TransferDataFromWindow();

	// Calculate a common bounding box of all selected objects.
	BoundingBox bbox;
	size_t n;
	double scale;
	for(n = 0; n < project->objects.GetCount(); ++n){
		if(!project->objects[n].selected) continue;
		bbox.Insert(project->objects[n].bbox);
	}

	switch(event.GetId()){
	case ID_SCALEUNITX:
		if(bbox.xmin >= bbox.xmax) break;
		scale = scaleUnitX / (bbox.xmax - bbox.xmin);
		if(scaleProportional){
			scalePercent = scale;
			scalePercentX = scale;
			scalePercentY = scale;
			scalePercentZ = scale;
		}else{
			scalePercentX = scale;
		}
		break;
	case ID_SCALEUNITY:
		if(bbox.ymin >= bbox.ymax) break;
		scale = scaleUnitY / (bbox.ymax - bbox.ymin);
		if(scaleProportional){
			scalePercent = scale;
			scalePercentX = scale;
			scalePercentY = scale;
			scalePercentZ = scale;
		}else{
			scalePercentY = scale;
		}
		break;
	case ID_SCALEUNITZ:
		if(bbox.zmin >= bbox.zmax) break;
		scale = scaleUnitZ / (bbox.zmax - bbox.zmin);
		if(scaleProportional){
			scalePercent = scale;
			scalePercentX = scale;
			scalePercentY = scale;
			scalePercentZ = scale;
		}else{
			scalePercentZ = scale;
		}
		break;
	}
	TransferDataToWindow();
}

void DialogObjectTransformation::OnFlipNormals(wxCommandEvent& event)
{
//	wxLogMessage(
//			wxString::Format(_T("Propagation: %i, ID: %i"),
//					event.ShouldPropagate(), event.GetId()));

	// Button event is not a command event. A new event is generated here
	// and passed to the main frame.
	wxCommandEvent flipEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_OBJECTFLIPNORMALS);
	ProcessEvent(flipEvent);
}
