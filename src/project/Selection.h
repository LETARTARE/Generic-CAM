///////////////////////////////////////////////////////////////////////////////
// Name               : Selection.h
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

#ifndef SRC_PROJECT_SELECTION_H_
#define SRC_PROJECT_SELECTION_H_

/*!\class Selection
 * \brief Stores a selection
 *
 */

#include <cstddef>
#include <set>
#include <string>

class Selection {
public:
	enum BaseType {
		BaseNone = 0, BaseObject, BaseRun
	};
	enum Type {
		Anything = 0,
		Object,
		Triangle,
		TriangleGroup,
		Edge,
		EdgeGroup,
		Vertex,
		VertexGroup,
		Axis,
		Run,
		Generator
	};

	Selection(bool selecteverything = false);
	Selection(Type type);
	Selection(Type type, size_t ID);
	Selection(BaseType basetype, size_t baseID = 0, Type type = Anything);
	Selection(BaseType basetype, size_t baseID, Type type, size_t ID);

	virtual ~Selection();

	void Clear(void);
	void ClearKeepBase(void);
	void ClearSetBase(BaseType basetype, size_t baseID = 0);

	void SetBase(BaseType basetype, size_t baseID = 0);
	size_t GetBaseID(void) const;
	bool IsBase(BaseType basetype, size_t baseID = 0) const;
	bool IsBaseType(BaseType basetype) const;
	static std::string GetBaseTypeName(BaseType basetype);
	std::string GetBaseTypeName(void) const;

	size_t Size(void) const;
	bool IsSetEmpty(void) const;
	const std::set <size_t> & GetSet(void) const;
	const std::set <size_t>::iterator begin(void) const;
	const std::set <size_t>::iterator end(void) const;
	size_t operator[](size_t index) const;

	void Invert(void);
	const bool IsInverted(void) const;

	void SetType(Type type);
	Selection::Type GetType(void) const;
	bool IsType(Type type) const;
	static std::string GetTypeName(Type type);
	std::string GetTypeName(void) const;

	bool CanAdd(BaseType basetype) const;
	bool CanAdd(BaseType basetype, Type type) const;
	bool CanAdd(BaseType basetype, size_t baseID) const;
	bool CanAdd(BaseType basetype, size_t baseID, Type type) const;
	bool CanAdd(Type type) const;
	bool CanAdd(const Selection &other) const;

	bool Add(size_t ID);
	bool Add(Type type, size_t ID);
	bool Add(BaseType basetype, Type type, size_t ID);
	bool Add(BaseType basetype, size_t baseID, Type type, size_t ID);
	bool Add(const Selection &other);

	bool Has(size_t ID) const;
	bool Has(Type type, size_t ID) const;
	bool Has(BaseType basetype, Type type, size_t ID) const;
	bool Has(BaseType basetype, size_t baseID, Type type, size_t ID) const;

	// https://en.cppreference.com/w/cpp/language/operators
	Selection& operator|=(const Selection& b); ///< Union
	Selection& operator+=(const Selection& b); ///< Union
	Selection& operator&=(const Selection& b); ///< Intersection
	Selection& operator-=(const Selection& b); ///< Difference
	friend Selection operator|(Selection a, const Selection& b)
	{
		a |= b;
		return a;
	}
	friend Selection operator+(Selection a, const Selection& b)
	{
		a += b;
		return a;
	}
	friend Selection operator&(Selection a, const Selection& b)
	{
		a &= b;
		return a;
	}
	friend Selection operator-(Selection a, const Selection& b)
	{
		a -= b;
		return a;
	}
	// To make this class usable as in std::set<Selection> it needs to be sortable.
	// The type of the selected entity is the sorting criterion.
	friend bool operator<(const Selection& a, const Selection& b)
	{
		return a.type < b.type;
	}
	friend bool operator==(const Selection& a, const Selection& b)
	{
		if(a.basetype != b.basetype) return false;
		if(a.basetype != BaseNone && a.baseID != b.baseID) return false;
		if(a.type != b.type) return false;
		if(a.inverted != b.inverted) return false;
		if(a.selected.size() != b.selected.size()) return false;
		if(!std::equal(a.selected.begin(), a.selected.end(),
				b.selected.begin())) return false;
		return true;
	}
	friend bool operator!=(const Selection& a, const Selection& b)
	{
		return !(a == b);
	}
	std::string ToString(void) const;

private:
	BaseType basetype;
	Type type;
	size_t baseID;
	std::set <size_t> selected;
	bool inverted;

	// Speedup of index lookup with operator[]
	mutable bool lastrequestvalid;
	mutable std::set <size_t>::iterator lastrequestediterator;
	mutable size_t lastrequestedindex;
};

#endif /* SRC_PROJECT_SELECTION_H_ */
