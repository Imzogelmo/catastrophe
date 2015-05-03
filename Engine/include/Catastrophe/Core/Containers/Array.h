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
#include "Catastrophe/Core/Iterator.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Allocators/Allocator.h"

CE_NAMESPACE_BEGIN


///
/// @Array
///
/// A simple resizable, dynamic array.
///

template <class T>
class Array
{
public:
	typedef T							ElementType;
	typedef T*							Iterator;
	typedef const T*					ConstIterator;
	typedef T&							Reference;
	typedef const T&					ConstReference;
	typedef ReverseIterator<const T*>	ConstReverseIterator;
	typedef ReverseIterator<T*>			ReverseIterator;

	Array()
		: m_data(null), m_size(0), m_allocator(Memory::GetDefaultAllocator())
		{
		}

	explicit Array(Allocator* allocator)
		: m_data(null), m_size(0), m_allocator(allocator)
		{
			CE_ASSERT(allocator != null);
		}

	explicit Array(u32 numElements, const T& value = T(), Allocator* allocator = Memory::GetDefaultAllocator())
		: m_data(null), m_size(0), m_allocator(allocator)
		{
			m_data = AllocateFill(numElements, value);
			m_size = numElements;
		}

	template <class ForwardIterator>
	Array(ForwardIterator first, ForwardIterator last)
		: m_data(null), m_size(0), m_allocator(Memory::GetDefaultAllocator())
		{
			const u32 numElements = (u32)IteratorDistance(first, last);
			m_data = AllocateCopy(numElements, first, last);
			m_size = numElements;
		}

	Array(const Array<T>& x)
		: m_data(null), m_size(0), m_allocator(null)
		{
			Allocator* pAllocator = x.GetAllocator();
			if(pAllocator->AllowPropagation())
			{
				m_allocator = pAllocator;
			}
			else
			{
				m_allocator = Memory::GetDefaultAllocator();
			}

			*this = x;
		}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return m_allocator; }

	/// Set the allocator used by this container.
	void SetAllocator( Allocator* allocator ) { m_allocator = allocator; }

	bool Empty() const { return m_size == 0; }
	u32 Size() const { return m_size; }

	T* data() { return m_data; }
	const T* data() const { return m_data; }

	Iterator begin()				{ return m_data; }
	Iterator end()					{ return m_data + m_size; }
	ConstIterator begin() const		{ return m_data; }
	ConstIterator end() const		{ return m_data + m_size; }

	ReverseIterator rend()				{ return ReverseIterator(begin()); }
	ConstReverseIterator rend() const	{ return ConstReverseIterator(begin()); }
	ReverseIterator rbegin()			{ return ReverseIterator(end()); }
	ConstReverseIterator rbegin() const	{ return ConstReverseIterator(end()); }

	ElementType& operator[](u32 index) { return m_data[index]; }
	const ElementType& operator[](u32 index) const { return m_data[index]; }

	T& at(u32 index)
	{
		CE_ASSERT(index < Size());
		return m_data[index];
	}

	const T& at(u32 index) const
	{
		CE_ASSERT(index < Size());
		return m_data[index];
	}

	bool IteratorIsValid(ConstIterator it) const
	{
		return (it >= begin() && it <= end());
	}

	void Fill(const T& value)
	{
		Algorithm::FillValues(m_data, m_size, value);
	}

	NOINLINE void Resize(u32 newSize, const T& value = T())
	{
		if(LIKELY(newSize != m_size))
		{
			const u32 minSize = m_size < newSize ? m_size : newSize;
			T* newData = AllocateCopy(newSize, m_data, m_data + minSize);

			if(newSize > m_size)
				Memory::UninitializedFillValues(newData + m_size, newSize - minSize, value);

			Memory::DestroyRange(m_data, m_data + m_size);
			Deallocate();

			m_data = newData;
			m_size = newSize;
		}
	}

	template <class ForwardIterator>
	NOINLINE void Assign(ForwardIterator first, ForwardIterator last)
	{
		const u32 numElements = (u32)IteratorDistance(first, last);
		if(numElements != m_size)
		{
			T* newData = AllocateCopy(numElements, first, last);
			Memory::DestroyRange(m_data, m_data + m_size);
			Deallocate();
			m_data = newData;
			m_size = numElements;
		}
		else
		{
			Algorithm::Copy(first, last, m_data);
		}
	}

	Array<T> &operator =(const Array<T> &x)
	{
		if(this != &x)
			Assign(x.m_data, x.m_data + x.m_size);

		return *this;
	}

protected:
	T* Allocate(u32 numElements)
	{
		return (T*)(numElements ? m_allocator->Allocate(numElements * sizeof(T)) : null);
	}

	void Deallocate()
	{
		if(m_data != null)
			m_allocator->Deallocate(m_data, m_size * sizeof(T));
	}

	template <class ForwardIterator>
	T* AllocateCopy(u32 newCapacity, ForwardIterator first, ForwardIterator last)
	{
		T* p = Allocate(newCapacity);
		Memory::UninitializedCopy(first, last, p);
		return p;
	}

	T* AllocateFill(u32 newCapacity, const T& value)
	{
		T* p = Allocate(newCapacity);
		Memory::UninitializedFillValues(p, newCapacity, value);
		return p;
	}

	T* m_data;
	u32 m_size;
	Allocator* m_allocator;
};


template <class T> inline
	bool operator ==(const Array<T>& a, const Array<T>& b)
	{
		return(&a == &b || (a.Size() == b.Size() && Algorithm::Equal(a.begin(), a.end(), b.begin())));
	}

template <class T> inline
	bool operator !=(const Array<T>& a, const Array<T>& b)
	{
		return !(a == b);
	}


CE_NAMESPACE_END
