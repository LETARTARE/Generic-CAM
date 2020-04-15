///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunAdd.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.12.2019
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

#include "CommandRunAdd.h"

#include "../Project.h"
#include "../Selection.h"
#include <algorithm>

CommandRunAdd::CommandRunAdd(const wxString& name, Project* project,
		const wxString &runName, size_t runID, const std::set <size_t> &objIDs) :
		wxCommand(true, name), runID(runID), run(runID)
{
	this->project = project;
	this->run.name = runName;
	for(std::set <size_t>::const_iterator objID = objIDs.begin();
			objID != objIDs.end(); ++objID)
		this->run.object.Add(Selection::Object, *objID);
}

bool CommandRunAdd::Do(void)
{
	if(project == NULL) return false;
	project->run.push_back(this->run);
	project->Update();
	return true;
}

bool CommandRunAdd::Undo(void)
{
	if(project == NULL) return false;
	std::vector <Run>::iterator it;
	it = std::find(project->run.begin(), project->run.end(), runID);
	if(it == project->run.end()) return false;
	project->run.erase(it);
	project->Update();
	return true;
}
