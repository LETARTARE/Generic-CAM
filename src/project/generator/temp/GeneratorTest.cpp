///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorTest.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.07.2011
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

#include "GeneratorTest.h"

#include <math.h>
#include <wx/log.h>
#include <wx/wxchar.h>

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Polygon25.h"
#include "../../3D/Vector3.h"
#include "../machine/CNCPosition.h"
#include "../Project.h"
#include "../ToolPath.h"
#include "DexelTarget.h"

GeneratorTest::GeneratorTest()
{
	twiddleFactor = 0.008;
}

GeneratorTest::~GeneratorTest()
{

}

void GeneratorTest::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorTest * temp = dynamic_cast <const GeneratorTest*>(other);

	twiddleFactor = temp->twiddleFactor;
}

wxString GeneratorTest::GetName(void) const
{
	return _T("Test Generator (using Dexel)");
}

void GeneratorTest::AddToPanel(wxPanel* panel, CollectionUnits* settings)
{
	Generator::AddToPanel(panel, settings);

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer(1, 3, 0, 0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextTwiddleFactor = new wxStaticText(panel, wxID_ANY,
			wxT("Twiddle factor:"), wxDefaultPosition, wxDefaultSize, 0);
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

void GeneratorTest::TransferDataToPanel(void) const
{
	m_staticTextUnit->SetLabel(settings->SmallDistance.GetOtherName());
	m_textCtrlTwiddleFactor->SetValue(
			settings->SmallDistance.TextFromSI(twiddleFactor));

}

void GeneratorTest::TransferDataFromPanel(void)
{
	twiddleFactor = settings->SmallDistance.SIFromString(
			m_textCtrlTwiddleFactor->GetValue());
}

void GeneratorTest::GenerateToolpath(void)
{
	output.Empty();
	const Run* const run = this->parent;
	assert(run != NULL);
	if(refTool >= run->machine.tools.GetCount()){
		output = _T("Tool empty.");
		errorOccured = true;
		return;
	}

	GeneratorDexel::GenerateToolpath();

	const Tool* const tool = &(run->machine.tools[refTool]);

	const double maxCutDepth = tool->GetCuttingDepth();

	const double tolerance = 0.0001; // 1/10 mm

	ToolPath tp;

	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY(),
			false);

	toolShape.NegateZ();
	DexelTarget temp = target;
	DexelTarget tempStart = start;
	temp.FoldRaise(toolShape);
	tempStart.FoldRaise(toolShape);
	temp.Limit();
	tempStart.Limit();
	toolShape.NegateZ();

	DexelTarget temptop = temp;
	temp.InvertTop();
	temp &= tempStart;
	double level = temp.GetSizeZ(); // at upper surface

	GCodeBlock m;
	m.X = 0.0;
	m.Y = 0.0;
	m.Z = temp.GetSizeZ() + freeHeight;
	m.Rapid();

	std::vector <Polygon25> pgs;
	Polygon25 pg;

//	AffineTransformMatrix tm;
//	tm.TranslateGlobal(0.0, 0.0, -0.0001);

	while(level > -tolerance){
		const double dropLevel = fmax(level - maxCutDepth, 0.0);

		// Find all polygons on one level
		pg = temp.GeneratePolygon(-1, -1, level - tolerance);
		while(pg.Size() > 0){
			temptop.PolygonDropOntoTarget(pg, dropLevel);
			temp.PolygonPunchThroughTarget(pg, dropLevel, toolShape);
			pg.PolygonSmooth();
			pgs.push_back(pg);
			pg = temp.GeneratePolygon(-1, -1, level - tolerance);
		}

//		debug = temp;
//		debug.Empty();
//		debug.outLine = pgs[4];
//		for(size_t n = 0; n < debug.N; n++){
//			const double x = ((double) (n % debug.nx) + 0.5) * debug.rx;
//			const double y = ((double) (n / debug.nx) + 0.5) * debug.ry;
//			if(pgs[4].IsElementInside(Vector3(x, y, 0))){
//				debug.field[n].down = 0.01;
//				debug.field[n].up = 0.02;
//			}
//		}
//		return;

		Polygon25::SortPolygonsFromOutside(&pgs);

//		debug = temp;

		bool isMillUp = true;
		// Generate a toolpath from the polygon collection
		for(size_t i = pgs.size(); i > 0; i--){
			if(pgs[i - 1].Size() == 0) continue;

			pgs[i - 1].RotatePolygonStart(m.X, m.Y);

			if(!isMillUp){
				const double d2 = (m.X - pgs[i - 1][0].x)
						* (m.X - pgs[i - 1][0].x)
						+ (m.Y - pgs[i - 1][0].y) * (m.Y - pgs[i - 1][0].y);
				if(d2 > (twiddleFactor * twiddleFactor)){
					// Move tool out of material to travel to next polygon.
					m.Rapid();
					m.Z = temp.GetSizeZ() + freeHeight;
					tp.positions.Add(m);
					isMillUp = true;
				}
			}

			if(isMillUp){
				// Move tool to next position
				m.X = pgs[i - 1][0].x;
				m.Y = pgs[i - 1][0].y;
				m.Z = temp.GetSizeZ() + freeHeight;
				m.Rapid();
				tp.positions.Add(m);
			}
			// Add polyg.positions[i].X,on
			m.FeedSpeed();
			isMillUp = false;

			for(size_t j = 0; j < pgs[i - 1].Size(); j++){
				m.X = pgs[i - 1][j].x;
				m.Y = pgs[i - 1][j].y;
				m.Z = pgs[i - 1][j].z;
				tp.positions.Add(m);
			}
		}
		pgs.clear();

		if(level >= 0.0 && level < 3 * tolerance){
			level = -1.0;
		}else{
			level = dropLevel;
			if(level < 2 * tolerance){
				level = 2 * tolerance;
			}
		}

		// Move tool out of material
		m.Z = temp.GetSizeZ() + freeHeight;
		m.Rapid();
		isMillUp = true;
		tp.positions.Add(m);
#ifdef _DEBUGMODE
		wxLogMessage(wxString::Format(_T("Next Level: %.3f m"), level));
//		level = -1;
#endif
	}
//	debug = temp;
	tp.FlagAll(true);

	toolpath = tp;
}
