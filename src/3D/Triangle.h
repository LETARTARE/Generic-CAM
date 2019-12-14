///////////////////////////////////////////////////////////////////////////////
// Name               : Triangle.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
///////////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

/*!\class Triangle
 * \ingroup Base3D
 * \brief Simple triangle
 *
 * Holds the data for a simple triangle. Three vertices with three normal vectors.
 */

#include "Vector3.h"

#include <wx/string.h>

class AffineTransformMatrix;

class Triangle {
	// Constructor/Destructor:
public:
	Triangle();
	Triangle(wxString string);

	//Member variables:
	Vector3 p[3]; //!< Position of vertices.
	Vector3 n[3]; //!< Normal vectors.
	Vector3 c[3]; //!< Color vectors.

	//Methods:
	wxString ToString(void) const;
	void FromString(wxString const &string);

	void Paint(bool useNormals = true, bool useColors = false) const;
	void CalculateNormal();
	void ApplyTransformation(const AffineTransformMatrix &matrix);

};

#endif /* TRIANGLE_H_ */
