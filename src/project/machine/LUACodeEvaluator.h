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

#ifndef LUACODEEVALUATOR_H_
#define LUACODEEVALUATOR_H_

/*!\class LUACodeEvaluator
 * \ingroup Machine
 * \brief Wrapper for calling LUA.
 *
 * The evaluation of the LUA code takes place in a
 * separate thread. This way, if the program hangs
 * it can be killed by the main thread.
 *
 * If the thread hangs it will be simply killed.
 * A more graceful exit would be to insert a hook-line
 * see StopEvaluation();
 *
 * Still Calling Functions in a running Thread is not
 * recommended and may not work everywhere. So we kill
 * it. The lua_state may be Borscht afterwards. But in
 * a joinable thread we still have the destructor.
 *
 * Things to keep in mind when trying to get it up and running on Windows:
 * \code
 * gcc -shared -o lua51.dll lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o
 * strip --strip-unneeded lua51.dll
 * gcc -o lua.exe -s lua.o lua51.dll -lm
 * make[2]: Leaving directory `/d/home/lua-5.1.4/src'
 * make "LUAC_T=luac.exe" luac.exe
 * make[2]: Entering directory `/d/home/lua-5.1.4/src'
 * gcc -O2 -Wall    -c -o luac.o luac.c
 * gcc -O2 -Wall    -c -o print.o print.c
 * ar rcu liblua.a lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o
 * ranlib liblua.a
 * gcc -o luac.exe  luac.o print.o liblua.a -lm
 * \endcode
 */

#include "../../StdInclude.h"
#include "MachineComponent.h"
#include "../../3D/AffineTransformMatrix.h"
#include <wx/string.h>
#include <lua.hpp>
#include <list>

class Machine;

class LUACodeEvaluator {
public:
	LUACodeEvaluator();
	LUACodeEvaluator(const LUACodeEvaluator & other); //!< Copy constructor
	LUACodeEvaluator& operator=(const LUACodeEvaluator& other); ///< Assignment operator
	virtual ~LUACodeEvaluator();

	void LinkToMachine(Machine* machine);
	void InsertVariable(wxString vName, float vValue);

	bool EvaluateProgram();
	bool EvaluateAssembly();

	void StopEvaluation();

	wxString GetOutput();

	// Glue functions added to the LUA state
	static int print_glue(lua_State * L);

	static int identity_glue(lua_State * L);
	static int translate_glue(lua_State * L);
	static int rotate_glue(lua_State * L);
	static int scale_glue(lua_State * L);

	static int addcomponent_glue(lua_State * L);

	static int setstyle_glue(lua_State * L);

	static int box_glue(lua_State * L);
	static int cylinder_glue(lua_State * L);
	static int loadgeometry_glue(lua_State * L);

	static int tableorigin_glue(lua_State * L);
	static int toolholder_glue(lua_State * L);

	static int placecomponent_glue(lua_State * L);

private:
	/** \brief Find the caller for a lua_State
	 *
	 * Do a lookup of the caller by looking at the lua_state.
	 *
	 * @param L Pointer to LUA-State
	 * @return Pointer to LUACodeEvaluator
	 */
	static LUACodeEvaluator* FindCallingClass(lua_State * L);

	/**\brief The hook routine can be inserted to stop a script that got caught in an infinite loop.
	 *
	 * @param L Pointer to LUA-State
	 * @param ar
	 */
	static void HookRoutine(lua_State * L, lua_Debug * ar);

	void SetupState(void);

	// Member Variables
public:
	wxString programOutput;

protected:
	lua_State *L;
	Machine* linkedMachine;
	MachineComponent* componentToManipulate;
	AffineTransformMatrix matrix; //!< Used for chaining transformations in the machine description.
};

//TODO: Find out if there is a better way to tell the static functions about the CallingClass.
// This is better then "static void* CallingClass;"
static std::list <LUACodeEvaluator *> availableLUACodeEvaluators;

#endif /* LUACODEEVALUATOR_H_ */
