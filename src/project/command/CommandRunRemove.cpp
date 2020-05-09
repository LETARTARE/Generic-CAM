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
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
}

CommandRunRemove::~CommandRunRemove()
{
}

bool CommandRunRemove::Do(void)
{
	if(project == NULL) return false;

	position = std::find(project->run.begin(), project->run.end(), runID);
	if(position == project->run.end()) return false;

	run.splice(run.end(), project->run, position);

	project->Modify(true);
	project->Update();
	return true;
}

bool CommandRunRemove::Undo(void)
{
	if(project == NULL) return false;

	project->run.splice(position, run);

	project->Modify(true);
	project->Update();
	return true;
}
