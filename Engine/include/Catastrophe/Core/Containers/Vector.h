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
#include "Catastrophe/Core/Iterator.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Algorithm/Copy.h"
#include "Catastrophe/Core/Allocators/Allocator.h"
#include "Catastrophe/Core/Containers/AlignedBuffer.h"

CE_NAMESPACE_BEGIN


///
/// @Vector
///
/// A standard vector container class similar to std::vector, except with
/// an enhanced feature-set and optimization for POD types.
///
/// This class is generally faster and produces less compiled code than
/// generic standard library std::vector implementations.
///

template <class T>
class Vector
{
public:
	typedef T								ElementType;
	typedef T*								Iterator;
	typedef const T*						ConstIterator;
	typedef ReverseIterator<const T*>		ConstReverseIterator;
	typedef ReverseIterator<T*>				ReverseIterator;

	Vector()
		: m_begin(null), m_end(null), m_capacity(null), m_allocator(Memory::GetDefaultAllocator())
		{
		}

	explicit Vector(Allocator* allocator)
		: m_begin(null), m_end(null), m_capacity(null), m_allocator(allocator)
		{
			CE_ASSERT(allocator != null);
		}

	explicit Vector(u32 numElements, const T& value = T(), Allocator* allocator = Memory::GetDefaultAllocator())
		: m_begin(null), m_end(null), m_capacity(null), m_allocator(allocator)
		{
			InitializeValues(numElements, value);
		}

	template <class InputIterator>
		Vector(InputIterator first, InputIterator last, Allocator* allocator = Memory::GetDefaultAllocator())
		: m_begin(null), m_end(null), m_capacity(null), m_allocator(allocator)
		{
			InitializeDispatch(first, last,
				typename is_integral<InputIterator>::type());
		}

	Vector(const Vector<T>& x)
		: m_begin(null), m_end(null), m_capacity(null), m_allocator(null)
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

