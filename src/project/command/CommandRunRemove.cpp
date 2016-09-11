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

CommandRunRemove::CommandRunRemove(const wxString& name, Project* project,
		int runNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->run = NULL;
}

CommandRunRemove::~CommandRunRemove()
{
	if(run != NULL) delete run;
}

bool CommandRunRemove::Do(void)
{
	run = project->run.Detach(runNr);
	return true;
}

bool CommandRunRemove::Undo(void)
{
	if(runNr >= project->run.GetCount()){
		project->run.Add(run);
	}else{
		project->run.Insert(run, runNr);
	}
	// If the the workpiece was inserted back into the project,
	// this function must not delete the workpiece in the destructor.
	run = NULL;
	return true;
}
