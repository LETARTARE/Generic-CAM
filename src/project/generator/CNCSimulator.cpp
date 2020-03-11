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
#include "../../3D/OpenGL.h"

CNCSimulator::CNCSimulator()
{
	initialized = false;
	tStep = 0;
	step = 0;

	tools = NULL;
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

void CNCSimulator::InsertBase(DexelTarget* target)
{
	if(this->basetarget == target && target != NULL) return;
	this->basetarget = target;
	initialized = false;
}

void CNCSimulator::InsertToolPath(std::vector <CNCPosition> * toolpath,
		bool calculateTiming)
{
	std::cout << "CNCSimulator::InsertToolPath(..., " << calculateTiming
			<< ")\n";

	const double minimumFeed = 1e-9; // 1 nm/s (If this should ever be a problem, I would love to know the field of application.)

	if(this->toolpath == toolpath && toolpath != NULL) return;
	this->toolpath = toolpath;
	if(calculateTiming && toolpath != NULL && toolpath->size() > 0){
		const size_t N = toolpath->size();
		double t = 0.0;
		for(size_t n = 0; (n + 1) < N; ++n){
			(*toolpath)[n].t = t;
			const double d = (*toolpath)[n].Abs((*toolpath)[n + 1]);
			(*toolpath)[n].dt = d * fmax((*toolpath)[n].F, minimumFeed);
			t += (*toolpath)[n].dt;
		}
		if(N > 0) (*toolpath)[N - 1].t = t;
	}
}

void CNCSimulator::Reset(void)
{
	if(!initialized){
		simulated.displayBox = true;
		initialized = true;
	}
	if(basetarget != NULL){
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
	const Tool * tool = NULL;
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
	dex.SetupTool(*tool, simulated.GetResolutionX(), simulated.GetResolutionY());
//		dex.MirrorZ();
		dex.NegateZ();

	AffineTransformMatrix shift = stockposition * (origin.Inverse());
	temp.ApplyTransformation(shift);
	simulated.PolygonCutInTarget(temp, dex);

//	if(step + 1 == position.size()){
//		machine->position = position[step];
//	}else{
//		machine->position = position[step]
//				+ (position[step + 1] - position[step])
//						/ position[step].duration * (tTarget - tStep);
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

void CNCSimulator::Paint(void) const
{
	if(!initialized) return;
	glPushMatrix();
	simulated.Paint();
	glPopMatrix();
}
