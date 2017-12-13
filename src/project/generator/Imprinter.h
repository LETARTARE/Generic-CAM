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
 * The values of the cells are defined in the middle of each cell. They are
 * shifted by 1/2 dx and 1/2 dy respectively.
 *
 * The setup of the objects is done directly by using the basic
 * functions to generate the objects or by imprinting 3D triangle-
 * meshes.
 *
 * This class also contains some basic functions to manipulate the
 * object.
 *
 * The really fancy functions are found in DexelTarget.
 *
 *
 *
 *
 *
 */

#include "../../3D/Geometry.h"
#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Vector3.h"

#include <GL/gl.h>

//TODO: Change in concept (together with Dexeltarget) there should be only be an up, down and normal vectors for up and down.

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
	float normalx;
	float normaly;
	//  normalz is sqrt(1-normalx*normalx-normaly*normaly)

	// Methods
public:
	bool IsVisible(void); ///< A cell is visible, if the upper level is above the lower one.
	void Swap(ImprinterElement& b);
};

//TODO Base Imprinter on BoundingBox
class Imprinter {
	friend class GeneratorTest; //TODO: Remove this friend class.
public:
	enum face_t {
		facing_up, //!< Triangle facing up
		facing_down, //!< Triangle facing down
		facing_side, //!< Triangle facing to the side
		other //!< Something else
	};

	// Constructor / Destructor
public:
	Imprinter();
	Imprinter(const size_t countX, const size_t countY,
			const double resolutionX, const double resolutionY);
	Imprinter(const double sizeX, const double sizeY, const double sizeZ,
			const double resolutionX, const double resolutionY);
	Imprinter(const Imprinter& ip); ///< Copy constructor
	Imprinter& operator=(const Imprinter &b); ///< Assignment operator
	virtual ~Imprinter();
private:
	void InitInstance(void);

	// Methods
public:

// **** Low level ****

	void PresetResolution(const double resolutionX, const double resolutionY =
			-1);
	void PresetResolution(const Imprinter &other);

	void CopyRescale(const Imprinter &other, const size_t cellCount);

	bool SetupField(const size_t sizeX, const size_t sizeY,
			const double resolutionX = -1, const double resolutionY = -1);
	bool SetupField(const Imprinter& other);
	void ClearField(void); ///< Deallocate the field from memory
	bool IsMemoryAllocated(void) const; ///< Test, if memory has been allocated
	size_t MemoryUsageInBytes(void) const;

	double GetSizeX(void) const;
	double GetSizeY(void) const;
	double GetSizeZ(void) const;
	double GetResolutionX(void) const;
	double GetResolutionY(void) const;
	size_t GetCountTotal(void) const;
	size_t GetCountX(void) const;
	size_t GetCountY(void) const;

	void Refresh(); ///< Regenerates the OpenGL displaylist.
	void Paint() const; ///< Paint the Imprinter at the origin in OpenGL.

// ***** Imprinting geometry *****

	void InitImprinting(void);
	void InsertTriangle(Vector3 a, Vector3 b, Vector3 c,
			face_t facetype = other);
	void InsertGeometrie(const Geometry *geometry,
			const AffineTransformMatrix & shift);
	void FinishImprint(void);

// ***** Basic shape setup *****

	/**\brief Setup a box */
	bool SetupBox(const double sizeX, const double sizeY, const double sizeZ,
			const double resolutionX = -1, const double resolutionY = -1);
	/**\brief Setup a sphere */
	void SetupSphere(double radius, const double resolutionX = -1,
			const double resolutionY = -1);
	/**\brief Setup a cylinder */
	void SetupCylinder(double radius, double height, const double resolutionX =
			-1, const double resolutionY = -1);
	/**\brief Setup a disc */
	void SetupDisc(double radius, const double resolutionX = -1,
			const double resolutionY = -1);

// ***** Test functions *****

	bool IsFilled(int x, int y, double height) const; ///< Test, if at cell[x,y] the level at height is filled.
	bool IsFilled(size_t p, double height) const; ///< Test, if at cell[p] the level at height is filled.
	bool IsFilledAbove(int x, int y, double height) const; ///< Test, if upper in cell(x,y) is above height.
	bool IsFilledAbove(size_t p, double height) const; ///< Test, if upper in cell(x,y) is above height.
	bool IsFilled(size_t p) const; ///< Test, if cell(p) has a particle somewhere.
	bool IsVisible(int x, int y) const; ///< Synonymous with IsFilled
	bool IsVisible(size_t p) const; ///< Synonymous with IsFilled
	bool IsOnOuterBorder(size_t p) const; ///< Test, if cell belongs to the outermost row.
	bool IsSurrounded(size_t p) const; ///< Test, if cell is not on outer border and surrounded by filled cells. Does not check cell itself.
	bool IsStandAlone(size_t p, double height) const; ///< Test, if cell is not on outer border and surrounded by filled cells at a certain height. Does not check cell itself.

