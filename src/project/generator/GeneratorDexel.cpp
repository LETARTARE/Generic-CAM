///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorDexel.cpp
// Purpose            : Base class for Dexel based generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "GeneratorDexel.h"

#include "../Project.h"
#include "../Run.h"
#include "../Tool.h"
#include "../../Config.h"
#include <iostream>
#include <float.h>

#include "../../3D/OpenGL.h"

GeneratorDexel::GeneratorDexel(size_t ID) :
		Generator(ID)
{
//	area.alpha = 1.0;
//	area.displaySides = false;
//	area.displayBox = true;

#ifdef _DEBUGMODE
	start.displayField = true;
//	start.displayBox = true;
	target.displayField = true;
	selected.displayField = true;
	debug.displayField = true;
	simulation.displayField = true;
#else
	target.displayField = false;
	debug.displayField = false;
#endif
}

GeneratorDexel::~GeneratorDexel()
{
}

void GeneratorDexel::Paint(void) const
{
	Generator::Paint();
#ifdef _DEBUGMODE
//	glPushMatrix();
//	glTranslatef(debugOrigin.x, debugOrigin.y, debugOrigin.z);
//
//	glPushMatrix();
//	glTranslatef(0, start.GetSizeY(), 0);
//	debug.Paint();
//	glPopMatrix();
//	glPushMatrix();
//	glTranslatef(start.GetSizeX(), start.GetSizeY(), 0);
//	start.Paint();
//	glPopMatrix();
//	glPushMatrix();
//	glTranslatef(2 * start.GetSizeX(), start.GetSizeY(), 0);
//	target.Paint();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(start.GetSizeX(), 0, 0);
//	selected.Paint();
//	glPopMatrix();
//	glPushMatrix();
//	glTranslatef(2 * start.GetSizeX(), 0, 0);
//	simulation.Paint();
//	glPopMatrix();
//
//	glPopMatrix();
#endif
}

void GeneratorDexel::PrepareTargets(const Run &run,
		const std::vector <Object> &objects, const DexelTarget &start)
{
	this->start = start;
	this->simulation = start;

#ifdef _DEBUGMODE
	debugOrigin.Set(run.stock.xmin, run.stock.ymin, run.stock.zmin);
#endif

	selected.SetupField(start);
	target.SetupField(start);

	selected.InitImprinting();
	target.InitImprinting();

	std::set <size_t> objIDs;
	if(area.IsBaseType(Selection::BaseObject)) objIDs.insert(area.GetBaseID());
	if(area.IsType(Selection::Object)) objIDs.insert(area.begin(), area.end());
	if(objIDs.empty()){
		std::cout << "GeneratorDexel::GenerateToolpath - No object in area.\n";
		throw(std::logic_error(
				"GeneratorDexel::GenerateToolpath - No object in area."));
	}

	for(std::vector <Object>::const_iterator obj = objects.begin();
			obj != objects.end(); ++obj){
		AffineTransformMatrix M = obj->matrix;
		M.TranslateGlobal(-obj->bbox.xmin, -obj->bbox.ymin, -obj->bbox.zmin);
		M.TranslateGlobal(-run.stock.xmin + obj->bbox.xmin,
				-run.stock.ymin + obj->bbox.ymin,
				-run.stock.zmin + obj->bbox.zmin);

		Vector3 a, b, c, normal;

		const size_t N = obj->geometry.GetTriangleCount();
		for(size_t n = 0; n < N; ++n){
			const Hull::Triangle & tri = obj->geometry.GetTriangle(n);
			obj->geometry.GetTriangle(n, a, b, c);
			a = M.Transform(a);
			b = M.Transform(b);
			c = M.Transform(c);
			normal = M.TransformNoShift(tri.n);
			if(normal.z > 0){
				target.InsertTriangle(a, b, c, Imprinter::facing_up);
			}else{
				target.InsertTriangle(a, b, c, Imprinter::facing_down);
			}
		}

		if(area.IsType(Selection::Object) && area.Has(obj->GetID())){
			for(size_t n = 0; n < N; ++n){
				const Hull::Triangle & tri = obj->geometry.GetTriangle(n);
				obj->geometry.GetTriangle(n, a, b, c);
				a = M.Transform(a);
				b = M.Transform(b);
				c = M.Transform(c);
				normal = M.TransformNoShift(tri.n);
				if(normal.z > 0){
					selected.InsertTriangle(a, b, c, Imprinter::facing_up);
				}else{
					selected.InsertTriangle(a, b, c, Imprinter::facing_down);
				}
			}
		}
		if(area.IsBase(Selection::BaseObject, obj->GetID())
				&& area.IsType(Selection::TriangleGroup)){
			for(std::set <size_t>::const_iterator it = area.begin();
					it != area.end(); ++it){
				for(size_t n = 0; n < N; ++n){
					const Hull::Triangle & tri = obj->geometry.GetTriangle(n);
					if(tri.group != *it) continue;
					obj->geometry.GetTriangle(n, a, b, c);
					a = M.Transform(a);
					b = M.Transform(b);
					c = M.Transform(c);
					normal = M.TransformNoShift(tri.n);

					if(normal.z > 0){
						selected.InsertTriangle(a, b, c, Imprinter::facing_up);
					}else{
						selected.InsertTriangle(a, b, c,
								Imprinter::facing_down);
					}
				}
			}
		}
	}
	target.FinishImprint();
	selected.FinishImprint();
}

