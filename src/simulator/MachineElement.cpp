//============================================================================
// Name        : MachineElement.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 27.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "MachineElement.h"
#include <GL/gl.h>
#include <wx/log.h>
MachineElement::MachineElement(unsigned char typeOfElement)
{
	this->typeOfElement = typeOfElement;
	x = y = z = 1.0;
	r1 = r2 = h = 1.0;
}

MachineElement::~MachineElement()
{
	// TODO Auto-generated destructor stub
}

void MachineElement::Paint(void)
{
	unsigned int i;
	const unsigned int N = 32;

	float ss[N + 1], cc[N + 1];

	float x2, y2, z2;
	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	switch(typeOfElement){
	case MACHINEELEMENT_BOX:

		x2 = x / 2;
		y2 = y / 2;
		z2 = z / 2;

		::glBegin(GL_QUADS);

		::glNormal3f(1, 0, 0);
		::glVertex3f(x2, y2, z2);
		::glVertex3f(x2, -y2, z2);
		::glVertex3f(x2, -y2, -z2);
		::glVertex3f(x2, y2, -z2);

		::glNormal3f(-1, 0, 0);
		::glVertex3f(-x2, y2, z2);
		::glVertex3f(-x2, -y2, z2);
		::glVertex3f(-x2, -y2, -z2);
		::glVertex3f(-x2, y2, -z2);

		::glNormal3f(0, 1, 0);
		::glVertex3f(x2, y2, z2);
		::glVertex3f(-x2, y2, z2);
		::glVertex3f(-x2, y2, -z2);
		::glVertex3f(x2, y2, -z2);

		::glNormal3f(0, -1, 0);
		::glVertex3f(x2, -y2, z2);
		::glVertex3f(-x2, -y2, z2);
		::glVertex3f(-x2, -y2, -z2);
		::glVertex3f(x2, -y2, -z2);

		::glNormal3f(0, 0, 1);
		::glVertex3f(x2, y2, z2);
		::glVertex3f(-x2, y2, z2);
		::glVertex3f(-x2, -y2, z2);
		::glVertex3f(x2, -y2, z2);

		::glNormal3f(0, 0, -1);
		::glVertex3f(x2, y2, -z2);
		::glVertex3f(-x2, y2, -z2);
		::glVertex3f(-x2, -y2, -z2);
		::glVertex3f(x2, -y2, -z2);

		::glEnd();

		break;
	case MACHINEELEMENT_CYLINDER:

		for(i = 0; i <= N; i++){
			ss[i] = sin(2*M_PI / N * i);
			cc[i] = cos(2*M_PI / N * i);
		}

		::glBegin(GL_TRIANGLE_FAN);
		::glNormal3f(0, 0, 1);
		::glVertex3f(0, 0, h / 2);
		for(i = 0; i <= N; i++){
			glVertex3f(r1 * cc[i], r1 * ss[i], h / 2);
		}
		::glEnd();
		::glBegin(GL_TRIANGLE_FAN);
		::glNormal3f(0, 0, -1);
		::glVertex3f(0, 0, -h / 2);
		for(i = 0; i <= N; i++){
			glVertex3f(r2 * cc[i], r2 * ss[i], -h / 2);
		}
		::glEnd();
		::glBegin(GL_QUAD_STRIP);
		for(i = 0; i <= N; i++){
			::glNormal3f(cc[i], ss[i], 0);
			::glVertex3f(r1 * cc[i], r1 * ss[i], h / 2);
			::glVertex3f(r2 * cc[i], r2 * ss[i], -h / 2);
		}
		::glEnd();

		break;
	}
	::glPopMatrix();
}
