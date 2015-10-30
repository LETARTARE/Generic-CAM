///////////////////////////////////////////////////////////////////////////////
// Name               : GeometryFileAbstract.h
// Purpose            : Abstract class for geometry loaded from a file
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

#ifndef GEOMETRYFILEABSTRACT_H_
#define GEOMETRYFILEABSTRACT_H_

#include "Geometry.h"
#include <wx/string.h>

/*!\class GeometryFileAbstract
 * \ingroup File3D
 * \brief Abstract class for 3D files
 */

class GeometryFileAbstract {
	// Constructor/ Destructor
public:
	GeometryFileAbstract();
	virtual ~GeometryFileAbstract();

	// Member variables
public:
	wxString filename; ///< Last read / written file
	AffineTransformMatrix matrix;
	ArrayOfGeometry geometry;
	wxString error; ///> Errorstring, empty if no errors occured
	Vector3 color; ///> Color of object, if no color is provided by the geometry itself.

	//Methods:
public:
	void Paint(void) const;
	virtual bool ReadFile(wxString fileName);
	virtual bool WriteFile(wxString fileName) const;
};

#endif /* GEOMETRYFILEABSTRACT_H_ */
