///////////////////////////////////////////////////////////////////////////////
// Name               : StockMaterial.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef STOCKMATERIAL_H_
#define STOCKMATERIAL_H_

#include <wx/string.h>

#include <wx/dynarray.h>
#include "../3D/AffineTransformMatrix.h"
#include "../3D/Vector3.h"

/*!\class StockMaterial
 * \brief Definition of one piece of raw material.
 *
 * The material is defined as a Quadtree to speed up drawing.
 *
 */

class StockMaterial {
	// Constructor / Destructor
public:
	StockMaterial();
	virtual ~StockMaterial();

	// Member variables
public:

	AffineTransformMatrix matrix;
	Vector3 color;

	bool available; ///> Available in workshop
	wxString name;
	float sx, sy, sz;
	float maxToolSpeed;
	float maxFeedrate;
	float thermalConductivity;
	float ignitionTemperature;

	// Methods
public:
	void Paint(void);

};
WX_DECLARE_OBJARRAY(StockMaterial, ArrayOfStockMaterial)
;
#endif /* STOCKMATERIAL_H_ */
