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
	MachinePosition(double x = 0.0, double y = 0.0, double z = 0.0, double a = 0.0,
			double b = 0.0, double c = 0.0, double u = 0.0, double v = 0.0,
			double w = 0.0);

	virtual ~MachinePosition();

	// Member variables
public:
	double axisX;
	double axisY;
	double axisZ;
	double axisA;
	double axisB;
	double axisC;
	double axisU;
	double axisV;
	double axisW;

	double radiusI;
	double radiusJ;
	double radiusK;
	double radiusR;
	bool isRotationPositiv;

	double duration;

	double feed;

	wxString code;

	bool isCutting;

	// Methods


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

	MachinePosition & operator*=(const double &b)
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

	const MachinePosition operator*(const double &b) const
	{
		MachinePosition temp = *this;
		temp *= b;
		return temp;
	}

	MachinePosition & operator/=(const double &b)
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

	const MachinePosition operator/(const double &b) const
	{
		MachinePosition temp = *this;
		temp /= b;
		return temp;
	}

	void Zero(void);
	double AbsXYZ() const;
	double AbsUVW() const;
	double AbsXYZUVW() const;

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
