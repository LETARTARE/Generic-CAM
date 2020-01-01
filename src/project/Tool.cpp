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

#include <GL/gl.h>
#include <math.h>
#include <float.h>
#include <iostream>

Tool::Tool()
{
	hasStartValues = false;
	hasGeometry = false;
	type = flat_end_mill;
	GRADE = "generic";
}

Tool::~Tool()
{
}

void Tool::Update(void)
{
	contour.clear();
	ContourElement temp;

	switch(type){
	case flat_end_mill:
		temp.Set(0, 0, geometry.DC / 2.0, 0, true);
		contour.push_back(temp);
		temp.Set(geometry.DC / 2.0, geometry.LCF, true);
		contour.push_back(temp);
		break;
	default:
		std::cout << "Tool::GenerateContour - Unsupported tooltype.\n";
		return;
		break;
	}

//	float xPosition = shaftDiameter / 2;
//	float zPosition = 0.0;
//
//
//
//	float d, x, z, r;
//	for(unsigned int j = 0; j < elements.Count(); j++){
//
//		x = (elements[j].d / 2) - xPosition;
//		z = elements[j].h;
//		r = elements[j].r;
//		d = x * x + z * z;
//		if(d > 0)
//			d = sqrt(d);
//		else
//			d = 1.0;
//
//		switch(elements[j].t){
//		case 1:
//			temp = new ToolContourElement(elements[j].cutting);
//			if(x > 0){
//				temp->n1.z = -1;
//				temp->n2.z = -1;
//			}else{
//				temp->n1.z = 1;
//				temp->n2.z = 1;
//			}
//			temp->p1.x = xPosition;
//			temp->p1.z = zPosition;
//			temp->p2.x = xPosition + x;
//			temp->p2.z = zPosition;
//			contour.Add(temp);
//			temp = new ToolContourElement(elements[j].cutting);
//			temp->n1.x = 1;
//			temp->n2.x = 1;
//			temp->p1.x = xPosition + x;
//			temp->p1.z = zPosition;
//			temp->p2.x = xPosition + x;
//			temp->p2.z = zPosition + z;
//			contour.Add(temp);
//			break;
//
//		case 2:
//			temp = new ToolContourElement(elements[j].cutting);
//			temp->n1.x = 1;
//			temp->n2.x = 1;
//			temp->p1.x = xPosition;
//			temp->p1.z = zPosition;
//			temp->p2.x = xPosition;
//			temp->p2.z = zPosition + z;
//			contour.Add(temp);
//			temp = new ToolContourElement(elements[j].cutting);
//			if(x > 0){
//				temp->n1.z = -1;
//				temp->n2.z = -1;
//			}else{
//				temp->n1.z = 1;
//				temp->n2.z = 1;
//			}
//			temp->p1.x = xPosition;
//			temp->p1.z = zPosition + z;
//			temp->p2.x = xPosition + x;
//			temp->p2.z = zPosition + z;
//			contour.Add(temp);
//			break;
//
//		case 3:
//			// calc h
//			if(x < 0){
//				r = xPosition;
//				z = sqrt(r * r - (xPosition + x) * (xPosition + x));
//			}else{
//				r = -xPosition;
//				if(x > 2 * xPosition) x = 2 * xPosition;
//				z = sqrt(r * r - (x - xPosition) * (x - xPosition));
//			}
//			elements[j].h = z;
//			elements[j].r = r;
//			break;
//		case 4:
//			// calc h
//			if(x > 0){
//				r = xPosition + x;
//				z = sqrt(r * r - xPosition * xPosition);
//			}else{
//				r = -(xPosition + x);
//				if(x < 2 * (xPosition + x)) x = 2 * (xPosition + x);
//				z = sqrt(r * r - (x + (x + xPosition)) * (x + (x + xPosition)));
//			}
//			elements[j].h = z;
//			elements[j].r = r;
//			break;
//		}
//
//		if(elements[j].t == 0 || elements[j].t == 3 || elements[j].t == 4){
//			if(fabs(r) < 1e-6){
//				temp = new ToolContourElement(elements[j].cutting);
//				temp->n1.x = z / d;
//				temp->n1.z = -x / d;
//				temp->n2.x = z / d;
//				temp->n2.z = -x / d;
//				temp->p1.x = xPosition;
//				temp->p1.z = zPosition;
//				temp->p2.x = xPosition + x;
//				temp->p2.z = zPosition + z;
//				contour.Add(temp);
//
//			}else{
//				d = sqrt(x * x + z * z);
//				float h = r * r - d * d / 4;
//				if(h < 0)
//					h = 0;
//				else
//					h = sqrt(h);
//				float x2, z2;
//				if(r > 0){
//					x2 = x / 2 - z * h / d;
//					z2 = z / 2 + x * h / d;
//				}else{
//					x2 = x / 2 + z * h / d;
//					z2 = z / 2 - x * h / d;
//				}
//				//wxLogMessage(wxString::Format(_T("x: %f z: %f"),x,z));
//				//wxLogMessage(wxString::Format(_T("x2: %f z2: %f"), x2, z2));
//				const float a = atan2(x, z);
//				const float a1 = a + asin(d / 2 / r);
//				const float a2 = a - asin(d / 2 / r);
//				//				wxLogMessage(wxString::Format(_T("a: %f a1: %f a2: %f"), a
//				//						/ M_PI * 180, a1 / M_PI * 180, a2 / M_PI * 180));
//				const unsigned int n = floor(fabs(a2 - a1) / M_PI * 180 / 15);
//				//wxLogMessage(wxString::Format(_T("n: %u"),n));
//				//wxLogMessage(wxString::Format(_T("r: %f x: %f, z: %f"),r,x,z));
//				for(unsigned int k = 0; k < n; k++){
//					const float cc1 = cos(
//							a1 + (a2 - a1) / (float) n * (float) k);
//					const float ss1 = -sin(
//							a1 + (a2 - a1) / (float) n * (float) k);
//					const float cc2 = cos(
//							a1 + (a2 - a1) / (float) n * (float) (k + 1));
//					const float ss2 = -sin(
//							a1 + (a2 - a1) / (float) n * (float) (k + 1));
//					temp = new ToolContourElement(elements[j].cutting);
//					temp->n1.x = cc1;
//					temp->n1.z = ss1;
//					temp->n2.x = cc2;
//					temp->n2.z = ss2;
//					temp->p1.x = cc1 * r + x2 + xPosition;
//					temp->p1.z = ss1 * r + z2 + zPosition;
//					temp->p2.x = cc2 * r + x2 + xPosition;
//					temp->p2.z = ss2 * r + z2 + zPosition;
//					contour.Add(temp);
//				}
//			}
//		}
//
//		zPosition += z;
//		xPosition += x;
//	}
}

