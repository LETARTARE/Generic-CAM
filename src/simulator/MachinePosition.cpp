//============================================================================
// Name        : MachinePosition.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 08.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "MachinePosition.h"

MachinePosition::MachinePosition(float x, float y, float z, float a, float b,
		float c, float u, float v, float w)
{
	axisX = x;
	axisY = y;
	axisZ = z;
	axisA = a;
	axisB = b;
	axisC = c;
	axisU = u;
	axisV = v;
	axisW = w;

	duration = 5.0;
}

MachinePosition::~MachinePosition()
{
}

void MachinePosition::Zero(void)
{
	axisX = axisY = axisZ = 0.0;
	axisA = axisB = axisC = 0.0;
	axisU = axisV = axisW = 0.0;
}
