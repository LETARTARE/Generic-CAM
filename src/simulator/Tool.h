//============================================================================
// Name        : Tool.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================
#ifndef TOOL_H_
#define TOOL_H_
#include "ToolElement.h"
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(ToolElement, ArrayOfToolElement)
;

class Tool {
	// Constructor/ Destructor
public:
	Tool();
	virtual ~Tool();


	// Member variables
private:
	ArrayOfToolElement elements;


	// Methods
public:


};

#endif /* TOOL_H_ */
