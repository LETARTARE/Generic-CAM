///////////////////////////////////////////////////////////////////////////////
// Name               : SettingsStereo3D.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.02.2019
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

#ifndef _SETTINGSSTEREO3D_H_
#define _SETTINGSSTEREO3D_H_

/*!\class SettingsStereo3D
 * \brief ...
 *
 * ...
 */

#include <wx/config.h>

class OpenGLCanvas;

class SettingsStereo3D {
public:
	SettingsStereo3D();
	virtual ~SettingsStereo3D();

	float eyeDistance;
	float focalDistance;
	unsigned char backgroundGrayLevel;
	unsigned char rightEyeR;
	unsigned char rightEyeG;
	unsigned char rightEyeB;
	unsigned char leftEyeR;
	unsigned char leftEyeG;
	unsigned char leftEyeB;

	bool Load(wxConfig * config);
	bool Save(wxConfig * config);

	void WriteToCanvas(OpenGLCanvas * canvas);

};

#endif /* _SETTINGSSTEREO3D_H_ */
