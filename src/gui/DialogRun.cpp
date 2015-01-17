///////////////////////////////////////////////////////////////////////////////
// Name               : DialogRun.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.01.2015
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

#include "DialogRun.h"

DialogRun::DialogRun(wxWindow* parent, Project* project,
		wxCommandProcessor* commandProcessor, DisplaySettings* settings) :
		GUIRun(parent)
{
	this->project = project;
	this->commandProcessor = commandProcessor;
	this->settings = settings;
}

DialogRun::~DialogRun()
{
}

bool DialogRun::TransferDataToWindow(void)
{
	size_t i;
	for(i = 0; i < project->run.GetCount(); i++){
		if(i >= m_choiceRun->GetCount()){
			m_choiceRun->Append(project->run[i].name);
		}else{
			m_choiceRun->SetString(i, project->run[i].name);
		}
	}
	for(i = m_choiceRun->GetCount(); i > project->run.GetCount(); i--)
		m_choiceRun->Delete(i - 1);

	for(i = 0; i < project->workpieces.GetCount(); i++){
		if(i >= m_choiceWorkpiece->GetCount()){
			m_choiceWorkpiece->Append(project->workpieces[i].name);
		}else{
			m_choiceWorkpiece->SetString(i, project->workpieces[i].name);
		}
	}
	for(i = m_choiceWorkpiece->GetCount(); i > project->workpieces.GetCount();
			i--)
		m_choiceWorkpiece->Delete(i - 1);

	return true;
}

bool DialogRun::TransferDataFromWindow(void)
{
	return false;
}

void DialogRun::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogRun::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}
