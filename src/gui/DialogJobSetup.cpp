///////////////////////////////////////////////////////////////////////////////
// Name               : DialogJobSetup.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.11.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogJobSetup.h"

#include "../project/command/CommandRunSetCorrdinateSystem.h"
#include "../project/command/CommandRunSetObject.h"
#include "../project/command/CommandRunSetStockBox.h"
#include "../project/command/CommandRunSetStockObject.h"
#include "../project/command/CommandRunSetStockOrigin.h"
#include "../project/command/CommandRunSetStockType.h"
#include "../project/Project.h"
#include "../project/ProjectView.h"
#include "FrameMain.h"
#include "FrameParent.h"

DialogJobSetup::DialogJobSetup(wxWindow* parent) :
		GUIJobSetup(parent)
{
	runID = 0;
	oldType = Run::BoxCenter;
}

DialogJobSetup::~DialogJobSetup()
{
}

void DialogJobSetup::SetSelection(const Selection &selection)
{
	size_t oldID = this->runID;
	if(selection.IsBaseType(Selection::BaseRun)){
		this->runID = selection.GetBaseID();
	}
	if(selection.IsType(Selection::Run) && !selection.IsSetEmpty()){
		this->runID = selection[0];
	}
	if(this->runID == oldID) return;
	std::cout << "DialogJobSetup::SetSelection(" << this->runID << ");\n";
	TransferDataToWindow();
}

bool DialogJobSetup::SelectionIsOK(void) const
{
	const FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	const Project* project = wxStaticCast(frame->GetDocument(), Project);
	if(project == NULL) return false;
	return (project->Has(Selection(Selection::Run, this->runID)));
}

bool DialogJobSetup::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	const Project * project = wxStaticCast(frame->GetDocument(), Project);
	if(project == NULL) return false;
	const CollectionUnits* settings = &(frame->GetParentFrame()->units);

	m_staticTextUnitBoxX->SetLabelText(settings->Distance.GetOtherName());
	m_staticTextUnitBoxY->SetLabelText(settings->Distance.GetOtherName());
	m_staticTextUnitBoxZ->SetLabelText(settings->Distance.GetOtherName());

	if(!project->Has(Selection::Run, runID)){
		this->SetTitle(_("No run selected..."));
		m_textCtrlObject->SetValue(_T("-"));
		m_textCtrlAxisX->SetValue(_T("-"));
		m_textCtrlAxisY->SetValue(_T("-"));
		m_textCtrlAxisZ->SetValue(_T("-"));
		return false;
	}
	const Run * run = project->GetRun(runID);
	this->SetTitle(run->name);

	if(!run->object.IsType(Selection::Object)){
		m_textCtrlObject->SetValue(_("No Object selected."));
	}else{
		wxString temp;
		for(std::set <size_t>::iterator objID = run->object.begin();
				objID != run->object.end(); ++objID){
			if(!temp.IsEmpty()) temp += _T(", ");
			temp += project->Get3DObject(*objID)->name;
		}
		m_textCtrlObject->SetValue(temp);
	}
	m_textCtrlAxisX->SetValue(run->coordX.ToString());
	m_textCtrlAxisY->SetValue(run->coordY.ToString());
	m_textCtrlAxisZ->SetValue(run->coordZ.ToString());

	m_choicebookStock->SetSelection((run->stocktype == Run::sObject)? 1 : 0);

	if(project->Has(Selection::Object, run->stockobject)){
		m_textCtrlStockObject->SetValue(
				project->Get3DObject(run->stockobject)->name);
	}else{
		m_textCtrlStockObject->SetValue(_T("-"));
	}

	wxString temp = wxString::Format(_T("(%g, %g, %g)"),
			run->stockorigin.x * 2 - 1, run->stockorigin.y * 2 - 1,
			run->stockorigin.z * 2 - 1);
	m_textCtrlOrigin->SetValue(temp);

	m_textCtrlBoxX->SetValue(settings->Distance.TextFromSI(run->stocksize.x));
	m_textCtrlBoxY->SetValue(settings->Distance.TextFromSI(run->stocksize.y));
	m_textCtrlBoxZ->SetValue(settings->Distance.TextFromSI(run->stocksize.z));

	if(run->stocktype == Run::BoxTop) m_radioBox->SetSelection(0);
	if(run->stocktype == Run::BoxCenter) m_radioBox->SetSelection(1);
	if(run->stocktype == Run::BoxBottom) m_radioBox->SetSelection(2);

	if(run->stocktype == Run::BoxTop || run->stocktype == Run::BoxCenter
			|| run->stocktype == Run::BoxBottom) oldType = run->stocktype;

	return true;
}

bool DialogJobSetup::TransferDataFromWindow(void)
{
	return true;
}

void DialogJobSetup::OnXClose(wxCloseEvent& event)
{
	this->Hide();
}

void DialogJobSetup::OnSelect(wxCommandEvent& event)
{
	if(runID == 0) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project * project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
//	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	switch(event.GetId()){
	case ID_SELECTOBJECT:
		view->type = ProjectView::vObject;
		frame->SetRequestSelection(this, event.GetId(), true,
				Selection(Selection::Object));
		break;

	case ID_SELECTAXISX:
	case ID_SELECTAXISY:
	case ID_SELECTAXISZ:
		frame->SetRequestSelection(this, event.GetId(), false,
				Selection(Selection::Axis));
		frame->AddRequestSelection(Selection(Selection::EdgeGroup));
		break;

	case ID_SELECTOBJECTSTOCK:
		view->type = ProjectView::vObject;
		frame->SetRequestSelection(this, event.GetId(), false,
				Selection(Selection::Object));
		break;

	case ID_SELECTORIGIN:
		view->type = ProjectView::vOrigin;
		frame->SetRequestSelection(this, event.GetId(), false,
				Selection(Selection::BaseRun, runID, Selection::Vertex));
		break;

	default:
		std::cout << "DialogJobSetup::OnSelect - unhandled ID: "
				<< event.GetId() << "\n";
		break;
	}
	this->Hide();
	frame->SetFocus();
}

