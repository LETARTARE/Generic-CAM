///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorDexel.h
// Purpose            : Base class for Dexel based generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef GENERATORDEXEL_H_
#define GENERATORDEXEL_H_

/*!\class GeneratorDexel
 * \ingroup Generator
 * \brief Base class for all generators that use a Dexel representation
 *
 * The Dexel approach may not be the best one in respect to precisision, but it is
 * the fastest one (and the easiest one to programm).
 *
 * The workflow for Dexel generators is:
 *  -# Set up the target and start representations. The target-representation
 *     has an additional operation to mark areas the are not to be milled (yet)
 *     or that cannot be milled, because the machine would collide with the
 *     workpiece. It also considers the form of the tool used so that control
 *     can follow the surface of the target workpiece.
 *  -# Use some algorithms to generate toolpath segments
 *  -# Fuse the segments into a full toolpath
 *
 */

#include "../../Config.h"

#include "Generator.h"
#include "DexelTarget.h"
#include "ProtoToolpath.h"

#include <stddef.h>
#include <vector>

class GeneratorDexel:public Generator {
public:
	GeneratorDexel(size_t ID);
	virtual ~GeneratorDexel();

	virtual void ToStream(wxTextOutputStream & stream);
	virtual bool FromStream(wxTextInputStream & stream);

	virtual void Paint(void) const;

protected:

	void PrepareTargets(const Run &run,
			const std::vector <Object> &objects, const DexelTarget &start);

	void QuickCollectToolpaths(std::vector <ProtoToolpath> &ptp,
			const double pathDistance);

	DexelTarget start; ///< Stock before generator
	DexelTarget selected; ///< Stock with selection to size
	DexelTarget target; ///< Target object without stock

	DexelTarget simulation; ///< Recreation of milling process while simulating
	DexelTarget debug; ///< Debugging display

#ifdef _DEBUGMODE
	Vector3 debugOrigin;
#endif
};

#endif /* GENERATORDEXEL_H_ */
