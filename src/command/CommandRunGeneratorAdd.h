///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunGeneratorAdd.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.02.2015
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

#ifndef COMMANDRUNADDGENERATOR_H_
#define COMMANDRUNADDGENERATOR_H_

#include <wx/cmdproc.h>
#include <wx/string.h>
#include "../generator/Generator.h"
#include "../project/Project.h"

/*!\class CommandRunGeneratorAdd
 * \brief Command to add a toolpath / generator to a project
 */

class CommandRunGeneratorAdd:public wxCommand {
public:
	CommandRunGeneratorAdd(const wxString& name, Project * project, size_t runNr,
			size_t position, Generator* generator);
	virtual ~CommandRunGeneratorAdd(void);

	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	int runNr;
	size_t position;
	Generator * newGenerator;
};

#endif /* COMMANDRUNADDGENERATOR_H_ */
