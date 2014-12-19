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

#include "Serializer.h"
#include "Deserializer.h"

#include <fc/vector.h>

CE_NAMESPACE_BEGIN

/* @FileBuffer
 * File class that writes to an internal buffer.
 *
 */
class FileBuffer : public Deserializer, public Serializer
{
public:
	typedef fc::vector<u8> vec_type;

	FileBuffer();
	FileBuffer( const void* data, u32 size );

	virtual u32 Read( void* dest, u32 size );
	virtual u32 Write( const void* data, u32 size );
	virtual u32 Seek( u32 position );

	virtual void SetData( const void* data, u32 size );
	virtual void Clear();
	virtual void Reserve( u32 capacity );
	virtual void Resize( u32 size );
	virtual bool IsEof() const { return m_position >= m_buffer.size(); }
	virtual u32 Size() const { return m_buffer.size(); }
	virtual u32 Position() const { return m_position; }

	const void* GetData() const { return (void*)(m_buffer.empty() ? null : &m_buffer[0]); }
	void* GetData() { return (void*)(m_buffer.empty() ? null : &m_buffer[0]); }
	
protected:
	vec_type	m_buffer;
	u32			m_position;

};



CE_NAMESPACE_END
