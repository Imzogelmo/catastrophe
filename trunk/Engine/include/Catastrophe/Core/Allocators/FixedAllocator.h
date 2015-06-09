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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Allocators/Allocator.h"

CE_NAMESPACE_BEGIN



// @FixedAllocator
//
// Allocator that stores a pointer to a user supplied buffer and can otherwise Allocate
// and Deallocate memory as a normal Allocator with the exception that if Deallocate
// is called with a pointer that is equal to the internal buffer pointer, no memory is
// freed. This Allocator is used internally by fixed containers to prevent the possible
// freeing of stack-based memory or corruption of the heap.

template <u32 N>
class FixedAllocator : public Allocator
{
public:
	FixedAllocator() {}

	void* Allocate( u32 nBytes, u32 alignment = CE_DEFAULT_ALIGN )
	{
		if( m_size == 0 && nBytes <= N )
		{
			m_size = nBytes;
			return (void*)m_buffer;
		}

		return Allocator::Allocate( nBytes, alignment );
	}

	void Deallocate( void* ptr, u32 size = 0 )
	{
		// If an object deallocates an internal buffer then it can
		// be safely assumed that it is no longer in use.
		if(ptr == m_buffer)
		{
			m_size = 0;
			return;
		}

		Allocator::Deallocate(ptr, size);
	}

	bool operator ==( const Allocator& ) const
	{
		return false;
	}

protected:
	char m_buffer[N];
	u32 m_size;

};



CE_NAMESPACE_END

