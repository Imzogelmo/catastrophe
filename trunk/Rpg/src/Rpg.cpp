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


#include <Catastrophe/System.h>
#include <Catastrophe/Input.h>
#include <Catastrophe/IO/ConfigFile.h>

#include "Common.h"
#include "GlobalSettings.h"
#include "Game.h"

#include "ResourceManager.h"


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



void LoadConfigSettings( int argc, char *argv[] )
{

	//ExpCurve exp;
	//exp.GenerateCurve();


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


//I use this periodically to test/accum data.
//just make sure that Tests() is commented out
//before running it.

//temp includes
#include "Monster.h"
#include "MonsterPartyData.h"
#include "Item.h"
#include "Tile/TilesetManager.h"
#include <Catastrophe/IO/File.h>
#include "CharacterClass.h"

MonsterList gMonsterList; //temp for gererating data.

void DoTests()
{

	ResourceManager rm;
	gSetActiveResourceManager(&rm);
	rm.SetBaseDirectory("data/");
	rm.SetTextureDirectory("textures/");
	rm.LoadTexture("monsters_psp.png");

	gMonsterList.DeserializeXml("monsters_psp.xml");
	gMonsterList.SerializeXml("M2.xml");



	bool r;
	CharacterClassList ccl;
	CharacterClassList::vec_type & v = ccl.GetVector();

	Texture t;
	t.LoadFromFile("data/textures/characters.png");
	t.SetName("characters.png");

	/*
	ResourceManager rm;
	gSetActiveResourceManager(&rm);
	rm.SetBaseDirectory("data/");
	rm.SetTextureDirectory("textures/");
	rm.LoadTexture("characters.png");
	ccl.DeserializeXml("chars_test.h");
	*/

	int y = 0;
	foreachi(i, 12)
	{
		v.push_back();
		for(int j(24); j < 29; j++ )
			v.back().attributes.stats[j] = 5;

		v.back().name = "Fighter";
		v.back().animation_set.SetSize( Vector2(24) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(0,y,48,48)) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(24,y,48,48)) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(48,y,48,48), 4, 0, 0) );//walking
		v.back().animation_set.GetAnimation(2).SetAnimationSpeed(4);
		v.back().animation_set.AddAnimation( Animation(&t, Rect(148,y,48,48), 2, 0, 0) );//casting
		v.back().animation_set.GetAnimation(3).SetAnimationSpeed(6);
		v.back().animation_set.AddAnimation( Animation(&t, Rect(192,y,48,48)) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(192,y,48,48), 2, 0, 0) );//victory
		v.back().animation_set.AddAnimation( Animation(&t, Rect(240,y,48,48)) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(264,y,48,48)) );
		v.back().animation_set.AddAnimation( Animation(&t, Rect(298,y,48,48)) );
		y += 24;
	}

	ccl.SerializeXml("chars_test.h");

	if(!r)
		r = ! r;
	return; //for debug stepping.
}


void CheckWinMemStats();
void DoAtlasPack();
void DoAtlasPack2();
void DoAtlasPack3();
void DoAtlasPack4();
#include <fc/multi_array.h>
#include <Catastrophe/Util/Timer.h>


