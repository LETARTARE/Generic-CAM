/*
 * Machine.cpp
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */

#include "Machine.h"

#include <wx/log.h>
#include "LUACodeEvaluator.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineParts)

Machine::Machine()
{
	ClearParts();
}

Machine::~Machine()
{

}

void Machine::InsertMachineDescription(wxString text)
{
	machineDescription = text;
	wxLogMessage(_T("Machine::InsertMachineDescription"));
	LUACodeEvaluator eval(wxTHREAD_JOINABLE);
	eval.Create();
	eval.LinkToMachine(this);
	eval.Run();
	eval.Wait();
}

void Machine::ClearParts(void)
{
	parts.Empty();
	AddPart(_T("Base"));
}

bool Machine::AddPart(wxString name)
{
	unsigned int i;
	for(i = 0; i < parts.Count(); i++){
		if(parts[i].partname.Cmp(name) == 0) return false;
	}
	MachinePart* temp = new MachinePart(name);
	parts.Add(temp);
	partToManipulate = temp;
	return true;
}
