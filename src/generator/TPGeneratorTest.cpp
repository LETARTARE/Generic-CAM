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

#include <math.h>
#include <wx/log.h>

TPGeneratorTest::TPGeneratorTest()
{

	freeHeightAboveMaterial = 0.002;

	levelDrop = 0.005;
}

TPGeneratorTest::~TPGeneratorTest()
{

}

void TPGeneratorTest::GenerateToolpath(Target &target, Tool &tool)
{
	ToolPath tp;
	MachinePosition m;

	if(target.IsEmpty()) return;

	// TODO: Change this to reflect tool shape.
	Target discTool;
	discTool.SetupDisc(0.003, target.GetSizeRX(), target.GetSizeRY());

	Target temp = target;
	Target temptop;

	temp.FoldRaise(discTool);
	temp.Limit();
	temptop = temp;
	temp.InvertTop();

	double level = temp.GetSizeZ() - 0.0005;


	// Starting point
	//
	//	tp.positions.Add(m);

	// Position at start (! not a toolpath position)
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;

	ArrayOfPolygon25 pgs;
	Polygon25 pg;

	AffineTransformMatrix tm;
	tm.TranslateGlobal(0.0, 0.0, -0.0001);

	while(level > -0.0001){


		// Find All polygons on one level
		bool flag;
		flag = true;
		while(flag){
			pg = temp.GeneratePolygon(-1, -1, level);
			pg.ApplyTransformation(tm);
			if(pg.elements.GetCount() < 1) flag = false;
			if(pg.elements.GetCount() > 1){
				temptop.PolygonDrop(pg, levelDrop - 0.0005);
				pg.ApplyTransformation(tm);
				temp.PolygonDropTarget(pg, discTool);
				pg.PolygonSmooth();
				pgs.Add(pg);
			}
		}

		bool isMillUp = true;
		// Generate a toolpath from polygons
		size_t j;
		size_t i;
		double d2;
		for(i = pgs.GetCount(); i > 0; i--){
			if(pgs[i - 1].elements.GetCount() > 0){

				pgs[i - 1].RotatePolygonStart(m.axisX, m.axisY);

				if(!isMillUp){
					d2 = (m.axisX - pgs[i - 1].elements[0].x) * (m.axisX
							- pgs[i - 1].elements[0].x) + (m.axisY
							- pgs[i - 1].elements[0].y) * (m.axisY
							- pgs[i - 1].elements[0].y);
					if(d2 > (0.008 * 0.008)){
						// Move tool out of material to travel to next polygon.
						m.isCutting = false;
						m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
						tp.positions.Add(m);
						isMillUp = true;
					}
				}

				if(isMillUp){
					// Move tool into material
					m.axisX = pgs[i - 1].elements[0].x;
					m.axisY = pgs[i - 1].elements[0].y;
					m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
					m.isCutting = false;
					tp.positions.Add(m);
				}
				// Add polyg.positions[i].axisX,on
				m.isCutting = true;
				isMillUp = false;

				for(j = 0; j < pgs[i - 1].elements.GetCount(); j++){
					m.axisX = pgs[i - 1].elements[j].x;
					m.axisY = pgs[i - 1].elements[j].y;
					m.axisZ = pgs[i - 1].elements[j].z;
					tp.positions.Add(m);
				}

			}
		}
		pgs.Clear();
		level -= levelDrop;
		wxLogMessage(wxString::Format(_T("Next Level: %.3f m"), level));
	}

	// Move tool out of material
	m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
	m.isCutting = false;
	tp.positions.Add(m);


	// Shift toolpath down to align 0 with top-of-stock
	for(size_t i = 0; i < tp.positions.GetCount(); i++){
		tp.positions[i].axisZ -= temp.GetSizeZ();
	}
	tp.matrix.TranslateGlobal(0, 0, temp.GetSizeZ());


	//	t.InitImprinting();
	//	t.matrix.SetIdentity();
	//t.matrix.TranslateGlobal(t.GetSizeX(), 0, 0);
	//targets.Add(t);

	target.toolpath = tp;
}
