///////////////////////////////////////////////////////////////////////////////
// Name               : MachinePosition.h
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#ifndef MACHINEPOSITION_H_
#define MACHINEPOSITION_H_

// C++ Operator Overloading Guidelines
// http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html

#include <wx/string.h>
#include <wx/dynarray.h>

class MachinePosition {
	// Constructor/ Destructor
public:
	MachinePosition(float x = 0.0, float y = 0.0, float z = 0.0, float a = 0.0,
			float b = 0.0, float c = 0.0, float u = 0.0, float v = 0.0,
			float w = 0.0);

	virtual ~MachinePosition();

	// Member variables
public:
	float axisX;
	float axisY;
	float axisZ;
	float axisA;
	float axisB;
	float axisC;
	float axisU;
	float axisV;
	float axisW;

	float radiusI;
	float radiusJ;
	float radiusK;

	float duration;

	float feed;

	wxString code;

	// Methods

	//TODO: Cleanup all the operator stuff.

	// This may be useful, if the class gets a pointer as a member variable.
	//	MachinePosition & operator=(const MachinePostion &a)
	//	{
	//		ASSERT(this != a); // Self assignment = error in program.
	//		// 1.  Deallocate any memory that MyClass is using internally
	//		// 2.  Allocate some memory to hold the contents of rhs
	//		// 3.  Copy the values from rhs into this instance
	//		// 4.  Return *this
	//		return *this;
	//	}


	const MachinePosition operator+(const MachinePosition& a) const
	{
		return MachinePosition(axisX + a.axisX, axisY + a.axisY, axisZ
				+ a.axisZ, axisA + a.axisA, axisB + a.axisB, axisC + a.axisC,
				axisU + a.axisU, axisV + a.axisV, axisW + a.axisW);
	}
	MachinePosition & operator+=(const MachinePosition& a)
	{
		axisX += a.axisX;
		axisY += a.axisY;
		axisZ += a.axisZ;
		axisA += a.axisA;
		axisB += a.axisB;
		axisC += a.axisC;
		axisU += a.axisU;
		axisV += a.axisV;
		axisW += a.axisW;
		return *this;
		//MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
		//	axisV, axisW);
	}
	MachinePosition operator-(const MachinePosition& a)
	{
		return MachinePosition(axisX - a.axisX, axisY - a.axisY, axisZ
				- a.axisZ, axisA - a.axisA, axisB - a.axisB, axisC - a.axisC,
				axisU - a.axisU, axisV - a.axisV, axisW - a.axisW);
	}
	MachinePosition & operator-=(const MachinePosition& a)
	{
		axisX -= a.axisX;
		axisY -= a.axisY;
		axisZ -= a.axisZ;
		axisA -= a.axisA;
		axisB -= a.axisB;
		axisC -= a.axisC;
		axisU -= a.axisU;
		axisV -= a.axisV;
		axisW -= a.axisW;
		return *this;
		//return MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
		//	axisV, axisW);
	}
	MachinePosition operator-()
	{
		return MachinePosition(-axisX, -axisY, -axisZ, -axisA, -axisB, -axisC,
				-axisU, -axisV, -axisW);
	}
	MachinePosition operator*(const float &b)
	{
		return MachinePosition(axisX * b, axisY * b, axisZ * b, axisA * b,
				axisB * b, axisC * b, axisU * b, axisV * b, axisW * b);
	}
	MachinePosition operator*=(const float &b)
	{
		axisX *= b;
		axisY *= b;
		axisZ *= b;
		axisA *= b;
		axisB *= b;
		axisC *= b;
		axisU *= b;
		axisV *= b;
		axisW *= b;
		return MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
				axisV, axisW);
	}
	MachinePosition operator/(const float &b)
	{
		return MachinePosition(axisX / b, axisY / b, axisZ / b, axisA / b,
				axisB / b, axisC / b, axisU / b, axisV / b, axisW / b);
	}
	MachinePosition operator/=(const float &b)
	{
		axisX /= b;
		axisY /= b;
		axisZ /= b;
		axisA /= b;
		axisB /= b;
		axisC /= b;
		axisU /= b;
		axisV /= b;
		axisW /= b;
		return MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
				axisV, axisW);
	}
	void Zero(void);
	float AbsXYZ() const;
	float AbsUVW() const;
	float AbsXYZUVW() const;

	bool ParseGCodeLine(wxString lineOfText);

};

WX_DECLARE_OBJARRAY(MachinePosition, ArrayOfMachinePosition)
;


#endif /* MACHINEPOSITION_H_ */
