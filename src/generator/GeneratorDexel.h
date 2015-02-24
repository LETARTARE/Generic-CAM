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

#include "Generator.h"

/*!\class GeneratorDexel
 * \brief Base class for all generators that use a Dexel representation
 *
 * The Dexel approach may not be the best one in respect to precisision, but it is
 * the fastest one (and the easiest one to programm).
 */

class GeneratorDexel:public Generator {
public:
	GeneratorDexel(Project * project, size_t runNr, size_t toolpathNr);
	virtual void CopyFrom(const Generator * other);
	virtual ~GeneratorDexel();
};

#endif /* GENERATORDEXEL_H_ */
