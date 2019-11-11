///////////////////////////////////////////////////////////////////////////////
// Name               : MatlabFile.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.08.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MATLABFILE_H_
#define MATLABFILE_H_

/*!\class MatlabFile
 * \brief Matlab MAT file
 *
 * With this class MatlabMatrix%s can be read and written to Matlab MAT files.
 *
 *  \warning{In V4 only 2 dimenstional double matrices can be stored.}
 */

#include "MatlabMatrix.h"

#include <string>
#include <stdio.h>

class MatlabFile {
public:
	enum Version {
		V4 = 4, V6 = 6
	};

public:
	MatlabFile(); //!< Constructor
	MatlabFile(const MatlabFile& other); //!< Copy constructor
	MatlabFile& operator=(const MatlabFile& other); //!< Assignment constructor
	MatlabFile(const std::string& filename, Version version = V4); //!< Constructor with setting filename
	virtual ~MatlabFile(); //!< Destructor

	void SetVersion(Version version);
	Version GetVersion(void) const;

	void SetFilename(const std::string& filename); //!< Set a new filename
	bool IsOpen(void) const; //!< Test if file is open
	void Close(void); //!< Close the file. This is also done by the Destructor.
	/*! \brief Read a MatlabMatrix from the file
	 *
	 * @param M Pointer to a MatlabMatrix
	 * @param matrixname Search for this matrix in the file.
	 */
	void ReadMatrix(MatlabMatrix* M, const std::string& matrixname = "");
	/*! \brief Write Matrix to file
	 *
	 * If the file is open, append the matrix, otherwise open the file and overwrite the
	 * data with this matrix.
	 * @param M Pointer to a MatlabMatrix
	 */
	void WriteMatrix(const MatlabMatrix& M);

private:
	Version version;
	FILE* fhd;
	std::string filename;
};

#endif /* MATLABFILE_H_ */
