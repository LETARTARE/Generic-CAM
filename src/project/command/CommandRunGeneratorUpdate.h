///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunGeneratorUpdate.h
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

#ifndef COMMANDRUNGENERATORUPDATE_H_
#define COMMANDRUNGENERATORUPDATE_H_

/*!\class CommandRunGeneratorUpdate
 * \brief Update the settings of a toolpath generator
 *
 * The toolpath is cleared in this operation. It has to be calculated again afterwards.
 *
 * This command takes over the pointer passed to it. It also cares for the deletion of the
 * generator object at the destruction of this command object or at the end of the
 * program.
 */

#include "../Project.h"
#include "../generator/Generator.h"

#include <wx/cmdproc.h>
#include <wx/string.h>

class CommandRunGeneratorUpdate:public wxCommand {
public:
	CommandRunGeneratorUpdate(const wxString& name, Project* project,
			size_t runID, size_t generatorID, Generator* generator);
	virtual ~CommandRunGeneratorUpdate(void);

	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	int runID;
	size_t generatorID;

	Generator * newGenerator;
	Generator * oldGenerator;

};

#endif /* COMMANDRUNGENERATORUPDATE_H_ */