	double GetMeanLevel(int x, int y) const; ///< Get the middle of the cell[x,y], otherwise return -1;
	double GetMeanLevel(size_t p) const; ///< Get the middle of the cell[p], otherwise return -1;
	double GetLevel(double x, double y) const; ///< Get the up-height at cell closest to point(x,y). Otherwise -1;
	double GetMaxLevel(void) const; ///< Returns the max value of the visible elements in the field.
	const ImprinterElement GetElement(double x, double y) const;

// ***** Manipulation *****

	void Empty(void); ///< Empty the volume
	void Fill(void); ///< Fill the volume

	/**\brief OR assignment operator (= Union)
	 *
	 * Adds two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * Additions is equivalent to a "or" (or union) operation on the volume.
	 */
	Imprinter & operator|=(const Imprinter &other);

	/**\brief OR operator (= Union)
	 *
	 * Adds two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * Additions is equivalent to a "or" (or union) operation on the volume.
	 */
	const Imprinter operator|(const Imprinter& other) const;

	/**\brief DIFF assignment operator (= Subtraction)
	 *
	 * Subtract two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * If the subtraction always removes material from the top.
	 */
	Imprinter & operator-=(const Imprinter &other);

	/**\brief DIFF operator (= Subtraction)
	 *
	 * Adds two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 * Additions is equivalent to a "or" (or union) operation on the volume.
	 */
	const Imprinter operator-(const Imprinter& other) const;

	/**\brief INTERSECTION assignment operator (= And)
	 *
	 * Intersect two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 */
	Imprinter & operator&=(const Imprinter &other);

	/**\brief INTERSECTION operator (= And)
	 *
	 * Intersect two Imprinter%s, if they have the same size.
	 * If they are diffrently sized, nothing happens.
	 */
	const Imprinter operator&(const Imprinter& other) const;

	/**\brief Addition assignment operator
	 *
	 * Shifts the geometry of an imprinter up by value.
	 */
	Imprinter & operator+=(const double value);

	/**\brief Addition operator
	 *
	 * Shifts the geometry of an imprinter up by value.
	 */
	const Imprinter operator+(const double value) const;

// ***** Inverting *****

	void HardInvert(void); ///< Invert field without contour.
	void MaxFilling(void); ///< Fill up cells with particle to the max.
	void InvertTop(void); ///< Invert the top levels height.
	void NegateZ(void); ///< Invert around 0.
	void MirrorY(void); ///< Mirror along the Y axis.
	void MirrorZ(void); ///< Mirror along the Z axis.
	void RotateX180(void); ///< Rotate along the X axis.

// ***** Complex functions *****

	void CleanOutlier(void); ///< Defunct.
	void Limit(void); ///< Limit values of the field to the size of the Imprinter in z.

// ***** Folding *****

	/**\brief Folding operation. Surface is dropped at position
	 *
	 * @param x Integer position of cell.
	 * @param y Integer position of cell.
	 * @param z Float Height of center of 2nd Imprinter.
	 * @param b 2nd Imprinter
	 */
	void ShiftDown(int x, int y, double z, const Imprinter &b);
	void TouchErase(int x, int y, double z, double level, const Imprinter &b);
	void FoldRaise(const Imprinter &b); ///< Folding operation of two Imprinters. Surface is only raised.
	void FoldReplace(const Imprinter &b); ///< Folding operation. Model is replaced.

private:
	Vector3 RecalculateCellNormals(double p0, double p1, double p2,
			double p3) const;

	// Member variables
public:

	bool displayBox; ///< Display the up surface as a continuous plane.
	bool displayField; ///< Display the up and down surface as planar squares.
	bool displayAboveDown; ///< Display the above down surface as a grid.
	bool displayBelowUp; ///< Display the below up surface as a grid.
	bool displayAboveUp; ///< Display the above up surface as a grid.
	bool displayBelowDown; ///< Display the below down surface as a grid.

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
