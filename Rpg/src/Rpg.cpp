

#include <Catastrophe/System.h>

#include "Common.h"
#include "ConfigFile.h"
#include "GlobalSettings.h"
#include "Game.h"

#include "ResourceManager.h"


//for memory leak checking
#include <crtdbg.h>


GlobalSettings g_settings;



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

	ConfigFile* configFile = g_settings.GetConfigFile();
	configFile->Read();

	//commandLine.Process( argc, argv, settings );

}

//temp includes
#include "MonsterData.h"
#include "ItemData.h"


int main(int argc, char* argv[])
{
	// enable memory leak checking.
	static int crtDebugflags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	crtDebugflags |= (crtDebugflags & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
	_CrtSetDbgFlag(crtDebugflags);


	// initialize system and sub-systems.
	System::Init();
	System::InitLogging("debug.log", true);

	// read config file and parse command-line arguments.
	LoadConfigSettings(argc, argv);

	//Game game;
	//if( game.Initialize() != 0 )
	//	return -1;

	ResourceManager rm;

	Window* window = System::CreateWindow();
	if( !window || !window->IsOpen() )
	{
		LogError("Fatal error: Window could not be created.");
		exit(1);
	}

	//ItemList il;
	bool retval;// = ml.DeserializeXml("test.xml");
	//foreachi(i, 10)
	//	il.Add( ItemData() );

	//retval = il.SerializeXml("test.xml");

	MonsterList ml;
	//retval = ml.DeserializeXml("test.xml");
	foreachi(i, 10)
		ml.Add( MonsterData() );

	retval = ml.SerializeXml("test.xml");

	Texture* t = 0;
	t = rm.LoadTexture("../Engine/Tests/tiles.png");
	t = rm.LoadTexture("../Engine/Tests/tiles.png");
	rm.SetBaseDirectory("../Engine/");
	rm.SetTextureDirectory("Tests/");
	t = rm.LoadTexture("tiles.png");
	t = 0;

	rm.DeleteResources();

	// TODO: Need to handle loading +
	// Splash screen here...

	while( !window->RequestClose() )
	{
		window->ClearColor();
		window->Update();


		window->Sleep(16);
		window->SwapBuffers();
	}



	// shut down all sub-systems and release resources.
	System::Terminate();
	return 0;
}


