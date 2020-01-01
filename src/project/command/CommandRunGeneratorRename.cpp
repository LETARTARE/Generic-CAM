///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunGeneratorRename.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 23.12.2019
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

#include "CommandRunGeneratorRename.h"

#include "../Project.h"

CommandRunGeneratorRename::CommandRunGeneratorRename(const wxString& name,
		Project* project, size_t runID, size_t generatorID,
		const wxString newName) :
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
	this->generatorID = generatorID;
	this->newName = newName;
}

bool CommandRunGeneratorRename::Do(void)
{
	if(project == NULL) return false;
	if(project->run.find(runID) == project->run.end()) return false;
	this->oldName = project->run[runID].generators[generatorID]->name;
	project->run[runID].generators[generatorID]->name = this->newName;
	project->Update();
	return true;
}

bool CommandRunGeneratorRename::Undo(void)
{
	project->run[runID].generators[generatorID]->name = this->oldName;
	project->Update();
	return true;
}
