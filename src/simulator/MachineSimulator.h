///////////////////////////////////////////////////////////////////////////////
// Name               : MachineSimulator.h
// Purpose            : A simulator for the machine operation.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#ifndef MACHINESIMULATOR_H_
#define MACHINESIMULATOR_H_
#include "../project/Toolbox.h"
#include "ToolPath.h"
#include "../machine/Machine.h"
#include "../machine/MachinePosition.h"
#include <wx/filename.h>

class MachineSimulator {
	// Constructor/ Destructor
public:
	MachineSimulator();
	virtual ~MachineSimulator();

	//Member variables
public:

	Machine machine;
	ArrayOfMachinePosition position;

	ToolPath toolpath;
	Toolbox toolbox;

	float tStep;
	unsigned long step;

	//Methods
public:
	void InsertMachine(Machine* machine);
	void Reset(void);
	void Step(float tTarget);

	bool ReadGCodeFile(wxFileName fileName);
};

#endif /* MACHINESIMULATOR_H_ */
