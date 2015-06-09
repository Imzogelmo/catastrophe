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

#include "Catastrophe/Core/Memory.h"
#include "Catastrophe/Core/Containers/ObjectPool.h"

CE_NAMESPACE_BEGIN


ObjectPoolBase::ObjectPoolBase() :
	m_capacity(0),
	m_objectSize(0),
	m_allocator(Memory::GetDefaultAllocator()),
	m_pool()
{
}


ObjectPoolBase::~ObjectPoolBase()
{
	DeallocateMemory();
}


void ObjectPoolBase::DeallocateMemory()
{
	if(m_capacity != 0)
	{
		// Notify of possible memory corruption.
		if(m_pool.GetNumUsedBlocks() != 0)
			LogError("ObjectPool was destroyed with %d objects in use.", m_pool.GetNumUsedBlocks());

		m_allocator->Deallocate(m_pool.GetRawMemoryPtr(), m_objectSize * m_capacity);
		m_capacity = 0;
	}
}


void ObjectPoolBase::Resize(u32 capacity, u32 objectSize, u32 alignment)
{
	ASSERT(GetUsedObjectCount() == 0);
	if(GetUsedObjectCount() != 0)
		return;

	if(m_capacity == capacity && m_objectSize == objectSize)
		return;

	m_objectSize = objectSize;
	if(m_capacity != 0)
		m_allocator->Deallocate(m_pool.GetRawMemoryPtr(), objectSize * m_capacity);

	u32 nBytes = 0;
	void* pMemory = null;

	m_capacity = capacity;
	if(capacity != 0)
	{
		nBytes = Memory::Align(objectSize * capacity, alignment);
		pMemory = m_allocator->Allocate(nBytes, alignment);
	}

	// Initialize the pool allocator and let it do all of the work.
	m_pool.InitializeMemory(pMemory, nBytes, objectSize, alignment);
}



CE_NAMESPACE_END
