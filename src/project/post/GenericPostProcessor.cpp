///////////////////////////////////////////////////////////////////////////////
// Name               : Generic PostProcessor.cpp
// Purpose            : Minimal Postprocessor
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "GenericPostProcessor.h"

#include <iostream>
#include <fstream>
#include <float.h>

GenericPostProcessor::Axis::Axis()
{
	ref = X;
	negativ = false;
	rotational = false;
	factorLength = 1000.0;
	factorAngle = 180.0 / M_PI;
	value = 0.0;
	oldValue = 0.0;
}

void GenericPostProcessor::Axis::Set(const Vector3& position, Vector3& normal)
{
	oldValue = value;
	if(rotational){
		const double tempx = normal.x;
		const double tempy = normal.y;
		const double tempz = normal.z;
		switch(ref){
		case X:
		{
			value = atan2(-normal.y, normal.z);
			const double c = cos(value);
			const double s = sin(value);
			normal.y = tempy * c - tempz * s;
			normal.z = tempz * c + tempy * s;
			break;
		}
		case Y:
		{
			value = atan2(normal.x, normal.z);
			const double c = cos(value);
			const double s = sin(value);
			normal.x = tempx * c + tempz * s;
			normal.z = tempz * c - tempx * s;
			break;
		}
		case Z:
		{
			value = atan2(normal.y, normal.x);
			const double c = cos(value);
			const double s = sin(value);
			normal.y = tempy * c + tempx * s;
			normal.x = tempx * c - tempy * s;
			break;
		}
		}
		value *= factorAngle;
	}else{
		switch(ref){
		case X:
			value = position.x;
			break;
		case Y:
			value = position.y;
			break;
		case Z:
			value = position.z;
			break;
		}
		value *= factorLength;
	}
}

std::ostream& operator<<(std::ostream &out,
		const GenericPostProcessor::Axis &axis)
{
	if(fabs(axis.oldValue - axis.value) < FLT_EPSILON) return out;
	out << " " << axis.name << ((axis.negativ)? (-axis.value) : axis.value);
	return out;
}

GenericPostProcessor::GenericPostProcessor(const std::string name) :
		PostProcessor(name)
{
	configuration = "XYZ"; // Long form: +X~X +Y~Y +Z~Z
	// 5 axis CNC: XYZB~X-A~Y   +X~X +Y~Y +Z~Z +B~X -A~Y
	// Switched axes: X~Y Y~Z Z~X
	preblock =
			"G90 G80 G40 G54 G21 G17 G50 G94 G64 (safety block)\nG49 (disable tool length compensation)\nG80 (disable modal motion)\nG64 P2 (exact path mode)";
	postblock =
			"M5 (stop spindel)\nG4 P3 (wait for 3 seconds)\nM2 (end programm)";
}

GenericPostProcessor::~GenericPostProcessor()
{
}

std::map <std::string, std::string> GenericPostProcessor::GetParameter(
		void) const
{
	std::map <std::string, std::string> temp;
	temp["preblock"] = preblock;
	temp["configuration"] = configuration;
	temp["postblock"] = postblock;
	return temp;
}

bool GenericPostProcessor::SetParameter(std::string name, std::string value)
{
	if(name.compare("preblock") == 0){
		preblock = value;
		return true;
	}
	if(name.compare("configuration") == 0){
		configuration = value;
		return true;
	}
	if(name.compare("postblock") == 0){
		postblock = value;
		return true;
	}
	return false;
}

void GenericPostProcessor::Update(void)
{
	axis.clear();
	Axis temp;
	temp.oldValue = -FLT_MAX;
	int state = 0;

	for(size_t n = 0; n < configuration.size(); ++n){
		const char c = configuration[n];
		if(c <= 32) continue;
		int newState = -1;

		if((state == 1 || state == 3)
				&& ((c >= 'u' && c <= 'z') || (c >= 'U' && c <= 'Z')
						|| (c >= 'A' && c <= 'C') || (c >= 'A' && c <= 'C')
						|| c == '+' || c == '-')){
			axis.push_back(temp);
			temp.negativ = false;
			temp.oldValue = -FLT_MAX;
		}
		if(state == 1 || state == 3){
			if(c == '-') temp.negativ = true;
			if(c == '+') temp.negativ = false;
		}
		if(state == 0 || state == 1 || state == 3){
			if(c == 'a' || c == 'A' || c == 'x' || c == 'X' || c == 'u'
					|| c == 'U') temp.ref = Axis::X;
			if(c == 'b' || c == 'B' || c == 'y' || c == 'Y' || c == 'v'
					|| c == 'V') temp.ref = Axis::Y;
			if(c == 'c' || c == 'C' || c == 'z' || c == 'Z' || c == 'w'
					|| c == 'W') temp.ref = Axis::Z;
			if((c >= 'u' && c <= 'z') || (c >= 'U' && c <= 'Z')
					|| (c >= 'A' && c <= 'C') || (c >= 'A' && c <= 'C')){
				temp.name = std::string(1, c);
				newState = 1;
			}
		}
		if(state == 1 && c == '~') newState = 2;
		if(state == 2){
			if(c == 'x' || c == 'X') temp.ref = Axis::X;
			if(c == 'y' || c == 'Y') temp.ref = Axis::Y;
			if(c == 'z' || c == 'Z') temp.ref = Axis::Z;
			if((c >= 'X' && c <= 'Z') || (c >= 'x' && c <= 'z')) newState = 3;
		}
		state = newState;
	}
	if(state == 1 || state == 3) axis.push_back(temp);
}

bool GenericPostProcessor::SaveGCode(std::string filename)
{
	Update();
	std::ofstream out(filename.c_str(), std::ofstream::out);
	out << preblock << "\n";

	CNCPosition oldPosition;
	double oldF = 0.0;
	double oldS = 0.0;

	for(std::vector <CNCPosition>::const_iterator it = toolpath->begin();
			it != toolpath->end(); ++it){

		if(oldS <= FLT_EPSILON && it->S > FLT_EPSILON){
			out << "M3 (start spindel ccw)\nG4 P3 (wait for 3 seconds)\n";
		}
		if(oldS >= -FLT_EPSILON && it->S < FLT_EPSILON){
			out << "M4 (start spindel cw)\nG4 P3 (wait for 3 seconds)\n";
		}

		Vector3 normal = it->normal;
		for(std::vector <Axis>::iterator a = axis.begin(); a != axis.end();
				++a){
			a->Set(it->position, normal);
			out << *a;
		}
		if(fabs(oldF - it->F) > FLT_EPSILON){
			out << " F" << (fabs(it->F) * 1000.0);
		}

		if(fabs(oldS - it->S) > FLT_EPSILON){
			out << " S" << (fabs(it->S) * 60.0);
		}
		out << "\n";

		if(fabs(oldS) > FLT_EPSILON && fabs(it->S) < FLT_EPSILON){
			out << "M5 (stop spindel)\nG4 P3 (wait for 3 seconds)\n";
		}
		oldF = it->F;
		oldS = it->S;
	}
	out << postblock << "\n";
	return out.good();
}

