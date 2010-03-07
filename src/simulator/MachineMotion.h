//============================================================================
// Name        : MachineMotion.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 06.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================
// (read "raw G-Code")

#ifndef MACHINEMOTION_H_
#define MACHINEMOTION_H_

class MachineMotion {
	// Constructor/ Destructor
public:
	MachineMotion();
	virtual ~MachineMotion();

	// Member variables
public:
	float axisA;
	float axisB;
	float axisC;
	float axisU;
	float axisV;
	float axisW;
	float axisX;
	float axisY;
	float axisZ;

	float duration;

	// Methods

};

#endif /* MACHINEMOTION_H_ */
