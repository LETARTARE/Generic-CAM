///////////////////////////////////////////////////////////////////////////////
// Name               : CommandObjectRemove.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.01.2015
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

#include "CommandObjectRemove.h"

#include "../Project.h"
#include <algorithm>
#include <stddef.h>

CommandObjectRemove::CommandObjectRemove(const wxString& name, Project* project,
		size_t ID) :
		wxCommand(true, name), object(ID)
{
	this->project = project;
	this->ID = ID;
	position = 0;
}

CommandObjectRemove::~CommandObjectRemove()
{
}

bool CommandObjectRemove::Do(void)
{
	if(project == NULL) return false;
	std::vector <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), ID);
	if(it == project->objects.end()) return false;
	position = it - project->objects.begin();
	this->object = *it;
	project->objects.erase(it);
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandObjectRemove::Undo(void)
{
	if(project == NULL) return false;
	std::vector <Object>::iterator it;
	it = project->objects.begin() + position;
	project->objects.insert(it, this->object);
	project->Modify(true);
	project->Update();
	return true;
}
