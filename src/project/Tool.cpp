///////////////////////////////////////////////////////////////////////////////
// Name               : Tool.cpp
// Purpose            : A tool for the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
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

#include "Tool.h"

#include "../3D/OpenGLMaterial.h"

#include <float.h>
#include <iostream>
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "../3D/OpenGL.h"

Tool::Tool()
{
	hasStartValues = false;
	hasPostProcess = false;
	hasGeometry = false;
	hasHolder = false;
	hasShaft = false;
	lastmodified = 0;
	addtonewprojects = false;
	unitinfile = unit_none;
}

Tool::~Tool()
{
}

bool Tool::operator ==(const std::string& guid) const
{
	return (base.guid.compare(guid) == 0);
}

void Tool::Update(void)
{
	if(!base.hasSegments){
		base.segments.clear();
		switch(base.type){
		case flat_end_mill:
		{
			Segment temp;
			temp.lowerdiameter = geometry.DC;
			temp.upperdiameter = geometry.DC;
			temp.height = geometry.LCF;
			temp.isCutting = true;
			base.segments.push_back(temp);
			if(geometry.shoulderlength > geometry.LCF){
				temp.isCutting = false;
				temp.height = geometry.shoulderlength - geometry.LCF;
				base.segments.push_back(temp);
			}
		}
			break;
		default:
			std::cout
					<< "Tool::GenerateContour - (Yet) Unsupported tooltype.\n";
			return;
			break;
		}
	}
	float z = 0.0;
	z = base.Update(z);
	if(!shaft.hasSegments){
		shaft.segments.clear();
		Segment temp;
		if(geometry.SFDM > 1e-6){
			temp.lowerdiameter = geometry.SFDM;
			temp.upperdiameter = geometry.SFDM;
		}else{
			temp.lowerdiameter = geometry.DC;
			temp.upperdiameter = geometry.DC;
		}
		temp.height = geometry.OAL - z;
		shaft.segments.push_back(temp);
	}
	z = shaft.Update(z);
	if(hasGeometry){
		if(geometry.LB > 1e-6) z = geometry.LB;
	}
	holder.Update(z);
}

void Tool::Paint(bool showHolder, bool showShaft, bool showTool) const
{
	if(showTool){
		OpenGLMaterial mat(OpenGLMaterial::cGray);
		mat.UseMaterial();
		base.Paint();
	}
	if(showShaft){
		OpenGLMaterial mat(OpenGLMaterial::cSilver);
		mat.UseMaterial();
		shaft.Paint();
	}
	if(showHolder){
		OpenGLMaterial mat(OpenGLMaterial::cAqua);
		mat.UseMaterial();
		holder.Paint();
	}
}

float Tool::GetToolLength(void) const
{
	return geometry.LB;
}

float Tool::GetMaxDiameter(void) const
{
	return geometry.DC;
}

float Tool::GetCuttingDepth(void) const
{
	return geometry.LCF;
}

//void Tool::ToStream(wxTextOutputStream & stream)
//{
//	stream << _T("Tool:") << endl;
//	stream << toolName << endl;
//	stream << _T("Comment:") << endl;
//	wxString temp = comment;
//	temp.Replace(wxT("\n"), wxT("\\n"));
//	temp.Replace(wxT("\r"), wxT("\\r"));
//	stream << temp << endl;
//	stream << _T("Parameter: ");
//	stream << shaftDiameter << _T(" ");
//	stream << shaftLength << _T(" ");
//	stream << maxSpeed << _T(" ");
//	stream << feedCoefficient << _T(" ");
//	stream << nrOfTeeth << _T(" ");
//	stream << slotNr << _T(" ");
//	stream << endl;
//	stream << _T("Elements: ");
//	stream << wxString::Format(_T("%zu"), elements.GetCount());
//	stream << endl;
//	for(size_t n = 0; n < elements.GetCount(); n++){
//		stream << elements[n].ToString() << endl;
//	}
//}

