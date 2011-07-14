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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#ifndef RUN_H_
#define RUN_H_

#include "../3D/Geometry.h"
#include "Toolbox.h"
#include "../machine/Machine.h"
#include "StockMaterial.h"
#include "../simulator/Workpiece.h"
#include "../simulator/ToolPath.h"

#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/dynarray.h>

/*!\class Run
 * \brief ...
 *
 * ...
 */

class Run {
	// Constructor / Destructor
public:
	Run();
	virtual ~Run();
	// Member variables
public:
	wxString runName;

	bool useExtraMachine;
	Machine machine;
	bool useExtraToolbox;
	Toolbox toolbox;

	ToolPath toolPath;

	StockMaterial stockMaterial;
	Workpiece workPiece;
	Geometry target;

	// Methods
public:

	void WriteToFile(wxTextFile &f);

};
WX_DECLARE_OBJARRAY(Run, ArrayOfRun)
;

#endif /* RUN_H_ */
