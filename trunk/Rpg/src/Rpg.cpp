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


#include <time.h>
#include <stdlib.h>

#include <fc/rand.h>
#include <Catastrophe/System.h>
#include <Catastrophe/Input.h>
#include <Catastrophe/IO/ConfigFile.h>
#include <Catastrophe/Util/Timer.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/TextureLoader.h>
#include <Catastrophe/Graphics/Image.h>

#include "Common.h"
#include "GlobalSettings.h"
#include "Game.h"
#include "GameData.h"
#include "Database.h"


//for memory leak checking
#include <crtdbg.h>


GlobalSettings g_settings;

ConfigFile* gGetConfigFile() { return g_settings.GetConfigFile(); }
void GlobalSettings::Initialize() //I'm just sticking this here for now.
{
	m_configfile = new ConfigFile("settings.cfg");
}

GlobalSettings::~GlobalSettings()
{
	delete m_configfile;
}

void GenMonForm();
void GenMonTroopForm();

class _TestCrap
{
public:
	bool DArg( const fc::string& n = "", int val = 0 )
	{
		if( n.empty() && val > 9 )
			return true;
		return false;
	}
};


void LoadConfigSettings( int argc, char *argv[] )
{
	/*
		Step 1: Read the config file.
		Step 2: Get the command-line args, overriding the previous
				configuration state as needed.
	*/

	/*
		Parse default params from the config file.
		If the config file does not exist a new
		file will be created.
	*/

	g_settings.Initialize();

	ConfigFile* configFile = g_settings.GetConfigFile();

	if( !configFile->Read() )
	{
		// graphics
		configFile->SetCurrentSection("graphics");
		configFile->SetBool("vsync", false);
		configFile->SetBool("keep_aspect", false);
		configFile->SetBool("keep_scale", false);
		configFile->SetBool("antialias", true);
		configFile->SetBool("fullscreen", false);
		configFile->SetInt("resx", 640);
		configFile->SetInt("resy", 480);
		configFile->SetInt("multisample", 0);
		configFile->SetInt("scale", 0);

		/*
		// keyboard
		configFile->SetCurrentSection("keyboard");
		configFile->SetInt("button_y", 0);
		configFile->SetInt("button_b", 1);
		configFile->SetInt("button_a", 2);
		configFile->SetInt("button_x", 3);
		configFile->SetInt("button_l", 4);
		configFile->SetInt("button_r", 5);
		configFile->SetInt("button_l2", 6);
		configFile->SetInt("button_r2", 7);
		configFile->SetInt("button_select", 8);
		configFile->SetInt("button_start", 9);
		configFile->SetInt("button_l3", 10);
		configFile->SetInt("button_r3", 11);
		*/

		// joystick
		configFile->SetCurrentSection("joystick");
		configFile->SetInt("dpad_up", 0);
		configFile->SetInt("dpad_right", 1);
		configFile->SetInt("dpad_down", 2);
		configFile->SetInt("dpad_left", 3);
		configFile->SetInt("button_y", 0);
		configFile->SetInt("button_b", 1);
		configFile->SetInt("button_a", 2);
		configFile->SetInt("button_x", 3);
		configFile->SetInt("button_l", 4);
		configFile->SetInt("button_r", 5);
		configFile->SetInt("button_l2", 6);
		configFile->SetInt("button_r2", 7);
		configFile->SetInt("button_select", 8);
		configFile->SetInt("button_start", 9);
		configFile->SetInt("button_l3", 10);
		configFile->SetInt("button_r3", 11);



		configFile->Write();
	}

	//commandLine.Process( argc, argv, settings );

}


