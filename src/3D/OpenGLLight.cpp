///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLLight.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.03.2019
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

#include "OpenGLLight.h"

OpenGLLight::OpenGLLight(GLenum lightsource)
		: lightsource(lightsource)
{
	moveWithCamera = false;
}

void OpenGLLight::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	buffer[0] = r;
	buffer[1] = g;
	buffer[2] = b;
	buffer[3] = 1;
	glLightfv(lightsource, GL_AMBIENT, buffer);
}

void OpenGLLight::SetAmbient(Vector3 c)
{
	buffer[0] = c.x;
	buffer[1] = c.y;
	buffer[2] = c.z;
	buffer[3] = 1;
	glLightfv(lightsource, GL_AMBIENT, buffer);
}

void OpenGLLight::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	buffer[0] = r;
	buffer[1] = g;
	buffer[2] = b;
	buffer[3] = 1;
	glLightfv(lightsource, GL_DIFFUSE, buffer);
}

void OpenGLLight::SetDiffuse(Vector3 c)
{
	buffer[0] = c.x;
	buffer[1] = c.y;
	buffer[2] = c.z;
	buffer[3] = 1;
	glLightfv(lightsource, GL_DIFFUSE, buffer);
}

void OpenGLLight::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	buffer[0] = r;
	buffer[1] = g;
	buffer[2] = b;
	buffer[3] = 1;
	glLightfv(lightsource, GL_SPECULAR, buffer);
}

void OpenGLLight::SetSpecular(Vector3 c)
{
	buffer[0] = c.x;
	buffer[1] = c.y;
	buffer[2] = c.z;
	buffer[3] = 1;
	glLightfv(lightsource, GL_SPECULAR, buffer);
}

void OpenGLLight::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position.Set(x, y, z);
	Update();
}

void OpenGLLight::SetPosition(Vector3 p)
{
	position = p;
	Update();
}

void OpenGLLight::Enable(bool on)
{
	if(on)
		glEnable(lightsource);
	else
		glDisable(lightsource);
}

void OpenGLLight::Update(bool preRender)
{
	if(preRender && moveWithCamera) return;
	buffer[0] = position.x;
	buffer[1] = position.y;
	buffer[2] = position.z;
	buffer[3] = 0;
	glLightfv(lightsource, GL_POSITION, buffer);
}
