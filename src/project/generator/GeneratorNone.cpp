///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorNone.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.02.2015
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

#include "GeneratorNone.h"

#include "../../icon/curlyarrow.xpm"

#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/sizer.h>

GeneratorNone::GeneratorNone()
{
}

void GeneratorNone::CopyParameterFrom(const Generator * other)
{
	Generator::CopyParameterFrom(other);
}

GeneratorNone::~GeneratorNone()
{
}

wxString GeneratorNone::GetName(void) const
{
	return _("None");
}

void GeneratorNone::AddToPanel(wxPanel* panel, DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);
	wxStaticBitmap* m_bitmap;
	wxStaticText* m_staticText1;
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);
	bSizer1->Add(0, 0, 1, wxEXPAND, 5);
	m_bitmap = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(curlyarrow_xpm),
			wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_bitmap, 0, wxALL, 5);
	m_staticText1 = new wxStaticText(panel, wxID_ANY,
			wxT("Select a generator from the list above."), wxDefaultPosition,
			wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer1->Add(m_staticText1, 0, wxALL, 5);
	bSizer1->Add(0, 0, 1, wxEXPAND, 5);
	panel->SetSizer(bSizer1);
	panel->Layout();
	bSizer1->Fit(panel);
}

void GeneratorNone::TransferDataToPanel(void) const
{
}

void GeneratorNone::TransferDataFromPanel(void)
{
}

void GeneratorNone::GenerateToolpath(void)
{
	printf("None called.\n");
	errorOccured = false;
	toolpathGenerated = true;
}
