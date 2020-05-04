///////////////////////////////////////////////////////////////////////////////
// Name               : CommandObjectTransform.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.12.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CommandObjectTransform.h"

#include "../Project.h"
#include <algorithm>

CommandObjectTransform::CommandObjectTransform(const wxString& name,
		Project* project, size_t ID, bool flipX, bool flipY, bool flipZ,
		bool flipNormals, const AffineTransformMatrix& matrixNew) :
		wxCommand(true, name)
{
	this->project = project;
	this->ID = ID;
	this->flipX = flipX;
	this->flipY = flipY;
	this->flipZ = flipZ;
	this->flipNormals = flipNormals;
	this->matrixNew = matrixNew;
}

bool CommandObjectTransform::Do(void)
{
	if(project == NULL) return false;
	std::vector <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), ID);
	if(it == project->objects.end()) return false;

	matrixOld = it->matrix;
	it->matrix = matrixNew;
	if(flipX) it->FlipX();
	if(flipY) it->FlipY();
	if(flipZ) it->FlipZ();
	if(flipNormals) it->FlipNormals();
//	project->objects[objectNr].Update();
	project->Modify(true);
	project->Update();
	return true;
}

bool CommandObjectTransform::Undo(void)
{
	if(project == NULL) return false;
	std::vector <Object>::iterator it;
	it = std::find(project->objects.begin(), project->objects.end(), ID);
	if(it == project->objects.end()) return false;
	it->matrix = matrixOld;
	if(flipX) it->FlipX();
	if(flipY) it->FlipY();
	if(flipZ) it->FlipZ();
	if(flipNormals) it->FlipNormals();
//	project->objects[objectNr].Update();
	project->Modify(true);
	project->Update();
	return true;
}
