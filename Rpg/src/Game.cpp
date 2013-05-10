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

Game* game = 0;
ScriptEngine* g_scriptEngine = 0;

ScriptEngine* gGetScriptEngine() { return g_scriptEngine; }
Game* gGetGame() { return game; }



int Game::Initialize()
{
	g_scriptEngine = &m_scriptEngine;
	//gSetActiveDatabase(&m_database);

	//m_resourceManager.GetResourceDirectory().SetRootDirectory("data/");

	int ret(0);
	//ret = InternalInitScriptEngine();
	if(ret != 0)
		return ret;

	return ret;
}


void Game::Shutdown()
{
}


//for testing
#include <conio.h>
#include <stdio.h>
#include "TestScreen.h" //testing pt.2


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
		if( engine->Compile("script/blocks.cpp", fc::vector<fc::string>()) != 0 )
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
	m_spriteBatch.Begin();

	static bool testInit = false;
	if(!testInit)
	{
	//	m_screenManager.Add( new TestScreen(&m_screenManager) ); //....
		testInit = true;
	}

	//m_scriptEngine.Update();
	m_screenManager.Update();
}


void Game::Render()
{
	m_screenManager.Render();

	//script drawing is stuck here for now.
	//m_spriteBatch.Begin();
	m_spriteBatch.Render();
	m_spriteBatch.End();
}


