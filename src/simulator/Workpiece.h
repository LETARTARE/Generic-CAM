//============================================================================
// Name        : Workpiece.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 29.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef WORKPIECE_H_
#define WORKPIECE_H_

#include "../3D/CSGSurface.h"

class Workpiece {
	// Constructor / Destructor
public:
	Workpiece();
	virtual ~Workpiece();

	// Member variables
public:
	CSGSurface s;

	// Methods
public:
	void Paint();
};

#endif /* WORKPIECE_H_ */
