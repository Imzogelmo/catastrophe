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

#include "Catastrophe/Core/Containers/Forward.h"
#include "Catastrophe/Core/Functional.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Algorithm/BinarySearch.h"
#include "Catastrophe/Core/Containers/KeyValuePair.h"

CE_NAMESPACE_BEGIN


template <class Key, class Compare, class Container>
class VectorSet
{
public:
	typedef VectorSet<Key, Compare, Container>		ThisType;
	typedef Compare									CompareType;
	typedef Container								VectorType;
	typedef Key										KeyType;
	typedef Key*									Iterator;
	typedef const Key*								ConstIterator;

	VectorSet()
		: m_container(), m_compare()
		{
		}

	explicit VectorSet(Allocator* allocator)
		: m_container(allocator), m_compare()
		{
		}

	explicit VectorSet(const Compare& compare)
		: m_container(), m_compare(compare)
		{
		}

	VectorSet( const ThisType& x )
		: m_container(x.m_container), m_compare(x.m_compare)
		{
		}

	ThisType& operator =( const ThisType& x )
	{
		m_container = x.m_container;
		m_compare = x.m_compare;
		return *this;
	}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return m_container.GetAllocator(); }

	/// Set the allocator used by this container.
	void SetAllocator( Allocator* allocator ) { m_container.SetAllocator(allocator); }

	Iterator		begin()			{ return m_container.begin(); }
	Iterator		end()			{ return m_container.end(); }
	ConstIterator	begin() const	{ return m_container.begin(); }
	ConstIterator	end() const		{ return m_container.end(); }

	/// Reallocates the memory used by this container to a size only large enough
	/// to hold the elements currently stored, in that a call to Full() shall return true.
	void ShrinkToFit() { m_container.ShrinkToFit(); }

	/// Sets the exact capacity of the vector. Unlike reserve or resize, which never
	/// shrink the container, setting the capacity to a smaller size will reallocate
	/// memory and move the elements to a buffer exactly of size 'capacity'.
	void SetCapacity(u32 capacity) { m_container.SetCapacity(capacity); }

	/// Makes sure there is enough memory allocated to contain 'capacity' num elements.
	void Reserve(u32 capacity) { m_container.Reserve(capacity); }

	/// Returns true if there are no elements stored in this Vector.
	bool Empty() const { return m_container.Empty(); }

	/// Returns if there is enough current memory allocated to store additional elements
	/// without having to reallocate.
	bool Full() const { return m_container.Full(); }

	/// Returns the amount of currently stored elements in this Vector.
	u32 Size() const { return m_container.Size(); }

	/// The total number of elements this container can store without having to reallocate memory.
	u32 Capacity() const { return m_container.Capacity(); }

	/// Returns the amount of unused elements in this container.
	u32 Unused() const { return m_container.Unused(); }

	/// Destroys all elements and sets the size to 0.
	void Clear() { m_container.Clear(); }

	/// Adds a new key-value pair to this map if key does not already exist.
	Iterator Add( const Key& key )
	{
		Iterator p = LowerBound(key);
		if( p == m_container.end() || m_compare(key, *p) )
			p = m_container.Insert(p, key);

		return p;
	}

	template <class InputIterator>
	void Insert( InputIterator first, InputIterator last )
	{
		for( InputIterator it = first; first != last; ++first )
			Add(*first);
	}

	/// Removes the element at Iterator position from within this map.
	void Remove( Iterator position ) { m_container.Erase(position); }

	/// Removes the range of elements (first, last] from within this map.
	void RemoveRange( Iterator first, Iterator last ) { m_container.Erase(first, last); }

	/// Erases the key-value pair associated with this key.
	void Remove( const Key& key )
	{
		Iterator p = Find(key);
		if( p != m_container.end() )
			m_container.Erase(p);
	}

	/// Finds a key-value pair by key.
	Iterator Find( const Key& key )
	{
		Iterator p = LowerBound(key);
		if( p != m_container.end() && m_compare(key, *p) )
			p = m_container.end();
		return p;
	}

	/// Finds a key-value pair by key.
	ConstIterator Find( const Key& key ) const
	{
		return (ConstIterator)const_cast<ThisType*>(this)->Find(key);
	}

	/// Returns true if the specified key exists in this map.
	bool Contains( const Key& key ) const
	{
		return Find(key) != m_container.end();
	}

	/// Returns true if the specified key exists in this map.
	bool ContainsKey( const Key& key ) const
	{
		return Find(key) != m_container.end();
	}

	Iterator LowerBound( const Key& key )
	{
		return Algorithm::LowerBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	ConstIterator LowerBound( const Key& key ) const
	{
		return Algorithm::LowerBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	Iterator UpperBound( const Key& key )
	{
		return Algorithm::UpperBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	ConstIterator UpperBound( const Key& key ) const
	{
		return Algorithm::UpperBound( m_container.begin(), m_container.end(), key, m_compare );
	}

protected:
	VectorType m_container;
	CompareType m_compare;

};







template <class Key, class Compare, class Container>
class VectorMultiset
{
public:
	typedef VectorMultiset<Key, Compare, Container>		ThisType;
	typedef Container									VectorType;
	typedef Key											KeyType;
	typedef Compare										CompareType;
	typedef Key*										Iterator;
	typedef const Key*									ConstIterator;
	//typedef typename IteratorRange<ConstIterator, ConstIterator>	ConstIteratorRange;
	//typedef typename IteratorRange<Iterator, Iterator>				IteratorRange;

	VectorMultiset()
		: m_container(), m_compare()
		{
		}

	explicit VectorMultiset(Allocator* allocator)
		: m_container(allocator), m_compare()
		{
		}

	explicit VectorMultiset(const Compare& compare)
		: m_container(), m_compare(compare)
		{
		}

	VectorMultiset( const ThisType& x )
		: m_container(x.m_container), m_compare(x.m_compare)
		{
		}

	ThisType& operator =( const ThisType& x )
	{
		m_container = x.m_container;
		m_compare = x.m_compare;
		return *this;
	}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return m_container.GetAllocator(); }

	/// Set the allocator used by this container.
	void SetAllocator( Allocator* allocator ) { m_container.SetAllocator(allocator); }

	Iterator		begin()			{ return m_container.begin(); }
	Iterator		end()			{ return m_container.end(); }
	ConstIterator	begin() const	{ return m_container.begin(); }
	ConstIterator	end() const		{ return m_container.end(); }

	/// Reallocates the memory used by this container to a size only large enough
	/// to hold the elements currently stored, in that a call to Full() shall return true.
	void ShrinkToFit() { m_container.ShrinkToFit(); }

	/// Sets the exact capacity of the vector. Unlike reserve or resize, which never
	/// shrink the container, setting the capacity to a smaller size will reallocate
	/// memory and move the elements to a buffer exactly of size 'capacity'.
	void SetCapacity(u32 capacity) { m_container.SetCapacity(capacity); }

	/// Makes sure there is enough memory allocated to contain 'capacity' num elements.
	void Reserve(u32 capacity) { m_container.Reserve(capacity); }

	/// Returns true if there are no elements stored in this Vector.
	bool Empty() const { return m_container.Empty(); }

	/// Returns if there is enough current memory allocated to store additional elements
	/// without having to reallocate.
	bool Full() const { return m_container.Full(); }

	/// Returns the amount of currently stored elements in this Vector.
	u32 Size() const { return m_container.Size(); }

	/// The total number of elements this container can store without having to reallocate memory.
	u32 Capacity() const { return m_container.Capacity(); }

	/// Returns the amount of unused elements in this container.
	u32 Unused() const { return m_container.Unused(); }

	/// Destroys all elements and sets the size to 0.
	void Clear() { m_container.Clear(); }

	/// Adds a new key to this set.
	Iterator Add( const Key& key )
	{
		Iterator p = m_container.Insert(LowerBound(key), key);
		return p;
	}

	template <class InputIterator>
	void Insert( InputIterator first, InputIterator last )
	{
		for( InputIterator it = first; first != last; ++first )
			Add(*first);
	}

	/// Removes the key at Iterator position from within this map.
	void Remove( Iterator position ) { m_container.Erase(position); }

	/// Removes the range of elements (first, last] from within this map.
	void RemoveRange( Iterator first, Iterator last ) { m_container.Erase(first, last); }

	/// Erases all keys associated with this key.
	void Remove( const Key& key )
	{
		IteratorRange<Iterator, Iterator> iteratorRange = EqualRange(key);
		if( !iteratorRange.Empty() )
			m_container.Erase(iteratorRange.first, iteratorRange.last);
	}

	/// Finds a key-value pair by key.
	Iterator Find( const Key& key )
	{
		Iterator it = LowerBound(key);
		if( it != m_container.end() && m_compare(key, *it) )
			it = m_container.end();
		return it;
	}

	/// Finds a key-value pair by key.
	ConstIterator Find( const Key& key ) const
	{
		return (ConstIterator)const_cast<ThisType*>(this)->Find(key);
	}

	/// Returns true if the specified key exists in this map.
	bool Contains( const Key& key ) const
	{
		return Find(key) != m_container.end();
	}

	/// Returns true if the specified key exists in this map.
	bool ContainsKey( const Key& key ) const
	{
		return Find(key) != m_container.end();
	}

	u32 Count( const Key& key ) const
	{
		IteratorRange<ConstIterator, ConstIterator> iteratorRange = EqualRange(key);
		return u32(iteratorRange.last - iteratorRange.first);
	}

	IteratorRange<Iterator, Iterator> EqualRange( const Key& key )
	{
		Iterator first = LowerBound(key);
		Iterator last(first);
		while( last != end() && !m_compare(key, *++last) ) ;
		return IteratorRange<Iterator, Iterator>(first, last);
	}

	IteratorRange<ConstIterator, ConstIterator> EqualRange( const Key& key ) const
	{
		ConstIterator first = lower_bound(key);
		ConstIterator last(first);
		while( last != end() && !m_compare(key, *++last) ) ;
		return IteratorRange<ConstIterator, ConstIterator>(first, last);
	}

	Iterator LowerBound( const Key& key )
	{
		return Algorithm::LowerBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	ConstIterator LowerBound( const Key& key ) const
	{
		return Algorithm::LowerBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	Iterator UpperBound( const Key& key )
	{
		return Algorithm::UpperBound( m_container.begin(), m_container.end(), key, m_compare );
	}

	ConstIterator UpperBound( const Key& key ) const
	{
		return Algorithm::UpperBound( m_container.begin(), m_container.end(), key, m_compare );
	}

protected:
	VectorType m_container;
	CompareType m_compare;

};


CE_NAMESPACE_END

