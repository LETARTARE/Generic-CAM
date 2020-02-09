///////////////////////////////////////////////////////////////////////////////
// Name               : SettingsStereo3D.cpp
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

#include "SettingsStereo3D.h"

#include "../3D/OpenGLCanvas.h"

SettingsStereo3D::SettingsStereo3D()
{
	eyeDistance = 0.1;
	focalDistance = 1.0;
	backgroundGrayLevel = 90;
	rightEyeR = 0;
	rightEyeG = 77;
	rightEyeB = 102;
	leftEyeR = 179;
	leftEyeG = 0;
	leftEyeB = 0;
}

SettingsStereo3D::~SettingsStereo3D()
{
}

bool SettingsStereo3D::Load(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	long lval;
	config->Read(_T("Stereo3DColorLeftEyeRed"), &lval, 140l);
	leftEyeR = lval;
	config->Read(_T("Stereo3DColorLeftEyeGreen"), &lval, 0l);
	leftEyeG = lval;
	config->Read(_T("Stereo3DColorLeftEyeBlue"), &lval, 0l);
	leftEyeB = lval;
	config->Read(_T("Stereo3DColorRightEyeRed"), &lval, 0l);
	rightEyeR = lval;
	config->Read(_T("Stereo3DColorRightEyeGreen"), &lval, 70l);
	rightEyeG = lval;
	config->Read(_T("Stereo3DColorRightEyeBlue"), &lval, 90l);
	rightEyeB = lval;

	double dval;
	config->Read(_T("Stereo3DEyeDistance"), &dval, 0.1);
	eyeDistance = dval;
	config->Read(_T("Stereo3DFocalDistance"), &dval, 1.0);
	focalDistance = dval;

	// Plausibility check
	eyeDistance = fmin(fmax(eyeDistance, 0.001), 1);
	focalDistance = fmin(fmax(focalDistance, 0.01), 10);
	return true;
}

bool SettingsStereo3D::Save(wxConfig* config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	config->Write(_T("Stereo3DColorLeftEyeRed"), (long) leftEyeR);
	config->Write(_T("Stereo3DColorLeftEyeGreen"), (long) leftEyeG);
	config->Write(_T("Stereo3DColorLeftEyeBlue"), (long) leftEyeB);
	config->Write(_T("Stereo3DColorRightEyeRed"), (long) rightEyeR);
	config->Write(_T("Stereo3DColorRightEyeGreen"), (long) rightEyeG);
	config->Write(_T("Stereo3DColorRightEyeBlue"), (long) rightEyeB);
	config->Write(_T("Stereo3DEyeDistance"), (double) eyeDistance);
	config->Write(_T("Stereo3DFocalDistance"), (double) focalDistance);

	return true;
}

void SettingsStereo3D::WriteToCanvas(OpenGLCanvas* canvas)
{
	canvas->leftEyeR = this->leftEyeR;
	canvas->leftEyeG = this->leftEyeG;
	canvas->leftEyeB = this->leftEyeB;
	canvas->rightEyeR = this->rightEyeR;
	canvas->rightEyeG = this->rightEyeG;
	canvas->rightEyeB = this->rightEyeB;
	canvas->focalDistance = this->focalDistance;
	canvas->eyeDistance = this->eyeDistance;
	canvas->backgroundGrayLevel = this->backgroundGrayLevel;
}
