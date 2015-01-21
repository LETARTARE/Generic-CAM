///////////////////////////////////////////////////////////////////////////////
// Name               : DisplaySettings.h
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

#ifndef DISPLAYSETTINGS_H_
#define DISPLAYSETTINGS_H_

/*!\class DisplaySettings
 * \brief ...
 *
 * ...
 */

#include <wx/config.h>

#include "Unit.h"

class DisplaySettings {
	friend class DialogSetupUnits;

public:
	DisplaySettings();
	virtual ~DisplaySettings();

	Unit Time;
	Unit Distance;
	Unit LinearSpeed;
	Unit RotationalSpeed;
	Unit Angle;

	wxString lastProjectDirectory;
	wxString lastObjectDirectory;
	wxString lastStockDirectory;
	wxString lastMachineDirectory;
	wxString lastToolboxDirectory;

	bool GetConfigFrom(wxConfig * config);
	bool WriteConfigTo(wxConfig * config);

protected:
	wxArrayString unitsOfLength;
	wxArrayString unitsOfTime;
	wxArrayString unitsOfSpeedLinear;
	wxArrayString unitsOfSpeedRotational;

	double * factorofLength;
	double * factorofTime;
	double * factorofSpeedLinear;
	double * factorofSpeedRotational;

};

#endif /* DISPLAYSETTINGS_H_ */
