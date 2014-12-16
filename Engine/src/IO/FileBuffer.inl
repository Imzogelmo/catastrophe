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
#include "IO/FileBuffer.h"
#include <cstring>

CE_NAMESPACE_BEGIN


FileBuffer::FileBuffer() :
	m_buffer(),
	m_position(0)
{
}


FileBuffer::FileBuffer( const void* data, u32 size ) :
	m_buffer(),
	m_position(0)
{
	SetData(data, size);
}


u32 FileBuffer::Read( void* dest, u32 size )
{
	CE_ASSERT(dest != null);

	if( size > 0 )
	{
		if( size + m_position > m_buffer.size() )
			size = m_buffer.size() - m_position;

		if( size > sizeof(u64) )
		{
			memcpy(dest, &m_buffer[m_position], size);
		}
		else
		{
			u8* src = &m_buffer[m_position];
			u8* p = (u8*)dest;
			for( u32 i(0); i < size; ++i )
			{
				p[i] = src[i];
			}
		}
	}

	m_position += size;
	return size;
}


u32 FileBuffer::Write( const void* data, u32 size )
{
	CE_ASSERT(data != null);

	if( size > 0 )
	{
		const u32 bufferSize = m_buffer.size();

		// Optimized for the most common usage.
		if( m_position == bufferSize )
		{
			m_buffer.push_back_uninitialized(size);
		}
		else if( m_position + size > bufferSize )
		{
			const u32 difference = (m_position + size) - bufferSize;
			m_buffer.push_back_uninitialized(difference);
		}

		if( size > sizeof(u64) )
		{
			memcpy(&m_buffer[m_position], data, size);
		}
		else
		{
			u8* dest = &m_buffer[m_position];
			u8* src = (u8*)data;
			for( u32 i(0); i < size; ++i )
			{
				dest[i] = src[i];
			}
		}
	}

	m_position += size;
	return size;
}


u32 FileBuffer::Seek( u32 position )
{
	if( position > m_buffer.size() )
		position = m_buffer.size();
	
	m_position = position;
	return m_position;
}


void FileBuffer::SetData( const void* data, u32 size )
{
	Clear();
	Write(data, size);
}


void FileBuffer::Clear()
{
	m_buffer.clear();
	m_position = 0;
}


void FileBuffer::Reserve( u32 capacity )
{
	m_buffer.reserve(capacity);
}


void FileBuffer::Resize( u32 size )
{
	m_buffer.resize(size, 0);
	if( m_position > m_buffer.size() )
		m_position = m_buffer.size();
}



CE_NAMESPACE_END
