
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "Bound.h"

#include "VectorSet.h"

// Complete.

//double Bound::TOL = 1e-10f;
double Bound::TOL = 1e-5f;

Bound::Bound(const mlVector3D & p1, const mlVector3D & p2, const mlVector3D & p3)
{
	xMax = xMin = p1.x;
	yMax = yMin = p1.y;
	zMax = zMin = p1.z;

	checkVertex(p2);
	checkVertex(p3);
}

Bound::Bound(VectorSet * vertices)
{
	xMax = xMin = vertices->GetVector(0)->x;
	yMax = yMin = vertices->GetVector(0)->y;
	zMax = zMin = vertices->GetVector(0)->z;

	for(int i=1;i<vertices->GetSize();i++)
	{
		checkVertex(*(vertices->GetVector(i)));
	}
}

Bound::~Bound()
{
}

//public String toString()
//{
//	return "x: "+xMin+" .. "+xMax+"\ny: "+yMin+" .. "+yMax+"\nz: "+zMin+" .. "+zMax;
//}

// What about (for fun) intersecting 2 bounds??

bool Bound::overlap(Bound  bound)
{
	if((xMin>bound.xMax+TOL)||(xMax<bound.xMin-TOL)||(yMin>bound.yMax+TOL)||(yMax<bound.yMin-TOL)||(zMin>bound.zMax+TOL)||(zMax<bound.zMin-TOL))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Bound::checkVertex(const mlVector3D & vertex)
{
	if(vertex.x>xMax)
	{
		xMax = vertex.x;
	}
	else if(vertex.x<xMin)
	{
		xMin = vertex.x;
	}

	if(vertex.y>yMax)
	{
		yMax = vertex.y;
	}
	else if(vertex.y<yMin)
	{
		yMin = vertex.y;
	}

	if(vertex.z>zMax)
	{
		zMax = vertex.z;
	}
	else if(vertex.z<zMin)
	{
		zMin = vertex.z;
	}
}

