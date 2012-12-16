

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


Window* CreateWindow()
{
	ConfigSetting* setting = g_settings.GetConfigFile()->GetSettings();

	bool vsync			= setting[ ConfigSetting::Vsync ].value ? true : false;
	bool keep_aspect	= setting[ ConfigSetting::KeepAspect ].value ? true : false;
	bool keep_scale		= setting[ ConfigSetting::KeepScale ].value ? true : false;
	bool antialias		= setting[ ConfigSetting::Antialiasing ].value ? true : false;
	bool fullscreen		= setting[ ConfigSetting::Fullscreen ].value ? true : false;

	int resx			= setting[ ConfigSetting::ResX ].value;
	int resy			= setting[ ConfigSetting::ResY ].value;
	int multisample		= setting[ ConfigSetting::Multisample ].value;
	int scale			= setting[ ConfigSetting::Scale ].value;


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
	System::InitLogging("debug.log", true); //todo put this after config..

	// read config file and parse command-line arguments.
	LoadConfigSettings(argc, argv);

	//Game game;
	//if( game.Initialize() != 0 )
	//	return -1;

	Window* window = CreateWindow();


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


