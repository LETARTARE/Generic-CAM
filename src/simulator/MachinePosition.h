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

	float duration;

	// Methods
	MachinePosition operator+(const MachinePosition& a)
	{
		return MachinePosition(axisX + a.axisX, axisY + a.axisY, axisZ
				+ a.axisZ, axisA + a.axisA, axisB + a.axisB, axisC + a.axisC,
				axisU + a.axisU, axisV + a.axisV, axisW + a.axisW);
	}
	MachinePosition operator+=(const MachinePosition& a)
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
		return MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
				axisV, axisW);
	}
		MachinePosition operator-(const MachinePosition& a)
	{
		return MachinePosition(axisX - a.axisX, axisY - a.axisY, axisZ
				- a.axisZ, axisA - a.axisA, axisB - a.axisB, axisC - a.axisC,
				axisU - a.axisU, axisV - a.axisV, axisW - a.axisW);
	}
	MachinePosition operator-=(const MachinePosition& a)
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
		return MachinePosition(axisX, axisY, axisZ, axisA, axisB, axisC, axisU,
				axisV, axisW);
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
};

#endif /* MACHINEPOSITION_H_ */
