///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLLight.h
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

#ifndef SRC_3D_OPENGLLIGHT_H_
#define SRC_3D_OPENGLLIGHT_H_

/*!\class OpenGLLight
 * \brief ...
 * \ingroup View3D
 *
 * ...
 */

#include "Vector3.h"
#include "OpenGL.h"

class OpenGLLight {
public:
	OpenGLLight(GLenum lightsource);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetAmbient(Vector3 c);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(Vector3 c);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(Vector3 c);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetPosition(Vector3 p);
	void Enable(bool on = true);
	void Update(bool preRender = false);

	bool moveWithCamera;
private:
	GLenum lightsource;
	GLfloat buffer[4];
	Vector3 position;
};

#endif /* SRC_3D_OPENGLLIGHT_H_ */
