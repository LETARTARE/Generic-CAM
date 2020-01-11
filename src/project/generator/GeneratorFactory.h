///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorFactory.h
// Purpose            : Factory pattern for Generators
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.03.2015
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

#ifndef GENERATORFACTORY_H_
#define GENERATORFACTORY_H_

/*!\class GeneratorFactory
 * \ingroup GeneratorBasics
 * \brief Factory for all available Generator%s
 *
 * To add new Generator%s in GeneratorCollection.cpp, add Generator
 * to the NewGenerator(...) function
 */

#include "Generator.h"

#include <stddef.h>

#define TYPE_GENERATORAREAGRID				17420528
#define TYPE_GENERATORAREAMILLINGDYNAMIC	16974365
#define TYPE_GENERATORDRILLDEXEL			299440696
#define TYPE_GENERATORLOADFROMFILE			9731665
#define TYPE_GENERATOROUTLINE				88500055
#define TYPE_GENERATORSURFACE				24947036
#define TYPE_GENERATORTEST					34745572

class GeneratorFactory {
	friend class DialogToolpathGenerator;
public:
	GeneratorFactory();
//	GeneratorFactory(const GeneratorFactory& other);
	virtual ~GeneratorFactory();

	static Generator * NewGenerator(size_t generatorNr);

//	static size_t GetCount();
//	wxString GetName(size_t generatorNr) const;
//	bool FindGenerator(const Generator* generator, size_t *nr) const;
//	bool FindGenerator(const wxString& name, size_t *nr) const;

private:
//	Generator ** generators;
};

#endif /* GENERATORFACTORY_H_ */
