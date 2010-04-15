//============================================================================
// Name        : CSGSurface.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 15.04.2010
// Copyright   : (c) 2010
// Description : Wrapper for Constructive Solid Geometry
//============================================================================


#ifndef CSGSURFACE_H_
#define CSGSURFACE_H_

#include <gts.h>

class CSGSurface {
	// Constructor / Destructor
public:
	CSGSurface();
	virtual ~CSGSurface();
	// Member variables
public:

private:
	GtsSurface * s;

	// Methods
public:
	void Paint();

	void AddBox(const double sizeX, const double sizeY, const double sizeZ);
	void SetSphere(const double radius, const unsigned char subdivision = 3);

	void ScaleUniform(float scaleXYZ);
	void Scale(float scaleX, float scaleY, float scaleZ);
	void Rotate(float rotateX, float rotateY, float rotateZ);
	void Translate(float translateX = 0, float translateY = 0,
			float translateZ = 0);

	void BooleanRemove(const CSGSurface* surfaceToRemove);

};

#endif /* CSGSURFACE_H_ */
