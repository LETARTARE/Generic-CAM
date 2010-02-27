//============================================================================
// Name        : MachineElement.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 27.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef MACHINEELEMENT_H_
#define MACHINEELEMENT_H_

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Vector3.h"

#define MACHINEELEMENT_BOX	1
#define MACHINEELEMENT_CYLINDER	2

class MachineElement {
	// Constructor/ Destructor
public:
	MachineElement(unsigned char typeOfElement = 0);
	virtual ~MachineElement();
	// Member variables
public:

	AffineTransformMatrix matrix;
	unsigned char typeOfElement;

	float x,y,z,r1,r2,h;

	// Methods
public:
	void Paint(void);

};

#endif /* MACHINEELEMENT_H_ */
