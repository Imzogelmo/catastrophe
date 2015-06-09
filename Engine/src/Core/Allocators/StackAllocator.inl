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
	nBytes = Memory::Align( nBytes, alignment );

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

	m_current = (u8*)ptrStackPosition;
}



CE_NAMESPACE_END



