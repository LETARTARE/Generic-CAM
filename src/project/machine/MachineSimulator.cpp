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

#include <wx/textfile.h>

MachineSimulator::MachineSimulator()
{
	tStep = 0;
	step = 0;

//	position.reserve(100);
//	position.push_back(MachinePosition(0.1, 0.1, -0.0));
//	position.push_back(MachinePosition(0.1, 0.1, -0.1));
//	position.push_back(MachinePosition(0.1, 0.1, -0.0));
//	position.push_back(MachinePosition(0.1, 0.2, -0.0));
//	position.push_back(MachinePosition(0.2, 0.2, -0.0));
//	position.push_back(MachinePosition(0.1, 0.1, -0.0));

	AffineTransformMatrix a, b;

	a.TranslateGlobal(-0.05, 0, 0);
	b.TranslateGlobal(+0.05, 0.1, 0);

	machine = NULL;
	workpiece = NULL;
	toolpath = NULL;

}

MachineSimulator::~MachineSimulator()
{
}

void MachineSimulator::InsertWorkpiece(Workpiece* workpiece)
{
	this->workpiece = workpiece;
}

void MachineSimulator::InsertToolPath(ToolPath* toolpath)
{
	this->toolpath = toolpath;
}

void MachineSimulator::InsertMachine(Machine* machine)
{
	this->machine = machine;
}

void MachineSimulator::Reset(void)
{
	step = 0;
}

void MachineSimulator::Rewind(void)
{
}

void MachineSimulator::Step(float tTarget)
{
	if(tTarget < tStep){
		tStep = 0;
		step = 0;
	}

//	while(step + 1 < position.size()
//			&& tTarget > tStep + position[step].duration){
//		tStep += position[step].duration;
//		step++;
//	}

//	if(step + 1 == position.size()){
//		machine->position = position[step];
//	}else{
//		machine->position = position[step]
//				+ (position[step + 1] - position[step])
//						/ position[step].duration * (tTarget - tStep);
//	}
}

void MachineSimulator::FForward(void)
{
}

void MachineSimulator::InitSimulation(size_t maxCells)
{
	const double area = workpiece->GetSizeX() * workpiece->GetSizeY();
	const double L = sqrt(area / (double) maxCells);
	size_t nx = floor(workpiece->GetSizeX() / L);
	size_t ny = floor(workpiece->GetSizeY() / L);
	if(nx == 0 || ny == 0) return;
	const double dx = workpiece->GetSizeX() / (double) nx;
	const double dy = workpiece->GetSizeY() / (double) ny;
	simulation.SetupBox(workpiece->GetSizeX(), workpiece->GetSizeY(),
			workpiece->GetSizeZ(), dx, dy);
	simulation.displayBox = true;
}

bool MachineSimulator::ReadGCodeFile(wxFileName fileName)
{
	return false;
}

void MachineSimulator::Paint(void) const
{
	if(workpiece == NULL) return;
	glPushMatrix();
	glMultMatrixd(workpiece->matrix.a);
	simulation.Paint();
	glPopMatrix();
}

