
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef VERTEX_H
#define VERTEX_H

#include "ML_Vector.h"
#include "GX_Color.h"

class VertexPointerSet;

class Vertex
{
public:

	float x;
	float y;
	float z;

	gxColor color;

	// Replace these with the static ints
	//enum Status
	//{
	//	UNKNOWN,
	//	INSIDE,
	//	OUTSIDE,
	//	BOUNDARY
	//};

	static int UNKNOWN;
	static int INSIDE;
	static int OUTSIDE;
	static int BOUNDARY;

	int status;

	static double TOL;

	Vertex();

//@@	Vertex(Vertex & otherVertex);
		
	Vertex(const mlVector3D & position, const gxColor & color);
	Vertex(const mlVector3D & position, const gxColor & color, int eStatus);
	
	Vertex(float x, float y, float z, const gxColor & color);
	Vertex(float x, float y, float z, const gxColor & color, int eStatus);

	virtual ~Vertex();
	
	//String toString();
	bool equals(Vertex * vertex);
		
	void setStatus(int eStatus);
	mlVector3D getPosition();
	VertexPointerSet * getAdjacentVertices();
	
	int getStatus();

	gxColor getColor();

	void addAdjacentVertex(Vertex * adjacentVertex);

	void mark(int eStatus);

	Vertex & operator=(const Vertex & v);

private:

	VertexPointerSet * adjacentVertices;
};

#endif // VERTEX_H
