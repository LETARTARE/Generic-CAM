///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceObjectTransform.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 30.01.2015
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

#ifndef COMMANDWORKPIECEOBJECTTRANSFORM_H_
#define COMMANDWORKPIECEOBJECTTRANSFORM_H_

/*!\class CommandWorkpieceObjectTransform
 * \brief ...
 *
 * ...
 */

#include "../Project.h"
#include "../../3D/AffineTransformMatrix.h"

#include <wx/cmdproc.h>

class CommandWorkpieceObjectTransform:public wxCommand {
public:
	CommandWorkpieceObjectTransform(const wxString& name, Project * project,
			size_t workpieceNr, size_t placementNr,
			const AffineTransformMatrix& matrixNew, float x, float y,
			bool useContour, double slowWidth);
	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	size_t workpieceNr;
	size_t placementNr;
	AffineTransformMatrix matrixNew;
	AffineTransformMatrix matrixOld;
	float newX;
	float newY;
	bool newUseContour;
	double newSlotWidth;
	float oldX;
	float oldY;
	bool oldUseContour;
	double oldSlotWidth;

};

#endif /* COMMANDWORKPIECEOBJECTTRANSFORM_H_ */
