//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////


#include "Precompiled.h"


#include "DebugConsole.h"


#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


#ifdef _MSC_VER
	#pragma warning ( disable : 4996 )
#endif



DebugConsole::DebugConsole()
{
	InitializeConsole();
}


DebugConsole::~DebugConsole()
{
	FreeConsole();
}


void DebugConsole::InitializeConsole()
{
	const int MAX_CONSOLE_LINES = 512;

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	int hConHandle;
	long lStdHandle;

	AllocConsole();
	SetConsoleTitle("Debug Console");


	// set the screen buffer to be big enough to scroll text
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &console_info );
	console_info.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize( GetStdHandle(STD_OUTPUT_HANDLE), console_info.dwSize );


	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle( STD_OUTPUT_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stdout = *_fdopen( hConHandle, "w" );
	setvbuf( stdout, NULL, _IONBF, 0 );


	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle( STD_INPUT_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stdin = *_fdopen( hConHandle, "r" );
	setvbuf( stdin, NULL, _IONBF, 0 );


	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle( STD_ERROR_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stderr = *_fdopen( hConHandle, "w" );
	setvbuf( stderr, NULL, _IONBF, 0 );


	//for cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	std::ios::sync_with_stdio();
}



#ifdef _MSC_VER
	#pragma warning ( default : 4996 )
#endif


#endif //_WIN32

