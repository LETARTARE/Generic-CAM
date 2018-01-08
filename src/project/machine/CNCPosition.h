///////////////////////////////////////////////////////////////////////////////
// Name               : CNCPosition.h
// Purpose            : The position of the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.03.2010
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
///////////////////////////////////////////////////////////////////////////////
#ifndef CNCPOSITION_H_
#define CNCPOSITION_H_

/*!\class CNCPosition
 * \ingroup Machine
 * \ingroup CoordinateSystems
 * \brief 9-dimensional CNC coordinate system
 *
 * The state of the CNC machine are stored in the Machine itself. This class manages only
 * a coordinate system for a CNC machine.
 *
 * The animation of the transition between two states is done by the MachineSimulator.
 *
 * The transformations in this class especially the functions GetMatrix(), GetNormal() and
 * GetPosition() are the central points describing the transformations of tool and
 * workpiece.
 */

// C++ Operator Overloading Guidelines
// http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html
#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Vector3.h"

#include <wx/string.h>
#include <wx/dynarray.h>

class CNCPosition {
	// Constructor/ Destructor
public:
	CNCPosition(double x = 0.0, double y = 0.0, double z = 0.0, double a = 0.0,
			double b = 0.0, double c = 0.0, double u = 0.0, double v = 0.0,
			double w = 0.0);
	CNCPosition(const AffineTransformMatrix &matrix);
	virtual ~CNCPosition();

	// Member variables
public:
	double X; //!< X coordinate
	double Y; //!< Y coordinate
	double Z; //!< Z coordinate
	double A; //!< rotation around X coordinate
	double B; //!< rotation around Y coordinate
	double C; //!< rotation around Z coordinate
	double U; //!< axis parallel rotated X coordinate
	double V; //!< axis parallel rotated Y coordinate
	double W; //!< axis parallel rotated Z coordinate

	double dt; //!< Time taken to move to this position (optional, not directly manipulated by the functions of this class)
	double t; //!< Absolute time this position is reached (optional, not directly manipulated by the functions of this class)

	/*! \brief Overloaded operator to a positions to another
	 *
	 * Adds XYZ, ABC and UWV from the other position to this one.
	 */
	CNCPosition & operator+=(const CNCPosition& a);

	/*! \brief Overloaded operator to add two positions
	 *
	 * Returns the sum of XYZ, ABC and UWV from two positions.
	 */
	const CNCPosition operator+(const CNCPosition &b) const;

	/*! \brief Overloaded operator to a positions to another
	 *
	 * Adds XYZ, ABC and UWV from the other position to this one.
	 */
	CNCPosition & operator-=(const CNCPosition& a);
	const CNCPosition operator-(const CNCPosition &b) const;
	const CNCPosition operator-() const; //!< Inverts all components (XYZABCUWV).

	CNCPosition & operator*=(const double &b); //!< Multiply all components of the position by a factor
	const CNCPosition operator*(const double &b) const; //!< Multiply all components of the position by a factor

	CNCPosition & operator/=(const double &b); //!< Divide all components of the position by a factor
	const CNCPosition operator/(const double &b) const; //!< Divide all components of the position by a factor

	double AbsXYZ() const; //!< Return the length of the XYZ components
	double AbsABC() const; //!< Return the length of the ABC components
	double AbsUVW() const; //!< Return the length of the UVW components
	double AbsXYZUVW() const; //!< Return the length of the XYZUVW components

	Vector3 GetPosition(void) const; //!< Return the XYZ component of this position
	Vector3 GetNormal(void) const; //!< Return the normal vector for this position
	AffineTransformMatrix GetMatrix(void) const; //!< Return a transformation matrix for this position

};
WX_DECLARE_OBJARRAY(CNCPosition, ArrayOfCNCPosition);

#endif /* CNCPOSITION_H_ */
