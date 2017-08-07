///////////////////////////////////////////////////////////////////////////////
// Name               : MachineSimulator.cpp
// Purpose            : A simulator for the machine operation.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "MachineSimulator.h"

#include <float.h>

#include <wx/textfile.h>

MachineSimulator::MachineSimulator()
{
	initialized = false;
	tStep = 0;
	step = 0;

	machine = NULL;
	workpiece = NULL;
	toolpath = NULL;
}

MachineSimulator::~MachineSimulator()
{
}

void MachineSimulator::InsertWorkpiece(Workpiece* workpiece)
{
	if(this->workpiece == workpiece && workpiece != NULL) return;
	this->workpiece = workpiece;
	initialized = false;
}

void MachineSimulator::InsertToolPath(ToolPath* toolpath)
{
	if(this->toolpath == toolpath && toolpath != NULL) return;
	this->toolpath = toolpath;
	initialized = false;
}

void MachineSimulator::InsertMachine(Machine* machine)
{
	if(this->machine == machine && machine != NULL) return;
	this->machine = machine;
	initialized = false;
}

void MachineSimulator::InitSimulation(size_t maxCells)
{
	if(workpiece == NULL) return;
	const double area = workpiece->GetSizeX() * workpiece->GetSizeY();
	const double L = sqrt(area / (double) maxCells);
	size_t nx = floor(workpiece->GetSizeX() / L);
	size_t ny = floor(workpiece->GetSizeY() / L);
	if(nx == 0 || ny == 0) return;
	if(nx != simulation.GetXCount() || ny != simulation.GetYCount()) initialized =
			false;

	if(!initialized){
		const double dx = workpiece->GetSizeX() / (double) nx;
		const double dy = workpiece->GetSizeY() / (double) ny;
		simulation.SetupBox(workpiece->GetSizeX(), workpiece->GetSizeY(),
				workpiece->GetSizeZ(), dx, dy);
		if(machine != NULL && toolpath != NULL){
			machine->Reset();
			offset = machine->workpiecePosition.GetCenter()
					- machine->toolPosition.GetCenter();
			machine->DryRunToolPath(toolpath);
		}
		tStep = 0;
		step = 0;
		initialized = true;
	}
	simulation.displayBox = true;
}

void MachineSimulator::Reset(void)
{
	if(!initialized) return;
	const double dx = simulation.GetSizeRX();
	const double dy = simulation.GetSizeRY();
	simulation.SetupBox(workpiece->GetSizeX(), workpiece->GetSizeY(),
			workpiece->GetSizeZ(), dx, dy);
	tStep = 0;
	step = 0;
	if(machine != NULL){
		machine->Reset();
		offset = machine->workpiecePosition.GetCenter()
				- machine->toolPosition.GetCenter();
		if(toolpath != NULL && !toolpath->positions.IsEmpty()){
			machine->ProcessGCode(toolpath->positions[0]);
		}
	}
}

void MachineSimulator::Previous(void)
{
	if(toolpath == NULL) return;
	if(step > 1) Step(toolpath->positions[step - 1].tStart + FLT_EPSILON);
}

void MachineSimulator::Step(float tTarget)
{
	if(!initialized) return;
	if(machine == NULL) return;
	if(toolpath == NULL) return;

	if(tTarget < tStep){
		Reset();
	}

	Polygon3 temp;
	temp.InsertPoint(machine->position.X - offset.x,
			machine->position.Y - offset.y, machine->position.Z - offset.z);
	while(step + 1 < toolpath->positions.GetCount() && tTarget > tStep){
		step++;
		tStep = toolpath->positions[step].tStart
				+ toolpath->positions[step].duration;
		machine->ProcessGCode(toolpath->positions[step]);
		const double toolLength = machine->toolLength;
		temp.InsertPoint(machine->position.X - offset.x,
				machine->position.Y - offset.y,
				machine->position.Z - offset.z - toolLength);
	}
	machine->Assemble();

	if(machine->toolSlot > 0){
		const Tool* tool = &(machine->tools[machine->toolSlot - 1]);
		DexelTarget dex;
		dex.SetupTool(*tool, simulation.GetSizeRX(), simulation.GetSizeRY());
//		dex.MirrorZ();
//		dex.NegateZ();
		simulation.PolygonCutInTarget(temp, dex);
	}

//	if(step + 1 == position.size()){
//		machine->position = position[step];
//	}else{
//		machine->position = position[step]
//				+ (position[step + 1] - position[step])
//						/ position[step].duration * (tTarget - tStep);
//	}
}

void MachineSimulator::Next(void)
{
	if(toolpath == NULL) return;
	if(step + 1 < toolpath->positions.GetCount()) Step(
			toolpath->positions[step + 1].tStart + FLT_EPSILON);
}

void MachineSimulator::Last(void)
{
	if(toolpath == NULL) return;
	Step(toolpath->MaxTime() - FLT_EPSILON);
}

void MachineSimulator::Paint(void) const
{
	if(!initialized) return;
	if(workpiece == NULL) return;
//	if(machine == NULL) return;
//	if(toolpath == NULL) return;

	glPushMatrix();
	glMultMatrixd(workpiece->matrix.a);
	simulation.Paint();
	glPopMatrix();
}

