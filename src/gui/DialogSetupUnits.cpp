///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupUnits.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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

#include "DialogSetupUnits.h"
#include "IDs.h"

DialogSetupUnits::DialogSetupUnits(wxWindow* parent, DisplaySettings * settings) :
		GUISetupUnits(parent)
{
	this->settings = settings;

	// Setup available units

	factorofLength = new double[7];
	unitsOfLength.Add(_T("um"));
	factorofLength[0] = 1e-6; // m
	unitsOfLength.Add(_T("mil"));
	factorofLength[1] = 25.4e-6; // m
	unitsOfLength.Add(_T("mm"));
	factorofLength[2] = 1e-3; // m
	unitsOfLength.Add(_T("cm"));
	factorofLength[3] = 10e-3; // m
	unitsOfLength.Add(_T("in"));
	factorofLength[4] = 25.4e-3; // m
	unitsOfLength.Add(_T("ft"));
	factorofLength[5] = 12 * 25.4e-3; // m
	unitsOfLength.Add(_T("m"));
	factorofLength[6] = 1; // m

	factorofSpeedLinear = new double[12];
	unitsOfSpeedLinear.Add(_T("mm/s"));
	factorofSpeedLinear[0] = 1e-3; // m/s
	unitsOfSpeedLinear.Add(_T("cm/s"));
	factorofSpeedLinear[1] = 10e-3; // m/s
	unitsOfSpeedLinear.Add(_T("in/s"));
	factorofSpeedLinear[2] = 25.4e-3; // m/s
	unitsOfSpeedLinear.Add(_T("ft/s"));
	factorofSpeedLinear[3] = 12.0 * 25.4e-3; // m/s
	unitsOfSpeedLinear.Add(_T("m/s"));
	factorofSpeedLinear[4] = 1; // m/s
	unitsOfSpeedLinear.Add(_T("mm/min"));
	factorofSpeedLinear[5] = 1.0e-3 / 60; // m/s
	unitsOfSpeedLinear.Add(_T("cm/min"));
	factorofSpeedLinear[6] = 10.0e-3 / 60; // m/s
	unitsOfSpeedLinear.Add(_T("in/min"));
	factorofSpeedLinear[7] = 25.4e-3 / 60; // m/s
	unitsOfSpeedLinear.Add(_T("ft/min"));
	factorofSpeedLinear[8] = 12.0 * 25.4e-3 / 60; // m/s
	unitsOfSpeedLinear.Add(_T("m/min"));
	factorofSpeedLinear[9] = 1.0 / 60; // m/s
	unitsOfSpeedLinear.Add(_T("km/h"));
	factorofSpeedLinear[10] = 1000.0 / 3600; // m/s
	unitsOfSpeedLinear.Add(_T("mph"));
	factorofSpeedLinear[11] = 0.44704; // m/s (per definition)

	factorofSpeedRotational = new double[3];
	unitsOfSpeedRotational.Add(_T("1/s"));
	factorofSpeedRotational[0] = 1; // 1/s
	unitsOfSpeedRotational.Add(_T("1/min"));
	factorofSpeedRotational[1] = 1.0 / 60; // 1/s
	unitsOfSpeedRotational.Add(_T("rpm"));
	factorofSpeedRotational[2] = 1.0 / 60; // 1/s

	factorofTime = new double[4];
	unitsOfTime.Add(_T("s"));
	factorofTime[0] = 1; // s
	unitsOfTime.Add(_T("min"));
	factorofTime[1] = 60; // s
	unitsOfTime.Add(_T("h"));
	factorofTime[2] = 3600; // s
	unitsOfTime.Add(_T("d"));
	factorofTime[3] = 86400; // s

	TransferDataToWindow();
}

DialogSetupUnits::~DialogSetupUnits()
{
	delete[] factorofTime;
	delete[] factorofSpeedRotational;
	delete[] factorofSpeedLinear;
	delete[] factorofLength;
}

void DialogSetupUnits::OnClose(wxCommandEvent& event)
{
	Close();
}

bool DialogSetupUnits::TransferDataToWindow(void)
{
	int i;

	m_choiceUnitLength->Clear();
	m_choiceUnitLength->Append(unitsOfLength);
	i = m_choiceUnitLength->FindString(settings->Distance.GetOtherName());
	if(i == wxNOT_FOUND) i = 6;
	m_choiceUnitLength->SetSelection(i);

	m_choiceUnitSpeedLinear->Clear();
	m_choiceUnitSpeedLinear->Append(unitsOfSpeedLinear);
	i = m_choiceUnitSpeedLinear->FindString(
			settings->LinearSpeed.GetOtherName());
	if(i == wxNOT_FOUND) i = 3;
	m_choiceUnitSpeedLinear->SetSelection(i);

	m_choiceUnitSpeedRotational->Clear();
	m_choiceUnitSpeedRotational->Append(unitsOfSpeedRotational);
	i = m_choiceUnitSpeedRotational->FindString(
			settings->RotationalSpeed.GetOtherName());
	if(i == wxNOT_FOUND) i = 0;
	m_choiceUnitSpeedRotational->SetSelection(i);

	m_choiceUnitTime->Clear();
	m_choiceUnitTime->Append(unitsOfTime);
	i = m_choiceUnitTime->FindString(settings->Time.GetOtherName());
	if(i == wxNOT_FOUND) i = 0;
	m_choiceUnitTime->SetSelection(i);

	return true;
}
bool DialogSetupUnits::TransferDataFromWindow(void)
{
	int i;

	i = m_choiceUnitLength->GetSelection();
	settings->Distance.Setup(_T("m"), unitsOfLength[i], factorofLength[i]);

	i = m_choiceUnitSpeedLinear->GetSelection();
	settings->LinearSpeed.Setup(_T("m/s"), unitsOfSpeedLinear[i],
			factorofSpeedLinear[i]);

	i = m_choiceUnitSpeedRotational->GetSelection();
	settings->RotationalSpeed.Setup(_T("1/s"), unitsOfSpeedRotational[i],
			factorofSpeedRotational[i]);

	i = m_choiceUnitTime->GetSelection();
	settings->Time.Setup(_T("m"), unitsOfTime[i], factorofTime[i]);

	return true;
}

void DialogSetupUnits::OnChangeUnit(wxCommandEvent& event)
{
	TransferDataFromWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE);
	ProcessEvent(selectEvent);
}
