///////////////////////////////////////////////////////////////////////////////
// Name               : LUACodeEvaluator.cpp
// Purpose            : Wrapper for calling LUA.
// Thread Safe        : Tricky...
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

#include "LUACodeEvaluator.h"
#include "../Config.h"
#include "Machine.h"
#include <wx/debug.h>
#include <wx/log.h>
#include <math.h>

LUACodeEvaluator::LUACodeEvaluator()
{
	linkedMachine = NULL;

	L = lua_open();

	availableLUACodeEvaluators.push_back(this);

	luaopen_base(L);
	luaopen_math(L);
	luaopen_table(L);
	luaopen_string(L);
	lua_register(L, "print", print_glue);

	lua_register(L, "identity", identity_glue);
	lua_register(L, "box", box_glue);
	lua_register(L, "cylinder", cylinder_glue);
	lua_register(L, "setstyle", setstyle_glue);
	lua_register(L, "addcomponent", addcomponent_glue);
	lua_register(L, "toolholder", toolholder_glue);
	lua_register(L, "tableorigin", tableorigin_glue);

	lua_register(L, "translate", translate_glue);
	lua_register(L, "rotate", rotate_glue);

	lua_register(L, "placecomponent", placecomponent_glue);

	lua_register(L, "loadstl", loadstl_glue);
}

LUACodeEvaluator::~LUACodeEvaluator()
{
	availableLUACodeEvaluators.remove(this);
	lua_close(L);
	L = NULL;
}

void LUACodeEvaluator::LinkToProject(Machine* machine)
{
	linkedMachine = machine;
}

void LUACodeEvaluator::InsertVariable(wxString vName, float vValue)
{
	wxASSERT(L!=NULL);
	lua_pushnumber(L, vValue);
	lua_setglobal(L, vName.ToAscii());
}

wxString LUACodeEvaluator::GetOutput()
{
	return programOutput;
}

bool LUACodeEvaluator::EvaluateProgram()
{
	if(linkedMachine == NULL) return false;
	int error = 0;

	linkedMachine->ClearComponents();

	//	wxLogMessage(wxString::Format(_T("Blip: %u"),linkedMachine->components.Count()));
	//		return NULL;

	componentToManipulate = 0;

	programOutput.Empty();

	matrix.SetIdentity();

	error = luaL_loadstring(L, linkedMachine->machineDescription.ToAscii());
	if(error){
		programOutput += _("\n---------- error while parsing ----------\n");
		programOutput += wxString::FromAscii(lua_tostring(L, -1));
		return false;
	}else{
		error = lua_pcall(L, 0, 0, 0);
		if(error){
			programOutput += _("\n---------- error while running ----------\n");

			programOutput += wxString::FromAscii(lua_tostring(L, -1));
			return false;
		}
	}

	if(_DEBUGMODE){

		unsigned int i;
		for(i = 0; i < linkedMachine->components.Count(); i++){
			wxLogMessage(
					wxString::Format(_T("Component %u:"), i)
							+ linkedMachine->components[i].nameOfComponent);

		}

	}
	return true;

}

