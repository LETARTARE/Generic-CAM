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
#include "ProtoToolpath.h"

#include "../../icon/xtheny.xpm"
#include "../../icon/ythenx.xpm"

#include <wx/sizer.h>
#include <float.h>
#include <cmath>

GeneratorAreaGridDexel::GeneratorAreaGridDexel()
{
	overlap = 0.1;
	maxStepUp = 0.01;
	type = 0;
	generateA = false;
	generateB = false;
}

GeneratorAreaGridDexel::~GeneratorAreaGridDexel()
{

}

void GeneratorAreaGridDexel::CopyParameterFrom(const Generator * other)
{
	GeneratorDexel::CopyParameterFrom(other);

	const GeneratorAreaGridDexel * temp =
			dynamic_cast <const GeneratorAreaGridDexel*>(other);

	type = temp->type;
	overlap = temp->overlap;
	generateA = temp->generateA;
	generateB = temp->generateB;
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
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerBorder;
	bSizerBorder = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizerDirection;
	sbSizerDirection = new wxStaticBoxSizer( new wxStaticBox( panel, wxID_ANY, wxT("Direction") ), wxVERTICAL );

	wxFlexGridSizer* fgSizerDirection;
	fgSizerDirection = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerDirection->SetFlexibleDirection( wxBOTH );
	fgSizerDirection->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_radioBtnXthenY = new wxRadioButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("X first then Y"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerDirection->Add( m_radioBtnXthenY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_bitmapXthenY = new wxStaticBitmap( sbSizerDirection->GetStaticBox(), wxID_ANY, wxBitmap( xtheny_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerDirection->Add( m_bitmapXthenY, 0, wxALL, 5 );

	m_radioBtnYthenX = new wxRadioButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("Y first then X"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerDirection->Add( m_radioBtnYthenX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_bitmapYthenX = new wxStaticBitmap( sbSizerDirection->GetStaticBox(), wxID_ANY, wxBitmap( ythenx_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerDirection->Add( m_bitmapYthenX, 0, wxALL, 5 );


	sbSizerDirection->Add( fgSizerDirection, 0, 0, 5 );


	bSizerBorder->Add( sbSizerDirection, 0, wxEXPAND|wxBOTTOM, 5 );

	wxBoxSizer* bSizerDistance;
	bSizerDistance = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* fgSizerDistance;
	fgSizerDistance = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizerDistance->AddGrowableCol( 1 );
	fgSizerDistance->SetFlexibleDirection( wxBOTH );
	fgSizerDistance->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextOverlap = new wxStaticText( panel, wxID_ANY, wxT("Overlap:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOverlap->Wrap( -1 );
	fgSizerDistance->Add( m_staticTextOverlap, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlOverlap = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlOverlap->SetToolTip( wxT("Distance between two rows.") );

	fgSizerDistance->Add( m_textCtrlOverlap, 0, wxALL|wxEXPAND, 5 );

	m_staticTextUnitOverlap = new wxStaticText( panel, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitOverlap->Wrap( -1 );
	fgSizerDistance->Add( m_staticTextUnitOverlap, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerDistance->Add( fgSizerDistance, 1, 0, 5 );


	bSizerBorder->Add( bSizerDistance, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerRotations;
	sbSizerRotations = new wxStaticBoxSizer( new wxStaticBox( panel, wxID_ANY, wxT("Rotations") ), wxVERTICAL );

	m_checkBoxA = new wxCheckBox( sbSizerRotations->GetStaticBox(), wxID_ANY, wxT("Generate A rotations"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxA->SetToolTip( wxT("5-axis milling: Generate rotations around X axis (= A axis).") );

	sbSizerRotations->Add( m_checkBoxA, 0, wxALL, 5 );

	m_checkBoxB = new wxCheckBox( sbSizerRotations->GetStaticBox(), wxID_ANY, wxT("Generate B rotations"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxB->SetToolTip( wxT("5-axis milling: Generate rotations around the Y axis (= B axis).") );

	sbSizerRotations->Add( m_checkBoxB, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	bSizerBorder->Add( sbSizerRotations, 0, wxEXPAND|wxTOP, 5 );


	bSizer->Add( bSizerBorder, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	panel->SetSizer(bSizer);
	panel->Layout();
	bSizer->Fit(panel);
}

void GeneratorAreaGridDexel::TransferDataToPanel(void) const
{
	m_staticTextUnitOverlap->SetLabel(settings->Percentage.GetOtherName());
	m_textCtrlOverlap->SetValue(settings->Percentage.TextFromSI(overlap));
	m_radioBtnXthenY->SetValue(type.direction == 0);
	m_radioBtnYthenX->SetValue(type.direction == 1);
	m_checkBoxA->SetValue(generateA);
	m_checkBoxB->SetValue(generateB);
}

void GeneratorAreaGridDexel::TransferDataFromPanel(void)
{
	overlap = settings->Percentage.SIFromString(m_textCtrlOverlap->GetValue());
	if(m_radioBtnXthenY->GetValue()) type.direction = 0;
	if(m_radioBtnYthenX->GetValue()) type.direction = 1;
	generateA = m_checkBoxA->GetValue();
	generateB = m_checkBoxB->GetValue();
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
	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY(),
			false);
	toolShape.NegateZ();

	start.FoldRaise(toolShape);
	start.Limit();
	target.FoldRaise(toolShape);
	target.Limit();
//	debug = target;
	type.resolutionX = target.GetResolutionX();
	type.resolutionY = target.GetResolutionY();
	type.offsetX = target.GetResolutionX() / 2;
	type.offsetY = target.GetResolutionY() / 2;

	toolpath.Clear();

	const double tooldiameter = tool->GetMaxDiameter();
	ArrayOfProtoToolpath aptp;
	ProtoToolpath ptp;
	const double cutdepth = tool->GetCuttingDepth();

	const int N = ceil((area.zmax - area.zmin) / cutdepth);

//	debug = start;

	for(int n = 1; n <= N; n++){
		const double level = fmax(area.zmax - n * cutdepth, area.zmin);

		aptp.Clear();
		for(double x = area.xmin + tooldiameter / 2;
				x < area.xmax - tooldiameter / 2;
				x += tooldiameter * (1 - overlap)){

			const int ix = round(
					(x - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			if(ix < 0 || ix >= target.GetCountX()) continue;
			int py0 = round(
					(area.ymin - target.GetResolutionY() / 2)
							/ target.GetResolutionY());
			int py1 = round(
					(area.ymax - target.GetResolutionY() / 2)
							/ target.GetResolutionY());
			if(py0 < 0) py0 = 0;
			if(py1 >= target.GetCountY()) py1 = target.GetCountY() - 1;
			if(py1 < py0) continue;

			ptp.Clear();
			GCodeBlock m;
			for(int iy = py0; iy <= py1; iy++){

				m.X = ix * target.GetResolutionX()
						+ target.GetResolutionX() / 2;
				m.Y = iy * target.GetResolutionY()
						+ target.GetResolutionY() / 2;
				const ImprinterElement e = target.GetElement(m.X, m.Y);
				const ImprinterElement s = start.GetElement(m.X, m.Y);

				if(generateA && !generateB) m.A = asin(-e.normaly);
				if(!generateA && generateB) m.B = asin(e.normalx);
				if(generateA && generateB){
					m.A = asin(-e.normaly);
					//TODO Check needed for e.normaly <= 1.0
					m.B = asin(e.normalx / sqrt(1.0 - e.normaly * e.normaly));
				}
				m.FeedSpeed();

				m.Z = fmax(e.up, level);

				if(m.Z < s.up - FLT_EPSILON){
					start.SetLevel(m.X, m.Y, m.Z);
					if(!ptp.IsEmpty()
							&& fabs(ptp.positions.Last().Z - m.Z) > maxStepUp){
						aptp.Add(ptp);
						ptp.Clear();
					}
					ptp.positions.Add(m);
				}else{
					aptp.Add(ptp);
					ptp.Clear();
				}
			}
			if(!ptp.IsEmpty()) aptp.Add(ptp);
		}
		CollectToolpaths(aptp, 3 * tooldiameter);
	}
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
		toolpath.FlagAll(true, false, false, generateA | generateB);
	}
}

void GeneratorAreaGridDexel::CollectToolpaths(ArrayOfProtoToolpath &ptp,
		const double pathDistance)
{
	if(ptp.GetCount() == 0) return;

	GCodeBlock m;
	if(!toolpath.IsEmpty()){
		m.X = toolpath.positions.Last().X;
		m.Y = toolpath.positions.Last().Y;
		m.Z = fmax(toolpath.positions.Last().Z, target.GetSizeZ() + freeHeight);
	}else{
		m.Z = target.GetSizeZ() + freeHeight;
	}
//toolpath.positions.Add(m);

	const Vector3 dirmain = type.GetNormal();
	const Vector3 dirextra(-dirmain.y, dirmain.x, 0);

	// Assign parents
	ptp[0].inserted = false;
	for(size_t q = 0; q < ptp.GetCount(); q++){
		if(ptp[q].IsEmpty()){
			ptp[q].inserted = true;
			continue;
		}
		ptp[q].inserted = false;
		const Vector3 a0(ptp[q].positions[0].X, ptp[q].positions[0].Y, 0);
		const Vector3 a1(ptp[q].positions.Last().X, ptp[q].positions.Last().Y,
				0);
		const double width = (a1 - a0).Dot(dirextra);
		for(size_t r = q; r-- > 0;){
			if(ptp[r].IsEmpty()) continue;
			const Vector3 b0(ptp[r].positions[0].X, ptp[r].positions[0].Y, 0);
			const Vector3 b1(ptp[r].positions.Last().X,
					ptp[r].positions.Last().Y, 0);
			const double v0 = (b0 - a0).Dot(dirmain);
			const double v1 = (b1 - a0).Dot(dirmain);
			const double v = (v0 + v1) / 2.0;
			if(v < -pathDistance || v > -FLT_EPSILON) continue;
			const double w0 = (b0 - a0).Dot(dirextra);
			const double w1 = (b1 - a0).Dot(dirextra);
			if(w1 < 0 || w0 > width) continue;
			ptp[q].parents.Add(r);
		}
	}

	bool allowReversing = true;
	// Connect the path segments
	do{
		double dopt = FLT_MAX;
		int nopt = -1;
		bool forward = true;
		for(size_t n = 0; n < ptp.GetCount(); n++){
			if(ptp[n].inserted) continue;
			bool ok = true;
			for(size_t u = 0; u < ptp[n].parents.GetCount(); u++){
				if(!ptp[ptp[n].parents[u]].inserted) ok = false;
			}
			if(!ok) continue;
			const double d = (m.X - ptp[n].positions[0].X)
					* (m.X - ptp[n].positions[0].X)
					+ (m.Y - ptp[n].positions[0].Y)
							* (m.Y - ptp[n].positions[0].Y)
					+ (m.Z - ptp[n].positions[0].Z)
							* (m.Z - ptp[n].positions[0].Z);
			if(d < dopt){
				forward = true;
				dopt = d;
				nopt = n;
			}
			if(allowReversing){
				const double d = (m.X - ptp[n].positions.Last().X)
						* (m.X - ptp[n].positions.Last().X)
						+ (m.Y - ptp[n].positions.Last().Y)
								* (m.Y - ptp[n].positions.Last().Y)
						+ (m.Z - ptp[n].positions.Last().Z)
								* (m.Z - ptp[n].positions.Last().Z);
				if(d < dopt){
					forward = false;
					dopt = d;
					nopt = n;
				}
			}
		}
		if(nopt < 0) break;
		GCodeBlock mlast = m;
		if(forward)
			m = ptp[nopt].positions[0];
		else
			m = ptp[nopt].positions.Last();

		{
			double px0 = round(
					(mlast.X - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py0 = round(
					(mlast.Y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());
			double px1 = round(
					(m.X - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py1 = round(
					(m.Y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());

			const double d = fmax(fabs(px0 - px1), fabs(py0 - py1));
			const int N = round(d);
			GCodeBlock delta = (m - mlast) / fmax(1.0, d);
			GCodeBlock p = mlast;

			const double dd = fmax(fabs(px0 - px1) * target.GetResolutionX(),
					fabs(py0 - py1) * target.GetResolutionY());

			if(fabs(m.Z - mlast.Z) <= maxStepUp && dd < pathDistance){
				ToolPath tp1;
				double cost = 0.0;
				for(size_t u = 0; u <= N; u++){
					const double h = target.GetLevel(p.X, p.Y);
					if(h > -FLT_EPSILON){
						cost += fmax(h - p.Z, 0);
						GCodeBlock temp = p;
						temp.Z = fmax(temp.Z, h); //TODO This is following the surface exactly, but should skip gaps.
						tp1.positions.Add(temp);
					}
					p += delta;
				}
				toolpath += tp1;

			}else{
				if(mlast.Z < target.GetSizeZ() + freeHeight - FLT_EPSILON){
					mlast.Z = target.GetSizeZ() + freeHeight;
					mlast.Rapid();
					toolpath.positions.Add(mlast);
				}
				mlast = m;
				mlast.Z = target.GetSizeZ() + freeHeight;
				mlast.Rapid();
				toolpath.positions.Add(mlast);
			}
		}

//		m.Z = fmax(m.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.positions.Add(m);

		if(forward){
			for(size_t m = 0; m < ptp[nopt].positions.GetCount(); m++){
				toolpath.positions.Add(ptp[nopt].positions[m]);
			}
		}else{
			for(size_t m = ptp[nopt].positions.GetCount(); m-- > 0;){
				toolpath.positions.Add(ptp[nopt].positions[m]);
			}
		}
		m = toolpath.positions.Last();
//		m.Z = fmax(m.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.positions.Add(m);

		ptp[nopt].inserted = true;
	}while(true);

// Move out of workpiece
	if((toolpath.GetCount() > 0)
			&& (toolpath.positions.Last().Z
					< (target.GetSizeZ() + freeHeight - FLT_EPSILON))){
		GCodeBlock m;
		//Note: Rotations are kept at zero for the starting position
		m.X = toolpath.positions.Last().X;
		m.Y = toolpath.positions.Last().Y;
		m.Z = target.GetSizeZ() + freeHeight;
		m.Rapid();
		toolpath.positions.Add(m);
	}

}
