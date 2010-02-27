/*
 * MachineComponent.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */
#ifndef MACHINECOMPONENT_H_
#define MACHINECOMPONENT_H_
#include "../3D/AffineTransformMatrix.h"
#include "MachineElement.h"
#include <wx/string.h>
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(MachineElement, ArrayOfMachineElement)
;

class MachineComponent {
	// Constructor / Destructor
public:
	MachineComponent();
	MachineComponent(wxString nameOfComponent);

	virtual ~MachineComponent();

	// Member variables
public:

	wxString nameOfComponent;
	ArrayOfMachineElement elements;
private:
	AffineTransformMatrix matrix;

	// Methods
public:
	void Paint(void);
	void InsertBox(AffineTransformMatrix matrix, float x, float y, float z);
	void InsertCylinder(AffineTransformMatrix matrix, float h, float r);
	void InsertCone(AffineTransformMatrix matrix, float h, float r1, float r2);
private:
	MachineElement* AddElement();
};

#endif /* MACHINECOMPONENT_H_ */
