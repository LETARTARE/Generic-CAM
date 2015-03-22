///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorFast.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.08.2011
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

#include "GeneratorFast.h"
#include <math.h>

#include "../project/Project.h"

GeneratorFast::GeneratorFast(Project * project, size_t runNr, size_t toolpathNr) :
		GeneratorDexel(project, runNr, toolpathNr)
{
	freeHeightAboveMaterial = 0.002;
	maxSingleStep = 0.020;
	raiseStep = 0.005;
	dropStep = 0.008;

	toolDiameter = 0.0;
}

GeneratorFast::~GeneratorFast()
{
}

ToolPath GeneratorFast::GenerateDrill(double x, double y, double diameter,
		double depth)
{
	ToolPath temp;
	MachinePosition mp;

	double r = (diameter - toolDiameter) / 2.0;

	mp.axisX = x;
	mp.axisY = y;
	mp.axisZ = 0.0;
	mp.isCutting = true;
	mp.isRotationPositiv = true;
	temp.positions.Add(mp);

	if(r <= 0.001){
		double d = 0.0;
		while(d > dropStep - depth){
			d -= dropStep;

			mp.axisZ = d;
			temp.positions.Add(mp);
			mp.axisZ = 0.0;
			temp.positions.Add(mp);
		}
		mp.axisZ = -depth;
		mp.axisX += r;
		temp.positions.Add(mp);
		mp.radiusI = -r;
		temp.positions.Add(mp);
		mp.radiusI = 0.0;
		mp.axisX = x;
		temp.positions.Add(mp);
	}else{
		mp.axisX += r;
		temp.positions.Add(mp);
		mp.radiusI = -r;
		while(mp.axisZ > dropStep - depth){
			mp.axisZ -= dropStep;
			temp.positions.Add(mp);
		}
		mp.axisZ = -depth;
		temp.positions.Add(mp);
		temp.positions.Add(mp);
		mp.radiusI = 0.0;
		mp.axisX = x;
		temp.positions.Add(mp);
	}

	return temp;
}

ToolPath GeneratorFast::GenerateSpiral(double x, double y, double radius)
{
	ToolPath temp;
	MachinePosition mp;

	double rinc = toolDiameter / 2.0;
	double r;

	size_t Npt = 40;
	size_t Nt = floor((double) Npt * radius / rinc);
	size_t n;

	mp.axisX = x;
	mp.axisY = y;
	mp.axisZ = 0.0;
	mp.isCutting = true;
	mp.isRotationPositiv = true;
	temp.positions.Add(mp);

	for(n = 1; n <= Nt; n++){
		r = radius / (double) Nt * (double) n;
		mp.radiusR = r;
		mp.axisX = x + r * cos(2 * M_PI / (double) Npt * (double) n);
		mp.axisY = y + r * sin(2 * M_PI / (double) Npt * (double) n);
		temp.positions.Add(mp);
	}
	return temp;
}

bool GeneratorFast::IsDirectlyReachable(DexelTarget &target, double sx,
		double sy, double sz, double x, double y, double z)
{
	double dx = x - sx;
	double dy = y - sy;
	double dz = z - sz;
	double d = sqrt(dx * dx + dy * dy);
	double rx = target.GetSizeRX();
	double ry = target.GetSizeRY();
	size_t n = round(d / (rx + ry) * 2);
	double px, py, pz, hz;
	size_t i;
	for(i = 0; i < n; i++){
		px = sx + dx / (double) n * (double) i;
		py = sy + dy / (double) n * (double) i;
		pz = sz + dz / (double) n * (double) i;
		hz = target.GetLevel(px, py);
		if(hz > pz) return false;
	}
	return true;
}

void GeneratorFast::CopyFrom(const Generator* other)
{
	GeneratorDexel::CopyFrom(other);
}

wxString GeneratorFast::GetName(void) const
{
	return _T("Fast Generator (using Dexel)");
}

void GeneratorFast::AddToPanel(wxPanel* panel, DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);
}

void GeneratorFast::TransferDataToPanel(void) const
{
}

void GeneratorFast::TransferDataFromPanel(void)
{
}

wxString GeneratorFast::ToString(void) const
{
	return _T("");
}

void GeneratorFast::FromString(const wxString& text)
{
}

