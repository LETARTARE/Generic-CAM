///////////////////////////////////////////////////////////////////////////////
// Name               : MathParser.cpp
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

#include "MathParser.h"

#include <wx/debug.h>
#include <math.h>

MathParser::MathParser(bool autoEvaluate)
{
	wxASSERT(maxStackDepth > 5);

	this->autoEvaluate = autoEvaluate;
	addUnit = false;
	number = 0.0;
	ResetVariables(true);
}

void MathParser::SetString(const wxString& expression)
{
	text = expression;
	if(autoEvaluate) Evaluate();
}

wxString MathParser::GetString(void) const
{
	return text;
}

wxString MathParser::GetString(const double& number)
{
	this->number = number;
	text = wxString::Format(_T("%g"), number);
	return text;
}

void MathParser::SetNumber(const double& number)
{
	this->number = number;
	text = wxString::Format(_T("%g"), this->number);
	if(addUnit && !unit.IsEmpty()) text = text + _T(" ") + unit;
}

double MathParser::GetNumber(void) const
{
	return number;
}

double MathParser::GetNumber(const wxString& expression)
{
	text = expression;
	Evaluate();
	return number;
}

wxString MathParser::GetError(void) const
{
	return error;
}

void MathParser::SetUnit(const wxString& unit)
{
	this->unit = unit;
}

wxString MathParser::GetUnit(void) const
{
	return unit;
}

void MathParser::ResetVariables(bool setStandard)
{
	globals.clear();
	if(setStandard){
		globals[_T("pi")] = M_PI;
		globals[_T("e")] = M_E;
	}
}

void MathParser::SetVariable(const wxString& variable, double value)
{
	globals[variable] = value;
}

double MathParser::GetVariable(const wxString& variable)
{
	double x = globals[variable];
	return x;
}

void MathParser::ResetAllowedUnits(void)
{
	allowedUnits.clear();
}

void MathParser::AddAllowedUnit(const wxString& unit, double factor)
{
	allowedUnits[unit] = factor;
}

bool MathParser::GetNextToken(void)
{
	if(posStack >= maxStackDepth){
		error = _T("Stack full.");
		return false;
	}

	// Remove spaces in front
	while(posText < strLength && text[posText] == ' ')
		posText++;

	// If nothing is left of the string, add expressionEnd and return.
	if(posText >= strLength){
		if(posStack > 0 && stackType[posStack - 1] == expressionEnd) return false;
		stackStartPos[posStack] = 0;
		stackCharCount[posStack] = 0;
		stackType[posStack] = expressionEnd;
		stackNumber[posStack] = 0.0;
		posStack++;
		return true;
	}

	// TODO: Put in counters to keep the numberparser from overflowing. Otherwise it may return wrong numbers.
	expressionType type = expressionNone;
	expressionType newType = expressionNone;
	wxChar c;
	int64_t num = 0;
	int exp = 0;
	int shift = 0;
	bool negativeExponent = false;
	int state = 0;

	stackStartPos[posStack] = posText;

	while(posText < strLength){
		c = text[posText];

		if(c == ' ') newType = expressionEnd;
		if(c == '(') newType = expressionBracketOpen;
		if(c == ')') newType = expressionBracketClose;
		if((c >= '0' && c <= '9') || c == '.' || c == ',') newType =
				expressionNumber;
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
				|| c == '%') newType = expressionText;
		if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') newType =
				expressionOperation;

		if(type == expressionNumber && state < 2 && (c == 'e' || c == 'E')) newType =
				expressionNumber;
		if(type == expressionNumber && state == 2 && (c == '-' || c == '+')) newType =
				expressionNumber;

		if(newType == expressionNone){
			error = _T("Unknown characters in string.");
			return false;
		}

		if(type == expressionNone){
			type = newType;
		}else{
			if(type != newType){
				break;
			}
		}
		if(type == expressionNumber){

			if(state == 1 && (c == '.' || c == ',')){
				error = _T("Multiple '.' or ',' in a number.");
				return false;
			}
			if(state > 1 && (c == '.' || c == ',')){
				error = _T("'.' or ',' inside the exponent of a number.");
				return false;
			}

			switch(state){
			case 0:
				if(c == '.' || c == ',') state = 1;
				if(c == 'e' || c == 'E') state = 2;
				if(c >= '0' && c <= '9'){
					num *= 10;
					num += c - '0';
				}
				break;
			case 1:
				if(c == 'e' || c == 'E') state = 2;
				if(c >= '0' && c <= '9'){
					num *= 10;
					num += c - '0';
					shift--;
				}
				break;
			case 2:
				if(c == '-') negativeExponent = true;
				if(c >= '0' && c <= '9'){
					exp *= 10;
					exp += c - '0';
				}
				state = 3;
				break;
			case 3:
				if(c >= '0' && c <= '9'){
					exp *= 10;
					exp += c - '0';
				}
				break;
			}

		}
		posText++;
		if(type == expressionBracketOpen || type == expressionBracketClose
				|| type == expressionOperation) break;
	}

	if(type != expressionNone){
		stackCharCount[posStack] = posText - stackStartPos[posStack];
		stackType[posStack] = type;
		if(type == expressionNumber){
			if(negativeExponent) exp = -exp;
			stackNumber[posStack] = (double) num
					* pow(10, double(exp) + (double) shift);
		}else{
			stackNumber[posStack] = 0.0;
		}
		posStack++;
	}

	return true;
}

