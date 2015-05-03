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

#include "memory.h"

FC_NAMESPACE_BEGIN


// temporary_buffer
//
// Implements a simple non-shared buffer of temporary memory, that is,
// transfering of buffer memory is strictly prohibited.

template <class T>
class TemporaryBuffer
{
public:
	typedef T ValueType;

	explicit TemporaryBuffer( u32 n )
	{
		m_begin = (T*)fc::allocate_temporary( n * sizeof(T), FC_ALIGNOF(T) );
		m_end = m_begin + n;
	}

	template <class ForwardIterator>
	TemporaryBuffer( ForwardIterator first, ForwardIterator last )
	{
		const u32 n = IteratorDistance(first, last);
		m_begin = (T*)fc::allocate_temporary( n * sizeof(T), FC_ALIGNOF(T) );
		m_end = m_begin + n;

		fc::uninitialized_copy( first, last, m_begin );
	}

	~TemporaryBuffer()
	{
		if( m_begin != null )
		{
			fc::destroy_range( m_begin, m_end );
			fc::deallocate_temporary( m_begin, (m_end - m_begin) * sizeof(T) );
		}
	}

	u32 Size() const { return u32(m_end - m_begin); }

	T* begin() { return m_begin; }
	T* end() { return m_end; }
	const T* begin() const { return m_begin; }
	const T* end() const { return m_end; }

protected:
	TemporaryBuffer( const TemporaryBuffer<T>& );
	TemporaryBuffer& operator =( const TemporaryBuffer<T>& );

	mutable T* m_begin;
	mutable T* m_end;

};



FC_NAMESPACE_END
