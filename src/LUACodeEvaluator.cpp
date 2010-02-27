/*
 * ObjectEvaluator.cpp
 *
 *  Created on: 26.07.2009
 *      Author: toby
 */

#include "LUACodeEvaluator.h"
#include "Config.h"
#include <wx/debug.h>

LUACodeEvaluator::LUACodeEvaluator(wxThreadKind kind) :
	wxThread(kind)
{
	linkedMachine = NULL;

	L = lua_open();
	availableLUACodeEvaluators.push_back(this);

	luaopen_base(L);
	luaopen_math(L);
	luaopen_table(L);
	luaopen_string(L);
	lua_register(L,"print",print_glue);

	lua_register(L,"box",box_glue);
	lua_register(L,"cylinder",cylinder_glue);
	lua_register(L,"setstyle",setstyle_glue);
	lua_register(L,"partname",partname_glue);
	lua_register(L,"toolholder",toolholder_glue);
	lua_register(L,"tableorigin",tableorigin_glue);

	lua_register(L,"translate",translate_glue);
	lua_register(L,"rotate",rotate_glue);

	lua_register(L,"placepart",placepart_glue);

}

LUACodeEvaluator::~LUACodeEvaluator()
{
	availableLUACodeEvaluators.remove(this);
	lua_close(L);
	L = NULL;
}

void LUACodeEvaluator::LinkToMachine(Machine* machine)
{
	linkedMachine = machine;
	program = linkedMachine->machineDescription;
}

wxString LUACodeEvaluator::GetOutput()
{
	return programOutput;
}

void *LUACodeEvaluator::Entry()
{
	if(linkedMachine == NULL) return NULL;
	int error;
	linkedMachine->parts.Empty();

	programOutput.Empty();

	matrix.Identity();

	error = luaL_loadstring(L, program.ToAscii());
	if(error){
		programOutput += _("\n---------- error while parsing ----------\n");
		programOutput += wxString::FromAscii(lua_tostring(L, -1));
	}else{
		error = lua_pcall(L, 0, 0, 0);
		if(error){
			programOutput += _("\n---------- error while running ----------\n");

			programOutput += wxString::FromAscii(lua_tostring(L, -1));
		}
	}

	if(_DEBUGMODE){
		//		std::list <GeometryConnector>::iterator i;
		//		programOutput
		//				+= wxString::Format(
		//						_T("\r\n\r\nConnectors:\r\nname:\t(x,y,z)\t(nx,ny,nz)\r\n"));
		//		for(i = linkedGeometry->connector.begin(); i
		//				!= linkedGeometry->connector.end(); ++i){
		//			programOutput += i->connectorName + wxString::Format(
		//					_T(":\t(%f %f %f) (%f %f %f)\r\n"), i->p.x, i->p.y,
		//					i->p.z, i->n.x, i->n.y, i->n.z);
		//		}
	}

	return NULL;
}

void LUACodeEvaluator::StopEvaluation()
{
	if(L == NULL) return;
	lua_sethook(L, HookRoutine, LUA_MASKLINE, 0);
}

void LUACodeEvaluator::HookRoutine(lua_State * L, lua_Debug * ar)
{
	// Only listen to "Hook Lines" events
	if(ar->event == LUA_HOOKLINE){
		// Ok, let's abort the script
		lua_pushstring(L, "HookRoutine: abort requested!");
		lua_error(L);
	}
}

// The next function is megaugly!
LUACodeEvaluator* LUACodeEvaluator::FindCallingClass(lua_State * L)
{
	std::list <LUACodeEvaluator*>::iterator p;
	for(p = availableLUACodeEvaluators.begin(); p
			!= availableLUACodeEvaluators.end(); ++p){
		if((*p)->L == L) return *p;
	}
	return NULL;
}

// ++++++++++ Glue functions ++++++++++

int LUACodeEvaluator::print_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	//TODO: What if CC == NULL?
	wxASSERT(CC==NULL);

	int n = lua_gettop(L); /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for(i = 1; i <= n; i++){
		const char *s;
		lua_pushvalue(L, -1); /* function to be called */
		lua_pushvalue(L, i); /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1); /* get result */
		if(s == NULL) return luaL_error(L,
				LUA_QL("tostring") " must return a string to " LUA_QL("print"));
		if(i > 1) CC->programOutput += _T("\t");
		CC->programOutput += wxString::FromAscii(s);
		lua_pop(L, 1); /* pop result */
	}
	CC->programOutput += _T("\n");
	return 0;
}

int LUACodeEvaluator::partname_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 1){
		lua_pushstring(L, "partname: parameter mismatch");
		lua_error(L);
		return 0;
	}
	// Generate a new part for the machine.
	int n = lua_gettop(L); /* number of arguments */
	if(n != 1) return luaL_error(L, "partname needs exactly one string");

	lua_getglobal(L, "tostring");
	const char *s;
	lua_pushvalue(L, -1); /* function to be called */
	lua_pushvalue(L, 1); /* value to print */
	lua_call(L, 1, 1);
	s = lua_tostring(L, -1); /* get result */
	if(s == NULL) return luaL_error(L,
			LUA_QL("tostring") " must return a string to " LUA_QL("print"));

	if(!CC->linkedMachine->AddPart(wxString::FromAscii(s))){
		return luaL_error(L, "partname: part already exists!");
	}
	return 0;
}

int LUACodeEvaluator::translate_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 3){
		lua_pushstring(L, "translate: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float z = luaL_checknumber(L, 3);

	CC->matrix.TranslateByTrackball(x, y, z);
	return 0;
}
int LUACodeEvaluator::rotate_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 3){
		lua_pushstring(L, "rotate: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float z = luaL_checknumber(L, 3);
	CC->matrix.RotateByTrackball(x, y, z);
	return 0;
}

int LUACodeEvaluator::box_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 3){
		lua_pushstring(L, "box: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float z = luaL_checknumber(L, 3);

	CC->linkedMachine->partToManipulate->InsertBox(CC->matrix, x, y, z);
	return 0;
}
int LUACodeEvaluator::cylinder_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 2){
		lua_pushstring(L, "cylinder: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float h = luaL_checknumber(L, 1);
	float r = luaL_checknumber(L, 2);

	CC->linkedMachine->partToManipulate->InsertCylinder(CC->matrix, h, r);
	return 0;
}
int LUACodeEvaluator::setstyle_glue(lua_State * L)
{
	return 0;
}
int LUACodeEvaluator::toolholder_glue(lua_State * L)
{
	return 0;
}
int LUACodeEvaluator::tableorigin_glue(lua_State * L)
{
	return 0;
}
int LUACodeEvaluator::placepart_glue(lua_State * L)
{
	return 0;
}

