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
#include <stdlib.h>
#include <gts.h>
#include "../3D/Vector3.h"
class Workpiece {
	// Constructor / Destructor
public:
	Workpiece();
	virtual ~Workpiece();

	// Member variables
public:
	GtsSurface * s;

	// Methods
public:
	void Paint();
	void AddQuad(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2,
			const Vector3 &p3);
	void AddTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
	void AddBox(const double sizeX, const double sizeY, const double sizeZ);
};

#endif /* WORKPIECE_H_ */
