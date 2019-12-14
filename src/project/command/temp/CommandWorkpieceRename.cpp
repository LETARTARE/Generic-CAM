///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceRename.cpp
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

#include "CommandWorkpieceRename.h"

CommandWorkpieceRename::CommandWorkpieceRename(const wxString& name,
		Project* project, int workpieceNr, const wxString newName) :
		wxCommand(true, name)
{
	this->project = project;
	this->workpieceNr = workpieceNr;
	this->newName = newName;
}

bool CommandWorkpieceRename::Do(void)
{
	this->oldName = project->workpieces[workpieceNr].name;
	project->workpieces[workpieceNr].name = this->newName;
	project->Update();
	return true;
}

bool CommandWorkpieceRename::Undo(void)
{
	project->workpieces[workpieceNr].name = this->oldName;
	project->Update();
	return true;
}
