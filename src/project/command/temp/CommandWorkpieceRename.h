///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceRename.h
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

#ifndef COMMANDWORKPIECERENAME_H_
#define COMMANDWORKPIECERENAME_H_

#include "../Project.h"

#include <wx/cmdproc.h>
#include <wx/string.h>

class CommandWorkpieceRename:public wxCommand {
public:
	CommandWorkpieceRename(const wxString& name, Project * project,
			int workpieceNr, const wxString newName);

	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	int workpieceNr;
	wxString newName;
	wxString oldName;
};

#endif /* COMMANDWORKPIECERENAME_H_ */
