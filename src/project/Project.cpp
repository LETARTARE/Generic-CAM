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
	StockMaterial temp;
	stock.Add(temp);

	displayGeometry = true;
	displayBoundingBox = true;
	displayMachine = true;
	displayStock = true;

}

Project::~Project()
{
}

void Project::RegenerateBoundingBox(void)
{
	size_t i;
	bbox.Reset();
	for(i = 0; i < geometry.GetCount(); i++){
		bbox.Insert((geometry[i]));
	}
}

void Project::Assemble(void)
{
	machine.Assemble();
	if(machine.IsInitialized())
	{
		stock[selectedStock].matrix=machine.workpiecePosition;
	}
}


void Project::Paint(void)
{
	size_t i;
	if(displayGeometry){
		for(i = 0; i < geometry.GetCount(); i++)
			geometry[i].Paint();
	}
	if(displayMachine) machine.Paint();
	if(displayStock) stock[selectedStock].Paint();
	if(displayBoundingBox) bbox.Paint();
}
