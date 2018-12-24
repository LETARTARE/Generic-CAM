///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunToolAdd.cpp
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

#include "CommandRunToolAdd.h"

CommandRunToolAdd::CommandRunToolAdd(const wxString& name, Project* project,
		int runNr, Tool newTool, int slotNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->slotNr = slotNr;
	this->newTool = newTool;
	this->newTool.slotNr = slotNr;
	onlyUpdating = false;
}

CommandRunToolAdd::~CommandRunToolAdd(void)
{
}

bool CommandRunToolAdd::Do(void)
{
	if(project == NULL) return false;
	Run* const run = &(project->run[runNr]);
	const size_t maxTools = run->machine.tools.GetCount();
	if(maxTools > 0){
		for(size_t n = 0; n < maxTools; n++){
			if(run->machine.tools[n].slotNr == slotNr){
				onlyUpdating = true;
				oldTool = run->machine.tools[n];
				run->machine.tools[n] = newTool;
				project->Update();
				return true;
			}
		}
	}
	run->machine.tools.Add(newTool);
	run->Update();
	project->Update();
	return true;
}

bool CommandRunToolAdd::Undo(void)
{
	if(project == NULL) return false;
	Run* const run = &(project->run[runNr]);

	const size_t maxTools = run->machine.tools.GetCount();
	if(onlyUpdating){
		for(size_t n = 0; n < maxTools; n++){
			if(run->machine.tools[n].slotNr == slotNr){
				run->machine.tools[n] = oldTool;
				project->Update();
				return true;
			}
		}
		return false;
	}
	run->machine.tools.RemoveAt(run->machine.tools.GetCount() - 1, 1);
	run->Update();
	project->Update();
	return true;
}
