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

#include "Catastrophe/Core/IO/Deserializer.h"
#include "Catastrophe/Core/IO/Serializer.h"

CE_NAMESPACE_BEGIN


enum FileMode
{
	FileRead,
	FileReadText,
	FileWrite,
	FileWriteText,
	FileReadWrite
};


class CE_API File : public Deserializer, public Serializer
{
public:
	File();
	File( const String& fileName, FileMode mode = FileRead );
	virtual ~File();

	virtual u32 Read( void* dest, u32 size );
	virtual u32 Write( const void* data, u32 size );
	virtual u32 Seek( u32 position );
	virtual u32 Size() const { return m_size; }
	virtual u32 Position() const { return m_position; }

	virtual bool Open( const String& filename, FileMode mode = FileRead );
	virtual void Close();
	virtual void Flush();

	const String& GetFileName() const { return m_filename; }
	
	FileMode GetMode() const { return m_mode; }
	bool IsOpen() const { return m_handle != 0; }
	void* GetHandle() const { return m_handle; }
	bool IsEof() const { return m_position >= m_size; }
	bool Eof() const { return IsEof(); }

protected:
	FileMode	m_mode;
	void*		m_handle;
	u32			m_position;
	u32			m_size;
	u32			m_offset; //for packfiles
	String		m_filename;

};


CE_NAMESPACE_END
