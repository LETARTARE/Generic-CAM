///////////////////////////////////////////////////////////////////////////////
// Name               : CNCSimulator.cpp
// Purpose            : A simulator for the machine operation.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CNCSimulator.h"

#include "../Project.h"

#include <wx/textfile.h>

#include <iostream>
#include <float.h>
#include <wx/filename.h>

#include "../../3D/OpenGL.h"
#include "../../Config.h"

CNCSimulator::CNCSimulator()
{
	initialized = false;
	tStep = 0;
	step = 0;

	tools = NULL;
	tool = NULL;
	basetarget = NULL;
	toolpath = NULL;
}

CNCSimulator::~CNCSimulator()
{
}

void CNCSimulator::SetTools(const std::vector <Tool> * tools)
{
	this->tools = tools;
}

std::string CNCSimulator::GetToolID(void) const
{
	if(tool == NULL) return "";
	return tool->GetGUID();
}
void CNCSimulator::InsertBase(const DexelTarget* target)
{
	if(this->basetarget == target && target != NULL) return;
	this->basetarget = target;
	initialized = false;
}

void CNCSimulator::InsertToolPath(const std::vector <CNCPosition> * toolpath)
{
	this->toolpath = toolpath;
}

void CNCSimulator::Reset(void)
{
	if(!initialized){
		simulated.displayBox = true;
		initialized = true;
	}
	if(basetarget != NULL){
		if(DEBUG) printf("CNCSimulator::Reset: to Pointer %p with N=%zu\n",
				basetarget, basetarget->GetCountTotal());
		simulated = *basetarget;
	}else{
		simulated.Empty();
	}
	tStep = 0.0;
	step = 0;
}

void CNCSimulator::Step(float tTarget)
{
	if(!initialized) return;
	if(toolpath == NULL || (toolpath->size()) < 2) return;

	if(tTarget < (*toolpath)[0].dt || tTarget < tStep) Reset();

	Polygon3 temp;
	temp.InsertPoint((*toolpath)[step].position);

	while((step + 1) < (*toolpath).size() && tTarget > tStep){
		step++;
		tStep = (*toolpath)[step].t + (*toolpath)[step].dt;
		temp.InsertPoint((*toolpath)[step].position);
	}

	//TODO Add multi-tool toolpaths (bigger loop)
	tool = NULL;
	for(std::vector <Tool>::const_iterator it = tools->begin();
			it != tools->end(); ++it){
		if(it->postprocess.number == (*toolpath)[step].toolSlot){
			tool = &(*it);
		}
	}
	if(tool == NULL){
		std::cout << "NCSimulator::Step(...) - Tool T"
				<< (*toolpath)[step].toolSlot << " not found.\n";
		return;
	}

	DexelTarget dex;
	dex.SetupTool(*tool, simulated.GetResolutionX(),
			simulated.GetResolutionY());
//		dex.MirrorZ();
	dex.NegateZ();

	AffineTransformMatrix shift = stockposition * (origin.Inverse());
	temp.ApplyTransformation(shift);
	simulated.PolygonCutInTarget(temp, dex);

//	if((step + 1) < (*toolpath).size()){

	machineposition = (*toolpath)[step];
	tooltipposition = machineposition.GetMatrix();

//	}else{
//
//		machineposition = (*toolpath)[step]
//				+ ((*toolpath)[step + 1] - (*toolpath)[step])
//						/ (*toolpath)[step].dt * (tTarget - tStep);
//
//	}
}

void CNCSimulator::Previous(void)
{
	if(toolpath == NULL || toolpath->empty()) return;
	if(step >= 1) Step((*toolpath)[step - 1].t + FLT_EPSILON);
}

void CNCSimulator::Next(void)
{
	if(toolpath == NULL || toolpath->empty()) return;
	if((step - 1) < (*toolpath).size()) Step(
			(*toolpath)[step + 1].t + FLT_EPSILON);
}

void CNCSimulator::Last(void)
{
	if(toolpath == NULL || toolpath->empty()) return;
	Step(GetMaxTime());
}

void CNCSimulator::FullSimulation(void)
{
	Reset();
	Last();
}

double CNCSimulator::GetMaxTime(void) const
{
	if(toolpath == NULL || toolpath->empty()) return 0.0;
	return (*toolpath).at((*toolpath).size() - 1).t;
}

double CNCSimulator::GetTime(void) const
{
	return tStep;
}

const DexelTarget* CNCSimulator::GetResult(void) const
{
	return &simulated;
}

void CNCSimulator::PaintSimulation(void) const
{
	if(!initialized) return;
	glPushMatrix();
	simulated.Paint();
	glPopMatrix();
}

void CNCSimulator::PaintMachine(void) const
{
	if(!machine.IsLoaded()) return;
	machine.Paint();
}

void CNCSimulator::PaintTool(bool paintHolder) const
{
	if(tool == NULL) return;
	glPushMatrix();
	tooltipposition.GLMultMatrix();
	tool->Paint(paintHolder, true, true);
	glPopMatrix();
}

bool CNCSimulator::LoadMachine(const wxFileName &filename)
{
	if(filename != machine.fileName || !machine.IsLoaded()){
		bool flag = machine.Load(filename);

		if(tool == NULL){
			machine.SetToolLength(0.0);
		}else{
			machine.SetToolLength(tool->GetFullLength());
		}
		machine.SetPosition(CNCPosition());
		machine.Assemble();
		workpieceposition0 = machine.workpiecePosition;
		return flag;
	}
	return true;
}

AffineTransformMatrix CNCSimulator::GetMachineCenter(void) const
{
	if(tool == NULL){
		machine.SetToolLength(0.0);
	}else{
		machine.SetToolLength(tool->GetFullLength());
	}
	machine.SetPosition(machineposition);
	machine.Assemble();
	return machine.workpiecePosition.Inverse();
}

AffineTransformMatrix CNCSimulator::GetToolPosition(void) const
{
	return tooltipposition;
}

AffineTransformMatrix CNCSimulator::GetWorkpiecePosition0(void) const
{
	return workpieceposition0;
}