bool LUACodeEvaluator::EvaluateAssembly()
{
	if(linkedMachine == NULL) return false;
	int error;

	componentToManipulate = 0;

	programOutput.Empty();
	matrix.SetIdentity();

	InsertVariable(_T("AXIS_X"), linkedMachine->position.axisX);
	InsertVariable(_T("AXIS_Y"), linkedMachine->position.axisY);
	InsertVariable(_T("AXIS_Z"), linkedMachine->position.axisZ);
	InsertVariable(_T("AXIS_A"), linkedMachine->position.axisA);
	InsertVariable(_T("AXIS_B"), linkedMachine->position.axisB);
	InsertVariable(_T("AXIS_C"), linkedMachine->position.axisC);
	InsertVariable(_T("AXIS_U"), linkedMachine->position.axisU);
	InsertVariable(_T("AXIS_V"), linkedMachine->position.axisV);
	InsertVariable(_T("AXIS_W"), linkedMachine->position.axisW);

	lua_getglobal(L, "AssembleMachine");

	error = lua_pcall(L, 0, 0, 0);
	if(error){
		programOutput += _("\n---------- error while running ----------\n");

		programOutput += wxString::FromAscii(lua_tostring(L, -1));
		return false;
	}
	return true;

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
	for(p = availableLUACodeEvaluators.begin();
			p != availableLUACodeEvaluators.end(); ++p){
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

int LUACodeEvaluator::addcomponent_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 1){
		lua_pushstring(L, "addcomponent: parameter mismatch");
		lua_error(L);
		return 0;
	}
	// Generate a new part for the machine.
	int n = lua_gettop(L); /* number of arguments */
	if(n != 1) return luaL_error(L, "addcomponent needs exactly one string");

	lua_getglobal(L, "tostring");
	const char *s;
	lua_pushvalue(L, -1); /* function to be called */
	lua_pushvalue(L, 1); /* value to print */
	lua_call(L, 1, 1);
	s = lua_tostring(L, -1); /* get result */
	if(s == NULL) return luaL_error(L,
	LUA_QL("tostring") " must return a string to " LUA_QL("print"));

	if(!CC->linkedMachine->AddComponent(wxString::FromAscii(s))){
		return luaL_error(L, "addcomponent: part already exists!");
	}
	CC->componentToManipulate = CC->linkedMachine->components.GetCount() - 1;
	CC->matrix.SetIdentity();
	return 0;
}
int LUACodeEvaluator::identity_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 0){
		lua_pushstring(L, "identity: parameter mismatch");
		lua_error(L);
		return 0;
	}
	CC->matrix.SetIdentity();
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

	CC->matrix.TranslateLocal(x, y, z);
	return 0;
}
int LUACodeEvaluator::rotate_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	float x, y, z, tx, ty, tz;
	switch(lua_gettop(L)){
	case 3:
		x = luaL_checknumber(L, 1) / 180 * M_PI;
		y = luaL_checknumber(L, 2) / 180 * M_PI;
		z = luaL_checknumber(L, 3) / 180 * M_PI;
		CC->matrix = CC->matrix * AffineTransformMatrix::RotateXYZ(x, y, z);
		break;
	case 6:
		x = luaL_checknumber(L, 1) / 180 * M_PI;
		y = luaL_checknumber(L, 2) / 180 * M_PI;
		z = luaL_checknumber(L, 3) / 180 * M_PI;
		tx = luaL_checknumber(L, 4);
		ty = luaL_checknumber(L, 5);
		tz = luaL_checknumber(L, 6);
		CC->matrix.TranslateLocal(tx, ty, tz);
		CC->matrix = CC->matrix * AffineTransformMatrix::RotateXYZ(x, y, z);
		CC->matrix.TranslateLocal(-tx, -ty, -tz);
		break;
	default:
		lua_pushstring(L,
				"rotate: parameter mismatch (3 or 6 parameters expected!).");
		lua_error(L);
		break;
	}
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

	CC->linkedMachine->components[CC->componentToManipulate].InsertBox(
			CC->matrix, x, y, z);
	return 0;
}
int LUACodeEvaluator::cylinder_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);

	float h, r1, r2;
	switch(lua_gettop(L)){
	case 2:
		h = luaL_checknumber(L, 1);
		r1 = luaL_checknumber(L, 2);
		CC->linkedMachine->components[CC->componentToManipulate].InsertCylinder(
				CC->matrix, h, r1);

		break;
	case 3:
		h = luaL_checknumber(L, 1);
		r1 = luaL_checknumber(L, 2);
		r2 = luaL_checknumber(L, 3);
		CC->linkedMachine->components[CC->componentToManipulate].InsertCone(
				CC->matrix, h, r1, r2);
		break;
	default:
		lua_pushstring(L, "cylinder: parameter mismatch");
		lua_error(L);
		break;
	}
	return 0;
}

