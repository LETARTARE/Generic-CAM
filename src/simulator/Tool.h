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
#include "../3D/Vector3.h"
#include <wx/string.h>
#include <wx/dynarray.h>

class ToolContourElement {
	// Constructor/ Destructor
public:
	ToolContourElement(bool cutting = false, bool partOfShaft = false);
	virtual ~ToolContourElement();

	// Member variables
public:
	Vector3 p1;
	Vector3 p2;
	Vector3 n1;
	Vector3 n2;
	bool isCutting;
	bool belongsToShaft;

	// Methods
public:
};

WX_DECLARE_OBJARRAY(ToolElement, ArrayOfToolElement)
;
WX_DECLARE_OBJARRAY(ToolContourElement, ArrayOfToolContourElement)
;

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
	ArrayOfToolContourElement contour;
	unsigned int slot;
	const unsigned int resolution;

	// Methods
public:
	void GenerateContour(void);
	void GenerateOutline(float alpha);

	float GetPositiveLength(void);
	float GetNegativeLength(void);
	float GetMaxDiameter(void);

	void Paint(void);
};

#endif /* TOOL_H_ */
