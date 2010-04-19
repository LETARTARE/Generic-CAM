/*
 * MachineComponent.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachineComponent.h"

#include <wx/glcanvas.h>
#include <wx/log.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineElement)

MachineComponent::MachineComponent()
{

}
MachineComponent::MachineComponent(wxString nameOfComponent)
{
	this->nameOfComponent = nameOfComponent;
}

MachineComponent::~MachineComponent()
{
	elements.Clear();
}

MachineElement* MachineComponent::AddElement()
{
	MachineElement* temp = new MachineElement();
	elements.Add(temp);
	return temp;
}

void MachineComponent::InsertBox(AffineTransformMatrix matrix, float x,
		float y, float z)
{


	//return;
	MachineElement* temp = AddElement();
	temp->matrix = matrix;
	temp->typeOfElement = MACHINEELEMENT_BOX;
	temp->x = x;
	temp->y = y;
	temp->z = z;
}
void MachineComponent::InsertCylinder(AffineTransformMatrix matrix, float h,
		float r)
{
	MachineElement* temp = AddElement();
	temp->matrix = matrix;
	temp->typeOfElement = MACHINEELEMENT_CYLINDER;
	temp->r1 = r;
	temp->r2 = r;
	temp->h = h;
}

void MachineComponent::InsertCone(AffineTransformMatrix matrix, float h,
		float r1, float r2)
{
	MachineElement* temp = AddElement();
	temp->matrix = matrix;
	temp->typeOfElement = MACHINEELEMENT_CYLINDER;
	temp->r1 = r1;
	temp->r2 = r2;
	temp->h = h;
}

void MachineComponent::InsertSTL(AffineTransformMatrix matrix, wxFileName file)
{
	MachineElement* temp = AddElement();
	temp->matrix = matrix;
	temp->typeOfElement = MACHINEELEMENT_ARBITRARY;
	temp->ReadSTL(file);
}


void MachineComponent::Paint(void)
{

	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	unsigned int i;
	for(i = 0; i < elements.Count(); i++){
		elements[i].Paint();
	}
	::glPopMatrix();
}
