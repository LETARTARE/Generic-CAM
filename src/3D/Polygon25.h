///////////////////////////////////////////////////////////////////////////////
// Name               : Polygon3.h
// Purpose            : Contains a 2.5D polygon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.07.2011
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

#ifndef POLYGON25_H_
#define POLYGON25_H_

/*!\class Polygon25
 * \brief Plane polygon in 3D
 *
 * Expansion of the Polygon3 class with functions for 2.5D polygons.
 *
 * All polygons are used as if they were flat polygons in the XY plane with a height assigned
 * to each point.
 */

#include "Polygon3.h"

class Polygon25:public Polygon3 {
public:
	Polygon25();
	virtual ~Polygon25();

	// Methods
public:
	/*! \brief Returns the length, as if the polygon was flat in the XY plane
	 */
	double GetLengthXY(void) const;

	/*! \brief Searches for points below z -0.5 and replaces them with the average value of the point above -0.5
	 *
	 * (Very domain specific function for a very specific problem. Should probably be elsewhere.)
	 */
	void PolygonFillHoles(void);

	/*! \brief MA Filter for polygons with the size of 3
	 *
	 * Replaces every vertex i with the average of the vertices i-1, i, i+1.
	 * \todo Move to the more general Polygon3
	 */
	void PolygonSmooth(void);

	/*! \brief Move the point of the Polygon to the right (outside)
	 *
	 * The function uses the direction of the polygon in the XY plane to
	 * determine outside / right. It assumes, that the polygon is defined
	 * mathematically positive.
	 * \todo Revisit, for this may be broken. Also add interpolating / cutting function for sharp corners.
	 * @param r Distance to move the points of the polygon
	 */
	void PolygonExpand(double r);

	/*! \brief Move the points of the polygon to the left (inside)
	 *
	 * Uses PolygonExpand with negative parameter.
	 *
	 * \todo Remove, as it is covered by PolygonExpand
	 *
	 * @param r Distance to move the points of the polygon
	 */
	void PolygonDiminish(double r);

	/*! \brief Determins if a point is inside or outside the polygon in the XY plane
	 *
	 * Searches the XY plane, if a point is inside or outside the polygon projected onto this plane.
	 *
	 * @param v Vector3 point
	 * @return Boolean, if point is inside
	 */
	bool IsElementInside(const Vector3 &v) const;

	bool IsPolygonInside(const Polygon25 &other) const;

	static void SortPolygonsFromOutside(std::vector<Polygon25> *array);

	/*! \brief Find the closest distance of a line to an element on the polygon
	 *
	 * The algorithm projects the polygon into the xy plane.
	 *
	 * vx and vy also determine the length of the line.
	 *
	 * @param elementInPolygon Number of element in polygon
	 * @param x Starting x-point of line
	 * @param y Starting y-point of line
	 * @param vx x-direction of line
	 * @param vy y-direction of line
	 * @return
	 */
	double DistanceToElement(const size_t elementInPolygon, const double x,
			const double y, const double vx, const double vy) const;

	/*! \brief Calculates the smallest distance of a polygon to this polygon in a certain direction
	 *
	 * @param polygon Reference to another Polygon25
	 * @param vx x-direction
	 * @param vy y-direction
	 * @return Smallest distance between the polygons
	 */
	double DistanceToPolygon(const Polygon25 &polygon, double vx,
			double vy) const;

	/*! \brief Rotate the polygon start to be close to a given point
	 *
	 * (Assumes a closed polygon.)
	 *
	 * @param x X Coordinate of the point
	 * @param y Y Coordinate of the point
	 */
	void RotatePolygonStart(double x, double y);
};

#endif /* POLYGON25_H_ */
