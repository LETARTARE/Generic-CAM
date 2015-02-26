///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorTest.cpp
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
///////////////////////////////////////////////////////////////////////////////

#include "GeneratorTest.h"

#include <math.h>
#include <wx/log.h>
#include <wx/wxchar.h>

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Polygon25.h"
#include "../3D/Vector3.h"
#include "../machine/MachinePosition.h"
#include "../project/Project.h"
#include "../project/ToolPath.h"
#include "DexelTarget.h"

GeneratorTest::GeneratorTest(Project * project, size_t runNr, size_t toolpathNr) :
		GeneratorDexel(project, runNr, toolpathNr)
{
	freeHeightAboveMaterial = 0.002;
	levelDrop = 0.020;
}

GeneratorTest::~GeneratorTest()
{

}

void GeneratorTest::CopyFrom(const Generator* other)
{
	GeneratorDexel::CopyFrom(other);
}

wxString GeneratorTest::GetName(void) const
{
	return _T("Test Generator (using Dexel)");
}

void GeneratorTest::AddToPanel(wxPanel* panel, DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);
}

void GeneratorTest::TransferDataToPanel(void) const
{
}

void GeneratorTest::TransferDataFromPanel(void)
{
}

wxString GeneratorTest::ToString(void) const
{
	return _T("");
}

void GeneratorTest::FromString(const wxString& text)
{
}

void GeneratorTest::GenerateToolpath()
{
	output.Empty();

	size_t slotNr = project->run[runNr].toolpaths[toolpathNr].generator->slotNr;
	Tool * tool = project->run[runNr].toolbox.GetToolInSlot(slotNr);
	if(tool == NULL) output = _T("Tool empty.");

	ToolPath tp;
	MachinePosition m;

	GenerateTarget();

	if(target.IsEmpty()){
		output = _T("DexelTarget empty.");
		errorOccured = true;
		return;
	}

	// TODO: Change this to reflect tool shape.
	DexelTarget discTool;
	discTool.SetupDisc(0.003, target.GetSizeRX(), target.GetSizeRY());

	DexelTarget temp = target;
	DexelTarget temptop;

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
				temp.PolygonDropDexelTarget(pg, discTool);
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
					d2 = (m.axisX - pgs[i - 1].elements[0].x)
							* (m.axisX - pgs[i - 1].elements[0].x)
							+ (m.axisY - pgs[i - 1].elements[0].y)
									* (m.axisY - pgs[i - 1].elements[0].y);
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
		// Move tool out of material
		m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
		m.isCutting = false;
		isMillUp = true;
		tp.positions.Add(m);
		wxLogMessage(wxString::Format(_T("Next Level: %.3f m"), level));
	}

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
