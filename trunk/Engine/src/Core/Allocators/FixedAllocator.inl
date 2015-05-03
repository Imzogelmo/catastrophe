

#include "Core/Allocators/FixedAllocator.h"

CE_NAMESPACE_BEGIN



void* FixedAllocator::Allocate( u32 nBytes, u32 alignment )
{
	if( m_size == 0 && nBytes <= N )
	{
		m_size = nBytes;
		return (void*)m_buffer;
	}

	return Allocator::Allocate( nBytes, alignment );
}


void FixedAllocator::Deallocate( void* ptr, u32 size )
{
	// If an object deallocates an internal buffer then it can
	// be safely assumed that it is no longer in use.
	if( ptr == m_buffer )
	{
		CE_ASSERT(m_size == size);
		m_size = 0;
	}

	Allocator::Deallocate( ptr, size );
}


CE_NAMESPACE_END
