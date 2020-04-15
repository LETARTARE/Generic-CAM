///////////////////////////////////////////////////////////////////////////////
// Name               : TestSelection.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.12.2019
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

#include "TestSelection.h"
#ifdef _USE_CPPUNIT

#include "../project/Selection.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestSelection);

// Set protection macro
#define SET(...) __VA_ARGS__
// Set compare macro
#define ASSERT_SET(x, expectedsize, expected)                    \
		{CPPUNIT_ASSERT_EQUAL( x.Size(), (size_t)expectedsize ); \
        std::set <size_t> s = x.GetSet();                        \
        size_t y[expectedsize] = expected ;                      \
        CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),y));}

void TestSelection::testCreation()
{
	Selection all(true);
	Selection nothing(false);

	CPPUNIT_ASSERT_EQUAL(true, all.IsSetEmpty());
	CPPUNIT_ASSERT_EQUAL(true, all.IsInverted());
	CPPUNIT_ASSERT_EQUAL(true, nothing.IsSetEmpty());
	CPPUNIT_ASSERT_EQUAL(false, nothing.IsInverted());

	Selection a(Selection::BaseAnything, 12, Selection::Anything, 34);
	CPPUNIT_ASSERT_EQUAL((size_t )1, a.Size());
	CPPUNIT_ASSERT_EQUAL((size_t )34, a[0]);
	CPPUNIT_ASSERT_EQUAL((size_t )0, a.GetBaseID());

	Selection b(a);
	CPPUNIT_ASSERT_EQUAL((size_t )1, b.Size());
	b.Set(Selection::BaseAnything, 12);
	CPPUNIT_ASSERT_EQUAL((size_t )1, b.Size());
	b.Set(Selection::BaseAnything, 123);
	CPPUNIT_ASSERT_EQUAL((size_t )1, b.Size());
	b.Add(100);
	CPPUNIT_ASSERT_EQUAL((size_t )2, b.Size());
	b.Set(Selection::BaseRun, 123);
	CPPUNIT_ASSERT_EQUAL((size_t )2, b.Size());
	CPPUNIT_ASSERT_EQUAL((size_t )123, b.GetBaseID());

	Selection c = a;
	c.Set(Selection::Axis);
	c.ClearSet();
	CPPUNIT_ASSERT_EQUAL((size_t )0, c.Size());
	CPPUNIT_ASSERT_EQUAL((size_t )0, c.GetBaseID());

	Selection d(Selection::BaseObject);
	CPPUNIT_ASSERT_EQUAL((size_t )0, d.Size());
	CPPUNIT_ASSERT_EQUAL((size_t )0, d.GetBaseID());
}

void TestSelection::testBaseTests()
{
	Selection a(Selection::BaseAnything, 1);
	CPPUNIT_ASSERT_EQUAL((size_t )0, a.GetBaseID());

	a.Set(Selection::BaseObject, 100);
	CPPUNIT_ASSERT(a.IsBaseType(Selection::BaseObject));
	CPPUNIT_ASSERT(a.IsBase(Selection::BaseObject, 100));

	Selection b(Selection::BaseAnything, 100);
	CPPUNIT_ASSERT(!b.IsBase(Selection::BaseObject, 100));
	CPPUNIT_ASSERT(b.IsBase(Selection::BaseAnything, 200));
}

void TestSelection::testTests()
{

	Selection a(Selection::BaseAnything, 0, Selection::Anything, 0);
	CPPUNIT_ASSERT(a.IsBaseType(Selection::BaseAnything));
	CPPUNIT_ASSERT(a.IsBase(Selection::BaseAnything, 100));
	CPPUNIT_ASSERT(a.GetBaseID() == 0);

}

void TestSelection::testCompares()
{
	Selection a(Selection::BaseAnything, 0, Selection::Anything, 0);
	Selection b(Selection::BaseAnything, 0, Selection::Object, 10);

	CPPUNIT_ASSERT(a.CanAdd(b));

	Selection c;
	c.Add(Selection::Object, 10);
	CPPUNIT_ASSERT(a != c);
	CPPUNIT_ASSERT(b == c);
}

void TestSelection::testAdd()
{
	Selection a(Selection::BaseAnything, 0, Selection::Object, 7);
	a.Add(9);
	a.Add(7);
	a.Invert();
	a.Add(7);
	a.Invert();

	ASSERT_SET(a, 1, SET({9}))
}

void TestSelection::testDelete()
{
	Selection a(Selection::BaseAnything, 0, Selection::Object, 7);
	a.Add(9);
	a.Add(5);
	ASSERT_SET(a, 3, SET({5, 7, 9}))

	a.Invert();
	a.Add(9);
	ASSERT_SET(a, 2, SET({5, 7}))
}

void TestSelection::testSetOperations()
{
	Selection a(Selection::BaseAnything, 4321, Selection::Object);
	a.Add(13);
	a.Add(17);

	Selection b(Selection::BaseAnything, 6543, Selection::Object);
	b.Add(19);
	b.Add(17);

	CPPUNIT_ASSERT_EQUAL((size_t ) 2, a.Size());
	CPPUNIT_ASSERT_EQUAL((size_t ) 2, b.Size());

	{
		Selection c = a + b;
		ASSERT_SET(c, 3, SET({13, 17, 19}))
	}
	{
		Selection c = a | b;
		ASSERT_SET(c, 3, SET({13, 17, 19}))
	}
	{
		Selection c = a - b;
		ASSERT_SET(c, 1, SET({13}))
	}
	{
		Selection c = a & b;
		ASSERT_SET(c, 1, SET({17}))
	}
}

#endif
