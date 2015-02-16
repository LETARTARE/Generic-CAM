///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunGeneratorDelete.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.02.2015
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

#include "CommandRunGeneratorDelete.h"

CommandRunGeneratorDelete::CommandRunGeneratorDelete(const wxString& name,
		Project* project, size_t runNr, size_t position) :
		wxCommand(true, name)
{
	this->project = project;
	this->runNr = runNr;
	this->position = position;
	this->oldGenerator = NULL;
}

CommandRunGeneratorDelete::~CommandRunGeneratorDelete(void)
{
	if(oldGenerator != NULL) delete oldGenerator;
}

bool CommandRunGeneratorDelete::Do(void)
{
	ToolPath * temp = project->run[runNr].toolpaths.Detach(position);
	oldGenerator = temp->generator;
	temp->generator = NULL;
	delete temp;
	return true;
}

bool CommandRunGeneratorDelete::Undo(void)
{
	ToolPath * temp = new ToolPath;
	temp->generator = oldGenerator;

	size_t N = project->run[runNr].toolpaths.GetCount();

	if(position >= N)
		project->run[runNr].toolpaths.Add(temp);
	else
		project->run[runNr].toolpaths.Insert(temp, position);
	oldGenerator = NULL;
	return true;
}
