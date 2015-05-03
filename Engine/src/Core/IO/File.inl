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
#include "Catastrophe/Core/IO/File.h"
#include "Catastrophe/Core/IO/Log.h"
#include "Core/StringUtils.h"

#include <cstdio>

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


File::File() :
	m_mode(FileRead),
	m_handle(0),
	m_position(0),
	m_size(0),
	m_offset(0)
{
}


File::File( const String& fileName, FileMode mode ) :
	m_mode(FileRead),
	m_handle(0),
	m_position(0),
	m_size(0),
	m_offset(0)
{
	Open(fileName, mode);
}


File::~File()
{
	Close();
}


bool File::Open( const String& fileName, FileMode mode )
{
	Close();

	const char* FILE_OPEN_MODE[] = { "rb", "r", "wb", "w", "w+b" };
	m_handle = fopen(GetNativePath(fileName).CString(), FILE_OPEN_MODE[mode]);
	if(!m_handle)
	{
		Log("Could not open file " + fileName);
		return false;
	}

	m_filename = fileName;
	m_mode = mode;
	m_position = 0;
	m_offset = 0;

	//get file size
	fseek((FILE*)m_handle, 0, SEEK_END);
	m_size = ftell((FILE*)m_handle);
	fseek((FILE*)m_handle, 0, SEEK_SET);

	return true;
}


u32 File::Read( void* dest, u32 size )
{
	CE_ASSERT(m_mode != FileWrite);
	CE_ASSERT(dest != null);
	CE_ASSERT(size != 0);

	if( size + m_position > m_size )
		size = m_size - m_position;

	if( !m_handle )
	{
		Log("File::Read Error: File not open");
		return 0;
	}

	u32 ret = fread(dest, size, 1, (FILE*)m_handle);
	if( ret != 1 )
	{
		fseek((FILE*)m_handle, m_position + m_offset, SEEK_SET);
		Log("Error reading from file " + GetFileName());
		return 0;
	}

	m_position += size;
	return size;
}


u32 File::Seek( u32 position )
{
	if( m_mode == FileRead && position > m_size )
		position = m_size;

	if( !m_handle )
	{
		Log("Error: File not open");
		return 0;
	}

	fseek((FILE*)m_handle, position + m_offset, SEEK_SET);
	m_position = position;
	return m_position;
}


u32 File::Write( const void* data, u32 size )
{
	CE_ASSERT(m_mode != FileRead);

	if( size > 0 )
	{
		if( m_handle == null )
		{
			Log("Error: File not open");
			return 0;
		}

		if(fwrite(data, size, 1, (FILE*)m_handle) != 1)
		{
			fseek((FILE*)m_handle, m_position + m_offset, SEEK_SET);
			Log("Error writing to file " + GetFileName());
			return 0;
		}

		m_position += size;
		if (m_position > m_size)
			m_size = m_position;
	}

	return size;
}


void File::Close()
{
	if(m_handle)
	{
		fclose((FILE*)m_handle);
		m_handle = 0;
		m_position = 0;
		m_size = 0;
		m_offset = 0;
	}
}


void File::Flush()
{
	if(m_handle)
		fflush((FILE*)m_handle);
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif

CE_NAMESPACE_END
