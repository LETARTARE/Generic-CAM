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
	Target temp2;
	AffineTransformMatrix shift;

	Object* obj = &(objects[activeObject]);
	obj->UpdateBoundingBox();

	temp.SetupBox(obj->bbox.xmax + 4* slotWidth ,
			obj->bbox.ymax + 4* slotWidth , sliceThickness, resolution,
			resolution);

	size_t i, n;
	n = ceil(obj->bbox.zmax / sliceThickness);

	Target sphere;
	Target cylinder;
	Target disc;

	sphere.SetupSphere(0.003, resolution, resolution);
	cylinder.SetupCylinder(slotWidth, sliceThickness, resolution, resolution);
	disc.SetupDisc(0.003, resolution, resolution);

	sphere.matrix.TranslateGlobal(0, -0.1, 0);
	cylinder.matrix.TranslateGlobal(0.1, -0.1, 0);
	disc.matrix.TranslateGlobal(0.2, -0.1, 0);
	targets.Add(sphere);
	targets.Add(cylinder);
	targets.Add(disc);


	//temp.matrix.TranslateGlobal(slotWidth, 0, 0);

	for(i = 2; i < 3; i++){

		shift.SetIdentity();
		shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth, (double) i
				* -sliceThickness);

		temp.InsertObject(obj, shift);
		temp2 = temp;
		temp2.FoldReplace(&cylinder);
		temp2.HardInvert();

		temp.GeneratePolygon(-1, -1, 20.0 / 1000);

		temp += temp2;

		temp.matrix.SetIdentity();
		temp.matrix.TranslateGlobal((4* slotWidth + obj->bbox.xmax) * i, 0, 0);

		targets.Add(temp);


		//temp.FoldRaise(&sphere);
		//temp.Limit();

		//temp.matrix.TranslateGlobal(obj->bbox.xmax + slotWidth * 2, 0, 0);

	}

	objects[0].geometries[0].matrix.TranslateGlobal(0, -0.35, 0);
	stock.stockMaterials[0].matrix.TranslateGlobal(0, 0.35, 0);
}

