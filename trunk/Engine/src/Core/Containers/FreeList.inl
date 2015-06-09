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
#include "Catastrophe/Core/Containers/FreeList.h"

CE_NAMESPACE_BEGIN



u32 FreeList::Initialize( void* ptrMemory, u32 nBytes, u32 objectSize, u32 alignment )
{
	u32 numBlocksAvailable = 0;

	if( objectSize < sizeof(void*) )
		objectSize = sizeof(void*);

	// align object size and memory ptr.
	objectSize = Memory::Align(objectSize, alignment);
	ptrMemory = Memory::Align(ptrMemory, alignment);

	// make sure we have enough room for objects.
	nBytes = (nBytes - (nBytes % objectSize));

	FreeList* p = m_next = (FreeList*)ptrMemory;
	for( u32 i(0); i < nBytes; i += objectSize )
	{
		if( (i + objectSize) <= nBytes )
		{
			p->m_next = (FreeList*)((u32)ptrMemory + i);
			p = p->m_next;

			numBlocksAvailable++;
		}
	}

	p->m_next = null;

	return numBlocksAvailable;
}


CE_NAMESPACE_END

