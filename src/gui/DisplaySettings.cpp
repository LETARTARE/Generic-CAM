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

DisplaySettings::DisplaySettings()
{
	Time.Setup(_T("s"), _T("min"), (double) 60);
	Distance.Setup(_T("m"), _T("cm"), (double) 10e-3);
	RotationalSpeed.Setup(_T("1/s"), _T("1/min"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("cm/min"), (double) 10e-3 / 60);
	Angle.Setup(_T("deg"), _T("deg"), (double) 1.0);
}

DisplaySettings::~DisplaySettings()
{
}

bool DisplaySettings::GetConfigFrom(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	return true;
}

bool DisplaySettings::WriteConfigTo(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	return true;
}
