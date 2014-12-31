///////////////////////////////////////////////////////////////////////////////
// Name               : commandObjectLoad.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.12.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "commandObjectLoad.h"

commandObjectLoad::commandObjectLoad(const wxString& name, Project * project,
		const wxString& fileName) :
		wxCommand(true, name)
{
	this->project = project;
	this->fileName = fileName;
}

bool commandObjectLoad::Do(void)
{
	Object temp;
	if(temp.LoadObject(fileName)){
		temp.matrix.ScaleGlobal(0.01, 0.01, 0.01);
		project->objects.Add(temp);
		return true;
	}
	return false;
}

bool commandObjectLoad::Undo(void)
{
	project->objects.RemoveAt(project->objects.GetCount() - 1, 1);
	return true;
}
