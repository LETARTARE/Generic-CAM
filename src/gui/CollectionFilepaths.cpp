///////////////////////////////////////////////////////////////////////////////
// Name               : CollectionFilepaths.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.02.2019
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

#include "CollectionFilepaths.h"

CollectionFilepaths::CollectionFilepaths()
{
}

CollectionFilepaths::~CollectionFilepaths()
{
}

bool CollectionFilepaths::Load(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	wxString cwd = wxFileName::GetCwd();
	config->Read(_T("LastProjectDirectory"), &lastProjectDirectory, cwd);
	config->Read(_T("LastObjectDirectory"), &lastObjectDirectory, cwd);
	config->Read(_T("LastMachineDirectory"), &lastMachineDirectory, cwd);
	config->Read(_T("LastStockDirectory"), &lastStockDirectory, cwd);
	config->Read(_T("LastToolboxDirectory"), &lastToolboxDirectory, cwd);
	config->Read(_T("LastToolpathDirectory"), &lastToolpathDirectory, cwd);

	return true;
}

bool CollectionFilepaths::Save(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	config->Write(_T("LastProjectDirectory"), lastProjectDirectory);
	config->Write(_T("LastObjectDirectory"), lastObjectDirectory);
	config->Write(_T("LastMachineDirectory"), lastMachineDirectory);
	config->Write(_T("LastStockDirectory"), lastStockDirectory);
	config->Write(_T("LastToolboxDirectory"), lastToolboxDirectory);
	config->Write(_T("LastToolpathDirectory"), lastToolpathDirectory);

	return true;
}
