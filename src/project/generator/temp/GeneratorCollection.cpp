///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorCollection.cpp
// Purpose            : Collection of Generators
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

#include "GeneratorCollection.h"

#include "GeneratorNone.h"
#include "GeneratorPositioningDrills.h"
#include "GeneratorLoadFromFile.h"
#include "GeneratorAreaGridDexel.h"
#include "GeneratorTest.h"
#include "GeneratorDrillDexel.h"
#include "GeneratorSurfaceDexel.h"
#include "GeneratorAreaMillingDynamic.h"
#include "GeneratorOutlineDexel.h"

#include <typeinfo>

const size_t N_GENERATORS = 9;

Generator* GeneratorCollection::NewGenerator(size_t generatorNr)
{
	assert(generatorNr < GetCount());
	switch(generatorNr){
	case 0:
		return new GeneratorNone();
		break;
	case 1:
		return new GeneratorPositioningDrills();
		break;
	case 2:
		return new GeneratorLoadFromFile();
		break;
	case 3:
		return new GeneratorAreaGridDexel();
		break;
	case 4:
		return new GeneratorAreaMillingDynamic();
		break;
	case 5:
		return new GeneratorTest();
		break;
	case 6:
		return new GeneratorDrillDexel();
		break;
	case 7:
		return new GeneratorOutlineDexel();
		break;
	case 8:
		return new GeneratorSurfaceDexel();
		break;	}
	return NULL;
}

size_t GeneratorCollection::GetCount()
{
	return N_GENERATORS;
}

bool GeneratorCollection::FindGenerator(const Generator* generator,
		size_t *nr) const
{
	assert(generator !=NULL);
	for(size_t n = 0; n < GetCount(); n++)
		if(typeid(*(generator)) == typeid(*(generators[n]))){
			*nr = n;
			return true;
		}
	return false;
}

bool GeneratorCollection::FindGenerator(const wxString& name, size_t *nr) const
{
	for(size_t n = 0; n < GetCount(); n++)
		if(generators[n]->GetName().Cmp(name) == 0){
			*nr = n;
			return true;
		}
	return false;
}

GeneratorCollection::GeneratorCollection()
{
	// Create a list of all available generators
	generators = new Generator*[GetCount()];
	for(size_t i = 0; i < GetCount(); i++)
		generators[i] = NewGenerator(i);
}
GeneratorCollection::GeneratorCollection(const GeneratorCollection& other)
{
	printf(__FILE__ ": Copy constructor called.");
	generators = new Generator*[GetCount()];
	for(size_t i = 0; i < GetCount(); i++)
		generators[i] = NewGenerator(i);
}

wxString GeneratorCollection::GetName(size_t generatorNr) const
{
	if(generatorNr >= GetCount()) return _T("");
	return generators[generatorNr]->GetName();
}

GeneratorCollection::~GeneratorCollection()
{
	for(size_t i = 0; i < GetCount(); i++)
		delete generators[i];
	delete[] generators;
}

