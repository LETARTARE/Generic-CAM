///////////////////////////////////////////////////////////////////////////////
// Name               : FileGTS.h
// Purpose            : Reads a GTS File.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.08.2010
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

#ifndef FILEGTS_H_
#define FILEGTS_H_

/*!\class FileGTS
 * \ingroup File3D
 * \brief GTS file
 *
 * This class reads holds and displays the content of a GTS file.
 *
 * Documentation on GTS files can be found here:
 * http://gts.sourceforge.net/reference/gts-surfaces.html#GTS-SURFACE-WRITE
 */

#include "GeometryFileAbstract.h"

#include <wx/string.h>

class FileGTS:public GeometryFileAbstract {
	// Constructor/ Destructor
public:
	FileGTS();
	virtual ~FileGTS();

	// Member variables
public:

	//Methods:
public:
	bool ReadFile(wxString fileName);
};

#endif /* FILEGTS_H_ */
