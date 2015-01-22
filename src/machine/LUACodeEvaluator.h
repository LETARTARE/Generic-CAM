///////////////////////////////////////////////////////////////////////////////
// Name               : LUACodeEvaluator.h
// Purpose            : Wrapper for calling LUA
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -llua
// Author             : Tobias Schaefer
// Created            : 26.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

//TODO: On LUA 5.2 there is no lua_open() function. It has been replaced by luaL_newstate().
//TODO: This needs a copy constructor. It is in no way save to make a copy.

// The evaluation of the LUA code takes place in a
// seperate thread. This way, if the program hangs
// it can be killed by the main thread.

// If the thread hangs it will be simply killed.
// A more graceful exit would be to insert a hook-line
// see StopEvaluation();
// Still Calling Functions in a running Thread is not
// recommended and may not work everywhere. So we kill
// it. The lua_state may be Borscht afterwards. But in
// a joinable thread we still have the destructor.

// Things to keep in mind when trying to get it up and running on Windows:
// gcc -shared -o lua51.dll lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o
// strip --strip-unneeded lua51.dll
// gcc -o lua.exe -s lua.o lua51.dll -lm
// make[2]: Leaving directory `/d/home/lua-5.1.4/src'
// make "LUAC_T=luac.exe" luac.exe
// make[2]: Entering directory `/d/home/lua-5.1.4/src'
// gcc -O2 -Wall    -c -o luac.o luac.c
// gcc -O2 -Wall    -c -o print.o print.c
// ar rcu liblua.a lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o
// ranlib liblua.a
// gcc -o luac.exe  luac.o print.o liblua.a -lm

#ifndef LUACODEEVALUATOR_H_
#define LUACODEEVALUATOR_H_

#include "../StdInclude.h"
#include <wx/string.h>
#include <lua.hpp>
#include <list>
#include "MachineComponent.h"

#include "../3D/AffineTransformMatrix.h"

class Machine;

/*! \class LUACodeEvaluator
 * \brief Wrapper for calling LUA.
 *
 */
class LUACodeEvaluator {

	// Constructor / Destructor
public:
	LUACodeEvaluator();
	virtual ~LUACodeEvaluator();

	// Member Variables
protected:

	lua_State *L;
	wxString programOutput;

	Machine* linkedMachine;
	size_t componentToManipulate;
	AffineTransformMatrix matrix;

	// Methods
public:

	void LinkToProject(Machine* machine);
	void InsertVariable(wxString vName, float vValue);

	bool EvaluateProgram();
	bool EvaluateAssembly();

	void StopEvaluation();

	wxString GetOutput();

	static LUACodeEvaluator* FindCallingClass(lua_State * L);
	static void HookRoutine(lua_State * L, lua_Debug * ar);
	static int print_glue(lua_State * L);

	static int identity_glue(lua_State * L);

	static int box_glue(lua_State * L);
	static int cylinder_glue(lua_State * L);

	static int setstyle_glue(lua_State * L);

	static int toolholder_glue(lua_State * L);
	static int tableorigin_glue(lua_State * L);

	static int addcomponent_glue(lua_State * L);

	static int translate_glue(lua_State * L);
	static int rotate_glue(lua_State * L);
	static int placecomponent_glue(lua_State * L);

	static int loadstl_glue(lua_State * L);
};

//TODO: Find out if there is a better way to tell the static functions about the CallingClass.
static std::list <LUACodeEvaluator *> availableLUACodeEvaluators;
// This is better then "static void* CallingClass;"

#endif /* LUACODEEVALUATOR_H_ */
