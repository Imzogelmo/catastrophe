
#pragma once

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"
#include "../Game.h"


namespace script
{
	//todo


} //namespace script



void ScriptEngine::RegisterGame()
{
	int r(0);
	using namespace script;
	r = engine->SetDefaultNamespace("game"); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "::map@ get_map(int)", asFUNCTION(GetMap), asCALL_CDECL); assert( r >= 0 );
	r = engine->SetDefaultNamespace(""); assert( r >= 0 );
}


void ScriptEngine::RegisterGameInterface()
{
	RegisterGame();
}