ToolPath GeneratorFast::MoveSavely(DexelTarget &target, double sx, double sy,
		double sz, double x, double y, double z)
{
	ToolPath tp;
	MachinePosition mp;

	bool hasToDrop = false;

	size_t i;
	double px, py;
	double hz;

	double rx = target.GetSizeRX();
	double ry = target.GetSizeRY();
	double r = (rx + ry) / 2;

	mp.axisX = sx;
	mp.axisY = sy;
	mp.axisZ = sz;
	mp.isCutting = false;

	double dx = x - sx;
	double dy = y - sy;
	double dz = z - sz;

	double d = sqrt(dx * dx + dy * dy);
	double dt;

	if(dz >= 0){
		mp.axisZ = z + 0.001;
		tp.positions.Add(mp);
	}

	size_t n = round(d / r);

	for(i = 1; i < n; i++){

		px = sx + dx / (double) n * (double) i;
		py = sy + dy / (double) n * (double) i;
		hz = target.GetLevel(px, py);

		dt = d * (1 - (double) i / (double) n);

		if(hz > mp.axisZ && !mp.isCutting){
			mp.axisX = sx + dx / (double) (n - 1) * (double) i;
			mp.axisY = sy + dy / (double) (n - 1) * (double) i;
			mp.axisZ = target.GetSizeZ() + freeHeightAboveMaterial;
			tp.positions.Add(mp);
			hasToDrop = true;
		}

		if(dt <= toolDiameter / 2 && !mp.isCutting && !hasToDrop){
			mp.axisX = sx + dx / (double) (n - 1) * (double) i;
			mp.axisY = sy + dy / (double) (n - 1) * (double) i;
			tp.positions.Add(mp);
			mp.axisX = px;
			mp.axisY = py;
			mp.isCutting = true;
			tp.positions.Add(mp);
		}
	}
	mp.axisX = x;
	mp.axisY = y;
	if(!hasToDrop) mp.axisZ = z;
	tp.positions.Add(mp);

	if(hasToDrop){
		double d = target.GetSizeZ();
		while(d > dropStep + z){
			mp.isCutting = true;
			d -= dropStep;
			mp.axisZ = d;
			tp.positions.Add(mp);
			mp.isCutting = false;
			mp.axisZ = target.GetSizeZ();
		}
		mp.isCutting = true;
		mp.axisZ = z;
		tp.positions.Add(mp);
	}
	return tp;
}

