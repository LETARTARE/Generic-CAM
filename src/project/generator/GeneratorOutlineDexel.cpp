///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorOutlineDexel.cpp
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

#include "GeneratorOutlineDexel.h"

#include "../Run.h"
#include "../../3D/Polygon25.h"

#include <float.h>

GeneratorOutlineDexel::GeneratorOutlineDexel()
{
}

GeneratorOutlineDexel::~GeneratorOutlineDexel()
{
}

void GeneratorOutlineDexel::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorOutlineDexel * temp =
			dynamic_cast <const GeneratorOutlineDexel*>(other);
}

wxString GeneratorOutlineDexel::GetName(void) const
{
	return _T("Outline (using Dexel)");
}

void GeneratorOutlineDexel::AddToPanel(wxPanel* panel,
		DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);

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

	panel->SetSizer(bSizer);
	panel->Layout();
	bSizer->Fit(panel);
}

void GeneratorOutlineDexel::TransferDataToPanel(void) const
{
}

void GeneratorOutlineDexel::TransferDataFromPanel(void)
{
}

void GeneratorOutlineDexel::GenerateToolpath(void)
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

//	DexelTarget surface = target;
	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetResolutionX(),
			target.GetResolutionY());
	debug = target;
	toolShape.NegateZ();
	target.FoldRaise(toolShape);
	target.Limit();

	Polygon25 pg = target.GeneratePolygon(-1, -1, FLT_EPSILON);
	pg.RotatePolygonStart(0, 0);

	toolpath.Clear();

	GCodeBlock m;
	if(pg.GetCount() > 0){
		m.Rapid();
		m.X = pg.elements[0].x;
		m.Y = pg.elements[0].y;
		m.Z = target.GetSizeZ() + freeHeight;
		toolpath.positions.Add(m);

		const double cutdepth = tool->GetCuttingDepth();
		const int N = ceil((area.zmax - area.zmin) / cutdepth);
		for(int n = 1; n <= N; n++){
			const double level = fmax(area.zmax - n * cutdepth, area.zmin);

			for(size_t n = 0; n < pg.GetCount(); n++){
				m.X = pg.elements[n].x;
				m.Y = pg.elements[n].y;
				m.Z = level;
				m.FeedSpeed();
				toolpath.positions.Add(m);
			}
			m.X = pg.elements[0].x;
			m.Y = pg.elements[0].y;
			toolpath.positions.Add(m);
		}
		m.Z = target.GetSizeZ() + freeHeight;
		m.Rapid();
		toolpath.positions.Add(m);
	}
	toolpath.FlagAll(true);
}
