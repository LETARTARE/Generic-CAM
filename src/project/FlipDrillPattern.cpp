///////////////////////////////////////////////////////////////////////////////
// Name               : FlipDrillPattern.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 20.02.2015
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

#include "FlipDrillPattern.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfDrillPosition)
WX_DEFINE_OBJARRAY(ArrayOfFlipDrillPattern)

DrillPosition::DrillPosition()
{
	x = 0.0;
	y = 0.0;
	depth = 0.0;
	diameter = 0.0;
}

FlipDrillPattern::FlipDrillPattern()
{
	//size_t Project::SetupMachineBed(bool flipped)
	//{
	//	TargetPlacement tempPlace;
	//	Run* run = new Run;
	//	run.Empty();
	//	targets.Empty();

	// TODO: Remove next line to get full machinebed.
	//	if(true){
	//
	//		// The groundplane im machine coordinates
	//		tempPlace.Clear();
	//		tempPlace.outLine.InsertPoint(0.064, 0.082, 0.0);
	//		tempPlace.outLine.InsertPoint(0.533, 0.083, 0.0);
	//		tempPlace.outLine.InsertPoint(0.532, 0.342, 0.0);
	//		tempPlace.outLine.InsertPoint(0.064, 0.342, 0.0);
	//		tempPlace.outLine.Close();
	//		tempPlace.isMovable = false;
	//		tempPlace.isKeepout = true;
	//		run->placements.Add(tempPlace);
	//
	//		// Screws in the plane
	//		tempPlace.SetKeepout(0.078, 0.097, 0.010, 0.010);
	//		run->placements.Add(tempPlace);
	//
	//		tempPlace.SetKeepout(0.509, 0.096, 0.010, 0.010);
	//		run->placements.Add(tempPlace);
	//
	//		tempPlace.SetKeepout(0.507, 0.318, 0.010, 0.010);
	//		run->placements.Add(tempPlace);
	//
	//		tempPlace.SetKeepout(0.079, 0.316, 0.010, 0.010);
	//		run->placements.Add(tempPlace);
	//
	//		InsertDrillGrid(*run, 0.380, 0.230, flipped);
	//
	//	}
	//
	//	run.Add(run);
	//	return (run.GetCount() - 1);
	//}
}

void FlipDrillPattern::Paint(void) const
{
	toolpath.Paint();
	outLine.Paint();
}

void FlipDrillPattern::SetupDrill(Tool &tool, double diameter, double depth)
{
	const double d = diameter + 0.002;
	outLine.Clear();
	outLine.InsertPoint(-d, -d, 0.0);
	outLine.InsertPoint(d, -d, 0.0);
	outLine.InsertPoint(d, d, 0.0);
	outLine.InsertPoint(-d, d, 0.0);
	outLine.Close();

	const double r = (diameter - 0.0061) / 2.0;
	MachinePosition temp;
	temp.axisZ = 0.004;
	toolpath.positions.Add(temp);
	temp.axisZ = 0.001;
	toolpath.positions.Add(temp);
	temp.isCutting = true;
	temp.axisZ = -0.001;
	temp.axisX = r;
	toolpath.positions.Add(temp);
	temp.isRotationPositiv = true;
	temp.radiusI = -r;
	while(temp.axisZ > 0.003 - depth){
		temp.axisZ -= 0.003;
		toolpath.positions.Add(temp);
	}
	temp.axisZ = -depth;
	toolpath.positions.Add(temp);
	toolpath.positions.Add(temp);
	temp.axisZ += 0.001;
	temp.axisX = 0.000;
	temp.radiusI = 0.000;
	temp.isCutting = false;
	toolpath.positions.Add(temp);
	temp.axisZ = 0.004;
	toolpath.positions.Add(temp);
}

