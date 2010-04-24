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
#include "AffineTransformMatrix.h"

#include <wx/string.h>
#include <wx/dynarray.h>

class Triangle {
public:
	Triangle();
	virtual ~Triangle();
	Vector3 p[3];
	Vector3 n[1];
	void Paint(void);
	void CalculateNormal();
};
WX_DECLARE_OBJARRAY(Triangle, ArrayOfTriangles)
;
WX_DECLARE_OBJARRAY(Vector3, ArrayOfVectors)
;

class Geometry {
	// Constructor/ Destructor
public:
	Geometry();
	virtual ~Geometry();

	// Member variables
public:

private:
	ArrayOfTriangles triangles;

	// Methods
public:

	void ApplyTransformation(const AffineTransformMatrix &matrix);

	void AddTriangle(const AffineTransformMatrix &matrix, const Vector3 &a,
			const Vector3 &b, const Vector3 &c);
	void AddQuad(const AffineTransformMatrix &matrix, const Vector3 &a,
			const Vector3 &b, const Vector3 &c, const Vector3 &d);

	void Paint(void) const;

	bool ReadSTL(wxString fileName);
	bool ReadGTS(wxString fileName);
};

#endif /* GEOMETRY_H_ */
