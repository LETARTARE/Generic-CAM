///////////////////////////////////////////////////////////////////////////////
// Name               : commandRunLoadMachine.cpp
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

#include "CommandRunMachineLoad.h"

CommandRunMachineLoad::CommandRunMachineLoad(const wxString& name,
		Project* project, int runNr, const wxString& fileName) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->fileName = fileName;
}

bool CommandRunMachineLoad::Do(void)
{
	bool flag = project->run[runNr].machine.Load(wxFileName(fileName));
	project->Update();
	return flag;
}

bool CommandRunMachineLoad::Undo(void)
{
	//TODO: Implement Machine::Clear();
	project->run[runNr].machine.ClearComponents();
	project->Update();
	return true;
}
