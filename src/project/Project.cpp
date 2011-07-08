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

	sliceThickness = 0.025;
	slotWidth = 0.010;
	supportDistance = 0.050;
	supportWidth = 0.005;
	supportHeight = 0.010;

	resolution = 0.0005;

	levelDrop = 0.005;

	freeHeightAboveMaterial = 0.010;

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

	if(displayToolpath){
		for(i = 0; i < toolpath.GetCount(); i++)
			toolpath[i].Paint();
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
	Target temp3;

	AffineTransformMatrix shift;

	Object* obj = &(objects[activeObject]);
	obj->UpdateBoundingBox();

	temp.SetupBox(obj->bbox.xmax + 4 * slotWidth, obj->bbox.ymax + 4
			* slotWidth, sliceThickness, resolution, resolution);

	size_t i, n;
	n = ceil(obj->bbox.zmax / sliceThickness);

	Target sphereSurfaceOffset;
	Target discSlot;
	Target discTool;

	sphereSurfaceOffset.SetupSphere(0.003, resolution, resolution);
	discSlot.SetupCylinder(slotWidth, resolution, resolution);
	discTool.SetupDisc(0.003, resolution, resolution);

	sphereSurfaceOffset.matrix.TranslateGlobal(0, -0.1, 0);
	discSlot.matrix.TranslateGlobal(0.1, -0.1, 0);
	discTool.matrix.TranslateGlobal(0.2, -0.1, 0);
	targets.Add(sphereSurfaceOffset);
	targets.Add(discSlot);
	targets.Add(discTool);


	//temp.matrix.TranslateGlobal(slotWidth, 0, 0);

	for(i = 1; i < 2; i++){

		shift.SetIdentity();
		shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth, (double) i
				* -sliceThickness);

		temp.InsertObject(obj, shift);

		temp2 = temp;

		temp2.FoldRaise(&discSlot);

		temp2.GeneratePolygon(-1, -1);

		if(temp2.polygons.GetCount() > 0){
			temp2.PolygonSmooth(0);
			temp2.PolygonSmooth(0);
			temp2.PolygonSmooth(0);
		}

		//temp2.matrix.TranslateGlobal(obj->bbox.xmax + slotWidth * 2, 0, 0);
		//targets.Add(temp2);

		//		temp = temp2;
		temp2.HardInvert();

		temp += temp2;
		temp.polygons = temp2.polygons;
		if(temp.polygons.GetCount() > 0){
			//			temp3 = temp;
			//			temp3.InitImprinting(); // == Clear();
			//			temp3.polygons = temp.polygons;

			temp.AddSupport(0, supportDistance, supportHeight, supportWidth,
					slotWidth);
			//			temp3.matrix.SetIdentity();
			//			temp3.matrix.TranslateGlobal((4 * slotWidth + obj->bbox.xmax), 0, 0);
			//			targets.Add(temp3);

		}

		//temp.matrix.SetIdentity();
		//temp.matrix.TranslateGlobal((4* slotWidth + obj->bbox.xmax) * i, 0, 0);

		temp.polygons.Clear();

		targets.Add(temp);

		GenerateToolpath(targets.GetCount() - 1);


		//temp.FoldRaise(&sphere);
		//temp.Limit();

		//temp.matrix.TranslateGlobal(obj->bbox.xmax + slotWidth * 2, 0, 0);

	}

	objects[0].geometries[0].matrix.TranslateGlobal(0, -0.35, 0);
	stock.stockMaterials[0].matrix.TranslateGlobal(0, 0.35, 0);
}

void Project::GenerateToolpath(size_t nrTarget)
{
	Target t;
	ToolPath temp;
	MachinePosition m;

	Target discTool;
	discTool.SetupDisc(0.003, resolution, resolution);

	t = targets[nrTarget];

	t.FoldRaise(&discTool);
	t.Limit();
	t.InvertTop();

	double level = t.GetSizeZ() - 0.00015;


	// Starting point
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = t.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;
	temp.positions.Add(m);

	while(level > 0.0){

		bool flag;
		t.polygons.Clear();
		flag = true;
		while(flag){
			flag = t.GeneratePolygon(-1, -1, level);
			if(flag){
				t.PolygonDiminish(t.polygons.GetCount() - 1, t.GetSizeRX());
				t.PolygonDrop(t.polygons.GetCount() - 1, levelDrop);
				t.PolygonSmooth(t.polygons.GetCount() - 1);
				t.PolygonDropTarget(t.polygons.GetCount() - 1, &discTool);
			}
		}

		size_t j;
		int i;
		for(i = t.polygons.GetCount() - 1; i >= 0; i--){
			if(t.polygons[i].elements.GetCount() > 0){
				// Starting point
				m.axisX = t.polygons[i].elements[0].x;
				m.axisY = t.polygons[i].elements[0].y;
				m.axisZ = t.GetSizeZ() + freeHeightAboveMaterial;
				m.isCutting = false;
				temp.positions.Add(m);
				m.isCutting = true;

				for(j = 1; j < t.polygons[i].elements.GetCount(); j++){
					m.axisX = t.polygons[i].elements[j].x;
					m.axisY = t.polygons[i].elements[j].y;
					m.axisZ = t.polygons[i].elements[j].z;
					temp.positions.Add(m);
				}
				m.isCutting = false;
				m.axisZ = t.GetSizeZ() + freeHeightAboveMaterial;
				temp.positions.Add(m);
			}
		}
		t.polygons.Clear();

		level -= levelDrop;
	}

	// Starting point
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = t.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;
	temp.positions.Add(m);


	//	t.InitImprinting();
	//	t.matrix.SetIdentity();
	//t.matrix.TranslateGlobal(t.GetSizeX(), 0, 0);
	//targets.Add(t);

	toolpath.Add(temp);

}

