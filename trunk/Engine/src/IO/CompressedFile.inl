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
#include "IO/CompressedFile.h"
#include "IO/Log.h"
#include "IO/LZ4.h"

#include <cstdio>

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


CompressedFile::CompressedFile() :
	File(),
	m_buffer()
{
}


CompressedFile::CompressedFile( const String& filename, FileMode mode ) :
	File(),
	m_buffer()
{
	Open(filename, mode);
}


CompressedFile::~CompressedFile()
{
	//Close();
}


bool CompressedFile::Open( const String& filename, FileMode mode )
{
	File::Open(filename, mode);

	if( mode == FileRead || mode == FileReadText )
	{
		// Read and uncompress the file contents to a memory buffer
		if( IsOpen() )
		{
			u32 uncompressedSize = 0;
			u32 compressedSize = 0;

			if( File::Read(&uncompressedSize, 4) && File::Read(&compressedSize, 4) )
			{
				u32 pos = File::Position();
				u32 size = m_size - pos;
				u8* p = (u8*)fc::allocate(compressedSize + 8);

				File::Read(p, size);
				File::Seek(pos);

				m_buffer.Resize(uncompressedSize);
				if( LZ4::DecompressData(m_buffer.GetData(), p, uncompressedSize) != compressedSize )
				{
					LogError("Error reading file %s, Compressed data possibly corrupted. ");
				}

				fc::deallocate(p);
			}
		}
	}

	return true;
}


u32 CompressedFile::Read( void* dest, u32 size )
{
	CE_ASSERT(m_mode != FileWrite);
	CE_ASSERT(size != 0);
	CE_ASSERT(size + m_position <= m_size);

	return m_buffer.Read(dest, size);
}


u32 CompressedFile::Write( const void* data, u32 size )
{
	CE_ASSERT(m_mode != FileRead);
	if(size == 0)
		return 0;

	return m_buffer.Write(data, size);
}


void CompressedFile::Close()
{
	if( !IsOpen() || m_mode != FileWrite )
		return;

	if( m_buffer.Size() == 0 )
	{
		u32 zero = 0;
		File::Write(&zero, 4);
		File::Write(&zero, 4);
	}
	else
	{
		u32 uncompressedSize = m_buffer.Size();
		u32 compressionBounds = LZ4::GetCompressionBounds(uncompressedSize);

		u8* p = (u8*)fc::allocate(compressionBounds);
		u32 compressedSize = LZ4::CompressData(p, m_buffer.GetData(), uncompressedSize);

		File::Write(&uncompressedSize, 4);
		File::Write(&compressedSize, 4);
		File::Write(p, compressedSize);

		fc::deallocate(p);
	}

	File::Close();
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif

CE_NAMESPACE_END
