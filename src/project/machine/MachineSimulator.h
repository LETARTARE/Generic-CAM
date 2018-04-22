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
	void InsertToolPath(ToolPath* toolpath);
	void InsertTarget(DexelTarget* target); //!< Inserts a target into the simulator. This target remains unchanged.
	const DexelTarget* GetTarget(void) const; //!< Returns the modified internal target.

	/*! \brief Return the G-code currently executed by the machine
	 *
	 * The default value pos = 0 returns the G-code that is/was currently executed.
	 *
	 * \param pos Return another G-code block around the current position (0 = current code, -1 = last code, 1 = next code)
	 * \return wxString with the G-code block
	 */
	wxString GetCurrentGCode(int pos = 0) const;
	double GetTime(void) const;
	double GetMaxTime(void) const;

	/*! \brief Return to the first G-code block
	 *
	 * Actually it reads in the first G-code but the machine does not move for the time t is set to 0.
	 *
	 * \param calculateTiming Only calculates the duration of each G-code, without interpolating or cutting. Used to get the timing right.
	 */
	void Reset(bool calculateTiming = true);
	void Previous(void);
	void Step(float tTarget);
	void Next(void);
	void Last(void);

	void Paint(void) const;

	//Member variables
private:
	Machine* machine; //!< Linked Machine to move around.
	ToolPath* toolpath; //!< Toolpath to apply to target.
	DexelTarget* basetarget; //!< Provided target to initialize the internal copy from.
	DexelTarget target; //!< Internal target to work on.

	bool initialized;
	float tStep;
	size_t step;
};

#endif /* MACHINESIMULATOR_H_ */
