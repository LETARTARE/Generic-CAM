//============================================================================
// Name        : Tool.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "Tool.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfToolElement)

#include <GL/gl.h>
#include <math.h>
#include <wx/log.h>

Tool::Tool()
{
	// TODO Auto-generated constructor stub


}

Tool::~Tool()
{
	// TODO Auto-generated destructor stub
}

void Tool::Paint2D(void)
{
	unsigned int i;
	//	for(i = 0; i < elements.Count(); i++){
	//		elements[i].Paint();
	//	}
}

void Tool::Paint3D(void)
{
	unsigned int i;
	const unsigned int N = 32;

	float ss[N + 1], cc[N + 1];
	for(i = 0; i <= N; i++){
		ss[i] = sin(2* M_PI / N * i);
		cc[i] = cos(2* M_PI / N * i);
	}

	float xPosition = shaftDiameter / 2;
	float zPosition = 0.0;


	// Cap on top
	::glBegin(GL_TRIANGLE_FAN);
	::glNormal3f(0, 0, -1);
	::glVertex3f(0, 0, -shaftLength);
	for(i = 0; i <= N; i++){
		glVertex3f(xPosition * cc[i], xPosition * ss[i], -shaftLength);
	}
	::glEnd();


	// Top part of shaft
	::glBegin(GL_QUAD_STRIP);
	for(i = 0; i <= N; i++){
		::glNormal3f(cc[i], ss[i], 0);
		::glVertex3f(xPosition * cc[i], xPosition * ss[i], -shaftLength);
		::glVertex3f(xPosition * cc[i], xPosition * ss[i], 0);
	}
	::glEnd();

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
			::glBegin(GL_QUAD_STRIP);
			if(x > 0)
				::glNormal3f(0, 0, -1);
			else
				::glNormal3f(0, 0, 1);

			for(i = 0; i <= N; i++){
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition);
				::glVertex3f((xPosition + x) * cc[i], (xPosition + x) * ss[i],
						zPosition);
			}
			::glEnd();
			::glBegin(GL_QUAD_STRIP);
			for(i = 0; i <= N; i++){
				::glNormal3f(cc[i], ss[i], 0);
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition);
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition
						+ z);
			}
			::glEnd();

			break;

		case 2:
			::glBegin(GL_QUAD_STRIP);
			for(i = 0; i <= N; i++){
				::glNormal3f(cc[i], ss[i], 0);
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition);
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition
						+ z);
			}
			::glEnd();
			::glBegin(GL_QUAD_STRIP);

			if(x > 0)
				::glNormal3f(0, 0, -1);
			else
				::glNormal3f(0, 0, 1);

			for(i = 0; i <= N; i++){
				::glVertex3f(xPosition * cc[i], xPosition * ss[i], zPosition
						+ z);
				::glVertex3f((elements[j].d / 2) * cc[i], (elements[j].d / 2)
						* ss[i], zPosition + z);
			}
			::glEnd();
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
			break;
		}
		if(elements[j].t == 0 || elements[j].t == 3 || elements[j].t == 4){
			if(fabs(r) < 1e-6){

				::glBegin(GL_QUAD_STRIP);
				for(i = 0; i <= N; i++){
					::glNormal3f(cc[i] * z / d, ss[i] * z / d, -x / d);
					::glVertex3f(xPosition * cc[i], xPosition * ss[i],
							zPosition);
					::glVertex3f((elements[j].d / 2) * cc[i], (elements[j].d
							/ 2) * ss[i], zPosition + z);
				}
				::glEnd();

			}else{
				d = x * x + z * z;
				if(d > 0)
					d = sqrt(d);
				else
					d = 1.0;

				float x2 = x / 2 - z * sqrt(4 * r * r - x * x - z * z) / 2 / d;
				float z2 = z / 2 + x * sqrt(4 * r * r - x * x - z * z) / 2 / d;


				//wxLogMessage(wxString::Format(_T("sqrt(...): %f"),sqrt(4 * r * r - x * x - z * z)));


				//wxLogMessage(wxString::Format(_T("x2: %f z2: %f"),x2,z2));



				float a1 = atan2(zPosition - z2, xPosition - x2);
				float a2 = atan2(zPosition + z - z2, xPosition + x - x2);

				//wxLogMessage(wxString::Format(_T("a1: %f a2: %f"),a1/M_PI*180,a2/M_PI*180));

				unsigned char n = floor(fabs(a2 - a1) / M_PI * 180 / 1);
				unsigned char k;

				//wxLogMessage(wxString::Format(_T("n: %u"),n));


				//wxLogMessage(wxString::Format(_T("r: %f x: %f, z: %f"),r,x,z));

				for(k = 0; k < n; k++){
					float cc1 = cos(a1 + (a2 - a1) / (float)n * (float)k);
					float ss1 = sin(a1 + (a2 - a1) / (float)n * (float)k);
					float cc2 = cos(a1 + (a2 - a1) / (float)n * (float)(k + 1));
					float ss2 = sin(a1 + (a2 - a1) / (float)n * (float)(k + 1));

					::glBegin(GL_QUAD_STRIP);
					for(i = 0; i <= N; i++){
						::glNormal3f(cc[i] * cc1, ss[i] * cc1, ss1);
						::glVertex3f(cc[i] * (cc1 * r + x2), ss[i] * (cc1 * r
								+ x2), ss1 * r + z2);
						::glNormal3f(cc[i] * cc2, ss[i] * cc2, ss2);
						::glVertex3f(cc[i] * (cc2 * r + x2), ss[i] * (cc2 * r
								+ x2), ss2 * r + z2);
					}
					::glEnd();

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
		//TODO: Extend this for round elements. Round elements can extend further downwards than the start end endpoint.
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
