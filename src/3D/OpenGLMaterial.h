///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLMaterial.h
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

#ifndef SRC_3D_OPENGLMATERIAL_H_
#define SRC_3D_OPENGLMATERIAL_H_

/*!\class OpenGLMaterial
 * \brief Simple Material definition for OpenGL
 * \ingroup View3D
 *
 * This class contains the ambient, diffuse and specular values for classic
 * material in OpenGL. The Function UseMaterial activates the material in
 * the OpenGL context. The static Function UseColor switches back to a glColor
 * based setting of colors / materials.
 *
 * The functions only change the material definition, if GL_COLOR_WRITEMASK is
 * all enabled. If not all channels (red, green blue, alpha) are activated in
 * the mask this hints that the 3D stereo display is calculated and everythig
 * is rendered in a single color.
 */

#include "Vector3.h"
#include <GL/gl.h>
#include <string.h>

class OpenGLMaterial {
public:
	enum Material {
		emerald,
		jade,
		obsidian,
		pearl,
		ruby,
		turquoise,
		brass,
		bronze,
		chrome,
		copper,
		gold,
		silver,
		blackplastic,
		cyanplastic,
		greenplastic,
		redplastic,
		whiteplastic,
		yellowplastic,
		blackrubber,
		cyanrubber,
		greenrubber,
		redrubber,
		whiterubber,
		yellowrubber
	}; //<! Preset materials

	OpenGLMaterial();
	OpenGLMaterial(Material preset, float emit = 0.0);
	OpenGLMaterial(float r, float g, float b, float emit = 0.0);

	void Preset(Material preset); ///< Set the material to a preset.
	static std::string GetPresetName(Material preset); ///< Return the name of a preset.

	void SetSimpleColor(float r, float g, float b, float emit = 0.0); ///< Equivalent to using the glColor command.
	void SetSimpleColor(Vector3 c, float emit = 0.0); ///< Uses x,y,z of a vector as the color components.

	void UseMaterial(void); ///< Start using this material. Turns off glColor command.
	void UseColor(float emit = 0.0); ///< Activates glColor and sets the diffuse color of this material.
	static void EnableColors(void); ///< Switch back to using glColor.

	static bool ColorsAllowed(void); ///< Test, if colores are allowed to use.

	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 emission;
	GLfloat shininess;

private:
	GLfloat buffer[4]; // Buffer for passing values to OpenGL.
};

#endif /* SRC_3D_OPENGLMATERIAL_H_ */
