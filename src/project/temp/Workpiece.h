///////////////////////////////////////////////////////////////////////////////
// Name               : Workpiece.h
// Purpose            : The workpiece
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef WORKPIECE_H_
#define WORKPIECE_H_

/*!\class Workpiece
 * \ingroup document
 * \brief Workpiece for a Run
 *
 */

#include "../3D/BooleanBox.h"
#include "../3D/BoundingBox.h"

#include <wx/txtstrm.h>

class Project;

class Workpiece:public BoundingBox {
	// Constructor / Destructor
public:
	Workpiece();
	virtual ~Workpiece();

//	void PrepareModel(void);

// Member variables
public:
	wxString name;
	Project * parent; //!< Pointer back to the Project this Workpiece belongs to.
//	AffineTransformMatrix matrix; //!< Matrix for flipping and rotating the Workpiece.
//	ArrayOfObjectPlacement placements; //!< List of objects to place into the Workpiece.
//	ArrayOfSupport supports; //!< List of extra geometry used as support.

	size_t refObject; //!< Use an Object as the Workpiece definition.

	// The result is of Type DexelTarget. It is written to from each Run during Toolpath generation.
	// it keeps track on how the Workpiece look like at the moment. This Structure is read by the
	// Toolpath Generators as a reference point to start from.
	// This is not optimal. In the end the result has to be stored into a more flexible
	// structure (OctreeSomething, perhaps).
//	DexelTarget model; ///< Result after the Generators have run

//	volatile bool hasRunningGenerator;

private:
	BooleanBox bbox; ///< A BooleanBox is used to generate the Workpiece from embedding the Objects into it.

	// Methods
public:
//	void ToStream(wxTextOutputStream & stream);
//	bool FromStream(wxTextInputStream & stream);
//
//	Vector3 GetCenter(void) const;

	void Paint(void) const;
//	void Update(void);
//	void SortTargets(void);
};

#endif /* WORKPIECE_H_ */
