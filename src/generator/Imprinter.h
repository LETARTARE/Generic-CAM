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
	bool IsVisible(void);
	void Set(const ImprinterElement& b);
	void Swap(ImprinterElement& b);
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

	enum face_t {
		facing_up, facing_down, facing_side, other
	};

	bool displayBox;

protected:
	ImprinterElement *field;
	double sx, sy, sz;
	double rx, ry;
	size_t nx, ny, N;

protected:
	Vector3 colorNormal;
	Vector3 colorUnscratched;
	Vector3 colorTodo;

	// Methods
public:

	Imprinter& operator=(const Imprinter &b);
	Imprinter & operator+=(const Imprinter &a);
	const Imprinter operator+(const Imprinter& a) const;

	void Paint() const;
	bool SetupField(const size_t sizeX, const size_t sizeY,
			const double resolutionX = 0.001, const double resolutionY = 0.001);
	void ClearField(void);

	bool SetupBox(const double sizeX, const double sizeY, const double sizeZ,
			const double resolutionX = 0.001, const double resolutionY = 0.001);

	size_t MemoryUsageInBytes(void);
	void InitImprinting(void);
	void InsertTriangle(Vector3 a, Vector3 b, Vector3 c, face_t facetype =
			other);
	void InsertGeometrie(const Geometry *geometry, AffineTransformMatrix shift);
	void FinishImprint(void);

	void SetupSphere(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	void SetupCylinder(double radius, double height, const double resolutionX =
			0.001, const double resolutionY = 0.001);
	void SetupDisc(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);

	bool IsFilled(int x, int y, double height);
	bool IsFilledAbove(int x, int y, double height);
	bool IsFilled(size_t p, double height);
	bool IsFilled(size_t p);
	bool IsOnOuterBorder(size_t p);
	bool IsSurrounded(size_t p);

	bool IsVisible(int x, int y);
	bool IsVisible(size_t p);

	double GetMeanLevel(int x, int y);
	double GetMeanLevel(size_t p);
	double GetLevel(double x, double y);

	void CleanOutlier(void);

	void Limit(void);
	void FoldRaise(const Imprinter &b);
	void FoldReplace(const Imprinter &b);
	void FoldLower(int x, int y, double z, const Imprinter &b);
	void HardInvert(void);
	void MaxFilling(void);
	void InvertTop(void);
	void InvertZ(void);
	void FlipX(void);
	void FlipY(void);
	void Rot90(void);
	void Rot180(void);
	void Rot270(void);

	double GetSizeX(void)
	{
		return sx;
	}
	double GetSizeY(void)
	{
		return sy;
	}
	double GetSizeZ(void)
	{
		return sz;
	}
	double GetSizeRX(void)
	{
		return rx;
	}
	double GetSizeRY(void)
	{
		return ry;
	}

};

#endif /* IMPRINTER_H_ */
