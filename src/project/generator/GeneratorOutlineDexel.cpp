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

wxString GeneratorOutlineDexel::GetTypeName(void) const
{
	return _T("Outline (using Dexel)");
}

wxSizer * GeneratorOutlineDexel::AddToPanel(wxPanel* panel,
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

void GeneratorOutlineDexel::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
}

void GeneratorOutlineDexel::TransferDataFromPanel(CollectionUnits* settings)
{
}

bool GeneratorOutlineDexel::operator ==(const Generator& b) const
{
	const GeneratorOutlineDexel * temp =
			dynamic_cast <const GeneratorOutlineDexel*>(&b);
	std::cout << "GeneratorOutlineDexel::operator ==\n";
	if(!(this->Generator::operator ==(b))) return false;
	return true;
}

void GeneratorOutlineDexel::GenerateToolpath(const Run &run,
		const std::map <size_t, Object> &objects, const Tool &tool,
		const DexelTarget &base)
{
	errorOccured = false;
	toolpathGenerated = true;
	output.Empty();

	GeneratorDexel::PrepareTargets(run, objects, tool, base);

//	DexelTarget surface = target;
	DexelTarget toolShape;
	toolShape.SetupTool(tool, target.GetResolutionX(),
			target.GetResolutionY());
	debug = target;
	toolShape.NegateZ();
	target.FoldRaise(toolShape);
	target.Limit();

	Polygon25 pg = target.GeneratePolygon(-1, -1, FLT_EPSILON);
	pg.RotatePolygonStart(0, 0);

	toolpath.clear();

	CNCPosition m;
	if(pg.Size() > 0){
		m.Rapid();
		m.position.Set(pg[0].x, pg[0].y, target.GetSizeZ() + freeHeight);
		toolpath.push_back(m);

		const double cutdepth = tool.GetCuttingDepth();
		const int N = ceil((start.GetSizeZ() - 0) / cutdepth);
		for(int n = 1; n <= N; n++){
			const double level = fmax(start.GetSizeZ() - n * cutdepth, 0);

			for(size_t n = 0; n < pg.Size(); n++){
				m.position.Set(pg[n].x, pg[n].y, level);
				m.FeedSpeed();
				toolpath.push_back(m);
			}
			m.position.x = pg[0].x;
			m.position.y = pg[0].y;
			toolpath.push_back(m);
		}
		m.position.z = target.GetSizeZ() + freeHeight;
		m.Rapid();
		toolpath.push_back(m);
	}
}
