///////////////////////////////////////////////////////////////////////////////
// Name               : FileSTL.h
// Purpose            : Reads a STL File
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.06.2011
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

#ifndef FILESTL_H_
#define FILESTL_H_

#include "GeometryFileAbstract.h"
#include <wx/string.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/datstrm.h>

/*!\class FileSTL
 * \ingroup File3D
 * \brief Stereolithography files
 *
 * STL is a very widespread file format to exchange geometry data
 * between CAD programms. This class reads a STL file and stores its
 * triangles.
 */

class FileSTL:public GeometryFileAbstract {
	// Constructor/ Destructor
public:
	FileSTL();
	virtual ~FileSTL();

	// Member variables
public:

	//Methods:
public:
	bool ReadFile(wxString fileName);
	bool ReadStream(wxInputStream & stream);
	static void WriteStream(wxOutputStream & stream, Geometry & g);
private:
	bool ReadStreamBinary(wxInputStream & stream, bool hasRead5Byte = false);
	bool ReadStreamAscii(wxInputStream & stream, bool hasRead5Byte = false);
};

#endif /* FILESTL_H_ */
