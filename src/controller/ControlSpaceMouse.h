/*
 * ControlSpaceMouse.h
 *
 *  Created on: 23.01.2010
 *      Author: toby
 */

#ifndef CONTROLSPACEMOUSE_H_
#define CONTROLSPACEMOUSE_H_

#include "Control3DAbstract.h"

#define CONTROLSPACEMOUSE_MAXDATALENGTH	256
#define CONTROLSPACEMOUSE_ID	3
class ControlSpaceMouse: public Control3DAbstract
{
	// Constructor / Destructor
public:
	ControlSpaceMouse();
	virtual ~ControlSpaceMouse();

	// Variables
private:
	unsigned char InBuffer[CONTROLSPACEMOUSE_MAXDATALENGTH];
	int idx;

	// Methods
public:
	virtual const unsigned char ReturnID(){return CONTROLSPACEMOUSE_ID;}
protected:

	virtual void InitDevice();
	virtual bool ProcessPacket();
	virtual void DataIn(unsigned char c);
};

#endif /* CONTROLSPACEMOUSE_H_ */
