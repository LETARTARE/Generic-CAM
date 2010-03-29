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

#include <wx/textfile.h>

MachineSimulator::MachineSimulator()
{
	machine = NULL;
	tStep = 0;

	MachinePosition* pos;
	pos = new MachinePosition(0.1, 0.1, -0.0);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.1);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.0);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.2, -0.0);
	position.Add(pos);
	pos = new MachinePosition(0.2, 0.2, -0.0);
	position.Add(pos);
	pos = new MachinePosition(0.1, 0.1, -0.0);
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

bool MachineSimulator::ReadGCodeFile(wxString fileName)
{
	wxTextFile file;

	if(!file.Open(fileName)){
		wxLogError(_T("ReadGCodeFile: Can't open ") + fileName + _T(" !"));
		return false;
	}

	wxString temp;
	if(file.Eof()){
		wxLogError(_T("ReadGCodeFile: File is empty! (a)"));
		return false;
	}
	temp = file.GetFirstLine();
	if(temp.IsEmpty()){
		wxLogError(_T("ReadGCodeFile: File is empty! (b)"));
		return false;
	}

	MachinePosition* pos = new MachinePosition;
	position.Clear();

	if(pos->ParseGCodeLine(temp)){
		position.Add(pos);
		pos = new MachinePosition;
		*pos = position[position.Count() - 1];
	}
	while(!file.Eof()){
		temp = file.GetNextLine();
		if(pos->ParseGCodeLine(temp)){
			position.Add(pos);
			pos = new MachinePosition;
			//TODO: Check if there is a command like position.End()
			*pos = position[position.Count() - 1];
		}
	}
	position.Add(pos);
	file.Close();
	step = 0;
	tStep=0;

	return true;
}

bool MachineSimulator::WriteGCodeFile(wxString fileName)
{
	//TODO: Writing G-Code Files
	return false;
}

