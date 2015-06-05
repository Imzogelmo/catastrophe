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


const char* logLevels[] =
{
	"<DEBUG> ",
	"<INFO> ",
	"<WARNING> ",
	"<ERROR> "
};


Logger Logger::m_instance = Logger();

Logger::Logger() : 
	m_level(0),
	m_file(),
	m_printToStdOut(false),
	m_hasTimestamp(true)
{
}


Logger::~Logger()
{
	Close();
}


void Logger::Close()
{
	m_file.Close();
}


Logger* Logger::GetInstance()
{
	return &m_instance;
}


bool Logger::Open(const String& logFilename, bool writeToStdOut)
{
	if( m_file.IsOpen() )
		return true;

	m_printToStdOut = writeToStdOut;
	if( !logFilename.Empty() )
		m_file.Open(logFilename, FileWrite);

	return m_file.IsOpen();
}


void Logger::Write(int level, const char* message)
{
	if(m_level > level)
		return;

	String formattedString;//(message);
	formattedString.Reserve(Strlen(message) + 16);

	if(m_hasTimestamp)
	{
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		char buffer[64];
		sprintf(buffer, "[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

		formattedString += buffer;
	}

	//formattedString += logLevels[level];
	formattedString += message;
	//formattedString += '\n';

	FlushString(level, formattedString);
}


void Logger::FlushString(int level, const String& formattedString)
{
	if( m_file.IsOpen() )
	{
		m_file.WriteLine(formattedString, true);
		m_file.Flush();
	}

	if( m_printToStdOut )
	{
		fprintf((level > LOG_WARNING) ? stderr : stdout, "%s\n", formattedString.CString());
	}
}


NOINLINE void LogWrite(int level, const char* format, ...)
{
	char buffer[1024];

	va_list args;
	va_start(args, format);
	vsprintf(&buffer[0], format, args);
	va_end(args);

	Logger::GetInstance()->Write(level, buffer);
}


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif




CE_NAMESPACE_END
