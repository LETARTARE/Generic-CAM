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

GeneratorDexel::GeneratorDexel()
{
	area.alpha = 1.0;
	area.displaySides = false;
	area.displayBox = true;

#ifdef _DEBUGMODE
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
	mask -= temp;

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
		mask |= temp;
	}
	target.FinishImprint();
	for(size_t i = 0; i < workpiece->supports.GetCount(); i++){
		//TODO: Insert supports into target.
	}

	// TODO Check why in a direct c = a & b; the overloaded & does not return a DexelTarget.
	temp = start;
	temp &= mask;
	target |= temp;

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

