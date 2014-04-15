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
#include "GameData.h"
#include "Database.h"
#include "BattleScreen.h"


Game* game = 0;
//ScriptEngine* g_scriptEngine = 0;
BattleEngine* g_battleEngine = 0;
SpriteBatch* g_tempSpriteBatch = 0;

//ScriptEngine* gGetScriptEngine() { return g_scriptEngine; }
Game* gGetGame() { return game; }
Game* GetGame() { return game; }
SpriteBatch* gGetSpriteBatch() { return g_tempSpriteBatch; }

Database g_database;

//I'm sticking this here for now also!
Database* GetDatabase()
{
	return &g_database;
}
BattleEngine* GetBattleEngine()
{
	return g_battleEngine;
}



int Game::Initialize()
{
	//g_scriptEngine = &m_scriptEngine;
	g_tempSpriteBatch = &m_spriteBatch;
	//gSetActiveDatabase(&m_database);

	//m_resourceManager.GetResourceDirectory().SetRootDirectory("data/");

	int ret(0);
	ret = InternalInitScriptEngine();
	if(ret != 0)
		return ret;

	return ret;
}


MonoScriptObject* mso;

void Game::Shutdown()
{
	MonoScriptEngine* scriptEngine = GetScriptEngine();
	scriptEngine->DestroyScriptObject(mso);
	scriptEngine->Shutdown();
}


//for testing
#include <conio.h>
#include <stdio.h>
#include "TestScreen.h" //testing pt.2


int Game::InternalInitScriptEngine()
{
	MonoScriptEngine* scriptEngine = GetScriptEngine();
	scriptEngine->SetDefaultEngineProperties();
	scriptEngine->Initialize();
	scriptEngine->LoadScriptAssembly("../Tetris/bin/Release/Tetris.exe");

//../Framework/bin/Debug

	return 0;
}




void Game::Update()
{
	static bool testInit = false;
	if(!testInit)
	{
		GetScriptEngine()->GetScriptAssembly()->CallApplicationMain();
		mso = m_scriptEngine.CreateScriptObject("TetrisGame", "Tetris");
		mso->CallDefaultCtor();
		testInit = true;
		return;

		// TEST ONLY
		Battle* b = new Battle();
	/*	b->CreateFromMonsterTroopId(238);
		b->AddMonsterTroopId(244);
		b->AddMonsterTroopId(242);
		b->AddMonsterTroopId(240);*/
		b->AddMonsterTroopId(4);

		///*
		BattleScreen* bs = new BattleScreen();
		bs->GetBattleEngine()->AddPlayerCombatantsFromParty( GetGameData()->GetActiveParty() );
		bs->GetBattleEngine()->AddBattle(b);
		bs->GetBattleEngine()->Setup();

		g_battleEngine = bs->GetBattleEngine(); //fixme

		m_screenManager.Add( bs );
		//*/

		//m_screenManager.Add( new TestScreen() ); //....
		testInit = true;
	}

	mso->CallUpdateMethod();
	MonoGC gc;
	int hs = gc.GetHeapSize();
	//Log("gc : size [%i]", hs);

	//m_scriptEngine.Update();
	m_screenManager.Update();
}

Texture* bgt = 0;
void Game::Render()
{
	m_spriteBatch.Begin();


	if(!bgt)
	{
		bgt = new Texture();
		bgt->LoadFromFile("data/textures/backgrounds/14.png");
	}
	//m_spriteBatch.DrawTexture(GetDatabase()->character_battle_sprites[0].LoadTexture(), Vector2(30,30));
	//m_spriteBatch.DrawTexture(bgt, Vector2(0,0));

	m_screenManager.Render();

	//script drawing is stuck here for now.
	//m_spriteBatch.Begin();
	m_spriteBatch.Render();
	m_spriteBatch.End();

	mso->CallRenderMethod();

}


