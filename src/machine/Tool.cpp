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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "Tool.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTool)

#include <GL/gl.h>
#include <math.h>
#include <wx/log.h>

Tool::Tool() :
	resolution(32)
{
	feedCoefficient = 0.005;
	maxSpeed = 10000;
	nrOfTeeth = 3;
	shaftDiameter = 0.006;
	shaftLength = 0.01;
	slot = 0;
}

Tool::~Tool()
{

}

void Tool::GenerateContour(void)
{
	contour.Clear();

	float xPosition = shaftDiameter / 2;
	float zPosition = 0.0;

	ToolContourElement* temp;


	// Cap on top
	temp = new ToolContourElement(false, true);
	temp->n1.z = -1;
	temp->p1.z = -shaftLength;
	temp->n2.z = -1;
	temp->p2.x = xPosition;
	temp->p2.z = -shaftLength;
	contour.Add(temp);


	// Top part of shaft
	temp = new ToolContourElement(false, true);
	temp->n1.x = 1;
	temp->p1.x = xPosition;
	temp->p1.z = -shaftLength;
	temp->n2.x = 1;
	temp->p2.x = xPosition;
	contour.Add(temp);

	float d, x, z, r;
	unsigned int j;
	for(j = 0; j < elements.Count(); j++){

		x = (elements[j].d / 2) - xPosition;
		z = elements[j].h;
		r = elements[j].r;
		d = x * x + z * z;
		if(d > 0)
			d = sqrt(d);
		else
			d = 1.0;

		switch(elements[j].t){
		case 1:
			temp = new ToolContourElement(elements[j].cutting);
			if(x > 0){
				temp->n1.z = -1;
				temp->n2.z = -1;
			}else{
				temp->n1.z = 1;
				temp->n2.z = 1;
			}
			temp->p1.x = xPosition;
			temp->p1.z = zPosition;
			temp->p2.x = xPosition + x;
			temp->p2.z = zPosition;
			contour.Add(temp);
			temp = new ToolContourElement(elements[j].cutting);
			temp->n1.x = 1;
			temp->n2.x = 1;
			temp->p1.x = xPosition + x;
			temp->p1.z = zPosition;
			temp->p2.x = xPosition + x;
			temp->p2.z = zPosition + z;
			contour.Add(temp);
			break;

		case 2:
			temp = new ToolContourElement(elements[j].cutting);
			temp->n1.x = 1;
			temp->n2.x = 1;
			temp->p1.x = xPosition;
			temp->p1.z = zPosition;
			temp->p2.x = xPosition;
			temp->p2.z = zPosition + z;
			contour.Add(temp);
			temp = new ToolContourElement(elements[j].cutting);
			if(x > 0){
				temp->n1.z = -1;
				temp->n2.z = -1;
			}else{
				temp->n1.z = 1;
				temp->n2.z = 1;
			}
			temp->p1.x = xPosition;
			temp->p1.z = zPosition + z;
			temp->p2.x = xPosition + x;
			temp->p2.z = zPosition + z;
			contour.Add(temp);
			break;

		case 3:
			// calc h
			if(x < 0){
				r = xPosition;
				z = sqrt(r * r - (xPosition + x) * (xPosition + x));
			}else{
				r = -xPosition;
				if(x > 2* xPosition ) x = 2* xPosition ;
				z = sqrt(r * r - (x - xPosition) * (x - xPosition));
			}
			elements[j].h = z;
			elements[j].r = r;
			break;
		case 4:
			// calc h
			if(x > 0){
				r = xPosition + x;
				z = sqrt(r * r - xPosition * xPosition);
			}else{
				r = -(xPosition + x);
				if(x < 2 * (xPosition + x)) x = 2 * (xPosition + x);
				z = sqrt(r * r - (x + (x + xPosition)) * (x + (x + xPosition)));
			}
			elements[j].h = z;
			elements[j].r = r;
			break;
		}

		if(elements[j].t == 0 || elements[j].t == 3 || elements[j].t == 4){
			if(fabs(r) < 1e-6){
				temp = new ToolContourElement(elements[j].cutting);
				temp->n1.x = z / d;
				temp->n1.z = -x / d;
				temp->n2.x = z / d;
				temp->n2.z = -x / d;
				temp->p1.x = xPosition;
				temp->p1.z = zPosition;
				temp->p2.x = xPosition + x;
				temp->p2.z = zPosition + z;
				contour.Add(temp);

			}else{
				d = sqrt(x * x + z * z);
				float h = r * r - d * d / 4;
				if(h < 0)
					h = 0;
				else
					h = sqrt(h);
				float x2, z2;
				if(r > 0){
					x2 = x / 2 - z * h / d;
					z2 = z / 2 + x * h / d;
				}else{
					x2 = x / 2 + z * h / d;
					z2 = z / 2 - x * h / d;
				}
				//wxLogMessage(wxString::Format(_T("x: %f z: %f"),x,z));
				//wxLogMessage(wxString::Format(_T("x2: %f z2: %f"), x2, z2));
				float a = atan2(x, z);
				float a1 = a + asin(d / 2 / r);
				float a2 = a - asin(d / 2 / r);
				//				wxLogMessage(wxString::Format(_T("a: %f a1: %f a2: %f"), a
				//						/ M_PI * 180, a1 / M_PI * 180, a2 / M_PI * 180));
				unsigned char n = floor(fabs(a2 - a1) / M_PI * 180 / 15);
				unsigned char k;
				//wxLogMessage(wxString::Format(_T("n: %u"),n));
				//wxLogMessage(wxString::Format(_T("r: %f x: %f, z: %f"),r,x,z));
				for(k = 0; k < n; k++){
					float cc1 = cos(a1 + (a2 - a1) / (float) n * (float) k);
					float ss1 = -sin(a1 + (a2 - a1) / (float) n * (float) k);
					float cc2 = cos(a1 + (a2 - a1) / (float) n
							* (float) (k + 1));
					float ss2 = -sin(a1 + (a2 - a1) / (float) n * (float) (k
							+ 1));
					temp = new ToolContourElement(elements[j].cutting);
					temp->n1.x = cc1;
					temp->n1.z = ss1;
					temp->n2.x = cc2;
					temp->n2.z = ss2;
					temp->p1.x = cc1 * r + x2 + xPosition;
					temp->p1.z = ss1 * r + z2 + zPosition;
					temp->p2.x = cc2 * r + x2 + xPosition;
					temp->p2.z = ss2 * r + z2 + zPosition;
					contour.Add(temp);
				}
			}
		}

		zPosition += z;
		xPosition += x;
	}
}

