///////////////////////////////////////////////////////////////////////////////
// Name               : ProtoToolpath.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : tobiassch
// Created            : 03.01.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef PROTOTOOLPATH_H_
#define PROTOTOOLPATH_H_

/*!\class ProtoToolpath
 * \brief Toolpath with additional information for sorting
 *
 * Toolpaths are generated in the wrong order. This class contains the
 * sections of a toolpath for later sorting and joining.
 */

#include <stddef.h>
#include <vector>

#include "CNCPosition.h"

class ProtoToolpath {
public:
	ProtoToolpath();
	ProtoToolpath(const std::vector <CNCPosition> &p);
	virtual ~ProtoToolpath();

public:
	bool inserted;
	std::vector <size_t> parents;

	std::vector <CNCPosition> p;

private:
};

#endif /* PROTOTOOLPATH_H_ */
