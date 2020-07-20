///////////////////////////////////////////////////////////////////////////////
// Name               : CollectionUnits.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.02.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CollectionUnits.h"

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

CollectionUnits::CollectionUnits()
{
	Time.Setup(_T("s"), _T("min"), (double) 60);
	Distance.Setup(_T("m"), _T("cm"), (double) 10e-3);
	SmallDistance.Setup(_T("m"), _T("mm"), (double) 1e-3);
	Tolerance.Setup(_T("m"), _T("um"), (double) 1e-6);
	LinearSpeed.Setup(_T("m/s"), _T("cm/min"), (double) 10e-3 / 60);
	RotationalSpeed.Setup(_T("1/s"), _T("1/min"), (double) 1 / 60);
	Angle.Setup(_T("rad"), _T("deg"), (double) M_PI / 180.0);
	Percentage.Setup(_T("-"), _T("%"), (double) 0.01);

	// Setup available units

	factorofTime = new double[4];
	unitsOfTime.Add(_T("s"));
	factorofTime[0] = 1; // s
	unitsOfTime.Add(_T("min"));
	factorofTime[1] = 60; // s
	unitsOfTime.Add(_T("h"));
	factorofTime[2] = 3600; // s
	unitsOfTime.Add(_T("d"));
	factorofTime[3] = 86400; // s

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

	factorofAngle = new double[3];
	unitsOfAngle.Add(_T("rad"));
	factorofAngle[0] = 1.0; // rad
	unitsOfAngle.Add(_T("deg"));
	factorofAngle[1] = M_PI / 180.0; // rad
	unitsOfAngle.Add(_T("gon"));
	factorofAngle[2] = M_PI / 200.0; // rad
}

CollectionUnits::~CollectionUnits()
{
	delete[] factorofAngle;
	delete[] factorofSpeedRotational;
	delete[] factorofSpeedLinear;
	delete[] factorofLength;
	delete[] factorofTime;
}

bool CollectionUnits::Load(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	wxString temp;
	int i;

	config->Read(_T("UnitTime"), &temp, _T("min"));
	i = unitsOfTime.Index(temp);
	if(i != wxNOT_FOUND) Time.Setup(_T("s"), unitsOfTime[i], factorofTime[i]);

	config->Read(_T("UnitDistance"), &temp, _T("cm"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) Distance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitSmallDistance"), &temp, _T("cm"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) SmallDistance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitTolerance"), &temp, _T("um"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) Tolerance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitLinearSpeed"), &temp, _T("cm/min"));
	i = unitsOfSpeedLinear.Index(temp);
	if(i != wxNOT_FOUND) LinearSpeed.Setup(_T("m/s"), unitsOfSpeedLinear[i],
			factorofSpeedLinear[i]);

	config->Read(_T("UnitRotationalSpeed"), &temp, _T("1/min"));
	i = unitsOfSpeedRotational.Index(temp);
	if(i != wxNOT_FOUND) RotationalSpeed.Setup(_T("1/s"),
			unitsOfSpeedRotational[i], factorofSpeedRotational[i]);

	config->Read(_T("UnitAngle"), &temp, _T("deg"));
	i = unitsOfAngle.Index(temp);
	if(i != wxNOT_FOUND) Angle.Setup(_T("rad"), unitsOfAngle[i],
			factorofAngle[i]);

	// unitsOfPercentage is not saved in config file.

	return true;
}

bool CollectionUnits::Save(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	config->Write(_T("UnitTime"), Time.GetOtherName());
	config->Write(_T("UnitDistance"), Distance.GetOtherName());
	config->Write(_T("UnitSmallDistance"), SmallDistance.GetOtherName());
	config->Write(_T("UnitTolerance"), Tolerance.GetOtherName());
	config->Write(_T("UnitLinearSpeed"), LinearSpeed.GetOtherName());
	config->Write(_T("UnitRotationalSpeed"), RotationalSpeed.GetOtherName());
	config->Write(_T("UnitAngle"), Angle.GetOtherName());
	// unitsOfPercentage is not loaded from config file.
	return true;
}
