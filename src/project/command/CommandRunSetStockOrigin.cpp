///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunSetStockOrigin.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.12.2019
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

#include "CommandRunSetStockOrigin.h"
#include <algorithm>

CommandRunSetStockOrigin::CommandRunSetStockOrigin(const wxString& name,
		Project* project, size_t runID, Vector3 relOrigin) :
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
	this->newOrigin = relOrigin;
}

bool CommandRunSetStockOrigin::Do(void)
{
	if(project == NULL) return false;
	std::list <Run>::iterator itRun;
	itRun = std::find(project->run.begin(), project->run.end(), runID);
	if(itRun == project->run.end()) return false;
	oldOrigin = itRun->stockorigin;
	itRun->stockorigin = newOrigin;
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandRunSetStockOrigin::Undo(void)
{
	if(project == NULL) return false;
	std::list <Run>::iterator itRun;
	itRun = std::find(project->run.begin(), project->run.end(), runID);
	if(itRun == project->run.end()) return false;
	itRun->stockorigin = oldOrigin;
	project->Modify(true);
	project->Update();
	return true;
}
