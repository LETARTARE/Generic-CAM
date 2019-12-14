///////////////////////////////////////////////////////////////////////////////
// Name               : ToolPath.h
// Purpose            : Describing the boundary of the volume to be cut away.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.03.2010
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
//$LastChangedDate: 2011-06-16 01:34:14 +0200 (Do, 16. Jun 2011) $
//$Revision: 56 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////

/*!\class ToolPath
 * \code #include "ToolPath.h"\endcode
 * \brief Describes the boundary of the volume to be cut away.
 *
 */

#ifndef TOOLPATH_H_
#define TOOLPATH_H_

#include "../3D/AffineTransformMatrix.h"
#include "../3D/Geometry.h"
#include "../machine/Tool.h"

class ToolPath:public Geometry {
	// Constructor / Destructor

public:
	ToolPath();
	virtual ~ToolPath();

	// Member variables
public:


	// Methods
public:

	void Generate(Tool const& tool, AffineTransformMatrix const& position1,
			AffineTransformMatrix const& position2);

};

#endif /* TOOLPATH_H_ */
