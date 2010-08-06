
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef BOUND_H
#define BOUND_H

#include "ML_Vector.h"

class VectorSet;

class Bound
{
public:

	float xMax;
	float xMin;
	float yMax;
	float yMin;
	float zMax;
	float zMin;

	Bound(const mlVector3D & p1, const mlVector3D & p2, const mlVector3D & p3);
	Bound(VectorSet * vertices);
	virtual ~Bound();

	bool overlap(Bound  bound);

	static double TOL;

private:

	void checkVertex(const mlVector3D & vertex);
};

#endif // BOUND_H
