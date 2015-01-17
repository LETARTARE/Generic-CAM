///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineControl.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.01.2015
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

#include "DialogMachineControl.h"

DialogMachineControl::DialogMachineControl(wxWindow* parent, Project * project,
		DisplaySettings * settings) :
		GUIMachineControl(parent)
{
	this->project = project;
	this->settings = settings;
}

void DialogMachineControl::OnClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogMachineControl::OnScroll(wxScrollEvent& event)
{
}

void DialogMachineControl::OnTrack(wxScrollEvent& event)
{
}

bool DialogMachineControl::TransferDataToWindow(void)
{
	return false;
}

bool DialogMachineControl::TransferDataFromWindow(void)
{
	return false;
}

void DialogMachineControl::OnTextChanged(wxCommandEvent& event)
{
}
