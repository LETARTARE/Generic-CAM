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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#ifndef OCTREE_H_
#define OCTREE_H_

#include "../3D/Triangle.h"
#include "../3D/Vector3.h"

#include <GL/gl.h>

#include <stdint.h>

#include <wx/dynarray.h>

/*!\class OctreeElement
 * \brief Stores the data for an element.
 *
 * The subdivision (sdx, sdy, sdz)entries can later be used to improve
 * the surface on painting (-> Primal Contouring).
 */

class OctreeElement {
	// Constructor / Destructor
public:
	OctreeElement(bool isSolid = false);
	virtual ~OctreeElement();
	// Member variables
public:

	OctreeElement* sub[8]; ///< Pointer to the 8 possible subelements.
	bool hasSubElements; ///< Flag to speed up element lookup.

	bool isSolid; ///< Flag, if this Element is solid. On splitting the element, this is inherited to the 8 children.
	Vector3 color; ///< Color of this particular element. Also inherited upon splitting.

	float sdx; ///< Subdivision on the x axis (0...1)
	float sdy; ///< Subdivision on the y axis (0...1)
	float sdz; ///< Subdivision on the z axis (0...1)

	// Methods
public:
	void Split(void); ///< Splits an element into 8 subelements.
	void Paint(void); ///< Paints the element itself and its subelements (if any).
	bool CheckIntersection(Triangle *tri, Vector3 pos, float scale);
	void CheckTriangle(Triangle *tri, Vector3 pos, uint32_t scale);
};

/*!\class Octree
 * \brief Holds, operates on and displays volumentric data.
 *
 *  This class can store volumentric data. The data is stored in a structure
 *  known as octree. That is a tree where every node connects to up to 8 subnodes.
 *  The nodes are numbered, so that the first three bit of the index represent the
 *  coordinate from the origin. Bit 0 is x, bit 1 is y and bit 2 is the z direction.
 *
 *  The octree can be set up from triangle data according to the paper
 *
 *  - Ju2004 - Robust Repair of Polygonal Models
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

	OctreeElement* root; ///< Pointer towards the root element.

	unsigned char maxDepth; ///< maximum splitting depth of the octree.

private:

	GLuint displayListIndex; ///< Variable pointing to the OpenGL display list.
	bool displayListGenerated; ///< Flag showing if an OpenGL display list has been created.
	bool refresh; ///< Flag to show, that the OpenGL display list has to be recreated.

	// Methods
public:
	void InsertTriangle(Triangle tri);///< Insert a new triangle into the octree.
	void Paint(void); ///< Paints the octree and creates the OpenGL display list.
};
WX_DECLARE_OBJARRAY(Octree, ArrayOfOctree)
;

#endif /* OCTREE_H_ */
