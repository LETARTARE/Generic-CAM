//============================================================================
// Name        : MachineMotion.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 06.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "MachineMotion.h"

MachineMotion::MachineMotion()
{
	axisA = 0.0;
	axisB = 0.0;
	axisC = 0.0;
	axisU = 0.0;
	axisV = 0.0;
	axisW = 0.0;
	axisX = 0.0;
	axisY = 0.0;
	axisZ = 0.0;

	duration = 0.0;
}

MachineMotion::~MachineMotion()
{
}
