///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceAssignObject.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.01.2015
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

#ifndef COMMANDWORKPIECEASSIGNOBJECT_H_
#define COMMANDWORKPIECEASSIGNOBJECT_H_

#include "../Project.h"

#include <wx/cmdproc.h>

class CommandWorkpieceObjectAssign:public wxCommand {
public:
	CommandWorkpieceObjectAssign(const wxString& name, Project * project,
			 int workpieceNr,int objectNr);

	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	int workpieceNr;
	int objectNr;
};

#endif /* COMMANDWORKPIECEASSIGNOBJECT_H_ */
