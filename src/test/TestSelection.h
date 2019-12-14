///////////////////////////////////////////////////////////////////////////////
// Name               : TestSelection.h
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

#ifndef SRC_TEST_TESTSELECTION_H_
#define SRC_TEST_TESTSELECTION_H_
#include "../Config.h"
#ifdef _USE_CPPUNIT

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestSelection:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE (TestSelection);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testBaseTests);
	CPPUNIT_TEST(testTests);
	CPPUNIT_TEST(testCompares);
	CPPUNIT_TEST(testAdd);
	CPPUNIT_TEST(testDelete);
	CPPUNIT_TEST(testSetOperations);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreation();
	void testBaseTests();
	void testTests();
	void testCompares();
	void testAdd();
	void testDelete();
	void testSetOperations();
};

#endif
#endif /* SRC_TEST_TESTSELECTION_H_ */
