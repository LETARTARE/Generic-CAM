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

#include "../project/command/CommandRunSetObject.h"
#include "FrameMain.h"
#include "FrameParent.h"

DialogJobSetup::DialogJobSetup(wxWindow* parent) :
		GUIJobSetup(parent)
{
	runID = 0;
}

DialogJobSetup::~DialogJobSetup()
{
}

void DialogJobSetup::SetRunID(size_t runID)
{
	this->runID = runID;
	TransferDataToWindow();
}

bool DialogJobSetup::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	if(project == NULL) return false;

	if(!project->Has(Selection::Run, runID)){
		this->SetTitle(_("No run selected..."));
		m_textCtrlObject->SetValue(_T("-"));
		return false;
	}
	const Run &run = project->run[runID];
	this->SetTitle(run.name);

	if(!run.object.IsType(Selection::Object)){
		m_textCtrlObject->SetValue(_("No Object selected."));
	}else{
		wxString temp;
		for(std::set <size_t>::iterator objID = run.object.begin();
				objID != run.object.end(); ++objID){
			if(!temp.IsEmpty()) temp += _T(", ");
			temp += project->objects[*objID].name;
		}
		m_textCtrlObject->SetValue(temp);
	}

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
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project * project = wxStaticCast(frame->GetDocument(), Project);
//	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
//	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	switch(event.GetId()){
	case ID_SELECTOBJECT:
		frame->RequestSelection(this, ID_SELECTOBJECT, false,
				Selection(Selection::Object));
		break;

	case ID_SELECTAXISX:
	case ID_SELECTAXISY:
	case ID_SELECTAXISZ:
		frame->RequestSelection(this, event.GetId(), false,
				Selection(Selection::Axis),
				Selection(Selection::TriangleGroup));
		break;

	default:
		std::cout << "DialogJobSetup::OnSelect - unhandled ID: "
				<< event.GetId() << "\n";
		break;
	}
	this->Hide();
	frame->SetFocus();
}

bool DialogJobSetup::OnSelected(size_t ID, Selection selection)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = project->GetCommandProcessor();
	//	CollectionUnits* settings = &(frame->GetParentFrame()->units);

	if(!selection.IsType(Selection::Object)) return false;

	switch(ID){
	case ID_SELECTOBJECT:
	{
		cmdProc->Submit(
				new CommandRunSetObject(_("Change object selectionfor run."),
						project, runID, selection));
//		wxString temp;
//		for(std::map <size_t, Object>::const_iterator obj =
//				project->objects.begin(); obj != project->objects.end(); ++obj){
//			if(selection.Has(Selection::Object, obj->first)){
//				temp += wxString(obj->second.name);
//			}
//		}
		break;
	}
	default:
	{
		std::cout << "DialogJobSetup::OnSelected - unhandled ID: " << ID
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
}