Window* CreateWindow()
{
	ConfigFile* config = gGetConfigFile();

	config->SetCurrentSection("graphics");
	bool vsync			= config->GetBool("vsync", false);
	bool keep_aspect	= config->GetBool("keep_aspect", false);
	bool keep_scale		= config->GetBool("keep_scale", false);
	bool antialias		= config->GetBool("antialias", true);
	bool fullscreen		= config->GetBool("fullscreen", false);

	int resx			= config->GetInt("resx", 640);
	int resy			= config->GetInt("resy", 480);
	int multisample		= config->GetInt("multisample", 0);
	int scale			= config->GetInt("scale", 0);


	Window* window = System::CreateWindow(
		resx,
		resy,
		fullscreen,
		true,		//resizable
		8,			//depth
		0,			//stencyl
		multisample
	);

	if( !window || !window->IsOpen() )
	{
		LogError("Fatal error: Window could not be created.");
		exit(1);
	}

	window->SetVSync(vsync);
	window->KeepAspectRatio(keep_aspect);
	//window->SetScale(scale); todo

	if( window->HasAntialiasing() != antialias )
		window->EnableAntiAliasing(antialias);

	return window;
}



int main(int argc, char* argv[])
{
	// enable memory leak checking.
	static int crtDebugflags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	crtDebugflags |= (crtDebugflags & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
	_CrtSetDbgFlag(crtDebugflags);

	// initialize system and sub-systems.
	System::Init();
	System::InitLogging("debug.log", true); //todo put this after config..


	//_TestCrap tc;
	//return tc.DArg(76) ? 1 : 0;


	// init lib
	//todo: ...
	RpgLibInit();
	GetDatabase()->Initialize(); //fixme

	/*
	DataArray<Item> idl;
	Database *db = GetDatabase();
	db->characters.resize(12);
	foreachi(i,12)
	{
		db->characters[i].class_id = i;
		db->characters[i].battle_spriteset_id = i;
		db->characters[i].map_spriteset_id = i;
		db->characters[i].portrait_id = i;
		db->characters[i].script = "Fighter";
		db->characters[i].name = "Name" + fc::to_string(i);
	}
	db->characters.SerializeXml();
	return 0;
	*/

	//GenMonForm();
	//GenMonTroopForm();
	//return 0;

	GameData* gd = GetGameData();
	Database* db = GetDatabase();
	db->DeserializeAllDataXml();
	gd->InitializeFromDatabase(GetDatabase());
	//gd->GetActiveParty()->SetMaxActivePartySize(32);
	foreachi(i,4){
		gd->GetActiveParty()->AddMember(i);
	}

	//MonsterData::RegisterObject();
	//CharacterClass::RegisterObject();
	db->monsters.filename = "testMonsters.xml";
	db->monsters.resource_directory = 0;
	db->monsters.SerializeXml();

	db->character_classes.filename = "testClass.xml";
	db->character_classes.resource_directory = 0;
	db->character_classes.SerializeXml();

	db->monster_troops.filename = "testTroops.xml";
	db->monster_troops.resource_directory = 0;
	db->monster_troops.SerializeXml();

	return 0;

	//db->GenerateScriptHeaders();
	//return 0;

	// read config file and parse command-line arguments.
	LoadConfigSettings(argc, argv);

	// seed rng
	fc::srand(int(time(0)));


	Game* game = new Game();

	Timer timer;
	timer.Reset();
	//if( game->Initialize() != 0 )
	//	return -1;
	Log( "game->Initialize milliseconds : %0.4f", float(timer.MilliSeconds()) );

	Window* window = CreateWindow();


	//Timer timer;
	Timer loopTimer;

	window->SetOrthographicProjection(0, 256, 224, 0);
	while( !window->RequestClose() )
	{
		window->ClearColor(Color::DarkBlue());
		window->Update();

		// DETECTS BUGS IN MULTI-MEDIA DRIVERS ON WIN32 (true story)
		// sometimes they are big piles of shit that stall the cpu.
		//timer.Reset();
		Input::Update();
		//Log("update %0.4f", float(timer.Seconds()));

		game->Update();
		game->Render();

		window->SwapBuffers();

		int elapsedMS = (int)loopTimer.ElapsedMilliseconds();
		while(elapsedMS <= 16)
		{
			int tMS = elapsedMS;
			//Log( "-------------TMS-----------: (%i)", elapsedMS );
			System::Sleep( (16 - tMS) > 0 ? (16 - tMS) - 1 : 0 );
			elapsedMS = (int)loopTimer.ElapsedMilliseconds();
		}
		//Log("frame time: (%0.4f)", float(loopTimer.ElapsedMicroseconds() / 1000.0f));
		//Log( "frame time: (%i)", int(loopTimer.ElapsedMilliseconds()) );
		loopTimer.Reset();

	}


	delete game;

	//todo
	RpgLibShutdown();

	// shut down all sub-systems and release resources.
	System::Terminate();
	return 0;
}





// more data generators.
///////////////////////////////////////////////////////////////////////////////////////
void GenMonForm()
{
	Database * db = GetDatabase();
	MonsterFormation* m = 0;
	db->monster_formations.resize(4);

	//pos
	//int sX[9] = { 32, 32, 32, 64, 64, 64, 96, 96, 96 };
	//int sY[9] = { 64, 32, 96, 64, 32, 96, 64, 32, 96 };
	int sX[9] = { 0, 0, 0, 32, 32, 32, 64, 64, 64 };
	int sY[9] = { 64, 32, 96, 64, 32, 96, 64, 32, 96 };
	//int lX[4] = { 32, 32, 80, 80 };
	//int lY[4] = { 32, 80, 32, 80 };
	int lX[4] = { 0, 0, 48, 48 };
	int lY[4] = { 48, 96, 48, 96 };

	// 1
	m = db->GetMonsterFormation(0);
	m->formations.resize(9);
	foreachi(i, 9)
	{
		m->formations[i].x = sX[i];
		m->formations[i].y = sY[i];
	}

	// 2
	m = db->GetMonsterFormation(1);
	m->formations.resize(8);
	foreachi(i, 8)
	{
		if( i < 2 ) {
			m->formations[i].x = lX[i];
			m->formations[i].y = lY[i];
		}
		else {
			m->formations[i].x = sX[i] - 16;
			m->formations[i].y = sY[i];
		}
	}

	// 3
	m = db->GetMonsterFormation(2);
	m->formations.resize(4);
	foreachi(i, 4)
	{
		m->formations[i].x = lX[i];
		m->formations[i].y = lY[i];
	}


	// Boss formation - center x,y
	// 4
	m = db->GetMonsterFormation(3);
	m->formations.resize(1);

	m->formations[0].x = 48;
	m->formations[0].y = 48;






	db->monster_formations.SerializeXml("monster_formations.xml");

}


void GenMonTroopForm()
{
	Database * db = GetDatabase();
	MonsterTroop* t = 0;
	db->DeserializeAllDataXml();


	foreachi(i, db->monster_troops.size())
	{
		bool boss = false;
		int small = 0;
		int large = 0;
		int lastSize = 0; //0 - small
		int curSize = 0; //0 - small

		t = db->GetMonsterTroop(i);
		foreachi( j, t->groups.size() )
		{
			int id = t->groups[j].monster_id;
			float x = db->monster_battle_sprites.at(id).size.x;
			if( x < 40 )
			{
				small++;
				curSize = 0;
			}
			else if( x < 64 )
			{
				large++;
				curSize = 1;
			}

			else boss = true;

			if( j > 0 && curSize == 1 )
			{
				if( lastSize == 0 )
				{
					fc::swap(t->groups[j], t->groups[j-1]);
					curSize = 0;
				}
			}

			lastSize = curSize;
		}

		int form = 0;
		if(large > 0)
		{
			if(small > 0)
				form = 1;
			else
				form = 2;
		}

		t->formation_id = form;

		if(form == 0) t->max_monsters = 9;
		else if(form == 1) t->max_monsters = 8;
		else if(form == 2) t->max_monsters = 4;
		else if(form == 3) t->max_monsters = 1;

	}

	db->monster_troops.SerializeXml("monster_troops.xml");

}

