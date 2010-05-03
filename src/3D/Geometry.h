///////////////////////////////////////////////////////////////////////////////
// Name               : Geometry.h
// Purpose            : Class for managing 3D geometry data.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Vector3.h"
#include "AffineTransformMatrix.h"

#include <wx/string.h>
#include <wx/dynarray.h>
/*!\class Triangle
 * \brief Defines a simple triangle.
 *
 * Holds the data for a simple triangle. Three vertices with three normal vectors.
 */

class Triangle {
public:
	Triangle();
	virtual ~Triangle();
	Vector3 p[3]; //!< Position of vertices.
	Vector3 n[3]; //!< Normal vectors.
	void Paint(void) const;
	void CalculateNormal();
};
WX_DECLARE_OBJARRAY(Triangle, ArrayOfTriangles)
;
WX_DECLARE_OBJARRAY(Vector3, ArrayOfVectors)
;

/*!\class Geometry
 * \brief Contains geometric data.
 *
 * Data from STL and GTS files is stored within this class.
 */
class Geometry {
	// Constructor/ Destructor
public:
	Geometry();
	virtual ~Geometry();

	// Member variables
public:

private:
	AffineTransformMatrix m; //!< Transformation of the data.
	ArrayOfTriangles triangles; //!< The storage of the geometric data.

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
