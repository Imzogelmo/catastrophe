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
#include "Catastrophe/Core/Containers/FreeList.h"
#include "Catastrophe/Core/Containers/AlignedBuffer.h"

CE_NAMESPACE_BEGIN


/// @StaticObjectPool
///
/// Defines a statically-sized object pool using stack memory.
/// The pool can never be resized.
///

template <class T, u32 N>
class StaticObjectPool
{
public:

	StaticObjectPool()
		: m_size(0), m_pool(), m_buffer()
	{
		m_pool.Initialize(&m_buffer, sizeof(T) * N, sizeof(T), CE_ALIGNOF(T));
	}

	~StaticObjectPool()
	{
		// Notify of possible memory corruption.
		if(m_size != 0)
			LogError("StaticObjectPool was destroyed with %d objects in use.", m_size);
	}

	/// Creats a default-constructed object and returns a pointer to it.
	T* CreateObject()
	{
		ASSERT(m_size != N);

		++m_size;
		void* object = m_pool.Aquire();
		if(object != null)
			new (object) T();

		return (T*)object;
	}

	/// Creates a object copy-constructed to value and returns a pointer to it.
	T* CreateObject(const T& value)
	{
		ASSERT(m_size != N);

		++m_size;
		void* object = m_pool.Aquire();
		if(object != null)
			new (object) value;

		return (T*)object;
	}

	/// Destroys an object and allows the object pool to reclaim its memory.
	void ReleaseObject(T* object)
	{
		ASSERT(m_size != 0);

		--m_size;
		Memory::Destroy(object);
		m_pool.Release(object);
	}

	/// True if all the objects in this pool are free.
	bool Empty() const
	{
		return m_size == 0;
	}

	/// True if all the objects in this pool are in use.
	bool Full() const
	{
		return m_size == N;
	}

	/// Gets the total number of objects that can be created.
	u32 Capacity() const
	{
		return N;
	}

	/// Gets the number of currently used objects created by this pool.
	u32 GetUsedObjectCount() const
	{
		return m_size;
	}

	/// Gets the remaining number of objects this pool can create.
	u32 GetFreeObjectCount() const
	{
		return N - m_size;
	}

protected:
	StaticObjectPool(const StaticObjectPool&);
	StaticObjectPool& operator =(const StaticObjectPool&);

	u32 m_size;
	FreeList m_pool;
	AlignedBuffer<N, CE_ALIGNOF(T)> m_buffer;

};



CE_NAMESPACE_END
