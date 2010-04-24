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
#include "Toolbox.h"
#include "ToolPath.h"
#include "Machine.h"
#include "MachinePosition.h"
#include <wx/filename.h>
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(MachinePosition, ArrayOfMachinePosition)
;

class MachineSimulator {
	// Constructor/ Destructor
public:
	MachineSimulator();
	virtual ~MachineSimulator();

	//Member variables
public:

	Machine machine;
	ArrayOfMachinePosition position;

	ToolPath toolpath;
	Toolbox toolbox;

	float tStep;
	unsigned long step;

	//Methods
public:
	void InsertMachine(Machine* machine);
	void Reset(void);
	void Step(float tTarget);

	bool ReadGCodeFile(wxFileName fileName);
	bool WriteGCodeFile(wxFileName fileName);

};

#endif /* MACHINESIMULATOR_H_ */
