///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunAdd.cpp
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

#include "CommandRunAdd.h"

#include "../Run.h"

CommandRunAdd::CommandRunAdd(const wxString& name, Project* project,
		wxString runName) :
		wxCommand(true, name)
{
	this->project = project;
	this->runName = runName;
}

bool CommandRunAdd::Do(void)
{
	Run* temp = new Run();
	temp->name = runName;
	project->run.Add(temp);
	project->Update();
	return true;
}

bool CommandRunAdd::Undo(void)
{
	project->run.RemoveAt(project->run.GetCount() - 1);
	project->Update();
	return true;
}
