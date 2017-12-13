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
#include "../Project.h"

#include <wx/textfile.h>
#include <float.h>

MachineSimulator::MachineSimulator()
{
	initialized = false;
	tStep = 0;
	step = 0;

	machine = NULL;
	basetarget = NULL;
	toolpath = NULL;
}

MachineSimulator::~MachineSimulator()
{
}

void MachineSimulator::InsertTarget(DexelTarget* target)
{
	if(this->basetarget == target && target != NULL) return;
	this->basetarget = target;
	initialized = false;
}

void MachineSimulator::InsertToolPath(ToolPath* toolpath)
{
	if(this->toolpath == toolpath && toolpath != NULL) return;
	this->toolpath = toolpath;
	tStep = 0;
	step = 0;
}

void MachineSimulator::InsertMachine(Machine* machine)
{
	if(this->machine == machine && machine != NULL) return;
	this->machine = machine;
	initialized = false;
}

void MachineSimulator::Reset(bool calculateTiming)
{
	if(!initialized){
		target.displayBox = true;
		initialized = true;
	}
	if(basetarget != NULL){
		target = *basetarget;
	}else{
		target.Empty();
	}

	if(machine != NULL && toolpath != NULL && calculateTiming){
		machine->Reset();
		machine->TouchoffHeight(0);
		for(size_t n = 0; n < toolpath->positions.Count(); n++)
			machine->InterpretGCode(&(toolpath->positions[n]), false);
	}
	machine->Reset();
	machine->TouchoffHeight(0);

	if(toolpath != NULL && !toolpath->positions.IsEmpty()){
		machine->InterpretGCode(&(toolpath->positions[0]));
	}
	tStep = 0;
	step = 0;
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

	CNCPosition cp = machine->currentpos + CNCPosition(machine->offset0);
	temp.InsertPoint(cp.X, cp.Y, cp.Z);

	while(step + 1 < toolpath->positions.GetCount() && tTarget > tStep){
		step++;
		tStep = toolpath->positions[step].t
				+ toolpath->positions[step].duration;

		machine->InterpretGCode(&(toolpath->positions[step]), false);

		CNCPosition cp = machine->currentpos + machine->offset0;
		temp.InsertPoint(cp.X, cp.Y, cp.Z);
	}
	machine->Assemble();

	if(machine->selectedToolSlot > 0){
		const Tool* tool = &(machine->tools[machine->selectedToolSlot - 1]);
		DexelTarget dex;
		dex.SetupTool(*tool, target.GetResolutionX(), target.GetResolutionY());
//		dex.MirrorZ();
//		dex.NegateZ();
		target.PolygonCutInTarget(temp, dex);
	}

//	if(step + 1 == position.size()){
//		machine->position = position[step];
//	}else{
//		machine->position = position[step]
//				+ (position[step + 1] - position[step])
//						/ position[step].duration * (tTarget - tStep);
//	}
}

void MachineSimulator::Previous(void)
{
	if(toolpath == NULL) return;
	if(step > 1) Step(toolpath->positions[step - 1].t + FLT_EPSILON);
}

void MachineSimulator::Next(void)
{
	if(toolpath == NULL) return;
	if(step + 1 < toolpath->positions.GetCount()) Step(
			toolpath->positions[step + 1].t + FLT_EPSILON);
}

void MachineSimulator::Last(void)
{
	if(toolpath == NULL) return;
	Step(toolpath->MaxTime() - FLT_EPSILON);
}

double MachineSimulator::GetMaxTime(void) const
{
	if(toolpath == NULL) return 0.0;
	return toolpath->MaxTime();
}

double MachineSimulator::GetCurrentTime(void) const
{
	return tStep;
}

const DexelTarget* MachineSimulator::GetTarget(void) const
{
	return &target;
}

void MachineSimulator::Paint(void) const
{
	if(!initialized) return;
	glPushMatrix();
	target.Paint();
	glPopMatrix();
}

wxString MachineSimulator::GetCurrentGCode(int pos) const
{
	if(toolpath == NULL) return wxString();
	if(pos < 0 && step < -pos) return wxString();
	return toolpath->GetGCode(step + pos);
}