			InitializeIterator(x.Size(), x.m_begin, x.m_end);
		}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return m_allocator; }

	/// Set the allocator used by this container.
	void SetAllocator( Allocator* allocator ) { m_allocator = allocator; }

	/// Returns true if there are no elements stored in this Vector.
	bool Empty() const { return m_end == m_begin; }

	/// Returns if there is enough current memory allocated to store additional elements
	/// without having to reallocate.
	bool Full() const { return m_end == m_capacity; }

	/// Returns the amount of currently stored elements in this Vector.
	u32 Size() const { return u32(m_end - m_begin); }

	/// The total number of elements this container can store without having to reallocate memory.
	u32 Capacity() const { return u32(m_capacity - m_begin); }

	/// Returns the amount of unused elements in this container.
	u32 Unused() const { return u32(m_capacity - m_end); }

	T& operator [] (u32 index) { return *(m_begin + index); }
	const T& operator [] (u32 index) const { return *(m_begin + index); }

	T& At(u32 index)
	{
		CE_ASSERT(index < Size());
		return *(m_begin + index);
	}

	const T& At(u32 index) const
	{
		CE_ASSERT(index < Size());
		return *(m_begin + index);
	}

	T&			Front()			{ return *m_begin; }
	const T&	Front() const	{ return *m_begin; }
	T&			Back()			{ return *(m_end - 1); }
	const T&	Back()	const	{ return *(m_end - 1); }

	T*			begin()			{ return m_begin; }
	const T*	begin() const	{ return m_begin; }
	T*			end()			{ return m_end; }
	const T*	end() const		{ return m_end; }

	ReverseIterator			rbegin()		{ return ReverseIterator(m_end); }
	ConstReverseIterator	rbegin() const	{ return ConstReverseIterator(m_end); }
	ReverseIterator			rend()			{ return ReverseIterator(m_begin); }
	ConstReverseIterator	rend() const	{ return ConstReverseIterator(m_begin); }

	T* data()				{ return m_begin; }
	const ElementType* data() const	{ return m_begin; }

	void Reserve(u32 newCapacity)
	{
		// By far the most common use case - the user requests an allocation
		// up front, before the Vector is used.
		if(m_capacity - m_begin == 0)
			InitializeCapacity(newCapacity);

		// Not performance critical, 
		else SetCapacity(newCapacity);
	}

	void Resize(u32 newSize, const T& value = T())
	{
		const u32 currentSize = u32(m_end - m_begin);
		if(newSize > currentSize)
		{
			// always respect the capacity request by the user.
			Reserve(newSize);

			Memory::UninitializedFillValues(m_end, newSize - currentSize, value);
			m_end = m_begin + newSize;
		}
		else if(newSize < currentSize)
		{
			T* newEnd = m_begin + newSize;
			Memory::DestroyRange(newEnd, m_end);
			m_end = newEnd;
		}
	}

	void Reset() { m_end = m_begin; } //todo: change this
	void Clear()
	{
		Memory::DestroyRange(m_begin, m_end);
		m_end = m_begin;
	}

	/// Reallocates the memory used by this container to a size only large enough
	/// to hold the elements currently stored, in that a subsequent call to Full() shall return true.
	void ShrinkToFit() { SetCapacity(u32(m_end - m_begin)); }

	/// Sets the exact capacity of the vector. Unlike reserve or resize, which never
	/// shrink the amount of allocated memory, setting the capacity to a smaller size will reallocate
	/// memory and move the elements to a buffer exactly of size 'capacity'.
	NOINLINE void SetCapacity(u32 newCapacity)
	{
		// Only reallocate if capacity is being changed
		if(newCapacity != u32(m_capacity - m_begin))
		{
			// We may be shrinking, so roll back the size if needed
			const u32 newSize = Math::Min(newCapacity, u32(m_end - m_begin));

			T* p = newCapacity ? AllocateCopy(newCapacity, m_begin, m_begin + newSize) : null;
			Memory::DestroyRange(m_begin, m_end);
			Deallocate();

			m_begin = p;
			m_end = p + newSize;
			m_capacity = p + newCapacity;
		}
	}

	/// Fills the Vector with exactly 'numElement' elements of 'value'.
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

	void InsertAt(u32 position, const T& value) { Insert(m_begin + position, value); }
	void InsertAt(u32 position, u32 numElements, const T& value) { Insert(m_begin + position, numElements, value); }

	Iterator Insert(Iterator position, const T& value)
	{
		T* p = InsertHole(position, typename is_pod<T>::type());
		*p = value;
		return p;
	}

	inline void Insert(Iterator position, u32 numElements, const T& value)
	{
		T* p = InsertHole(position, numElements, typename is_pod<T>::type());
		Algorithm::FillValues(p, numElements, value);
	}

	template <class InputIterator> inline
	void Insert(Iterator position, InputIterator first, InputIterator last)
	{
		InsertDispatch(position, first, last,
			typename is_integral<InputIterator>::type());
	}

	/// Erases element at position.
	Iterator Erase(Iterator position)
	{
		CE_ASSERT(position >= m_begin && position < m_end);
		Algorithm::Copy(position + 1, m_end, position);
		Memory::Destroy(--m_end);

		return position;
	}

	/// Erases all elements in the range first, last.
	Iterator Erase(Iterator first, Iterator last)
	{
		CE_ASSERT(IteratorIsValid(first) && IteratorIsValid(last));
		CE_ASSERT(first <= last);

		T* ptr = Algorithm::Copy(last, m_end, first);
		Memory::DestroyValues(ptr, u32(last - first));
		m_end -= (last - first);

		return first;
	}

	/// Erases an element but does not guarantee to preserve element order.
	Iterator EraseUnordered(Iterator position)
	{
		CE_ASSERT(position >= m_begin && position < m_end);

		if(*position != m_end)
			*position = *(--m_end);
		Memory::Destroy(m_end);

		return position;
	}

	void EraseUnorderedAt(u32 position) { EraseUnordered(m_begin + position); }
	void EraseAt(u32 position) { Erase(m_begin + position); }
	void EraseAt(u32 position, u32 n) { Erase(m_begin + position, m_begin + position + n); }

	/// Removes the first occurrence of value from this array.
	bool RemoveValue(const T& value)
	{
		T* p = Algorithm::Find(m_begin, m_end, value);
		if(p != m_end)
		{
			Erase(p);
			return true;
		}

		return false;
	}

	/// Removes all occurrences of value from this array.
	NOINLINE void RemoveAll(const T& value)
	{
		T* newEnd = Algorithm::RemoveAll(m_begin, m_end, value);
		if(newEnd != m_end)
		{
			Memory::DestroyRange(newEnd, m_end);
			m_end = newEnd;
		}
	}

	/// Removes all elements at the specified indices from this array.
	NOINLINE void RemoveIndices(u32* pIndices, u32 count)
	{
		T* newEnd = Algorithm::RemoveIndices(m_begin, m_end, pIndices, pIndices + count);
		if(newEnd != m_end)
		{
			Memory::DestroyRange(newEnd, m_end);
			m_end = newEnd;
		}
	}

	/// Adds a value to the end of this array, but constructs it with an
	/// argument of another type. This is useful when you don't want to create
	/// a temporary value of an object.
	///
	/// Example Usage:
	///     Vector<String> MyStrings;
	///     MyStrings.Add("Don't create a temporary string object from this CString!");
	///
	template<class ConstructableType>
	void AddAs(const ConstructableType& value)
	{
		T* p = AddUninitialized();
		Memory::ConstructAs(p, value);
	}

	/// Adds a value to the end of this array.
	void Add(const T& value = T())
	{
		if(UNLIKELY(m_end == m_capacity))
			Grow();

		Memory::Construct(m_end, value);
		++m_end;
	}

	/// Adds a value to the end of the array only if it does not already exist.
	void AddUnique(const T& value)
	{
		if( !Contains(value) )
			Add(value);
	}

	ElementType* AddUninitialized(u32 numElements = 1)
	{
		if(UNLIKELY(m_end + numElements > m_capacity))
			Grow(numElements);

		m_end += numElements;
		return m_end - numElements;
	}

	void Append( Iterator first, Iterator last )
	{
		T* p = AddUninitialized( u32(last - first) );
		Memory::UninitializedCopy(first, last, p);
	}

	void Append( const T& value, u32 numElements )
	{
		T* p = AddUninitialized(numElements);
		Memory::UninitializedFill(p, p + numElements, value);
	}

	T* InsertUninitialized(Iterator position, u32 numElements = 1)
	{
		return InsertHole(position, numElements, typename is_pod<T>::type());
	}

	template<class ConstructableType>
	void InsertAs(Iterator position, const ConstructableType& value)
	{
		T* p = InsertUninitialized(position);
		Memory::ConstructAs(p, value);
	}

	void PopBack()
	{
		CE_ASSERT(!Empty());
		Memory::Destroy(--m_end);
	}

	void PopBackElements(u32 numElements)
	{
		CE_ASSERT(u32(m_end - m_begin) >= numElements);
		Memory::DestroyRange(m_end - numElements, m_end);
		m_end -= numElements;
	}

	void PushFront(const T& value = T()) { Insert(m_begin, value); }
	void PopFront() { Erase(m_begin); }

	ConstIterator FindFirst(const T& value) const
	{
		return Algorithm::Find(m_begin, m_end, value);
	}

	ConstIterator FindLast(const T& value) const
	{
		return Algorithm::ReverseFind(m_begin, m_end, value);
	}

	bool Contains(const T& value) const
	{
		return Algorithm::Contains(m_begin, m_end, value);
	}

	Vector<T>& operator =(const Vector<T>& x)
	{
		if(this != &x)
			AssignIterator(x.m_begin, x.m_end, typename is_pod<T>::type());

		return *this;
	}

	bool IteratorIsValid(ConstIterator position) const
	{
		return (position >= m_begin && position <= m_end);
	}

	NOINLINE void Grow(u32 minimumGrowth = 1)
	{
		const u32 newCapacity = GetNewCapacity(minimumGrowth);
		const u32 newSize = u32(m_end - m_begin);
		T* newBegin = AllocateCopy(newCapacity, m_begin, m_end);

		Memory::DestroyRange(m_begin, m_end);
		Deallocate();

		m_begin = newBegin;
		m_end = newBegin + newSize;
		m_capacity = newBegin + newCapacity;
	}

	u32 GetNewCapacity(u32 minimumGrowth) const
	{
		const u32 oldCapacity = u32(m_capacity - m_begin);
		u32 newCapacity = oldCapacity ? (oldCapacity * 2) : CE_MIN_VECTOR_GROWTH;
		if(newCapacity < oldCapacity + minimumGrowth)
			newCapacity = oldCapacity + minimumGrowth;

		return newCapacity;
	}

