/*
 * Machine.cpp
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */

#include "Machine.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfMachineParts)

Machine::Machine()
{
	ClearParts();
}

Machine::~Machine()
{

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
	matrixToManipulate = &(temp->matrix);
	return true;
}
