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

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Polygon25.h"
#include "../../3D/Vector3.h"
#include "../machine/MachinePosition.h"
#include "../Project.h"
#include "../ToolPath.h"
#include "DexelTarget.h"

GeneratorTest::GeneratorTest()
{
}

GeneratorTest::~GeneratorTest()
{

}

void GeneratorTest::CopyParameterFrom(const Generator* other)
{
	GeneratorDexel::CopyParameterFrom(other);
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

void GeneratorTest::GenerateToolpath(void)
{
	output.Empty();
	const Run* const run = this->parent;
	assert(run != NULL);
	if(refTool >= run->tools.GetCount()){
		output = _T("Tool empty.");
		errorOccured = true;
		return;
	}
	GeneratorDexel::GenerateToolpath();
	const Tool* const tool = &(run->tools[refTool]);

	const double maxCutDepth = tool->GetCuttingDepth();

	const double tolerance = 0.0001; // 1/10 mm

	ToolPath tp;
	MachinePosition m;

	DexelTarget toolShape;
	toolShape.SetupTool(*tool, target.GetSizeRX(), target.GetSizeRY());

	toolShape.NegateZ();
	DexelTarget temp = target;
	temp.FoldRaise(toolShape);
	temp.Limit();
	toolShape.NegateZ();

	DexelTarget temptop = temp;
	temp.InvertTop();
	double level = temp.GetSizeZ(); // at upper surface

	// Position at start (! not a toolpath position)
	m.axisX = 0.0;
	m.axisY = 0.0;
	m.axisZ = temp.GetSizeZ() + freeHeight;
	m.isCutting = false;

	ArrayOfPolygon25 pgs;
	Polygon25 pg;

//	AffineTransformMatrix tm;
//	tm.TranslateGlobal(0.0, 0.0, -0.0001);

	while(level > -tolerance){
		double dropLevel = level - maxCutDepth;
		if(dropLevel < 0.0) dropLevel = 0.0;

		// Find all polygons on one level
		pg = temp.GeneratePolygon(-1, -1, level - tolerance);
		while(pg.elements.GetCount() > 0){
			temptop.PolygonDropOntoTarget(pg, dropLevel);
			temp.PolygonPunchThroughTarget(pg, dropLevel, toolShape);
			pg.PolygonSmooth();
			pgs.Add(pg);
			pg = temp.GeneratePolygon(-1, -1, level - tolerance);
		}

//		debug = temp;
//		debug.Empty();
//		debug.outLine = pgs[4];
//		for(size_t n = 0; n < debug.N; n++){
//			const double x = ((double) (n % debug.nx) + 0.5) * debug.rx;
//			const double y = ((double) (n / debug.nx) + 0.5) * debug.ry;
//			if(pgs[4].IsElementInside(Vector3(x, y, 0))){
//				debug.field[n].down = 0.01;
//				debug.field[n].up = 0.02;
//			}
//		}
//		return;

		Polygon25::SortPolygonsFromOutside(&pgs);

//		debug = temp;

		bool isMillUp = true;
		// Generate a toolpath from the polygon collection
		for(size_t i = pgs.GetCount(); i > 0; i--){
			if(pgs[i - 1].elements.GetCount() == 0) continue;

			pgs[i - 1].RotatePolygonStart(m.axisX, m.axisY);

			if(!isMillUp){
				const double d2 = (m.axisX - pgs[i - 1].elements[0].x)
						* (m.axisX - pgs[i - 1].elements[0].x)
						+ (m.axisY - pgs[i - 1].elements[0].y)
								* (m.axisY - pgs[i - 1].elements[0].y);
				if(d2 > (0.008 * 0.008)){
					// Move tool out of material to travel to next polygon.
					m.isCutting = false;
					m.axisZ = temp.GetSizeZ() + freeHeight;
					tp.positions.Add(m);
					isMillUp = true;
				}
			}

			if(isMillUp){
				// Move tool to next position
				m.axisX = pgs[i - 1].elements[0].x;
				m.axisY = pgs[i - 1].elements[0].y;
				m.axisZ = temp.GetSizeZ() + freeHeight;
				m.isCutting = false;
				tp.positions.Add(m);
			}
			// Add polyg.positions[i].axisX,on
			m.isCutting = true;
			isMillUp = false;

			for(size_t j = 0; j < pgs[i - 1].elements.GetCount(); j++){
				m.axisX = pgs[i - 1].elements[j].x;
				m.axisY = pgs[i - 1].elements[j].y;
				m.axisZ = pgs[i - 1].elements[j].z;
				tp.positions.Add(m);
			}
		}
		pgs.Clear();

		if(level >= 0.0 && level < 3 * tolerance){
			level = -1.0;
		}else{
			level = dropLevel;
			if(level < 2 * tolerance){
				level = 2 * tolerance;
			}
		}

		// Move tool out of material
		m.axisZ = temp.GetSizeZ() + freeHeight;
		m.isCutting = false;
		isMillUp = true;
		tp.positions.Add(m);
#ifdef _DEBUGMODE
		wxLogMessage(wxString::Format(_T("Next Level: %.3f m"), level));
//		level = -1;
#endif
	}
//	debug = temp;
	toolpath = tp;
}
