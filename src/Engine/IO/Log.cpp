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

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
	#pragma warning ( disable : 4201 )
#endif

#include <stdarg.h> //for va_list

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

	m_console = create_debug_console;
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
