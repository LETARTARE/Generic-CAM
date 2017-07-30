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

GeneratorDexel::GeneratorDexel()
{
	area.alpha = 1.0;
	area.displaySides = false;
	area.displayBox = true;

	target.displayField = false;

	debug.displayField = false;
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

	glPushMatrix();
	glTranslatef(area.xmin, area.ymin, area.zmin);
	target.Paint();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(area.xmin - 0.0, area.ymin, area.zmin);
	debug.Paint();
	glPopMatrix();

}

void GeneratorDexel::GenerateToolpath(void)
{

	const double resX = 0.001;
	const double resY = 0.001;

	target.SetupBox(area.GetSizeX(), area.GetSizeY(), area.GetSizeZ(), resX,
			resY);
	target.InitImprinting();

	const Run* const run = this->parent;
	assert(run != NULL);
	const Project* const project = run->parent;
	assert(project != NULL);
	const Workpiece* const workpiece = &(project->workpieces[run->refWorkpiece]);
	assert(workpiece != NULL);

	AffineTransformMatrix tempMatrix;

	DexelTarget outside(target);
	outside.SetupBox(area.GetSizeX(), area.GetSizeY(), area.GetSizeZ(), resX,
			resY);

	outside.Empty();

	for(size_t i = 0; i < workpiece->placements.GetCount(); i++){
		const ObjectPlacement* const opl = &(workpiece->placements[i]);
		size_t refObject = opl->refObject;
		Object* object = &(project->objects[refObject]);
		tempMatrix.SetIdentity();
		tempMatrix.TranslateGlobal(-area.xmin, -area.ymin, -area.zmin);
		tempMatrix *= opl->matrix;
		target.InsertObject(*object, tempMatrix);

		DexelTarget temp(target);
		temp.InitImprinting();
		if(opl->useContour){
			temp.InsertObject(*object, tempMatrix);
			temp.FinishImprint();
			DexelTarget discSlot;
			discSlot.SetupDisc(opl->slotWidth, resX, resY);
			temp.FoldRaise(discSlot);
		}else{
			temp.InsertTriangle(
					Vector3(opl->xmin - area.xmin, opl->ymin - area.ymin,
							opl->zmax - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymin - area.ymin,
							opl->zmax - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymax - area.ymin,
							opl->zmax - area.zmin), Imprinter::facing_up);
			temp.InsertTriangle(
					Vector3(opl->xmin - area.xmin, opl->ymin - area.ymin,
							opl->zmax - area.zmin),
					Vector3(opl->xmin - area.xmin, opl->ymax - area.ymin,
							opl->zmax - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymax - area.ymin,
							opl->zmax - area.zmin), Imprinter::facing_up);
			temp.InsertTriangle(
					Vector3(opl->xmin - area.xmin, opl->ymin - area.ymin,
							opl->zmin - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymin - area.ymin,
							opl->zmin - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymax - area.ymin,
							opl->zmin - area.zmin), Imprinter::facing_down);
			temp.InsertTriangle(
					Vector3(opl->xmin - area.xmin, opl->ymin - area.ymin,
							opl->zmin - area.zmin),
					Vector3(opl->xmin - area.xmin, opl->ymax - area.ymin,
							opl->zmin - area.zmin),
					Vector3(opl->xmax - area.xmin, opl->ymax - area.ymin,
							opl->zmin - area.zmin), Imprinter::facing_down);
			temp.FinishImprint();
		}

		outside += temp;
	}
	for(size_t i = 0; i < workpiece->supports.GetCount(); i++){
		//TODO: Insert supports into target.
	}
	target.FinishImprint();
//	target.CleanOutlier();
	outside.HardInvert();

	// Draw a single cell line on the outside of the area to keep the tool inside the
	// pocket.
	//TODO Turn this feature off, if the working area is bigger or the same size as the workpiece in XY.
	outside.MarkOutline();

	target += outside;

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

