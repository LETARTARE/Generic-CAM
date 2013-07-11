///////////////////////////////////////////////////////////////////////////////
// Name               : OctreeInt64.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 09.06.2013
// Copyright          : (C) 2013 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef OCTREEINT64_H_
#define OCTREEINT64_H_

#include <GL/gl.h>
#include <stdint.h>

/*!\class VectorInt64
 * \brief Stores an int64_t vector with 3 elements.
 */

class VectorInt64 {
public:
	int64_t x;
	int64_t y;
	int64_t z;
	VectorInt64();

	VectorInt64& operator=(const VectorInt64 &rhs);

};

/*!\class TriangleInt64
 * \brief Stores a discrete triangle.
 */

class TriangleInt64 {
public:
	VectorInt64 p[3];
	VectorInt64 bbmin;
	VectorInt64 bbmax;
	VectorInt64 normal;
	TriangleInt64();
};

/*!\class OctreeInt64Element
 * \brief Stores the data for an element.
 *
 * The subdivision (sdx, sdy, sdz) entries can later be used to improve
 * the surface on painting (-> Primal Contouring).
 *
 *  The octree is set up from triangle data according to the paper
 *
 *  - Ju2004 - Robust Repair of Polygonal Models
 *
 * The coordinate system is right handed with z pointing up.<BR>
 * (e.g. 	x towards the viewer,
 * 			y to the right and
 * 			z up.)
 *
 * The edges are numbered from 0 to 11 so that:
 *
 * uint8 -><BR>
 * 	0	= Starts at X:0 Y:0 Z:0 in X-direction<BR>
 * 	1	= Starts at X:0 Y:1 Z:0 in X-direction<BR>
 * 	2	= Starts at X:0 Y:0 Z:1 in X-direction<BR>
 * 	3	= Starts at X:0 Y:1 Z:1 in X-direction<BR>
 * 	4	= Starts at X:0 Y:0 Z:0 in Y-direction<BR>
 * 	5	= Starts at X:0 Y:0 Z:1 in Y-direction<BR>
 * 	6	= Starts at X:1 Y:0 Z:0 in Y-direction<BR>
 * 	7	= Starts at X:1 Y:0 Z:1 in Y-direction<BR>
 * 	8	= Starts at X:0 Y:0 Z:0 in Z-direction<BR>
 * 	9	= Starts at X:1 Y:0 Z:0 in Z-direction<BR>
 * 	10	= Starts at X:0 Y:1 Z:0 in Z-direction<BR>
 * 	11	= Starts at X:1 Y:1 Z:0 in Z-direction<BR>
 *
 */

class OctreeInt64Element {
	// Constructor / Destructor
public:
	OctreeInt64Element(bool isSolid = false);
	virtual ~OctreeInt64Element();
	// Member variables
public:
	OctreeInt64Element* sub[8]; ///< Pointer to the 8 possible subelements.
	bool hasSubElements; ///< Flag to speed up element lookup.

	bool isSolid; ///< Flag, if this Element is solid. On splitting the element, this is inherited to the 8 children.
	GLfloat r; ///< Red - Color of this particular element. Also inherited upon splitting.
	GLfloat g; ///< Red - Color of this particular element. Also inherited upon splitting.
	GLfloat b; ///< Red - Color of this particular element. Also inherited upon splitting.

	uint8_t clip; ///< Intersection of one edge.
	uint8_t sign; ///< Sign of the clipping (1 = 1, 0 = -1).

	// Methods
public:
	void SetColor(GLfloat r = 1.0, GLfloat g = 1.0, GLfloat b = 1.0);
	void Split(void); ///< Splits an element into 8 subelements.
	void Paint(void); ///< Paints the element itself and its subelements (if any).

	bool CheckIntersection(TriangleInt64 *tri, VectorInt64 pos);
	void CheckTriangle(TriangleInt64 *tri, VectorInt64 pos);
};

/*!\class OctreeInt64
 * \brief Octree based completely on integer calculation.
 *
 * Fast octree implementation with hole filling. The maximum number of cells
 * is 2^20 = 1048576 along one axis.
 *
 * The tree has always 20 levels. The resolution of the tree is done by scaling.
 * Level 0 is one unit long.
 * Level 1 = 0.5 units
 * Level 2 = 0.25 units
 * Level 3 = 0.125 units
 * ...
 * Level 19 = 1.9e-6 units
 * Level 20 = 9.5e-7 units
 *
 * The octree is split 20 times. For an volume of 1mx1mx1m the resolution is 0.95 micrometer.
 */

class OctreeInt64 {
	// Constructor / Destructor
public:
	OctreeInt64();
	virtual ~OctreeInt64();

	// Member variables
public:
	OctreeInt64Element* root; ///< Pointer towards the root element.

private:
	GLuint displayListIndex; ///< Variable pointing to the OpenGL display list.
	bool displayListGenerated; ///< Flag showing if an OpenGL display list has been created.
	bool refresh; ///< Flag to show, that the OpenGL display list has to be recreated.

	// Methods
public:
	void InsertTriangle(TriangleInt64 &tri); ///< Insert a new triangle into the octree.
	void Paint(void); ///< Paints the octree.
};

#endif /* OCTREEINT64_H_ */
