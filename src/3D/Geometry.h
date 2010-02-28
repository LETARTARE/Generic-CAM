//============================================================================
// Name        : Geometry.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Vector3.h"

#include <wx/string.h>
#include <wx/dynarray.h>

class Triangle {
public:
	Triangle();
	virtual ~Triangle();
	Vector3 p[3];
	Vector3 n;
	void Paint(void);
	void CalculateNormal();
};

WX_DECLARE_OBJARRAY(Triangle, ArrayOfTriangles);


class Geometry {
	// Constructor/ Destructor
public:
	Geometry();
	virtual ~Geometry();

	// Member variables
public:
	ArrayOfTriangles triangles;

	// Methods
public:
	void Paint(void);
	bool ReadSTL(wxString fileName);
};

#endif /* GEOMETRY_H_ */
