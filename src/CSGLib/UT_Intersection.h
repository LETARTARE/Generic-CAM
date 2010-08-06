
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/
  
#ifndef UT_INTERSECTION_H
#define UT_INTERSECTION_H

#include "ML_Triangle.h"
#include "ML_Line.h"

struct utIntersectionResult
{
	utIntersectionResult() :
		lineLengthener(0.0f),
		intersectionPosition(mlVector3DZero),
		intersected(false)
		{}

	utIntersectionResult(
		mlFloat lineLengthenerv,
		const mlVector3D & intersectionPositionv) :
			lineLengthener(lineLengthenerv),
			intersectionPosition(intersectionPositionv),
			intersected(true)
		{}

	mlFloat		lineLengthener;
	mlVector3D	intersectionPosition;
	bool		intersected;
};

utIntersectionResult utIntersectionPosition(const mlLine & ray, const mlTriangle & plane);
utIntersectionResult utIntersectionPosition(const mlVector3D & rayPoint, const mlVector3D & rayVector, const mlTriangle & plane);

#endif // UT_INTERSECTION_H

