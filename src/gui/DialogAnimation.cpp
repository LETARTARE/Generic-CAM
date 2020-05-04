///////////////////////////////////////////////////////////////////////////////
// Name               : DialogAnimation.cpp
// Purpose            : A window displaying the animation controls.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.07.2011
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogAnimation.h"

#include <math.h>
#include "../icon/play.xpm"
#include "../icon/stop.xpm"
#include "../project/generator/CNCSimulator.h"
#include "../project/ProjectView.h"
#include "FrameMain.h"
#include "IDs.h"

DialogAnimation::DialogAnimation(wxWindow* parent) :
		GUIAnimation(parent)
{
	runID = 0;
	simulator = NULL;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	simulator = &(view->simulator);
	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(DialogAnimation::OnTimer),
	NULL, this);
}

DialogAnimation::~DialogAnimation()
{
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(DialogAnimation::OnTimer),
	NULL, this);
}

void DialogAnimation::SetSelection(const Selection &selection)
{
	size_t oldRunID = runID;

	if(selection.IsBaseType(Selection::BaseRun)){
		runID = selection.GetBaseID();
	}
	if(selection.IsType(Selection::Run) && !selection.IsSetEmpty()){
		runID = selection[0];
	}

	const FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	const Project * project = wxStaticCast(frame->GetDocument(), Project);

	if(!project->Has(Selection(Selection::Run, this->runID))){
		runID = oldRunID;
		return;
	}
	const Run * run = project->GetRun(runID);
	simulator->SetTools(project->GetTools());
	simulator->InsertToolPath(&(run->toolpath));
	simulator->origin = run->origin;

	if(runID != oldRunID){
		//	if(DEBUG) printf(
		//			"DialogAnimation::InitSimulation - Dexeltarget: %p with N=%zu\n",
		//			&(run->base), run->base.GetCountTotal());
		simulator->InsertBase(&(run->start));
		simulator->Reset();
	}

	if(!selection.IsType(Selection::Generator)) return;
	if(selection.IsSetEmpty()) return;

//	this->generatorID = selection[0];
//	TransferDataToWindow();
}

bool DialogAnimation::SelectionIsOK(void) const
{
	const FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	const Project* project = wxStaticCast(frame->GetDocument(), Project);
	return (project->Has(Selection(Selection::Run, this->runID)));
}

bool DialogAnimation::TransferDataToWindow(void)
{
	if(!this->IsShown()) return false;
	if(loopGuard.TryLock() == wxMUTEX_BUSY) return false;

	if(timer.IsRunning()){
		m_bpButtonPlayStop->SetBitmapLabel(wxIcon(stop_xpm));
	}else{
		m_bpButtonPlayStop->SetBitmapLabel(wxIcon(play_xpm));
	}
	if(simulator == NULL){
		m_textCtrlMaxTime->SetValue(SecondsToTC(0));
		m_textCtrlTime->SetValue(SecondsToTC(0));
		loopGuard.Unlock();
		return false;
	}else{
		m_textCtrlMaxTime->SetValue(SecondsToTC(simulator->GetMaxTime()));
		m_textCtrlTime->SetValue(SecondsToTC(simulator->GetTime()));
	}
	if(!SelectionIsOK()){
		loopGuard.Unlock();
		return false;
	}

	const FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	const Project * project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView * view = wxStaticCast(frame->GetView(), ProjectView);
	const Run * run = project->GetRun(runID);

	view->showSimulated = m_checkBoxSimulateWorkpiece->GetValue();

	int simulationdisplay = m_choiceDisplay->GetCurrentSelection();
	if(simulationdisplay == 0) view->simulationDisplay =
			ProjectView::vSimulationWorkpiece;
	if(simulationdisplay == 1) view->simulationDisplay =
			ProjectView::vSimulationTool;
	if(simulationdisplay == 2) view->simulationDisplay =
			ProjectView::vSimulationHolder;
	if(simulationdisplay == 3) view->simulationDisplay =
			ProjectView::vSimulationMachine;
	int simulationcenter = m_choiceFocus->GetCurrentSelection();
	if(simulationcenter == 0) view->simulationCenter =
			ProjectView::vCenterWorkpiece;
	if(simulationcenter == 1) view->simulationCenter = ProjectView::vCenterTool;
	if(simulationcenter == 2) view->simulationCenter =
			ProjectView::vCenterMachine;

	simulator->LoadMachine(run->machinefile);

	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_REFRESHALL3D);
	ProcessEvent(refreshEvent);

	loopGuard.Unlock();
	return true;
}

