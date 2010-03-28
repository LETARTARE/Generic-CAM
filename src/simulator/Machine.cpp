/*
 * Machine.cpp
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */

#include "Machine.h"

#include <wx/log.h>
#include <GL/gl.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineComponent)

Machine::Machine()
{
	activeTool = 1;
	position.Zero();
	ClearComponents();
}

Machine::~Machine()
{
}

void Machine::Paint(void)
{
	unsigned int i;
	for(i = 0; i < components.Count(); i++){
		components[i].Paint();
	}

	if(activeTool > 0 && activeTool <= toolbox.tools.Count()){
		::glPushMatrix();
		::glMultMatrixd(toolPosition.a);
		toolbox.tools[activeTool - 1].Paint();
		::glPopMatrix();
	}
}

void Machine::SetMachineDescription(wxString text)
{
	machineDescription = text;
	wxLogMessage(_T("Machine::InsertMachineDescription"));

	evaluator.LinkToMachine(this);
	evaluator.EvaluateProgram();

	evaluator.EvaluateAssembly();

	textOut = evaluator.GetOutput();
}

void Machine::ClearComponents(void)
{
	components.Empty();
	AddComponent(_T("Base"));
}

bool Machine::AddComponent(wxString nameOfComponent)
{
	unsigned int i;
	for(i = 0; i < components.Count(); i++){
		if(components[i].nameOfComponent.Cmp(nameOfComponent) == 0) return false;
	}
	MachineComponent* temp = new MachineComponent(nameOfComponent);
	components.Add(temp);
	return true;
}

bool Machine::PlaceComponent(wxString nameOfComponent,
		const AffineTransformMatrix &matrix)
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
				materialPosition.Set(materialPositionRelativ);
				materialPosition = matrix * materialPosition;
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
