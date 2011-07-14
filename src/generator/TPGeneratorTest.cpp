///////////////////////////////////////////////////////////////////////////////
// Name               : TPGeneratorTest.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.07.2011
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


#include "TPGeneratorTest.h"

TPGeneratorTest::TPGeneratorTest()
{
	slotWidth = 0.010;
	supportDistance = 0.050;
	supportHeight = 0.005;
	supportWidth = 0.005;

	freeHeightAboveMaterial = 0.002;

	levelDrop = 0.005;
}

TPGeneratorTest::~TPGeneratorTest()
{

}

void TPGeneratorTest::SetupSlot(double slotWidth, double supportDistance,
		double supportWidth, double supportHeight)
{
	this->slotWidth = slotWidth;
	this->supportDistance = supportDistance;
	this->supportWidth = supportWidth;
	this->supportHeight = supportHeight;

}

void TPGeneratorTest::GenerateToolpath(Target &target, Object &obj, Tool &tool)
{
	ToolPath tp;
	MachinePosition m;


	// TODO: Change this to reflect tool shape.
	Target discTool;
	discTool.SetupDisc(0.003, target.GetSizeRX(), target.GetSizeRY());

	Target discSlot;
	discSlot.SetupCylinder(slotWidth, target.GetSizeRX(), target.GetSizeRY());

	obj.UpdateBoundingBox();
	target.SetupBox(obj.bbox.xmax + 4 * slotWidth, obj.bbox.ymax + 4
			* slotWidth, target.GetSizeZ(), target.GetSizeRX(),
			target.GetSizeRY());

	target.InsertObject(obj, target.shift);

	Target temp = target;

	target.FoldRaise(discSlot);

	Polygon3 outline = target.GeneratePolygon(-1, -1);

	target.HardInvert();
	target += temp;

	target.AddSupport(outline, supportDistance, supportHeight, supportWidth,
			slotWidth);

	target.FoldRaise(discTool);
	target.Limit();
	target.InvertTop();

	double level = temp.GetSizeZ() - 0.00015;


	// Starting point
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = target.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;
	tp.positions.Add(m);

	ArrayOfPolygon3 pgs;
	Polygon3 pg;

	while(level > 0.0){

		bool flag;
		flag = true;
		while(flag){
			pg = target.GeneratePolygon(-1, -1, level);
			if(pg.elements.GetCount() < 2) flag = false;
			if(flag){
				target.PolygonDrop(pg, levelDrop);
				target.PolygonSmooth(pg);
				target.PolygonDropTarget(pg, discTool);
				pgs.Add(pg);
			}
		}

		size_t j;
		int i;
		for(i = pgs.GetCount() - 1; i >= 0; i--){
			if(pgs[i].elements.GetCount() > 0){
				// Starting point
				m.axisX = pgs[i].elements[0].x;
				m.axisY = pgs[i].elements[0].y;
				m.axisZ = target.GetSizeZ() + freeHeightAboveMaterial;
				m.isCutting = false;
				tp.positions.Add(m);
				m.isCutting = true;

				for(j = 1; j < pgs[i].elements.GetCount(); j++){
					m.axisX = pgs[i].elements[j].x;
					m.axisY = pgs[i].elements[j].y;
					m.axisZ = pgs[i].elements[j].z;
					tp.positions.Add(m);
				}
				m.isCutting = false;
				m.axisZ = target.GetSizeZ() + freeHeightAboveMaterial;
				tp.positions.Add(m);
			}
		}
		pgs.Clear();
		level -= levelDrop;
	}

	// Starting point
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = target.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;
	tp.positions.Add(m);

	for(size_t i = 0; i < tp.positions.GetCount(); i++){
		tp.positions[i].axisZ -= target.GetSizeZ();
	}
	tp.matrix.TranslateGlobal(0, 0, target.GetSizeZ());


	//	t.InitImprinting();
	//	t.matrix.SetIdentity();
	//t.matrix.TranslateGlobal(t.GetSizeX(), 0, 0);
	//targets.Add(t);

	target.toolpath = tp;
}
