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
 *
 * This class provides a buffer, that is filled by the OnPick function of the OpenGLCanvas.
 *
 * In the main code this is called by using the associated OpenGLCanvas and passing an object of this
 * class to the OnPick function.
 *
 * \code
 * void FrameMain::On3DSelect(wxMouseEvent& event)
 * {
 *   int x = event.GetX();
 *   int y = event.GetY();
 *   OpenGLPick result;
 *   m_canvas->OnPick(result, x, y);
 *   if(result.HasHits()){
 *     result.SortByNear();
 *     if(result.Get(0, 0) == 1){
 *       <...>
 *     }
 *   }
 * }
 * \endcode
 *
 * \note When extending this class:\n
 * The internal buffer is organized as a list of GLuint. Each record consists of\n
 *   [Number of levels N], [Near value], [Far value], [Name0], ..., [NameN]\n
 * Thus each record can have a different size.
 */

#include <GL/gl.h>

class OpenGLPick {
	friend class OpenGLCanvas;
public:
	OpenGLPick(GLsizei bufferSize = 512);
	OpenGLPick(const OpenGLPick& other); //!< Copy constructor
	OpenGLPick& operator=(const OpenGLPick& other); ///< Assignment operator
	virtual ~OpenGLPick();

	bool SetBufferSize(GLsizei newSize); //!< Initialize the pick buffer

	bool HasHits(void); //!< Are there any hits at this position at all
	unsigned int GetCount(void); //!< Number of hits recorded
	void SortByNear(void); //!< Sort the results by the Near value
	int NearestWithLevel0(unsigned int L0); //!< Find the nearest result with level0 == L0. Returns -1, if there is nothing found.
	int NearestWithLevel01(unsigned int L0, unsigned int L1); //!< Find the nearest result with Name0 == L0 and Name1 = L1. Returns -1, if there is nothing found.
	int Get(unsigned int hit, unsigned int level); //!< Return the levels of the namestack. Returns -1, if nothing is at this level.
	unsigned int Near(unsigned int hit); //!< Return the Near value of the hit
	unsigned int Far(unsigned int hit); //!< Return the Far value of the hit

protected:
	void SetHits(GLuint hits); //!< OpenGLCanvas tells this class the number of hits found
	GLuint * GetBuffer(); //!< OpenGLCanvas requests the pointer to the buffer
	GLsizei GetBufferSize(); //!< OpenGLCanvas requests the size of the buffer

private:
	void MoveBufferPos(GLuint hit); //!< Shift the pointer to the result buffer around.

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
