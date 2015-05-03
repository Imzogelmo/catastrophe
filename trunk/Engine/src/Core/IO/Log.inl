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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/IO/Log.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
	#pragma warning ( disable : 4201 )
#endif

#include <time.h>
#include <stdarg.h> //for va_list

CE_NAMESPACE_BEGIN


Logger Logger::m_instance = Logger();

Logger::Logger() : 
	m_file(),
	m_console(false),
	m_append_new_line(true) ,
	m_hasTimestamp(false)
{
}

Logger::Logger( const String& outfilename, bool create_debug_console, bool auto_append_new_line )
{
	m_hasTimestamp = false;
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


bool Logger::Open( const String& outfilename, bool create_debug_console, bool auto_append_new_line )
{
	if( m_file.IsOpen() )
	{
		m_file.WriteString("Log::file_out already initialized...\n");
		return false;
	}

	if( !outfilename.Empty() )
	{
		m_file.Open( outfilename, FileWriteText );
	}

	m_console = create_debug_console;
	m_append_new_line = auto_append_new_line;

	return m_file.IsOpen();
}


void Logger::Write( const String& message )
{
	String str( message );

	if(m_hasTimestamp)
	{
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		char buffer[64];
		sprintf(buffer, "[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

		str += buffer;
	}

	Logger::GetInstance().AppendNewLine( str );
	Logger::GetInstance().FlushString( str );
}


void Logger::AppendNewLine( String& str )
{
	if( m_append_new_line && !str.Empty() )
	{
		if( str.Back() != '\n' )
			str += '\n';
	}
}


void Logger::FlushString( const String& str )
{
	if( m_file.IsOpen() )
	{
		m_file.WriteLine(str, false);
		m_file.Flush();
	}

	if( m_console )
	{
		printf( str.CString() );
	}
}


NOINLINE void __Internal_Log_Write( const char* format, ... )
{
	char buffer[ 1024 ];

	va_list args;
	va_start( args, format );
	vsprintf( &buffer[0], format, args );
	va_end( args );

	Logger::GetInstance().Write( buffer );
}


NOINLINE void __Internal_Log_Write( const String& message )
{
	Logger::GetInstance().Write( message );
}


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif




CE_NAMESPACE_END
