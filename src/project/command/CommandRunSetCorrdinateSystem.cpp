///////////////////////////////////////////////////////////////////////////////
// Name               : CommandRunSetCorrdinateSystem.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.12.2019
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

#include "CommandRunSetCorrdinateSystem.h"

#include "../Project.h"

CommandRunSetCorrdinateSystem::CommandRunSetCorrdinateSystem(
		const wxString& name, Project* project, size_t runID, size_t axis,
		const Selection &selection) :
		wxCommand(true, name)
{
	this->project = project;
	this->runID = runID;
	this->newSelection = selection;
	this->axis = axis;
}

bool CommandRunSetCorrdinateSystem::Do(void)
{
	if(project == NULL) return false;
	if(!project->Has(Selection::Run, runID)) return false;
	switch(axis){
	case 0:
	{
		this->oldSelection = project->run[runID].coordX;
		project->run[runID].coordX = this->newSelection;
		break;
	}
	case 1:
	{
		this->oldSelection = project->run[runID].coordY;
		project->run[runID].coordY = this->newSelection;
		break;
	}
	case 2:
	{
		this->oldSelection = project->run[runID].coordZ;
		project->run[runID].coordZ = this->newSelection;
		break;
	}
	}
	project->Update();
	return true;
}

bool CommandRunSetCorrdinateSystem::Undo(void)
{
	if(project == NULL) return false;
	if(!project->Has(Selection::Run, runID)) return false;
	switch(axis){
	case 0:
	{
		project->run[runID].coordX = this->oldSelection;
		break;
	}
	case 1:
	{
		project->run[runID].coordY = this->oldSelection;
		break;
	}
	case 2:
	{
		project->run[runID].coordZ = this->oldSelection;
		break;
	}
	}
	project->Update();
	return true;
}