//bool Tool::FromStream(wxTextInputStream& stream)
//{
//	wxString temp;
//	temp = stream.ReadLine();
//	if(temp.Cmp(_T("Tool:")) != 0) return false;
//	toolName = stream.ReadLine();
//	temp = stream.ReadLine();
//	if(temp.Cmp(_T("Comment:")) != 0) return false;
//	temp = stream.ReadLine();
//	temp.Replace(wxT("\\n"), wxT("\n"));
//	temp.Replace(wxT("\\r"), wxT("\r"));
//	comment = temp;
//	temp = stream.ReadWord();
//	if(temp.Cmp(_T("Parameter:")) != 0) return false;
//	stream >> shaftDiameter;
//	stream >> shaftLength;
//	stream >> maxSpeed;
//	stream >> feedCoefficient;
//	stream >> nrOfTeeth;
//	stream >> slotNr;
//	temp = stream.ReadWord();
//	if(temp.Cmp(_T("Elements:")) != 0) return false;
//	const size_t N = stream.Read32();
//	ToolElement element;
//	elements.Clear();
//	for(size_t n = 0; n < N; n++){
//		temp = stream.ReadLine();
//		element.FromString(temp);
//		elements.Add(element);
//	}
//	GenerateContour();
//	return true;
//}

Tool::Segment::Segment()
{
	height = 0.0;
	lowerdiameter = 0.0;
	upperdiameter = 0.0;
	x0 = 0.0;
	z0 = 0.0;
	x1 = 0.0;
	z1 = 0.0;
	nx = 1.0;
	nz = 0.0;
	isCutting = false;
}

Tool::Geometry::Geometry()
{
	CSP = false;
	DC = 0.0;
	HAND = false;
	LB = 0.0;
	LCF = 0.0;
	NOF = 0;
	NT = 0;
	OAL = 0.0;
	RE = 0.0;
	SFDM = 0.0;
	SIG = 0.0;
	TA = 0.0;
	TP = 0.0;
	shoulderlength = 0.0;
	threadprofileangle = 0.0;
	tipdiameter = 0.0;
	tiplength = 0.0;
	tipoffset = 0.0;
}

void Tool::ConvertToSI(void)
{
	UnitType unit = base.unit;
	if(unit == unit_SI || unit == unit_none) return;
	this->unitinfile = unit;

	// Geometry
	if(unit == unit_millimeter){
		geometry.DC *= 1.0e-3;
		geometry.LB *= 1.0e-3;
		geometry.LCF *= 1.0e-3;
		geometry.OAL *= 1.0e-3;
		geometry.RE *= 1.0e-3;
		geometry.SFDM *= 1.0e-3;
		geometry.TP *= 1.0e-3;
		geometry.shoulderlength *= 1.0e-3;
		geometry.tipdiameter *= 1.0e-3;
		geometry.tiplength *= 1.0e-3;
		geometry.tipoffset *= 1.0e-3;
	}
	if(unit == unit_inch){
		geometry.DC *= 2.54e-2;
		geometry.LB *= 2.54e-2;
		geometry.LCF *= 2.54e-2;
		geometry.OAL *= 2.54e-2;
		geometry.RE *= 2.54e-2;
		geometry.SFDM *= 2.54e-2;
		geometry.TP *= 2.54e-2;
		geometry.shoulderlength *= 2.54e-2;
		geometry.tipdiameter *= 2.54e-2;
		geometry.tiplength *= 2.54e-2;
		geometry.tipoffset *= 2.54e-2;
	}

	// Start values
	if(unit == unit_millimeter){
		startvalues.fn *= 1.0e-3;
		startvalues.fz *= 1.0e-3;

		startvalues.n /= 60.0;
		startvalues.nramp /= 60.0;

		startvalues.vc *= (1.0e-3 / 60.0);
		startvalues.vf *= (1.0e-3 / 60.0);
		startvalues.vfleadin *= (1.0e-3 / 60.0);
		startvalues.vfleadout *= (1.0e-3 / 60.0);
		startvalues.vfplunge *= (1.0e-3 / 60.0);
		startvalues.vframp *= (1.0e-3 / 60.0);
		startvalues.vfretract *= (1.0e-3 / 60.0);
	}
	if(unit == unit_inch){
		startvalues.fn *= 2.54e-2;
		startvalues.fz *= 2.54e-2;
		startvalues.n /= 60.0;
		startvalues.nramp /= 60.0;
		startvalues.vc *= (2.54e-2 / 60.0);
		startvalues.vf *= (2.54e-2 / 60.0);
		startvalues.vfleadin *= (2.54e-2 / 60.0);
		startvalues.vfleadout *= (2.54e-2 / 60.0);
		startvalues.vfplunge *= (2.54e-2 / 60.0);
		startvalues.vframp *= (2.54e-2 / 60.0);
		startvalues.vfretract *= (2.54e-2 / 60.0);
	}
	shaft.ConvertToSI(unit);
	holder.ConvertToSI(unit);
	this->base.unit = unit_SI;
}

