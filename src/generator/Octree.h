///////////////////////////////////////////////////////////////////////////////
// Name               : Octree.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.08.2011
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


#ifndef OCTREE_H_
#define OCTREE_H_

#include <wx/dynarray.h>

/*!\class Octree
 * \brief ...
 *
 * ...
 */

class OctreeElement {
	// Constructor / Destructor
public:
	OctreeElement();
	virtual ~OctreeElement();
	// Member variables
public:


	// Methods
public:
};
WX_DECLARE_OBJARRAY(OctreeElement, ArrayOfOctreeElement)
;

/*!\class Octree
 * \brief ...
 *
 * ...
 */

class Octree {
	// Constructor / Destructor
public:
	Octree();
	virtual ~Octree();

	// Member variables
public:

private:
	ArrayOfOctreeElement oe;

	// Methods
public:


	void Paint(void);
};

#endif /* OCTREE_H_ */