int main(int argc, char* argv[])
{
	// enable memory leak checking.
	static int crtDebugflags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	crtDebugflags |= (crtDebugflags & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
	_CrtSetDbgFlag(crtDebugflags);

	/*
	File f("sansation.ttf");
	File out("out.txt", FileWriteText);
	int i(0);
	while(!f.IsEof())
	{
		ubyte c = f.ReadByte();
		out.WriteLine(fc::to_string(int(c)) + ",", (++i % 30) == 0);
	}

	f.Close();
	out.Close();
	return 0;
*/
	// initialize system and sub-systems.
	System::Init();
	System::InitLogging("debug.log", true); //todo put this after config..

	//DoTests();


	// read config file and parse command-line arguments.
	LoadConfigSettings(argc, argv);


	Game* game = new Game();
	if( game->Initialize() != 0 )
		return -1;

	Window* window = CreateWindow();

	//DoTests(); //some quick and dirty testing.


	//DoAtlasPack4();
	//return 0;

	//Font font;
	//font.LoadFromFile(fc::string(), 32);
	//CheckWinMemStats();

	Timer timer;
	Timer loopTimer;
	window->SetOrthographicProjection(0, 256, 208, 0);
	while( !window->RequestClose() )
	{
		window->ClearColor();
		window->Update();

		//timer.Reset();
		Input::Update();
		//Log("update %0.4f", float(timer.Seconds()));

		//timer.Reset();
		game->Update();

			static int tmp = 0;
			tmp++;
			//if(tmp % 12 == 0) Log("update %0.4f", float(timer.Seconds() * 60.f));
			//if(tmp % 12 == 0) Log("update %i", int(timer.ElapsedMicroseconds()));
			//timer.Reset();
		game->Render();
			//if(tmp % 12 == 0) Log("render %0.4f", float(timer.Seconds() * 60.f));
			//if(tmp % 12 == 0) Log("render %i", int(timer.ElapsedMicroseconds()));


		//window->Sleep(16);
		window->SwapBuffers();

		int elapsedMS = loopTimer.ElapsedMilliseconds();
		while(elapsedMS <= 16)
		{
			int tMS = elapsedMS;
			//Log( "-------------TMS-----------: (%i)", elapsedMS );
			window->Sleep( (16 - tMS) > 0 ? (16 - tMS) - 1 : 0 );
			elapsedMS = loopTimer.ElapsedMilliseconds();
		}
		//Log("frame time: (%0.4f)", float(loopTimer.ElapsedMicroseconds() / 1000.0f));
		//Log( "frame time: (%i)", int(loopTimer.ElapsedMilliseconds()) );
		loopTimer.Reset();

	}


	delete game;

	// shut down all sub-systems and release resources.
	System::Terminate();
	return 0;
}





/*
#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//windows crap
#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_IX86)
#define _X86_
#endif

//more windows crap
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOGDI
#include <windef.h>
#include <winbase.h>


#include <stdio.h>
#include <Catastrophe/Graphics/Image.h>
#include <Catastrophe/Graphics/TextureLoader.h>
#include <Catastrophe/Util/TexturePacker.h>

#include <fc/dynamic_array2d.h>
#include <fc/sort.h>
#include "Util/StringAlias.h"

#include <cstdlib>


#include "psapi.h"
#pragma comment(lib, "psapi.lib")
void CheckWinMemStats()
{
	MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

	PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

	Log("VM (total: %i, used %i) - PM (total %i, virtual %i, physical %i)",
		(int)(totalVirtualMem / 1024)/ 1024,
		(int)(virtualMemUsed / 1024)/ 1024,
		(int)(totalPhysMem / 1024)/ 1024,
		(int)(virtualMemUsedByMe / 1024)/ 1024,
		(int)(physMemUsedByMe / 1024)/ 1024
		);

}


int hexStrToInt( const fc::string& s) {
    char * p;
    long n = strtol( s.c_str(), & p, 16 );
    assert(p);
	return (int)n;
}

class FileGetter{
    WIN32_FIND_DATAA found; 
    HANDLE hfind;
    char folderstar[255];       
    int chk;

public:
    FileGetter(char* folder){       
        sprintf(folderstar,"%s\\*.*",folder);
        hfind = FindFirstFileA(folderstar,&found);
        //skip .
        FindNextFileA(hfind,&found);        
    }

    int getNextFile(char* fname){
        //skips .. when called for the first time
        chk=FindNextFileA(hfind,&found);
        if (chk)
            strcpy(fname, found.cFileName);     
        return chk;
    }

};


void DoAtlasPack() //let's do it!
{
	const int W = 1024;
	const int H = 1024;
	const int MAX_EN = 204;

	bool r = gMonsterList.DeserializeXml("monsters.xml");
	assert(r);

	StringAliasList strAlias;
	strAlias.DeserializeXml( "monster_compat.xml" );

	for(int u(0); u < gMonsterList.Size(); ++ u )
	{
		gMonsterList[u].attributes.stats[0] = 1; //lv
	}

	for(int u(0); u < strAlias.GetList().size(); ++ u )
	{
		bool found = false;
		for(int w(0); w < gMonsterList.Size(); ++ w )
		{
			if( gMonsterList.GetMonster(w).GetName().to_lower() == strAlias.GetList()[u].alias )
			{
				found = true;
				break;
			}
		}

		if(!found)
		{
			Log("!!!correct alias (%s)", strAlias.GetList()[u].alias.c_str() );
			//exit(1);
		}
	}


	FileGetter fg("ff1");
	TextureLoader tl;

	//Image image;
	//image.CreateFromPixels(1024, 1024, 0); //blank image (all black)
	//image.GetPixelArray();

	fc::dynamic_array2d<Color> pixels(H,W);
	pixels.assign(Color::Black(0)); //0,0,0,0 color
	fc::dynamic_array2d<Color> temp[128];
	fc::string str[128];

	int i(0);
	char buf[255];
	while( fg.getNextFile(buf) )
	{
		Point size = Point::Zero;
		fc::string s = buf;
		if(s == "Thumbs.db" || s == "thumbs.db")
			continue;

		str[i] = s;
		str[i].erase(str[i].size() - 4, 4); //erase ".png"

		if( !strAlias.ContainsName(str[i]) )
		{
			Log("no name (%s) found.", str[i].c_str());
		}

		s.insert(0, "ff1/");
		ubyte* data = tl.LoadFromFile(s, size);
		if(data)
		{
			temp[i].resize(size.y, size.x);
			temp[i].assign(Color::Black(0));

			int q(0);
			for( int k(0); k < size.y; ++k )
			{
				for( int j(0); j < size.x; ++j )
				{
					Color *pixel = & temp[i]( k, j );
					(*pixel).r = *(data + q++);
					(*pixel).g = *(data + q++);
					(*pixel).b = *(data + q++);
					(*pixel).a = *(data + q++);
				}
			}

			Color mask = temp[i][0];
			if( str[i] == "coctrice" || str[i] == "perilisk" )
			{
				mask = temp[i](15,0);
			}

			for( int  j(0); j < temp[i].size(); ++j )
			{
				if( temp[i][j] == mask )
				{
					temp[i][j] = Color::Black(0);
				}
			}

			tl.FreePtr(data);
		}

		i++;
	}

	struct arrStr{
		fc::dynamic_array2d<Color>* p;
		fc::string* s;
	};

	struct sortstructx{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->x() < b.p->x();
		}
	};

	struct sortstructy{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->y() < b.p->y();
		}
	};

	struct sortstructxy{
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return (a.p->y() * a.p->x()) < (b.p->y() * b.p->x());
		}
	};

	arrStr as[128];
	for( int  j(0); j < 128; ++j )
	{
		as[j].p = &temp[j];
		as[j].s = &str[j];
	}

	//sort pointers to arrays.
	fc::insertion_sort( as, as + 128, sortstructy() );
	fc::insertion_sort( as, as + 128, sortstructx() );
	fc::insertion_sort( as, as + 128, sortstructxy() );

	//align to grid for extensibility.
	GridTexturePacker texPack(W,H);
	Rect sourceRects[128];

	bool firstInc = false;
	bool secInc = false;
	for( int  j(0); j < 128; ++j )
	{
		if( !firstInc && as[j].p->y() > 32 )
		{
			firstInc = true;
			texPack.IncrementRow();
		}
		else if( !secInc && as[j].p->y() > 48 )
		{
			secInc = true;
			texPack.IncrementRow();
		}

		Point pos = Point::Zero;
		assert( texPack.Pack(as[j].p->x(), as[j].p->y(), pos) );

		sourceRects[j] = Rect( pos, Point(as[j].p->x(), as[j].p->y()) );
		//gMonsterList[u].sprite.SetFrameData(
		//	Rect(pos.x, pos.y)
		//);

		//copy to our texture atlas
		pixels.write_region( pos.x, pos.y, as[j].p->x(), as[j].p->y(), *as[j].p );
	}


	Texture tex;
	tex.CreateTexture(pixels.data(), pixels.x(), pixels.y());
	tex.SetName("monsters.png");

	for(int u(0); u < 128; ++ u )
	{
		gMonsterList.GetMonster(u).sprite.SetTexture(&tex);
	}

	for(int u(0); u < 128; ++ u )
	{
		fc::string al;
		bool suc = strAlias.GetAlias(*as[u].s, al);
		//assert(suc);

		bool found = false;
		for(int w(0); w < gMonsterList.Size(); ++ w )
		{
			if( gMonsterList.GetMonster(w).GetName().to_lower() == al )
			{
				gMonsterList.GetMonster(w).sprite.SetFrameData(sourceRects[u]);
				gMonsterList.GetMonster(w).sprite.size = sourceRects[u].size;
				found = true;
				break;
			}
		}

		if(!found)
		{
			Log("Not found (%s)", al.c_str());
		}

	}

	gMonsterList.SerializeXml("new_m.xml");
	for(int u(0); u < 128; ++ u )
	{
		if(gMonsterList[u].sprite.size.x > 300)
		{
			Log("%s", gMonsterList[u].name.c_str());
		}
	}
	//..finally save the atlas.
	tl.SaveToFile( "monsters.png", pixels.data(), pixels.x(), pixels.y() );
}



void DoAtlasPack2()
{
	const int W = 2048;
	const int H = 1024;
	const int MAX_EN = 175;

	bool r = gMonsterList.DeserializeXml("monsters.xml");
	assert(r);

	FileGetter fg("ENEMY");
	TextureLoader tl;

	//Image image;
	//image.CreateFromPixels(1024, 1024, 0); //blank image (all black)
	//image.GetPixelArray();

	fc::dynamic_array2d<Color> pixels(H,W);
	pixels.assign(Color::Black(0)); //0,0,0,0 color
	fc::dynamic_array2d<Color> temp[MAX_EN];
	fc::string str[MAX_EN];

	int i(0);
	char buf[255];
	while( fg.getNextFile(buf) )
	{
		Point size = Point::Zero;
		fc::string s = buf;
		if(s == "Thumbs.db" || s == "thumbs.db")
			continue;

		str[i] = s;
		str[i].erase(str[i].size() - 4, 4); //erase ".png"
		str[i].erase(0, 3);

		s.insert(0, "ENEMY/");
		ubyte* data = tl.LoadFromFile(s, size);
		if(data)
		{
			temp[i].resize(size.y, size.x);
			temp[i].assign(Color::Black(0));

			int q(0);
			for( int k(0); k < size.y; ++k )
			{
				for( int j(0); j < size.x; ++j )
				{
					Color *pixel = & temp[i]( k, j );
					(*pixel).r = *(data + q++);
					(*pixel).g = *(data + q++);
					(*pixel).b = *(data + q++);
					(*pixel).a = *(data + q++);
				}
			}

			tl.FreePtr(data);
		}

		i++;
	}

	struct arrStr{
		fc::dynamic_array2d<Color>* p;
		fc::string* s;
	};

	struct sortstructx{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->x() < b.p->x();
		}
	};

	struct sortstructy{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->y() < b.p->y();
		}
	};

	struct sortstructxy{
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return (a.p->y() * a.p->x()) < (b.p->y() * b.p->x());
		}
	};

	arrStr as[MAX_EN];
	for( int  j(0); j < MAX_EN; ++j )
	{
		as[j].p = &temp[j];
		as[j].s = &str[j];
	}

	//sort pointers to arrays.
	//fc::insertion_sort( as, as + MAX_EN, sortstructy() );
	//fc::insertion_sort( as, as + MAX_EN, sortstructx() );
	fc::insertion_sort( as, as + MAX_EN, sortstructxy() );

	//align to grid for extensibility.
	GridTexturePacker texPack(W,H);
	Rect sourceRects[MAX_EN];

	bool inc[3] = { false, false, false };
	for( int  j(0); j < MAX_EN; ++j )
	{
		if( !inc[0] && as[j].p->y() > 64 )
		{
			inc[0] = true;
			texPack.IncrementRow();
		}
		else if( !inc[1] && as[j].p->y() > 96 )
		{
			inc[1] = true;
			texPack.IncrementRow();
		}

		Point pos = Point::Zero;
		assert( texPack.Pack(as[j].p->x(), as[j].p->y(), pos) );

		sourceRects[j] = Rect( pos, Point(as[j].p->x(), as[j].p->y()) );
		//gMonsterList[u].sprite.SetFrameData(
		//	Rect(pos.x, pos.y)
		//);

		//copy to our texture atlas
		pixels.write_region( pos.x, pos.y, as[j].p->x(), as[j].p->y(), *as[j].p );
	}

	Texture tex;
	tex.CreateTexture(pixels.data(), pixels.x(), pixels.y());
	tex.SetName("monsters2.png");

	for( int  u(0); u < 128; ++u )
	{
		gMonsterList.GetMonster(u).sprite.SetTexture(&tex);
	}
	for( int  u(0); u < MAX_EN; ++u )
	{
		if(as[u].s->empty())
			continue;

		int n = hexStrToInt(*as[u].s);
		if(n < 128 )
		{
			gMonsterList.GetMonster(n).sprite.SetFrameData(sourceRects[u]);
			gMonsterList.GetMonster(n).sprite.size = sourceRects[u].size;
		}
	}

	//..finally save the atlas.
	tl.SaveToFile( "monsters.png", pixels.data(), pixels.x(), pixels.y() );

	gMonsterList.SerializeXml("m2.xml");
}


void DoAtlasPack3()
{
	const int W = 2048;
	const int H = 1024;
	const int MAX_EN = 304;

	FileGetter fg("dw7");
	TextureLoader tl;

	fc::dynamic_array2d<Color> pixels(H,W);
	pixels.assign(Color::Black(0)); //0,0,0,0 color
	fc::dynamic_array2d<Color> temp[MAX_EN];
	fc::string str[MAX_EN];

	int i(0);
	char buf[255];
	while( fg.getNextFile(buf) )
	{
		Point size = Point::Zero;
		fc::string s = buf;
		if(s == "Thumbs.db" || s == "thumbs.db")
			continue;

		str[i] = s;
		str[i].erase(str[i].size() - 4, 4); //erase ".png"
		s.insert(0, "dw7/");
		ubyte* data = tl.LoadFromFile(s, size);
		if(data)
		{
			temp[i].resize(size.y, size.x);
			temp[i].assign(Color::Black(0));

			int q(0);
			for( int k(0); k < size.y; ++k )
			{
				for( int j(0); j < size.x; ++j )
				{
					Color *pixel = & temp[i]( k, j );
					(*pixel).r = *(data + q++);
					(*pixel).g = *(data + q++);
					(*pixel).b = *(data + q++);
					(*pixel).a = *(data + q++);
				}
			}

			tl.FreePtr(data);
		}

		i++;
	}

	struct arrStr{
		fc::dynamic_array2d<Color>* p;
		fc::string* s;
	};

	struct sortstructx{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->x() < b.p->x();
		}
	};

	struct sortstructy{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->y() < b.p->y();
		}
	};

	struct sortstructxy{
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return (a.p->y() * a.p->x()) < (b.p->y() * b.p->x());
		}
	};

	arrStr as[MAX_EN];
	for( int  j(0); j < MAX_EN; ++j )
	{
		as[j].p = &temp[j];
		as[j].s = &str[j];
	}

	//sort pointers to arrays.
	fc::insertion_sort( as, as + MAX_EN, sortstructx() );
	fc::insertion_sort( as, as + MAX_EN, sortstructy() );
	fc::insertion_sort( as, as + MAX_EN, sortstructxy() );
	fc::insertion_sort( as, as + MAX_EN, sortstructy() );

	//align to grid for extensibility.
	GridTexturePacker texPack(W,H);
	Rect sourceRects[MAX_EN];

	bool inc[3] = { false, false, false };
	for( int  j(0); j < MAX_EN; ++j )
	{
		Point pos = Point::Zero;
		assert( texPack.Pack(as[j].p->x(), as[j].p->y(), pos) );

		sourceRects[j] = Rect( pos, Point(as[j].p->x(), as[j].p->y()) );

		//copy to our texture atlas
		pixels.write_region( pos.x, pos.y, as[j].p->x(), as[j].p->y(), *as[j].p );
	}

	Texture tex;
	tex.CreateTexture(pixels.data(), pixels.x(), pixels.y());
	tex.SetName("dw7.png");

	for( int u(0); u < MAX_EN; ++u )
	{
		if(as[u].s->empty())
		{
			assert(true);
			continue;
		}

		Monster m;
		m.SetName(*as[u].s);
		m.SetScript(*as[u].s);
		m.sprite.SetTexture(&tex);
		m.sprite.SetFrameData(sourceRects[u]);
		m.sprite.size = sourceRects[u].size;
		gMonsterList.Add(m);
	}

	//..finally save the atlas.
	tl.SaveToFile( "dw7.png", pixels.data(), pixels.x(), pixels.y() );

	gMonsterList.SerializeXml("dw7.xml");
}


void DoAtlasPack4()
{
	const int W = 2048;
	const int H = 1024;
	const int MAX_EN = 344;

	FileGetter fg("ff6");
	TextureLoader tl;

	fc::dynamic_array2d<Color> pixels(H,W);
	pixels.assign(Color::Black(0)); //0,0,0,0 color
	fc::dynamic_array2d<Color> temp[MAX_EN];
	fc::string str[MAX_EN];

	int i(0);
	char buf[255];
	while( fg.getNextFile(buf) )
	{
		Point size = Point::Zero;
		fc::string s = buf;
		if(s == "Thumbs.db" || s == "thumbs.db")
			continue;

		str[i] = s;
		str[i].erase(str[i].size() - 4, 4); //erase ".png"
		s.insert(0, "ff6/");
		ubyte* data = tl.LoadFromFile(s, size);
		if(data)
		{
			temp[i].resize(size.y, size.x);
			temp[i].assign(Color::Black(0));

			int q(0);
			for( int k(0); k < size.y; ++k )
			{
				for( int j(0); j < size.x; ++j )
				{
					Color *pixel = & temp[i]( k, j );
					(*pixel).r = *(data + q++);
					(*pixel).g = *(data + q++);
					(*pixel).b = *(data + q++);
					(*pixel).a = *(data + q++);
				}
			}

			tl.FreePtr(data);
		}

		i++;
	}

	struct arrStr{
		fc::dynamic_array2d<Color>* p;
		fc::string* s;
	};

	struct sortstructx{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->x() < b.p->x();
		}
	};

	struct sortstructy{ //sort by x pos.
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return a.p->y() < b.p->y();
		}
	};

	struct sortstructxy{
		bool operator()( const arrStr& a, const arrStr& b ) const{
			return (a.p->y() * a.p->x()) < (b.p->y() * b.p->x());
		}
	};

	arrStr as[MAX_EN];
	for( int  j(0); j < MAX_EN; ++j )
	{
		as[j].p = &temp[j];
		as[j].s = &str[j];
	}

	//sort pointers to arrays.
	//fc::insertion_sort( as, as + MAX_EN, sortstructx() );
	//fc::insertion_sort( as, as + MAX_EN, sortstructy() );
	fc::sort( as, as + MAX_EN, sortstructxy() );
	fc::sort( as, as + MAX_EN, sortstructy() );

	//align to grid for extensibility.
	RectangleTexturePacker texPack(W,H);
	Rect sourceRects[MAX_EN];

	bool inc[3] = { false, false, false };
	for( int  j(0); j < MAX_EN; ++j )
	{
		Point pos = Point::Zero;
		assert( texPack.Pack(as[j].p->x() + 1, as[j].p->y() + 1, pos) );

		sourceRects[j] = Rect( pos, Point(as[j].p->x(), as[j].p->y()) );

		//copy to our texture atlas
		pixels.write_region( pos.x, pos.y, as[j].p->x(), as[j].p->y(), *as[j].p );
	}

	Texture tex;
	tex.CreateTexture(pixels.data(), pixels.x(), pixels.y());
	tex.SetName("ff6.png");

	for( int u(0); u < MAX_EN; ++u )
	{
		if(as[u].s->empty())
		{
			assert(true);
			continue;
		}

		Monster m;
		m.SetName(*as[u].s);
		m.SetScript(*as[u].s);
		m.sprite.SetTexture(&tex);
		m.sprite.SetFrameData(sourceRects[u]);
		m.sprite.size = sourceRects[u].size;
		gMonsterList.Add(m);
	}

	//..finally save the atlas.
	tl.SaveToFile( "ff6.png", pixels.data(), pixels.x(), pixels.y() );

	gMonsterList.SerializeXml("ff6.xml");
}
*/



