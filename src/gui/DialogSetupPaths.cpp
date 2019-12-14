///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupPaths.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogSetupPaths.h"

#include <cstdio>
DialogSetupPaths::DialogSetupPaths(wxWindow * parent,
		const CollectionFilepaths * collection) :
		GUISetupPaths(parent)
{
	m_dirPickerProjectDirectory->SetPath(collection->lastProjectDirectory);
	m_dirPickerObjectDirectory->SetPath(collection->lastObjectDirectory);
	m_dirPickerToolpathDirectory->SetPath(collection->lastToolpathDirectory);
	m_dirPickerToolboxDirectory->SetPath(collection->lastToolboxDirectory);
	m_dirPickerPostProcessorDirectory->SetPath(
			collection->lastPostProcessorDirectory);
	m_dirPickerMachineDirectory->SetPath(collection->lastMachineDirectory);
}

DialogSetupPaths::~DialogSetupPaths()
{
}

void DialogSetupPaths::OnClose(wxCommandEvent& event)
{
	EndModal(wxID_OK);
}
void DialogSetupPaths::UpdateCollection(CollectionFilepaths* collection) const
{
	collection->lastProjectDirectory = m_dirPickerProjectDirectory->GetPath();
	collection->lastObjectDirectory = m_dirPickerObjectDirectory->GetPath();
	collection->lastToolpathDirectory = m_dirPickerToolpathDirectory->GetPath();
	collection->lastToolboxDirectory = m_dirPickerToolboxDirectory->GetPath();
	collection->lastPostProcessorDirectory =
			m_dirPickerPostProcessorDirectory->GetPath();
	collection->lastMachineDirectory = m_dirPickerMachineDirectory->GetPath();
}