//	for(size_t i = 0; i < workpiece->placements.GetCount(); i++){
//		const ObjectPlacement* const opl = &(workpiece->placements[i]);
//		const size_t refObject = opl->refObject;
//		const Object* object = &(project->objects[refObject]);
//		AffineTransformMatrix tempMatrix;
//		tempMatrix *= run->workpiecePlacement;
//		tempMatrix *= opl->matrix;
//		target.InsertObject(*object, tempMatrix);
//
//		DexelTarget temp(mask);
//		if(useContours){
//			//TODO More differentiated contour processing
//			temp.InitImprinting();
//			temp.InsertObject(*object, tempMatrix);
//			temp.FinishImprint();
//			DexelTarget discSlot;
//			discSlot.SetupDisc(opl->slotWidth, mask.GetResolutionX(),
//					mask.GetResolutionY());
//			temp.FoldRaise(discSlot);
//			temp.HardInvert();
//		}else{
//			temp.Empty();
//		}
//		mask &= temp;
//	}

//	debug = mask;

//	for(size_t i = 0; i < workpiece->supports.GetCount(); i++){
//		//TODO: Insert supports into target.
//	}

//	DexelTarget temp;
//	temp = mask;
//	temp.InitImprinting();
//
//	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmax),
//			Vector3(area.xmax, area.ymin, area.zmax),
//			Vector3(area.xmax, area.ymax, area.zmax), Imprinter::facing_up);
//	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmax),
//			Vector3(area.xmin, area.ymax, area.zmax),
//			Vector3(area.xmax, area.ymax, area.zmax), Imprinter::facing_up);
//	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmin),
//			Vector3(area.xmax, area.ymin, area.zmin),
//			Vector3(area.xmax, area.ymax, area.zmin), Imprinter::facing_down);
//	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmin),
//			Vector3(area.xmin, area.ymax, area.zmin),
//			Vector3(area.xmax, area.ymax, area.zmin), Imprinter::facing_down);

//	temp.FinishImprint();
//	temp.HardInvert();
//	mask |= temp;

//	temp = start;
// TODO Check why in a direct c = a & b; the overloaded & does not return a DexelTarget.
//	temp &= mask;
//	debug = allObjects;
//	target |= allObjects;
//	debug = toolShape;

//	target.CleanOutlier();
//	target.Refresh();