float Tool::GetPositiveLength(void)
{
	float maxLength = 0.0;
	float zPosition = 0.0;
	unsigned int i;
	for(i = 0; i < elements.Count(); i++){
		zPosition += elements[i].h;
		//TODO: Extend this for round elements. Round elements can extend further downwards than the start and endpoint.
		if(zPosition > maxLength) maxLength = zPosition;
	}
	return maxLength;
}

float Tool::GetNegativeLength(void)
{
	return shaftLength;
}

float Tool::GetMaxDiameter(void)
{
	float maxD = shaftDiameter;
	unsigned int i;
	for(i = 0; i < elements.Count(); i++){
		if(elements[i].d > maxD) maxD = elements[i].d;
	}
	return maxD;
}

void Tool::Paint(void)
{
	unsigned int i, j;

	float ss[resolution + 1], cc[resolution + 1];
	for(i = 0; i <= resolution; i++){
		ss[i] = sin(2* M_PI / resolution * i);
		cc[i] = cos(2* M_PI / resolution * i);
	}

	for(i = 0; i < contour.Count(); i++){
		::glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= resolution; j++){
			::glNormal3f(cc[j] * contour[i].n1.x, ss[j] * contour[i].n1.x,
					contour[i].n1.z);
			::glVertex3f(cc[j] * contour[i].p1.x, ss[j] * contour[i].p1.x,
					contour[i].p1.z);
			::glNormal3f(cc[j] * contour[i].n2.x, ss[j] * contour[i].n2.x,
					contour[i].n2.z);
			::glVertex3f(cc[j] * contour[i].p2.x, ss[j] * contour[i].p2.x,
					contour[i].p2.z);
		}
		::glEnd();
	}
}
