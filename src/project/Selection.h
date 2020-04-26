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

#include "../math/JSON.h"

#include <cstddef>
#include <set>
#include <string>

class Selection {
public:
	//Note: BaseType and Type describing the same thing have to have the same ID.
	enum BaseType {
		BaseAnything = 0, BaseObject = 1, BaseRun = 2
	};
	enum Type {
		Anything = 0,
		Object = 1,
		Run = 2,
		Generator = 3,
		Triangle = 4,
		TriangleGroup = 5,
		Edge = 6,
		EdgeGroup = 7,
		Vertex = 8,
		VertexGroup = 9,
		Axis = 10
	};

private:
	BaseType basetype;
	size_t baseID;
	Type type;
	std::set <size_t> selected;
	bool invertedselection;

public:
	Selection(bool selecteverything = false);
	Selection(Type type);
	Selection(Type type, size_t ID);
	Selection(BaseType basetype, size_t baseID = 0, Type type = Anything);
	Selection(BaseType basetype, size_t baseID, Type type, size_t ID);
	Selection& operator=(const Selection& other);

	virtual ~Selection();

	void Set(Type type);
	void Set(Type type, size_t ID);
	void Set(BaseType basetype, size_t baseID = 0);
	void Set(BaseType basetype, size_t baseID, Type type);
	void Set(BaseType basetype, size_t baseID, Type type, size_t ID);

	void Reset(bool selecteverything = false);
	void ResetBase(void);

	bool IsBase(BaseType basetype, size_t baseID = 0) const;
	bool IsBaseType(BaseType basetype) const;
	size_t GetBaseID(void) const;
	static std::string GetBaseTypeName(BaseType basetype);
	std::string GetBaseTypeName(void) const;
	void ShiftUp(void);

	bool IsType(Type type) const;
	Selection::Type GetType(void) const;
	static std::string GetTypeName(Type type);
	std::string GetTypeName(void) const;

	void ClearSet(bool selecteverything = false);

	/*!\brief Check if something can be added to this class.
	 *
	 * Not that this is not bijective: The other Selection can be added to
	 * this one, if true is returned, but not necessariely the other way
	 * around.
	 */
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

	void Invert(void);
	const bool IsInverted(void) const;

	bool IsSetEmpty(void) const;
	size_t Size(void) const;
	const std::set <size_t> & GetSet(void) const;
	const std::set <size_t>::iterator begin(void) const;
	const std::set <size_t>::iterator end(void) const;
	size_t operator[](size_t index) const;

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
		// Base
		if(a.basetype != b.basetype) return false;
		if(a.basetype != BaseAnything && b.basetype != BaseAnything
				&& a.baseID != b.baseID) return false;
		// Type
		if(a.type != Anything && b.type != Anything && a.type != b.type) return false;
		// Selected
		if(a.invertedselection != b.invertedselection) return false;
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
	void ToJSON(JSON &js) const;
	bool FromJSON(const JSON &js);

private:
	// Speedup of index lookup with operator[]
	mutable bool lastrequestvalid;
	mutable std::set <size_t>::iterator lastrequestediterator;
	mutable size_t lastrequestedindex;
};

#endif /* SRC_PROJECT_SELECTION_H_ */
