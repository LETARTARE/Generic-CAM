///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunRemoveTool.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.01.2015
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

#include "CommandRunRemoveTool.h"

CommandRunRemoveTool::CommandRunRemoveTool(const wxString& name,
		Project* project, int runNr, int slotNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->slotNr = slotNr;
	this->oldTool = NULL;
	this->position = 0;
}

CommandRunRemoveTool::~CommandRunRemoveTool(void)
{
	if(oldTool != NULL) delete oldTool;
}

bool CommandRunRemoveTool::Do(void)
{
	size_t N = project->run[runNr].toolbox.tools.GetCount();
	for(position = 0; position < N; position++){
		if(project->run[runNr].toolbox.tools[position].slot == this->slotNr) break;
	}
	if(position == N) return false;
	oldTool = project->run[runNr].toolbox.tools.Detach(position);
	return true;
}

bool CommandRunRemoveTool::Undo(void)
{
	if(position >= project->run[runNr].toolbox.tools.GetCount()){
		project->run[runNr].toolbox.tools.Add(oldTool);
	}else{
		project->run[runNr].toolbox.tools.Insert(oldTool, runNr);
	}
	// If the the tool was inserted back into the project,
	// this function must not delete the tool in the destructor.
	oldTool = NULL;
	return true;
}
