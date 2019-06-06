///////////////////////////////////////////////////////////////////////////////
// Name               : Unit.cpp
// Purpose            : Value with unit
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

#include "Unit.h"

#include <wx/log.h>

Unit::Unit()
{
	factor = 1.0;
	m = 0;
	s = 0;
	kg = 0;
	A = 0;
	K = 0;
	mol = 0;
	cd = 0;
	cur = 0;
	power = 0.0;
//	this->extra = _T("*");
}

Unit::Unit(wxString currency)
{
	SetCurrency(currency);
}

Unit::Unit(unit predefinedUnit, wxString extra)
{
	SetUnit(predefinedUnit, extra);
}

Unit::Unit(const wxString SIName, const wxString otherName, const double factor)
{
	this->SIName = SIName;
	this->otherName = otherName;
	if(factor != 0)
		this->factor = factor;
	else
		this->factor = 1.0;
	m = 0;
	kg = 0;
	s = 0;
	A = 0;
	K = 0;
	mol = 0;
	cd = 0;
	cur = 0;
	power = 0.0;
}

Unit::Unit(int m, int kg, int s, int A, int K, int mol, int cd, int cur)
		: m(m), kg(kg), s(s), A(A), K(K), mol(mol), cd(cd), cur(cur)
{
	power = 0.0;
	factor = 1.0;
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

void Unit::SetUnit(unit predefinedUnit, wxString extra)
{
	m = 0;
	s = 0;
	kg = 0;
	A = 0;
	K = 0;
	mol = 0;
	cd = 0;
	cur = 0;
//	this->extra = extra;

	switch(predefinedUnit){
	case Unitless:
		break;
	case Second:
		s = 1;
		break;
	case Volume:
		m = 3;
		break;
	case Celsius:
		K = 1;
		break;
	}
}

void Unit::SetCurrency(wxString currency)
{
	m = 0;
	s = 0;
	kg = 0;
	A = 0;
	K = 0;
	mol = 0;
	cd = 0;
	cur = 1;
//	this->extra = currency;
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

wxString Unit::TextFromSIWithUnit(const double value, int digitsAfterComma)
{
	if(digitsAfterComma < 0){
		return wxString::Format(_T("%g "), FromSI(value)) + otherName;
	}else{
		wxString temp = wxString::Format(_T("%%.%uf "), digitsAfterComma);
		return wxString::Format(temp, FromSI(value)) + otherName;
	}
}

wxString Unit::TextFromSI(const double value, int digitsAfterComma)
{
	if(digitsAfterComma < 0){
		return wxString::Format(_T("%g"), FromSI(value));
	}else{
		wxString temp = wxString::Format(_T("%%.%uf"), digitsAfterComma);
		return wxString::Format(temp, FromSI(value));
	}
}

wxString Unit::GetOtherName(void)
{
	return otherName;
}

double Unit::SIFromString(const wxString& text, bool useEvaluator)
{
#ifdef _USE_MATHPARSER
	parser.SetString(text);
	return ToSI(parser.GetNumber());
#else
	double temp;
	text.ToDouble(&temp);
	return ToSI(temp);
#endif
}
