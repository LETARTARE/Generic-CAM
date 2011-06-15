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
	SerialPort port; //< Serial port to 6-DOF controller
	wxString connection; //< Name of the connection /dev/ttyUSB, COM1, ...
	int Button[CONTROL3DABSTRACT_MAXBUTTONS]; //< Button states
	int Axis[6]; //< The six axes of the controller
	bool hasChanged; //< Indicates a change during the last pumping of data

	// Methods
public:
	///\brief Opens the connection to the serial port.
	bool Open();
	///\brief Closes the connection to the serial port.
	void Close();
	///\brief Sets a new port address
	void SetPort(wxString connection);
	///\brief Gets the port address
	wxString GetPort();
	///\brief Shows whether the connection is established.
	bool IsConnected()
	{
		return port.IsOpen();
	}
	///\brief Returns the state of a given button.
	int GetButton(unsigned char i) const;
	///\brief Returns the state of a given axis.
	int GetAxis(unsigned char i) const;
	///\brief Indicates a change during the last pumping of data.
	bool HasChanged()
	{
		return hasChanged;
	}

	///\brief Pumps data from the serial port to the packet analyser.
	bool Pump();

	///\brief Returns an ID for the given 6-DOF driver.
	virtual const unsigned char ReturnID() = 0;
protected:
	virtual void InitDevice();
	virtual bool ProcessPacket() = 0;
	virtual void DataIn(unsigned char c) = 0;

};

#include "ControlSpaceBall.h"
#include "ControlSpaceOrb.h"
#include "ControlSpaceMouse.h"

#endif /* CONTROL3DABSTRACT_H_ */
