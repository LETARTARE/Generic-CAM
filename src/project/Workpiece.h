///////////////////////////////////////////////////////////////////////////////
// Name               : Workpiece.h
// Purpose            : The workpiece
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.03.2010
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

#ifndef WORKPIECE_H_
#define WORKPIECE_H_

#include <wx/dynarray.h>

#include "../3D/BooleanBox.h"
#include "../3D/Vector3.h"
#include "Object.h"
#include "ObjectPlacement.h"
#include "StockMaterial.h"

class Workpiece:public StockMaterial {
	// Constructor / Destructor
public:
	Workpiece();
	Workpiece(const StockMaterial &material);
	virtual ~Workpiece();

	// Member variables
public:
	bool selected;

	ArrayOfObjectPlacement placements;

	BooleanBox box;
protected:

	// Methods
public:
	void Paint(const ArrayOfObject& objects) const;
	void Update(ArrayOfObject& objects);
};

WX_DECLARE_OBJARRAY(Workpiece, ArrayOfWorkpiece);

#endif /* WORKPIECE_H_ */
