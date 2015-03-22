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
#include <typeinfo>

#include "../generator/GeneratorNone.h"
#include "../generator/GeneratorPositioningDrills.h"
#include "../generator/GeneratorLoadFromFile.h"
#include "../generator/GeneratorAreaGridDexel.h"
#include "../generator/GeneratorFast.h"
#include "../generator/GeneratorTest.h"

#define N_GENERATORS 		5

Generator* GeneratorCollection::NewGenerator(int generatorNr, Project * project,
		size_t runNr, size_t toolpathNr)
{
	assert(generatorNr < GetCount());
	switch(generatorNr){
	case 0:
		return new GeneratorNone(project, runNr, toolpathNr);
		break;
	case 1:
		return new GeneratorPositioningDrills(project, runNr, toolpathNr);
		break;
	case 2:
		return new GeneratorLoadFromFile(project, runNr, toolpathNr);
		break;
//	case 3:
//		return new GeneratorAreaGridDexel(project, runNr, toolpathNr);
//		break;
	case 3:
		return new GeneratorFast(project, runNr, toolpathNr);
		break;
	case 4:
		return new GeneratorTest(project, runNr, toolpathNr);
		break;
	}
	return NULL;
}

size_t GeneratorCollection::GetCount()
{
	return N_GENERATORS;
}

int GeneratorCollection::FindGenerator(Generator* generator) const
{
	assert(generator !=NULL);
	for(int n = 0; n < GetCount(); n++)
		if(typeid(*(generator)) == typeid(*(generators[n]))) return n;
	return -1;
}
int GeneratorCollection::FindGenerator(const wxString& name) const
{
	for(int n = 0; n < GetCount(); n++)
		if(generators[n]->GetName().Cmp(name) == 0) return n;
	return -1;
}

GeneratorCollection::GeneratorCollection(const GeneratorCollection& other)
{
	Project * project = other.generators[0]->project;
	size_t i;
	generators = new Generator*[GetCount()];
	for(i = 0; i < GetCount(); i++)
		generators[i] = NewGenerator(i, project, 0, 0);
}
GeneratorCollection::GeneratorCollection()
{
// Create a list of all available generators
	size_t i;
	generators = new Generator*[GetCount()];
	for(i = 0; i < GetCount(); i++)
		generators[i] = NewGenerator(i, NULL, 0, 0);
}
GeneratorCollection::GeneratorCollection(Project* project)
{
	size_t i;
	generators = new Generator*[GetCount()];
	for(i = 0; i < GetCount(); i++)
		generators[i] = NewGenerator(i, project, 0, 0);
}

wxString GeneratorCollection::GetName(int generatorNr) const
{
	if(generatorNr < 0 || generatorNr >= GetCount()) return _T("");
	return generators[generatorNr]->GetName();
}

GeneratorCollection::~GeneratorCollection()
{
	int i;
	for(i = 0; i < GetCount(); i++)
		delete generators[i];
	delete[] generators;
}

