///////////////////////////////////////////////////////////////////////////////
// Name               : VoxelVolume.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.09.2017
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

#ifndef _VOXELVOLUME_H_
#define _VOXELVOLUME_H_

/*!\class VoxelVolume
 * \brief Definition of a volume in 3D-space based on voxel
 *
 * A voxel is a volume pixel. The volume contains a 2D grid in XY. Each gridpoint
 * has a upper and lower value in Z. The volume between these is filled. If the
 * upper level is below the lower, the volume pixel is considered empty.
 *
 */

#include "../../3D/BoundingBox.h"

class VoxelVolume:public BoundingBox {

public:
	class Voxel {
		// Constructor / Destructor
	public:
		Voxel();
		virtual ~Voxel();
		bool IsVisible(void); ///< A cell is visible, if the upper level is above the lower one.
		void Swap(Voxel& b);
	public:
		float up;
		float down;
		float normalupx;
		float normalupy;
		float normaldownx;
		float normaldowny;
		//  normal in z is sqrt(1-normalx*normalx-normaly*normaly)
	};

public:
	VoxelVolume();
	virtual ~VoxelVolume();

};

#endif /* _VOXELVOLUME_H_ */