void Tool::Paint(void) const
{
	const size_t resolution = 32;
	float ss[resolution + 1];
	float cc[resolution + 1];
	for(size_t i = 0; i <= resolution; i++){
		ss[i] = sin(-2.0 * M_PI / (float) resolution * (float) i);
		cc[i] = cos(-2.0 * M_PI / (float) resolution * (float) i);
	}
	for(size_t i = 0; i < contour.size(); i++){
		::glBegin(GL_QUAD_STRIP);
		for(size_t j = 0; j <= resolution; j++){
			::glNormal3f(cc[j] * contour[i].nx, ss[j] * contour[i].nx,
					contour[i].nz);
			::glVertex3f(cc[j] * contour[i].x0, ss[j] * contour[i].x0,
					contour[i].z0);
			::glNormal3f(cc[j] * contour[i].nx, ss[j] * contour[i].nx,
					contour[i].nz);
			::glVertex3f(cc[j] * contour[i].x1, ss[j] * contour[i].x1,
					contour[i].z1);
		}
		::glEnd();
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
//
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
}

Tool::Geometry::Geometry()
{
	CSP = false;
	DC = 0.0;
	HAND = false;
	LB = 0.0;
	LCF = 0.0;
	NOF = 0;
	NT = 1;
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

Tool::PostProcess::PostProcess()
{
	breakcontrol = false;
	diameteroffset = 0;
	lengthoffset = 0;
	live = true;
	manualtoolchange = false;
	number = 0;
	turret = 0;
}

Tool::StartValues::StartValues()
{
	fn = 1.0;
	fz = 1.0;
	n = 1.0;
	nramp = 1.0;
	vc = 1.0;
	vf = 1.0;
	vfleadin = 1.0;
	vfleadout = 1.0;
	vfplunge = 1.0;
	vframp = 1.0;
	vfretract = 1.0;
}

Tool::ContourElement::ContourElement()
{
	x0 = 0.0;
	z0 = 0.0;
	x1 = 0.0;
	z1 = 0.0;
	nx = 1.0;
	nz = 0.0;
	isCutting = false;
	belongsToShaft = false;
}

void Tool::ContourElement::Set(float x0, float z0, float x1, float z1,
		bool isCutting, bool belongsToShaft)
{
	this->x0 = x0;
	this->z0 = z0;
	this->x1 = x1;
	this->z1 = z1;
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
	this->isCutting = isCutting;
	this->belongsToShaft = belongsToShaft;
}

void Tool::ContourElement::Set(float x1, float z1, bool isCutting,
		bool belongsToShaft)
{
	this->Set(this->x1, this->z1, x1, z1, isCutting, belongsToShaft);
}
