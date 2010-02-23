// SpaceOrb.h: interface for the CSpaceOrb class.
// adapted from Linux Kernels spaceorb.c
//////////////////////////////////////////////////////////////////////

#ifndef _CONTROLSPACEORB_H_
#define _CONTROLSPACEORB_H_

#include "Control6DOF.h"

#define CONTROLSPACEORB_MAXDATALENGTH	64
#define CONTROLSPACEORB_ID 2
class ControlSpaceOrb:public Control6DOF {

	// Constructor /Destructor
public:

	ControlSpaceOrb();
	virtual ~ControlSpaceOrb();

	// Member variables

private:
	unsigned char Data[CONTROLSPACEORB_MAXDATALENGTH];
	int idx;

	// Methods
public:
	virtual const unsigned char ReturnID(){return CONTROLSPACEORB_ID ;}
protected:
	virtual void InitDevice();
	virtual bool ProcessPacket();
	virtual void DataIn(unsigned char c);

};

#endif // _CONTROLSPACEORB_H_
