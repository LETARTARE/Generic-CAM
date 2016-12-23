///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLPick.h
// Purpose            : Storage and interpretaton for OpenGL picking results
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef OPENGLPICK_H_
#define OPENGLPICK_H_

/*!\class OpenGLPick
 * \ingroup View3D
 * \brief Storage for the result of an OpenGL picking operation
 *
 * The result is stored as it is delivered from the OpenGL call.
 * Functions are provided to interpret the results.
 */

#include <GL/gl.h>

class OpenGLPick {
	friend class OpenGLCanvas;
public:
	OpenGLPick(GLsizei bufferSize = 512);
	OpenGLPick(const OpenGLPick& other); //!< Copy constructor
	OpenGLPick& operator=(const OpenGLPick& other); ///< Assignment operator
	virtual ~OpenGLPick();

	bool SetBufferSize(GLsizei newSize);

	bool HasHits(void);
	unsigned int GetCount(void);
	void SortByNear(void);
	int Get(unsigned int hit, unsigned int level);
	unsigned int Near(unsigned int hit);
	unsigned int Far(unsigned int hit);

protected:
	void SetHits(GLuint hits);
	GLuint * GetBuffer();
	GLsizei GetBufferSize();
	void MoveBufferPos(GLuint hit);

private:
	GLsizei bufferSize;
	GLuint * buffer;
	GLuint * sort;
	bool bufferAssigned;
	GLuint results;
	GLuint pos;
	GLuint hitpos;
};

#endif /* OPENGLPICK_H_ */
