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
///////////////////////////////////////////////////////////////////////////////

#ifndef IMPRINTER_H_
#define IMPRINTER_H_

/*!\class Imprinter
 * \ingroup GeneratorBasics
 * \brief Definition of 3D objects based on a upper and a lower layer
 *
 * The Imprinter contains representations of 2.5D objects.
 * It contains 2D arrays, that capture the levels of the upper and lower
 * surface of an object.
 *
 * The setup of the objects is done directly by using the basic
 * functions to generate the objects or by imprinting 3D triangle-
 * meshes.
 *
 * This class also contains some basic functions to manipulate the
 * object.
 *
 * The really fancy functions are found in DexelTarget.
 */

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Geometry.h"
#include "../../3D/Vector3.h"

#include <GL/gl.h>

class ImprinterElement {
	// Constructor / Destructor
public:
	ImprinterElement();
	virtual ~ImprinterElement();
	// Member variables
public:
	float up;
	float down;

	float aboveDown;
	float belowUp;
	float aboveUp;
	float belowDown;

	// TODO: Add a surface orientation to the dexel cells.
	//	float normal; // 0..Pi/2<
	//	float orientation; // 0..2Pi

	// Methods
public:
	bool IsVisible(void); ///< A cell is visible, if the upper level is above the lower one.
	void Swap(ImprinterElement& b); //TODO: Replace everywhere with std::swap(...)
};

//TODO: Base Imprinter on BoundingBox
class Imprinter {
public:
	enum face_t {
		facing_up, facing_down, facing_side, other
	};

	// Constructor / Destructor
public:
	Imprinter(const double sizeX = 0.01, const double sizeY = 0.01,
			const double sizeZ = 0.05, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	Imprinter(const Imprinter& ip); ///< Copy constructor
	Imprinter& operator=(const Imprinter &b); ///< Assignment operator
	virtual ~Imprinter();

	// Methods
public:

	// **** Low level ****

	bool SetupField(const size_t sizeX, const size_t sizeY,
			const double resolutionX = 0.001, const double resolutionY = 0.001);
	void ClearField(void); ///< Deallocate the field from memory
	size_t MemoryUsageInBytes(void) const;

	/**\brief Test, if memory has been allocated */
	bool IsMemoryAllocated(void) const
	{
		return (field == NULL);
	}
	double GetSizeX(void) const
	{
		return sx;
	}
	double GetSizeY(void) const
	{
		return sy;
	}
	double GetSizeZ(void) const
	{
		return sz;
	}
	double GetSizeRX(void) const
	{
		return rx;
	}
	double GetSizeRY(void) const
	{
		return ry;
	}

	void Refresh();
	void Paint() const; ///< Paint the Imprinter at the origin in OpenGL.

	// ***** Imprinting geometry *****

	void Empty(void); ///< Empty all cells
	void InitImprinting(void);
	void InsertTriangle(Vector3 a, Vector3 b, Vector3 c,
			face_t facetype = other);
	void InsertGeometrie(const Geometry *geometry,
			const AffineTransformMatrix & shift);
	void FinishImprint(void);

	// ***** Basic shape setup *****

	/**\brief Setup a box */
	bool SetupBox(const double sizeX, const double sizeY, const double sizeZ,
			const double resolutionX = 0.001, const double resolutionY = 0.001);
	/**\brief Setup a sphere */
	void SetupSphere(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);
	/**\brief Setup a cylinder */
	void SetupCylinder(double radius, double height, const double resolutionX =
			0.001, const double resolutionY = 0.001);
	/**\brief Setup a disc */
	void SetupDisc(double radius, const double resolutionX = 0.001,
			const double resolutionY = 0.001);

	// ***** Test functions *****

	bool IsFilled(int x, int y, double height); ///< Test, if at cell[x,y] the level at height is filled.
	bool IsFilled(size_t p, double height); ///< Test, if at cell[p] the level at height is filled.
	bool IsFilledAbove(int x, int y, double height); ///< Test, if upper in cell(x,y) is above height.
	bool IsFilled(size_t p); ///< Test, if cell(p) has a particle somewhere.
	bool IsVisible(int x, int y); ///< Synonymous with IsFilled
	bool IsVisible(size_t p); ///< Synonymous with IsFilled
	bool IsOnOuterBorder(size_t p); ///< Test, if cell belongs to the outermost row.
	bool IsSurrounded(size_t p); ///< test, if cell is not on outer border and surrounded by filled cells. Does not check cell itself.

	double GetMeanLevel(int x, int y); ///< Get the middle of the cell[x,y], otherwise return -1;
	double GetMeanLevel(size_t p); ///< Get the middle of the cell[p], otherwise return -1;
	double GetLevel(double x, double y); ///< Get the up-height at cell closest to point(x,y). Otherwise -1;

	// ***** Manipulation *****

	/**\brief Addition/assignment operator
	 *
	 * Adds two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * Additions is done, by copying every visible column from the
	 * right operand into this Imprinter.
	 */
	Imprinter & operator+=(const Imprinter &a);

	/**\brief Addition operator
	 *
	 * Adds two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * Additions is done, by copying every visible column from the
	 * right operand into this Imprinter.
	 */
	const Imprinter operator+(const Imprinter& a) const;

	void CleanOutlier(void); ///< Defunct.
	void Limit(void); ///< Limit values of the field to the size of the Imprinter in z.
	void FoldRaise(const Imprinter &b); ///< Folding operation of two Imprinters. Surface is only raised.
	void FoldReplace(const Imprinter &b); ///< Folding operation. Model is replaced.
	/**\brief Folding operation. Surface is dropped at position
	 *
	 * @param x Integer position of cell.
	 * @param y Integer position of cell.
	 * @param z Float Height of center of 2nd Imprinter.
	 * @param b 2nd Imprinter
	 */
	void FoldLower(int x, int y, double z, const Imprinter &b);
	void HardInvert(void); ///< Invert field without contour.
	void MaxFilling(void); ///< Fill up cells with particle to the max.
	void InvertTop(void); ///< Invert the top levels height.
	void InvertZ(void); ///< Mirror along the z axis.
	void FlipX(void); ///< Mirror along the x axis.
//	void FlipY(void);

	// Member variables
public:

	bool displayField;
	bool displayAboveDown;
	bool displayBelowUp;
	bool displayAboveUp;
	bool displayBelowDown;

	Vector3 colorNormal;
	Vector3 colorUnscratched;
	Vector3 colorTodo;

protected:
	ImprinterElement *field;
	size_t nx; ///< Number of cells in x
	size_t ny; ///< Number of cells in y
	size_t N; ///< = nx * ny

	double sx; ///< Size in x
	double sy; ///< Size in y
	double sz; ///< Size in z
	double rx; ///< Resolution in x
	double ry; ///< Resolution in y

	mutable bool refresh; ///< Initialize an update of the OpenGL display-list.

private:
	mutable GLuint displayListIndex; ///< Index of a OpenGL display-list for speedup
	mutable bool displayListGenerated; ///< Flag to initialize display-list only once
};

#endif /* IMPRINTER_H_ */
