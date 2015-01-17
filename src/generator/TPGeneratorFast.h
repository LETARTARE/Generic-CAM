///////////////////////////////////////////////////////////////////////////////
// Name               : TPGeneratorFast.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.08.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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


#ifndef TPGENERATORFAST_H_
#define TPGENERATORFAST_H_

#include "DexelTarget.h"
#include "../3D/Polygon3.h"
#include "../machine/Tool.h"

/*!\class TPGeneratorFast
 * \brief ...
 *
 * ...
 */
class TPGeneratorFast {
	// Constructor/ Destructor
public:
	TPGeneratorFast();
	virtual ~TPGeneratorFast();

	//Member variables:
public:

	double freeHeightAboveMaterial;
	double maxSingleStep;
	double raiseStep;

	double dropStep;

private:
	double toolDiameter;

	//Methods:
public:
	void GenerateToolpath(DexelTarget &target, Tool &tool);

private:
	ToolPath GenerateSpiral(double x, double y, double radius);
	ToolPath GenerateDrill(double x, double y, double diameter, double depth);
	bool IsDirectlyReachable(DexelTarget &target, double sx, double sy, double sz,
			double x, double y, double z);
	ToolPath MoveSavely(DexelTarget &target, double sx, double sy, double sz,
			double x, double y, double z);

};

#endif /* TPGENERATORFAST_H_ */
