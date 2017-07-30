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

#include "IDs.h"

DialogAnimation::DialogAnimation(wxWindow* parent, Project *project) :
		GUIAnimation(parent)
{
	this->project = project;
}

DialogAnimation::~DialogAnimation()
{
	return;
}

int DialogAnimation::GetSelectedRun(void)
{
	if(project == NULL) return -1;
	int selected = -1;
	for(size_t i = 0; i < project->run.GetCount(); i++){
		if(selected == -1 && project->run[i].selected) selected = i;
	}
	return selected;
}

bool DialogAnimation::TransferDataToWindow(void)
{

	int selected = -1;
	m_choiceToolpath->Clear();
	m_choiceToolpath->Append(_T(""));

	for(size_t i = 0; i < project->run.GetCount(); i++){
		m_choiceToolpath->Append(project->run[i].name);
		if(selected == -1 && project->run[i].selected) selected = i;
	}
	m_choiceToolpath->SetSelection(selected + 1);

	return true;
}
bool DialogAnimation::TransferDataFromWindow(void)
{
	return true;
}

void DialogAnimation::OnXClose(wxCloseEvent &event)
{
	this->Show(false);
	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHALL);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnSelectToolpath(wxCommandEvent& event)
{
}

void DialogAnimation::OnChangeTime(wxCommandEvent& event)
{
}

void DialogAnimation::OnScroll(wxScrollEvent& event)
{
	if(project == NULL) return;

	const int runNr = GetSelectedRun();
	if(runNr < 0 || runNr >= project->run.GetCount()) return;
	const Run * const run = &(project->run[runNr]);

	const int workpieceNr = run->refWorkpiece;
	if(workpieceNr < 0 || workpieceNr >= project->workpieces.GetCount()) return;
	Workpiece * const workpiece = &(project->workpieces[workpieceNr]);

	const int generatorNr = 0;
	if(generatorNr < 0 || generatorNr >= run->generators.GetCount()) return;
	const Generator * const generator = run->generators[generatorNr];

//	const int toolNr = generator->refTool;
//	if(toolNr < 0 || toolNr >= run->tools.GetCount()) return;
//	const Tool * const tool = &(run->tools[toolNr]);

//	workpiece->InitSimulation(1000000);
//	workpiece->simulation.Simulate(generator->toolpath, *tool);

	wxCommandEvent refreshEvent(wxEVT_COMMAND_MENU_SELECTED,
			ID_UPDATESIMULATION);
	ProcessEvent(refreshEvent);
}

void DialogAnimation::OnFirst(wxCommandEvent& event)
{
}

void DialogAnimation::OnPrev(wxCommandEvent& event)
{
}

void DialogAnimation::OnPlayStop(wxCommandEvent& event)
{
}

void DialogAnimation::OnNext(wxCommandEvent& event)
{
}

void DialogAnimation::OnLast(wxCommandEvent& event)
{
}
