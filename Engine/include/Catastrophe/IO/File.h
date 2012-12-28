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

#include "Deserializer.h"
#include "Serializer.h"

CE_NAMESPACE_BEGIN


enum FileMode
{
	FileRead = 0,
	FileReadText,
	FileWrite,
	FileWriteText,
	FileReadWrite,
	FileReadBinary = FileRead,
	FileWriteBinary = FileWrite
};


class CE_API File : public Deserializer, public Serializer
{
public:
	File();
	File(const fc::string& fileName, FileMode mode = FileRead);
	virtual ~File();

	virtual size_t Read(void* dest, size_t size);
	virtual size_t Seek(size_t position);
	virtual size_t Write(const void* data, size_t size);

	bool Open(const fc::string& fileName, FileMode mode = FileRead);
	void Close();
	void Flush();

	const fc::string& GetFileName() const { return m_filename; }
	
	FileMode GetMode() const { return m_mode; }
	bool IsOpen() const { return m_handle != 0; }
	void* GetHandle() const { return m_handle; }
	size_t Size() const { return m_size; }
	size_t Position() const { return m_position; }
	bool IsEof() const { return m_position >= m_size; }
	bool Eof() const { return IsEof(); }

	fc::string GetNativePath(const fc::string& path);

private:
	FileMode	m_mode;
	void*		m_handle;
	size_t		m_position;
	size_t		m_size;
	size_t		m_offset; //for packfiles
	fc::string	m_filename;

};


CE_NAMESPACE_END
