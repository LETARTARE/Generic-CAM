/*
 * Machine.cpp
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */

#include "Machine.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <wx/textfile.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineComponent)

Machine::Machine()
{
	tool = NULL;
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

bool Machine::LoadDescription(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	return ReLoadDescription();
}
