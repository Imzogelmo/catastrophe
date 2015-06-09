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

#include "Core/PlatformMemory.h"
#include "Core/Allocators/LinearAllocator.h"

CE_NAMESPACE_BEGIN


LinearAllocator::LinearAllocator() :
	Allocator(),
	m_begin(null),
	m_end(null),
	m_current(null)
{
}


LinearAllocator::LinearAllocator(void* pMemory, u32 nBytes) :
	Allocator(),
	m_begin(null),
	m_end(null),
	m_current(null)
{
	InitializeMemory(pMemory, nBytes);
}


void LinearAllocator::InitializeMemory(void* pMemory, u32 nBytes)
{
	m_begin = (u8*)pMemory;
	m_end = (u8*)pMemory + nBytes;
	m_current = (u8*)pMemory;
}


void LinearAllocator::Clear()
{
	m_current = m_begin;
}


void* LinearAllocator::Allocate(u32 nBytes, u32 alignment /*= CE_DEFAULT_ALIGN */)
{
	u8* ptrCurrent = (u8*)Memory::Align(m_current, alignment);

	if(ptrCurrent + nBytes <= m_end)
	{
		m_current = ptrCurrent + nBytes;
		return ptrCurrent;
	}

	// Out of memory
	return null;
}


void LinearAllocator::Deallocate(void* ptr, u32 /*= 0 */)
{
	ASSERT((u8*)ptr >= m_begin && (u8*)ptr < m_end);

	// Do nothing.
	// Individual blocks cannot be freed.
}


CE_NAMESPACE_END


