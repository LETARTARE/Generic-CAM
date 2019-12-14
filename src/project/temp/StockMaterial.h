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

/*!\class StockMaterial
 * \ingroup document
 * \brief Definition of one piece of raw material.
 *
 * Stock material as it can be found in the workshop. It is assumed that it is box-like.
 *
 * The stock material contains technical data of the material as well.
 *
 * \section Thermal conductivities:
 *
 * in W/(K*m)
 *
 * - Wood - 0.04 .. 0.4
 * - Rubber - 0.15
 * - Polypropylene - 0.25
 * - Cement - 0.3
 * - Glass - 1.1
 * - Steel - 12 .. 45
 * - Aluminium - 240
 * - Gold - 310
 * - Copper - 400
 * - Silver - 430
 * - Graphene - 5000 .. 5500
 *
 */

#include "../3D/Vector3.h"

class StockMaterial {
	// Constructor / Destructor
public:
	StockMaterial();
	virtual ~StockMaterial();

	// Member variables
public:
	std::string name;
	float sx, sy, sz;

	bool available; ///< Available in workshop

	float maxToolSpeed; ///< Maximum rotational speed of the toolhead (1/s)
	float maxFeedrate; ///< Maximum feedrate (m/s)
	float thermalConductivity; ///< Thermal conductivity to calculate heat buildup in W/(K*m)
	float maxTemperature; ///< Temperature where bad things start to happen (wood burning, plastics melting, steel changing characteristics, ...) (K)

	Vector3 color; ///< Color of the material for rendering

	// Methods
public:
	void Paint(float alpha, bool flipNormals = false) const;
	void PaintWireBox(void) const;
//	void ToStream(wxTextOutputStream & stream);
//	bool FromStream(wxTextInputStream & stream);
};

#endif /* STOCKMATERIAL_H_ */
