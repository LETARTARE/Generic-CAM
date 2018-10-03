///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorPositioningDrills.cpp
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

#include "GeneratorPositioningDrills.h"

#include <stddef.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/sizer.h>

#include "../../gui/DisplaySettings.h"
#include "../../gui/Unit.h"
#include "../FlipDrillPattern.h"
#include "../Project.h"

GeneratorPositioningDrills::GeneratorPositioningDrills()
{
	
	selectedPattern = -1;
	diameter = 0.0;
	depth = 0.0;

}

void GeneratorPositioningDrills::CopyParameterFrom(const Generator * other)
{
	Generator::CopyParameterFrom(other);

	const GeneratorPositioningDrills * temp =
			dynamic_cast <const GeneratorPositioningDrills*>(other);

	selectedPattern = temp->selectedPattern;
	diameter = temp->diameter;
	depth = temp->depth;

	wxLogMessage(wxString::Format(_T("CopyFrom: %i"), selectedPattern));
}

GeneratorPositioningDrills::~GeneratorPositioningDrills()
{
}

wxString GeneratorPositioningDrills::GetName(void) const
{
	return _("Positioning Drillings");
}

void GeneratorPositioningDrills::AddToPanel(wxPanel* panel,
		DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxArrayString m_choiceSetupsChoices;
	m_choiceSetups = new wxChoice( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSetupsChoices, 0 );
	m_choiceSetups->SetSelection( 0 );
	bSizer->Add( m_choiceSetups, 0, wxALL|wxEXPAND, 5 );

	wxString m_radioBoxChoices[] = { wxT("Mirrored along X-axis"), wxT("Mirrored along Y-axis (default)"), wxT("Normal (for Machinebed preparation)") };
	int m_radioBoxNChoices = sizeof( m_radioBoxChoices ) / sizeof( wxString );
	m_radioBox = new wxRadioBox( panel, wxID_ANY, wxT("Change drill positioning"), wxDefaultPosition, wxDefaultSize, m_radioBoxNChoices, m_radioBoxChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBox->SetSelection( 0 );
	bSizer->Add( m_radioBox, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer->AddGrowableCol( 1 );
	fgSizer->SetFlexibleDirection( wxBOTH );
	fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticTextHoleDiameter = new wxStaticText( panel, wxID_ANY, wxT("Hole diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHoleDiameter->Wrap( -1 );
	fgSizer->Add( m_staticTextHoleDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlHoleDiameter = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer->Add( m_textCtrlHoleDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	m_staticTextUnitDiameter = new wxStaticText( panel, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	fgSizer->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticTextHoleDepth = new wxStaticText( panel, wxID_ANY, wxT("Depth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHoleDepth->Wrap( -1 );
	fgSizer->Add( m_staticTextHoleDepth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlHoleDepth = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer->Add( m_textCtrlHoleDepth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	m_staticTextUnitDepth = new wxStaticText( panel, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDepth->Wrap( -1 );
	fgSizer->Add( m_staticTextUnitDepth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer->Add( fgSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer->Add( 0, 0, 1, 0, 5 );

	m_staticTextInfo = new wxStaticText( panel, wxID_ANY, wxT("Please note, that the measurements of the workpiece have to be exact for this to work correctly. (At least in the direction You are flipping the workpiece in. The height has to be correct as well.)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextInfo->Wrap( 400 );
	bSizer->Add( m_staticTextInfo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer->Add( 0, 0, 1, 0, 5 );

	panel->Layout();
	bSizer->Fit(panel);

	m_choiceSetups->Append(_T(""));
	m_choiceSetups->SetSelection(0);
}

void GeneratorPositioningDrills::TransferDataToPanel(void) const
{
	m_staticTextUnitDepth->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnitDiameter->SetLabel(settings->SmallDistance.GetOtherName());

	m_textCtrlHoleDepth->SetValue(settings->SmallDistance.TextFromSI(depth));
	m_textCtrlHoleDiameter->SetValue(
			settings->SmallDistance.TextFromSI(diameter));

	m_choiceSetups->Clear();
	m_choiceSetups->Append(_T(""));

	//TODO: the info from the Run about the available pattern is needed here.
//	for(size_t n = 0; n < project->pattern.GetCount(); n++){
//		m_choiceSetups->Append(project->pattern[n].name);
//	}
	m_choiceSetups->SetSelection(selectedPattern + 1);
//	wxLogMessage(
//			_T("to Window ")
//					+ wxString::Format(_T("%i / %i"), selectedPattern,
//							project->pattern.GetCount()));
}

void GeneratorPositioningDrills::TransferDataFromPanel(void)
{
	depth = settings->SmallDistance.SIFromString(
			m_textCtrlHoleDepth->GetValue());
	diameter = settings->SmallDistance.SIFromString(
			m_textCtrlHoleDiameter->GetValue());
	selectedPattern = m_choiceSetups->GetSelection() - 1;
	wxLogMessage(
	_T("from Window ") + wxString::Format(_T("%i"), selectedPattern));
}

void GeneratorPositioningDrills::GenerateToolpath(void)
{
	printf("PositioningDrills called.\n");
	errorOccured = false;
	toolpathGenerated = true;
}

//void Project::InsertDrillGrid(Run &run, double sizex, double sizey,
//		bool flipped)
//{
//	Target temp;
//	TargetPlacement tempPlace;
//	temp.SetupDrill(toolbox.tools[0], 0.0082, 0.012);
//	targets.Add(temp);
//	tempPlace.outLine = temp.outLine;
//	tempPlace.isMovable = false;
//	tempPlace.targetNumber = targets.GetCount() - 1;
//	tempPlace.matrix.SetIdentity();
//	tempPlace.matrix.TranslateGlobal(offsetX, middleY - sizey / 2,
//			run.stockMaterial.sz);
//
//	run.placements.Add(tempPlace);
//	tempPlace.matrix.SetIdentity();
//	tempPlace.matrix.TranslateGlobal(offsetX, middleY + sizey / 2,
//			run.stockMaterial.sz);
//	run.placements.Add(tempPlace);
//	tempPlace.matrix.SetIdentity();
//	if(flipped){
//		tempPlace.matrix.TranslateGlobal(offsetX + sizex, middleY - sizey / 2,
//				run.stockMaterial.sz);
//	}else{
//		tempPlace.matrix.TranslateGlobal(offsetX + sizex, middleY + sizey / 2,
//				run.stockMaterial.sz);
//	}
//	run.placements.Add(tempPlace);
//}

