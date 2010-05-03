///////////////////////////////////////////////////////////////////////////////
// Name               : Control3DAbstract.h
// Purpose            : Abstract class for 6DOF controller classes.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#ifndef CONTROL3DABSTRACT_H_
#define CONTROL3DABSTRACT_H_

#define CONTROL3DABSTRACT_MAXBUTTONS	10

#include "SerialPort.h"
#include <wx/string.h>

class Control3DAbstract {


	// Constructor/Destructor
public:
	Control3DAbstract();
	virtual ~Control3DAbstract();

	// Member variables
public:
protected:
	SerialPort port;
	wxString connection;
	int Button[CONTROL3DABSTRACT_MAXBUTTONS];
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

#endif /* CONTROL3DABSTRACT_H_ */
