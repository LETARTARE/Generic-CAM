///////////////////////////////////////////////////////////////////////////////
// Name               : Control3D.h
// Purpose            : Main class for 6DOF controller
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.12.2009
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
///////////////////////////////////////////////////////////////////////////////


#ifndef CONTROL3D_H_
#define CONTROL3D_H_

#include "Control3DAbstract.h"
#include <wx/config.h>

class Control3D {
	// Constructor / Destructor
public:
	Control3D();
	virtual ~Control3D();

	// Member  variables
protected:
	Control3DAbstract* controller;
private:


	// Methods
public:
	bool Open(wxString connection);
	bool Open(void);
	void Close(void);
	bool IsOpen(void);

	bool SetType(char id);
	char GetType(void);

	bool HasChanged(void);
	bool IsIdle(void);
	int GetButton(unsigned char i);
	int GetAxis(unsigned char i);
	wxString GetPort(void);
	bool SetPort(wxString port);
	bool Load(wxConfig *config);
	bool Save(wxConfig *config);

	bool Pump(void);

};

#endif /* CONTROL3D_H_ */
