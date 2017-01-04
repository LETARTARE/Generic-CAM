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

#include "../generator/GeneratorNone.h"
#include "../generator/GeneratorPositioningDrills.h"
#include "../generator/GeneratorLoadFromFile.h"
#include "../generator/GeneratorAreaGridDexel.h"
#include "../generator/GeneratorFast.h"
#include "../generator/GeneratorTest.h"

#include <typeinfo>

const size_t N_GENERATORS = 6;

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
		return new GeneratorFast();
		break;
	case 5:
		return new GeneratorTest();
		break;
	}
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