//	, temp2;
//	TargetPlacement tempPlace;
//	Run* run = new Run;
//
//	run->stockMaterial = stock.stockMaterials[0];
//
//	AffineTransformMatrix shift;
//
//	Object* obj = &(objects[activeObject]);
//	AffineTransformMatrix oldPos = obj->matrix;
//
//	obj->UpdateBoundingBox();
//
//	size_t i, n;
//	n = ceil(obj->bbox.zmax / stock.stockMaterials[activeStock].sz);
//

//
//	slotWidth = 0.025;
//	Target discSlot2;
//	discSlot2.SetupDisc(slotWidth, resolution, resolution);
//
//	i = SetupMachineBed(true);
//	run = &(run[i]);
//
//	//	discSlot.matrix.TranslateGlobal(0.1, -0.1, 0);
//	//	targets.Add(discSlot);
//
//	wxLogMessage(
//			wxString::Format(_T("%u Targets after stockmaterial placement."),
//					run->placements.GetCount()));
//
//	//	// Hole@:
//	//	tempPlace.SetKeepout(0.23858 - 0.010, 0.329268 - 0.010, 0.020, 0.020);
//	//	run->placements.Add(tempPlace);
//
//	// Screw 1:
//	tempPlace.SetKeepout(0.0785 - 0.010, 0.114 - 0.010, 0.020, 0.020);
//	run->placements.Add(tempPlace);
//
//	// Screw 2:
//	tempPlace.SetKeepout(0.0755 - 0.010, 0.301 - 0.010, 0.020, 0.020);
//	run->placements.Add(tempPlace);
//
//	// Screw 3:
//	tempPlace.SetKeepout(0.469 - 0.010, 0.099 - 0.010, 0.020, 0.020);
//	run->placements.Add(tempPlace);
//
//	wxLogMessage(
//			wxString::Format(_T("%u Targets after keepout placement."),
//					run->placements.GetCount()));
//
//	wxLogMessage(
//			wxString::Format(_T("%u Targets after drill placement."),
//					run->placements.GetCount()));
//
//	double gridx = 0.0;
//	double gridy = 0.0;
//	double gridsx = obj->bbox.xmax + 4 * slotWidth;
//	double gridsy = obj->bbox.ymax + 4 * slotWidth;
//
//	//if(n > 2) n = 2; // TODO: Remove this line!
//	for(i = 4; i < 9; i++){
//		//for(i = 0; i <= 2; i++){
//
//		if(true){
//			temp.SetupBox(obj->bbox.xmax + 4 * slotWidth,
//					obj->bbox.ymax + 4 * slotWidth,
//					stock.stockMaterials[activeStock].sz, resolution,
//					resolution);
//
//			shift.SetIdentity();
//			shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth,
//					(double) i * -stock.stockMaterials[activeStock].sz);
//
//		}else{
//			temp.SetupBox(obj->bbox.xmax, obj->bbox.ymax,
//					stock.stockMaterials[activeStock].sz, resolution,
//					resolution);
//
//			shift.SetIdentity();
//			shift.TranslateGlobal(0.0, 0.0,
//					(double) i * -stock.stockMaterials[activeStock].sz);
//		}
//
//		obj->matrix = shift * oldPos;
//		temp.InsertObject(*obj);
//		temp.CleanOutlier();
//
//		//		temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);
//		//		targets.Add(temp);
//		if(true) //TODO: Remove this line
//		{
//			temp2 = temp;
//
//			if(i == 0){
//				temp2.FoldRaise(discSlot2);
//			}else{
//				temp2.FoldRaise(discSlot);
//			}
//
//			temp.outLine = temp2.GenerateConvexOutline();
//
//			if(temp.outLine.elements.GetCount() >= 2){
//
//				temp.supportLine = temp2.GeneratePolygon(-1, -1);
//				temp.supportLine.PolygonSmooth();
//				temp.supportLine.PolygonSmooth();
//				temp.supportLine.PolygonSmooth();
//
//				//temp.FillOutsidePolygon(temp.outline);
//				temp2.HardInvert();
//				temp += temp2;
//
//				temp.AddSupport(temp.supportLine, supportDistance,
//						supportHeight, supportWidth, slotWidth);
//			}
//		}
//
//		tempPlace.Clear();
//		tempPlace.matrix.TranslateGlobal(gridx, gridy, 0.0);
//		//		tempPlace.matrix = AffineTransformMatrix::RotateXYZ(0.0, 0.0,
//		//				(double) (i % 2) * 2 * M_PI) * tempPlace.matrix;
//
//		temp.refresh = true;
//
//		targets.Add(temp);
//		tempPlace.targetNumber = targets.GetCount() - 1;
//		tempPlace.outLine = temp.outLine;
//		run->placements.Add(tempPlace);
//
//		gridx += gridsx;
//		if(gridx + gridsx > stock.stockMaterials[activeStock].sx){
//			gridx = 0.0;
//			gridy += gridsy;
//		}
//
//		//		Target mill;
//		//		mill.SetupDisc(3.0/1000,temp.GetSizeRX(),temp.GetSizeRY());
//		//		temp.FoldRaise(mill);
//		//
//		//		temp.InvertTop();
//		//
//		//		temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);
//		//		targets.Add(temp);
//
//		//temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);
//
//		//		if(temp.outLine.elements.GetCount() >= 2){
//
//		//temp.ClearField();
//
//		//			ToolPathGenerator.GenerateToolpath(temp, *obj, toolbox.tools[0]);
//
//	}
//
//	wxLogMessage(
//			wxString::Format(_T("%u Targets after target placement."),
//					run->placements.GetCount()));
//
//	//run->SortTargets();
//
//	run.Add(run);
//
//	obj->matrix = oldPos;
//
//	displayGeometry = false;
//	displayStock = true;
//	displayTargets = true;
//	if(false){
//		GenerateToolPath();
//
//		n = targets.GetCount() - 1;
//
//		temp = targets[n];
//		temp.Simulate();
//		targets.Add(temp);
//		tempPlace.targetNumber = targets.GetCount() - 1;
//		tempPlace.matrix.SetIdentity();
//		tempPlace.matrix.TranslateGlobal(2 * temp.GetSizeX(), 0.0, 0.0);
//		run[0].placements.Add(tempPlace);
//
//		temp = targets[n];
//
//		Target discTool;
//		discTool.SetupDisc(0.003, temp.GetSizeRX(), temp.GetSizeRY());
//
//		temp.FoldRaise(discTool);
//		temp.Limit();
//		temp.InvertTop();
//
//		targets.Add(temp);
//		tempPlace.targetNumber = targets.GetCount() - 1;
//		tempPlace.matrix.SetIdentity();
//		tempPlace.matrix.TranslateGlobal(temp.GetSizeX(), 0.0, 0.0);
//		run[0].placements.Add(tempPlace);
//	}

