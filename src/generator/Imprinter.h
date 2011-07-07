///////////////////////////////////////////////////////////////////////////////
// Name               : Imprinter.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.07.2011
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


#ifndef IMPRINTER_H_
#define IMPRINTER_H_

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Geometry.h"
#include "../3D/Vector3.h"

/*!\class Imprinter
 * \brief ...
 *
 * ...
 */

class ImprinterElement {
	// Constructor / Destructor
public:
	ImprinterElement();
	virtual ~ImprinterElement();
	// Member variables
public:
	float upperLimit;
	float lowerLimit;
	float upperLimitUpside;
	float lowerLimitUpside;
	float upperLimitDownside;
	float lowerLimitDownside;

	// TODO: ...later...
	//	float normal; // 0..Pi/2<
	//	float orientation; // 0..2Pi

	// Methods
public:
	bool IsVisible(void)
	{
		return (upperLimit > lowerLimit);
	}
};

class Imprinter {
	// Constructor / Destructor
public:
	Imprinter(const double sizeX = 0.1, const double sizeY = 0.1,
			const double sizeZ = 0.05, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	Imprinter(const Imprinter& ip); ///> Copy constructor
	virtual ~Imprinter();

	// Member variables
public:
	AffineTransformMatrix matrix;

private:
	ImprinterElement *field;
	double sx, sy, sz;
	size_t nx, ny, N;
	double rx, ry;
protected:
	Vector3 colorNormal;
	Vector3 colorUnscratched;
	Vector3 colorTodo;

	// Methods
public:
	void Paint() const;

	void SetupBox(const double sizeX, const double sizeY, const double sizeZ,
			const double resolutionX = 0.001, const double resolutionY = 0.001);
	size_t MemoryUsageInBytes(void);
	void InitImprinting(void);
	void InsertTriangle(Vector3 a, Vector3 b, Vector3 c, char strategy = 1);
	void InsertGeometrie(const Geometry *geometry, double shiftZ = 0.0);
	void FinishImprint(void);

	void SetSphere(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	void SetCylinder(double radius,double height, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	void SetDisc(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	void FoldRaise(const Imprinter *b);
	void FoldReplace(const Imprinter *b);
	void FlipX(void);
	void FlipY(void);
	void Rot90(void);
	void Rot180(void);
	void Rot270(void);

};

#endif /* IMPRINTER_H_ */
