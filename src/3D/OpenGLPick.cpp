///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLPick.cpp
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

#include "OpenGLPick.h"

#include <stdlib.h>

OpenGLPick::OpenGLPick(GLsizei bufferSize)
{
	this->bufferSize = bufferSize;
	this->buffer = new GLuint[this->bufferSize];
	this->sort = new GLuint[this->bufferSize];
	this->bufferAssigned = false;
	this->results = 0;
	this->pos = 0;
	this->hitpos = 0;
}

OpenGLPick::OpenGLPick(const OpenGLPick& other)
{
	throw("'OpenGLPick::Copy constructor' is unimplemented!");
}

OpenGLPick& OpenGLPick::operator=(const OpenGLPick& other)
{
	if(&other == this) return *this;

	throw("'OpenGLPick::operator=' is unimplemented!");

	return *this;
}

OpenGLPick::~OpenGLPick()
{
	if(buffer != NULL) delete[] buffer;
	if(sort != NULL) delete[] sort;
}

bool OpenGLPick::SetBufferSize(GLsizei newSize)
{
	// Do not change or deallocate the buffer, while it is assigned to
	// an OpenGL context.
	// Probably this problem will never arise. But if it happens, it would
	// be a major headache to debug.
	// (buffer assigned to OGL -> buffer delete[] -> OGL tries to write -> SEG_FAULT)
	// The bufferAssigned flag is used to mitigate the problem.
	if(bufferAssigned) return false;

	// Create new buffer and copy the old content.
	GLuint * temp = new GLuint[newSize];

	GLsizei m = bufferSize;
	if(newSize < m) m = newSize;
	for(GLsizei n = 0; n < m; n++)
		temp[n] = buffer[n];
	if(buffer != NULL) delete[] buffer;
	buffer = temp;

	if(sort != NULL) delete[] sort;
	sort = new GLuint[newSize];

	bufferSize = newSize;
	pos = 0;
	hitpos = 0;
	return true;
}

GLsizei OpenGLPick::GetBufferSize()
{
	return bufferSize;
}
GLuint* OpenGLPick::GetBuffer()
{
	// If the pointer to the buffer is requested, it is most likely, that
	// the buffer is about to be assigned to an OpenGL context.
	bufferAssigned = true;
	return buffer;
}
void OpenGLPick::SetHits(GLuint hits)
{
	// If the hits have been requested from the OpenGL context and entered into
	// this function, the buffer is most likely not assigned to the OpenGL context
	// anymore.
	bufferAssigned = false;
	this->results = hits;
	pos = 0;
	hitpos = 0;
}

bool OpenGLPick::HasHits(void)
{
	return results > 0;
}

unsigned int OpenGLPick::GetCount(void)
{
	return results;
}

int OpenGLPick::Get(unsigned int hit, unsigned int level)
{
	if(hit >= results) return -1;
	MoveBufferPos(hit);
	GLuint N = buffer[pos];
	if(level >= N) return -1;
	return buffer[pos + 3 + level];
}

int OpenGLPick::NearestWithLevel0(unsigned int L0)
{
	int temp = -1;
	for(unsigned int n = 0; n < results; n++){
		MoveBufferPos(n);
		GLuint N = buffer[pos];
		if(N < 1) continue;
		if(buffer[pos + 3] != L0) continue;
		temp = n;
		break;
	}
	return temp;
}

int OpenGLPick::NearestWithLevel01(unsigned int L0, unsigned int L1)
{
	int temp = -1;
	for(unsigned int n = 0; n < results; n++){
		MoveBufferPos(n);
		GLuint N = buffer[pos];
		if(N < 2) continue;
		if(buffer[pos + 3] != L0 || buffer[pos + 4] != L1) continue;
		temp = n;
		break;
	}
	return temp;
}

unsigned int OpenGLPick::Near(unsigned int hit)
{
	if(hit >= results) return 0;
	MoveBufferPos(hit);
	return buffer[pos + 1];
}

unsigned int OpenGLPick::Far(unsigned int hit)
{
	if(hit >= results) return 0;
	MoveBufferPos(hit);
	return buffer[pos + 2];
}

void OpenGLPick::SortByNear(void)
{
	if(results < 2) return;
	bool sorted = false;

	GLuint p1, p2, p; // Positions of the results
	GLuint near1, near2; // Near values
	GLuint N1, N2; // Number of uints for each result
	GLuint r, n; // Counter

	// Bubble sort
	while(!sorted){
		sorted = true;
		p1 = 0;
		for(r = 0; r < results - 1; r++){
			// p1 = p2 would not work, because the sizes of a result may have changed.
			if(r == 0){
				p1 = 0;
			}else{
				p1 = p1 + buffer[p1] + 3;
			}
			p2 = p1 + buffer[p1] + 3;
			near1 = buffer[p1 + 1];
			near2 = buffer[p2 + 1];
			if(near1 > near2){
				// Swapping the results
				N1 = buffer[p1] + 3; // Number of uints in result m
				N2 = buffer[p2] + 3; // Number of uints in result m+1
				// Copy everything to the sort buffer
				for(n = 0; n < (N1 + N2); n++)
					sort[n] = buffer[p1 + n];
				// Pointer to keep track of position
				p = p1;
				// Copy back result m+1
				for(n = 0; n < N2; n++)
					buffer[p++] = sort[N1 + n];
				// Copy back result m
				for(n = 0; n < N1; n++)
					buffer[p++] = sort[n];
				sorted = false;
			}
		}
		// Here a backwards pass could be written, but the results have varying
		// sizes, so is would result in a very complicated iteration scheme.
	}
	pos = 0;
	hitpos = 0;
}

void OpenGLPick::MoveBufferPos(GLuint hit)
{
	if(hit >= results) return;
	if(hit < hitpos){
		hitpos = 0;
		pos = 0;
	}
	while(hitpos != hit && pos < bufferSize){
		pos += buffer[pos] + 3;
		hitpos++;
	}
	if(pos >= bufferSize){
		throw("OpenGLPick::MoveBufferPos - Inconsistent buffer returned from OpenGL.");
	}
}
