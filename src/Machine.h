/*
 * Machine.h
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "MachinePart.h"

#include <wx/string.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(MachinePart, ArrayOfMachineParts);

class Machine {
	//Constructor / Destructor
public:
	Machine();
	virtual ~Machine();

	// Member variables
public:
	wxString machineDescription;
	ArrayOfMachineParts parts;
	AffineTransformMatrix* matrixToManipulate;

	// Methods
public:
	void ClearParts(void);
	bool AddPart(wxString name);

};

#endif /* MACHINE_H_ */
