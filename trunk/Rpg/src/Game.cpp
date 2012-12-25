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

#include "Game.h"


Game* __gCurrentGameInstance = 0;
Game* gGetGameInstance()
{
	// I don't plan on allowing multiple game instances
	// to be active at once, though it is possible.
	return __gCurrentGameInstance;
}


int Game::Initialize()
{
	__gCurrentGameInstance = this;

	m_resourceManager.SetBaseDirectory("game/");
	m_resourceManager.SetTextureDirectory("textures/");
	m_resourceManager.SetFontDirectory("fonts/");

	int ret(0);
	ret = InternalInitScriptEngine();
	if(ret != 0)
		return ret;

	return ret;
}


//for testing
#include <conio.h>
#include <stdio.h>


int Game::InternalInitScriptEngine()
{
	ScriptEngine* engine = GetScriptEngine();
	engine->SetGame(this);
	engine->Initialize();
	engine->SetDefaultEngineProperties();
	engine->RegisterScriptingInterfaces();

	//WIP build - this will be removed later
	Log( "Compiling scripts..." );
	for( bool exit(false); exit != true; )
	{
		if( engine->Compile("script/TestCompile.cpp", fc::vector<fc::string>()) != 0 )
		{
			printf("-press [c] to recompile, or any key to exit.");
			int c = _getch();
			if( c != int('c') )
				return -1;
				//exit = true;

		}
		else exit = true;
	}

	return 0;
}






void Game::Update()
{
	m_scriptEngine.Update();
	m_screenManager.Update();
}


void Game::Render()
{
	m_screenManager.Render();
}


