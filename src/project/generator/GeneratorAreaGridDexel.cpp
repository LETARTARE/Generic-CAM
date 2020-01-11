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

#include "../../icon/xtheny.xpm"
#include "../../icon/ythenx.xpm"

#include <wx/sizer.h>
#include <float.h>

#include "../../gui/CollectionUnits.h"
#include "Generator.h"
//#include <cmath>

GeneratorAreaGridDexel::GeneratorAreaGridDexel()
{
	overlap = 0.1;
	maxStepUp = 0.01;
	type = 0;
}

GeneratorAreaGridDexel::~GeneratorAreaGridDexel()
{

}

wxString GeneratorAreaGridDexel::GetTypeName(void) const
{
	return _("Area Grid (Dexel)");
}

void GeneratorAreaGridDexel::CopyParameterFrom(const Generator * other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorAreaGridDexel * temp =
			dynamic_cast <const GeneratorAreaGridDexel*>(other);

	type = temp->type;
	overlap = temp->overlap;
}

bool GeneratorAreaGridDexel::operator ==(const Generator& b) const
{
	const GeneratorAreaGridDexel * temp =
			dynamic_cast <const GeneratorAreaGridDexel*>(&b);
	std::cout << "GeneratorAreaGridDexel::operator ==\n";
	if(!(this->Generator::operator ==(b))) return false;
	if(this->overlap != temp->overlap) return false;
	if(this->maxStepUp != temp->maxStepUp) return false;
	if(this->type != temp->type) return false;
	return true;
}
wxSizer * GeneratorAreaGridDexel::AddToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizerBorder;
	bSizerBorder = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* sbSizerDirection;
	sbSizerDirection = new wxStaticBoxSizer(
			new wxStaticBox(panel, wxID_ANY, wxT("Direction")), wxVERTICAL);

	wxFlexGridSizer* fgSizerDirection;
	fgSizerDirection = new wxFlexGridSizer(2, 2, 0, 0);
	fgSizerDirection->SetFlexibleDirection(wxBOTH);
	fgSizerDirection->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_radioBtnXthenY = new wxRadioButton(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxT("X first then Y"), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_radioBtnXthenY, 0, wxALL | wxALIGN_CENTER_VERTICAL,
			5);

	m_bitmapXthenY = new wxStaticBitmap(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxBitmap(xtheny_xpm), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_bitmapXthenY, 0, wxALL, 5);

	m_radioBtnYthenX = new wxRadioButton(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxT("Y first then X"), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_radioBtnYthenX, 0, wxALL | wxALIGN_CENTER_VERTICAL,
			5);

	m_bitmapYthenX = new wxStaticBitmap(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxBitmap(ythenx_xpm), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_bitmapYthenX, 0, wxALL, 5);

	sbSizerDirection->Add(fgSizerDirection, 0, 0, 5);

	bSizerBorder->Add(sbSizerDirection, 0, wxEXPAND | wxBOTTOM, 5);

	wxBoxSizer* bSizerDistance;
	bSizerDistance = new wxBoxSizer(wxHORIZONTAL);

	wxFlexGridSizer* fgSizerDistance;
	fgSizerDistance = new wxFlexGridSizer(1, 3, 0, 0);
	fgSizerDistance->AddGrowableCol(1);
	fgSizerDistance->SetFlexibleDirection(wxBOTH);
	fgSizerDistance->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextOverlap = new wxStaticText(panel, wxID_ANY, wxT("Overlap:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextOverlap->Wrap(-1);
	fgSizerDistance->Add(m_staticTextOverlap, 0,
			wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

	m_textCtrlOverlap = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, 0);
	m_textCtrlOverlap->SetToolTip(wxT("Distance between two rows."));

	fgSizerDistance->Add(m_textCtrlOverlap, 0, wxALL | wxEXPAND, 5);

	m_staticTextUnitOverlap = new wxStaticText(panel, wxID_ANY, wxT("%"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnitOverlap->Wrap(-1);
	fgSizerDistance->Add(m_staticTextUnitOverlap, 0,
			wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizerDistance->Add(fgSizerDistance, 1, 0, 5);

	bSizerBorder->Add(bSizerDistance, 0, wxEXPAND, 5);

	bSizer->Add(bSizerBorder, 0, wxALIGN_CENTER_HORIZONTAL, 5);
	return bSizer;
}

void GeneratorAreaGridDexel::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	m_staticTextUnitOverlap->SetLabel(settings->Percentage.GetOtherName());
	m_textCtrlOverlap->SetValue(settings->Percentage.TextFromSI(overlap));
	m_radioBtnXthenY->SetValue(type.direction == 0);
	m_radioBtnYthenX->SetValue(type.direction == 1);

}

void GeneratorAreaGridDexel::TransferDataFromPanel(CollectionUnits* settings)
{
	overlap = settings->Percentage.SIFromString(m_textCtrlOverlap->GetValue());
	if(m_radioBtnXthenY->GetValue()) type.direction = 0;
	if(m_radioBtnYthenX->GetValue()) type.direction = 1;
}

void GeneratorAreaGridDexel::GenerateToolpath(const Run &run,
		const std::map <size_t, Object> &objects, const Tool &tool,
		const DexelTarget &base)
{
	output.Empty();
	errorOccured = false;
	toolpathGenerated = true;

	GeneratorDexel::PrepareTargets(run, objects, tool, base);
	DexelTarget toolShape;
	toolShape.SetupTool(tool, selected.GetResolutionX(),
			selected.GetResolutionY(), false);
	toolShape.NegateZ();

	start.FoldRaise(toolShape);
	start.Limit();
	selected.FoldRaise(toolShape);
	selected.Limit();
//	debug = target;
	type.resolutionX = selected.GetResolutionX();
	type.resolutionY = selected.GetResolutionY();
	type.offsetX = selected.GetResolutionX() / 2;
	type.offsetY = selected.GetResolutionY() / 2;

	toolpath.clear();

	const double tooldiameter = tool.GetMaxDiameter();
	std::vector <ProtoToolpath> aptp;
	std::vector <CNCPosition> ptp;
	const double cutdepth = tool.GetCuttingDepth();
	const int N = ceil((start.GetSizeZ()) / cutdepth);

//	debug = start;

	for(int n = 1; n <= N; n++){
		const double level = fmax(start.GetSizeZ() - n * cutdepth, 0);

		aptp.clear();
		for(double x = 0 + tooldiameter / 2;
				x < start.GetSizeX() - tooldiameter / 2;
				x += tooldiameter * (1 - overlap)){

			const int ix = round(
					(x - selected.GetResolutionX() / 2)
							/ selected.GetResolutionX());
			if(ix < 0 || ix >= selected.GetCountX()) continue;
			int py0 = round(
					(0 - selected.GetResolutionY() / 2)
							/ selected.GetResolutionY());
			int py1 = round(
					(start.GetSizeY() - selected.GetResolutionY() / 2)
							/ selected.GetResolutionY());
			if(py0 < 0) py0 = 0;
			if(py1 >= selected.GetCountY()) py1 = selected.GetCountY() - 1;
			if(py1 < py0) continue;

			ptp.clear();
			CNCPosition m;
			for(int iy = py0; iy <= py1; ++iy){

				m.position.x = ix * selected.GetResolutionX()
						+ selected.GetResolutionX() / 2;
				m.position.y = iy * selected.GetResolutionY()
						+ selected.GetResolutionY() / 2;
				const ImprinterElement e = selected.GetElement(m.position.x,
						m.position.y);
				const ImprinterElement s = start.GetElement(m.position.x,
						m.position.y);
				m.normal.Set(e.normalx, e.normaly,
						sqrt(1.0 - e.normaly * e.normaly));
				m.FeedSpeed();

				m.position.z = fmax(e.up, level);

				if(m.position.z < s.up - FLT_EPSILON){
					start.SetLevel(m.position.x, m.position.y, m.position.z);
					if(!ptp.empty()
							&& fabs((ptp.end() - 1)->position.z - m.position.z)
									> maxStepUp){
						aptp.push_back(ProtoToolpath(ptp));
						ptp.clear();
					}
					ptp.push_back(m);
				}else{
					aptp.push_back(ProtoToolpath(ptp));
					ptp.clear();
				}
			}
			if(!ptp.empty()) aptp.push_back(ProtoToolpath(ptp));
		}
		CollectToolpaths(aptp, 3 * tooldiameter);
	}
	if(!toolpath.empty()){
		{
			CNCPosition m = toolpath[0];
			m.position.z = selected.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.insert(toolpath.begin(), m);
		}
		{
			CNCPosition m = *(toolpath.end() - 1);
			m.position.z = selected.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.push_back(m);
		}
	}
}

void GeneratorAreaGridDexel::CollectToolpaths(std::vector <ProtoToolpath> &ptp,
		const double pathDistance)
{
	if(ptp.size() == 0) return;

	CNCPosition m;
	if(!toolpath.empty()){
		m.position.x = (toolpath.end() - 1)->position.x;
		m.position.y = (toolpath.end() - 1)->position.y;
		m.position.z = fmax((toolpath.end() - 1)->position.z,
				selected.GetSizeZ() + freeHeight);
	}else{
		m.position.z = selected.GetSizeZ() + freeHeight;
	}
//toolpath.push_back(m);

	const Vector3 dirmain = type.GetNormal();
	const Vector3 dirextra(-dirmain.y, dirmain.x, 0);

// Assign parents
	for(size_t q = 0; q < ptp.size(); ++q){
		if(ptp[q].p.empty()){
			ptp[q].inserted = true;
			continue;
		}
		ptp[q].inserted = false;
		const CNCPosition p0 = *(ptp[q].p.begin());
		const CNCPosition p1 = *(ptp[q].p.end() - 1);
		const Vector3 a0(p0.position.x, p0.position.y, 0);
		const Vector3 a1(p1.position.x, p1.position.y, 0);
		const double width = (a1 - a0).Dot(dirextra);
		for(size_t r = q; r-- > 0;){
			if(ptp[r].p.empty()) continue;
			const CNCPosition p0 = *(ptp[r].p.begin());
			const CNCPosition p1 = *(ptp[r].p.end() - 1);
			const Vector3 b0(p0.position.x, p0.position.y, 0);
			const Vector3 b1(p1.position.x, p1.position.y, 0);
			const double v0 = (b0 - a0).Dot(dirmain);
			const double v1 = (b1 - a0).Dot(dirmain);
			const double v = (v0 + v1) / 2.0;
			if(v < -pathDistance || v > -FLT_EPSILON) continue;
			const double w0 = (b0 - a0).Dot(dirextra);
			const double w1 = (b1 - a0).Dot(dirextra);
			if(w1 < 0 || w0 > width) continue;
			ptp[q].parents.push_back(r);
		}
	}

	bool allowReversing = true;
	// Connect the path segments
	do{
		double dopt = FLT_MAX;
		int nopt = -1;
		bool forward = true;
		for(size_t n = 0; n < ptp.size(); n++){
			if(ptp[n].inserted) continue;
			bool ok = true;
			for(size_t u = 0; u < ptp[n].parents.size(); u++){
				if(!ptp[ptp[n].parents[u]].inserted) ok = false;
			}
			if(!ok) continue;
			assert(!ptp[n].p.empty());
			const CNCPosition p0 = *(ptp[n].p.begin());

			const double d = (m.position.x - p0.position.x)
					* (m.position.x - p0.position.x)
					+ (m.position.y - p0.position.y)
							* (m.position.y - p0.position.y)
					+ (m.position.z - p0.position.z)
							* (m.position.z - p0.position.z);
			if(d < dopt){
				forward = true;
				dopt = d;
				nopt = n;
			}
			if(allowReversing){
				const CNCPosition p1 = *(ptp[n].p.end() - 1);
				const double d = (m.position.x - p1.position.x)
						* (m.position.x - p1.position.x)
						+ (m.position.y - p1.position.y)
								* (m.position.y - p1.position.y)
						+ (m.position.z - p1.position.z)
								* (m.position.z - p1.position.z);
				if(d < dopt){
					forward = false;
					dopt = d;
					nopt = n;
				}
			}
		}
		if(nopt < 0) break;
		CNCPosition mlast = m;
		if(forward)
			m = *(ptp[nopt].p.begin());
		else
			m = *(ptp[nopt].p.end() - 1);

		{
			double px0 = round(
					(mlast.position.x - selected.GetResolutionX() / 2)
							/ selected.GetResolutionX());
			double py0 = round(
					(mlast.position.y - selected.GetResolutionY() / 2)
							/ selected.GetResolutionY());
			double px1 = round(
					(m.position.x - selected.GetResolutionX() / 2)
							/ selected.GetResolutionX());
			double py1 = round(
					(m.position.y - selected.GetResolutionY() / 2)
							/ selected.GetResolutionY());

			const double d = fmax(fabs(px0 - px1), fabs(py0 - py1));
			const int N = round(d);
			Vector3 delta = (m.position - mlast.position) / fmax(1.0, d);
			CNCPosition p = mlast;

			const double dd = fmax(fabs(px0 - px1) * selected.GetResolutionX(),
					fabs(py0 - py1) * selected.GetResolutionY());

			if(fabs(m.position.z - mlast.position.z) <= maxStepUp
					&& dd < pathDistance){
				std::vector <CNCPosition> tp1;
				double cost = 0.0;
				for(size_t u = 0; u <= N; u++){
					const double h = selected.GetLevel(p.position.x,
							p.position.y);
					if(h > -FLT_EPSILON){
						cost += fmax(h - p.position.z, 0);
						CNCPosition temp = p;
						temp.position.z = fmax(temp.position.z, h); //TODO This is following the surface exactly, but should skip gaps.
						tp1.push_back(temp);
					}
					p.position += delta;
				}
				toolpath.insert(toolpath.end(), tp1.begin(), tp1.end());

			}else{
				if(mlast.position.z
						< selected.GetSizeZ() + freeHeight - FLT_EPSILON){
					mlast.position.z = selected.GetSizeZ() + freeHeight;
					mlast.Rapid();
					toolpath.push_back(mlast);
				}
				mlast = m;
				mlast.position.z = selected.GetSizeZ() + freeHeight;
				mlast.Rapid();
				toolpath.push_back(mlast);
			}
		}

//		m.position.Z = fmax(m.position.Z, selected.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.push_back(m);

		if(forward){
			for(size_t m = 0; m < ptp[nopt].p.size(); m++){
				toolpath.push_back(ptp[nopt].p[m]);
			}
		}else{
			for(size_t m = ptp[nopt].p.size(); m-- > 0;){
				toolpath.push_back(ptp[nopt].p[m]);
			}
		}
		m = *(toolpath.end() - 1);
//		m.position.Z = fmax(m.position.Z, selected.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.push_back(m);

		ptp[nopt].inserted = true;
	}while(true);

// Move out of workpiece
	if((toolpath.size() > 0)
			&& ((toolpath.end() - 1)->position.z
					< (selected.GetSizeZ() + freeHeight - FLT_EPSILON))){
		CNCPosition p1 = *(toolpath.end() - 1);
		CNCPosition m(p1.position.x, p1.position.y,
				selected.GetSizeZ() + freeHeight);
		//Note: Rotations are kept at zero for the starting position
		m.Rapid();
		toolpath.push_back(m);
	}

}

