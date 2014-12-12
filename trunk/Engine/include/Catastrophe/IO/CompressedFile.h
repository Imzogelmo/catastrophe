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

#include <fc/vector.h>

#include "File.h"
#include "FileBuffer.h"

CE_NAMESPACE_BEGIN


// TODO: CompressedFile should inherit from FileBuffer, not file...

class CompressedFile : public File
{
public:
	CompressedFile();
	CompressedFile( const String& filename, FileMode mode = FileRead );
	virtual ~CompressedFile();

	virtual u32 Read( void* dest, u32 size );
	virtual u32 Write( const void* data, u32 size );
	//virtual u32 Seek( u32 position );

	virtual bool Open( const String& filename, FileMode mode = FileRead );
	virtual void Close();

	virtual u32 Size() const { return m_buffer.Size(); }
	virtual u32 Position() const { return m_buffer.Position(); }

protected:
	FileBuffer m_buffer;

};



CE_NAMESPACE_END
