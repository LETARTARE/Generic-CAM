///////////////////////////////////////////////////////////////////////////////
// Name               : TPGeneratorTest.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.07.2011
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#ifndef TPGENERATORTEST_H_
#define TPGENERATORTEST_H_

#include "../project/Target.h"
#include "../3D/Polygon3.h"
#include "../machine/Tool.h"
/*!\class TPGeneratorTest
 * \brief ...
 *
 * ...
 */

class TPGeneratorTest {
	// Constructor/ Destructor
public:
	TPGeneratorTest();
	virtual ~TPGeneratorTest();

	//Member variables:
public:


	// Slot around Object
	double slotWidth;
	double supportDistance;
	double supportWidth;
	double supportHeight;

	// Generic Toolpath parameters
	double freeHeightAboveMaterial;

	// Toolpath generation parameter (extract from tool?)
	double levelDrop;

	//Methods:
public:
	void SetupSlot(double slotWidth, double supportDistance,
			double supportWidth, double supportHeight);

	void GenerateToolpath(Target &target, Object &obj, Tool &tool);

};

#endif /* TPGENERATORTEST_H_ */
