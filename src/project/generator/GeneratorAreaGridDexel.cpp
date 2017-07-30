///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorAreaGridDexel.cpp
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

#include "GeneratorAreaGridDexel.h"

#include "../Run.h"
#include "../Tool.h"

#include <wx/sizer.h>

GeneratorAreaGridDexel::GeneratorAreaGridDexel()
{
	m_radioBoxDirection = NULL;
}

GeneratorAreaGridDexel::~GeneratorAreaGridDexel()
{

}

void GeneratorAreaGridDexel::CopyParameterFrom(const Generator * other)
{
	GeneratorDexel::CopyParameterFrom(other);
	// Only copy every public variable.
}

wxString GeneratorAreaGridDexel::GetName(void) const
{
	return _("Area Grid (Dexel)");
}

void GeneratorAreaGridDexel::AddToPanel(wxPanel* panel,
		DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);
	wxString arrayOfChoices[] =
		{wxT("X first then Y"), wxT("Y first then X")};
	int numberOfChoices = sizeof(arrayOfChoices) / sizeof(wxString);
	m_radioBoxDirection = new wxRadioBox(panel, wxID_ANY, wxT("Axis order"),
			wxDefaultPosition, wxDefaultSize, numberOfChoices, arrayOfChoices,
			1, wxRA_SPECIFY_ROWS);
	m_radioBoxDirection->SetSelection(0);
	bSizer->Add(m_radioBoxDirection, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	panel->SetSizer(bSizer);
	panel->Layout();
	bSizer->Fit(panel);
}

void GeneratorAreaGridDexel::TransferDataToPanel(void) const
{
}

void GeneratorAreaGridDexel::TransferDataFromPanel(void)
{
}

void GeneratorAreaGridDexel::GenerateToolpath(void)
{
	output.Empty();
	errorOccured = false;
	toolpathGenerated = true;
	const Run* const run = this->parent;
	assert(run != NULL);
	if(refTool >= run->machine.tools.GetCount()){
		output = _T("Tool empty.");
		errorOccured = true;
		return;
	}
	GeneratorDexel::GenerateToolpath();
	const Tool* const tool = &(run->machine.tools[refTool]);

	printf("AreaGridDexel called.\n");

//	ToolPath tp;
//	MachinePosition m;

	DexelTarget surface = target;
	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetSizeRX(), target.GetSizeRY());
	toolShape.NegateZ();
	surface.FoldRaise(toolShape);
	surface.Limit();

	debug = surface;
}
