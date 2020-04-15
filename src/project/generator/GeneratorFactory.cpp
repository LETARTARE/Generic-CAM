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

#include "GeneratorFactory.h"

#include "GeneratorAreaGridDexel.h"
#include "GeneratorAreaMillingDynamic.h"
#include "GeneratorDrillDexel.h"
#include "GeneratorLoadFromFile.h"
#include "GeneratorOutlineDexel.h"
#include "GeneratorSurfaceDexel.h"
#include "GeneratorTest.h"

#include <typeinfo>

//const size_t N_GENERATORS = 1;

Generator* GeneratorFactory::NewGenerator(size_t generatorType, size_t ID)
{
	switch(generatorType){
	case TYPE_GENERATORAREAGRID:
		return new GeneratorAreaGridDexel(ID);
		break;
	case TYPE_GENERATORAREAMILLINGDYNAMIC:
		return new GeneratorAreaMillingDynamic(ID);
		break;
	case TYPE_GENERATORLOADFROMFILE:
		return new GeneratorLoadFromFile(ID);
		break;
	case TYPE_GENERATORTEST:
		return new GeneratorTest(ID);
		break;
	case TYPE_GENERATORDRILLDEXEL:
		return new GeneratorDrillDexel(ID);
		break;
	case TYPE_GENERATOROUTLINE:
		return new GeneratorOutlineDexel(ID);
		break;
	case TYPE_GENERATORSURFACE:
		return new GeneratorSurfaceDexel(ID);
		break;
	default:
		throw std::range_error(
				"GeneratorFactory::NewGenerator(...) - generatortype not found");
	}
	return NULL;
}

//size_t GeneratorFactory::GetCount()
//{
//	return N_GENERATORS;
//}
//
//bool GeneratorFactory::FindGenerator(const Generator* generator,
//		size_t *nr) const
//{
//	assert(generator !=NULL);
//	for(size_t n = 0; n < GetCount(); n++)
//		if(typeid(*(generator)) == typeid(*(generators[n]))){
//			*nr = n;
//			return true;
//		}
//	return false;
//}
//
//bool GeneratorFactory::FindGenerator(const wxString& name, size_t *nr) const
//{
//	for(size_t n = 0; n < GetCount(); n++)
//		if(generators[n]->GetName().Cmp(name) == 0){
//			*nr = n;
//			return true;
//		}
//	return false;
//}

GeneratorFactory::GeneratorFactory()
{
//	// Create a list of all available generators
//	generators = new Generator*[GetCount()];
//	for(size_t i = 0; i < GetCount(); i++)
//		generators[i] = NewGenerator(i);
}

//GeneratorFactory::GeneratorFactory(const GeneratorFactory& other)
//{
//	printf(__FILE__ ": Copy constructor called.");
//	generators = new Generator*[GetCount()];
//	for(size_t i = 0; i < GetCount(); i++)
//		generators[i] = NewGenerator(i);
//}

//wxString GeneratorFactory::GetName(size_t generatorNr) const
//{
//	if(generatorNr >= GetCount()) return _T("");
//	return generators[generatorNr]->GetName();
//}

GeneratorFactory::~GeneratorFactory()
{
//	for(size_t i = 0; i < GetCount(); i++)
//		delete generators[i];
//	delete[] generators;
}

