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

#include "../Run.h"
#include "ProtoToolpath.h"

#include <float.h>

#include <wx/sizer.h>

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

wxString GeneratorSurfaceDexel::GetTypeName(void) const
{
	return _T("Surface refinement (using Dexel)");
}

wxSizer * GeneratorSurfaceDexel::AddToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
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
	return bSizer;
}

void GeneratorSurfaceDexel::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
}

void GeneratorSurfaceDexel::TransferDataFromPanel(CollectionUnits* settings)
{
}

bool GeneratorSurfaceDexel::operator ==(const Generator& b) const
{
	const GeneratorSurfaceDexel * temp =
			dynamic_cast <const GeneratorSurfaceDexel*>(&b);
	std::cout << "GeneratorSurfaceDexel::operator ==\n";
	if(!(this->Generator::operator ==(b))) return false;
	return true;
}

void GeneratorSurfaceDexel::GenerateToolpath(const Run &run,
		const std::map <size_t, Object> &objects, const Tool &tool,
		const DexelTarget &base)
{
	errorOccured = false;
	toolpathGenerated = true;
	output.Empty();
	GeneratorDexel::PrepareTargets(run, objects, base);

	//	DexelTarget surface = target;
	DexelTarget toolShape;
	toolShape.SetupTool(tool, target.GetResolutionX(), target.GetResolutionY());
	toolShape.NegateZ();

	target.FoldRaise(toolShape);
	target.Limit();
	start.MarkHeightDelta(toolShape, target, true);
//	debug = start;
//	debug.CopyToUp(4, 1.0);

	toolShape.SetupTool(tool, target.GetResolutionX(), target.GetResolutionY());
	toolShape.NegateZ();

	std::vector <ProtoToolpath> aptp;
	CNCPosition m;
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
			m.position.x = px;
			m.position.y = py;
			m.position.z = t.up;
			pt.p.push_back(m);

			double level = t.up;
			double nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);

			while(nd > FLT_EPSILON && t.IsVisible()){
				px -= t.normalx / nd * 0.8 * target.GetResolutionX();
				py -= t.normaly / nd * 0.8 * target.GetResolutionY();
				t = target.GetElement(px, py);
				if(t.up <= level) break;
				m.position.x = px;
				m.position.y = py;
				m.position.z = t.up;
				pt.p.push_back(m);

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

				m.position.x = px;
				m.position.y = py;
				m.position.z = t.up;
				pt.p.insert(pt.p.begin(), m);

				level = t.up;
				nd = sqrt(t.normalx * t.normalx + t.normaly * t.normaly);
			}

			std::vector <int> k;
			for(size_t n = 0; n < pt.p.size(); n++){
				const ImprinterElement s = start.GetElement(pt.p[n].position.x,
						pt.p[n].position.y);
				if(s.up - s.down < -FLT_EPSILON){

					k.push_back(0);
					continue;
				}
				k.push_back((s.aboveDown > residualError)? -1 : 0);
			}

			for(size_t n = 0; n < k.size(); ++n){
				const int ix = round(
						(pt.p[n].position.x - start.GetResolutionX() / 2)
								/ start.GetResolutionX());
				const int iy = round(
						(pt.p[n].position.y - start.GetResolutionY() / 2)
								/ start.GetResolutionY());
				if(ix >= 0 && ix < start.GetCountX() && iy >= 0
						&& iy < start.GetCountY()) start.TouchErase(ix, iy,
						pt.p[n].position.z, pt.p[n].position.z, toolShape);
			}

			int c = 100;
			for(size_t n = 0; n < pt.p.size(); ++n){
				if(k[n] < 0){
					if(c <= 2){
						for(size_t m = 0; m < c; ++m)
							k[n - m - 1] = -1;
					}
					c = 0;
				}else{
					c++;
				}
			}

			assert(k.size() == pt.p.size());
			k.push_back(0);
			ProtoToolpath temp;
			for(size_t n = 0; n < k.size(); n++){
				if(k[n]){
					temp.p.push_back(pt.p[n]);
					continue;
				}

				if(!temp.p.empty()){
					aptp.push_back(temp);
				}
				temp.p.clear();

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
//	CNCPosition m;
//	if(pg.GetCount() > 0){
//		m.Rapid();
//		m.position.X = pg.elements[0].x;
//		m.position.Y = pg.elements[0].y;
//		m.position.Z = target.GetSizeZ() + freeHeight;
//		toolpath.push_back(m);
//
//		const double cutdepth = tool->GetCuttingDepth();
//		const int N = ceil((start.GetSizez() - 0) / cutdepth);
//		for(int n = 1; n <= N; n++){
//			const double level = fmax(start.GetSizez() - n * cutdepth, 0);
//
//			for(size_t n = 0; n < pg.GetCount(); n++){
//				m.position.X = pg.elements[n].x;
//				m.position.Y = pg.elements[n].y;
//				m.position.Z = level;
//				m.FeedSpeed();
//				toolpath.push_back(m);
//			}
//			m.position.X = pg.elements[0].x;
//			m.position.Y = pg.elements[0].y;
//			toolpath.push_back(m);
//		}
//		m.position.Z = target.GetSizeZ() + freeHeight;
//		m.Rapid();
//		toolpath.push_back(m);
//	}

	QuickCollectToolpaths(aptp, 3 * 6e-3);

	if(!toolpath.empty()){
		{
			CNCPosition m = toolpath[0];
			m.position.z = target.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.insert(toolpath.begin(), m);
		}
		{
			CNCPosition m = *(toolpath.end() - 1);
			m.position.z = target.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.push_back(m);
		}
	}
}
