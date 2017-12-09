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
///////////////////////////////////////////////////////////////////////////////
#ifndef MACHINESIMULATOR_H_
#define MACHINESIMULATOR_H_

/*!\class MachineSimulator
 * \ingroup Machine
 * \brief Simlator of the movement and operation of the machine.
 *
 * Small class coordinating the advancements of the Machine during the
 * simulation cycle. It also coordinates the setup and processing of the
 * Workpieces in the machine.
 *
 * \todo Remove the quick simulator from the Machine. Everything should be simulated with the same code.
 */

#include "Machine.h"

#include "../ToolBox.h"
#include "../ToolPath.h"
#include "../Workpiece.h"
#include "../generator/DexelTarget.h"

#include <wx/filename.h>
#include <vector>
#include "CNCPosition.h"

class MachineSimulator {
	// Constructor/ Destructor
public:
	MachineSimulator();
	virtual ~MachineSimulator();

	void InsertMachine(Machine* machine);
	void InsertWorkpiece(Workpiece* workpiece);
	void InsertTarget(DexelTarget* target);
	void InsertToolPath(ToolPath* toolpath);

	void InitSimulation(size_t maxCells);

	void Reset(bool calculateTiming = true);
	void Previous(void);
	void Step(float tTarget);
	void Next(void);
	void Last(void);

	void Paint(void) const;

	//Member variables
public:
	Machine* machine; //!< Linked Machine to move around.

	Workpiece* workpiece; //!< Workpiece to start from. Alternative to basetarget.
	DexelTarget* basetarget; //!< Target to start from. Alternative to workpiece. Stays unchanged.

	DexelTarget target; //!< Target that is modified. Copied from basetarget or generated from workpiece.

	ToolPath* toolpath; //!< Toolpath to apply to target.

	bool initialized;

	float tStep;
	size_t step;

};

#endif /* MACHINESIMULATOR_H_ */
