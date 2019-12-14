///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunSetObject.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.12.2019
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

#include "CommandRunSetObject.h"

#include "../Project.h"

CommandRunSetObject::CommandRunSetObject(const wxString& name, Project* project,
		size_t runID, const Selection & selection) :
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
	this->newSelection = selection;
}

bool CommandRunSetObject::Do(void)
{
	if(project == NULL) return false;
	if(project->run.find(runID) == project->run.end()) return false;

	this->oldSelection = project->run[runID].object;

	project->run[runID].object = this->newSelection;
	project->Update();
	return true;
}

bool CommandRunSetObject::Undo(void)
{
	if(project == NULL) return false;
	if(project->run.find(runID) == project->run.end()) return false;
	project->run[runID].object = this->oldSelection;
	project->Update();
	return true;
}
