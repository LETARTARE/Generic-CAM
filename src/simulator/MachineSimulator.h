//============================================================================
// Name        : MachineSimulator.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 06.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef MACHINESIMULATOR_H_
#define MACHINESIMULATOR_H_

#include "Machine.h"
#include "MachineMotion.h"

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(MachineMotion, ArrayOfMachineMotion);

class MachineSimulator {
	// Constructor/ Destructor
public:
	MachineSimulator();
	virtual ~MachineSimulator();

	//Member variables
public:



	//Methods
public:


};

#endif /* MACHINESIMULATOR_H_ */
