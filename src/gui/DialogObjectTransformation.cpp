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

#include "../project/command/CommandObjectTransform.h"
#include "../project/command/CommandObjectSetColor.h"
#include "IDs.h"
#include <wx/event.h>
#include <math.h>

#include "FrameMain.h"
#include "FrameParent.h"

DialogObjectTransformation::DialogObjectTransformation(wxWindow* parent) :
		GUIObjectTransformation(parent)
{
	m_menuPreferences->Append(ID_SETUPUNITS, _("Setup &Units") + wxT("\tCtrl+U"));

	scaleProportional = true;
	scalePercent = 1;
	scalePercentX = 1;
	scalePercentY = 1;
	scalePercentZ = 1;
	scaleUnitX = 1;
	scaleUnitY = 1;
	scaleUnitZ = 1;
	moveStep = 0.05;
	rotateStep = M_PI_2;

	c = 0;
}

DialogObjectTransformation::~DialogObjectTransformation()
{
}

bool DialogObjectTransformation::TransferDataToWindow(void)
{
	if(!this->IsShown()) return false;
	Project* project = GetProject();
	CollectionUnits* settings = &(wxStaticCast(GetParent()->GetParent(),FrameParent)->units);
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
	Vector3 color;
	if(selection >= 0){
		m_choiceObjectSelection->SetSelection(selection);

		if(project->objects[selection].geometries.GetCount() > 0){
			color = project->objects[selection].geometries[0].color;

		}
	}
	m_colourPickerObject->SetColour(
	wxColor(floor(color.x * 255), floor(color.y * 255), floor(color.z * 255)));

	// Update Units

	if(selection >= 0){
		m_textCtrlSizeX->SetValue(
				settings->Distance.TextFromSI(
						project->objects[selection].bbox.GetSizeX()));
		m_textCtrlSizeY->SetValue(
				settings->Distance.TextFromSI(
						project->objects[selection].bbox.GetSizeY()));
		m_textCtrlSizeZ->SetValue(
				settings->Distance.TextFromSI(
						project->objects[selection].bbox.GetSizeZ()));
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
	m_staticTextUnitAngle->SetLabel(settings->Angle.GetOtherName());

	m_textCtrlScaleUnitX->SetValue(settings->Distance.TextFromSI(scaleUnitX));
	m_textCtrlScaleUnitY->SetValue(settings->Distance.TextFromSI(scaleUnitY));
	m_textCtrlScaleUnitZ->SetValue(settings->Distance.TextFromSI(scaleUnitZ));

	m_textCtrlScalePercent->SetValue(
			wxString::Format(_T("%.1f"), scalePercent * 100));
	m_textCtrlScalePercentX->SetValue(
			wxString::Format(_T("%.1f"), scalePercentX * 100));
	m_textCtrlScalePercentY->SetValue(
			wxString::Format(_T("%.1f"), scalePercentY * 100));
	m_textCtrlScalePercentZ->SetValue(
			wxString::Format(_T("%.1f"), scalePercentZ * 100));

	m_textCtrlMoveStep->SetValue(settings->Distance.TextFromSI(moveStep));
	m_textCtrlRotateStep->SetValue(settings->Angle.TextFromSI(rotateStep));

	m_checkBoxScaleProportionally->SetValue(scaleProportional);

//	c++;
//	wxLogMessage(
//			wxString::Format(_T("Transfer: %u - Selection: %i"), c, selection));

	this->Refresh();
	return true;
}
bool DialogObjectTransformation::TransferDataFromWindow(void)
{
	CollectionUnits* settings = &(wxStaticCast(GetParent(),FrameMain)->GetParentFrame()->units);

	m_textCtrlScalePercent->GetValue().ToDouble(&scalePercent);
	m_textCtrlScalePercentX->GetValue().ToDouble(&scalePercentX);
	m_textCtrlScalePercentY->GetValue().ToDouble(&scalePercentY);
	m_textCtrlScalePercentZ->GetValue().ToDouble(&scalePercentZ);
	m_textCtrlScaleUnitX->GetValue().ToDouble(&scaleUnitX);
	m_textCtrlScaleUnitY->GetValue().ToDouble(&scaleUnitY);
	m_textCtrlScaleUnitZ->GetValue().ToDouble(&scaleUnitZ);

	m_textCtrlMoveStep->GetValue().ToDouble(&moveStep);
	m_textCtrlRotateStep->GetValue().ToDouble(&rotateStep);

	scaleUnitX = settings->Distance.ToSI(scaleUnitX);
	scaleUnitY = settings->Distance.ToSI(scaleUnitY);
	scaleUnitZ = settings->Distance.ToSI(scaleUnitZ);
	moveStep = settings->Distance.ToSI(moveStep);
	rotateStep = settings->Angle.ToSI(rotateStep);

	scaleProportional = m_checkBoxScaleProportionally->GetValue();

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
void DialogObjectTransformation::OnXClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogObjectTransformation::OnSelectObject(wxCommandEvent& event)
{
	Project* project = GetProject();
	int id = m_choiceObjectSelection->GetSelection();
	// Return if "Multiple objects selected." was selected again.
	if(id >= project->objects.GetCount()) return;

	size_t n;
	for(n = 0; n < project->objects.GetCount(); n++)
		project->objects[n].selected = (n == id);

	// Tell the main frame to update the selection in the treeview via custom command.
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogObjectTransformation::OnTransform(wxCommandEvent& event)
{
	Project* project = GetProject();
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
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
		BoundingBox temp = project->objects[n].bbox;
		temp.Transform((project->objects[n].displayTransform));
		bbox.Insert(temp);
	}

	// Generate the commands for the modifications
	for(n = 0; n < project->objects.GetCount(); ++n){
		if(!project->objects[n].selected) continue;

		description.Empty();
		newMatrix = project->objects[n].displayTransform
				* project->objects[n].matrix; // Copy old to new for a start

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
		case ID_ALIGNCENTER:
			if(bbox.IsVolumeZero()) break;
			description = project->objects[n].name
					+ wxString::Format(_T(": align center"));
			newMatrix.TranslateGlobal(-(bbox.xmax + bbox.xmin) / 2.0,
					-(bbox.ymax + bbox.ymin) / 2.0,
					-(bbox.zmax + bbox.zmin) / 2.0);
			break;

		case ID_ROTATEXP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around X by %.0f degree"),
							rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(rotateStep, 0, 0)
					* newMatrix;
			break;
		case ID_ROTATEXN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around X by %.0f degree"),
							-rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(-rotateStep, 0, 0)
					* newMatrix;
			break;
		case ID_ROTATEYP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Y by %.0f degree"),
							rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(0, rotateStep, 0)
					* newMatrix;
			break;
		case ID_ROTATEYN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Y by %.0f degree"),
							-rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(0, -rotateStep, 0)
					* newMatrix;
			break;
		case ID_ROTATEZP:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Z by %.0f degree"),
							rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(0, 0, rotateStep)
					* newMatrix;
			break;
		case ID_ROTATEZN:
			description = project->objects[n].name
					+ wxString::Format(_T(": rotate around Z by %.0f degree"),
							-rotateStep);
			newMatrix = AffineTransformMatrix::RotationXYZ(0, 0, -rotateStep)
					* newMatrix;
			break;
		}

		if(!description.IsEmpty()){

			command = new CommandObjectTransform(description, project, n, flipX,
					flipY, flipZ, flipNormals, newMatrix);
			cmdProc->Submit(command);
		}else{
			wxLogMessage
			(
					wxString::Format(
							_T(
									"Unknown ID_... (=%i) in DialogObjectTransformation::OnTransform(...)"),
							event.GetId()));
		}
	}

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogObjectTransformation::OnSetFactors(wxCommandEvent& event)
{
	Project* project = GetProject();
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

void DialogObjectTransformation::OnChangeObjectColor(wxColourPickerEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(),Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	Vector3 color;
	wxColor temp = m_colourPickerObject->GetColour();
	color.x = (float) temp.Red() / 255.0;
	color.y = (float) temp.Green() / 255.0;
	color.z = (float) temp.Blue() / 255.0;
	for(size_t n = 0; n < project->objects.GetCount(); n++){
		if(!project->objects[n].selected) continue;
		CommandObjectSetColor* command = new CommandObjectSetColor(
				_("Set object color"), project, n, color);
		cmdProc->Submit(command);
	}
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

Project* DialogObjectTransformation::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}