Tool::PostProcess::PostProcess()
{
	breakcontrol = false;
	diameteroffset = 0;
	lengthoffset = 0;
	live = false;
	manualtoolchange = false;
	number = 0;
	turret = 0;
}

Tool::StartValues::StartValues()
{
	fn = 0.0;
	fz = 0.0;
	n = 0.0;
	nramp = 0.0;
	vc = 0.0;
	vf = 0.0;
	vfleadin = 0.0;
	vfleadout = 0.0;
	vfplunge = 0.0;
	vframp = 0.0;
	vfretract = 0.0;
}

float Tool::Segment::Update(float z)
{
	z0 = z;
	z1 = z0 + height;
	x0 = lowerdiameter / 2.0;
	x1 = upperdiameter / 2.0;
	const float dx = x1 - x0;
	const float dz = z1 - z0;
	const float d2 = dx * dx + dz * dz;
	if(d2 > FLT_EPSILON){
		const float d = sqrt(d2);
		this->nx = dz / d;
		this->nz = -dx / d;
	}else{
		this->nx = 1.0;
		this->nz = 0.0;
	}
	return z1;
}

Tool::Contour::Contour()
{
	hasSegments = false;
	type = no_type;
	unit = unit_none;
}

void Tool::Contour::ConvertToSI(UnitType baseunit)
{
	if(!hasSegments) return;
	UnitType unit = baseunit;
	if(this->unit != unit_none) unit = this->unit;
	if(unit == unit_millimeter){
		for(std::vector <Segment>::iterator it = segments.begin();
				it != segments.end(); ++it){
			it->height *= 1.0e-3;
			it->upperdiameter *= 1.0e-3;
			it->lowerdiameter *= 1.0e-3;
		}
		this->unit = unit_SI;
	}
	if(unit == unit_inch){
		for(std::vector <Segment>::iterator it = segments.begin();
				it != segments.end(); ++it){
			it->height *= 2.54e-2;
			it->upperdiameter *= 2.54e-2;
			it->lowerdiameter *= 2.54e-2;
		}
		this->unit = unit_SI;
	}
}

float Tool::Contour::Update(float z)
{
	for(std::vector <Segment>::iterator it = segments.begin();
			it != segments.end(); ++it)
		z = it->Update(z);
	return z;
}

void Tool::Contour::Paint(void) const
{
	const size_t resolution = 32;
	float ss[resolution + 1];
	float cc[resolution + 1];
	for(size_t i = 0; i <= resolution; i++){
		ss[i] = sin(-2.0 * M_PI / (float) resolution * (float) i);
		cc[i] = cos(-2.0 * M_PI / (float) resolution * (float) i);
	}
	float r = 0.0;
	for(size_t n = 0; n < segments.size(); ++n){
		const Segment &seg = segments[n];
		if(seg.x0 > r){
			glNormal3f(0, 0, -1);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0, 0, seg.z0);
			for(size_t n = 0; n <= resolution; ++n)
				glVertex3f(seg.x0 * cc[n], seg.x0 * ss[n], seg.z0);
			glEnd();
		}
		glBegin(GL_QUAD_STRIP);
		for(size_t n = 0; n <= resolution; ++n){
			glNormal3f(seg.nx * cc[n], seg.nx * ss[n], seg.nz);
			glVertex3f(seg.x0 * cc[n], seg.x0 * ss[n], seg.z0);
			glVertex3f(seg.x1 * cc[n], seg.x1 * ss[n], seg.z1);
		}
		glEnd();

		glNormal3f(0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, seg.z1);
		for(size_t n = 0; n <= resolution; ++n)
			glVertex3f(seg.x1 * cc[n], -seg.x1 * ss[n], seg.z1);
		glEnd();
		r = seg.x1;
	}

}

