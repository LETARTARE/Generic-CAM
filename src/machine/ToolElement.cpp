///////////////////////////////////////////////////////////////////////////////
// Name               : ToolElement.h
// Purpose            : Hold the description of an element of the toolshape.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
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

#include "ToolElement.h"

#include <wx/tokenzr.h>
#include <wx/arrimpl.cpp>
// this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfToolElement)
WX_DEFINE_OBJARRAY(ArrayOfToolContourElement)

ToolContourElement::ToolContourElement(bool cutting, bool partOfShaft)
{
	isCutting = cutting;
	belongsToShaft = partOfShaft;
}

ToolContourElement::~ToolContourElement()
{
}

ToolElement::ToolElement()
{
	d = h = 1.0;
	r = 0.0;
	cutting = false;
	t = 0;
}

ToolElement::ToolElement(const wxString & string)

{
	this->FromString(string);
}

ToolElement::~ToolElement()
{
}

wxString ToolElement::ToString(void) const
{
	return wxString::Format(_T("%f#%f#%f#%u#%c"), d, h, r, t,
			cutting? 'C' : 'N');
}

void ToolElement::FromString(wxString const &string)
{
	wxStringTokenizer tkz(string, wxT("#"));
	double temp;
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		switch(tkz.CountTokens()){
		case 4:
			token.ToDouble(&temp);
			d = temp;
			break;
		case 3:
			token.ToDouble(&temp);
			h = temp;
			break;
		case 2:
			token.ToDouble(&temp);
			r = temp;
			break;
		case 1:
			t = token[0] - '0';
			break;
		case 0:
			cutting = (token == 'C');
			break;
		}
	}
}
