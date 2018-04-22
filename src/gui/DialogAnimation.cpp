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
#include "IDs.h"

DialogAnimation::DialogAnimation(wxWindow* parent, Project *project) :
		GUIAnimation(parent)
{
	this->project = project;
	this->run = NULL;
	this->simulator = NULL;
	loopGuard = false;
	simulateWorkpiece = true;
	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(DialogAnimation::OnTimer),
	NULL, this);
}

DialogAnimation::~DialogAnimation()
{
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(DialogAnimation::OnTimer),
	NULL, this);
}

int DialogAnimation::GetSelectedRun(void)
{
	if(project == NULL) return -1;
	return project->GetFirstSelectedRun();
}

void DialogAnimation::InitSimulation(void)
{
	int runNr = GetSelectedRun();
	if(runNr >= 0){
		run = &(project->run[runNr]);
		Workpiece * workpiece = run->GetWorkpiece();
		simulator = &(run->simulator);
		simulator->InsertMachine(&(run->machine));
		simulator->InsertToolPath(run->GetFirstSelectedToolpath());
		if(workpiece != NULL){
			workpiece->PrepareModel();
			model.CopyRescale(workpiece->model, 2e5);
		}
		simulator->InsertTarget(&model);
	}else{
		run = NULL;
		if(simulator != NULL){
			simulator->InsertMachine(NULL);
			simulator->InsertToolPath(NULL);
		}
		simulator = NULL;
	}
}
bool DialogAnimation::TransferDataToWindow(void)
{
	if(loopGuard) return false;

	simulateWorkpiece = m_checkBoxSimulateWorkpiece->GetValue();

	m_choiceToolpath->Clear();
	m_choiceToolpath->Append(_T(""));

	int selected = -1;
	if(project != NULL){
		for(size_t i = 0; i < project->run.GetCount(); i++){
			m_choiceToolpath->Append(project->run[i].name);
			if(selected == -1 && project->run[i].selected) selected = i;
		}
		m_choiceToolpath->SetSelection(selected + 1);
		if(selected >= 0 && this->IsShown()){
			project->run[selected].showSimulation = simulateWorkpiece;
		}
	}else{
		m_choiceToolpath->Append(_T("No run found."));
		m_choiceToolpath->SetSelection(0);
	}

	if(this->IsShown()){
		InitSimulation();
	}

	loopGuard = true;

	if(timer.IsRunning()){
		m_bpButtonPlayStop->SetBitmapLabel(wxIcon(stop_xpm));
	}else{
		m_bpButtonPlayStop->SetBitmapLabel(wxIcon(play_xpm));
	}

	if(simulator != NULL){
		m_textCtrlMaxTime->SetValue(SecondsToTC(simulator->GetMaxTime()));
		m_textCtrlTime->SetValue(SecondsToTC(simulator->GetTime()));

		m_textCtrl0->SetValue(simulator->GetCurrentGCode(-2));
		m_textCtrl1->SetValue(simulator->GetCurrentGCode(-1));
		m_textCtrl2->SetValue(simulator->GetCurrentGCode(0));
		m_textCtrl3->SetValue(simulator->GetCurrentGCode(1));
		m_textCtrl4->SetValue(simulator->GetCurrentGCode(2));
	}else{
		m_textCtrlMaxTime->SetValue(SecondsToTC(0));
		m_textCtrlTime->SetValue(SecondsToTC(0));

		m_textCtrl0->SetValue(_T(""));
		m_textCtrl1->SetValue(_T(""));
		m_textCtrl2->SetValue(_T(""));
		m_textCtrl3->SetValue(_T(""));
		m_textCtrl4->SetValue(_T(""));
	}

	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_UPDATESIMULATION);
	ProcessEvent(refreshEvent);

	loopGuard = false;

	return true;
}

void DialogAnimation::OnXClose(wxCloseEvent &event)
{
	if(timer.IsRunning()){
		timer.Stop();
		TransferDataToWindow();
	}
	int selectedRun = GetSelectedRun();
	if(project != NULL && selectedRun >= 0) project->run[selectedRun].showSimulation =
			false;
	this->Show(false);
	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHALL);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnClose(wxCommandEvent& event)
{
	if(timer.IsRunning()){
		timer.Stop();
		TransferDataToWindow();
	}
	int selectedRun = GetSelectedRun();
	if(project != NULL && selectedRun >= 0) project->run[selectedRun].showSimulation =
			false;
	this->Show(false);
	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHALL);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnSelectToolpath(wxCommandEvent& event)
{
	TransferDataToWindow();
}

void DialogAnimation::OnChangeTime(wxCommandEvent& event)
{
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnScroll(wxScrollEvent& event)
{
	if(loopGuard) return;
	if(simulator == NULL) return;

	double target = simulator->GetMaxTime()
			/ (double) (m_sliderTime->GetMax() - m_sliderTime->GetMin())
			* (double) (event.GetPosition() - m_sliderTime->GetMin());

	simulator->Step(target);
	TransferDataToWindow();

//	const int toolNr = generator->refTool;
//	if(toolNr < 0 || toolNr >= run->tools.GetCount()) return;
//	const Tool * const tool = &(run->tools[toolNr]);

//	workpiece->InitSimulation(1000000);
//	workpiece->simulation.Simulate(generator->toolpath, *tool);

}

void DialogAnimation::OnFirst(wxCommandEvent& event)
{
	if(simulator == NULL) return;
	simulator->Reset(true); // TODO Remove the true, the recalculation of the timing is only needed here, because it is not handled correctly.
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
	if(loopGuard) return;
	loopGuard = true;
	if(simulator != NULL){
		m_sliderTime->SetValue(
				((double) (m_sliderTime->GetMax() - m_sliderTime->GetMin())
						/ simulator->GetMaxTime() * simulator->GetTime())
						+ m_sliderTime->GetMin());
		m_sliderTime->Enable(true);
	}else{
		m_sliderTime->SetValue(m_sliderTime->GetMin());
		m_sliderTime->Enable(false);
	}
	loopGuard = false;
}

void DialogAnimation::OnTimer(wxTimerEvent& event)
{
	if(!this->IsShown()) timer.Stop();
	if(loopGuard) return;
	if(simulator == NULL) return;
	double target = simulator->GetTime() + 0.5;
	if(target >= simulator->GetMaxTime()){
		timer.Stop();
		target = simulator->GetMaxTime();
	}
	simulator->Step(target);
	PositionSlider();
	TransferDataToWindow();
}

void DialogAnimation::OnChangeSimulation(wxCommandEvent& event)
{
	simulateWorkpiece = m_checkBoxSimulateWorkpiece->GetValue();
	TransferDataToWindow();
}

wxString DialogAnimation::SecondsToTC(const double t)
{
	return wxString::Format(_T("%02i:%02i:%02i"), (int) floor(t / 3600.0),
			((int) floor(t / 60.0)) % 60, ((int) floor(t)) % 60);
}
