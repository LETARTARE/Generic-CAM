///////////////////////////////////////////////////////////////////////////////
// Name               : test.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)

//
// This program is not free software: you can not redistribute it
// and/or modify it under any terms.
//
// Nontheless this program is distributed in the hope that it will
// be useful to me, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.
//
// You should have not received a copy of any license along with
// this program.  So you are required to delete this file.
//
///////////////////////////////////////////////////////////////////////////////

#include "test.h"

#include <iostream>

#include "../Config.h"

#ifdef _USE_CPPUNIT

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

bool TestAll(void)
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry =
			CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	return runner.run();
}

#else
bool TestAll(void)
{
	std::cout << "Self-tests cannot be executed, because Generic-CAM has not been compiled with cppunit.\n";
	return false;
}
#endif
