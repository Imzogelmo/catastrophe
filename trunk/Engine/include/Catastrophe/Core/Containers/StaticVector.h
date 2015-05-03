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
#include "Catastrophe/Core/TypeTraits.h"
#include "Catastrophe/Core/IteratorTraits.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Containers/AlignedBuffer.h"

CE_NAMESPACE_BEGIN


///
/// @StaticVector
///
/// A stack allocated vector container class that can never change capacity
/// and generally generates smaller compiled code than Vector.
/// POD optimization is also supported.
///

template <class T, u32 N>
class StaticVector
{
public:
	typedef T							ElementType;
	typedef T*							Iterator;
	typedef const T*					ConstIterator;

	enum { kMaxCapacity = N };
	typedef AlignedBuffer<(N * sizeof(T)), CE_ALIGNOF(T)> AlignedBufferType;

	StaticVector()
		: m_size(0)
		{
		}

	StaticVector(u32 numElements, const T& value)
		: m_size(0)
		{
			Assign(numElements, value);
		}

	template <class InputIterator>
	StaticVector(InputIterator first, InputIterator last)
		: m_size(0)
		{
			Assign(first, last);
		}

	StaticVector(const StaticVector<T, N>& x)
		: m_size(0)
		{
			Assign(x.begin(), x.end());
		}

