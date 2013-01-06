// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"
#include "../Game.h"


namespace script
{
	int LoadTexture( const fc::string& filename )
	{
		int id = -1;
		ResourceManager* resourceManager = gGetActiveGame()->GetResourceManager();
		Texture* texture = resourceManager->LoadTexture(filename, &id);
		if( !texture )
		{
			//todo: this is not really needed.
			gGetActiveGame()->GetScriptEngine()->SetException( asGetActiveContext(), filename );
		}

		return id;
	}

	int LoadFont( const fc::string& filename, int faceSize )
	{
		int id = -1;
		ResourceManager* resourceManager = gGetActiveGame()->GetResourceManager();
		Font* font = resourceManager->LoadFont(filename, faceSize, &id);
		if( !font )
		{
			//todo: this is not really needed.
			gGetActiveGame()->GetScriptEngine()->SetException( asGetActiveContext(), filename );
		}
		
		return id;
	}


	Texture* GetTextureResource( int id )
	{
		ResourceManager* resourceManager = gGetActiveGame()->GetResourceManager();
		Texture* texture = resourceManager->GetTexture(id);
		if( !texture )
		{
			//todo: this is not really needed.
			gGetActiveGame()->GetScriptEngine()->SetException( asGetActiveContext(), "Invalid texture id" );
		}

		return texture;
	}

	Font* GetFontResource( int id )
	{
		ResourceManager* resourceManager = gGetActiveGame()->GetResourceManager();
		Font* font = resourceManager->GetFont(id);
		if( !font )
		{
			//todo: this is not really needed.
			gGetActiveGame()->GetScriptEngine()->SetException( asGetActiveContext(), "Invalid font id" );
		}

		return font;
	}





} //namespace script



void ScriptEngine::RegisterGame()
{
	int r(0);
	using namespace script;
	r = engine->SetDefaultNamespace("game"); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int load_texture(const ::string& in)", asFUNCTION(LoadTexture), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int load_font(const ::string& in, int)", asFUNCTION(LoadFont), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "::map@ get_map(int)", asFUNCTION(GetMap), asCALL_CDECL); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "::texture@ get_texture(int)", asFUNCTION(GetTextureResource), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "::font@ get_font(int)", asFUNCTION(GetFontResource), asCALL_CDECL); assert( r >= 0 );

	//r = engine->RegisterGlobalFunction( "const sprite& create_sprite(const ::texture& in, const rect& in)", asFUNCTION(CreateSprite), asCALL_CDECL); assert( r >= 0 );

	r = engine->SetDefaultNamespace(""); assert( r >= 0 );
}


void ScriptEngine::RegisterGameInterface()
{
	RegisterGame();
}

