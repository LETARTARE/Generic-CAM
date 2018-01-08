///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorSurfaceDexel.cpp
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

#include "GeneratorSurfaceDexel.h"

#include <float.h>

#include "../Run.h"
#include "ProtoToolpath.h"

GeneratorSurfaceDexel::GeneratorSurfaceDexel()
{
}

GeneratorSurfaceDexel::~GeneratorSurfaceDexel()
{
}

void GeneratorSurfaceDexel::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorSurfaceDexel * temp =
			dynamic_cast <const GeneratorSurfaceDexel*>(other);
}

wxString GeneratorSurfaceDexel::GetName(void) const
{
	return _T("Surface refinement (using Dexel)");
}

void GeneratorSurfaceDexel::AddToPanel(wxPanel* panel,
		DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer(1, 3, 0, 0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextTwiddleFactor = new wxStaticText(panel, wxID_ANY,
			wxT("Max. rest error:"), wxDefaultPosition, wxDefaultSize, 0);
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

void GeneratorSurfaceDexel::TransferDataToPanel(void) const
{
}

void GeneratorSurfaceDexel::TransferDataFromPanel(void)
{
}

void GeneratorSurfaceDexel::GenerateToolpath(void)
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
	toolShape.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY(),
			true);
	toolShape.NegateZ();

	target.FoldRaise(toolShape);
	target.Limit();
	start.MarkHeightDelta(toolShape, target, true);
//	debug = start;
//	debug.CopyToUp(4, 1.0);

	toolShape.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY(),
			false);
	toolShape.NegateZ();

	ArrayOfProtoToolpath aptp;
	GCodeBlock m;
	m.FeedSpeed();
	int x, y;
	double d;
	d = start.GetMaxLevelAD(x, y);

	const double residualError = 2e-3;

	while(d > residualError){
		while(d > residualError){
			ProtoToolpath pt;
			double px = (double) x * target.GetResolutionX()
					+ target.GetResolutionX() / 2;
			double py = (double) y * target.GetResolutionY()
					+ target.GetResolutionY() / 2;

			ImprinterElement t = target.GetElement(px, py);
			m.X = px;
			m.Y = py;
			m.Z = t.up;
			pt.positions.Add(m);

			double level = t.up;
			double nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);

			while(nd > FLT_EPSILON && t.IsVisible()){
				px -= t.normalx / nd * 0.8 * target.GetResolutionX();
				py -= t.normaly / nd * 0.8 * target.GetResolutionY();
				t = target.GetElement(px, py);
				if(t.up <= level) break;
				m.X = px;
				m.Y = py;
				m.Z = t.up;
				pt.positions.Add(m);

				level = t.up;
				nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);
			}

			px = x * target.GetResolutionX() + target.GetResolutionX() / 2;
			py = y * target.GetResolutionY() + target.GetResolutionY() / 2;
			t = target.GetElement(px, py);
			level = t.up;
			nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);
			while(nd > FLT_EPSILON && t.IsVisible()){
				px += t.normalx / nd * 0.8 * target.GetResolutionX();
				py += t.normaly / nd * 0.8 * target.GetResolutionY();
				t = target.GetElement(px, py);
				if(t.up >= level) break;

				m.X = px;
				m.Y = py;
				m.Z = t.up;
				pt.positions.Insert(m, 0);

				level = t.up;
				nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);
			}

			wxArrayInt k;
			for(size_t n = 0; n < pt.positions.GetCount(); n++){
				const ImprinterElement s = start.GetElement(pt.positions[n].X,
						pt.positions[n].Y);
				if(s.up - s.down < -FLT_EPSILON){

					k.Add(0);
					continue;
				}
				k.Add((s.aboveDown > residualError)? -1 : 0);
			}

			for(size_t n = 0; n < k.GetCount(); n++){
				const int ix = round(
						(pt.positions[n].X - start.GetResolutionX() / 2)
								/ start.GetResolutionX());
				const int iy = round(
						(pt.positions[n].Y - start.GetResolutionY() / 2)
								/ start.GetResolutionY());
				if(ix >= 0 && ix < start.GetCountX() && iy >= 0
						&& iy < start.GetCountY()) start.TouchErase(ix, iy,
						pt.positions[n].Z, pt.positions[n].Z, toolShape);
			}

			int c = 100;
			for(size_t n = 0; n < pt.positions.GetCount(); n++){
				if(k[n] < 0){
					if(c <= 2){
						for(size_t m = 0; m < c; m++)
							k[n - m - 1] = -1;
					}
					c = 0;
				}else{
					c++;
				}
			}

			assert(k.GetCount() == pt.GetCount());
			k.Add(0);
			ProtoToolpath temp;
			for(size_t n = 0; n < k.GetCount(); n++){
				if(k[n]){
					temp.positions.Add(pt.positions[n]);
					continue;
				}

				if(!temp.positions.IsEmpty()){
					aptp.Add(temp);
				}
				temp.positions.Clear();

			}

			d = start.GetMaxLevelAD(x, y);
		}

		start.MarkHeightDelta(toolShape, target, false);
//		debug = toolShape;
//		debug.CopyToUp(4, 0.01);
		d = start.GetMaxLevelAD(x, y);
//		break;

	}
//	toolShape.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY(),
//			false);
//	toolShape.NegateZ();
//
//	toolpath.Clear();

//	Polygon25 pg = target.GeneratePolygon(-1, -1, FLT_EPSILON);
//	pg.RotatePolygonStart(0, 0);
//
//
//	GCodeBlock m;
//	if(pg.GetCount() > 0){
//		m.Rapid();
//		m.X = pg.elements[0].x;
//		m.Y = pg.elements[0].y;
//		m.Z = target.GetSizeZ() + freeHeight;
//		toolpath.positions.Add(m);
//
//		const double cutdepth = tool->GetCuttingDepth();
//		const int N = ceil((area.zmax - area.zmin) / cutdepth);
//		for(int n = 1; n <= N; n++){
//			const double level = fmax(area.zmax - n * cutdepth, area.zmin);
//
//			for(size_t n = 0; n < pg.GetCount(); n++){
//				m.X = pg.elements[n].x;
//				m.Y = pg.elements[n].y;
//				m.Z = level;
//				m.FeedSpeed();
//				toolpath.positions.Add(m);
//			}
//			m.X = pg.elements[0].x;
//			m.Y = pg.elements[0].y;
//			toolpath.positions.Add(m);
//		}
//		m.Z = target.GetSizeZ() + freeHeight;
//		m.Rapid();
//		toolpath.positions.Add(m);
//	}

	QuickCollectToolpaths(aptp, 3 * 6e-3);

	if(!toolpath.IsEmpty()){
		{
			GCodeBlock m = toolpath.positions[0];
			m.Z = target.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.positions.Insert(m, 0);
		}
		{
			GCodeBlock m = toolpath.positions.Last();
			m.Z = target.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.positions.Add(m);
		}
	}

	toolpath.FlagAll(true);

}
