///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorDrillDexel.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 23.12.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "GeneratorDrillDexel.h"

#include "../Run.h"

#include <float.h>
#include <wx/sizer.h>


GeneratorDrillDexel::GeneratorDrillDexel()
{
}

GeneratorDrillDexel::~GeneratorDrillDexel()
{
}

void GeneratorDrillDexel::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);
	const GeneratorDrillDexel * temp =
			dynamic_cast <const GeneratorDrillDexel*>(other);
}

bool GeneratorDrillDexel::operator ==(const Generator& b) const
{
	if(!(this->Generator::operator ==(b))) return false;
	return true;
}

wxSizer * GeneratorDrillDexel::AddToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer(1, 3, 0, 0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextTwiddleFactor = new wxStaticText(panel, wxID_ANY, wxT("XYZ:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextTwiddleFactor->Wrap(-1);
	fgSizer->Add(m_staticTextTwiddleFactor, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 5);

	m_textCtrlTwiddleFactor = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, 0);
	fgSizer->Add(m_textCtrlTwiddleFactor, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticTextUnit = new wxStaticText(panel, wxID_ANY, wxT("mm"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnit->Wrap(-1);
	fgSizer->Add(m_staticTextUnit, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer->Add(fgSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	return bSizer;
}

void GeneratorDrillDexel::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
}

void GeneratorDrillDexel::TransferDataFromPanel(CollectionUnits* settings)
{
}

void GeneratorDrillDexel::GenerateToolpath(const Run &run,
		const std::map <size_t, Object> &objects, const Tool &tool,
		const DexelTarget &base)
{
	GeneratorDexel::PrepareTargets(run, objects, tool, base);

	output.Empty();
	errorOccured = false;
	toolpathGenerated = true;
//	const Run* const run = this->parent;
//	assert(run != NULL);
//	if(refTool >= run->machine.tools.GetCount()){
//		output = _T("Tool empty.");
//		errorOccured = true;
//		return;
//	}
//	const Tool* const tool = &(run->machine.tools[refTool]);

//	DexelTarget surface = target;
//	DexelTarget toolShape;
//	toolShape.SetupTool(*tool, target.GetResolutionX(),
//			target.GetResolutionY());
//	toolShape.NegateZ();
//	target.FoldRaise(toolShape);
//	target.Limit();

//	target.GenerateDistanceMap(FLT_EPSILON, target.GetSizeZ() + FLT_EPSILON);
//	debug = target;
//	debug.CopyToUp(4, 1);

}
