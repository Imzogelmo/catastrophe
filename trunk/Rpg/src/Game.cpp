
#include "Game.h"



int Game::Initialize()
{
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

	engine->Initialize();
	engine->SetDefaultEngineProperties();
	engine->RegisterScriptingInterfaces();

	//WIP build - this will be removed later
	Log( "Compiling scripts..." );
	for( bool exit(false); exit != true; )
	{
		if( engine->Compile("Scripts/Main.cpp", fc::vector<fc::string>()) != 0 )
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

