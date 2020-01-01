///////////////////////////////////////////////////////////////////////////////
// Name               : Selection.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.11.2019
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

#include "Selection.h"

#include <algorithm>
#include <iterator>
#include <sstream>

Selection::Selection(bool selecteverything)
{
	basetype = BaseNone;
	baseID = 0;
	type = Anything;
	inverted = selecteverything;

	lastrequestvalid = false;
	lastrequestediterator = selected.begin();
	lastrequestedindex = 0;
}

Selection::Selection(Type type)
{
	this->basetype = BaseNone;
	this->baseID = 0;
	this->type = type;
	inverted = false;

	lastrequestvalid = false;
	lastrequestediterator = selected.begin();
	lastrequestedindex = 0;
}

Selection::Selection(Type type, size_t ID)
{
	this->basetype = BaseNone;
	this->baseID = 0;
	this->type = type;
	selected.insert(ID);
	inverted = false;

	lastrequestvalid = false;
	lastrequestediterator = selected.begin();
	lastrequestedindex = 0;
}

Selection::Selection(BaseType basetype, size_t baseID, Type type)
{
	this->basetype = basetype;
	if(basetype == BaseNone) baseID = 0;
	this->baseID = baseID;
	this->type = type;
	inverted = false;

	lastrequestvalid = false;
	lastrequestediterator = selected.begin();
	lastrequestedindex = 0;
}

Selection::Selection(BaseType basetype, size_t baseID, Type type, size_t ID)
{
	this->basetype = basetype;
	if(basetype == BaseNone) baseID = 0;
	this->baseID = baseID;
	this->type = type;
	selected.insert(ID);
	inverted = false;

	lastrequestvalid = false;
	lastrequestediterator = selected.begin();
	lastrequestedindex = 0;
}

Selection::~Selection()
{
}

void Selection::Clear(void)
{
	basetype = BaseNone;
	baseID = 0;
	type = Anything;
	inverted = false;
	selected.clear();
	lastrequestvalid = false;
}

void Selection::ClearKeepBase(void)
{
	selected.clear();
	lastrequestvalid = false;

	inverted = false;
}

void Selection::ClearSetBase(BaseType basetype, size_t baseID)
{
	this->basetype = basetype;
	if(basetype == BaseNone) baseID = 0;
	this->baseID = baseID;
	this->type = type;
	inverted = false;

	selected.clear();
	lastrequestvalid = false;
}

void Selection::SetBase(BaseType basetype, size_t baseID)
{
	if(basetype == BaseNone) baseID = 0;
	lastrequestvalid = false;
	this->basetype = basetype;
	this->baseID = baseID;
}

size_t Selection::GetBaseID(void) const
{
	return baseID;
}

bool Selection::IsBase(BaseType basetype, size_t baseID) const
{
	return (this->basetype == basetype
			&& (this->basetype == BaseNone || this->baseID == baseID));
}

bool Selection::IsBaseType(BaseType basetype) const
{
	return (this->basetype == basetype);
}

std::string Selection::GetBaseTypeName(BaseType basetype)
{
	switch(basetype){
	case BaseNone:
		return std::string("None");
	case BaseObject:
		return std::string("Object");
	case BaseRun:
		return std::string("Run");
	}
	return std::string("-");
}

std::string Selection::GetBaseTypeName(void) const
{
	return Selection::GetBaseTypeName(this->basetype);
}

size_t Selection::Size(void) const
{
	return selected.size();
}

bool Selection::IsSetEmpty(void) const
{
	return selected.empty();
}

const std::set <size_t> & Selection::GetSet(void) const
{
	return selected;
}

const std::set <size_t>::iterator Selection::begin(void) const
{
	return selected.begin();
}

const std::set <size_t>::iterator Selection::end(void) const
{
	return selected.end();
}

size_t Selection::operator [](size_t index) const
{
	const size_t N = selected.size();
	if(index > N) throw std::range_error(
			"Selection::operator[] - out of range.");
	if(!lastrequestvalid || lastrequestedindex > index){
		lastrequestediterator = selected.begin();
		lastrequestedindex = 0;
		lastrequestvalid = true;
	}
	while(lastrequestedindex < index){
		++lastrequestediterator;
		++lastrequestedindex;
	}
	return *lastrequestediterator;
}

void Selection::Invert(void)
{
	inverted = !inverted;
//	lastrequestvalid = false;
}

const bool Selection::IsInverted(void) const
{
	return inverted;
}

void Selection::SetType(Type type)
{
	if(this->type != type){
		selected.clear();
		lastrequestvalid = false;
		inverted = false;
	}
	this->type = type;
}

bool Selection::IsType(Type type) const
{
	return (type == this->type);
}

