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
#include "Catastrophe/Core/Memory.h"

CE_NAMESPACE_BEGIN


class PoolAllocator : public Allocator
{
public:
	struct PoolAllocatorHeader
	{
		PoolAllocatorHeader* next;
	};

	PoolAllocator();
	PoolAllocator( void* ptrMemory, u32 nBytes, u32 objectSize, u32 alignment = CE_DEFAULT_ALIGN );

	/// Initializes the memory pool from raw memory of size nBytes.
	///
	/// @param  ptrMemory - A pointer to a raw memory buffer
	/// @param  nBytes - The length in bytes of raw memory
	/// @param  objectSize - The size in bytes of the object this allocator is pooling
	/// @param  alignment - The additional alignment requirements of the memory, if any
	/// @return The number of blocks that can be obtained from this memory pool at once.
	///
	/// 	 Usage:
	/// 	 void* p = Memory::Allocate(1024 * sizeof(RoboTron2084));
	/// 	 if( mPool.InitializeMemory(p, 1024 * sizeof(RoboTron2084), sizeof(RoboTron2084)) != 1024 )
	/// 	     Assert(false && "Not enough memory for 1024 objects, Make sure object size is at least sizeof(void*)");
	///
	u32 InitializeMemory( void* ptrMemory, u32 nBytes, u32 objectSize, u32 alignment = CE_DEFAULT_ALIGN );

	/// Allocates raw memory from this allocator.
	/// If the pool is empty it will return null, or an Assertion will be triggered.
	///
	/// @return A pointer to raw block of pooled memory
	///
	void* Allocate( u32 /*nBytes*/ = 0, u32 /*alignment*/ = 0 );

	/// Give back a chunk of the memory pool that was given out by this allocator.
	/// If the memory was not allocated by this allocator an Assertion is raised.
	///
	/// @param  ptr - pointer to block of memory
	/// @param  size - unused
	///
	void Deallocate( void* ptr, u32 /*size*/ = 0 );

	/// True if every block in the memory pool is in use.
	bool OutOfMemory() const;

	/// True if this pool owns the memory pointed to by 'pMemoryBlock'.
	bool OwnsMemoryBlock( void* pMemoryBlock ) const;

	/// Returns a pointer to the allocated block of memory used by this pool.
	void* GetRawMemoryPtr() const { return m_poolBegin; }

	u32 GetNumUsedBlocks() { return m_usedBlocks; }

	bool operator ==( const PoolAllocator& allocator ) const { return &allocator == this; }
	bool operator ==( const Allocator& ) const { return false; }

protected:
	PoolAllocator(const PoolAllocator&);
	PoolAllocator& operator =(const PoolAllocator&);

	PoolAllocatorHeader* m_head;
	void* m_poolBegin;
	void* m_poolEnd;
	u32 m_usedBlocks;

};



CE_NAMESPACE_END
