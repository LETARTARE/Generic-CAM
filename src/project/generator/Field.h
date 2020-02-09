///////////////////////////////////////////////////////////////////////////////
// Name               : Field.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.01.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_PROJECT_GENERATOR_FIELD_H_
#define SRC_PROJECT_GENERATOR_FIELD_H_

/*!\class Field
 * \brief ...
 *
 * ...
 */

#include "../../3D/BoundingBox.h"

class Field:public BoundingBox {
public:
	Field();
	Field(BoundingBox box, double resolutionX, double resolutionY);
	Field(BoundingBox box, size_t cellCount);
	virtual ~Field();

	void SetSize(double x, double y, double z);
	double GetSizeX(void) const;
	double GetSizeY(void) const;
	double GetSizeZ(void) const;

	bool IsMemoryAllocated(void) const; ///< Test, if memory has been allocated
	size_t MemoryUsageBytes(void) const;
	void FreeMemory(void);

	void SetOrigin(Vector3 position);
	void SetOrigin(double x, double y, double z = 0.0);
	Vector3 GetOrigin(void) const;
	double GetOriginX(void) const;
	double GetOriginY(void) const;
	double GetOriginZ(void) const;

	void SetResolution(double rx, double ry = -1);
	void SetResolution(const Field &other);
	void SetCount(size_t nx, size_t ny);
	void SetCount(const Field &other);
	void SetMaxTotalCount(size_t N);
	double GetResolutionX(void) const;
	double GetResolutionY(void) const;

	void CopyRescale(const Field &other, const size_t newMaxCellCount);

	void AdaptSizeZ(void);
	void AdaptSizeOriginZ(void);

private:
	void SetupField(size_t nx, size_t ny);

protected:
	Field(const Field& other); ///< Copy constructor
	Field& operator=(const Field &other); ///< Assignment operator

private:
	size_t nx;
	size_t ny;
	size_t N;

	double *field;
};

#endif /* SRC_PROJECT_GENERATOR_FIELD_H_ */
