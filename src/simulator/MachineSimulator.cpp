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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "MachineSimulator.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachinePosition)

#include <wx/textfile.h>

MachineSimulator::MachineSimulator()
{
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

	AffineTransformMatrix a, b;

	a.TranslateGlobal(-0.05,0,0);
	b.TranslateGlobal(+0.05,0.1,0);

	machine.tool = &toolbox.tools[0];
	machine.toolpath = &toolpath;
	//toolpath.Generate(*machine.tool, a, b);

	toolpath.SetSphere(0.335,2);
	toolpath.SelfTest();

	machine.workpiece.BooleanRemove(&toolpath);
}

MachineSimulator::~MachineSimulator()
{

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
		machine.position = position[step];
	}else{
		machine.position = position[step] + (position[step + 1]
				- position[step]) / position[step].duration * (tTarget - tStep);
	}
}

bool MachineSimulator::ReadGCodeFile(wxFileName fileName)
{
	if(!fileName.IsOk()){
		wxLogError(_T("ReadGCodeFile: Incorrect fileName ")
				+ fileName.GetFullPath() + _T(" !"));
		return false;
	}

	wxTextFile file;

	if(!file.Open(fileName.GetFullPath())){
		wxLogError(_T("ReadGCodeFile: Can't open ") + fileName.GetFullPath()
				+ _T(" !"));
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
	tStep = 0;

	return true;
}

bool MachineSimulator::WriteGCodeFile(wxFileName fileName)
{
	//TODO: Writing G-Code Files
	return false;
}

