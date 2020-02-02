///////////////////////////////////////////////////////////////////////////////
// Name               : Generator.cpp
// Purpose            : Abstract class for toolpath generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.08.2011
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

#include "Generator.h"

#include "../Run.h"
#include "../../3D/OpenGLMaterial.h"

#include <iostream>
#include "../../3D/OpenGL.h"

Generator::Generator()
{
//	parent = NULL;

	ID = 0;

	marginBelow = 0.0;
	marginSide = 0.0;
	freeHeight = 0.001;

	spindlespeed = 0.0;
	feedrate = 0.0;
	toolguid = "#1";

//	this->project = project;
//	this->runNr = runNr;
//	this->toolpathNr = toolpathNr;
//	if(project == NULL || runNr >= project->run.GetCount()
//			|| toolpathNr >= project->run[runNr].toolpaths.GetCount()){
//		this->toolpath = NULL;
//	}else{
//		this->toolpath = &(project->run[runNr].toolpaths[toolpathNr]);
//	}

	toolpathGenerated = false;
	errorOccured = false;
}

Generator::~Generator()
{
}

wxString Generator::GetName(void) const
{
	return name;
}

size_t Generator::GetID(void)
{
	return ID;
}

void Generator::CopyParameterFrom(const Generator * other)
{
	this->name = other->name;
	this->area = other->area;
	this->toolguid = other->toolguid;
	this->spindlespeed = other->spindlespeed;
	this->feedrate = other->feedrate;
	this->freeHeight = other->freeHeight;
	this->marginBelow = other->marginBelow;
	this->marginSide = other->marginSide;
}

bool Generator::operator ==(const Generator& b) const
{
	std::cout << "Generator::operator==\n";
	if(this->name != b.name) return false;
	if(this->area != b.area) return false;
	if(this->spindlespeed != b.spindlespeed) return false;
	if(this->feedrate != b.feedrate) return false;
	if(this->toolguid != b.toolguid) return false;
	if(this->freeHeight != b.freeHeight) return false;
	if(this->marginBelow != b.marginBelow) return false;
	if(this->marginSide != b.marginSide) return false;
	return true;
}

void Generator::Paint(void) const
{
	if(toolpath.size() < 2) return;
//	std::cout << "Generator::Paint - " << toolpath.size() << "\n";
	glPushMatrix();
//	glTranslatef(area.xmin, area.ymin, area.zmin);
	OpenGLMaterial::EnableColors();
	glBegin(GL_LINE_STRIP);
	for(std::vector <CNCPosition>::const_iterator it = toolpath.begin();
			it != toolpath.end(); ++it){
		if(it->rapid)
			glColor3f(1, 0, 0);
		else
			glColor3f(0, 1, 0);
		glNormal3f(it->normal.x, it->normal.y, it->normal.z);
		glVertex3f(it->position.x, it->position.y, it->position.z);
	}
	glEnd();
	glPopMatrix();
//	std::cout << "Generator::Paint - end\n";
}

void Generator::ToStream(wxTextOutputStream& stream)
{
//	area.ToStream(stream);
	stream << marginBelow << _T(" ") << marginSide << endl;
	stream << toolguid;
	stream << _T(" ") << freeHeight << endl;
//	stream << (int) runNr << _T(" ") << (int) toolpathNr << endl;
}

bool Generator::FromStream(wxTextInputStream& stream)
{
//	if(!area.FromStream(stream)) return false;
	stream >> marginBelow;
	stream >> marginSide;
//	stream >> toolguid;
	stream >> freeHeight;
//	runNr = stream.Read32();
//	toolpathNr = stream.Read32();
	return true;
}

//void Project::GenerateToolPath(void)
//{
//	size_t i, j;
//	bool isUsed;
//	for(i = 0; i < targets.GetCount(); i++){
//		if(targets[i].toolpath.IsEmpty()){
//
//			isUsed = false;
//			for(j = 0; j < run[activeRun].placements.GetCount(); j++){
//				if(!run[activeRun].placements[j].isKeepout
//						&& run[activeRun].placements[j].targetNumber == i) isUsed =
//						true;
//			}
//
//			if(isUsed){
//
//				wxLogMessage(
//						wxString::Format(
//								_T("Generating toolpath for target %u:"), i));
//
//				run[activeRun].ToolPathGenerator.GenerateToolpath(targets[i],
//						toolbox.tools[0]);
//			}
//		}
//	}
//	CollectToolPath();
//}

//void Project::CollectToolPath(void)
//{
//	size_t i, n;
//	ToolPath temp;
//	run[activeRun].toolPath.Clear();
//	MachinePosition mp;
//	if(true){ // Startup move, to prevent WinPC-NC from messing up the toolpath.
//		mp.axisX = 0.0;
//		mp.axisY = 0.0;
//		mp.axisZ = this->stock.stockMaterials[activeStock].sz + 0.010;
//		mp.isCutting = false;
//		run[activeRun].toolPath.positions.Add(mp);
//		mp.axisZ = this->stock.stockMaterials[activeStock].sz + 0.011;
//		mp.isCutting = true;
//		run[activeRun].toolPath.positions.Add(mp);
//	}
//
//	for(i = 0; i < run[activeRun].placements.GetCount(); i++){
//		if(!run[activeRun].placements[i].isKeepout){
//			n = run[activeRun].placements[i].targetNumber;
//			if(!targets[n].toolpath.IsEmpty()){
//				temp = targets[n].toolpath;
//				temp.ApplyTransformation();
//				temp.ApplyTransformation(run[activeRun].placements[i].matrix);
//				run[activeRun].toolPath += temp;
//			}
//		}
//	}
//}

