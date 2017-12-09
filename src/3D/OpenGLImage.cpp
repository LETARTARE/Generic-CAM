///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLImage.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.01.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "OpenGLImage.h"

OpenGLImage::OpenGLImage()
{
	refresh = true;
	textureID = 0;
	isOGLInit = false;
	w = 0;
	h = 0;
	tex_w = 0;
	tex_h = 0;
}

OpenGLImage::OpenGLImage(const OpenGLImage& other) :
		wxImage(other)
{
	refresh = true;
	textureID = 0;
	isOGLInit = false;
	w = 0;
	h = 0;
	tex_w = 0;
	tex_h = 0;
}

OpenGLImage::OpenGLImage(const wxImage& other) :
		wxImage(other)
{
	refresh = true;
	textureID = 0;
	isOGLInit = false;
	w = 0;
	h = 0;
	tex_w = 0;
	tex_h = 0;
}

OpenGLImage::~OpenGLImage()
{
	if(isOGLInit) glDeleteTextures(1, &textureID);
}

OpenGLImage& OpenGLImage::operator=(const OpenGLImage& other)
{
	if(&other == this) return *this;
	wxImage::operator=(other);
	refresh = true;
	w = 0;
	h = 0;
	tex_w = 0;
	tex_h = 0;
	return *this;
}

OpenGLImage& OpenGLImage::operator=(const wxImage& other)
{
	wxImage::operator=(other);
	if(&other == this) return *this;
	refresh = true;
	w = 0;
	h = 0;
	tex_w = 0;
	tex_h = 0;
	return *this;
}

bool OpenGLImage::LoadFile(const wxString& name, long type, int index)
{
	bool temp = wxImage::LoadFile(name, type, index);
	refresh = true;
	return temp;
}

bool OpenGLImage::LoadFile(const wxString& name, const wxString& mimetype,
		int index)
{
	bool temp = wxImage::LoadFile(name, mimetype, index);
	refresh = true;
	return temp;
}

bool OpenGLImage::LoadFile(wxInputStream& stream, long type, int index)
{
	bool temp = wxImage::LoadFile(stream, type, index);
	refresh = true;
	return temp;
}

bool OpenGLImage::LoadFile(wxInputStream& stream, const wxString& mimetype,
		int index)
{
	bool temp = wxImage::LoadFile(stream, mimetype, index);
	refresh = true;
	return temp;
}

void OpenGLImage::Update(void) const
{
	if(!isOGLInit){
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &textureID);
		glDisable(GL_TEXTURE_2D);
		isOGLInit = true;
		refresh = true;
	}
	if(refresh){
		GLint maxTexture;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexture);
		maxTexture >>= 1;

		uint32_t w = GetWidth();
		uint32_t h = GetHeight();

		uint32_t tex_w = NextPowerOfTwo(w);
		uint32_t tex_h = NextPowerOfTwo(h);
		while(tex_w > maxTexture || tex_h > maxTexture){
			tex_w >>= 1;
			tex_h >>= 1;
			w >>= 1;
			h >>= 1;
		}

		this->tex_w = (GLfloat) w / (GLfloat) tex_w;
		this->tex_h = (GLfloat) h / (GLfloat) tex_h;
		if(w > h){
			this->w = 1.0;
			this->h = (GLfloat) h / (GLfloat) w;
		}else{
			this->w = (GLfloat) w / (GLfloat) h;
			this->h = 1.0;
		}

		wxImage temp(*this);
		temp.Rescale(w, h);
		temp.Resize(wxSize(tex_w, tex_h), wxPoint(0, 0), 255, 255, 100);

		if(HasAlpha()){

			unsigned char * rgba = new unsigned char[tex_w * tex_h * 4];
			size_t i = 0;
			for(size_t y = 0; y < tex_h; y++){
				for(size_t x = 0; x < tex_w; x++){
					rgba[i++] = GetRed(x, y);
					rgba[i++] = GetGreen(x, y);
					rgba[i++] = GetBlue(x, y);
					rgba[i++] = GetAlpha(x, y);

				}
			}
			glEnable( GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, rgba);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glDisable( GL_TEXTURE_2D);
			delete[] rgba;

		}else{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_w, tex_h, 0, GL_RGB,
			GL_UNSIGNED_BYTE, temp.GetData());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glDisable(GL_TEXTURE_2D);
		}
		refresh = false;
	}
}

void OpenGLImage::SetAlphaColor(unsigned char red, unsigned char green,
		unsigned char blue)
{
	if(~HasAlpha()) InitAlpha();
	for(size_t i = 0; i < GetWidth(); i++){
		for(size_t j = 0; j < GetHeight(); j++){
			if(GetRed(i, j) == red && GetGreen(i, j) == green
					&& GetBlue(i, j) == blue){
				SetAlpha(i, j, 0);
			}else{
				SetAlpha(i, j, 255);
			}
		}
	}
}

uint32_t OpenGLImage::NextPowerOfTwo(uint32_t v)
{
	// Algorithm by Sean Anderson (September 2001) and William Lewis (February 1997).
	// From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

void OpenGLImage::Paint(void) const
{
	Update();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, this->tex_h);
	glVertex3f(0, 0, 0);
	glTexCoord2f(this->tex_w, this->tex_h);
	glVertex3f(this->w, 0, 0);
	glTexCoord2f(this->tex_w, 0);
	glVertex3f(this->w, this->h, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, this->h, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

