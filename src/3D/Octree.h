///////////////////////////////////////////////////////////////////////////////
// Name               : Octree.h
// Purpose            : Contains an Octree and its support functions
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lgl
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

#include <stdint.h>

/*!\class OctreeCell
 * \brief Stores the data for a cell in the Octree.
 *
 * The subdivision (sdx, sdy, sdz) entries can later be used to improve
 * the surface on painting (-> Primal Contouring).
 */

class OctreeCell {
	friend class Octree;
	friend class OctreeGenerator;

	// Constructor / Destructor
public:
	OctreeCell(bool isSolid = false);
	virtual ~OctreeCell();

	// Member variables
public:

	float r; ///< Red - Color of this particular element. Also inherited upon splitting.
	float g; ///< Red - Color of this particular element. Also inherited upon splitting.
	float b; ///< Red - Color of this particular element. Also inherited upon splitting.

	uint8_t clip; ///< Intersection of one edge.
	uint8_t sign; ///< Sign of the clipping (1 = 1, 0 = -1).

protected:
	OctreeCell* sub[8]; ///< Pointers to the 8 possible subelements
	bool hasSubElements; ///< Flag to speed up element lookup
	bool isSolid; ///< Flag, if this Element is solid. On splitting the element, this is inherited to the 8 children.

	// Methods
public:
	void SetColor(float r = 1.0, float g = 1.0, float b = 1.0);
	void Split(void); ///< Splits an element into 8 subelements.
	void Paint(void); ///< Paints the element itself and its subelements (if any).

private:
//	void InsertTriangle(const Triangle tri, const BoundingBox bb);
//	void CheckTriangle(const Triangle tri, const Vector3 pos);
//	bool CheckIntersection(const Triangle tri, const Vector3 pos);
};

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
 *
 */

class Octree {
	friend class OctreeGenerator;
	// Constructor / Destructor
public:
	Octree();
	virtual ~Octree();

	// Member variables
public:
	OctreeCell* tree; ///< Pointer towards the topmost cell
	unsigned char depth;
	double cellSize; ///< Size (length, width, depth) of one cell at the lowest level. Resolution of the Octree.

private:
	unsigned int displayListIndex; ///< Variable pointing to the OpenGL display list.
	bool displayListGenerated; ///< Flag showing if an OpenGL display list has been created.
	bool refresh; ///< Flag to show, that the OpenGL display list has to be recreated.

	// Methods
public:
	void Paint(void); ///< Paints the octree and creates the OpenGL display list.

};

#endif /* OCTREE_H_ */
