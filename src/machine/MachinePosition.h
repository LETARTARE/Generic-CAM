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
	bool isRotationPositiv;

	float duration;

	float feed;

	wxString code;

	bool isCutting;

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


	MachinePosition & operator+=(const MachinePosition& a)
	{
		this->axisX += a.axisX;
		this->axisY += a.axisY;
		this->axisZ += a.axisZ;
		this->axisA += a.axisA;
		this->axisB += a.axisB;
		this->axisC += a.axisC;
		this->axisU += a.axisU;
		this->axisV += a.axisV;
		this->axisW += a.axisW;
		return *this;
	}

	const MachinePosition operator+(const MachinePosition &b) const
	{
		MachinePosition temp = *this;
		temp += b;
		return temp;
	}

	MachinePosition & operator-=(const MachinePosition& a)
	{
		this->axisX -= a.axisX;
		this->axisY -= a.axisY;
		this->axisZ -= a.axisZ;
		this->axisA -= a.axisA;
		this->axisB -= a.axisB;
		this->axisC -= a.axisC;
		this->axisU -= a.axisU;
		this->axisV -= a.axisV;
		this->axisW -= a.axisW;
		return *this;
	}

	const MachinePosition operator-(const MachinePosition &b) const
	{
		MachinePosition temp = *this;
		temp -= b;
		return temp;
	}

	const MachinePosition operator-() const
	{
		MachinePosition temp(-this->axisX, -this->axisY, -this->axisZ,
				-this->axisA, -this->axisB, -this->axisC, -this->axisU,
				-this->axisV, -this->axisW);
		return temp;
	}

	MachinePosition & operator*=(const float &b)
	{
		this->axisX *= b;
		this->axisY *= b;
		this->axisZ *= b;
		this->axisA *= b;
		this->axisB *= b;
		this->axisC *= b;
		this->axisU *= b;
		this->axisV *= b;
		this->axisW *= b;
		return *this;
	}

	const MachinePosition operator*(const float &b) const
	{
		MachinePosition temp = *this;
		temp *= b;
		return temp;
	}

	MachinePosition & operator/=(const float &b)
	{
		this->axisX /= b;
		this->axisY /= b;
		this->axisZ /= b;
		this->axisA /= b;
		this->axisB /= b;
		this->axisC /= b;
		this->axisU /= b;
		this->axisV /= b;
		this->axisW /= b;
		return *this;
	}

	const MachinePosition operator/(const float &b) const
	{
		MachinePosition temp = *this;
		temp /= b;
		return temp;
	}

	void Zero(void);
	float AbsXYZ() const;
	float AbsUVW() const;
	float AbsXYZUVW() const;

	bool ParseGCodeLine(wxString lineOfText);
	unsigned char GetGNumber(void) const;
	wxString GenerateCommandXYZ(void);
	wxString GenerateCommandXYZABC(void);
	wxString GenerateCommandXYZABCUVW(void);
	wxString GenerateCommandDiff(const MachinePosition &oldPosition);

};
WX_DECLARE_OBJARRAY(MachinePosition, ArrayOfMachinePosition)
;

#endif /* MACHINEPOSITION_H_ */