void GeneratorDexel::QuickCollectToolpaths(std::vector <ProtoToolpath> &ptp,
		const double pathDistance)
{
	if(ptp.size() == 0) return;

	CNCPosition m;
	if(!toolpath.empty()){
		CNCPosition p1 = *(toolpath.end() - 1);
		m.position.x = p1.position.x;
		m.position.y = p1.position.y;
		m.position.z = fmax(p1.position.z, target.GetSizeZ() + freeHeight);
	}else{
		m.position.z = target.GetSizeZ() + freeHeight;
	}
// Assign parents
	for(size_t q = 0; q < ptp.size(); ++q){
		if(ptp[q].p.empty()){
			ptp[q].inserted = true;
			continue;
		}
		ptp[q].inserted = false;
	}

	bool allowReversing = true;
	double maxStepUp = 0.01;

// Connect the path segments
	do{
		double dopt = FLT_MAX;
		int nopt = -1;
		bool forward = true;
		for(size_t n = 0; n < ptp.size(); n++){
			if(ptp[n].inserted) continue;

			const double d = (m.position.x - ptp[n].p[0].position.x)
					* (m.position.x - ptp[n].p[0].position.x)
					+ (m.position.y - ptp[n].p[0].position.y)
							* (m.position.y - ptp[n].p[0].position.y)
					+ (m.position.z - ptp[n].p[0].position.z)
							* (m.position.z - ptp[n].p[0].position.z);
			if(d < dopt){
				forward = true;
				dopt = d;
				nopt = n;
			}
			if(allowReversing){
				const CNCPosition p1 = *(ptp[n].p.end() - 1);
				const double d = (m.position.x - p1.position.x)
						* (m.position.x - p1.position.x)
						+ (m.position.y - p1.position.y)
								* (m.position.y - p1.position.y)
						+ (m.position.z - p1.position.z)
								* (m.position.z - p1.position.z);
				if(d < dopt){
					forward = false;
					dopt = d;
					nopt = n;
				}
			}
		}
		if(nopt < 0) break;
		CNCPosition mlast = m;
		if(forward)
			m = *(ptp[nopt].p.begin());
		else
			m = *(ptp[nopt].p.end() - 1);

		{
			double px0 = round(
					(mlast.position.x - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py0 = round(
					(mlast.position.y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());
			double px1 = round(
					(m.position.x - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py1 = round(
					(m.position.y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());

			const double d = fmax(fabs(px0 - px1), fabs(py0 - py1));
			const int N = round(d);
			Vector3 delta = (m.position - mlast.position) / fmax(1.0, d);
			CNCPosition p = mlast;

			const double dd = fmax(fabs(px0 - px1) * target.GetResolutionX(),
					fabs(py0 - py1) * target.GetResolutionY());

			if(fabs(m.position.z - mlast.position.z) <= maxStepUp
					&& dd < pathDistance){
				std::vector <CNCPosition> tp1;
				double cost = 0.0;
				for(size_t u = 0; u <= N; u++){
					const double h = target.GetLevel(p.position.x,
							p.position.y);
					if(h > -FLT_EPSILON){
						cost += fmax(h - p.position.z, 0);
						CNCPosition temp = p;
						temp.position.z = fmax(temp.position.z, h); //TODO This is following the surface exactly, but should skip gaps.
						tp1.push_back(temp);
					}
					p += delta;
				}
				toolpath.insert(toolpath.end(), tp1.begin(), tp1.end());

			}else{
				if(mlast.position.z
						< target.GetSizeZ() + freeHeight - FLT_EPSILON){
					mlast.position.z = target.GetSizeZ() + freeHeight;
					mlast.Rapid();
					toolpath.push_back(mlast);
				}
				mlast = m;
				mlast.position.z = target.GetSizeZ() + freeHeight;
				mlast.Rapid();
				toolpath.push_back(mlast);
			}
		}

//		m.position.Z = fmax(m.position.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.push_back(m);

		if(forward){
			for(size_t m = 0; m < ptp[nopt].p.size(); m++){
				toolpath.push_back(ptp[nopt].p[m]);
			}
		}else{
			for(size_t m = ptp[nopt].p.size(); m-- > 0;){
				toolpath.push_back(ptp[nopt].p[m]);
			}
		}
		m = *(toolpath.end() - 1);
//		m.position.Z = fmax(m.position.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.push_back(m);

		ptp[nopt].inserted = true;
	}while(true);

// Move out of workpiece
	if((toolpath.size() > 0)
			&& ((toolpath.end() - 1)->position.z
					< (target.GetSizeZ() + freeHeight - FLT_EPSILON))){
		CNCPosition m;
		CNCPosition p1 = *(toolpath.end() - 1);
		//Note: Rotations are kept at zero for the starting position
		m.position.x = p1.position.x;
		m.position.y = p1.position.y;
		m.position.z = target.GetSizeZ() + freeHeight;
		m.Rapid();
		toolpath.push_back(m);
	}

}

void GeneratorDexel::ToJSON(JSON& js) const
{
	Generator::ToJSON(js);
}

bool GeneratorDexel::FromJSON(const JSON& js)
{
	bool result = Generator::FromJSON(js);
	return result;
}
