///////////////////////////////////////////////////////////////////////////////
// Name               : Unit.h
// Purpose            : Converts from SI to other measures
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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

#ifndef UNIT_H_
#define UNIT_H_

#include <wx/string.h>
#include "MathParser.h"

/*!\class Unit
 * \brief Converts from SI to whatever and back
 *
 * Simple conversion class.
 * The factor is the multiplier to convert into the other unit.
 * E.g.:
 *    1 cm = 0.01 m, factor = 1/100
 *    1 rpm = 1/60 1/s, factor = 1/60
 *
 * HINT: The available types for the units are maintained in the DialogSetupUnits.
 */

class Unit {
	//Constructor / Destructor
public:
	Unit();
	Unit(const wxString SIName, const wxString otherName, const double factor);

	//Member variables
public:

private:
	double factor; ///> 1 in SI = factor in whatever
	wxString SIName; ///> The name in SI: m, m/s, 1/s, ...
	wxString otherName; ///> The name in the "other" system: h, cm, dm, rpm, inch, mil, mm, ...

	MathParser parser;

	// Methods
public:
	void Setup(const wxString SIName, const wxString otherName,
			const double factor);
	double FromSI(const double value);
	double ToSI(const double value);
	wxString TextFromSI(const double value, unsigned int digitsAfterComma = 3);
	wxString TextFromSIWithUnit(const double value,
			unsigned int digitsAfterComma = 3);
	double SIFromString(const wxString &text);

	wxString GetSIName(void);
	wxString GetOtherName(void);
};

#endif /* UNIT_H_ */
