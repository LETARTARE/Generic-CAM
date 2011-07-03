///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "Project.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfProject)

#include <GL/gl.h>

Project::Project()
{
	modified = false;
	projectName = _("Untitled");


	displayGeometry = true;
	displayBoundingBox = false;
	displayMachine = false;
	displayStock = false;
	displayWorkpiece = false;


}

Project::~Project()
{
}


void Project::Assemble(void)
{
	machine.Assemble();
	if(machine.IsInitialized())
		stock.matrix = machine.workpiecePosition;

}

void Project::Paint(void)
{
	size_t i;
	if(displayGeometry){
		for(i = 0; i < objects.GetCount(); i++)
			objects[i].Paint();
	}
	if(displayMachine) machine.Paint();
	if(displayStock) stock.Paint();
	//if(displayWorkpiece) workpiece.Paint();
	//if(displayBoundingBox) bbox.Paint();
}


//bool Project::LoadObject(wxFileName)

