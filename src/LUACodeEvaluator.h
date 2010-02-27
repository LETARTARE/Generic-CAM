/*
 * LUACodeEvaluator.h
 *
 *  Created on: 26.07.2009
 *  Author: Tobias Schaefer
 *
 */

// The evaluation of the LUA code takes place in a
// seperate thread. This way, if the program hangs
// it can be killed by the main thread.

// If the thread hangs it will bes simply killed.
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

#include "StdInclude.h"
#include <wx/string.h>
#include <lua.hpp>
#include <list>
#include <wx/thread.h>
#include "Machine.h"
#include "AffineTransformMatrix.h"

class LUACodeEvaluator:public wxThread {


	// Constructor / Destructor
public:
	LUACodeEvaluator(wxThreadKind kind = wxTHREAD_JOINABLE);
	virtual ~LUACodeEvaluator();

	// Member Variables
public:
protected:

	lua_State *L;

	wxString program;
	wxString programOutput;

	Machine* linkedMachine;

	AffineTransformMatrix matrix;

	// Methods
public:

	void LinkToMachine(Machine* machine);

	virtual void* Entry();
	void StopEvaluation();
	wxString GetOutput();

	static LUACodeEvaluator* FindCallingClass(lua_State * L);
	static void HookRoutine(lua_State * L, lua_Debug * ar);
	static int print_glue(lua_State * L);

	static int box_glue(lua_State * L);
	static int cylinder_glue(lua_State * L);
	static int setstyle_glue(lua_State * L);
	static int partname_glue(lua_State * L);
	static int toolholder_glue(lua_State * L);
	static int tableorigin_glue(lua_State * L);

	static int translate_glue(lua_State * L);
	static int rotate_glue(lua_State * L);
	static int placepart_glue(lua_State * L);

};

//TODO: Find out if there is a better way to tell the static functions about the CallingClass.
static std::list <LUACodeEvaluator *> availableLUACodeEvaluators;
// This is better then "static void* CallingClass;"


#endif /* LUACODEEVALUATOR_H_ */
