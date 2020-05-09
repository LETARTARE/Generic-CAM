///////////////////////////////////////////////////////////////////////////////
// Name               : CommandObjectRename.cpp
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

#include "CommandObjectRename.h"

#include "../Project.h"
#include <algorithm>

CommandObjectRename::CommandObjectRename(const wxString& name, Project* project,
		size_t ID, const wxString objectName) :
		wxCommand(true, name)
{
	this->project = project;
	this->ID = ID;
	this->newName = objectName;
}

bool CommandObjectRename::Do(void)
{
	if(project == NULL) return false;
	std::list <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), ID);
	if(it == project->objects.end()) return false;
	this->oldName = it->name;
	it->name = this->newName;
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandObjectRename::Undo(void)
{
	std::list <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), ID);
	if(it == project->objects.end()) return false;
	it->name = this->oldName;
	project->Modify(true);
	project->Update();
	return true;
}
