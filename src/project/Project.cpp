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
	displayToolpath = true;

	Tolerance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	Distance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	RotationalSpeed.Setup(_T("1/s"), _T("rpm"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("mm/s"), (double) 1 / 1000);

	slotWidth = 0.010;
	resolution = 0.0005;

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

	size_t i, n;
	n = ceil(obj->bbox.zmax / stock.stockMaterials[activeStock].z);

	Target discSlot;
	discSlot.SetupCylinder(slotWidth, stock.stockMaterials[activeStock].z,
			resolution, resolution);

	discSlot.matrix.TranslateGlobal(0.1, -0.1, 0);
	targets.Add(discSlot);

	for(i = 2; i < 3; i++){

		temp.SetupBox(obj->bbox.xmax + 4 * slotWidth, obj->bbox.ymax + 4
				* slotWidth, stock.stockMaterials[activeStock].z, resolution,
				resolution);

		temp.shift.SetIdentity();
		temp.shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth, (double) i
				* -stock.stockMaterials[activeStock].z);

		temp.InsertObject(*obj, temp.shift);
		temp.FoldRaise(discSlot);
		temp.outline = temp.GeneratePolygon(-1, -1);
		temp.PolygonSmooth(temp.outline);
		temp.PolygonSmooth(temp.outline);
		temp.PolygonSmooth(temp.outline);


		//temp.ClearField();

		if(temp.outline.elements.GetCount() >= 2){

			ToolPathGenerator.GenerateToolpath(temp, *obj, toolbox.tools[0]);
			targets.Add(temp);

		}

	}

	displayGeometry = false;
	displayStock = false;

}

