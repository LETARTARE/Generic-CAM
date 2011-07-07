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

	activeObject = 0;
	activeTarget = 0;
	activeStock = 0;

	displayGeometry = true;
	displayBoundingBox = false;
	displayMachine = false;
	displayStock = true;
	displayWorkpiece = false;
	displayTarget = true;

	Tolerance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	Distance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	RotationalSpeed.Setup(_T("1/s"), _T("rpm"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("mm/s"), (double) 1 / 1000);

	sliceThickness = 0.010;
	slotWidth = 0.010;
	supportDistance = 0.050;
	supportWidth = 0.010;
	supportHeight = 0.005;

}

Project::~Project()
{
}

void Project::Assemble(void)
{
	machine.Assemble();
	if(machine.IsInitialized()) stock.matrix = machine.workpiecePosition;

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

	if(displayTarget){
		for(i = 0; i < targets.GetCount(); i++)
			targets[i].Paint();
	}


	//if(displayWorkpiece) workpiece.Paint();
	//if(displayBoundingBox) bbox.Paint();
}

//bool Project::LoadObject(wxFileName)


void Project::GenerateTargets(void)
{
	targets.Clear();

	Target temp;
	Object* obj = &(objects[activeObject]);
	obj->UpdateBoundingBox();

	temp.SetupBox(obj->bbox.xmax, obj->bbox.ymax, sliceThickness);

	size_t i, n;
	n = ceil(obj->bbox.zmax / sliceThickness);

	temp.matrix.TranslateGlobal(slotWidth, 0, 0);
	for(i = 0; i < n; i++){


		temp.InsertObject(obj, (double) i * sliceThickness);
		temp.matrix.TranslateGlobal(slotWidth, 0, 0);
		targets.Add(temp);
		temp.matrix.TranslateGlobal(obj->bbox.xmax +slotWidth*2, 0, 0);

	}

	objects[0].geometries[0].matrix.TranslateGlobal(0,-0.35,0);
	stock.stockMaterials[0].matrix.TranslateGlobal(0, 0.35, 0);
}

