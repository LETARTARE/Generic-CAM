///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunToolRemove.cpp
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

#include "CommandRunToolRemove.h"

CommandRunToolRemove::CommandRunToolRemove(const wxString& name,
		Project* project, int runNr, int slotNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->slotNr = slotNr;
	this->oldTool = NULL;
}

CommandRunToolRemove::~CommandRunToolRemove(void)
{
	if(oldTool != NULL) delete oldTool;
}

bool CommandRunToolRemove::Do(void)
{
	Run* run = &(project->run[runNr]);
	size_t maxTools = run->tools.GetCount();
	if(slotNr >= maxTools) return false;
	oldTool = run->tools.Detach(slotNr);
	if(slotNr + 1 < maxTools){
		run->tools.Insert(Tool(), slotNr);
	}
	return true;
}

bool CommandRunToolRemove::Undo(void)
{
	Run* run = &(project->run[runNr]);
	size_t maxTools = run->tools.GetCount();
	if(slotNr >= maxTools){
		run->tools.Add(oldTool);
	}else{
		run->tools[slotNr] = *oldTool;
		delete oldTool;
	}
	oldTool = NULL;
	return true;
}
