///////////////////////////////////////////////////////////////////////////////
// Name               : Run.h
// Purpose            : Defines a machine run.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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

#ifndef RUN_H_
#define RUN_H_

#include <wx/dynarray.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/txtstrm.h>

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Geometry.h"
#include "../machine/Machine.h"
#include "StockMaterial.h"
#include "Toolbox.h"
#include "ToolPath.h"
#include "Workpiece.h"

class ArrayOfObject;
class ArrayOfWorkpiece;

/*!\class Run
 * \brief ...
 *
 * The workpiecePlacement matrix herein is for rotating the workpiece.
 * The machine itself contains another matrix used for placing the
 * workpiece in the machine.
 */

class Run {
	// Constructor / Destructor
public:
	Run();
	virtual ~Run();
	// Member variables
public:
	wxString name;
	bool selected;
	bool modified;

	AffineTransformMatrix workpiecePlacement; ///> For flipping the workpiece to machine the other sides.

	int workpieceNr;

	Machine machine;
	Toolbox toolbox;
	int selectedTool;

	ArrayOfToolPath toolpaths;

	// Methods
public:

	void Paint(const ArrayOfObject& objects,
			const ArrayOfWorkpiece& workpieces) const;
	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

	void ToStream(wxTextOutputStream & stream);
	bool FromStream(wxTextInputStream & stream, int runNr,Project * project);

	void ToolpathToStream(wxTextOutputStream & stream);

};
WX_DECLARE_OBJARRAY(Run, ArrayOfRun);

#endif /* RUN_H_ */
