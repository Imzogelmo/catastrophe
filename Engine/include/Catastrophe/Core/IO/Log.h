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

#include "Catastrophe/Core/IO/File.h"

CE_NAMESPACE_BEGIN



class CE_API Logger
{
public:
	Logger();
	~Logger();

	static Logger* GetInstance();

	bool Open(const String& filename, bool writeToStdOut);
	void Close();

	void Write(int level, const char* message);

	int GetLevel() const { return m_level; }
	void SetLevel( int value ) { m_level = value; }

	bool GetHasTimestamp() const { return m_hasTimestamp; }
	void SetHasTimestamp( bool value ) { m_hasTimestamp = value; }

private:
	void FlushString(int level, const String& formattedString);

	File			m_file;
	int				m_level;
	bool			m_printToStdOut;
	bool			m_hasTimestamp;

	static Logger	m_instance;
};



CE_NAMESPACE_END

