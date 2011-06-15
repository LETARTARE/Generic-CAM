///////////////////////////////////////////////////////////////////////////////
// Name               : ControlSpaceOrb.h
// Purpose            : Class to get data from a Spaceorb controller.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Vojtech Pavlik
// Modified for C++   : Tobias Schaefer
// Adapted            : 21.07.2009
// Copyright          : (C) 1999-2001 Vojtech Pavlik <vojtech@ucw.cz>
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


#ifndef _CONTROLSPACEORB_H_
#define _CONTROLSPACEORB_H_

#include "Control3DAbstract.h"

#define CONTROLSPACEORB_MAXDATALENGTH	64
#define CONTROLSPACEORB_ID 2
class ControlSpaceOrb:public Control3DAbstract {


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
	virtual const unsigned char ReturnID()
	{
		return CONTROLSPACEORB_ID;
	}
protected:
	virtual void InitDevice();
	virtual bool ProcessPacket();
	virtual void DataIn(unsigned char c);

};

#endif // _CONTROLSPACEORB_H_
