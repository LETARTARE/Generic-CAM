/*
 * Control3D.h
 *
 *  Created on: 01.12.2009
 *      Author: toby
 */

#ifndef CONTROL3D_H_
#define CONTROL3D_H_

#include "Control6DOF.h"
#include <wx/config.h>

class Control3D {
	// Constructor / Destructor
public:
	Control3D();
	virtual ~Control3D();

	// Member  variables
protected:
	Control6DOF* controller;
private:


	// Methods
public:
	bool Open(wxString connection);
	bool Open(void);
	void Close();
	bool IsOpen();

	bool SetType(char id);
	char GetType();

	int GetButton(unsigned char i) ;
	int GetAxis(unsigned char i) ;
	wxString GetPort();
	bool SetPort(wxString port);
	bool GetConfigFrom(wxConfig *config);
	bool WriteConfigTo(wxConfig *config);

	bool Pump();

};

#endif /* CONTROL3D_H_ */
