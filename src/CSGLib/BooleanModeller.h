
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef BOOLEANMODELLER_H
#define BOOLEANMODELLER_H

#include "Object3D.h"
#include "Solid.h"
#include "Face.h"

class Object3D;
class Solid;

class BooleanModeller
{
public:

	Object3D * m_pObject1;
	Object3D * m_pObject2;
	
	BooleanModeller(Solid * solid1, Solid * solid2);
	virtual ~BooleanModeller();

	Solid * getUnion();
	Solid * getIntersection();
	Solid * getDifference();

private:
	
	Solid * composeSolid(int faceStatus1, int faceStatus2, int faceStatus3); // Convert these to enums
	
	// Need IntSet
	// Need ColorSet
	void groupObjectComponents(Object3D & pObject, VertexSet & vertices, IntSet & indices, ColorSet & colors, int faceStatus1, int faceStatus2);
};

#endif // BOOLEANMODELLER_H
