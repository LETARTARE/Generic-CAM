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

#include <float.h>

GeneratorDexel::GeneratorDexel()
{
	area.alpha = 1.0;
	area.displaySides = false;
	area.displayBox = true;

#ifdef _DEBUGMODE
	start.displayField = true;
	target.displayField = true;
	debug.displayField = true;
#else
	target.displayField = false;
	debug.displayField = false;
#endif
}

void GeneratorDexel::CopyParameterFrom(const Generator * other)
{
	Generator::CopyParameterFrom(other);
}

GeneratorDexel::~GeneratorDexel()
{
}

void GeneratorDexel::ToStream(wxTextOutputStream& stream)
{
	Generator::ToStream(stream);
}

bool GeneratorDexel::FromStream(wxTextInputStream& stream)
{
	bool result = Generator::FromStream(stream);
	target.SetupBox(area.GetSizeX(), area.GetSizeY(), area.GetSizeZ());
	return result;
}

void GeneratorDexel::Paint(void) const
{
	Generator::Paint();
	area.Paint();
#ifdef _DEBUGMODE

	glPushMatrix();
	glTranslatef(0, target.GetSizeY(), 0);
	start.Paint();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -target.GetSizeY(), 0);
	target.Paint();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2 * target.GetSizeY(), 0);
	debug.Paint();
	glPopMatrix();

#endif
}

void GeneratorDexel::GenerateToolpath(void)
{
	const Run* const run = this->parent;
	assert(run != NULL);
	const Project* const project = run->parent;
	assert(project != NULL);
	const Workpiece* const workpiece = &(project->workpieces[run->refWorkpiece]);
	assert(workpiece != NULL);

	// Start to Target:
	// - Start: may have changes by previous toolpaths
	// - Mask: work only in designated area
	// - Temp: Remove workpiece OR remove immediate surroundings --> Set in WorkpiecePlacement

	start = workpiece->model;

	DexelTarget mask;
	mask = start;
	mask.Fill();

	target = start;
	target.InitImprinting();

	bool useContours = false;

	for(size_t i = 0; i < workpiece->placements.GetCount(); i++){
		const ObjectPlacement* const opl = &(workpiece->placements[i]);
		const size_t refObject = opl->refObject;
		Object* object = &(project->objects[refObject]);
		object->Update();
		AffineTransformMatrix tempMatrix;
		tempMatrix *= run->workpiecePlacement;
		tempMatrix *= opl->matrix;
		object->bbox.Transform(tempMatrix);
		if(area.Overlaps(object->bbox) && opl->useContour) useContours = true;
	}

	for(size_t i = 0; i < workpiece->placements.GetCount(); i++){
		const ObjectPlacement* const opl = &(workpiece->placements[i]);
		const size_t refObject = opl->refObject;
		const Object* object = &(project->objects[refObject]);
		AffineTransformMatrix tempMatrix;
		tempMatrix *= run->workpiecePlacement;
		tempMatrix *= opl->matrix;
		target.InsertObject(*object, tempMatrix);

		DexelTarget temp(mask);
		if(useContours){
			//TODO More differentiated contour processing
			temp.InitImprinting();
			temp.InsertObject(*object, tempMatrix);
			temp.FinishImprint();
			DexelTarget discSlot;
			discSlot.SetupDisc(opl->slotWidth, mask.GetResolutionX(),
					mask.GetResolutionY());
			temp.FoldRaise(discSlot);
			temp.HardInvert();
		}else{
			temp.Empty();
		}
		mask &= temp;
	}
	target.FinishImprint();

	for(size_t i = 0; i < workpiece->supports.GetCount(); i++){
		//TODO: Insert supports into target.
	}

	DexelTarget temp;
	temp = mask;
	temp.InitImprinting();
	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmax),
			Vector3(area.xmax, area.ymin, area.zmax),
			Vector3(area.xmax, area.ymax, area.zmax), Imprinter::facing_up);
	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmax),
			Vector3(area.xmin, area.ymax, area.zmax),
			Vector3(area.xmax, area.ymax, area.zmax), Imprinter::facing_up);
	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmin),
			Vector3(area.xmax, area.ymin, area.zmin),
			Vector3(area.xmax, area.ymax, area.zmin), Imprinter::facing_down);
	temp.InsertTriangle(Vector3(area.xmin, area.ymin, area.zmin),
			Vector3(area.xmin, area.ymax, area.zmin),
			Vector3(area.xmax, area.ymax, area.zmin), Imprinter::facing_down);
	temp.FinishImprint();
	temp.HardInvert();
	mask |= temp;

	temp = start;
	// TODO Check why in a direct c = a & b; the overloaded & does not return a DexelTarget.
	temp &= mask;
	debug = temp;
	target |= temp;
//	debug = target;

//	target.CleanOutlier();
	target.Refresh();
}

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
//	Target discSlot;
//	discSlot.SetupDisc(slotWidth, resolution, resolution);
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