	~StaticVector()
		{
			Clear();
		}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return null; }

	/// Set the allocator used by this container.
	void SetAllocator(Allocator*) {}

	bool Empty() const		{ return m_size == 0; }
	bool Full() const		{ return m_size == N; }
	u32 Capacity() const	{ return N; }
	u32 Unused() const		{ return N - m_size; }
	u32 Size() const		{ return m_size; }

	Iterator begin()			{ return (T*)m_buffer.data; }
	Iterator end()				{ return (T*)m_buffer.data + m_size; }
	ConstIterator begin() const	{ return (T*)m_buffer.data; }
	ConstIterator end() const	{ return (T*)m_buffer.data + m_size; }

	u32 size() const		{ return m_size; }
	T* data()				{ return (T*)m_buffer.data; }
	const T* data() const	{ return (T*)m_buffer.data; }

	T& Front()				{ return *((T*)m_buffer.data); }
	const T& Front() const	{ return *((T*)m_buffer.data); }
	T& Back()				{ return *((T*)m_buffer.data + (m_size - 1)); }
	const T& Back() const	{ return *((T*)m_buffer.data + (m_size - 1)); }

	T& operator [](u32 index)
	{
		return *(((T*)m_buffer.data) + index);
	}

	const T& operator [](u32 index) const { return *(((T*)m_buffer.data) + index); }

	T& at(u32 index)
	{
		CE_ASSERT(index < m_size);
		return *(((T*)m_buffer.data) + index);
	}

	const T& at(u32 index) const
	{
		CE_ASSERT(index < m_size);
		return *(((T*)m_buffer.data) + index);
	}

	void ShrinkToFit() {}
	void SetCapacity(u32) {}
	void Reserve(u32)
	{
		// do nothing
	}

	void Clear()
	{
		Memory::DestroyValues((T*)m_buffer.data, m_size);
		m_size = 0;
	}

	void Resize(u32 numElements, const T& value = T())
	{
		CE_ASSERT(numElements <= N);

		if(numElements > m_size)
			Memory::UninitializedFillValues(end(), numElements - m_size, value);

		else if(numElements < m_size)
			Memory::DestroyValues(m_buffer.data + numElements, m_size - numElements);

		m_size = numElements;
	}

	void Assign(u32 numElements, const T& value)
	{
		AssignValues(numElements, value, typename is_pod<T>::type());
	}

	template <class InputIterator>
	void Assign(InputIterator first, InputIterator last)
	{
		AssignDispatch(first, last,
			typename is_integral<InputIterator>::type());
	}

	void InsertAt(u32 position, const T& value) { Insert(begin() + position, value); }
	void InsertAt(u32 position, u32 numElements, const T& value) { Insert(begin() + position, numElements, value); }

	Iterator Insert(Iterator position, const T& value)
	{
		CE_ASSERT(IteratorIsValid(position));

		if(position == (T*)m_buffer.data + m_size)
		{
			Memory::Construct(((T*)m_buffer.data) + (m_size++), value);
		}
		else
		{
			// avoid making a Copy of unknown type if value is in range
			const T* ptrVal = &value;
			if((ptrVal >= position) && (ptrVal < end()))
				++ptrVal;

			T* last = end() - 1;
			Memory::Construct(end(), *(last));
			Algorithm::CopyBackward(position, last, end());
			*position = *ptrVal;
			++m_size;
		}

		return position;
	}

	inline void Insert(Iterator position, u32 numElements, const T& value)
	{
		InsertValues(position, numElements, value,
			typename is_pod<T>::type());
	}

	template <class InputIterator> inline
	void Insert(Iterator position, InputIterator first, InputIterator last)
	{
		InsertDispatch(position, first, last,
			typename is_integral<InputIterator>::type());
	}

	Iterator Erase(Iterator position)
	{
		CE_ASSERT(position >= begin() && position < end());

		if(position != end())
			Algorithm::Copy(position + 1, end(), position);

		Memory::Destroy(begin() + --m_size);

		return position;
	}

	Iterator Erase(Iterator first, Iterator last)
	{
		CE_ASSERT(IteratorIsValid(first) && IteratorIsValid(last));
		CE_ASSERT(first <= last);

		T* pEnd = end();
		if(last != pEnd)
			Algorithm::Copy(last, pEnd, first);

		Memory::DestroyRange(last, pEnd);
		m_size -= u32(last - first);

		return first;
	}

	Iterator EraseUnordered(Iterator position)
	{
		CE_ASSERT(position >= begin() && position < end());

		--m_size;
		*position = begin() + m_size;
		Memory::Destroy(begin() + m_size);

		return position;
	}

	void EraseUnorderedAt(u32 position) { EraseUnordered(begin() + position); }
	void EraseAt(u32 position) { Erase(begin() + position); }
	void EraseAt(u32 position, u32 numElements) { Erase(begin() + position, begin() + position + numElements); }

	/// Removes the first occurrence of value from this array.
	void RemoveValue(const T& value)
	{
		T* pEnd = (T*)m_buffer.data + m_size;
		T* p = Algorithm::Find((T*)m_buffer.data, pEnd, value);
		if(p != pEnd)
			Erase(p);
	}

	/// Removes all occurrences of value from this array.
	NOINLINE void RemoveAll(const T& value)
	{
		T* pEnd = (T*)m_buffer.data + m_size;
		T* newEnd = Algorithm::RemoveAll((T*)m_buffer.data, pEnd, value);
		if(newEnd != pEnd)
		{
			Memory::DestroyRange(newEnd, pEnd);
			m_size -= u32(pEnd - newEnd);
		}
	}

	/// Removes all elements at the specified indices from this array.
	NOINLINE void RemoveIndices(u32* pIndices, u32 count)
	{
		T* pEnd = (T*)m_buffer.data + m_size;
		T* newEnd = Algorithm::RemoveIndices((T*)m_buffer.data, pEnd, pIndices, pIndices + count);
		if(newEnd != pEnd)
		{
			Memory::DestroyRange(newEnd, pEnd);
			m_size -= u32(pEnd - newEnd);
		}
	}

	void Add(const T& value = T())
	{
		CE_ASSERT(m_size < N);
		Memory::Construct(((T*)m_buffer.data) + (m_size++), value);
	}

	T* AddUninitialized(u32 numElements = 1)
	{
		CE_ASSERT(m_size + numElements <= N);
		m_size += numElements;
		return (((T*)m_buffer.data) + (m_size - numElements));
	}

	T* InsertUninitialized(Iterator position)
	{
		// StaticVector doesn't support this yet, so we have to create a default value;
		return Insert(position, T());
	}

	void Append( Iterator first, Iterator last )
	{
		T* p = AddUninitialized( u32(last - first) );
		Memory::UninitializedCopy(first, last, p);
	}

	void PopBack()
	{
		CE_ASSERT(!Empty());
		Memory::Destroy(((T*)m_buffer.data) + (--m_size));
	}

	void PushFront(const T& value = T()) { Insert(begin(), value); }
	void PopFront() { Erase(begin()); }

	ConstIterator FindFirst(const T& value) const
	{
		return Algorithm::Find(begin(), end(), value);
	}

	ConstIterator FindLast(const T& value) const
	{
		return Algorithm::ReverseFind(begin(), end(), value);
	}

	bool Contains(const T& value) const
	{
		return Algorithm::Contains(begin(), end(), value);
	}

	StaticVector<T, N>& operator =(const StaticVector<T, N>& x)
	{
		if(this != &x)
			Assign(x.begin(), x.end());
		return *this;
	}

	bool IteratorIsValid(ConstIterator it) const
	{
		return (it >= begin() && it <= end());
	}


