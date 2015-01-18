///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineDebugger.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogMachineDebugger.h"

DialogMachineDebugger::DialogMachineDebugger(wxWindow * parent,
		Project * project, DisplaySettings * settings) :
		GUIMachineDebugger(parent)
{
	this->project = project;
	this->settings = settings;
	machineControl = NULL;
}

bool DialogMachineDebugger::TransferDataToWindow(void)
{
	return false;
}

bool DialogMachineDebugger::TransferDataFromWindow(void)
{
	return false;
}

void DialogMachineDebugger::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	machineControl->Show(false);
	this->Show(false);
}

void DialogMachineDebugger::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	machineControl->Show(false);
	this->Show(false);
}

void DialogMachineDebugger::OnMachineRestart(wxCommandEvent& event)
{
}

void DialogMachineDebugger::OnShowController(wxCommandEvent& event)
{
	if(machineControl == NULL) machineControl = new DialogMachineControl(this,
			settings);
	machineControl->Show();
	machineControl->TransferDataToWindow();
}

void DialogMachineDebugger::OnRestart(wxCommandEvent& event)
{
}
