///////////////////////////////////////////////////////////////////////////////
// Name               : CommandObjectSetColor.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.06.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CommandObjectSetColor.h"

CommandObjectSetColor::CommandObjectSetColor(const wxString& name,
		Project* project, size_t objectNr, Vector3 color) :
		wxCommand(true, name)
{
	this->project = project;
	this->objectNr = objectNr;
	this->newColor = color;
}

//TODO: Add checks
bool CommandObjectSetColor::Do(void)
{
	this->oldColor = project->objects[objectNr].geometries[0].color;
	project->objects[objectNr].geometries[0].color = this->newColor;
	return true;
}

bool CommandObjectSetColor::Undo(void)
{
	project->objects[objectNr].geometries[0].color = this->oldColor;
	return true;
}
