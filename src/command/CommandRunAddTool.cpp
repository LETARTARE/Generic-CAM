///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunAddTool.cpp
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

#include "CommandRunAddTool.h"

CommandRunAddTool::CommandRunAddTool(const wxString& name, Project* project,
		int runNr, int newToolNr, int slotNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->newTool = new Tool(project->toolbox.tools[newToolNr]);
	this->newTool->slot = slotNr;
	this->oldTool = NULL;
	this->position = 0;
}

CommandRunAddTool::~CommandRunAddTool(void)
{
	if(oldTool != NULL) delete oldTool;
	if(newTool != NULL) delete newTool;
}

bool CommandRunAddTool::Do(void)
{
	size_t N = project->run[runNr].toolbox.tools.GetCount();
	size_t n;
	for(n = 0; n < N; n++){
		if(project->run[runNr].toolbox.tools[n].slot >= newTool->slot) break;
	}
	if(N > 0 && n < N){
		if(project->run[runNr].toolbox.tools[n].slot == newTool->slot){
			oldTool = project->run[runNr].toolbox.tools.Detach(n);
			if(n + 1 == N){
				project->run[runNr].toolbox.tools.Add(newTool);
			}else{
				project->run[runNr].toolbox.tools.Insert(newTool, n);
			}
		}else{
			project->run[runNr].toolbox.tools.Insert(newTool, n);
			oldTool = NULL;
		}
	}else{
		project->run[runNr].toolbox.tools.Add(newTool);
		oldTool = NULL;
	}
	position = n;
	newTool = NULL;
	return true;
}

bool CommandRunAddTool::Undo(void)
{
	newTool = project->run[runNr].toolbox.tools.Detach(position);
	size_t N = project->run[runNr].toolbox.tools.GetCount();
	if(oldTool != NULL){
		if(position == N){
			project->run[runNr].toolbox.tools.Add(oldTool);
		}else{
			project->run[runNr].toolbox.tools.Insert(oldTool, position);
		}
		oldTool = NULL;
	}
	return true;
}
