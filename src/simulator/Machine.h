/*
 * Machine.h
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */
#ifndef MACHINE_H_
#define MACHINE_H_
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
	wxString machineDescription;
	ArrayOfMachineComponent components;
	wxString textOut;

	// Methods
public:
	void ClearComponents(void);
	bool AddComponent(wxString nameOfComponent);
	bool PlaceComponent(wxString nameOfComponent,
			const AffineTransformMatrix &matrix);
	void SetMachineDescription(wxString text);
	void Paint(void);
};

#endif /* MACHINE_H_ */
