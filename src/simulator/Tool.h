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
#include <wx/string.h>

class Tool {
	// Constructor/ Destructor
public:
	Tool();
	virtual ~Tool();


	// Member variables
public:
	wxString toolName;
	float shaftDiameter;
	float shaftLength;
	float maxSpeed;
	float feedCoefficient;
	unsigned int nrOfTeeth;
	wxString comment;
	ArrayOfToolElement elements;

	// Methods
public:
	void Paint2D(void);
	void Paint3D(void);

	float GetPositiveLength(void);
	float GetNegativeLength(void);
	float GetMaxDiameter(void);


};

#endif /* TOOL_H_ */
