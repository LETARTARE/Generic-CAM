///////////////////////////////////////////////////////////////////////////////
// Name               : Quadtree.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.05.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef QUADTREE_H_
#define QUADTREE_H_

/*!\class Quadtree
 * \brief A Quadtree
 * Quadtrees are a 2.5D representation of objects.
 *
 */

#include "Vector3.h"
#include "Triangle.h"
#include "BoundingBox.h"
#include <GL/gl.h>

class BoundingBox;

class Quadtree {
public:
	Quadtree();
	virtual ~Quadtree();

//	enum direction {
//		FaceDown = 1,
//		FaceUp = -1,
//		Undefined = 0
//	};

// Sub classes
private:
	class QuadtreeCell {
	public:
		QuadtreeCell();
		~QuadtreeCell();

		float top;
		float bot;
		float minTop;
		float maxBot;
		float bbTop;
		float bbBot;

		GLfloat r; ///< Red - Color of this particular element. Also inherited upon splitting.
		GLfloat g; ///< Red - Color of this particular element. Also inherited upon splitting.
		GLfloat b; ///< Red - Color of this particular element. Also inherited upon splitting.

	protected:
		QuadtreeCell * sub; ///< Pointers to the 4 possible subelements

	public:
		void InsertTriangle(const Triangle & triangle, const BoundingBox & bb,
				const Vector3 & position, const float cubeSize,
				const unsigned char depth);

		void SetColor(GLfloat r = 1.0, GLfloat g = 1.0, GLfloat b = 1.0);
		void Split(void); ///< Splits an element into 8 subelements.
		bool Clean(void);
		void Paint(void); ///< Paints the element itself and its subelements (if any).
	protected:
		bool CheckIntersection(const Triangle & tri, const Vector3 & pos,
				const float & scale, const BoundingBox & bb) const;
	};

	// Variables
public:
	QuadtreeCell * tree; ///< Pointer towards the topmost cell
	unsigned char depth;
	double cellSize; ///< Size (length, width, depth) of one cell at the lowest level. Resolution of the Octree.

private:
	GLuint displayListIndex; ///< Variable pointing to the OpenGL display list.
	bool displayListGenerated; ///< Flag showing if an OpenGL display list has been created.
	bool refresh; ///< Flag to show, that the OpenGL display list has to be recreated.

	Triangle triangle;

	// Methods
public:
	void InsertTriangle(Triangle tri);
	void Paint(void);

};

#endif /* QUADTREE_H_ */
