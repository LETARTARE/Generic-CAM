///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunGeneratorUpdate.cpp
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

#include "CommandRunGeneratorUpdate.h"

#include "../Project.h"
#include "../generator/Generator.h"
#include <algorithm>

CommandRunGeneratorUpdate::CommandRunGeneratorUpdate(const wxString& name,
		Project* project, size_t runID, size_t generatorID,
		Generator* generator) :
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
	this->generatorID = generatorID;
	this->newGenerator = generator;
	this->oldGenerator = NULL;
}

CommandRunGeneratorUpdate::~CommandRunGeneratorUpdate(void)
{
	if(newGenerator != NULL) delete newGenerator;
	if(oldGenerator != NULL) delete oldGenerator;
}

bool CommandRunGeneratorUpdate::Do(void)
{
	if(project == NULL) return false;
	std::list <Run>::iterator itRun;
	itRun = std::find(project->run.begin(), project->run.end(), runID);
	if(itRun == project->run.end()) return false;
	std::vector <Generator*>::iterator it;
	it = itRun->generators.begin();
	while(it != itRun->generators.end()){
		if((**it) == generatorID) break;
		++it;
	}
	if(it == itRun->generators.end()) return false;
	oldGenerator = *it;
	*it = newGenerator;
	newGenerator = NULL;
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandRunGeneratorUpdate::Undo(void)
{
	if(project == NULL) return false;
	std::list <Run>::iterator itRun;
	itRun = std::find(project->run.begin(), project->run.end(), runID);
	if(itRun == project->run.end()) return false;
	std::vector <Generator*>::iterator it;
	it = itRun->generators.begin();
	while(it != itRun->generators.end()){
		if((**it) == generatorID) break;
		++it;
	}
	if(it == itRun->generators.end()) return false;
	newGenerator = *it;
	*it = oldGenerator;
	oldGenerator = NULL;
	project->Modify(true);
	project->Update();
	return true;
}