protected:
	template <class InputIterator>
	inline void AssignDispatch(InputIterator first, InputIterator last, const false_type&)
	{
		AssignIterator(first, last, typename is_pod<T>::type());
	}

	template <class Integral>
	inline void AssignDispatch(Integral n, Integral value, const true_type&)
	{
		AssignValues((u32)n, (T)value, typename is_pod<T>::type());
	}

	template <class InputIterator>
	inline void InsertDispatch(Iterator position, InputIterator first, InputIterator last, const false_type&)
	{
		u32 numElements = u32(last - first);
		T* p = InsertHole(position, numElements, typename is_pod<T>::type());
		Algorithm::Copy(first, last, p);
	}

	template <class Integral>
	inline void InsertDispatch(Iterator position, Integral numElements, Integral value, const true_type&)
	{
		T* p = InsertHole(position, numElements, value, typename is_pod<T>::type());
		*p = value;
	}

	template <class InputIterator>
	inline void InitializeDispatch(InputIterator first, InputIterator last, const false_type&)
	{
		InitializeIterator(IteratorDistance(first, last), first, last);
	}

	template <class Integral>
	inline void InitializeDispatch(Integral numElements, Integral value, const true_type&)
	{
		InitializeValues((u32)numElements, value);
	}

	template <class ForwardIterator>
	void AssignIterator(ForwardIterator first, ForwardIterator last, true_type)
	{
		const u32 numElements = IteratorDistance(first, last);
		if(numElements > u32(m_capacity - m_begin))
		{
			Deallocate();
			m_begin = AllocateCopy(numElements, first, last);
			m_end = m_capacity = m_begin + numElements;
		}
		else
		{
			m_end = Algorithm::Copy(first, last, m_begin);
		}
	}

	template <class ForwardIterator>
	NOINLINE void AssignIterator(ForwardIterator first, ForwardIterator last, false_type)
	{
		const u32 numElements = IteratorDistance(first, last);
		if(numElements > Capacity())
		{
			Memory::DestroyRange(m_begin, m_end);
			Deallocate();

			m_begin = AllocateCopy(numElements, first, last);
			m_end = m_capacity = m_begin + numElements;
		}
		else
		if(numElements > Size())
		{
			ForwardIterator mid = first;
			IteratorAdvance(mid, Size());
			m_end = Memory::UninitializedCopy(mid, last, Copy(first, mid, m_begin));
		}
		else
		{
			T* newEnd = Copy(first, last, m_begin);
			Memory::DestroyValues(newEnd, u32(m_end - newEnd));
			m_end = newEnd;
		}
	}

	void AssignValues(u32 numElements, const T& value, true_type)
	{
		if(numElements > Capacity())
		{
			Deallocate();
			m_begin = AllocateFill(numElements, value);
			m_end = m_capacity = m_begin + numElements;
		}
		else
		{
			m_end = Algorithm::FillValues(m_begin, numElements, value);
		}
	}

	NOINLINE void AssignValues(u32 numElements, const T& value, false_type)
	{
		if(numElements > Capacity())
		{
			Memory::DestroyRange(m_begin, m_end);
			Deallocate();

			m_begin = AllocateFill(numElements, value);
			m_end = m_capacity = m_begin + numElements;
		}
		else
		if(numElements > Size())
		{
			Algorithm::Fill(m_begin, m_end, value);
			Memory::UninitializedFill(m_end, m_begin + numElements, value);
			m_end = m_begin + numElements;
		}
		else
		{
			Algorithm::FillValues(m_begin, numElements, value);
			Memory::DestroyRange(m_begin + numElements, m_end);
			m_end = m_begin + numElements;
		}
	}

	// This function is shared between all specializations of Insert(..)
	// and would be called when a reallocation is needed to meet the new capacity
	// requirements. This function reallocates memory and moves existing
	// elements to the proper position within the array, but leaves the memory
	// pointed to by position uninitialized.

	NOINLINE T* InsertHoleReallocate(Iterator position, u32 numElements)
	{
		const u32 newCapacity = GetNewCapacity(numElements);
		T* newBegin = Allocate(newCapacity);

		T* newPos = Memory::UninitializedCopy(m_begin, position, newBegin);
		T* newEnd = Memory::UninitializedCopy(position, m_end, newPos + numElements);

		Memory::DestroyRange(m_begin, m_end);
		Deallocate();

		m_begin = newBegin;
		m_end = newEnd;
		m_capacity = newBegin + newCapacity;

		return newPos;
	}

	Iterator InsertHole(Iterator position, true_type)
	{
		CE_ASSERT(IteratorIsValid(position));

		if(LIKELY(m_capacity != m_end))
		{
			if(position != m_end)
				Memory::Memmove(position + 1, position, u32(m_end - position) * sizeof(T));

			++m_end;
		}
		else
		{
			// reallocate
			position = InsertHoleReallocate(position, u32(1));
		}

		return position;
	}

	Iterator InsertHole(Iterator position, false_type)
	{
		CE_ASSERT(IteratorIsValid(position));

		// optimize for common cases by assuming we are not full,
		// and that there is a possibility that we are inserting to end.
		// by doing this we can avoid many cases where a Copy of the original
		// value must be constructed when its address is between [it, end).

		if(UNLIKELY(m_capacity != m_end))
		{
			if(position != m_end)
			{
				T* last = m_end - 1;
				Memory::Construct(m_end, *(last));
				Algorithm::CopyBackward(position, last, m_end);
			}

			++m_end;
		}
		else
		{
			// reallocate
			position = InsertHoleReallocate(position, u32(1));
			Memory::Construct(position);
		}

		return position;
	}

	Iterator InsertHole(Iterator position, u32 numElements, true_type)
	{
		CE_ASSERT(IteratorIsValid(position));

		if(LIKELY(u32(m_capacity - m_end) >= numElements))
		{
			if(position != m_end)
				Memory::Memmove(position + numElements, position, u32(m_end - position) * sizeof(T));

			m_end += numElements;
		}
		else
		{
			position = InsertHoleReallocate(position, numElements);
		}

		return position;
	}

	NOINLINE Iterator InsertHole(Iterator position, u32 numElements, false_type)
	{
		CE_ASSERT(IteratorIsValid(position));
		Iterator newEnd = m_end + numElements;

		if(m_capacity < newEnd)
		{
			position = InsertHoleReallocate(position, numElements);
			Memory::UninitializedFillValues(position, numElements, ElementType());
		}
		else
		if(position == m_end)
			Memory::ConstructValues(m_end, numElements), m_end = newEnd;
		else
		{
			const u32 rpos = u32(m_end - position);
			if(numElements <= rpos)
			{
				Iterator diff = m_end - numElements;
				Memory::UninitializedCopy(diff, m_end, m_end);
				Algorithm::CopyBackward(position, diff, m_end);
			}
			else
			{
				Memory::UninitializedCopyBackward(position, m_end, newEnd);
				Memory::ConstructValues(m_end, numElements - rpos);
			}

			m_end = newEnd;
		}

		return position;
	}

	void InitializeCapacity(u32 numElements)
	{
		m_begin = Allocate(numElements);
		m_end = m_begin;
		m_capacity = m_begin + numElements;
	}

	void InitializeValues(u32 numElements, const T& value)
	{
		m_begin = AllocateFill(numElements, value);
		m_end = m_capacity = m_begin + numElements;
	}

	template <class ForwardIterator>
	void InitializeIterator(u32 numElements, ForwardIterator first, ForwardIterator last)
	{
		m_begin = AllocateCopy(numElements, first, last);
		m_end = m_capacity = m_begin + numElements;
	}

	T* Allocate(u32 numElements)
	{
		return (T*)(numElements ? m_allocator->Allocate(numElements * sizeof(T)) : null);
	}

	void Deallocate()
	{
		if(m_begin)
			m_allocator->Deallocate((void*)m_begin, u32(m_end - m_begin) * sizeof(T));
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

	T* m_begin;
	T* m_end;
	T* m_capacity;
	Allocator* m_allocator;
};


