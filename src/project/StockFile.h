///////////////////////////////////////////////////////////////////////////////
// Name               : StockFile.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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

#ifndef STOCKFILE_H_
#define STOCKFILE_H_

/*!\class StockFile
 * \ingroup document
 * \brief Collection of raw material in the workshop
 *
 * A library of raw material.
 */

#include "StockMaterial.h"
#include "../3D/AffineTransformMatrix.h"

#include <wx/filename.h>

class StockFile {
	// Constructor / Destructor
public:
	StockFile();
	virtual ~StockFile();

	// Member variables
public:
	wxString name;
	ArrayOfStockMaterial stockMaterials;

private:
	wxFileName fileName;

	// Methods
public:
	bool LoadFromFile(wxString filename);
	bool WriteToFile(wxString filename);
};

#endif /* STOCKFILE_H_ */
