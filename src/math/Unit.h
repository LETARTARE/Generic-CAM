///////////////////////////////////////////////////////////////////////////////
// Name               : Unit.h
// Purpose            : Stores a physical unit
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.06.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef _UNIT_H_
#define _UNIT_H_

/*!\class Unit
 * \brief Stores a physical unit
 *
 * This class stores an unit and the conversion from SI to that unit and back.
 *
 * The factor is the multiplier to convert into the other unit.
 * E.g.:
 *  -  1 cm = 0.01 m        --> factor = 1/100
 *  -  1 rpm = 1/60 1/s     --> factor = 1/60
 *  -  1 mm = 1e-6 m        --> factor = 1e-6
 *  -  1 g  = 1e-3 kg       --> factor = 1e-3
 *  -  1 deg = M_PI/180 rad --> factor = M_PI/180
 *
 *
 *  Name: | Power:
 *  ------|--------
 *    y   | -24
 *    z   | -21
 *    a   | -18
 *    f   | -15
 *    p   | -12
 *    n   | -9
 *    µ   | -6
 *    u   | -6
 *    m   | -3
 *    c   | -2
 *    d   | -1
 *    da  | 1
 *    h   | 2
 *    k   | 3
 *    M   | 6
 *    G   | 9
 *    T   | 12
 *    P   | 15
 *    E   | 18
 *    Z   | 21
 *    Y   | 24
 *
 * The available types for the units are maintained in CollectionUnits.
 *
 * The used types are set in DialogSetupUnits.
 */

#include "../Config.h"

#ifdef _USE_MATHPARSER
#include "MathParser.h"
#endif

#include <string>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <wx/string.h> //TODO: Remove usage of wx/string.h

class Unit {
public:
	/*!\enum unit
	 * \brief Predefined types of units (SI and otherwise)
	 */
	enum unit {
		Unitless = 0, Second, Volume, Celsius
	};

private:
	wxString SIName; ///< The name in SI: m, m/s, 1/s, ...
	wxString otherName; ///< The name in the "other" system: h, cm, dm, rpm, inch, mil, mm, ...

	double factor; ///< 1 in SI = factor in non SI units
	int power; ///< Power for the units (normally a multiple of 3)

	int m; ///< Power of Length
	int kg; ///< Power of Mass
	int s; ///< Power of Time
	int A; ///< Power of Current
	int K; ///< Power of Temperature (absolut)
	int mol; ///< Power of Molar Mass
	int cd; ///< Power of Brightness
	int cur; ///< Power of Currency

#ifdef _USE_MATHPARSER
	MathParser parser;
#endif

public:
	Unit();
	Unit(int m, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0,
			int cd = 0, int cur = 0);
	Unit(wxString otherName);
	Unit(const wxString SIName, const wxString otherName, const double factor);
	Unit(unit predefinedUnit, wxString extra = _T("*"));

public:
	/*! \brief Setup a unit
	 *
	 *	The factor is set so that 1 otherName = factor SIName
	 *	e.g.
	 *
	 *	 - 1 mm = 1e-6 m  --> factor = 1e-6
	 *	 - 1 g  = 1e-3 kg --> factor = 1e-3
	 *	 - 1 deg = M_PI/180 rad --> factor = M_PI/180
	 */
	void Setup(const wxString SIName, const wxString otherName,
			const double factor);
	void SetUnit(unit predefinedUnit, wxString extra = _T("*"));
	void SetCurrency(wxString currency);

	wxString GetOtherName(void);
	wxString GetSIName(void);

	double FromSI(const double value);
	double ToSI(const double value);

	wxString TextFromSI(const double value, int digitsAfterComma = -1);
	wxString TextFromSIWithUnit(const double value, int digitsAfterComma = -1);

	double SIFromString(const wxString &text, bool useEvaluator = true);
	friend inline bool operator==(const Unit &lhs, const Unit &rhs)
	{
		return (lhs.m == rhs.m && lhs.s == rhs.s && lhs.kg == rhs.kg
				&& lhs.A == rhs.A && lhs.K == rhs.K && lhs.mol == rhs.mol
				&& lhs.cd == rhs.cd && lhs.cur == rhs.cur
				&& lhs.power == rhs.power
				&& fabs(lhs.factor - rhs.factor) < 1e-9);
	}
	friend inline bool operator!=(const Unit &lhs, const Unit &rhs)
	{
		return !(lhs == rhs);
	}


	//TODO: Check if the functions below belong into the Measurement class.

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


};

#endif /* _UNIT_H_ */
