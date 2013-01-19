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

#pragma once

#include <fc/string.h>

#include "File.h"

CE_NAMESPACE_BEGIN

extern void __Internal_Log_Write( const char* format, ... );
extern void __Internal_Log_Write( const fc::string& message );


class CE_API Logger
{
public:
	Logger();
	Logger( const fc::string& filename, bool create_debug_console = true, bool auto_append_new_line = true );
	~Logger();

	static Logger& GetInstance();
	bool Open( const fc::string& filename, bool create_debug_console = true, bool auto_append_new_line = true );
	void Close();

	void Write( const fc::string& message );
	void AppendNewLine( fc::string& str );

	File* GetFile() { return &m_file; }

private:
	void FlushString( const fc::string& str );

	File			m_file;
	bool			m_console;
	bool			m_append_new_line;
	static Logger	m_instance;
};



CE_NAMESPACE_END

