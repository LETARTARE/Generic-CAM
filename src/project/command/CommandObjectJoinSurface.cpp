///////////////////////////////////////////////////////////////////////////////
// Name               : CommandObjectJoinSurface.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.05.2020
// Copyright          : (C) 2020 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CommandObjectJoinSurface.h"

#include <algorithm>

CommandObjectJoinSurface::CommandObjectJoinSurface(const wxString& name,
		Project* project, size_t object_ID) :
		wxCommand(true, name), oldObject(object_ID)
{
	this->project = project;
	this->object_ID = object_ID;
}

bool CommandObjectJoinSurface::Do(void)
{
	if(project == NULL) return false;
	std::list <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), object_ID);
	if(it == project->objects.end()) return false;

	oldObject = *it;
	it->JoinSurface();
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandObjectJoinSurface::Undo(void)
{
	if(project == NULL) return false;
	std::list <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), object_ID);
	if(it == project->objects.end()) return false;
	*it = oldObject;
	project->Modify(true);
	project->Update();
	return true;
}
