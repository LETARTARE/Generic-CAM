///////////////////////////////////////////////////////////////////////////////
// Name               : DisplaySettings.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.01.2015
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

#include "DisplaySettings.h"

#include <wx/filename.h>

DisplaySettings::DisplaySettings()
{
	Time.Setup(_T("s"), _T("min"), (double) 60);
	Distance.Setup(_T("m"), _T("cm"), (double) 10e-3);
	SmallDistance.Setup(_T("m"), _T("mm"), (double) 1e-3);
	RotationalSpeed.Setup(_T("1/s"), _T("1/min"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("cm/min"), (double) 10e-3 / 60);
	Angle.Setup(_T("deg"), _T("deg"), (double) 1.0);

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

	eyeDistance = 0.1;
	focalDistance = 1.0;
	backgroundGrayLevel = 90;
	rightEyeR = 0;
	rightEyeG = 77;
	rightEyeB = 102;
	leftEyeR = 179;
	leftEyeG = 0;
	leftEyeB = 0;
}

DisplaySettings::~DisplaySettings()
{
	delete[] factorofTime;
	delete[] factorofSpeedRotational;
	delete[] factorofSpeedLinear;
	delete[] factorofLength;
}

bool DisplaySettings::GetConfigFrom(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	wxString cwd = wxFileName::GetCwd();

	config->Read(_T("LastProjectDirectory"), &lastProjectDirectory, cwd);
	config->Read(_T("LastObjectDirectory"), &lastObjectDirectory, cwd);
	config->Read(_T("LastMachineDirectory"), &lastMachineDirectory, cwd);
	config->Read(_T("LastStockDirectory"), &lastStockDirectory, cwd);
	config->Read(_T("LastToolboxDirectory"), &lastToolboxDirectory, cwd);

	long lval;

	config->Read(_T("Stereo3DColorLeftEyeRed"), &lval, 180l);
	leftEyeR = lval;
	config->Read(_T("Stereo3DColorLeftEyeGreen"), &lval, 0);
	leftEyeG = lval;
	config->Read(_T("Stereo3DColorLeftEyeBlue"), &lval, 0);
	leftEyeB = lval;
	config->Read(_T("Stereo3DColorRightEyeRed"), &lval, 0);
	rightEyeR = lval;
	config->Read(_T("Stereo3DColorRightEyeGreen"), &lval, 100);
	rightEyeG = lval;
	config->Read(_T("Stereo3DColorRightEyeBlue"), &lval, 100);
	rightEyeB = lval;

	double dval;

	config->Read(_T("Stereo3DEyeDistance"), &dval, 0.1);
	eyeDistance = dval;
	config->Read(_T("Stereo3DFocalDistance"), &dval, 0.0);
	focalDistance = dval;

	return true;
}

bool DisplaySettings::WriteConfigTo(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	config->Write(_T("LastProjectDirectory"), lastProjectDirectory);
	config->Write(_T("LastObjectDirectory"), lastObjectDirectory);
	config->Write(_T("LastMachineDirectory"), lastMachineDirectory);
	config->Write(_T("LastStockDirectory"), lastStockDirectory);
	config->Write(_T("LastToolboxDirectory"), lastToolboxDirectory);

	config->Write(_T("Stereo3DColorLeftEyeRed"), (long) leftEyeR);
	config->Write(_T("Stereo3DColorLeftEyeGreen"), (long) leftEyeG);
	config->Write(_T("Stereo3DColorLeftEyeBlue"), (long) leftEyeB);
	config->Write(_T("Stereo3DColorRightEyeRed"), (long) rightEyeR);
	config->Write(_T("Stereo3DColorRightEyeGreen"), (long) rightEyeG);
	config->Write(_T("Stereo3DColorRightEyeBlue"), (long) rightEyeB);
	config->Write(_T("Stereo3DEyeDistance"), (double) eyeDistance);
	config->Write(_T("Stereo3DFocalDistance"), (double) focalDistance);

	return true;
}

void DisplaySettings::WriteToCanvas(OpenGLCanvas* canvas)
{
	canvas->leftEyeR = this->leftEyeR;
	canvas->leftEyeG = this->leftEyeG;
	canvas->leftEyeB = this->leftEyeB;
	canvas->rightEyeR = this->rightEyeR;
	canvas->rightEyeG = this->rightEyeG;
	canvas->rightEyeB = this->rightEyeB;
	canvas->focalDistance = this->focalDistance;
	canvas->eyeDistance = this->eyeDistance;
	canvas->backgroundGrayLevel = this->backgroundGrayLevel;
}
