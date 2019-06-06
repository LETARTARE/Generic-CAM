///////////////////////////////////////////////////////////////////////////////
// Name               : Hull.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.06.2011
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

#ifndef HULL_H_
#define HULL_H_
/*!\class Hull
 * \brief A (possibly closed) hull made from trinagles
 *
 * This class stores and operates on a hull made from a triangle soup.
 * Triangles are connected with each other to form a hull. This hull can
 * be intersected by a plane to return closed polygons.
 */

#include <stddef.h>
#include <stdint.h>
#include <set>
#include <string>
#include <vector>

#include "AffineTransformMatrix.h"
#include "BoundingBox.h"
#include "Vector3.h"

class Geometry;
class Polygon3;

class Hull {
	// Constructor/ Destructor
public:
	Hull();
	virtual ~Hull();

	class Edge {
	public:
		Edge();
		size_t va, vb;
		size_t ta, tb;
		uint_least8_t trianglecount;
		Vector3 n;
		size_t OtherTriangle(size_t n);
	};
	class Triangle {
	public:
		Triangle();
		size_t va, vb, vc;
		size_t ea, eb, ec;
		Vector3 n;
		int Direction(size_t i1, size_t i2); //!< Test the direction of rotation of two indices respective to a triangle.
	};

	// Member variables
public:
	bool smooth;
	bool paintEdges;
	bool paintTriangles;
	bool paintVertices;
	bool paintNormals;
	bool paintSelected;

	AffineTransformMatrix matrix; //!< Transformation of the data.

private:
	std::set <size_t> selected; // Selected Vertices
	std::vector <Vector3> v; // Vertices
	std::vector <Vector3> vn; // Normal for vertices
	std::vector <Hull::Edge> e; // Edges
	std::vector <Hull::Triangle> t; // Triangles

	// Methods
public:
	void Clear(void);
	void SetEpsilon(double newEpsilon);
	void Paint(void) const;
	bool IsClosed(void) const; //!< Test, if the hull is perfectly closed.

	void CalcNormals(void);
	void FlipNormals(void);

	size_t SelectAll(void);
	size_t UnselectAll(void);
	size_t SelectByPlane(Vector3 n, double d);
	size_t UnselectByPlane(Vector3 n, double d);
	size_t SelectByNormal(Vector3 n, double limit = 0.0);
	size_t UnselectByNormal(Vector3 n, double limit = 0.0);
	size_t CountSelected(void) const;

	void ApplyTransformation(const AffineTransformMatrix &matrix);
	void ApplyTransformation(void);

	void CopyFrom(const Geometry &geometry);
	void CopyTrianglesFrom(const Geometry &geometry);

	bool LoadObj(std::string filename); //!< Load Wavefront OBJ file.

	size_t AddTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c);
	size_t AddTriangleTransform(const Vector3 &a, const Vector3 &b,
			const Vector3 &c, const AffineTransformMatrix &transformMatrix);
	size_t AddTriangleWithNormals(const Vector3 &a, const Vector3 &b,
			const Vector3 &c, const Vector3 &na, const Vector3 &nb,
			const Vector3 &nc);
	size_t AddTriangleWithNormal(const Vector3 &a, const Vector3 &b,
			const Vector3 &c, const Vector3 &n);

	void AddQuad(const Vector3 &a, const Vector3 &b, const Vector3 &c,
			const Vector3 &d);
	void AddQuadTransform(const Vector3 &a, const Vector3 &b, const Vector3 &c,
			const Vector3 &d, const AffineTransformMatrix &transformMatrix);

	Polygon3 IntersectPlane(Vector3 n, double d);
	Vector3 GetCenter(void) const;

	size_t GetVertexCount(void) const
	{
		return v.size();
	}
	Vector3 GetVertex(const size_t i) const
	{
		return v[i];
	}

private:
	double epsilon;
	double epsilon2;
	std::set <size_t> openedges;
	std::set <size_t> openvertices;

	size_t FindVertex(const Vector3& x);
	size_t FindEdge(const size_t indexa, const size_t indexb);
	Vector3 PlaneProjection(const Vector3 &a, const Vector3 &b, Vector3 n,
			double d) const;
};

#endif /* HULL_H_ */
