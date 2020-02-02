///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLMaterial.cpp
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

#include "OpenGLMaterial.h"

#include "OpenGL.h"

OpenGLMaterial::OpenGLMaterial()
{
	ambient.Set(0.2, 0.2, 0.2);
	diffuse.Set(0.8, 0.8, 0.8);
	specular.Set(0.7, 0.7, 0.7);
	shininess = 32;
}

OpenGLMaterial::OpenGLMaterial(Material preset, float emit)
{
	Preset(preset);
	emission = diffuse * emit;
}

OpenGLMaterial::OpenGLMaterial(float r, float g, float b, float emit)
{
	SetSimpleColor(r, g, b, emit);
}

void OpenGLMaterial::Preset(Material preset)
{
	// Preset-materials from http://devernay.free.fr/cours/opengl/materials.html
	switch(preset){
	case emerald:
		ambient.Set(0.0215, 0.1745, 0.0215);
		diffuse.Set(0.07568, 0.61424, 0.07568);
		specular.Set(0.633, 0.727811, 0.633);
		shininess = 38.4;
		break;
	case jade:
		ambient.Set(0.135, 0.2225, 0.1575);
		diffuse.Set(0.54, 0.89, 0.63);
		specular.Set(0.316228, 0.316228, 0.316228);
		shininess = 6.4;
		break;
	case obsidian:
		ambient.Set(0.05375, 0.05, 0.06625);
		diffuse.Set(0.18275, 0.17, 0.22525);
		specular.Set(0.332741, 0.328634, 0.346435);
		shininess = 19.2;
		break;
	case pearl:
		ambient.Set(0.25, 0.20725, 0.20725);
		diffuse.Set(1, 0.829, 0.829);
		specular.Set(0.296648, 0.296648, 0.296648);
		shininess = 5.632;
		break;
	case ruby:
		ambient.Set(0.1745, 0.01175, 0.01175);
		diffuse.Set(0.61424, 0.04136, 0.04136);
		specular.Set(0.727811, 0.626959, 0.626959);
		shininess = 38.4;
		break;
	case turquoise:
		ambient.Set(0.1, 0.18725, 0.1745);
		diffuse.Set(0.396, 0.74151, 0.69102);
		specular.Set(0.297254, 0.30829, 0.306678);
		shininess = 6.4;
		break;
	case brass:
		ambient.Set(0.329412, 0.223529, 0.027451);
		diffuse.Set(0.780392, 0.568627, 0.113725);
		specular.Set(0.992157, 0.941176, 0.807843);
		shininess = 13.9487;
		break;
	case bronze:
		ambient.Set(0.2125, 0.1275, 0.054);
		diffuse.Set(0.714, 0.4284, 0.18144);
		specular.Set(0.393548, 0.271906, 0.166721);
		shininess = 12.8;
		break;
	case chrome:
		ambient.Set(0.25, 0.25, 0.25);
		diffuse.Set(0.4, 0.4, 0.4);
		specular.Set(0.774597, 0.774597, 0.774597);
		shininess = 38.4;
		break;
	case copper:
		ambient.Set(0.19125, 0.0735, 0.0225);
		diffuse.Set(0.7038, 0.27048, 0.0828);
		specular.Set(0.256777, 0.137622, 0.086014);
		shininess = 6.4;
		break;
	case gold:
		ambient.Set(0.24725, 0.1995, 0.0745);
		diffuse.Set(0.75164, 0.60648, 0.22648);
		specular.Set(0.628281, 0.555802, 0.366065);
		shininess = 25.6;
		break;
	case silver:
		ambient.Set(0.19225, 0.19225, 0.19225);
		diffuse.Set(0.50754, 0.50754, 0.50754);
		specular.Set(0.508273, 0.508273, 0.508273);
		shininess = 25.6;
		break;
	case blackplastic:
		ambient.Set(0.0, 0.0, 0.0);
		diffuse.Set(0.01, 0.01, 0.01);
		specular.Set(0.50, 0.50, 0.50);
		shininess = 16;
		break;
	case cyanplastic:
		ambient.Set(0.0, 0.1, 0.06);
		diffuse.Set(0.0, 0.50980392, 0.50980392);
		specular.Set(0.50196078, 0.50196078, 0.50196078);
		shininess = 16;
		break;
	case greenplastic:
		ambient.Set(0.0, 0.0, 0.0);
		diffuse.Set(0.1, 0.35, 0.1);
		specular.Set(0.45, 0.55, 0.45);
		shininess = 16;
		break;
	case redplastic:
		ambient.Set(0.0, 0.0, 0.0);
		diffuse.Set(0.5, 0.0, 0.0);
		specular.Set(0.7, 0.6, 0.6);
		shininess = 16;
		break;
	case whiteplastic:
		ambient.Set(0.0, 0.0, 0.0);
		diffuse.Set(0.55, 0.55, 0.55);
		specular.Set(0.70, 0.70, 0.70);
		shininess = 16;
		break;
	case yellowplastic:
		ambient.Set(0.0, 0.0, 0.0);
		diffuse.Set(0.5, 0.5, 0.0);
		specular.Set(0.60, 0.60, 0.50);
		shininess = 16;
		break;
	case blackrubber:
		ambient.Set(0.02, 0.02, 0.02);
		diffuse.Set(0.01, 0.01, 0.01);
		specular.Set(0.4, 0.4, 0.4);
		shininess = 5;
		break;
	case cyanrubber:
		ambient.Set(0.0, 0.05, 0.05);
		diffuse.Set(0.4, 0.5, 0.5);
		specular.Set(0.04, 0.7, 0.7);
		shininess = 5;
		break;
	case greenrubber:
		ambient.Set(0.0, 0.05, 0.0);
		diffuse.Set(0.4, 0.5, 0.4);
		specular.Set(0.04, 0.7, 0.04);
		shininess = 5;
		break;
	case redrubber:
		ambient.Set(0.05, 0.0, 0.0);
		diffuse.Set(0.5, 0.4, 0.4);
		specular.Set(0.7, 0.04, 0.04);
		shininess = 5;
		break;
	case whiterubber:
		ambient.Set(0.05, 0.05, 0.05);
		diffuse.Set(0.5, 0.5, 0.5);
		specular.Set(0.7, 0.7, 0.7);
		shininess = 5;
		break;
	case yellowrubber:
		ambient.Set(0.05, 0.05, 0.0);
		diffuse.Set(0.5, 0.5, 0.4);
		specular.Set(0.7, 0.7, 0.04);
		shininess = 5;
		break;
	case cRed: //Color Red
		ambient.Set(1.0, 0.0, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;

	case cYellow: //Color Yellow
		ambient.Set(1.0, 1.0, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cGreen: //Color Green
		ambient.Set(0.0, 0.5, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cLime: //Color Lime
		ambient.Set(0.0, 1.0, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cTeal: //Color Teal
		ambient.Set(0.0, 0.5, 0.5);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cOlive: //Color Olive
		ambient.Set(0.5, 0.5, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cBlue: //Color Blue
		ambient.Set(0.0, 0.0, 1.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cAqua: //Color Aqua
		ambient.Set(0.0, 1.0, 1.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cNavy: //Color Navy
		ambient.Set(0.0, 0.0, 0.5);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cPurple: //Color Purple
		ambient.Set(0.5, 0.0, 0.5);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cFuchsia: //Color Fuchsia
		ambient.Set(1.0, 0.0, 1.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cMaroon: //Color Maroon
		ambient.Set(0.5, 0.0, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cGray: //Color Gray
		ambient.Set(0.75, 0.75, 0.75);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cSilver: //Color Silver
		ambient.Set(0.5, 0.5, 0.5);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cBlack: //Color Black
		ambient.Set(0.0, 0.0, 0.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;
	case cWhite: //Color White
		ambient.Set(1.0, 1.0, 1.0);
		diffuse = ambient;
		specular.Zero();
		shininess = 0;
		break;

	}
	emission.Zero();
}

std::string OpenGLMaterial::GetPresetName(Material preset)
{
	switch(preset){
	case emerald:
		return ("Emerald");
	case jade:
		return ("Jade");
	case obsidian:
		return ("Obsidian");
	case pearl:
		return ("Pearl");
	case ruby:
		return ("Ruby");
	case turquoise:
		return ("Turquoise");
	case brass:
		return ("Brass");
	case bronze:
		return ("Bronze");
	case chrome:
		return ("Chrome");
	case copper:
		return ("Copper");
	case gold:
		return ("Gold");
	case silver:
		return ("Silver");
	case blackplastic:
		return ("Black plastic");
	case cyanplastic:
		return ("Cyan plastic");
	case greenplastic:
		return ("Green plastic");
	case redplastic:
		return ("Red plastic");
	case whiteplastic:
		return ("White plastic");
	case yellowplastic:
		return ("Yellow plastic");
	case blackrubber:
		return ("Black rubber");
	case cyanrubber:
		return ("Cyan rubber");
	case greenrubber:
		return ("Green rubber");
	case redrubber:
		return ("Red rubber");
	case whiterubber:
		return ("White rubber");
	case yellowrubber:
		return ("Yellow rubber");
	case cRed:
		return ("Red");
	case cYellow:
		return ("Yellow");
	case cGreen:
		return ("Green");
	case cLime:
		return ("Lime");
	case cTeal:
		return ("Teal");
	case cOlive:
		return ("Olive");
	case cBlue:
		return ("Blue");
	case cAqua:
		return ("Aqua");
	case cNavy:
		return ("Navy");
	case cPurple:
		return ("Purple");
	case cFuchsia:
		return ("Fuchsia");
	case cMaroon:
		return ("Maroon");
	case cGray:
		return ("Gray");
	case cSilver:
		return ("Silver");
	case cBlack:
		return ("Black");
	case cWhite:
		return ("White");
	}
	return ("");
}

void OpenGLMaterial::SetSimpleColor(float r, float g, float b, float emit)
{
	ambient.Set(r, g, b);
	diffuse.Set(r, g, b);
	specular.Zero();
	emission = diffuse * emit;
	shininess = 0;
}

void OpenGLMaterial::SetSimpleColor(Vector3 c, float emit)
{
	SetSimpleColor(c.x, c.y, c.z, emit);
}

bool OpenGLMaterial::ColorsAllowed(void)
{
	GLboolean colormask[4];
	glGetBooleanv(GL_COLOR_WRITEMASK, colormask);
	return (colormask[0] && colormask[1] && colormask[2] && colormask[3]);
}

void OpenGLMaterial::UseMaterial(void) const
{
	if(!ColorsAllowed()) return;
	glDisable(GL_COLOR_MATERIAL);
	GLfloat buffer[4];
	buffer[0] = ambient.x;
	buffer[1] = ambient.y;
	buffer[2] = ambient.z;
	buffer[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, buffer);
	buffer[0] = diffuse.x;
	buffer[1] = diffuse.y;
	buffer[2] = diffuse.z;
	buffer[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, buffer);
	buffer[0] = specular.x;
	buffer[1] = specular.y;
	buffer[2] = specular.z;
	buffer[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, buffer);
	buffer[0] = emission.x;
	buffer[1] = emission.y;
	buffer[2] = emission.z;
	buffer[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, buffer);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void OpenGLMaterial::UseColor(float emit) const
{
	if(!ColorsAllowed()) return;
	glEnable(GL_COLOR_MATERIAL);
	GLfloat buffer[] =
		{0, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, buffer);
	buffer[0] = diffuse.x * emit;
	buffer[1] = diffuse.y * emit;
	buffer[2] = diffuse.z * emit;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, buffer);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glColor3f(diffuse.x, diffuse.y, diffuse.z);
}

void OpenGLMaterial::UseColor(void) const
{
	if(!ColorsAllowed()) return;
	glEnable(GL_COLOR_MATERIAL);
	GLfloat buffer[] =
		{0, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, buffer);
	buffer[0] = emission.x;
	buffer[1] = emission.y;
	buffer[2] = emission.z;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, buffer);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glColor3f(diffuse.x, diffuse.y, diffuse.z);
}

void OpenGLMaterial::EnableColors(void)
{
	if(!ColorsAllowed()) return;
	glEnable(GL_COLOR_MATERIAL);
	GLfloat buffer[] =
		{0, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, buffer);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, buffer);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}

