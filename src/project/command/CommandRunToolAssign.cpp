///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunToolAssign.cpp
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

#include "CommandRunToolAssign.h"

CommandRunToolAssign::CommandRunToolAssign(const wxString& name,
		Project* project, int runNr, Tool* newTool, int slotNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->slotNr = slotNr;
	this->newTool = newTool;
	this->oldTool = NULL;
}

CommandRunToolAssign::~CommandRunToolAssign(void)
{
	if(oldTool != NULL) delete oldTool;
	if(newTool != NULL) delete newTool;
}

bool CommandRunToolAssign::Do(void)
{
	Run* run = &(project->run[runNr]);
	size_t maxTools = run->tools.GetCount();
	if(slotNr >= maxTools){
		for(size_t n=0;n<(slotNr-maxTools);n++)
			run->tools.Add(Tool());
		run->tools.Add(newTool);
	}else{
		oldTool = run->tools.Detach(slotNr);
		if(slotNr + 1 == maxTools){
			run->tools.Add(newTool);
		}else{
			run->tools.Insert(newTool, slotNr);
		}
	}
	newTool = NULL;
	return true;
}

bool CommandRunToolAssign::Undo(void)
{
	Run* run = &(project->run[runNr]);
	size_t maxTools = run->tools.GetCount();
	newTool = run->tools.Detach(slotNr);
	if(oldTool != NULL){
		if(slotNr == maxTools){
			run->tools.Add(oldTool);
		}else{
			run->tools.Insert(oldTool, slotNr);
		}
		oldTool = NULL;
	}
	return true;
}
