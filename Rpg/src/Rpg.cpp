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


namespace fc
{
	void* allocate( size_t n, size_t /*alignment*/ )
	{
		return malloc(n);
	}

	void deallocate( void* p, size_t /*size*/ )
	{
		free(p);
	}

	void* allocate_temporary( size_t n, size_t alignment )
	{
		return allocate( n, alignment );
	}

	void deallocate_temporary( void* p, size_t size )
	{
		deallocate( p, size );
	}

	void assert_failure( const char* assertion, const char*, unsigned int )
	{
		assert(false && assertion);
	}
}


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



void CreateUnityBuildModule(
			fc::string directory,
			fc::string outFilename = "Unity_Build.cpp",
			fc::string extension = ".cpp" );


void CreateTestHeaderCPPFiles(
			fc::string directory,
			fc::string outDirectory );

void GenCWrapper( fc::string filename, fc::string outFn,
				 const char* prefixStr = "Self_", const char* classPtr = " _Self* self" );

void GenCWrappers();

int main(int argc, char* argv[])
{
	//const char* ubStr = "C:\\SVN\\EasyRPG\\Player\\src\\platform";
	//CreateUnityBuildModule( ubStr, "Unity_Build2.cpp", ".cpp" );
	//CreateTestHeaderCPPFiles( "C:\\C++\\include\\fc", "test" );

	//CreateUnityBuildModule( "C:/SVN/angelscript/sdk/angelscript/source", "Unity_Build2.cpp", ".cpp" );
	//return 0;

	GenCWrappers();
	return 0;

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

	Timer timer;
	timer.Reset();

	GameData* gd = GetGameData();
	Database* db = GetDatabase();
	db->DeserializeAllDataXml();
	gd->InitializeFromDatabase(GetDatabase());
	//gd->GetActiveParty()->SetMaxActivePartySize(32);
	foreachi(i,4){
		gd->GetActiveParty()->AddMember(i);
	}

	Log( "Database::DeserializeAllDataXml milliseconds : %0.4f", float(timer.MilliSeconds()) );

	/*
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
	*/


	//db->GenerateScriptHeaders();
	//return 0;

	// read config file and parse command-line arguments.
	LoadConfigSettings(argc, argv);

	// seed rng
	fc::srand(int(time(0)));


	Game* game = new Game();

	if( game->Initialize() != 0 )
		return -1;

	Window* window = CreateWindow();

	//...
	db->LogMemoryUsage();


	//Timer timer;
	Timer loopTimer;

	//window->SetOrthographicProjection(0, 256, 224, 0);
	window->SetOrthographicProjection(0, 640, 480, 0);
	while( !window->RequestClose() )
	{
		window->ClearColor(Color::DarkBlue());
		window->Update();

		// DETECTS BUGS IN MULTI-MEDIA DRIVERS ON WIN32 (true story)
		// sometimes they are big piles of shit that stall the cpu.
		//timer.Reset();
		Input::Update();
		//Log("update %0.4f", float(timer.Seconds()));

		timer.Reset();
		game->Update();
		game->Render();
		//Log("update/render time %0.4f", float(timer.Seconds() * 1000.0));

		window->SwapBuffers();

		int elapsedMS = (int)loopTimer.ElapsedMilliseconds();
		if(elapsedMS > 17 || elapsedMS < 0)
			elapsedMS = 0;

		/*
		//if(elapsedMS <= 16)
		{
			int tMS = elapsedMS;
			//Log( "-------------TMS-----------: (%i)", elapsedMS );
			//System::Sleep( (16 - tMS) > 0 ? (16 - tMS) - 1 : 0 );
			System::Sleep( (16 - tMS) > 0 ? (16 - tMS) : 0 );
			elapsedMS = (int)loopTimer.ElapsedMilliseconds();
		}
		//Log("frame time: (%0.4f)", float(loopTimer.ElapsedMicroseconds() / 1000.0f));
		//Log( "frame time: (%i)", int(loopTimer.ElapsedMilliseconds()) );
		//window->SetTitle( "FPS: " + fc::to_string(elapsedMS) );
		//loopTimer.Reset();
		*/
		System::Sleep(16);

	}


	game->Shutdown();
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


/////////////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOGDI
#include <windows.h>
#include <fc/string.h>

#pragma warning (disable : 4996)


class FileGetter
{
    WIN32_FIND_DATAA found; 
    HANDLE hfind;
    char folderstar[255];       
    int chk;

public:
    FileGetter(const char* folder)
	{       
        sprintf(folderstar,"%s\\*.*",folder);
        hfind = FindFirstFileA(folderstar,&found);
        //skip .
        FindNextFileA(hfind,&found);        
    }

    int GetNextFile(char* fname)
	{
        //skips .. when called for the first time
        chk=FindNextFileA(hfind,&found);
        if (chk)
            strcpy(fname, found.cFileName);     
        return chk;
    }

};

void CreateUnityBuildModule( fc::string directory, fc::string outFilename, fc::string extension )
{
	char buf[255];
	fc::string t, line;
	FileGetter fg( directory.c_str() );
	FILE* f = fopen( outFilename.c_str(), "w" );
	fwrite( "// Auto-generated file\n\n", 24, 1, f );

	while( fg.GetNextFile(buf) != 0 )
	{
		t = buf;
		if( t.size() > 4 && t.substr(t.size() - 4) == extension )
		{
			line = "#include \"" + t + "\"\n";
			fwrite( line.data(), line.size(), 1, f );
		}

	}

	fclose(f);
}


void CreateTestHeaderCPPFiles( fc::string directory, fc::string outDirectory )
{
	char buf[255];
	fc::string t, line;
	FileGetter fg( directory.c_str() );

	while( fg.GetNextFile(buf) != 0 )
	{
		t = buf;
		if( t.size() > 2 && t.substr(t.size() - 2) == ".h" )
		{
			t.pop_back();

			FILE* f = fopen( (outDirectory + "/" + t + "cpp").c_str(), "w" );
			line = "\n#include <fc/" + t + "h>\n";
			fwrite( line.data(), line.size(), 1, f );
			fclose(f);
		}

	}
}



////////////////////////////////////////////////////////////////////////////////////
#include <fc/dynamic_array2d.h>
void UntileCharactersImpl( fc::dynamic_array2d<Color>& p )
{
	fc::dynamic_array2d<Color> c = p;
	fc::dynamic_array2d<Color> t(16, 16);

}


void UntileCharacters( fc::string directory, fc::string outDirectory )
{
	char buf[255];
	fc::string t, line;
	FileGetter fg( directory.c_str() );

	while( fg.GetNextFile(buf) != 0 )
	{
		t = buf;
		if( t.size() > 4 && t.substr(t.size() - 4) == ".png" )
		{
			Image i(directory + t);
			UntileCharactersImpl(i.GetPixelArray());
		}
	}
}


#include <Catastrophe/IO/File.h>
#include <fc/static_vector.h>
#include <fc/tokenizer.h>

void GenCWrappers()
{
	GenCWrapper(
		"../Engine/include/Catastrophe/Graphics/SpriteAnimation.h",
		"spriteAnimation.h",
		"SpriteAnimation_",
		" SpriteAnimation* self");
	GenCWrapper(
		"../Engine/include/Catastrophe/Gui/Widget.h",
		"widget.h",
		"Widget_",
		" Widget* self");
	GenCWrapper(
		"C:/C++/include/fc/dynamic_array2d.h",
		"array.h",
		"Array_",
		" Array* self");

}

void GenCWrapper( fc::string filename, fc::string outFn, const char* prefixStr, const char* classPtr )
{
	//const char* classPtr = " _Self* self";
	//const char* prefixStr = "Self_";


	FILE* out = fopen(outFn.c_str(), "wb");
	File f(filename);
	fc::string d;
	fc::string str, e, h, getSet;
	d.reserve(1024 * 1024);
	str.reserve(1024 * 1024);
	e.reserve(4024);
	h.reserve(4024);

	fc::static_vector<fc::string, 16> strArray;

	int braceCount = 0;
	while( f.ReadLine(d) || !f.IsEof() )
	{
		bool isVoid = false;
		bool isImplementation = false;

		if( d.empty() )
			continue;
		if( d[0] == '{' )
			continue;
		if( d.length() <= 1 )
			continue;

		while( !d.empty() && (d[0] == '\t' || d[0] == ' ') )
			d.erase(d.begin(), d.begin()+1);
		if( d.empty() )
			continue;

		if( d[0] == 'v' && d[1] == 'o' )
			isVoid = true;

		else if( d[0] == '{' )
		{
			braceCount++;
			continue;
		}

		if( braceCount > 0 )
		{
			if( d[0] == '}' )
				braceCount--;

			continue;
		}

		size_t pos = d.find_first_not_of("\n\t ");
		if( pos == fc::string::npos )
			continue;

		if( d[pos] == 'c' && d[pos + 1] == 'l' )
			continue;

		if( d[pos] == 't' && d[pos + 1] == 'y' )
			continue;

		if( d[pos] == '/' && d[pos + 1] == '/' )
			continue;

		if( d[pos] == '#' )
			continue;

		size_t last = d.find_first_of(")", pos);
		if( last == fc::string::npos )
			continue;

		++last;

		fc::string s = d.substr( pos, last - pos );
		if( s.empty() )
			continue;

		size_t fp = 0;
		while ( (fp = s.find('&')) != fc::string::npos )
			s.erase(fp, 1);

		while ( (fp = s.find("const ")) != fc::string::npos )
			s.erase(fp, 6);

		while ( (fp = s.find(" const")) != fc::string::npos )
			s.erase(fp, 6);

		while ( (fp = s.find("virtual ")) != fc::string::npos )
			s.erase(fp, 8);

		while ( (fp = s.find("inline ")) != fc::string::npos )
			s.erase(fp, 7);

		while ( (fp = s.find("size_t")) != fc::string::npos )
			s.replace(fp, 6, "int");

		while ( (fp = s.find('\t')) != fc::string::npos )
			s.replace(fp, 1, " ");

		fp = 0;
		while ( (fp = s.find(" =", fp)) != fc::string::npos )
		{
			size_t fp2 = fp;
			fc::string token;
			if( fc::tokenizer::get_token(s, ",)\n", fp2, token) )
			{
				if( token.empty() )
					break;

				if( s[fp2] == ')' )
					fp2--;

				if( fp2 < s.size() )
					s.erase(fp, fp2 - fp);

				fp2++;
			}
			fp++;
		}


		size_t pos4 = s.find_first_of("(");
		if( pos4 == fc::string::npos )
			continue;

		if( pos4 != fc::string::npos )
		{
			if( s[pos4 + 1] != ')' )
				s.insert(pos4 + 1, ",");
			else
				s.insert(pos4 + 1, " ");

			s.insert(pos4 + 1, classPtr);
		}


		e += "[MethodImpl(MethodImplOptions.InternalCall)]\nextern ";
		e += s;
		e += ";\n\n";


		pos = s.find_first_of("(");
		if( pos == fc::string::npos )
			continue;

		size_t pos2 = pos;
		while( pos > 0 && s[pos] != ' ' )
			pos--;

		++pos;
		fc::string funcDecl = s.substr(pos, pos2-pos);

		strArray.clear();
		while( pos2 != fc::string::npos )
		{
			pos2 = s.find_first_of(',', pos2 + 1);
			if( pos2 != fc::string::npos )
			{
				size_t pos1 = pos2;
				while( pos1 > 0 && s[pos1] != ' ' )
					pos1--;

				strArray.push_back( s.substr(pos1+1, pos2 - pos1 - 1) );
			}
		}


		if( funcDecl.size() > 3 )
		{
			if( funcDecl[0] == 'G' && funcDecl[1] == 'e' && funcDecl[2] == 't' )
			{
				fc::string temp( funcDecl.begin() + 3, funcDecl.end() );
				temp += "\n{\n\tget { return ";
				temp += funcDecl;
				temp += "(_ptr); }\n";
				temp += "\tset { ";
				temp += "S";
				temp += funcDecl.begin() + 1;
				temp += "(_ptr, value); }\n}\n\n";

				getSet += s.substr(0, pos);
				getSet += temp;
			}
			else if( funcDecl[0] == 'S' && funcDecl[1] == 'e' && funcDecl[2] == 't' )
			{
			}
			else
			{
				fc::string temp = s;
				size_t p1 = temp.find_first_of('(');
				if( p1 != fc::string::npos )
				{
					p1++;
					if( temp[p1] == ' ' )
						p1++;

					if( temp[p1] != ')' )
					{
						size_t p2 = temp.find_first_of(",)");
						if( p2 != fc::string::npos )
							p2++;

						temp.erase(p1, p2 - p1);
					}
				}

				getSet += temp;
				getSet += "\n{\n\t";
				if( !isVoid )
					getSet += "return ";

				getSet += funcDecl;
				getSet += "(_ptr";
				if( strArray.size() > 1 )
					getSet += ", ";

				for( size_t i(1); i < strArray.size(); ++i )
				{
					getSet += strArray[i];
					if( i + 1 < strArray.size() )
						getSet += ", ";
				}
				getSet += ");\n}\n\n";

			}
		}


		s.insert(pos, prefixStr);

		h += "static ";
		h += s;
		h += ";\n";


		s += "\n{\n\t";
		//s += "if( self )\n\t\t";
		//if( !isVoid )
		//	s += "return ";


		if( isVoid )
			s += "CSFML_CALL(";
		else
			s += "CSFML_CALL_RETURN(";

		s += "self, ";
		s += funcDecl;

		s += "(";
		for( size_t i(1); i < strArray.size(); ++i )
		{
			s += strArray[i];
			if( i + 1 < strArray.size() )
				s += ", ";
		}
		s += ")";

		if( !isVoid )
			s += ", 0";

		s += ");\n";

		//if( !isVoid )
		//	s += "\n\t return 0;\n";

		s += "}\n\n\n";

		fwrite(s.c_str(), 1, s.size(), out);

	}

	int len = strlen(classPtr);
	size_t fp = 0;
	while ( (fp = e.find(classPtr)) != fc::string::npos )
		e.replace(fp, len, "IntPtr ptr");


	fwrite(h.c_str(), 1, h.size(), out);
	fwrite(getSet.c_str(), 1, getSet.size(), out);
	fwrite(e.c_str(), 1, e.size(), out);

}




