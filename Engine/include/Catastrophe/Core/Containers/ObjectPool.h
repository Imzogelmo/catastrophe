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
#include "Catastrophe/Core/Allocators/Allocator.h"
#include "Catastrophe/Core/Allocators/PoolAllocator.h"

CE_NAMESPACE_BEGIN



/// @ObjectPoolBase
///
/// Base class for object pools. Holds and manages a pool allocator and backing memory allocator.
/// Manages memory and related functionality in a non-templated manner to reduce bloat.
///

class ObjectPoolBase
{
public:

	ObjectPoolBase();
	~ObjectPoolBase();

	/// Deallocates any memory allocated by this pool.
	/// This does not destruct any instances of objects using the pool, and will
	/// warn or assert if there are any unreleased objects.
	NOINLINE void DeallocateMemory();

	/// Resizes the object pool. Will deallocate previous memory.
	NOINLINE void Resize(u32 capacity, u32 objectSize, u32 alignment = CE_DEFAULT_ALIGN);

	/// True if all the objects in this pool are free.
	bool Empty() const
	{
		return m_pool.GetNumUsedBlocks() == 0;
	}

	/// True if all the objects in this pool are in use.
	bool Full() const
	{
		return m_pool.OutOfMemory();
	}

	/// Gets the total number of objects that can be created.
	u32 Capacity() const
	{
		return m_pool.GetNumUsedBlocks();
	}

	/// Gets the number of currently used objects created by this pool.
	u32 GetUsedObjectCount() const
	{
		return m_pool.GetNumUsedBlocks();
	}

	/// Gets the remaining number of objects this pool can create.
	u32 GetFreeObjectCount() const
	{
		return m_capacity - m_pool.GetNumUsedBlocks();
	}

protected:
	ObjectPoolBase(const ObjectPoolBase&);
	ObjectPoolBase& operator =(const ObjectPoolBase&);

	u32				m_capacity;
	u32				m_objectSize;
	Allocator*		m_allocator;
	PoolAllocator	m_pool;

};



/// @ObjectPool
///
/// Defines a dynamically-sized object pool using heap memory.
/// An ObjectPool allows objects of the same type to be 'pooled' together
/// using the same raw memory buffer which can improve cache coherance
/// and performance at the cost of some potentially unused memory blocks.
/// Internally all object memory locations are stored as a free list
/// and objects have very fast O(1) allocation and deallocation.
///

template <class T>
class ObjectPool : public ObjectPoolBase
{
public:

	ObjectPool()
		: ObjectPoolBase()
	{
	}

	/// Resizes the object pool so that it can create a number of objects up to a maximum
	/// specified by capacity. The pool cannot safely be resized if any objects created by the pool
	/// remain unreleased, as this will mean all unreleased objects will be using memory that
	/// was destroyed. Will assert if GetUsedObjectCount() returns non-zero.
	void Resize(u32 capacity)
	{
		ObjectPoolBase::Resize(capacity, sizeof(T), CE_ALIGNOF(T));
	}

	/// Creats a default-constructed object and returns a pointer to it.
	/// Returns null if there is no free memory in the pool.
	T* CreateObject()
	{
		void* object = m_pool.Allocate();
		if(object != null)
			new (object) T();

		return (T*)object;
	}

	/// Creates an object constructed to value and returns a pointer to it.
	/// Returns null if there is no free memory in the pool.
	T* CreateObject(const T& value)
	{
		void* object = m_pool.Allocate();
		if(object != null)
			new (object) value;

		return (T*)object;
	}

	/// Destroys an object and allows the object pool to reclaim its memory.
	void ReleaseObject(T* object)
	{
		Memory::Destroy(object);
		m_pool.Deallocate(object);
	}

};



CE_NAMESPACE_END
