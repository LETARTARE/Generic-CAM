
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "Vertex.h"
#include "VertexSet.h"

#include <stdio.h>

int Vertex::UNKNOWN = 1;
int Vertex::INSIDE = 2;
int Vertex::OUTSIDE = 3;
int Vertex::BOUNDARY = 4;

double Vertex::TOL = 1e-5f;

int g_nMaxAdjacentVertices = 50;
//int g_nMaxAdjacentVertices = 10;

Vertex::Vertex()
{
	x = 0;
	y = 0;
	z = 0;

	// oops - nothing here
	adjacentVertices = new VertexPointerSet(g_nMaxAdjacentVertices);
	status = UNKNOWN;
	// ahhh thats better
}
/*
Vertex::Vertex(Vertex & otherVertex)
{
	x = 0;
	y = 0;
	z = 0;

	// oops - nothing here
	adjacentVertices = new VertexPointerSet(g_nMaxAdjacentVertices);
	status = UNKNOWN;
	// ahhh thats better
}
*/
Vertex & Vertex::operator=(const Vertex & v)
{
	// deepfuck the sister
	for(int i = 0; i < v.adjacentVertices->length; i++)
	{
		adjacentVertices->add(v.adjacentVertices->GetVertexPtr(i));
	}

	status = v.status;
	color = v.color;
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vertex::Vertex(const mlVector3D & position, const gxColor & colori)
{
	color.red = colori.red;
	color.green = colori.green;
	color.blue = colori.blue;
	color.alpha = colori.alpha;
	
	x = position.x;
	y = position.y;
	z = position.z;
	
	adjacentVertices = new VertexPointerSet(10);
	status = UNKNOWN;
}

Vertex::Vertex(const mlVector3D & position, const gxColor & colori, int status)
{
	color.red = colori.red;
	color.green = colori.green;
	color.blue = colori.blue;
	color.alpha = colori.alpha;
	
	x = position.x;
	y = position.y;
	z = position.z;
	
	adjacentVertices = new VertexPointerSet(10);
	this->status = status;
}

Vertex::Vertex(float x, float y, float z, const gxColor & colori)
{
	color.red = colori.red;
	color.green = colori.green;
	color.blue = colori.blue;
	color.alpha = colori.alpha;
	
	this->x = x;
	this->y = y;
	this->z = z;
	
	adjacentVertices = new VertexPointerSet(10);
	status = UNKNOWN;
}

Vertex::Vertex(float x, float y, float z, const gxColor & colori, int status)
{
	color.red = colori.red;
	color.green = colori.green;
	color.blue = colori.blue;
	color.alpha = colori.alpha;
	
	this->x = x;
	this->y = y;
	this->z = z;
	
	adjacentVertices = new VertexPointerSet(10);
	this->status = status;
}

Vertex::~Vertex()
{
	//printf("Deleting adjacent vertices\n");
	delete adjacentVertices;
}

//
////-----------------------------------OVERRIDES----------------------------------//
//
///**
// * Clones the vertex object
// * 
// * @return cloned vertex object
// */
//public Object clone()
//{
//	try
//	{
//		Vertex clone = (Vertex)super.clone();
//		clone.x = x;
//		clone.y = y;
//		clone.z = z;
//		clone.color = (Color3f)color.clone();
//		clone.status = status;
//		clone.adjacentVertices = new ArrayList();
//		for(int i=0;i<adjacentVertices.size();i++)
//		{
//			clone.adjacentVertices.add(((Vertex)adjacentVertices.get(i)).clone());								 
//		}
//		
//		return clone;
//	}
//	catch(CloneNotSupportedException e)
//	{	
//		return null;
//	}
//}
//
///**
// * Makes a string definition for the Vertex object
// * 
// * @return the string definition
// */
//public String toString()
//{
//	return "("+x+", "+y+", "+z+")";
//}
//
///**
// * Checks if an vertex is equal to another. To be equal, they have to have the same
// * coordinates(with some tolerance) and color
// * 
// * @param anObject the other vertex to be tested
// * @return true if they are equal, false otherwise. 
// */

// Switching to a pointer, because the parameter for this seems to always be the vertex member variable of a Face.
bool Vertex::equals(Vertex * vertex)
{
	// Doesn't seem to worry about the color or adjacent vertices.

	bool bPositionMatch = (mlFabs(x-vertex->x)<TOL && mlFabs(y-vertex->y)<TOL && mlFabs(z-vertex->z)<TOL);
	bool bColorMatch = (color.red == vertex->color.red) && (color.green == vertex->color.green) && (color.blue == vertex->color.blue) && (color.alpha == vertex->color.alpha);

	return bPositionMatch && bColorMatch;
}

void Vertex::setStatus(int status)
{
	if(status>=UNKNOWN && status<=BOUNDARY)
	{
		this->status = status;
	}
}

mlVector3D Vertex::getPosition()
{
	return mlVector3D(x, y, z);
} 

VertexPointerSet * Vertex::getAdjacentVertices()
{
	return adjacentVertices;
	// No need to return a new copy of the pointer set????
}


int Vertex::getStatus()
{
	return status;
}

gxColor Vertex::getColor()
{
	return color;
}

void Vertex::addAdjacentVertex(Vertex * adjacentVertex)
{
	// Call add on adjacentVertices
	bool bAlready = false;
	for(int i = 0; i < adjacentVertices->GetNumVertexPointers(); i++)
	{
		Vertex * pVertexI = adjacentVertices->GetVertexPtr(i);
		if(pVertexI == adjacentVertex)
		{
			bAlready = true;
		}
	}

	if(!bAlready)
	{
		adjacentVertices->AddVertexPointer(adjacentVertex);
	}
}

void Vertex::mark(int status)
{
	this->status = status;

	//return;

	for(int i = 0; i < adjacentVertices->GetNumVertexPointers(); i++)
	{
		Vertex * pVertexI = adjacentVertices->GetVertexPtr(i);

		if(pVertexI->getStatus()==Vertex::UNKNOWN)
		{
			pVertexI->mark(status);
		}
	}
}