bool DialogJobSetup::OnSelected(size_t ID, Selection selection, bool successful)
{
	if(runID == 0) return false;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();
	//	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	switch(ID){
	case ID_SELECTOBJECT:
	{
		std::cout << "DialogJobSetup::OnSelected(" << ID << ", "
				<< selection.ToString() << ")";
		if(!selection.IsType(Selection::Object)){
			std::cout << " ->not an Selection::Object;\n";
			return false;
		}
		std::cout << ";\n";
		cmdProc->Submit(
				new CommandRunSetObject(_("Change object selectionfor run."),
						project, runID, selection));
		break;
	}
	case ID_SELECTAXISX:
	{
		cmdProc->Submit(
				new CommandRunSetCorrdinateSystem(_("Change axis X."), project,
						runID, 0, selection));
		break;
	}
	case ID_SELECTAXISY:
	{
		cmdProc->Submit(
				new CommandRunSetCorrdinateSystem(_("Change axis Y."), project,
						runID, 1, selection));
		break;
	}
	case ID_SELECTAXISZ:
	{
		cmdProc->Submit(
				new CommandRunSetCorrdinateSystem(_("Change axis Z."), project,
						runID, 2, selection));
		break;
	}

	case ID_SELECTOBJECTSTOCK:
	{
		std::cout << "DialogJobSetup::OnSelected(" << ID << ", "
				<< selection.ToString() << ")";
		if(!selection.IsType(Selection::Object)){
			std::cout << " ->not an Selection::Object;\n";
			return false;
		}
		std::cout << ";\n";
		cmdProc->Submit(
				new CommandRunSetStockObject(
						_("Change stockobject selection for run."), project,
						runID, selection[0]));
		break;
	}

	case ID_SELECTORIGIN:
	{

		if(selection.IsType(Selection::Vertex)){
			double x = (double) (selection[0] % 3) / 2.0;
			double y = (double) ((selection[0] / 3) % 3) / 2.0;
			double z = (double) ((selection[0] / 9) % 3) / 2.0;
			cmdProc->Submit(
					new CommandRunSetStockOrigin(_("Select origin."), project,
							runID, Vector3(x, y, z)));
		}

		break;
	}

	default:
	{
		std::cout << "DialogJobSetup::OnSelected(...) -> unhandled ID: " << ID
				<< "\n";
		break;
	}
	}
	this->Show();
	this->TransferDataToWindow();
	Refresh();
	return true;
}

void DialogJobSetup::OnGetSizeFromObject(wxCommandEvent& event)
{
	if(runID == 0) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();
	if(project->GetRun(runID)->object.Size() == 0) return;
	size_t objID = project->GetRun(runID)->object[0];
	if(!project->Has(Selection::Object, objID)) return;

	BoundingBox bbox = project->GetBBox(Selection(Selection::Object, objID));

	cmdProc->Submit(
			new CommandRunSetStockBox(_("Change size."), project, runID,
					Vector3(bbox.GetSizeX(), bbox.GetSizeY(),
							bbox.GetSizeZ())));

}

void DialogJobSetup::OnChoicebookPageChanged(wxChoicebookEvent& event)
{
	if(runID == 0) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();

	if(event.GetSelection() == event.GetOldSelection()) return;

	if(event.GetSelection() == 0){
		cmdProc->Submit(
				new CommandRunSetStockType(_("Change type."), project, runID,
						oldType));
	}
	if(event.GetSelection() == 1){
		oldType = project->GetRun(runID)->stocktype;
		cmdProc->Submit(
				new CommandRunSetStockType(_("Change type."), project, runID,
						Run::sObject));
	}
}

void DialogJobSetup::OnTextEnter(wxCommandEvent& event)
{
	if(runID == 0) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	Vector3 size = project->GetRun(runID)->stocksize;
	double temp = settings->Distance.SIFromString(event.GetString());
	if(event.GetId() == ID_SETSIZEX){
		cmdProc->Submit(
				new CommandRunSetStockBox(_("Change stock size X."), project,
						runID, Vector3(temp, size.y, size.z)));
	}
	if(event.GetId() == ID_SETSIZEY){
		cmdProc->Submit(
				new CommandRunSetStockBox(_("Change stock size Y."), project,
						runID, Vector3(size.x, temp, size.z)));
	}
	if(event.GetId() == ID_SETSIZEZ){
		cmdProc->Submit(
				new CommandRunSetStockBox(_("Change stock size Z."), project,
						runID, Vector3(size.x, size.y, temp)));
	}
}

void DialogJobSetup::OnRadioBox(wxCommandEvent& event)
{
	if(runID == 0) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();

	oldType = project->GetRun(runID)->stocktype;

	if(event.GetSelection() == 0){
		cmdProc->Submit(
				new CommandRunSetStockType(_("Change type."), project, runID,
						Run::BoxTop));
	}
	if(event.GetSelection() == 1){
		cmdProc->Submit(
				new CommandRunSetStockType(_("Change type."), project, runID,
						Run::BoxCenter));
	}
	if(event.GetSelection() == 2){
		cmdProc->Submit(
				new CommandRunSetStockType(_("Change type."), project, runID,
						Run::BoxBottom));
	}
}

void DialogJobSetup::OnMachineSelected(wxFileDirPickerEvent& event)
{
}
