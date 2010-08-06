
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/
  
#include "UT_Intersection.h"

#include "ML_Maths.h"

utIntersectionResult utIntersectionPosition(const mlLine & ray, const mlTriangle & plane)
{
	return utIntersectionPosition( ray.a, (ray.b - ray.a).Normalised(), plane);
}

utIntersectionResult utIntersectionPosition(const mlVector3D & rayPoint, const mlVector3D & rayVector, const mlTriangle & plane)
{
	mlVector3D planeNormal = plane.Normal().Normalised();
	
	mlFloat rayLengthTowardPlane = rayVector * planeNormal;

	//rayLengthTowardPlane = mlFabs(rayLengthTowardPlane);
	
	if(rayLengthTowardPlane == 0.0f)
	{
		return utIntersectionResult();
	}
	
	mlVector3D planePointToRay = plane.a - rayPoint;
	
	mlFloat distanceToPlane = planePointToRay * planeNormal;
	
	//distanceToPlane = mlFabs(distanceToPlane);

	mlFloat lineLengthener = distanceToPlane / rayLengthTowardPlane;
	
	return utIntersectionResult(lineLengthener, rayPoint + (rayVector * lineLengthener));
}
