///////////////////////////////////////////////////////////////////////////////
// Name               : Machine.cpp
// Purpose            : The machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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

#include "Machine.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <wx/textfile.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineComponent)

Machine::Machine()
{
	initialized = false;
	tool = NULL;
	toolpath = NULL;
	position.Zero();
	ClearComponents();
}

Machine::~Machine()
{
}

void Machine::Paint(void) const
{
	unsigned int i;
	for(i = 0; i < components.Count(); i++){
		components[i].Paint();
	}

	if(tool != NULL){
		::glPushMatrix();
		::glMultMatrixd(toolPosition.a);
		tool->Paint();
		::glPopMatrix();
	}
	::glPushMatrix();
	::glMultMatrixd(workpiecePosition.a);
	workpiece.Paint();
	::glPopMatrix();

	//if(toolpath != NULL) toolpath->Paint();

}

void Machine::ClearComponents(void)
{
	components.Empty();
	AddComponent(_T("Base"));
}

bool Machine::AddComponent(wxString const& nameOfComponent)
{
	unsigned int i;
	for(i = 0; i < components.Count(); i++){
		if(components[i].nameOfComponent.Cmp(nameOfComponent) == 0) return false;
	}
	MachineComponent* temp = new MachineComponent(nameOfComponent);
	components.Add(temp);
	return true;
}

bool Machine::PlaceComponent(wxString const& nameOfComponent,
		AffineTransformMatrix const& matrix)
{
	unsigned int i;
	bool flag = false;
	for(i = 0; i < components.Count(); i++){
		if(components[i].nameOfComponent.Cmp(nameOfComponent) == 0){
			flag = true;
			components[i].matrix.Set(matrix);


			// Sideeffect of placing the components:
			// The tool and the material matrices are set up.
			if((int) i == componentWithMaterial){
				workpiecePosition.Set(workpiecePositionRelativ);
				workpiecePosition = matrix * workpiecePosition;
			}
			if((int) i == componentWithTool){
				toolPosition.Set(toolPositionRelativ);
				toolPosition = matrix * toolPosition;
			}
		}
	}
	return flag;
}

void Machine::Assemble()
{
	evaluator.EvaluateAssembly();
}

void Machine::EvaluateDescription(void)
{
	wxLogMessage(_T("Machine::InsertMachineDescription"));
	evaluator.LinkToMachine(this);
	evaluator.EvaluateProgram();
	Assemble();
	textOut = evaluator.GetOutput();
}

bool Machine::ReLoadDescription(void)
{
	if(!fileName.IsOk()) return false;
	wxTextFile file(fileName.GetFullPath());
	if(!file.Open(wxConvLocal)){
		if(!file.Open(wxConvFile)){
			wxLogError(_T("Opening of the file failed!"));
			return false;
		}
	}
	wxString str;
	machineDescription.Empty();
	for(str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()){
		machineDescription += str + _T("\n");
	}
	EvaluateDescription();
	return true;
}

bool Machine::LoadDescription(wxFileName const& fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	return ReLoadDescription();
}
