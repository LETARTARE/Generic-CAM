///////////////////////////////////////////////////////////////////////////////
// Name               : MachineComponent.h
// Purpose            : A component of the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MACHINECOMPONENT_H_
#define MACHINECOMPONENT_H_

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Geometry.h"

#include <wx/string.h>
#include <wx/filename.h>
#include <wx/dynarray.h>

class MachineComponent {
	// Constructor / Destructor
public:
	MachineComponent(wxString nameOfComponent = _T(""));
	virtual ~MachineComponent();

	// Member variables
public:

	wxString nameOfComponent;

	AffineTransformMatrix matrix;
private:
	Geometry geometry;

	// Methods
public:
	void Paint(void);
	void SetColor(float r, float g, float b);
	void InsertBox(AffineTransformMatrix matrix, float x, float y, float z);
	void InsertCylinder(AffineTransformMatrix matrix, float h, float r);
	void InsertCone(AffineTransformMatrix matrix, float h, float r1, float r2);
	bool InsertSTL(AffineTransformMatrix matrix, wxFileName file);
	bool InsertDXF(AffineTransformMatrix matrix, wxFileName file,
			wxString componentName);

private:
};
WX_DECLARE_OBJARRAY(MachineComponent, ArrayOfMachineComponent)
;

#endif /* MACHINECOMPONENT_H_ */
