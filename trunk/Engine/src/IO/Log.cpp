// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Common.h"
#include "IO/Log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


Logger Logger::m_instance = Logger();

Logger::Logger() : 
	m_file(),
	m_console(false),
	m_append_new_line(true) 
{
}

Logger::Logger( const fc::string& outfilename, bool create_debug_console, bool auto_append_new_line )
{
	Open(outfilename, create_debug_console, auto_append_new_line);
}

Logger::~Logger()
{
	Close();
}


void Logger::Close()
{
	m_file.Close();
}


Logger& Logger::GetInstance()
{
	return m_instance;
}


bool Logger::Open( const fc::string& outfilename, bool create_debug_console, bool auto_append_new_line )
{
	if( m_file.IsOpen() )
	{
		m_file.WriteString("Log::file_out already initialized...\n");
		return false;
	}

	if( !outfilename.empty() )
	{
		m_file.Open( outfilename, FileWriteText );
	}

	if( create_debug_console )
	{
		OpenDebugConsole();
		printf("DEBUG CONSOLE\n" );
	}

	m_append_new_line = auto_append_new_line;
	return m_file.IsOpen();
}


void Logger::Write( const fc::string& message )
{
	fc::string str( message );
	Logger::GetInstance().AppendNewLine( str );
	Logger::GetInstance().FlushString( str );
}


void Logger::AppendNewLine( fc::string& str )
{
	if( m_append_new_line && !str.empty() )
	{
		if( str.back() != '\n' )
			str += '\n';
	}
}


void Logger::FlushString( const fc::string& str )
{
	if( m_file.IsOpen() )
	{
		m_file.WriteLine(str, false);
		m_file.Flush();
	}

	if( m_console )
	{
		printf( str.c_str() );
	}
}


void Logger::OpenDebugConsole()
{
	const int MAX_CONSOLE_LINES = 256;

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	int hConHandle;
	long lStdHandle;

	AllocConsole();

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
	m_console = true;
}

void Logger::CloseDebugConsole()
{
	FreeConsole();
	m_console = false;
}


FC_NO_INLINE void __Internal_Log_Write( const char* format, ... )
{
	char buffer[ 1024 ];

	va_list args;
	va_start( args, format );
	vsprintf( &buffer[0], format, args );
	va_end( args );

	Logger::GetInstance().Write( buffer );
}


FC_NO_INLINE void __Internal_Log_Write( const fc::string& message )
{
	Logger::GetInstance().Write( message );
}


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif




CE_NAMESPACE_END
