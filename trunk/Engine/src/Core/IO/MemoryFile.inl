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
#include "Catastrophe/Core/IO/MemoryFile.h"
#include <cstring>

CE_NAMESPACE_BEGIN


MemoryFile::MemoryFile() :
	m_buffer(),
	m_position(0)
{
}


MemoryFile::MemoryFile( const void* data, u32 size ) :
	m_buffer(),
	m_position(0)
{
	SetData(data, size);
}


u32 MemoryFile::Read( void* dest, u32 size )
{
	CE_ASSERT(dest != null);

	if( size > 0 )
	{
		if( size + m_position > m_buffer.Size() )
			size = m_buffer.Size() - m_position;

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


u32 MemoryFile::Write( const void* data, u32 size )
{
	CE_ASSERT(data != null);

	if( size > 0 )
	{
		const u32 bufferSize = m_buffer.Size();

		// Optimized for the most common usage.
		if( m_position == bufferSize )
		{
			m_buffer.AddUninitialized(size);
		}
		else if( m_position + size > bufferSize )
		{
			const u32 difference = (m_position + size) - bufferSize;
			m_buffer.AddUninitialized(difference);
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


u32 MemoryFile::Seek( u32 position )
{
	if( position > m_buffer.Size() )
		position = m_buffer.Size();
	
	m_position = position;
	return m_position;
}


void MemoryFile::SetData( const void* data, u32 size )
{
	Clear();
	Write(data, size);
}


void MemoryFile::Clear()
{
	m_buffer.Clear();
	m_position = 0;
}


void MemoryFile::Reserve( u32 capacity )
{
	m_buffer.Reserve(capacity);
}


void MemoryFile::Resize( u32 size )
{
	m_buffer.Resize(size, 0);
	if( m_position > m_buffer.Size() )
		m_position = m_buffer.Size();
}



CE_NAMESPACE_END
