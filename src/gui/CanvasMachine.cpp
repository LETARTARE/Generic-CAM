///////////////////////////////////////////////////////////////////////////////
// Name               : CanvasMachine.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 21.12.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
#include "CanvasMachine.h"

CanvasMachine::CanvasMachine(wxWindow *parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style,
		const wxString& name) :
		OpenGLCanvas(parent, id, pos, size, style, name)
{
	machine = NULL;
}

CanvasMachine::~CanvasMachine()
{
}

void CanvasMachine::InsertMachine(Machine* machine)
{
	this->machine = machine;
}

void CanvasMachine::Render()
{
	if(machine == NULL) return;
	machine->Paint();
}