void DialogAnimation::OnClose(wxCommandEvent& event)
{
	if(timer.IsRunning()){
		timer.Stop();
		TransferDataToWindow();
	}
	this->Show(false);
	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHALL);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnXClose(wxCloseEvent &event)
{
	if(timer.IsRunning()){
		timer.Stop();
		TransferDataToWindow();
	}
//	int selectedRun = GetSelectedRun();
//	Project* project = GetProject();
//	if(project != NULL && selectedRun >= 0) project->run[selectedRun].showSimulation =
//			false;
	this->Show(false);
	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHALL);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnChangeTime(wxCommandEvent& event)
{
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnScroll(wxScrollEvent& event)
{
	if(simulator == NULL) return;
	if(loopGuard.TryLock() == wxMUTEX_BUSY) return;

	double target = simulator->GetMaxTime()
			/ (double) (m_sliderTime->GetMax() - m_sliderTime->GetMin())
			* (double) (event.GetPosition() - m_sliderTime->GetMin());

	simulator->Step(target);

//	const int toolNr = generator->refTool;
//	if(toolNr < 0 || toolNr >= run->tools.GetCount()) return;
//	const Tool * const tool = &(run->tools[toolNr]);

//	workpiece->InitSimulation(1000000);
//	workpiece->simulation.Simulate(generator->toolpath, *tool);

	loopGuard.Unlock();
	TransferDataToWindow();
}

void DialogAnimation::OnFirst(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	simulator->Reset(); // TODO Remove the true, the recalculation of the timing is only needed here, because it is not handled correctly.
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnPrev(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	simulator->Previous();
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnPlayStop(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	if(!timer.IsRunning()){
		timer.Start(100);
	}else{
		timer.Stop();
	}
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnNext(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	simulator->Next();
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnLast(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	simulator->Last();
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::PositionSlider(void)
{
	if(loopGuard.TryLock() == wxMUTEX_BUSY) return;

	if(simulator == NULL){
		m_sliderTime->SetValue(m_sliderTime->GetMin());
		m_sliderTime->Enable(false);
	}else{
		m_sliderTime->SetValue(
				((double) (m_sliderTime->GetMax() - m_sliderTime->GetMin())
						/ simulator->GetMaxTime() * simulator->GetTime())
						+ m_sliderTime->GetMin());
		m_sliderTime->Enable(true);
	}
	loopGuard.Unlock();
}

void DialogAnimation::OnTimer(wxTimerEvent& event)
{
	if(simulator == NULL) return;
	if(loopGuard.TryLock() == wxMUTEX_BUSY) return;
	if(!this->IsShown()) timer.Stop();

	double target = simulator->GetTime() + 0.5;
	if(target >= simulator->GetMaxTime()){
		timer.Stop();
		target = simulator->GetMaxTime();
	}
	simulator->Step(target);
	loopGuard.Unlock();
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnChangeView(wxCommandEvent& event)
{
	TransferDataToWindow();
}

wxString DialogAnimation::SecondsToTC(const double t)
{
	return wxString::Format(_T("%02i:%02i:%02i"), (int) floor(t / 3600.0),
			((int) floor(t / 60.0)) % 60, ((int) floor(t)) % 60);
}

