//============================================================================
// Name        : MachineSimulator.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 06.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "MachineSimulator.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachinePosition)

MachineSimulator::MachineSimulator()
{
	machine = NULL;
	tStep = 0;

	MachinePosition* pos;
	pos = new MachinePosition(0.1, 0.1, -0.1);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.2);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.1);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.2, -0.1);
	position.Add(pos);
	pos = new MachinePosition(0.2, 0.2, -0.1);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.1);
	position.Add(pos);

}

MachineSimulator::~MachineSimulator()
{

}

void MachineSimulator::InsertMachine(Machine* machine)
{
	this->machine = machine;
}
void MachineSimulator::Reset(void)
{
	step = 0;
}
void MachineSimulator::Step(float tTarget)
{
	if(tTarget < tStep){
		tStep = 0;
		step = 0;
	}

	while(step + 1 < position.Count() && tTarget > tStep
			+ position[step].duration){
		tStep += position[step].duration;
		step++;
	}

	if(step + 1 == position.Count()){
		machine->position = position[step];
	}else{
		machine->position = position[step] + (position[step + 1]
				- position[step]) / position[step].duration * (tTarget - tStep);
	}
}
