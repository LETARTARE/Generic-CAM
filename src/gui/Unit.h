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

/*!\class Unit
 * \brief Converts from SI to whatever and back
 *
 * Simple conversion class.
 * The factor is the multiplier to convert into the other unit.
 * E.g.:
 *    1 cm = 0.01 m, factor = 1/100
 *    1 rpm = 1/60 1/s, factor = 1/60
 *
 *
 *    Powers:
 *    'y',-24
 *    'z',-21
 *    'a',-18
 *    'f',-15
 *    'p',-12
 *    'n',-9
 *    'µ',-6
 *    'u',-6
 *    'm',-3
 *    'c',-2
 *    'd',-1
 *    'da',1
 *    'h',2
 *    'k',3
 *    'M',6
 *    'G',9
 *    'T',12
 *    'P',15
 *    'E',18
 *    'Z',21
 *    'Y',24
 *
 *
 *
 *
 * HINT: The available types for the units are maintained in the DialogSetupUnits.
 */

#include "MathParser.h"
#include <wx/string.h>

class Unit {
	// Enumerations
public:
	/*!\enum unit
	 * \brief Predefined types of units (SI and otherwise)
	 */
	enum unit {
		Unitless = 0, Second, Volume, Celsius
	};

	//Constructor / Destructor
public:
	Unit();
	Unit(int m, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0,
			int cd = 0, int cur = 0);
	Unit(wxString otherName);
	Unit(const wxString SIName, const wxString otherName, const double factor);
	Unit(unit predefinedUnit, wxString extra = _T("*"));

	// Methods
public:
	void Setup(const wxString SIName, const wxString otherName,
			const double factor);
	void SetUnit(unit predefinedUnit, wxString extra = _T("*"));
	void SetCurrency(wxString currency);

	wxString GetOtherName(void);
	wxString GetSIName(void);

	double FromSI(const double value);
	double ToSI(const double value);

	wxString TextFromSI(const double value, int digitsAfterComma = -1);
	wxString TextFromSIWithUnit(const double value,
			 int digitsAfterComma = -1);

	double SIFromString(const wxString &text, bool useEvaluator = true);

	Unit& operator*=(const Unit &other)
	{
		this->m += other.m;
		this->kg += other.kg;
		this->s += other.s;
		this->A += other.A;
		this->K += other.K;
		this->mol += other.mol;
		this->cd += other.cd;
		this->cur += other.cur;
		return *this;
	}
	friend inline Unit operator*(Unit lhs, const Unit &rhs)
	{
		return lhs *= rhs;
	}

	Unit& operator/=(const Unit &other)
	{
		this->m -= other.m;
		this->kg -= other.kg;
		this->s -= other.s;
		this->A -= other.A;
		this->K -= other.K;
		this->mol -= other.mol;
		this->cd -= other.cd;
		this->cur -= other.cur;
		return *this;
	}
	friend inline Unit operator/(Unit lhs, const Unit &rhs)
	{
		return lhs /= rhs;
	}

	friend inline bool operator==(const Unit &lhs, const Unit &rhs)
	{
		return (lhs.m == rhs.m && lhs.s == rhs.s && lhs.kg == rhs.kg
				&& lhs.A == rhs.A && lhs.K == rhs.K && lhs.mol == rhs.mol
				&& lhs.cd == rhs.cd && lhs.cur == rhs.cur);
	}
	friend inline bool operator!=(const Unit &lhs, const Unit &rhs)
	{
		return !(lhs == rhs);
	}

	//Member variables
private:
	double factor; ///< 1 in SI = factor in non SI units
	double power; ///<
	wxString SIName; ///< The name in SI: m, m/s, 1/s, ...
	wxString otherName; ///< The name in the "other" system: h, cm, dm, rpm, inch, mil, mm, ...

	MathParser parser;

	int m; ///< Power of Length
	int kg; ///< Power of Mass
	int s; ///< Power of Time
	int A; ///< Power of Current
	int K; ///< Power of Temperature (absolut)
	int mol; ///< Power of Molar Mass
	int cd; ///< Power of Brightness
	int cur; ///< Power of Currency

};

#endif /* UNIT_H_ */
