///////////////////////////////////////////////////////////////////////////////
// Name               : ControlSpaceMouse.h
// Purpose            : Class to get data from a Spaceball controller.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 31.01.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
