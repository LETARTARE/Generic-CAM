//============================================================================
// Name        : MachinePosition.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 08.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef MACHINEPOSITION_H_
#define MACHINEPOSITION_H_

// C++ Operator Overloading Guidelines
// http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html

#include <wx/string.h>

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

#endif /* MACHINEPOSITION_H_ */