void GeneratorFast::GenerateToolpath(void)
{
	output.Empty();

	size_t slotNr = project->run[runNr].toolpaths[toolpathNr].generator->slotNr;
	Tool * tool = project->run[runNr].toolbox.GetToolInSlot(slotNr);
	if(tool == NULL){
		output = _T("Tool empty.");
		errorOccured = true;
		return;
	}

	GenerateTarget();

	if(target.IsEmpty()){
		output = _T("DexelTarget empty.");
		errorOccured = true;
		return;
	}

	ToolPath tp;
	MachinePosition mp;

	toolDiameter = tool->GetMaxDiameter();

	DexelTarget discTool;
	discTool.SetupTool(*tool, target.GetSizeRX(), target.GetSizeRY());

	DexelTarget temp = target;
	DexelTarget temptop;

	temp.FoldRaise(discTool);
	temp.Limit();

	temptop = temp;
	temptop.InvertTop();

	double rx = target.GetSizeRX();
	double ry = target.GetSizeRY();
	double rx2 = rx / 2;
	double ry2 = ry / 2;

	int cx, cy;
	double d;

	Polygon25 poly;
	size_t i;
	ArrayOfMachinePosition mpa = target.toolpathFlipped.positions;

	// Begin drop&raise cycle

	double dmin = temptop.GetMinLevel();
	double level = dmin + raiseStep;

	temptop.InitOutSides(); // TODO: Check if definition is right?
	temptop.GenerateDistanceMap(level, true);

	double px, py, pz;

	// Removed other side from flipped designs
	if(!mpa.IsEmpty()){
		for(i = 0; i < mpa.GetCount(); i++){
			px = mpa[i].axisX;
			py = target.GetSizeY() - mpa[i].axisY;
			pz = target.GetSizeZ() - mpa[i].axisZ;
			if(pz > level) temptop.FoldLowerDistance(round((px - rx2) / rx),
					round((py - ry2) / ry), discTool);
		}
	}

	d = temptop.GetMaxUpsideLevel(cx, cy);

	if(tp.IsEmpty()){ // New toolpath starting position
		mp.axisX = rx * cx + rx2;
		mp.axisY = ry * cy + ry2;
		mp.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
		mp.isCutting = false;
		tp.positions.Add(mp);
	}

	// Remove material at drillhole
	//temptop.FoldLowerDistance(cx, cy, discTool);

	do{
		// Scrubb area
		while(temptop.FindNextDistance(cx, cy)){
			temptop.FindStartCutting(cx, cy);

			//		if(!IsDirectlyReachable(temp, mp.axisX, mp.axisY, mp.axisZ, cx * rx
			//				+ rx2, cy * ry + ry2, level)) break;

			poly = temptop.FindCut(cx, cy);
			temp.PolygonDrop(poly, level + raiseStep);

			if(mp.axisZ > level){
				// Drill down
				d = target.GetSizeZ();
				while(d > level + dropStep){
					mp.isCutting = true;
					d -= dropStep;
					mp.axisZ = d;
					tp.positions.Add(mp);
					mp.isCutting = false;
					mp.axisZ = target.GetSizeZ();
				}
				mp.isCutting = true;
				mp.axisZ = level;
				tp.positions.Add(mp);
			}
			//if(poly.elements.GetCount() > 3){
			for(i = 0; i < poly.elements.GetCount(); i++){

				temptop.FoldLowerDistance(
						round((poly.elements[i].x - rx2) / rx),
						round((poly.elements[i].y - ry2) / ry), discTool);

				if(i == 0){
					tp += MoveSavely(temp, mp.axisX, mp.axisY, mp.axisZ,
							poly.elements[i].x, poly.elements[i].y,
							poly.elements[i].z);
				}
				mp.axisX = poly.elements[i].x;
				mp.axisY = poly.elements[i].y;
				mp.axisZ = poly.elements[i].z;
				mp.isCutting = true;
				tp.positions.Add(mp);
				//}
			}
		}

		if(level < temptop.GetSizeZ() - 0.0001){
			level += raiseStep;
			if(level >= temptop.GetSizeZ() - 0.0001) level = temptop.GetSizeZ()
					- 0.00005;
		}else{
			level = temptop.GetSizeZ() + 0.0001;
		}

		mp.axisZ = level;
		mp.isCutting = false;
		tp.positions.Add(mp);

		if(level < temptop.GetSizeZ()){
			temptop.RaiseDistanceMap(level, true);

			// Removed other side from flipped designs
			if(!mpa.IsEmpty()){
				for(i = 0; i < mpa.GetCount(); i++){
					px = mpa[i].axisX;
					py = target.GetSizeY() - mpa[i].axisY;
					pz = target.GetSizeZ() - mpa[i].axisZ;
					if(pz > level) temptop.FoldLowerDistance(px, py, discTool);
				}
			}
		}

	}while(level < temptop.GetSizeZ());

	// Spiral out
	//temptp = GenerateSpiral(rx * cx, ry * cy, d / 2);

	//	// Drop onto geometry
	//	size_t i;
	//	for(i = 0; i < temptp.positions.GetCount(); i++)
	//		temp.VectorDrop(temptp.positions[i].axisX, temptp.positions[i].axisY,
	//				temptp.positions[i].axisZ, dmin);
	//
	//	tp += temptp;

	// Move out of material
	mp.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
	mp.isCutting = false;
	tp.positions.Add(mp);

	//target = temptop;

	//tp.CleanPath(0.0003);

	target.toolpath = tp;
	target.refresh = true;
	return;
	//
	//	double level = temp.GetSizeZ() - 0.0005;
	//
	//
	//	// Starting point
	//	//
	//	//	tp.positions.Add(m);
	//
	//	// Position at start (! not a toolpath position)
	//	m.axisX = 0.0;
	//	m.axisY = 0.0;
	//	m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
	//	m.isCutting = false;
	//
	//	ArrayOfPolygon25 pgs;
	//	Polygon25 pg;
	//
	//	AffineTransformMatrix tm;
	//	tm.TranslateGlobal(0.0, 0.0, -0.0001);
	//
	//
	//	// Move tool out of material
	//	m.axisZ = temp.GetSizeZ() + freeHeightAboveMaterial;
	//	m.isCutting = false;
	//	tp.positions.Add(m);
	//
	//
	//	// Shift toolpath down to align 0 with top-of-stock
	//	for(size_t i = 0; i < tp.positions.GetCount(); i++){
	//		tp.positions[i].axisZ -= temp.GetSizeZ();
	//	}
	//	tp.matrix.TranslateGlobal(0, 0, temp.GetSizeZ());
	//
	//
	//	//	t.InitImprinting();
	//	//	t.matrix.SetIdentity();
	//	//t.matrix.TranslateGlobal(t.GetSizeX(), 0, 0);
	//	//targets.Add(t);
	//
	//	target.toolpath = tp;
}