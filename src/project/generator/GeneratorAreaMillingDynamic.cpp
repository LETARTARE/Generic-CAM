///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorAreaMillingDynamic.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.08.2011
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

#include "GeneratorAreaMillingDynamic.h"

#include "../../gui/CollectionUnits.h"
#include "../Project.h"
#include "CNCPosition.h"

#include <float.h>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <wx/sizer.h>

GeneratorAreaMillingDynamic::GeneratorAreaMillingDynamic(size_t ID):GeneratorDexel(ID)
{
	freeHeightAboveMaterial = 0.002;
	maxSingleStep = 0.020;
	raiseStep = 0.005;
	dropStep = 0.008;

	toolDiameter = 0.0;
}

GeneratorAreaMillingDynamic::~GeneratorAreaMillingDynamic()
{
}

void GeneratorAreaMillingDynamic::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorAreaMillingDynamic * temp =
			dynamic_cast <const GeneratorAreaMillingDynamic*>(other);

	maxSingleStep = temp->maxSingleStep;
	raiseStep = temp->raiseStep;
	dropStep = temp->dropStep;
}

wxString GeneratorAreaMillingDynamic::GetTypeName(void) const
{
	return _("Area Milling - Dynamic (using Dexel)");
}

wxSizer * GeneratorAreaMillingDynamic::AddToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer(3, 3, 0, 0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText10 = new wxStaticText(panel, wxID_ANY, _("Max. single step:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	fgSizer->Add(m_staticText10, 0,
			wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);

	m_textCtrlMaxSingleStep = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, 0);
	fgSizer->Add(m_textCtrlMaxSingleStep, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticTextUnit1 = new wxStaticText(panel, wxID_ANY, _("mm"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnit1->Wrap(-1);
	fgSizer->Add(m_staticTextUnit1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_staticText12 = new wxStaticText(panel, wxID_ANY, _("Raise step:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticText12->Wrap(-1);
	fgSizer->Add(m_staticText12, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 5);

	m_textCtrlRaiseStep = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, 0);
	fgSizer->Add(m_textCtrlRaiseStep, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticTextUnit2 = new wxStaticText(panel, wxID_ANY, _("mm"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnit2->Wrap(-1);
	fgSizer->Add(m_staticTextUnit2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_staticText14 = new wxStaticText(panel, wxID_ANY, _("Drop step:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticText14->Wrap(-1);
	fgSizer->Add(m_staticText14, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 5);

	m_textCtrlDropStep = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, 0);
	fgSizer->Add(m_textCtrlDropStep, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticTextUnit3 = new wxStaticText(panel, wxID_ANY, _("mm"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnit3->Wrap(-1);
	fgSizer->Add(m_staticTextUnit3, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer11->Add(fgSizer, 0, 0, 5);

	bSizer->Add(bSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	return bSizer;
}

void GeneratorAreaMillingDynamic::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	m_staticTextUnit1->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnit2->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnit3->SetLabel(settings->SmallDistance.GetOtherName());

	m_textCtrlMaxSingleStep->SetValue(
			settings->SmallDistance.TextFromSI(maxSingleStep));
	m_textCtrlRaiseStep->SetValue(
			settings->SmallDistance.TextFromSI(raiseStep));
	m_textCtrlDropStep->SetValue(settings->SmallDistance.TextFromSI(dropStep));
}

void GeneratorAreaMillingDynamic::TransferDataFromPanel(
		CollectionUnits* settings)
{
	maxSingleStep = settings->SmallDistance.SIFromString(
			m_textCtrlMaxSingleStep->GetValue());
	raiseStep = settings->SmallDistance.SIFromString(
			m_textCtrlRaiseStep->GetValue());
	dropStep = settings->SmallDistance.SIFromString(
			m_textCtrlDropStep->GetValue());
}

std::vector <CNCPosition> GeneratorAreaMillingDynamic::GenerateDrill(double x,
		double y, double diameter, double depth)
{
	std::vector <CNCPosition> temp;
	CNCPosition mp;

	const double r = (diameter - toolDiameter) / 2.0;

	mp.FeedSpeed();
	mp.position.Set(x, y, 0.0);
	temp.push_back(mp);

	if(r <= 0.001){
		double d = 0.0;
		while(d > dropStep - depth){
			d -= dropStep;

			mp.position.z = d;
			temp.push_back(mp);
			mp.position.z = 0.0;
			temp.push_back(mp);
		}
		mp.position.z = -depth;
		mp.position.x += r;
		temp.push_back(mp);
//		mp.I = -r;
		temp.push_back(mp);
//		mp.I = 0.0;
		mp.position.x = x;
		temp.push_back(mp);
	}else{
		mp.position.x += r;
		temp.push_back(mp);
//		mp.ArcCCW();
//		mp.I = -r;
		while(mp.position.z > dropStep - depth){
			mp.position.z -= dropStep;
			temp.push_back(mp);
		}
		mp.position.z = -depth;
		temp.push_back(mp);
		temp.push_back(mp);
		mp.Rapid();
//		mp.I = 0.0;
		mp.position.x = x;
		temp.push_back(mp);
	}
	return temp;
}

std::vector <CNCPosition> GeneratorAreaMillingDynamic::GenerateSpiral(double x,
		double y, double radius)
{
	std::vector <CNCPosition> temp;
	CNCPosition mp;

	const double rinc = toolDiameter / 2.0;

	const size_t Npt = 40;
	const size_t Nt = floor((double) Npt * radius / rinc);
	size_t n;

	throw("Is this used?");

	mp.position.Set(x, y, 0.0);
	mp.FeedSpeed();
	temp.push_back(mp);

//	mp.ArcCCW();
	for(n = 1; n <= Nt; n++){
		const double r = radius / (double) Nt * (double) n;
//		mp.R = r;
		mp.position.x = x + r * cos(2 * M_PI / (double) Npt * (double) n);
		mp.position.y = y + r * sin(2 * M_PI / (double) Npt * (double) n);
		temp.push_back(mp);
	}
	return temp;
}

bool GeneratorAreaMillingDynamic::IsDirectlyReachable(DexelTarget &target,
		double sx, double sy, double sz, double x, double y, double z)
{
	double dx = x - sx;
	double dy = y - sy;
	double dz = z - sz;
	double d = sqrt(dx * dx + dy * dy);
	double rx = target.GetResolutionX();
	double ry = target.GetResolutionY();
	size_t n = round(d / (rx + ry) * 2);
	double px, py, pz, hz;
	size_t i;
	for(i = 0; i < n; i++){
		px = sx + dx / (double) n * (double) i;
		py = sy + dy / (double) n * (double) i;
		pz = sz + dz / (double) n * (double) i;
		hz = target.GetLevel(px, py);
		if(hz > pz) return false;
	}
	return true;
}

bool GeneratorAreaMillingDynamic::operator ==(const Generator& b) const
{
	const GeneratorAreaMillingDynamic * temp =
			dynamic_cast <const GeneratorAreaMillingDynamic*>(&b);
	std::cout << "GeneratorAreaMillingDynamic::operator ==\n";
	if(!(this->Generator::operator ==(b))) return false;
	if(fabs(this->toolDiameter - temp->toolDiameter) > FLT_EPSILON) return false;
	if(fabs(
			this->freeHeightAboveMaterial
					- temp->freeHeightAboveMaterial)>FLT_EPSILON) return false;
	if(fabs(this->maxSingleStep - temp->maxSingleStep) > FLT_EPSILON) return false;
	if(fabs(this->raiseStep - temp->raiseStep) > FLT_EPSILON) return false;
	if(fabs(this->dropStep - temp->dropStep) > FLT_EPSILON) return false;
	return true;
}

std::vector <CNCPosition> GeneratorAreaMillingDynamic::MoveSafely(
		DexelTarget &target, double sx, double sy, double sz, double x,
		double y, double z)
{
	std::vector <CNCPosition> tp;
	CNCPosition mp;

	bool hasToDrop = false;

	size_t i;
	double px, py;
	double hz;

	double rx = target.GetResolutionX();
	double ry = target.GetResolutionY();
	double r = (rx + ry) / 2;

	mp.position.Set(sx, sy, sz);
	mp.Rapid();

	double dx = x - sx;
	double dy = y - sy;
	double dz = z - sz;

	double d = sqrt(dx * dx + dy * dy);
	double dt;

	if(dz >= 0){
		mp.position.z = z + 0.001;
		tp.push_back(mp);
	}

	const size_t n = round(d / r);
	bool isCutting = false;
	for(i = 1; i < n; i++){

		px = sx + dx / (double) n * (double) i;
		py = sy + dy / (double) n * (double) i;
		hz = target.GetLevel(px, py);

		dt = d * (1 - (double) i / (double) n);

		if(hz > mp.position.z && !isCutting){
			mp.position.x = sx + dx / (double) (n - 1) * (double) i;
			mp.position.y = sy + dy / (double) (n - 1) * (double) i;
			mp.position.z = target.GetSizeZ() + freeHeightAboveMaterial;
			tp.push_back(mp);
			hasToDrop = true;
		}

		if(dt <= toolDiameter / 2 && !isCutting && !hasToDrop){
			mp.position.x = sx + dx / (double) (n - 1) * (double) i;
			mp.position.y = sy + dy / (double) (n - 1) * (double) i;
			tp.push_back(mp);
			mp.position.x = px;
			mp.position.y = py;
			isCutting = true;
			mp.FeedSpeed();
			tp.push_back(mp);
		}
	}
	mp.FeedSpeed();
	mp.position.x = x;
	mp.position.y = y;
	if(!hasToDrop) mp.position.z = z;
	tp.push_back(mp);

	if(hasToDrop){
		double d = target.GetSizeZ();
		while(d > dropStep + z){
			mp.FeedSpeed();
			d -= dropStep;
			mp.position.z = d;
			tp.push_back(mp);
			mp.Rapid();
			mp.position.z = target.GetSizeZ();
		}
		mp.FeedSpeed();
		mp.position.z = z;
		tp.push_back(mp);
	}
	return tp;
}
/// LT
/*
void GeneratorAreaMillingDynamic::GenerateToolpath(const Run &run,
		const std::vector <Object> &objects, const Tool &tool,
		const DexelTarget &base)
*/
void GeneratorAreaMillingDynamic::GenerateToolpath(		const Run &run,
			const std::list <Object> &objects, const Tool &tool,
			const DexelTarget &base)
{
	output.Empty();

	GeneratorDexel::PrepareTargets(run, objects, base);

	std::vector <CNCPosition> tp;
	CNCPosition mp;

	toolDiameter = tool.GetMaxDiameter();

	DexelTarget toolShape;
	toolShape.SetupTool(tool, target.GetResolutionX(), target.GetResolutionY());
//	toolShape.NegateZ();
	DexelTarget temp = target;
	DexelTarget temptop;

	temp.FoldRaise(toolShape);
	temp.Limit();

	temptop = temp;
	temptop.InvertTop();

	const double rx = target.GetResolutionX();
	const double ry = target.GetResolutionY();
	const double rx2 = rx / 2;
	const double ry2 = ry / 2;

	Polygon25 poly;

	// Begin drop&raise cycle

	double dmin = temptop.GetMinLevelD();
	double level = dmin + FLT_EPSILON;

	temptop.GenerateDistanceMap(level, true);

//TODO Removed other side from flipped designs?
//	ArrayOfMachinePosition mpa = target.toolpathFlipped.positions;
//	if(!mpa.IsEmpty()){
//		for(size_t i = 0; i < mpa.GetCount(); i++){
//			double px = mpa[i].X;
//			double py = target.GetSizeY() - mpa[i].Y;
//			double pz = target.GetSizeZ() - mpa[i].Z;
//			if(pz > level) temptop.FoldLowerDistance(round((px - rx2) / rx),
//					round((py - ry2) / ry), toolShape);
//		}
//	}

	int cx, cy;
	double d = temptop.GetMaxLevelAD(cx, cy);

	if(tp.empty()){ // New toolpath starting position
		mp.position.x = rx * cx + rx2;
		mp.position.y = ry * cy + ry2;
		mp.position.z = temp.GetSizeZ() + freeHeightAboveMaterial;
		mp.Rapid();
		tp.push_back(mp);
	}

	// Remove material at drillhole
	//temptop.FoldLowerDistance(cx, cy, toolShape);

	do{
		// Scrubb area
		while(temptop.FindNextDistanceBDAU(cx, cy)){
			temptop.FindStartCutting(cx, cy);

			//		if(!IsDirectlyReachable(temp, mp.X, mp.Y, mp.Z, cx * rx
			//				+ rx2, cy * ry + ry2, level)) break;

			poly = temptop.FindCut(cx, cy);
			temp.PolygonDropOntoTarget(poly, level);

			if(mp.position.z > level){
				// Drill down
				d = target.GetSizeZ();
				while(d > level + dropStep){
					mp.FeedSpeed();
					d -= dropStep;
					mp.position.z = d;
					tp.push_back(mp);
					mp.Rapid();
					mp.position.z = target.GetSizeZ();
				}
				mp.FeedSpeed();
				mp.position.z = level;
				tp.push_back(mp);
			}
			//if(poly.elements.GetCount() > 3){
			for(size_t i = 0; i < poly.Size(); i++){

				temptop.FoldLowerDistance(round((poly[i].x - rx2) / rx),
						round((poly[i].y - ry2) / ry), toolShape);

				if(i == 0){
					std::vector <CNCPosition> tempp = MoveSafely(temp,
							mp.position.x, mp.position.y, mp.position.z,
							poly[i].x, poly[i].y, poly[i].z);
					tp.insert(tp.end(), tempp.begin(), tempp.end());
				}
				mp.position.x = poly[i].x;
				mp.position.y = poly[i].y;
				mp.position.z = poly[i].z;
				mp.FeedSpeed();
				tp.push_back(mp);
				//}
			}
		}

		if(level < temptop.GetSizeZ() - 0.0001){
			level += raiseStep;
			if(level >= temptop.GetSizeZ() - 0.0001) level = temptop.GetSizeZ()
					- 0.00005;
		}else{
			level = temptop.GetSizeZ() + 0.0001;
		}

		mp.position.z = level;
		mp.Rapid();
		tp.push_back(mp);

		if(level < temptop.GetSizeZ()){
			temptop.RaiseDistanceMap(level, true);

			//TODO: Removed other side from flipped designs?
//			if(!mpa.IsEmpty()){
//				for(size_t i = 0; i < mpa.GetCount(); i++){
//					px = mpa[i].X;
//					py = target.GetSizeY() - mpa[i].Y;
//					pz = target.GetSizeZ() - mpa[i].Z;
//					if(pz > level) temptop.FoldLowerDistance(px, py, discTool);
//				}
//			}
		}

	}while(level < temptop.GetSizeZ());

	// Spiral out
	//temptp = GenerateSpiral(rx * cx, ry * cy, d / 2);

	//	// Drop onto geometry
	//	size_t i;
	//	for(i = 0; i < temptp.positions.GetCount(); i++)
	//		temp.VectorDrop(temptp.positions[i].X, temptp.positions[i].Y,
	//				temptp.positions[i].Z, dmin);
	//
	//	tp += temptp;

	// Move out of material
	mp.position.z = temp.GetSizeZ() + freeHeightAboveMaterial;
	mp.Rapid();
	tp.push_back(mp);

	//target = temptop;

	//tp.CleanPath(0.0003);

//	for(size_t i = 0; i < tp.positions.GetCount(); i++)
//		tp.positions[i].position.Z -= temp.GetSizeZ();
//	AffineTransformMatrix shiftback;
//	shiftback.TranslateGlobal(0, 0, 0);
//	tp.ApplyTransformation(shiftback);

	toolpath = tp;
	return;
	//
	//	double level = temp.GetSizeZ() - 0.0005;
	//
	//
	//	// Starting point
	//	//
	//	//	tp.push_back(m);
	//
	//	// Position at start (! not a toolpath position)
	//	m.position.X = 0.0;
	//	m.position.Y = 0.0;
	//	m.position.Z = temp.GetSizeZ() + freeHeightAboveMaterial;
	//	m.isCutting = false;
	//
	//	ArrayOfPolygon25 pgs;
	//	Polygon25 pg;
	//
	//	AffineTransformMatrix tm;
	//	tm.TranslateGlobal(0.0, 0.0, -0.0001);
	//
	//
	//	// Move tool out of material
	//	m.position.Z = temp.GetSizeZ() + freeHeightAboveMaterial;
	//	m.isCutting = false;
	//	tp.push_back(m);
	//
	//
	//	// Shift toolpath down to align 0 with top-of-stock
	//	for(size_t i = 0; i < tp.positions.GetCount(); i++){
	//		tp.positions[i].position.Z -= temp.GetSizeZ();
	//	}
	//	tp.matrix.TranslateGlobal(0, 0, temp.GetSizeZ());
	//
	//
	//	//	t.InitImprinting();
	//	//	t.matrix.SetIdentity();
	//	//t.matrix.TranslateGlobal(t.GetSizeX(), 0, 0);
	//	//targets.Add(t);
	//
	//	target.toolpath = tp;
}
