///////////////////////////////////////////////////////////////////////////////
// Name               : commandObjectDelete.cpp
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

#include "commandObjectDelete.h"

#include <stddef.h>

commandObjectDelete::commandObjectDelete(const wxString& name, Project* project,
		int objectNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->objectNr = objectNr;
	this->object = NULL;
}

bool commandObjectDelete::Do(void)
{
	object = project->objects.Detach(objectNr);
	return true;
}

commandObjectDelete::~commandObjectDelete()
{
	if(object != NULL) delete object;
}

bool commandObjectDelete::Undo(void)
{
	if(objectNr >= project->objects.GetCount()){
		project->objects.Add(object);
	}else{
		project->objects.Insert(object, objectNr);
	}
	// If the the object was inserted back into the project,
	// this function must not delete the object in the destructor.
	object = NULL;
	return true;
}
