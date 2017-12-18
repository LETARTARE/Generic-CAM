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

GeneratorAreaGridDexel::GeneratorAreaGridDexel()
{
	overlap = 0.1;
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
	fgSizerDirection->Add(m_bitmapXthenY, 0,
			wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_radioBtnYthenX = new wxRadioButton(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxT("Y first then X"), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_radioBtnYthenX, 0, wxALL | wxALIGN_CENTER_VERTICAL,
			5);

	m_bitmapYthenX = new wxStaticBitmap(sbSizerDirection->GetStaticBox(),
			wxID_ANY, wxBitmap(ythenx_xpm), wxDefaultPosition, wxDefaultSize,
			0);
	fgSizerDirection->Add(m_bitmapYthenX, 0, wxALL, 5);

	sbSizerDirection->Add(fgSizerDirection, 1, wxEXPAND, 5);

	bSizerBorder->Add(sbSizerDirection, 1, wxEXPAND | wxBOTTOM, 5);

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

	fgSizerDistance->Add(m_textCtrlOverlap, 0,
			wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL
					| wxEXPAND, 5);

	m_staticTextUnitOverlap = new wxStaticText(panel, wxID_ANY, wxT("%"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextUnitOverlap->Wrap(-1);
	fgSizerDistance->Add(m_staticTextUnitOverlap, 0,
			wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizerDistance->Add(fgSizerDistance, 1,
			wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	bSizerBorder->Add(bSizerDistance, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL,
			5);

	wxStaticBoxSizer* sbSizerRotations;
	sbSizerRotations = new wxStaticBoxSizer(
			new wxStaticBox(panel, wxID_ANY, wxT("Rotations")), wxVERTICAL);

	m_checkBoxA = new wxCheckBox(sbSizerRotations->GetStaticBox(), wxID_ANY,
			wxT("Generate A rotations"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBoxA->SetToolTip(
			wxT(
					"5-axis milling: Generate rotations around X axis (= A axis)."));

	sbSizerRotations->Add(m_checkBoxA, 0, wxALL, 5);

	m_checkBoxB = new wxCheckBox(sbSizerRotations->GetStaticBox(), wxID_ANY,
			wxT("Generate B rotations"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBoxB->SetToolTip(
			wxT(
					"5-axis milling: Generate rotations around the Y axis (= B axis)."));

	sbSizerRotations->Add(m_checkBoxB, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);

	bSizerBorder->Add(sbSizerRotations, 0,
			wxALIGN_CENTER_HORIZONTAL | wxEXPAND | wxTOP, 5);

	bSizer->Add(bSizerBorder, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	panel->SetSizer(bSizer);
	panel->Layout();
	bSizer->Fit(panel);
}

void GeneratorAreaGridDexel::TransferDataToPanel(void) const
{
	m_staticTextUnitOverlap->SetLabel(settings->Percentage.GetOtherName());
	m_textCtrlOverlap->SetValue(settings->Percentage.TextFromSI(overlap));
	m_radioBtnXthenY->SetValue(type == 0);
	m_radioBtnYthenX->SetValue(type == 1);
	m_checkBoxA->SetValue(generateA);
	m_checkBoxB->SetValue(generateB);
}

void GeneratorAreaGridDexel::TransferDataFromPanel(void)
{
	overlap = settings->Percentage.SIFromString(m_textCtrlOverlap->GetValue());
	if(m_radioBtnXthenY->GetValue()) type = 0;
	if(m_radioBtnYthenX->GetValue()) type = 1;
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

//	DexelTarget surface = target;
	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetResolutionX(),
			target.GetResolutionY());
	toolShape.NegateZ();
	target.FoldRaise(toolShape);
	target.Limit();

//	debug = target;

	toolpath.Clear();

	const double tooldiameter = tool->GetMaxDiameter();
	ProtoToolpath tp;
	GCodeBlock m;
	m.X = 0;
	m.Y = 0;
	m.Z = target.GetSizeZ() + freeHeight;
	m.Rapid();
	toolpath.positions.Add(m);

	{
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

			m.X = ix * target.GetResolutionX() + target.GetResolutionX() / 2;
			m.Y = py0 * target.GetResolutionY() + target.GetResolutionY() / 2;
			m.Rapid();
			toolpath.positions.Add(m);

			for(int iy = py0; iy <= py1; iy++){
				m.X = ix * target.GetResolutionX()
						+ target.GetResolutionX() / 2;
				m.Y = iy * target.GetResolutionY()
						+ target.GetResolutionY() / 2;
				const ImprinterElement e = target.GetElement(m.X, m.Y);

				m.Z = e.up;

				if(generateA && !generateB) m.A = asin(-e.normaly);
				if(!generateA && generateB) m.B = asin(e.normalx);
				if(generateA && generateB){
					m.A = asin(-e.normaly);
					//TODO Checks needed
					m.B = asin(e.normalx / sqrt(1.0 - e.normaly * e.normaly));
				}

				m.FeedSpeed();
				toolpath.positions.Add(m);
			}
			m.Z = target.GetSizeZ() + freeHeight;
			m.Rapid();
			toolpath.positions.Add(m);
		}

	}
	toolpath.FlagAll(true, false, false, generateA | generateB);
}
