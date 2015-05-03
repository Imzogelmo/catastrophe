//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Common.h"
#include "Catastrophe/Core/Memory.h"

CE_NAMESPACE_BEGIN



// FixedAllocator
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

	void* Allocate( u32 nBytes, u32 alignment = 0 )
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
		if( ptr == m_buffer )
		{
			CE_ASSERT(size == 0 || m_size == size);
			m_size = 0;
		}

		Allocator::Deallocate( ptr, size );
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