/*
template <class T, u32 N>
class FixedVector : public Vector<T>
{
public:
	typedef Vector<T>							BaseType;
	typedef typename BaseType::Iterator			Iterator;
	typedef typename BaseType::ConstIterator	ConstIterator;

	using BaseType::m_allocator;
	using BaseType::m_begin;
	using BaseType::m_end;
	using BaseType::m_capacity;

	enum
	{
		kBufferSize = N * sizeof(T),
		kBufferAlignment = FC_ALIGNOF(T)
	};

	typedef AlignedBuffer<kBufferSize, kBufferAlignment> AlignedBufferType;

	FixedVector()
		: BaseType(&m_fixedAllocatorInstance)
		{
			InitializeMemory();
		}

	explicit FixedVector(u32 n, const T& value = T())
		: BaseType()
		{
			InitializeMemory();
			BaseType::InitializeValues(n, value);
		}

	template<class InputIterator>
		FixedVector(InputIterator first, InputIterator last)
		: BaseType()
		{
			InitializeMemory();
			BaseType::InitializeIterator(IteratorDistance(first, last), first, last);
		}

	FixedVector(const FixedVector<T, N, AllocatorType>& x)
		: BaseType()
		{
			InitializeMemory();
			BaseType::InitializeIterator(x.size(), x.m_begin, x.m_end);
		}

	FixedVector(const BaseType& x)
		: BaseType()
		{
			InitializeMemory();
			BaseType::InitializeIterator(x.Size(), x.m_begin, x.m_end);
		}

	bool IsOverflowed() const
	{
		return m_begin != GetBuffer();
	}

	void Reset()
	{
		if(m_capacity)
		{
			BaseType::Clear();
			BaseType::Deallocate();
		}

		InitializeMemory();
	}

	T* GetBuffer() const
	{
		return (T*)m_buffer.data;
	}

protected:
	void InitializeMemory()
	{
		m_begin = m_end = m_fixedAllocatorInstance.Allocate(N);
		m_capacity = m_begin + N;
	}

	typedef FixedAllocator<N * sizeof(T)> AllocatorType;

	AllocatorType m_fixedAllocatorInstance;
	AlignedBufferType m_buffer;

};
*/


// global Vector operators

template <class T> inline
	bool operator ==(const Vector<T>& a, const Vector<T>& b)
	{
		return(a.Size() == b.Size() && equal(a.begin(), a.end(), b.begin()));
	}

template <class T> inline
	bool operator !=(const Vector<T>& a, const Vector<T>& b)
	{
		return !(a == b);
	}

template <class T> inline
	bool operator <(const Vector<T>& a, const Vector<T>& b)
	{
		return Algorithm::LexicographicalCompare(a.begin(), a.end(), b.begin(), b.end());
	}

template <class T> inline
	bool operator >(const Vector<T>& a, const Vector<T>& b)
	{
		return b < a;
	}

template <class T> inline
	bool operator <=(const Vector<T>& a, const Vector<T>& b)
	{
		return !(b < a);
	}

template <class T> inline
	bool operator >=(const Vector<T>& a, const Vector<T>& b)
	{
		return !(a < b);
	}



CE_NAMESPACE_END
