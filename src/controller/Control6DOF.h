/*
 * Control6DOF.h
 *
 *  Created on: 21.07.2009
 *      Author: toby
 */

#ifndef CONTROL6DOF_H_
#define CONTROL6DOF_H_

#define CONTROL6DOF_MAXBUTTONS	10

#include "SerialPort.h"
#include <wx/string.h>

class Control6DOF {


	// Constructor/Destructor
public:
	Control6DOF();
	virtual ~Control6DOF();

	// Member variables
public:
protected:
	Serial port;
	wxString connection;
	int Button[CONTROL6DOF_MAXBUTTONS];
	int Axis[6];

	// Methods
public:
	bool Open();
	void Close();
	void SetPort(wxString connection);
	wxString GetPort();
	bool IsConnected(){return port.IsOpen();}

	int GetButton(unsigned char i) const;
	int GetAxis(unsigned char i) const;
	bool Pump();

	virtual const unsigned char ReturnID()=0;
protected:
	virtual void InitDevice();
	virtual bool ProcessPacket() = 0;
	virtual void DataIn(unsigned char c)=0;

};


#include "ControlSpaceBall.h"
#include "ControlSpaceOrb.h"
#include "ControlSpaceMouse.h"

#endif /* CONTROL6DOF_H_ */
