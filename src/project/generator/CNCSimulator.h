///////////////////////////////////////////////////////////////////////////////
// Name               : CNCSimulator.h
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
#ifndef CNCSIMULATOR_H_
#define CNCSIMULATOR_H_

/*!\class CNCSimulator
 * \ingroup Machine
 * \brief Simlator of the movement and operation of the machine.
 *
 * Small class coordinating the advancements of the Machine during the
 * simulation cycle. It also coordinates the setup and processing of the
 * Workpieces in the machine.
 *
 */

#include <stddef.h>
#include <vector>

#include "../../3D/AffineTransformMatrix.h"
#include "../Tool.h"
#include "CNCPosition.h"
#include "DexelTarget.h"

class CNCSimulator {
	// Constructor/ Destructor
public:
	CNCSimulator();
	virtual ~CNCSimulator();

	void SetTools(const std::vector <Tool> *tools);

	void InsertTarget(DexelTarget* target); //!< Inserts a target into the simulator. This target remains unchanged.
	const DexelTarget* GetTarget(void) const; //!< Returns the modified internal target.

	void InsertToolPath(std::vector <CNCPosition> * toolpath,
			bool calculateTiming = true);

	double GetTime(void) const;
	double GetMaxTime(void) const;

	void Reset(void);
	void Previous(void);
	void Step(float tTarget);
	void Next(void);
	void Last(void);

	void Paint(void) const;

	//Member variables
	AffineTransformMatrix origin;
	AffineTransformMatrix stockposition;
private:
	const std::vector <Tool> * tools;
	std::vector <CNCPosition> * toolpath; //!< Toolpath to apply to target.

	DexelTarget* basetarget; //!< Provided target to initialize the internal copy from.
	DexelTarget target; //!< Internal target to work on.

	bool initialized;

	float tStep;
	size_t step;
};

#endif /* CNCSIMULATOR_H_ */