std::string Selection::GetTypeName(Type type)
{
	switch(type){
	case Anything:
		return std::string("Anything");
	case Axis:
		return std::string("Axis");
	case Object:
		return std::string("Object");
	case Triangle:
		return std::string("Triangle");
	case TriangleGroup:
		return std::string("TriangleGroup");
	case Edge:
		return std::string("Edge");
	case EdgeGroup:
		return std::string("EdgeGroup");
	case Vertex:
		return std::string("Vertex");
	case VertexGroup:
		return std::string("VertexGroup");
	case Run:
		return std::string("Run");
	case Generator:
		return std::string("Generator");
	}
	return std::string("-");
}

std::string Selection::GetTypeName(void) const
{
	return Selection::GetTypeName(this->type);
}

bool Selection::CanAdd(BaseType basetype) const
{
	return (this->basetype == BaseNone || this->basetype == basetype);
}

bool Selection::CanAdd(BaseType basetype, Type type) const
{
	return ((this->basetype == BaseNone || this->basetype == basetype)
			&& (this->type == Anything || this->type == type));
}

bool Selection::CanAdd(BaseType basetype, size_t baseID) const
{
	return ((this->basetype == BaseNone || this->basetype == basetype)
			&& (this->basetype == BaseNone || this->baseID == baseID));
}

bool Selection::CanAdd(BaseType basetype, size_t baseID, Type type) const
{
	return ((this->basetype == BaseNone || this->basetype == basetype)
			&& (this->basetype == BaseNone || this->baseID == baseID)
			&& (this->type == Anything || this->type == type));
}

bool Selection::CanAdd(Type type) const
{
	return (this->type == Anything || this->type == type);
}

bool Selection::CanAdd(const Selection& other) const
{
	return ((this->basetype == BaseNone || this->basetype == other.basetype)
			&& (this->basetype == BaseNone || this->baseID == other.baseID)
			&& (this->type == Anything || this->type == other.type)
			&& (this->type == Anything || this->type == other.type));
	//TODO: Check if it is a good idea to allow other.type==Anything here as well.
}

bool Selection::Add(size_t ID)
{
	if(inverted){
		selected.erase(ID);
	}else{
		selected.insert(ID);
	}
	lastrequestvalid = false;
	return true;
}

bool Selection::Add(Type type, size_t ID)
{
	if(this->type == Anything) this->type = type;
	if(this->type != Anything && this->type != type) return false;
	if(inverted){
		selected.erase(ID);
	}else{
		selected.insert(ID);
	}
	lastrequestvalid = false;
	return true;
}

bool Selection::Add(BaseType basetype, Type type, size_t ID)
{
	if(this->basetype == BaseNone){
		this->basetype = basetype;
		if(basetype == BaseNone) this->baseID = 0;
	}
	if(this->basetype != BaseNone && this->basetype != basetype) return false;
	if(this->type == Anything) this->type = type;
	if(this->type != Anything && this->type != type) return false;
	if(inverted){
		selected.erase(ID);
	}else{
		selected.insert(ID);
	}
	lastrequestvalid = false;
	return true;
}

bool Selection::Add(BaseType basetype, size_t baseID, Type type, size_t ID)
{
	if(this->basetype == BaseNone){
		this->basetype = basetype;
		this->baseID = (basetype == BaseNone)? 0 : baseID;
	}
	if(this->basetype != BaseNone && this->basetype != basetype) return false;
	if(this->basetype != BaseNone && this->baseID != baseID) return false;
	if(this->type == Anything) this->type = type;
	if(this->type != Anything && this->type != type) return false;
	if(inverted){
		selected.erase(ID);
	}else{
		selected.insert(ID);
	}
	lastrequestvalid = false;
	return true;
}

bool Selection::Add(const Selection& other)
{
	if(this->basetype == BaseNone){
		this->basetype = other.basetype;
		this->baseID = (other.basetype == BaseNone)? 0 : other.baseID;
	}
	if(this->basetype != BaseNone && this->basetype != other.basetype) return false;
	if(this->basetype != BaseNone && this->baseID != other.baseID) return false;
	if(this->type == Anything) this->type = other.type;
	if(this->type != Anything && this->type != other.type) return false;
	std::set <size_t> temp;
	if(this->inverted){
		std::set_difference(this->selected.begin(), this->selected.end(),
				other.selected.begin(), other.selected.end(),
				std::inserter(temp, temp.begin()));
	}else{
		std::set_union(this->selected.begin(), this->selected.end(),
				other.selected.begin(), other.selected.end(),
				std::inserter(temp, temp.begin()));
	}
	this->selected = temp;
	lastrequestvalid = false;
	return true;
}

bool Selection::Has(size_t ID) const
{
	return ((selected.find(ID) != selected.end()) != inverted);
}

bool Selection::Has(Type type, size_t ID) const
{
	if(this->type != Anything && this->type != type) return inverted;
	return ((selected.find(ID) != selected.end()) != inverted);
}

bool Selection::Has(BaseType basetype, Type type, size_t ID) const
{
	if(this->basetype != BaseNone && this->basetype != basetype) return inverted;
	if(this->type != Anything && this->type != type) return inverted;
	return ((selected.find(ID) != selected.end()) != inverted);
}

