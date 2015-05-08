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

CE_NAMESPACE_BEGIN


/// @FreeList
///
/// Implements a singly-linked FreeList structure.
/// The benefits of a FreeList are that it manages used/unused memory chunks in-place, and no
/// other memory allocations are needed to maintain that list.
///
class FreeList
{
public:
	FreeList() : m_next(null) {}

	/// Initializes the FreeList from raw memory of size nBytes.
	FreeList(void* ptrMemory, u32 nBytes, u32 elementSize, u32 alignment = CE_DEFAULT_ALIGN);

	/// Initializes the FreeList from raw memory of size nBytes.
	///
	/// @returns the number of elements in the list.
	u32 Initialize(void* ptrMemory, u32 nBytes, u32 elementSize, u32 alignment = CE_DEFAULT_ALIGN);

	/// Aquire a pointer to the next free block. Returns null if there are no more free blocks.
	void* Aquire()
	{
		if(m_next == null)
			return null;

		FreeList* head = m_next;
		m_next = head->m_next;
		return head;
	}

	/// Returns a memory block previously aquired to the free list.
	void Release(void* ptr)
	{
		ASSERT(ptr != null);

		FreeList* head = (FreeList*)ptr;
		head->m_next = m_next;
		m_next = head;
	}

protected:
	FreeList* m_next;

};


template <u32 NBytes, u32 ElementSize>
class StaticFreeList : public FreeList
{
public:
	StaticFreeList()
		: FreeList()
		{
			FreeList::Initialize(m_stackMemory, NBytes, ElementSize);
		}

protected:
	char m_stackMemory[NBytes];

};



CE_NAMESPACE_END
