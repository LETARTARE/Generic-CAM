///////////////////////////////////////////////////////////////////////////////
// Name               : Unit.cpp
// Purpose            : Value with unit
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

#include "Unit.h"

#include <wx/log.h>

Unit::Unit()
{
	factor = 1.0;
}

Unit::Unit(const wxString SIName, const wxString otherName, const double factor)
{
	this->SIName = SIName;
	this->otherName = otherName;
	if(factor != 0)
		this->factor = factor;
	else
		this->factor = 1.0;
}

void Unit::Setup(const wxString SIName, const wxString otherName,
		const double factor)
{
	this->SIName = SIName;
	this->otherName = otherName;
	if(factor != 0)
		this->factor = factor;
	else
		this->factor = 1.0;
}

double Unit::FromSI(const double value)
{
	return value / factor;
}

double Unit::ToSI(const double value)
{
	return value * factor;
}

wxString Unit::GetSIName(void)
{
	return SIName;
}

wxString Unit::TextFromSIWithUnit(const double value,
		unsigned int digitsAfterComma)
{
	wxString temp = wxString::Format(_T("%%.%uf "), digitsAfterComma);
	return wxString::Format(temp, FromSI(value)) + otherName;
}

wxString Unit::TextFromSI(const double value, unsigned int digitsAfterComma)
{
	wxString temp = wxString::Format(_T("%%.%uf "), digitsAfterComma);
	return wxString::Format(temp, FromSI(value));
}

wxString Unit::GetOtherName(void)
{
	return otherName;
}

double Unit::SIFromString(const wxString& text)
{
	parser.SetString(text);
	return ToSI(parser.GetNumber());
}
