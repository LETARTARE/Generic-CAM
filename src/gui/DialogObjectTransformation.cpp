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
#include "IDs.h"
#include <wx/event.h>
#include <math.h>

#include "FrameMain.h"
#include "FrameParent.h"

DialogObjectTransformation::DialogObjectTransformation(wxWindow* parent) :
		GUIObjectTransformation(parent)
{
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
	ProjectView* view = GetView();
	CollectionUnits* settings =
			&(wxStaticCast(GetParent()->GetParent(),FrameParent)->units);

	if(project == NULL) return false;

	if(selected.IsSetEmpty() || !selected.IsType(Selection::Object)){
		SetTitle(_("No object selected..."));
		m_textCtrlSizeX->SetValue(_T("-"));
		m_textCtrlSizeY->SetValue(_T("-"));
		m_textCtrlSizeZ->SetValue(_T("-"));
		// Turn off other things.
		return false;
	}

	const bool multiselect = selected.Size() > 1;
	size_t objID = selected[0];

	std::set <size_t> set = selected.GetSet();
	bbox.Clear();
	for(std::set <size_t>::const_iterator it = set.begin(); it != set.end();
			++it){
		if(project->objects.find(*it) == project->objects.end()) continue;
		bbox.Insert(project->objects[*it].bbox);
	}
	if(project->objects.find(objID) == project->objects.end()) return false;
	const Object* obj = &(project->objects[objID]);

	if(multiselect){
		SetTitle(_("Multiple object selected..."));
	}else{
		SetTitle(obj->name);
	}

	// Update Units
	m_textCtrlSizeX->SetValue(settings->Distance.TextFromSI(bbox.GetSizeX()));
	m_textCtrlSizeY->SetValue(settings->Distance.TextFromSI(bbox.GetSizeY()));
	m_textCtrlSizeZ->SetValue(settings->Distance.TextFromSI(bbox.GetSizeZ()));

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
	CollectionUnits* settings =
			&(wxStaticCast(GetParent(),FrameMain)->GetParentFrame()->units);

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

void DialogObjectTransformation::OnXClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogObjectTransformation::OnTransform(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	if(project == NULL) return;
	if(view->selection.IsType(Selection::Anything)) return;
	if(project->objects.find(view->selection.GetBaseID())
			== project->objects.end()) return;
	Object* obj = &(project->objects[view->selection.GetBaseID()]);

	TransferDataFromWindow();

	AffineTransformMatrix newMatrix;
	wxString description; // of the command executed (for the Undo/Redo menu)
	CommandObjectTransform * command;

	bool flipNormals = false;
	bool flipX = false;
	bool flipY = false;
	bool flipZ = false;

// Calculate a common bounding box of all selected objects.
	BoundingBox bbox = obj->bbox;

// Generate the commands for the modifications

	description.Empty();
	newMatrix = obj->matrix; // Copy old to new for a start

	switch(event.GetId()){
	case ID_MULTTEN:
		description = obj->name + _T(": * 10");
		newMatrix.ScaleGlobal(10, 10, 10);
		break;
	case ID_DIVTEN:
		description = obj->name + _T(": / 10");
		newMatrix.ScaleGlobal(0.1, 0.1, 0.1);
		break;
	case ID_SCALEPERCENT:
		description = obj->name
				+ wxString::Format(_T(": scale by %.1f %%"),
						scalePercent * 100);
		newMatrix.ScaleGlobal(scalePercent, scalePercent, scalePercent);
		break;
	case ID_SCALEPERCENTX:
		description = obj->name
				+ wxString::Format(_T(": scale X by %.1f %%"),
						scalePercentX * 100);
		newMatrix.ScaleGlobal(scalePercentX, 1, 1);
		break;
	case ID_SCALEPERCENTY:
		description = obj->name
				+ wxString::Format(_T(": scale Y by %.1f %%"),
						scalePercentY * 100);
		newMatrix.ScaleGlobal(1, scalePercentY, 1);
		break;
	case ID_SCALEPERCENTZ:
		description = obj->name
				+ wxString::Format(_T(": scale Z by %.1f %%"),
						scalePercentZ * 100);
		newMatrix.ScaleGlobal(1, 1, scalePercentZ);
		break;

	case ID_FLIPX:
		description = obj->name
				+ wxString::Format(_T(": mirroring along X axis"));
		flipNormals = true;
		flipX = true;
		break;
	case ID_FLIPY:
		description = obj->name
				+ wxString::Format(_T(": mirroring along Y axis"));
		flipNormals = true;
		flipY = true;
		break;
	case ID_FLIPZ:
		description = obj->name
				+ wxString::Format(_T(": mirroring along Z axis"));
		flipNormals = true;
		flipZ = true;
		break;

	case ID_MOVEXP:
		description = obj->name
				+ wxString::Format(
						_T(": move along X by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(moveStep));
		newMatrix.TranslateGlobal(moveStep, 0, 0);
		break;
	case ID_MOVEXN:
		description = obj->name
				+ wxString::Format(
						_T(": move along X by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(-moveStep));
		newMatrix.TranslateGlobal(-moveStep, 0, 0);
		break;
	case ID_MOVEYP:
		description = obj->name
				+ wxString::Format(
						_T(": move along Y by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(moveStep));
		newMatrix.TranslateGlobal(0, moveStep, 0);
		break;
	case ID_MOVEYN:
		description = obj->name
				+ wxString::Format(
						_T(": move along Y by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(-moveStep));
		newMatrix.TranslateGlobal(0, -moveStep, 0);
		break;
	case ID_MOVEZP:
		description = obj->name
				+ wxString::Format(
						_T(": move along Z by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(moveStep));
		newMatrix.TranslateGlobal(0, 0, moveStep);
		break;
	case ID_MOVEZN:
		description = obj->name
				+ wxString::Format(
						_T(": move along Z by %.3f ")
								+ settings->Distance.GetOtherName(),
						settings->Distance.FromSI(-moveStep));
		newMatrix.TranslateGlobal(0, 0, -moveStep);
		break;

	case ID_ALIGNTOP:
		if(bbox.IsVolumeZero()) break;
		description = obj->name + wxString::Format(_T(": align top"));
		newMatrix.TranslateGlobal(0, 0, -bbox.zmax);
		break;
	case ID_ALIGNMIDDLE:
		if(bbox.IsVolumeZero()) break;
		description = obj->name + wxString::Format(_T(": align middle"));
		newMatrix.TranslateGlobal(0, 0, -(bbox.zmax + bbox.zmin) / 2.0);
		break;
	case ID_ALIGNBOTTOM:
		if(bbox.IsVolumeZero()) break;
		description = obj->name + wxString::Format(_T(": align bottom"));
		newMatrix.TranslateGlobal(0, 0, -bbox.zmin);
		break;
	case ID_ALIGNCENTER:
		if(bbox.IsVolumeZero()) break;
		description = obj->name + wxString::Format(_T(": align center"));
		newMatrix.TranslateGlobal(-(bbox.xmax + bbox.xmin) / 2.0,
				-(bbox.ymax + bbox.ymin) / 2.0, -(bbox.zmax + bbox.zmin) / 2.0);
		break;

	case ID_ROTATEXP:
		description = obj->name
				+ wxString::Format(_T(": rotate around X by %.0f degree"),
						rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(rotateStep, 0, 0)
				* newMatrix;
		break;
	case ID_ROTATEXN:
		description = obj->name
				+ wxString::Format(_T(": rotate around X by %.0f degree"),
						-rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(-rotateStep, 0, 0)
				* newMatrix;
		break;
	case ID_ROTATEYP:
		description = obj->name
				+ wxString::Format(_T(": rotate around Y by %.0f degree"),
						rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(0, rotateStep, 0)
				* newMatrix;
		break;
	case ID_ROTATEYN:
		description = obj->name
				+ wxString::Format(_T(": rotate around Y by %.0f degree"),
						-rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(0, -rotateStep, 0)
				* newMatrix;
		break;
	case ID_ROTATEZP:
		description = obj->name
				+ wxString::Format(_T(": rotate around Z by %.0f degree"),
						rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(0, 0, rotateStep)
				* newMatrix;
		break;
	case ID_ROTATEZN:
		description = obj->name
				+ wxString::Format(_T(": rotate around Z by %.0f degree"),
						-rotateStep);
		newMatrix = AffineTransformMatrix::RotationXYZ(0, 0, -rotateStep)
				* newMatrix;
		break;
	}

	if(!description.IsEmpty()){

//		command = new CommandObjectTransform(description, project, n, flipX,
//				flipY, flipZ, flipNormals, newMatrix);
//		cmdProc->Submit(command);
	}else{
		wxLogMessage
		(
				wxString::Format(
						_T(
								"Unknown ID_... (=%i) in DialogObjectTransformation::OnTransform(...)"),
						event.GetId()));
	}

	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
	ProcessEvent(selectEvent);
}

void DialogObjectTransformation::OnSetFactors(wxCommandEvent& event)
{
	Project* project = GetProject();
	ProjectView* view = GetView();
	if(project == NULL) return;
	if(view->selection.IsType(Selection::Anything)) return;
	if(project->objects.find(view->selection.GetBaseID())
			== project->objects.end()) return;
	Object* obj = &(project->objects[view->selection.GetBaseID()]);

	TransferDataFromWindow();

// Calculate a common bounding box of all selected objects.
	BoundingBox bbox;
	size_t n;
	double scale;
	bbox = obj->bbox;

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

//void DialogObjectTransformation::OnChangeObjectColor(wxColourPickerEvent& event)
//{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
//	Vector3 color;
//	wxColor temp = m_colourPickerObject->GetColour();
//	color.x = (float) temp.Red() / 255.0;
//	color.y = (float) temp.Green() / 255.0;
//	color.z = (float) temp.Blue() / 255.0;
//	for(size_t n = 0; n < project->objects.GetCount(); n++){
//		if(!obj->selected) continue;
//		CommandObjectSetColor* command = new CommandObjectSetColor(
//				_("Set object color"), project, n, color);
//		cmdProc->Submit(command);
//	}
//	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHVIEW);
//	ProcessEvent(selectEvent);
//}

Project* DialogObjectTransformation::GetProject(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}

void DialogObjectTransformation::SetSelection(const Selection& selection)
{
	this->selected = selection;
	TransferDataToWindow();
}

ProjectView* DialogObjectTransformation::GetView(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	return view;
}