void GeneratorDexel::QuickCollectToolpaths(ArrayOfProtoToolpath &ptp,
		const double pathDistance)
{
	if(ptp.GetCount() == 0) return;

	GCodeBlock m;
	if(!toolpath.IsEmpty()){
		m.X = toolpath.positions.Last().X;
		m.Y = toolpath.positions.Last().Y;
		m.Z = fmax(toolpath.positions.Last().Z, target.GetSizeZ() + freeHeight);
	}else{
		m.Z = target.GetSizeZ() + freeHeight;
	}
	// Assign parents
	for(size_t q = 0; q < ptp.GetCount(); q++){
		if(ptp[q].IsEmpty()){
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
		for(size_t n = 0; n < ptp.GetCount(); n++){
			if(ptp[n].inserted) continue;

			const double d = (m.X - ptp[n].positions[0].X)
					* (m.X - ptp[n].positions[0].X)
					+ (m.Y - ptp[n].positions[0].Y)
							* (m.Y - ptp[n].positions[0].Y)
					+ (m.Z - ptp[n].positions[0].Z)
							* (m.Z - ptp[n].positions[0].Z);
			if(d < dopt){
				forward = true;
				dopt = d;
				nopt = n;
			}
			if(allowReversing){
				const double d = (m.X - ptp[n].positions.Last().X)
						* (m.X - ptp[n].positions.Last().X)
						+ (m.Y - ptp[n].positions.Last().Y)
								* (m.Y - ptp[n].positions.Last().Y)
						+ (m.Z - ptp[n].positions.Last().Z)
								* (m.Z - ptp[n].positions.Last().Z);
				if(d < dopt){
					forward = false;
					dopt = d;
					nopt = n;
				}
			}
		}
		if(nopt < 0) break;
		GCodeBlock mlast = m;
		if(forward)
			m = ptp[nopt].positions[0];
		else
			m = ptp[nopt].positions.Last();

		{
			double px0 = round(
					(mlast.X - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py0 = round(
					(mlast.Y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());
			double px1 = round(
					(m.X - target.GetResolutionX() / 2)
							/ target.GetResolutionX());
			double py1 = round(
					(m.Y - target.GetResolutionY() / 2)
							/ target.GetResolutionY());

			const double d = fmax(fabs(px0 - px1), fabs(py0 - py1));
			const int N = round(d);
			GCodeBlock delta = (m - mlast) / fmax(1.0, d);
			GCodeBlock p = mlast;

			const double dd = fmax(fabs(px0 - px1) * target.GetResolutionX(),
					fabs(py0 - py1) * target.GetResolutionY());

			if(fabs(m.Z - mlast.Z) <= maxStepUp && dd < pathDistance){
				ToolPath tp1;
				double cost = 0.0;
				for(size_t u = 0; u <= N; u++){
					const double h = target.GetLevel(p.X, p.Y);
					if(h > -FLT_EPSILON){
						cost += fmax(h - p.Z, 0);
						GCodeBlock temp = p;
						temp.Z = fmax(temp.Z, h); //TODO This is following the surface exactly, but should skip gaps.
						tp1.positions.Add(temp);
					}
					p += delta;
				}
				toolpath += tp1;

			}else{
				if(mlast.Z < target.GetSizeZ() + freeHeight - FLT_EPSILON){
					mlast.Z = target.GetSizeZ() + freeHeight;
					mlast.Rapid();
					toolpath.positions.Add(mlast);
				}
				mlast = m;
				mlast.Z = target.GetSizeZ() + freeHeight;
				mlast.Rapid();
				toolpath.positions.Add(mlast);
			}
		}

//		m.Z = fmax(m.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.positions.Add(m);

		if(forward){
			for(size_t m = 0; m < ptp[nopt].positions.GetCount(); m++){
				toolpath.positions.Add(ptp[nopt].positions[m]);
			}
		}else{
			for(size_t m = ptp[nopt].positions.GetCount(); m-- > 0;){
				toolpath.positions.Add(ptp[nopt].positions[m]);
			}
		}
		m = toolpath.positions.Last();
//		m.Z = fmax(m.Z, target.GetSizeZ() + freeHeight);
//		m.Rapid();
//		toolpath.positions.Add(m);

		ptp[nopt].inserted = true;
	}while(true);

// Move out of workpiece
	if((toolpath.GetCount() > 0)
			&& (toolpath.positions.Last().Z
					< (target.GetSizeZ() + freeHeight - FLT_EPSILON))){
		GCodeBlock m;
		//Note: Rotations are kept at zero for the starting position
		m.X = toolpath.positions.Last().X;
		m.Y = toolpath.positions.Last().Y;
		m.Z = target.GetSizeZ() + freeHeight;
		m.Rapid();
		toolpath.positions.Add(m);
	}

}