bool MathParser::Evaluate(void)
{
	error.Empty();
	if(text.IsEmpty()){
		error = _T("Expression empty.");
		return false;
	}

	strLength = text.Length();
	posText = 0;
	posStack = 0;
	bool flag;

	while(GetNextToken()){
		flag = true;
		while(flag){
			flag = false;

			// Replace variables
			if(posStack >= 2 && stackType[posStack - 2] == expressionText){
				wxString variable = text.Mid(stackStartPos[posStack - 2],
						stackCharCount[posStack - 2]);
				if(globals.count(variable) == 1){
					stackNumber[posStack - 2] = globals[variable];
					stackType[posStack - 2] = expressionNumber;
					flag = true;
				}
			}

			// Replace units
			if(posStack >= 2 && stackType[posStack - 1] == expressionText
					&& !allowedUnits.empty()){
				wxString temp = text.Mid(stackStartPos[posStack - 1],
						stackCharCount[posStack - 1]);
				if(allowedUnits.count(temp) == 1
						&& stackType[posStack - 2] == expressionNumber){
					stackNumber[posStack - 2] *= allowedUnits[temp];
					posStack--;
					flag = true;
				}
			}

			// Remove Brackets.
			if(posStack >= 4
					&& stackType[posStack - 2] == expressionBracketClose
					&& stackType[posStack - 3] == expressionNumber
					&& stackType[posStack - 4] == expressionBracketOpen){
				stackType[posStack - 4] = stackType[posStack - 3];
				stackNumber[posStack - 4] = stackNumber[posStack - 3];
				stackStartPos[posStack - 4] = stackStartPos[posStack - 3];
				stackCharCount[posStack - 4] = stackCharCount[posStack - 3];
				stackType[posStack - 3] = stackType[posStack - 1];
				stackNumber[posStack - 3] = stackNumber[posStack - 1];
				stackStartPos[posStack - 3] = stackStartPos[posStack - 1];
				stackCharCount[posStack - 3] = stackCharCount[posStack - 1];
				posStack -= 2;
				flag = true;
			}

			// Process functions.
			if(posStack >= 3 && stackType[posStack - 2] == expressionNumber
					&& stackType[posStack - 3] == expressionText){
				wxString command = text.Mid(stackStartPos[posStack - 3],
						stackCharCount[posStack - 3]);
				bool foundcommand = false;
				if(command.CmpNoCase(_T("cos")) == 0){
					stackNumber[posStack - 3] = cos(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("sin")) == 0){
					stackNumber[posStack - 3] = sin(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("tan")) == 0){
					stackNumber[posStack - 3] = tan(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("acos")) == 0){
					stackNumber[posStack - 3] = acos(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("asin")) == 0){
					stackNumber[posStack - 3] = asin(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("atan")) == 0){
					stackNumber[posStack - 3] = atan(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("exp")) == 0){
					stackNumber[posStack - 3] = exp(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("log")) == 0){
					if(stackNumber[posStack - 2] <= 0.0){
						error = _T("log of a negative number.");
						return false;
					}
					stackNumber[posStack - 3] = log(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("sqrt")) == 0){
					if(stackNumber[posStack - 2] < 0.0){
						error = _T("sqrt of a negative number.");
						return false;
					}
					stackNumber[posStack - 3] = sqrt(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("cbrt")) == 0){
					stackNumber[posStack - 3] = cbrt(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("ceil")) == 0){
					stackNumber[posStack - 3] = ceil(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("floor")) == 0){
					stackNumber[posStack - 3] = floor(
							stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("round")) == 0){
					stackNumber[posStack - 3] = round(
							stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(command.CmpNoCase(_T("abs")) == 0){
					stackNumber[posStack - 3] = fabs(stackNumber[posStack - 2]);
					foundcommand = true;
				}

				if(foundcommand){
					stackType[posStack - 3] = expressionNumber;
					stackType[posStack - 2] = stackType[posStack - 1];
					stackNumber[posStack - 2] = stackNumber[posStack - 1];
					stackStartPos[posStack - 2] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 2] = stackCharCount[posStack - 1];
					posStack -= 1;
					flag = true;
				}
			}

			// Negative numbers.
			if((posStack == 3 && stackType[posStack - 2] == expressionNumber
					&& stackType[posStack - 3] == expressionOperation)
					|| (posStack >= 4
							&& stackType[posStack - 2] == expressionNumber
							&& stackType[posStack - 3] == expressionOperation
							&& stackType[posStack - 4] != expressionNumber)){

				wxChar op = text.at(stackStartPos[posStack - 3]);
				if(op == '-'){
					stackNumber[posStack - 3] = -stackNumber[posStack - 2];
					stackType[posStack - 3] = expressionNumber;
					stackType[posStack - 2] = stackType[posStack - 1];
					stackNumber[posStack - 2] = stackNumber[posStack - 1];
					stackStartPos[posStack - 2] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 2] = stackCharCount[posStack - 1];
					posStack -= 1;
					flag = true;
				}
			}

			// Add, Sub, Mult, Div, Power. (also '^' before '*', '/' before '+', '-')
			if(posStack >= 4 && stackType[posStack - 2] == expressionNumber
					&& stackType[posStack - 3] == expressionOperation
					&& stackType[posStack - 4] == expressionNumber){
				// Current operation is in op, the next one is in op2. op2 is used to decide, if an
				// operation can be done right away or we have to do op2 first.
				wxChar op = text.at(stackStartPos[posStack - 3]);
				wxChar op2 = text.at(stackStartPos[posStack - 1]);
				if(stackType[posStack - 1] != expressionOperation || (op == '^')
						|| ((op == '*' || op == '/') && (op2 != '^'))
						|| ((op == '+' || op == '-')
								&& (op2 != '*' && op2 != '/' && op2 != '^'))){
					if(op == '+') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									+ stackNumber[posStack - 2];
					if(op == '-') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									- stackNumber[posStack - 2];
					if(op == '*') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									* stackNumber[posStack - 2];
					if(op == '/'){
						if(stackNumber[posStack - 2] == 0.0){
							error = _T("Division by 0.");
							return false;
						}
						stackNumber[posStack - 4] = stackNumber[posStack - 4]
								/ stackNumber[posStack - 2];
					}
					if(op == '^') stackNumber[posStack - 4] = pow(
							stackNumber[posStack - 4],
							stackNumber[posStack - 2]);
					stackType[posStack - 3] = stackType[posStack - 1];
					stackNumber[posStack - 3] = stackNumber[posStack - 1];
					stackStartPos[posStack - 3] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 3] = stackCharCount[posStack - 1];
					posStack -= 2;
					flag = true;
				}
			}

		}
	}

	// Check if stack could be totally reduced into a Number + EndSymbol or Number + Text + EndSymbol.
	// In the second case, assume that the text is a unit.

	switch(posStack){
	case 0:
		error = _T("This should not be possible.");
		break;
	case 1:
		error = _T("Expression empty.");
		break;
	case 2:
		if(stackType[1] == expressionEnd && stackType[0] == expressionNumber){
			number = stackNumber[0];
			unit.Empty();
		}else{
			error = _T("Cannot be reduced to a number.");
		}
		break;
	case 3:
		if(allowedUnits.empty() && stackType[2] == expressionEnd
				&& stackType[1] == expressionText
				&& stackType[0] == expressionNumber){
			number = stackNumber[0];
			unit = text.Mid(stackStartPos[1], stackCharCount[1]);
		}else{
			error = _T("Cannot be reduced to a number.");
		}
		break;
	default:
		error = _T("Could not parse expression completely.");
		break;
	}

	return !HasError();
}

