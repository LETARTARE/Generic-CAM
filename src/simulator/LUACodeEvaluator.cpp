/*
 * ObjectEvaluator.cpp
 *
 *  Created on: 26.07.2009
 *      Author: toby
 */

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
	lua_register(L,"print",print_glue);

	lua_register(L,"identity",identity_glue);
	lua_register(L,"box",box_glue);
	lua_register(L,"cylinder",cylinder_glue);
	lua_register(L,"setstyle",setstyle_glue);
	lua_register(L,"addcomponent",addcomponent_glue);
	lua_register(L,"toolholder",toolholder_glue);
	lua_register(L,"tableorigin",tableorigin_glue);

	lua_register(L,"translate",translate_glue);
	lua_register(L,"rotate",rotate_glue);

	lua_register(L,"placecomponent",placecomponent_glue);

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

void LUACodeEvaluator::EvaluateProgram()
{
	if(linkedMachine == NULL) return;
	int error;

	linkedMachine->ClearComponents();


	//	wxLogMessage(wxString::Format(_T("Blip: %u"),linkedMachine->components.Count()));
	//		return NULL;

	componentToManipulate = &(linkedMachine->components[0]);

	programOutput.Empty();

	matrix.SetIdentity();

	error = luaL_loadstring(L, linkedMachine->machineDescription.ToAscii());
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

		unsigned int i, j;
		for(i = 0; i < linkedMachine->components.Count(); i++){
			wxLogMessage(wxString::Format(_T("Component %u:"), i)
					+ linkedMachine->components[i].nameOfComponent);
			for(j = 0; j < linkedMachine->components[i].elements.Count(); j++){
				wxLogMessage(wxString::Format(_T("Element %u: %u"), j,
						linkedMachine->components[i].elements[j].typeOfElement));
			}

		}

	}

}

void LUACodeEvaluator::EvaluateAssembly()
{
	if(linkedMachine == NULL) return;
	int error;

	componentToManipulate = &(linkedMachine->components[0]);

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
	}

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
	CC->componentToManipulate
			= &(CC->linkedMachine->components[CC->linkedMachine->components.Count()
					- 1]);
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
	if(lua_gettop(L) != 3){
		lua_pushstring(L, "rotate: parameter mismatch");
		lua_error(L);
		return 0;
	}
	float x = luaL_checknumber(L, 1) / 180 * M_PI;
	float y = luaL_checknumber(L, 2) / 180 * M_PI;
	float z = luaL_checknumber(L, 3) / 180 * M_PI;
	CC->matrix = CC->matrix * AffineTransformMatrix::RotateXYZ(x, y, z);
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

	CC->componentToManipulate->InsertBox(CC->matrix, x, y, z);
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
		CC->componentToManipulate->InsertCylinder(CC->matrix, h, r1);
		break;
	case 3:
		h = luaL_checknumber(L, 1);
		r1 = luaL_checknumber(L, 2);
		r2 = luaL_checknumber(L, 3);
		CC->componentToManipulate->InsertCone(CC->matrix, h, r1, r2);
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
	CC->linkedMachine->componentWithTool
			= CC->linkedMachine->components.Count() - 1;
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
	CC->linkedMachine->materialPositionRelativ.Set(CC->matrix);
	CC->linkedMachine->materialPosition.Set(CC->matrix);
	CC->linkedMachine->componentWithMaterial
			= CC->linkedMachine->components.Count() - 1;
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

