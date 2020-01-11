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

class CNCPosition {
	// Constructor/ Destructor
public:
	CNCPosition(double x = 0.0, double y = 0.0, double z = 0.0, double nx = 0.0,
			double ny = 0.0, double nz = 1.0);
	CNCPosition(const Vector3& position, const Vector3& normal);
	CNCPosition(const AffineTransformMatrix& matrix);
	void Set(double x, double y, double z, bool rapid = false);
	void Rapid(void);
	void FeedSpeed(void);
	virtual ~CNCPosition();

	// Member variables
public:
	int toolSlot;
	Vector3 position;
	Vector3 normal;
	double S; //!< Spindle speed in 1/s
	double F; //!< Feed in m/s
	bool rapid;
	std::string comment;
	bool circle;

	double dt; //!< Time taken to move to this position (optional, not directly manipulated by the functions of this class)
	double t; //!< Absolute time this position is reached (optional, not directly manipulated by the functions of this class)

	CNCPosition& operator+=(const Vector3& a);
	CNCPosition& operator-=(const Vector3& a);
	double Abs(const CNCPosition& b) const; //!< Distance the tooltip moved
	double Rotation(const CNCPosition& b) const; //!< Angle between two CNCPositions

	AffineTransformMatrix GetMatrix(void) const; //!< Return a transformation matrix for this position
};

#endif /* CNCPOSITION_H_ */
