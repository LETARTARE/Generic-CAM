/*
 * Machine.h
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */
#ifndef MACHINE_H_
#define MACHINE_H_
#include "LUACodeEvaluator.h"
#include "MachineComponent.h"
#include <wx/string.h>
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(MachineComponent, ArrayOfMachineComponent)
;
class Machine {
	//Constructor / Destructor
public:
	Machine();
	virtual ~Machine();

	// Member variables
public:
	LUACodeEvaluator evaluator;
	wxString machineDescription;
	ArrayOfMachineComponent components;
	wxString textOut;

	float axisA;
	float axisB;
	float axisC;
	float axisU;
	float axisV;
	float axisW;
	float axisX;
	float axisY;
	float axisZ;

	// Methods
public:
	void SetMachineDescription(wxString text);

	void ClearComponents(void);
	bool AddComponent(wxString nameOfComponent);
	bool PlaceComponent(wxString nameOfComponent,
			const AffineTransformMatrix &matrix);

	bool Assemble(void);
	void Paint(void);

};

#endif /* MACHINE_H_ */