protected:
	template <class InputIterator>
	inline void AssignDispatch(InputIterator first, InputIterator last, const false_type&)
	{
		AssignIterator(first, last, typename is_pod<T>::type());
	}

	template <class Integral>
	inline void AssignDispatch(Integral numElements, Integral value, const true_type&)
	{
		AssignValues((u32)numElements, (T)value, typename is_pod<T>::type());
	}

	template <class InputIterator>
	inline void InsertDispatch(Iterator position, InputIterator first, InputIterator last, const false_type&)
	{
		InsertIterator(position, first, last, typename is_pod<T>::type());
	}

	template <class Integral>
	inline void InsertDispatch(Iterator position, Integral numElements, Integral value, const true_type&)
	{
		InsertValues(position, numElements, value, typename is_pod<T>::type());
	}

	void AssignValues(u32 numElements, const T& value, true_type)
	{
		numElements = Min(numElements, N);
		Algorithm::FillValues(begin(), numElements, value);
		m_size = numElements;
	}

	void AssignValues(u32 numElements, const T& value, false_type)
	{
		numElements = min(numElements, N);
		if(numElements > m_size)
		{
			Algorithm::Fill(begin(), end(), value);
			Memory::UninitializedFill(end(), begin() + numElements, value);
			m_size = numElements;
		}
		else
		{
			Algorithm::FillValues(begin(), numElements, value);
			Erase(begin() + numElements, end());
		}
	}

	template <class ForwardIterator>
	void AssignIterator(ForwardIterator first, ForwardIterator last, true_type)
	{
		const u32 numElements = Math::Min(N, (u32)IteratorDistance(first, last));
		ForwardIterator newLast = first;
		IteratorAdvance(newLast, numElements);
		Algorithm::Copy(first, newLast, begin());
		m_size = numElements;
	}

	template <class ForwardIterator>
	NOINLINE void AssignIterator(ForwardIterator first, ForwardIterator last, false_type)
	{
		const u32 numElements = Math::Min(N, (u32)IteratorDistance(first, last));
		if(numElements > m_size)
		{
			ForwardIterator mid = first;
			IteratorAdvance(mid, m_size);
			Memory::UninitializedCopy(mid, last, Algorithm::Copy(first, mid, begin()));
		}
		else
		{
			Algorithm::Copy(first, last, begin());
			Memory::DestroyRange(begin() + numElements, end());
		}
		m_size = numElements;
	}

	template <class ForwardIterator>
	void InsertIterator(Iterator position, ForwardIterator first, ForwardIterator last, true_type)
	{
		CE_ASSERT(IteratorIsValid(position));

		const u32 numElements = min(N - m_size, (u32)IteratorDistance(first, last));
		ForwardIterator newLast = first;
		IteratorAdvance(newLast, numElements);

		Memory::Memmove(end(), position, numElements * sizeof(T));
		Algorithm::Copy(first, newLast, position);
		m_size += numElements;
	}

	template <class InputIterator>
	NOINLINE void InsertIterator(Iterator position, InputIterator first, InputIterator last, false_type)
	{
		CE_ASSERT(IteratorIsValid(position));

		const u32 numElements = min(N - m_size, (u32)IteratorDistance(first, last));
		const u32 rpos = u32(end() - position);
		if(numElements <= rpos)
		{
			T* diff = end() - numElements;
			Memory::UninitializedCopy(diff, end(), end());
			Algorithm::CopyBackward(position, diff, end());
			Algorithm::Copy(first, last, position);
		}
		else
		{
			UninitializedCopy(position, end(), end() + numElements - rpos);

			InputIterator mid = first;
			IteratorAdvance(mid, rpos);
			Algorithm::Copy(first, mid, position);
			Memory::UninitializedCopy(mid, last, end());
		}
		m_size += numElements;
	}

	void InsertValues(Iterator position, u32 numElements, const T& value, true_type)
	{
		CE_ASSERT(IteratorIsValid(position));
		numElements = min(N - m_size, numElements);

		const ElementType tmp = value;
		Memory::Memmove(end(), position, numElements * sizeof(T));
		Algorithm::FillValues(position, numElements, tmp);
		m_size += numElements;
	}

	NOINLINE void InsertValues(Iterator position, u32 numElements, const T& value, false_type)
	{
		CE_ASSERT(IteratorIsValid(position));
		numElements = min(N - m_size, numElements);

		const ElementType tmp = value;
		const u32 rpos = u32(end() - position);
		if(numElements <= rpos)
		{
			Iterator diff = end() - numElements;
			Memory::UninitializedCopy(diff, end(), end());
			Algorithm::CopyBackward(position, diff, end());
			Algorithm::FillValues(position, numElements, tmp);
		}
		else
		{
			Memory::UninitializedCopyBackward(position, end(), end() + numElements);
			Memory::UninitializedFillValues(end(), numElements - rpos, tmp);
			Algorithm::FillValues(position, rpos, tmp);
		}

		m_size += numElements;
	}

	AlignedBufferType m_buffer;
	u32 m_size;

};


//template <class T> struct is_pod< StaticVector<T> > : integral_constant< is_pod<T>::value> > { };


// global vector operators

template <class T, u32 U, u32 V> inline
bool operator ==(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return(a.size() == b.size() && Equal(a.begin(), a.end(), b.begin()));
}

template <class T, u32 U, u32 V> inline
bool operator !=(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return !(a == b);
}

template <class T, u32 U, u32 V> inline
bool operator <(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return Algorithm::LexicographicalCompare(a.begin(), a.end(), b.begin(), b.end());
}

template <class T, u32 U, u32 V> inline
bool operator >(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return b < a;
}

template <class T, u32 U, u32 V> inline
bool operator <=(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return !(b < a);
}

template <class T, u32 U, u32 V> inline
bool operator >=(const StaticVector<T, U>& a, const StaticVector<T, V>& b)
{
	return !(a < b);
}



CE_NAMESPACE_END
