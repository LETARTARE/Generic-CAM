///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceObjectTransform.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 30.01.2015
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

#include "CommandWorkpieceObjectTransform.h"

CommandWorkpieceObjectTransform::CommandWorkpieceObjectTransform(
		const wxString& name, Project* project, size_t workpieceNr,
		size_t placementNr, const AffineTransformMatrix& matrixNew, float x,
		float y) :
		wxCommand(true, name)
{
	this->project = project;
	this->workpieceNr = workpieceNr;
	this->placementNr = placementNr;
	this->matrixNew = matrixNew;
	this->newX = x;
	this->newY = y;
	this->oldX = 0;
	this->oldY = 0;
}

bool CommandWorkpieceObjectTransform::Do(void)
{
	if(workpieceNr >= project->workpieces.GetCount()) return false;
	if(placementNr >= project->workpieces[workpieceNr].placements.GetCount()) return false;
	matrixOld = project->workpieces[workpieceNr].placements[placementNr].matrix;
	oldX = project->workpieces[workpieceNr].placements[placementNr].cornerX;
	oldY = project->workpieces[workpieceNr].placements[placementNr].cornerY;
	project->workpieces[workpieceNr].placements[placementNr].matrix = matrixNew;
	project->workpieces[workpieceNr].placements[placementNr].cornerX = newX;
	project->workpieces[workpieceNr].placements[placementNr].cornerY = newY;
	project->workpieces[workpieceNr].Update();
	return true;
}

bool CommandWorkpieceObjectTransform::Undo(void)
{
	if(workpieceNr >= project->workpieces.GetCount()) return false;
	if(placementNr >= project->workpieces[workpieceNr].placements.GetCount()) return false;
	project->workpieces[workpieceNr].placements[placementNr].matrix = matrixOld;
	project->workpieces[workpieceNr].placements[placementNr].cornerX = oldX;
	project->workpieces[workpieceNr].placements[placementNr].cornerY = oldY;
	project->workpieces[workpieceNr].Update();
	return true;
}
