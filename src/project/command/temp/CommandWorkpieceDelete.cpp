///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceDelete.cpp
// Purpose            : Delete a workpiece
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

#include "CommandWorkpieceDelete.h"

CommandWorkpieceDelete::CommandWorkpieceDelete(const wxString& name,
		Project* project, int workpieceNr) :
		wxCommand(true, name)
{
	this->project = project;
	this->workpieceNr = workpieceNr;
	this->workpiece = NULL;
}

CommandWorkpieceDelete::~CommandWorkpieceDelete()
{
	if(workpiece != NULL) delete workpiece;
}

bool CommandWorkpieceDelete::Do(void)
{
	workpiece = project->workpieces.Detach(workpieceNr);
	project->Update();
	return true;
}

bool CommandWorkpieceDelete::Undo(void)
{
	if(workpieceNr >= project->workpieces.GetCount()){
		project->workpieces.Add(workpiece);
	}else{
		project->workpieces.Insert(workpiece, workpieceNr);
	}
	// If the the workpiece was inserted back into the project,
	// this function must not delete the workpiece in the destructor.
	workpiece = NULL;
	project->Update();
	return true;
}
