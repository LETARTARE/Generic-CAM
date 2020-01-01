///////////////////////////////////////////////////////////////////////////////
// Name               : CollectionPostProcessor.h
// Purpose            : Abstract Base Postprocessor
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CollectionPostProcessor.h"

#include "GenericPostProcessor.h"

CollectionPostProcessor::CollectionPostProcessor()
{
	Refresh();
}

CollectionPostProcessor::~CollectionPostProcessor()
{
	for(std::vector <PostProcessor *>::iterator it = pp.begin(); it != pp.end();
			++it){
		delete (*it);
	}
}

void CollectionPostProcessor::Refresh(void)
{
	for(std::vector <PostProcessor *>::iterator it = pp.begin(); it != pp.end();
			++it)
		delete (*it);
	pp.clear();

	PostProcessor* temp;
	temp = new GenericPostProcessor("Generic 3-axis");
	temp->SetParameter("configuration", "XYZ");
	pp.push_back(temp);

	temp = new GenericPostProcessor("Generic 4-axis");
	temp->SetParameter("configuration", "XYZA~X");
	pp.push_back(temp);

	temp = new GenericPostProcessor("Generic 5-axis");
	temp->SetParameter("configuration", "XYZA~XB~Y");
	pp.push_back(temp);

	temp = new GenericPostProcessor("WinPC-NC");
	temp->SetParameter("configuration", "XY-Z");
	pp.push_back(temp);

}
std::vector <std::string> CollectionPostProcessor::GetNames(void) const
{
	std::vector <std::string> temp;
	for(std::vector <PostProcessor *>::const_iterator it = pp.begin();
			it != pp.end(); ++it){
		temp.push_back((*it)->GetName());
	}
	return temp;
}

size_t CollectionPostProcessor::Size(void) const
{
	return pp.size();
}
PostProcessor& CollectionPostProcessor::operator [](size_t index)
{
	if(index >= pp.size()) throw(std::range_error(
			"CollectionPostProcessor::operator[] - Index out of range."));
	return *(pp.at(index));
}
