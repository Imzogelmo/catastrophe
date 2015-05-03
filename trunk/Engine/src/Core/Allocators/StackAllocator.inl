

#include "Core/PlatformMemory.h"
#include "Core/Allocators/StackAllocator.h"

CE_NAMESPACE_BEGIN



StackAllocator::StackAllocator() :
m_begin(null), m_end(null), m_current(null)
{
}


StackAllocator::StackAllocator( void* ptrMemory, u32 nBytes ) :
m_begin(null), m_end(null), m_current(null)
{
	InitializeMemory( ptrMemory, nBytes );
}


void StackAllocator::InitializeMemory( void* ptrMemory, u32 nBytes )
{
	CE_ASSERT(m_begin == null);
	CE_ASSERT(nBytes != 0 && ptrMemory != null);

	m_begin = m_current = (u8*)ptrMemory;
	m_end = m_begin + nBytes;

	Debug(Memory::Memset(ptrMemory, (u8)0xFE, nBytes));
}


void* StackAllocator::Allocate( u32 nBytes, u32 alignment )
{
	u8* p = m_current;
	nBytes = Align( nBytes, alignment );

	CE_ASSERT(m_current + nBytes <= m_end);
	if( m_current + nBytes > m_end )
		return null;

	m_current += nBytes;
	return p;
}


bool StackAllocator::CanAllocate( u32 nBytes ) const
{
	return (m_current + nBytes <= m_end);
}


void StackAllocator::Unwind(const void* ptrStackPosition)
{
	CE_ASSERT(ptrStackPosition >= m_begin && ptrStackPosition < m_end);
	Debug(Memory::Memset(m_current, (u8)0xFE, u32(m_current - (u8*)ptrStackPosition)));

	m_current = ptrStackPosition;
}



CE_NAMESPACE_END



