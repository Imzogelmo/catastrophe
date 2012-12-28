
#pragma once

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"
#include "../Game.h"


namespace script
{
	int LoadTeaxture( const fc::string& filename )
	{
		int id = -1;
		ResourceManager* resourceManager = gGetGameInstance()->GetResourceManager();
		Texture* texture = resourceManager->LoadTexture(filename, &id);
		if( !texture )
		{
			//todo: this is not really needed.
			gGetGameInstance()->GetScriptEngine()->SetException( asGetActiveContext(), filename );
		}

		return id;
	}

	int LoadFont( const fc::string& filename, int faceSize )
	{
		int id = -1;
		ResourceManager* resourceManager = gGetGameInstance()->GetResourceManager();
		Font* font = resourceManager->LoadFont(filename, faceSize, &id);
		if( !font )
		{
			//todo: this is not really needed.
			gGetGameInstance()->GetScriptEngine()->SetException( asGetActiveContext(), filename );
		}
		
		return id;
	}

} //namespace script



void ScriptEngine::RegisterGame()
{
	int r(0);
	using namespace script;
	r = engine->SetDefaultNamespace("game"); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int load_texture(const string&)", asFUNCTION(LoadTeaxture), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int load_font(const string&, int)", asFUNCTION(LoadFont), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "::map@ get_map(int)", asFUNCTION(GetMap), asCALL_CDECL); assert( r >= 0 );
	r = engine->SetDefaultNamespace(""); assert( r >= 0 );
}


void ScriptEngine::RegisterGameInterface()
{
	RegisterGame();
}

