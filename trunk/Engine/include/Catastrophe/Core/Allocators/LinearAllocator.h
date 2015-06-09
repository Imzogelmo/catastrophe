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


/// @LinearAllocator
///
/// Allocator similar to a StackAllocator except that the individual allocated
/// chunks cannot be freed.
/// Use "LinearAllocator::Clear();" to reset the allocator.
///

class CE_API LinearAllocator : public Allocator
{
public:

	LinearAllocator();
	LinearAllocator(void* pMemory, u32 nBytes);

	/// Initializes this allocator by giving it a pointer to raw memory.
	void InitializeMemory(void* pMemory, u32 nBytes);

	/// Resets the current offset to the memory buffer.
	/// This will not deallocate nor nullify the memory buffer.
	void Clear();

	/// Allocates raw memory from this allocator.
	///
	/// @param  nBytes - The requested of bytes of memory
	/// @param  alignment - The additional alignment requirements of the memory, if any
	/// @return A pointer to raw block of memory
	///
	void* Allocate( u32 nBytes, u32 alignment = CE_DEFAULT_ALIGN );

	/// Allows the allocator reclaim memory that was allocated by this allocator.
	///
	/// @param  ptr - pointer to block of memory
	/// @param  size - the number of bytes of the memory block
	///
	void Deallocate( void* ptr, u32 size = 0 );

protected:
	LinearAllocator(const LinearAllocator&);
	LinearAllocator& operator =(const LinearAllocator&);

	u8* m_begin;
	u8* m_end;
	u8* m_current;

};



CE_NAMESPACE_END


