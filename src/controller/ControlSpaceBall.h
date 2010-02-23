
#ifndef _CONTROLSPACEBALL_H_
#define _CONTROLSPACEBALL_H_

#include "Control6DOF.h"

#define CONTROLSPACEBALL_MAXDATALENGTH	256
#define CONTROLSPACEBALL_ID	1
class ControlSpaceBall: public Control6DOF
{
	// Constructor / Destructor
public:
	ControlSpaceBall();
	virtual ~ControlSpaceBall();

	// Variables
private:
	unsigned char InBuffer[CONTROLSPACEBALL_MAXDATALENGTH];
	int idx;

	// Methods
public:
	virtual const unsigned char ReturnID(){return CONTROLSPACEBALL_ID;}
protected:

	virtual void InitDevice();
	virtual bool ProcessPacket();
	virtual void DataIn(unsigned char c);
};

#endif //_CONTROLSPACEBALL_H_
