///////////////////////////////////////////////////////////////////////////////
// Name               : commandObjectTransform.cpp
// Purpose            : 
// Thread Safe        : Yes
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

#include "commandObjectTransform.h"

commandObjectTransform::commandObjectTransform(const wxString& name,
		Project* project, size_t objectNr, bool flipX, bool flipY, bool flipZ,
		bool flipNormals, AffineTransformMatrix& matrixNew) :
		wxCommand(true, name)
{
	this->project = project;
	this->objectNr = objectNr;
	this->flipX = flipX;
	this->flipY = flipY;
	this->flipZ = flipZ;
	this->flipNormals = flipNormals;
	this->matrixNew = matrixNew;
}

bool commandObjectTransform::Do(void)
{
	if(objectNr >= project->objects.GetCount()) return false;
	matrixOld = project->objects[objectNr].matrix;
	project->objects[objectNr].matrix = matrixNew;
	if(flipX) project->objects[objectNr].FlipX();
	if(flipY) project->objects[objectNr].FlipY();
	if(flipZ) project->objects[objectNr].FlipZ();
	if(flipNormals) project->objects[objectNr].FlipNormals();
	project->objects[objectNr].Update();
	return true;
}

bool commandObjectTransform::Undo(void)
{
	if(objectNr >= project->objects.GetCount()) return false;
	project->objects[objectNr].matrix = matrixOld;
	if(flipX) project->objects[objectNr].FlipX();
	if(flipY) project->objects[objectNr].FlipY();
	if(flipZ) project->objects[objectNr].FlipZ();
	if(flipNormals) project->objects[objectNr].FlipNormals();
	project->objects[objectNr].Update();
	return true;
}
