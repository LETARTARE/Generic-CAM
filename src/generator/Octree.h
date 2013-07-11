///////////////////////////////////////////////////////////////////////////////
// Name               : Octree.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.08.2011
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

#ifndef OCTREE_H_
#define OCTREE_H_

#include "../3D/Triangle.h"
#include "../3D/Vector3.h"

#include "OctreeInt64.h"

#include <GL/gl.h>

#include <stdint.h>

#include <wx/dynarray.h>

/*!\class Octree
 * \brief Holds, operates on and displays volumentric data.
 *
 *  This class can store volumentric data. The data is stored in a structure
 *  known as octree. That is a tree where every node connects to up to 8 subnodes.
 *  The nodes are numbered, so that the first three bit of the index represent the
 *  coordinate from the origin. Bit 0 is x, bit 1 is y and bit 2 is the z direction.
 *
 *  The triangle data need not be a two-manifold. It can even have gaps and holes.
 *  It should only be designed as a thick-walled object. In case of a shell object the inside
 *  is made solid. If the hole are too big, it is not predictable, what the reconstruction
 *  algorithm will turn up with.
 */

class Octree {
	// Constructor / Destructor
public:
	Octree();
	virtual ~Octree();

	// Member variables
public:

	OctreeInt64* tree; ///< Pointer towards the discrete octree.

	double scale; ///< scaling of the Octree.

	// Methods
public:
	void InsertTriangle(Triangle tri); ///< Insert a new triangle into the octree.
	void Paint(void); ///< Paints the octree and creates the OpenGL display list.
};
WX_DECLARE_OBJARRAY(Octree, ArrayOfOctree)
;

#endif /* OCTREE_H_ */
