///////////////////////////////////////////////////////////////////////////////
// Name               : MathParser.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.10.2015
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

#ifndef MATHPARSER_H_
#define MATHPARSER_H_

#include <wx/string.h>

/*!\class MathParser
 * \brief Simple single-line math parser
 *
 * Parses a single line into an double number.
 *
 * Supported functions:
 *  - + - * / ^ ( )
 *  - cos sin tan acos asin atan
 *  - exp log
 *  - sqrt cbrt
 *  - ceil floor round
 *  - abs
 */

class MathParser {
public:
	MathParser();

	// Member functions
public:
	void SetString(const wxString& expression);
	wxString GetString(void) const;
	wxString GetString(const double& number);

	void SetNumber(const double& number);
	double GetNumber(void) const;
	double GetNumber(const wxString& expression);

	void SetUnit(const wxString& unit);
	wxString GetUnit(void) const;
	inline bool HasUnit(void) const
	{
		return unit.IsEmpty();
	}

	inline bool HasError(void) const
	{
		return error.IsEmpty();
	}
	wxString GetError(void) const;

	bool Evaluate(void);

private:
	bool GetNextToken(void);

	// Member variables
public:
	bool autoEvaluate; ///< Evaluate string whenever a new one is passed?
	bool addUnit; ///< Add unit to generated string?

private:
	wxString text;
	double number;
	wxString unit;
	wxString error;

	// Variables for parser:
	unsigned int strLength;

	enum expressionType {
		expressionNone,
		expressionText,
		expressionNumber,
		expressionOperation,
		expressionBracketOpen,
		expressionBracketClose,
		expressionEnd
	};

	static const unsigned int maxStackDepth = 64;
	unsigned int stackStartPos[maxStackDepth];
	unsigned int stackCharCount[maxStackDepth];
	expressionType stackType[maxStackDepth];
	double stackNumber[maxStackDepth];

	unsigned int posStack;
	unsigned int posText;
};

#endif /* MATHPARSER_H_ */
