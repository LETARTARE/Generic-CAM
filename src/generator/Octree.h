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

#include "../3D/Vector3.h"

#include <GL/gl.h>

#include <wx/dynarray.h>

/*!\class Octree
 * \brief ...
 *
 * ...
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

	bool isSolid;
	Vector3 colorNormal;

	// Methods
public:
	void Split(void); ///< Splits an element into 8 subelements.
	void Paint(void); ///< Paints the element itself and its subelements (if any).
};
WX_DECLARE_OBJARRAY(OctreeElement, ArrayOfOctreeElement)
;

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
 * ...
 */

class Octree {
	// Constructor / Destructor
public:
	Octree();
	virtual ~Octree();

	// Member variables
public:

	OctreeElement* root; ///< Pointer towards the root element.


private:
	ArrayOfOctreeElement oe; ///< This thing can go... I'm using old school pointers.

	GLuint displayListIndex; ///< Variable pointing to the OpenGL display list.
	bool displayListGenerated; ///< Flag showing if an OpenGL display list has been created.
	bool refresh; ///< Flag to show, that the OpenGL display list has to be recreated.

	// Methods
public:

	void Paint(void); ///< Paints the octree and creates the OpenGL display list.
};

#endif /* OCTREE_H_ */
