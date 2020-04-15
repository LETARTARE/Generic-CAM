///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunRemove.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.01.2015
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

#include "CommandRunRemove.h"

#include "../Project.h"
#include <algorithm>

CommandRunRemove::CommandRunRemove(const wxString& name, Project* project,
		size_t runID) :
		wxCommand(true, name), run(runID)
{
	this->project = project;
	this->runID = runID;
	this->position = 0;
}

CommandRunRemove::~CommandRunRemove()
{
}

bool CommandRunRemove::Do(void)
{
	if(project == NULL) return false;
	std::vector <Run>::iterator itRun;
	itRun = std::find(project->run.begin(), project->run.end(), runID);
	if(itRun == project->run.end()) return false;
	position = itRun - project->run.begin();
	this->run = *itRun;
	project->run.erase(itRun);
	project->Update();
	return true;
}

bool CommandRunRemove::Undo(void)
{
	if(project == NULL) return false;
	std::vector <Run>::iterator itRun;
	itRun = project->run.begin() + position;
	project->run.insert(itRun, run);
	project->Update();
	return true;
}
