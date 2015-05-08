//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Memory.h"
#include "Catastrophe/Core/Allocators/PoolAllocator.h"

CE_NAMESPACE_BEGIN


PoolAllocator::PoolAllocator()
	: Allocator(), m_head(null), m_poolBegin(null), m_poolEnd(null)
{
}


PoolAllocator::PoolAllocator( void* ptrMemory, u32 nBytes, u32 objectSize, u32 alignment )
	: Allocator()
{
	InitializeMemory( ptrMemory, nBytes, objectSize, alignment );
}


u32 PoolAllocator::InitializeMemory( void* ptrMemory, u32 nBytes, u32 objectSize, u32 alignment )
{
	u32 numBlocksAvailable = 0;

	// requirement for pool allocators.
	if( objectSize < sizeof(void*) )
		objectSize = sizeof(void*);

	// align object size and memory ptr.
	objectSize = Memory::Align( objectSize, alignment );
	ptrMemory = Memory::Align( ptrMemory, alignment );

	// make sure we have enough room for objects.
	nBytes = (nBytes - (nBytes % objectSize));

	PoolAllocatorHeader* p = m_head = (PoolAllocatorHeader*)ptrMemory;
	for( u32 i(0); i < nBytes; i += objectSize )
	{
		if( (i + objectSize) <= nBytes )
		{
			p->next = (PoolAllocatorHeader*)((u32)ptrMemory + i);
			p = p->next;

			numBlocksAvailable++;
		}
	}

	m_poolBegin = ptrMemory;
	m_poolEnd = (void*)((u32)m_poolBegin + nBytes);
	p->next = null;

	return numBlocksAvailable;
}


void* PoolAllocator::Allocate( u32 /*n*/, u32 /*alignment*/ )
{
	CE_ASSERT(!OutOfMemory());

	PoolAllocatorHeader* p = (PoolAllocatorHeader*)m_head;
	if( p != null )
	{
		m_head = m_head->next;
		m_usedBlocks++;
	}

	return (void*)p;
}


void PoolAllocator::Deallocate( void* ptr, u32 /*size*/ )
{
	bool isMemoryChunkValid = OwnsMemoryBlock(ptr);
	CE_ASSERT(isMemoryChunkValid);

	if( isMemoryChunkValid )
	{
		PoolAllocatorHeader* p = m_head;
		m_head = (PoolAllocatorHeader*)ptr;
		m_head->next = p;
		m_usedBlocks--;
	}
}


bool PoolAllocator::OutOfMemory() const
{
	return m_head == null;
}


bool PoolAllocator::OwnsMemoryBlock( void* pMemoryBlock ) const
{
	return (pMemoryBlock >= m_poolBegin && pMemoryBlock < m_poolEnd);
}



CE_NAMESPACE_END
