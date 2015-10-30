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

#ifndef OCTREEGENERATOR_H_
#define OCTREEGENERATOR_H_

#include "Octree.h"
#include "Triangle.h"
#include "Vector3.h"
#include "BoundingBox.h"
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

/*! \class OctreeGenerator
 *   \brief Class with functions to generate an Octree from a collection of triangles.
 *
 * The octree is set up from triangle data according to the paper
 *
 *  - Ju2004 - Robust Repair of Polygonal Models
 *
 * The coordinate system is right handed with z pointing up.<BR>
 * (e.g. 	x towards the viewer,
 * 			y to the right and
 * 			z up.)
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

class OctreeGenerator {
	// Constructor / Destructor
public:
	OctreeGenerator();
	virtual ~OctreeGenerator();

	// Member variables
public:
	Octree* root; ///< Pointer towards the octree class.

private:

	// Methods
public:
	void InsertTriangle(Triangle tri); ///< Insert a new triangle into the octree
//	void InsertTriangle(TriangleInt64 &tri); ///< Insert a new triangle into the octree

	void Paint(void); ///< Paints the underlying octree};

private:
	void CheckTriangle(OctreeCell * base, const Triangle tri, const Vector3 pos,
			float scale, BoundingBox & bb, unsigned char depth);

	bool CheckIntersection(const Triangle tri, const Vector3 pos, float scale,
			BoundingBox & bb);

	bool IsAlign(float tempx, float tempy, float tempz, Vector3 *t0,
			Vector3 *t1, Vector3 *t2, float scale);

};

#endif /* OCTREEGENERATOR_H_ */