bool Selection::Has(BaseType basetype, size_t baseID, Type type,
		size_t ID) const
{
	if(this->basetype != BaseNone && this->basetype != basetype) return inverted;
	if(this->basetype != BaseNone && this->baseID != baseID) return inverted;
	if(this->type != type) return inverted;
	return ((selected.find(ID) != selected.end()) != inverted);
}

Selection& Selection::operator |=(const Selection& b)
{
	// Compare types
	if(this->basetype != b.basetype) return *this;
	lastrequestvalid = false;
	if(this->basetype != BaseNone && !this->selected.empty()
			&& this->baseID != b.baseID) return *this;
	if(this->basetype == BaseNone){
		this->baseID = 0;
	}else{
		this->baseID = b.baseID;
	}
	if((this->type == Anything || this->selected.empty())
			&& !b.selected.empty()){
		this->type = b.type;
	}
	if(this->selected.empty()){
		if(!b.selected.empty()) this->selected = b.selected;
		return *this;
	}
	if(this->type != b.type) return *this;
	// Union
	if(b.selected.empty()) return *this;
	std::set <size_t> temp;
	std::set_union(this->selected.begin(), this->selected.end(),
			b.selected.begin(), b.selected.end(),
			std::inserter(temp, temp.begin()));
	this->selected = temp;
	return *this;
}

Selection& Selection::operator +=(const Selection& b)
{
	// Compare types
	if(this->basetype != b.basetype) return *this;
	if(this->basetype != BaseNone && !this->selected.empty()
			&& this->baseID != b.baseID) return *this;
	if(this->basetype == BaseNone){
		this->baseID = 0;
	}else{
		this->baseID = b.baseID;
	}
	if((this->type == Anything || this->selected.empty())
			&& !b.selected.empty()){
		this->type = b.type;
	}
	lastrequestvalid = false;
	if(this->selected.empty()){
		if(!b.selected.empty()) this->selected = b.selected;
		return *this;
	}
	if(this->type != b.type) return *this;
	// Union
	if(b.selected.empty()) return *this;
	std::set <size_t> temp;
	std::set_union(this->selected.begin(), this->selected.end(),
			b.selected.begin(), b.selected.end(),
			std::inserter(temp, temp.begin()));
	this->selected = temp;
	return *this;
}

Selection& Selection::operator &=(const Selection& b)
{
	lastrequestvalid = false;
	// Compare types
	if(this->basetype != b.basetype){
		selected.clear();
		return *this;
	}
	if(this->basetype != BaseNone && !this->selected.empty()
			&& this->baseID != b.baseID){
		selected.clear();
		return *this;
	}
	if(this->basetype == BaseNone){
		this->baseID = 0;
	}else{
		this->baseID = b.baseID;
	}
	if(this->type == Anything) this->type = b.type;
	if(this->selected.empty() || b.selected.empty() || this->type != b.type){
		selected.clear();
		return *this;
	}
	std::set <size_t> temp;
	std::set_intersection(this->selected.begin(), this->selected.end(),
			b.selected.begin(), b.selected.end(),
			std::inserter(temp, temp.begin()));
	this->selected = temp;
	return *this;
}

Selection& Selection::operator -=(const Selection& b)
{
// Compare types
	if(this->basetype != b.basetype) return *this;
	lastrequestvalid = false;
	if(this->basetype != BaseNone && !this->selected.empty()
			&& this->baseID != b.baseID) return *this;
	if(this->basetype == BaseNone){
		this->baseID = 0;
	}else{
		this->baseID = b.baseID;
	}
	if((this->type == Anything || this->selected.empty())
			&& !b.selected.empty()){
		this->type = b.type;
	}
	if(this->selected.empty()){
		if(!b.selected.empty()) this->selected = b.selected;
		return *this;
	}
	if(this->type != b.type) return *this;
// Difference
	if(b.selected.empty()) return *this;
	std::set <size_t> temp;
	std::set_difference(this->selected.begin(), this->selected.end(),
			b.selected.begin(), b.selected.end(),
			std::inserter(temp, temp.begin()));
	this->selected = temp;
	return *this;
}

Selection::Type Selection::GetType(void) const
{
	return type;
}

std::string Selection::ToString(void) const
{
	std::ostringstream x;

	if(basetype == BaseNone && type == Anything){
		if(inverted){
			x << "Everything";
		}else{
			x << "Nothing";
		}
	}else{
		if(inverted) x << "inv(";
		if(basetype != BaseNone){
			x << GetBaseTypeName();
			if(basetype != BaseNone){
				x << "#" << baseID;
			}
			x << ":";
		}
		x << GetTypeName();
		if(selected.size() > 0) x << "#";
		if(selected.size() > 1) x << "[";
		size_t c = 0;
		for(std::set <size_t>::iterator it = this->selected.begin();
				it != this->selected.end(); ++it){
			if(c > 0) x << ",";
			x << *it;
			++c;
			if(c >= 10){
				x << ",...";
				break;
			}
		}
		if(selected.size() > 1) x << "]";
		if(inverted) x << ")";
	}
	return x.str();
}