int LUACodeEvaluator::setstyle_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);

	if(lua_gettop(L) != 3){
		lua_pushstring(L, "setstyle: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float r = luaL_checknumber(L, 1);
	float g = luaL_checknumber(L, 2);
	float b = luaL_checknumber(L, 3);
	CC->linkedMachine->components[CC->componentToManipulate].SetColor(r, g, b);
	return 0;
}

int LUACodeEvaluator::toolholder_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 0){
		lua_pushstring(L, "identity: parameter mismatch");
		lua_error(L);
		return 0;
	}
	CC->linkedMachine->toolPositionRelativ.Set(CC->matrix);
	CC->linkedMachine->toolPosition.Set(CC->matrix);
	CC->linkedMachine->componentWithTool =
			CC->linkedMachine->components.GetCount() - 1;
	return 0;
}
int LUACodeEvaluator::tableorigin_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 0){
		lua_pushstring(L, "identity: parameter mismatch");
		lua_error(L);
		return 0;
	}
	CC->linkedMachine->workpiecePositionRelativ.Set(CC->matrix);
	CC->linkedMachine->workpiecePosition.Set(CC->matrix);
	CC->linkedMachine->componentWithMaterial =
			CC->linkedMachine->components.Count() - 1;
	return 0;
}
int LUACodeEvaluator::placecomponent_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 1){
		lua_pushstring(L, "placecomponent: parameter mismatch");
		lua_error(L);
		return 0;
	}
	// Generate a new part for the machine.
	int n = lua_gettop(L); /* number of arguments */
	if(n != 1) return luaL_error(L, "placecomponent needs exactly one string");

	lua_getglobal(L, "tostring");
	const char *s;
	lua_pushvalue(L, -1); /* function to be called */
	lua_pushvalue(L, 1); /* value to print */
	lua_call(L, 1, 1);
	s = lua_tostring(L, -1); /* get result */
	if(s == NULL) return luaL_error(L,
	LUA_QL("tostring") " must return a string to " LUA_QL("print"));

	if(!CC->linkedMachine->PlaceComponent(wxString::FromAscii(s), CC->matrix)){
		return luaL_error(L, "placecomponent: part does not exist!");
	}
	return 0;
}

int LUACodeEvaluator::loadstl_glue(lua_State * L)
{
	LUACodeEvaluator* CC = LUACodeEvaluator::FindCallingClass(L);
	wxASSERT(CC==NULL);
	if(lua_gettop(L) != 1){
		lua_pushstring(L, "loadstl: parameter mismatch");
		lua_error(L);
		return 0;
	}
	// Generate a new part for the machine.
	int n = lua_gettop(L); /* number of arguments */
	if(n != 1) return luaL_error(L, "loadstl needs exactly one string");

	lua_getglobal(L, "tostring");
	const char *s;
	lua_pushvalue(L, -1); /* function to be called */
	lua_pushvalue(L, 1); /* value to print */
	lua_call(L, 1, 1);
	s = lua_tostring(L, -1); /* get result */
	if(s == NULL) return luaL_error(L,
	LUA_QL("tostring") " must return a string to " LUA_QL("print"));

	wxFileName machinedirectory(CC->linkedMachine->fileName);
	wxFileName fileName(wxString::FromAscii(s));
	machinedirectory.Normalize();
	fileName.Normalize(
			wxPATH_NORM_DOTS | wxPATH_NORM_ENV_VARS | wxPATH_NORM_TILDE);

	fileName.SetPath(machinedirectory.GetPathWithSep() + fileName.GetPath());

	wxLogMessage(_T("machineDirectory:") + machinedirectory.GetPath());
	wxLogMessage(_T("fileNameDirectory:") + fileName.GetPath());

	if(!fileName.IsOk()){
		CC->programOutput += fileName.GetFullPath();
		return luaL_error(L, "File does not exist!");
	}

	CC->linkedMachine->components[CC->componentToManipulate].InsertSTL(
			CC->matrix, fileName);
	return 0;
}
