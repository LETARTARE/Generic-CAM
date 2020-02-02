///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLImage.h
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

#ifndef OPENGLIMAGE_H_
#define OPENGLIMAGE_H_

/*!\class OpenGLImage
 * \brief Displaying an image in 3D space.
 * \ingroup View3D
 *
 * This class is derived from wxImage. Upon loading an image it creates a glTexture to
 * display the image in 3D space.
 *
 * This class is intended to display a reference image in the background while modelling.
 *
 * It adds an extra layer to the LoadFile function to facilitate the conversion to glTextures.
 */

#include <wx/image.h>
#include <wx/string.h>
#include <stdint.h>

class OpenGLImage:public wxImage {
public:
	OpenGLImage();
	OpenGLImage(const OpenGLImage& other);
	OpenGLImage(const wxImage& other);
	virtual ~OpenGLImage();
	OpenGLImage& operator =(const OpenGLImage& other);
	OpenGLImage& operator =(const wxImage& other);

	bool LoadFile(const wxString& name, wxBitmapType type = wxBITMAP_TYPE_ANY,
			int index = -1);
	bool LoadFile(const wxString& name, const wxString& mimetype,
			int index = -1);
	bool LoadFile(wxInputStream& stream, wxBitmapType type, int index = -1);
	bool LoadFile(wxInputStream& stream, const wxString& mimetype, int index =
			-1);

	void SetAlphaColor(unsigned char red, unsigned char green,
			unsigned char blue);

	void Paint(void) const;
protected:
	void Update(void) const;
	mutable bool refresh;
	mutable float w;
	mutable float h;
	mutable float tex_w;
	mutable float tex_h;
	mutable unsigned int textureID;
	mutable bool isOGLInit;
private:
	static uint32_t NextPowerOfTwo(uint32_t v);
};

#endif /* OPENGLIMAGE_H_ */
