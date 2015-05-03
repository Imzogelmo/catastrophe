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
#include "Catastrophe/Core/Containers/HashMapBase.h"

CE_NAMESPACE_BEGIN


///
/// HashMap
///
/// A hash map implemented using open addressing and linear probing.
///

template <class Key, class Value, class HashFunction>
class HashMap
{
public:
	typedef HashMap<Key, Value, HashFunction>		ThisType;
	typedef Key										KeyType;
	typedef Value									ValueType;
	typedef KeyValuePair<const Key, Value>			KeyValuePairType;
	typedef HashEntry<KeyValuePairType>				HashEntryType;

	//enum : u32 { kUnusedIndex = u32(-1) };
	enum ENUM_TYPE(u32)
	{
		kUnusedIndex = u32(-1),
		kInitialCapacity = 32
	};

	typedef HashNodeIterator<HashEntryType, KeyValuePairType>				Iterator;
	typedef HashNodeIterator<const HashEntryType, const KeyValuePairType>	ConstIterator;

	HashMap()
		: m_nodes(null), m_size(0), m_capacity(0)
		{
		}

	HashMap( u32 capacity )
		: m_nodes(null), m_size(0), m_capacity(0)
		{
		}

	~HashMap()
		{
			Clear();
			Deallocate();
		}

	Iterator begin()
	{
		HashEntryType* node = m_nodes;
		while(node->hashIndex == kUnusedIndex)
			++node;

		return Iterator(node);
	}

	Iterator end()
	{
		return Iterator(m_nodes + m_size);
	}

	ConstIterator begin() const
	{
		const HashEntryType* node = m_nodes;
		while(node->hashIndex == kUnusedIndex)
			++node;

		return ConstIterator(node);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_nodes + m_size);
	}

	Allocator* GetAllocator() const { return m_allocator; }
	void SetAllocator( Allocator* allocator ) { m_allocator = allocator; }

	bool Empty() const { return m_size == 0; }

	/// Returns if there is not enough current memory allocated to store additional elements
	/// without having to reallocate.
	bool Full() const { return m_size == m_capacity; }

	/// Returns the amount of currently stored pairs in this map.
	u32 Size() const { return m_size; }

	/// The total number of elements this container can store without having to reallocate memory.
	u32 Capacity() const { return m_capacity; }

	/// Returns the amount of unused elements in this container.
	u32 Unused() const { return m_capacity - m_size; }

	void Reserve(u32 minCapacity)
	{
		u32 newCapacity = (m_capacity == 0 ? kInitialCapacity : m_capacity);

		while(newCapacity < minCapacity)
			newCapacity *= 2;

		if(newCapacity > m_capacity)
		{
			HashEntryType* ptr = Allocate(newCapacity);

			m_capacity = newCapacity;
			m_capacityMask = newCapacity - 1;
			m_nodes = ptr;
		}
	}

	/// Destroys all elements and sets the size to 0.
	void Clear()
	{
		if(m_size != 0)
		{
			HashEntryType* endNode = m_nodes + m_capacity;
			for(HashEntryType* node = m_nodes; node != endNode; ++node)
			{
				if(node->hashIndex != kUnusedIndex)
					Memory::Destroy(&node->data);

				node->hashIndex = kUnusedIndex;
				node->hashCount = 0;
			}

			m_size = 0;
		}
	}

	/// Find or Add a value by key.
	/// If key does not exist, a new element is added with key.
	Value& operator []( const Key& key )
	{
		HashEntryType* node = FindNode(key);
		if( node == null )
			node = InsertNode(key);

		return node->data.value;
	}

	/// Adds a new key-value pair to this map if key does not already exist.
	void Add( const KeyValuePairType& p )
	{
		InsertNode(p.key, p.value);
	}

	/// Adds a new key-value pair to this map if key does not already exist.
	void Add( const Key& key, const Value& value )
	{
		InsertNode(key, value);
	}

	template <class InputIterator>
	void Insert( InputIterator first, InputIterator last )
	{
		for( ; first != last; ++first )
			Add(*first);
	}

	//void Remove( Iterator position ) { m_container.Erase(position); }
	//void RemoveRange( Iterator first, Iterator last ) { m_container.Erase(first, last); }

	/// Erases the key-value pair associated with this key.
	void Remove( const Key& key )
	{
		HashEntryType* node = FindNode(key);
		if(node != null)
		{
			Memory::Destroy(&node->data);
			node->hashIndex = kUnusedIndex;
			--m_size;

			//TODO
			//m_nodes[i].count--;
		}
	}

	ConstIterator FindKey( const Key& key ) const
	{
		HashEntryType* node = FindNode(key);
		return ConstIterator(node ? node : m_nodes + m_size);
	}

	Iterator FindKey( const Key& key )
	{
		HashEntryType* node = FindNode(key);
		return Iterator(node ? node : m_nodes + m_size);
	}

	/// Finds the first key-value pair whose value matches the specified value, otherwise returns null.
	ConstIterator FindValue( const Value& value ) const
	{
		for( ConstIterator i = begin(); i != end(); ++i )
			if( i->value == value )
				return i;

		return end();
	}

	/// Finds the first key-value pair whose value matches the specified value, otherwise returns null.
	Iterator FindValue( const Value& value )
	{
		return Iterator(const_cast<const ThisType*>(this)->FindValue(value));
	}

	/// Returns true if the specified key exists in this map.
	bool Contains( const Key& key ) const
	{
		return FindNode(key) != null;
	}

	/// Returns true if the specified key exists in this map.
	bool ContainsKey( const Key& key ) const
	{
		return FindNode(key) != null;
	}

	/// Returns true if the specified value exists in this map.
	bool ContainsValue( const Value& value ) const
	{
		return FindValue(value) != null;
	}

protected:

	/// Finds a node within the map by key if it exists, otherwise returns null.
	HashEntryType* FindNode( const Key& key ) const
	{
		const u32 kCapacityMask = m_capacity - 1;
		const u32 hashCode = m_hashFunction(key);
		const u32 hashIndex = hashCode & kCapacityMask;
		u32 i = hashIndex;

		for(u32 hashCount = m_nodes[i].hashCount; hashCount-- != 0; i = (i + 1) & kCapacityMask)
		{
			while(m_nodes[i].hashIndex != hashIndex)
				i = (i + 1) & kCapacityMask;

			if(m_nodes[i].data.key == key)
				return m_nodes + i;
		}

		return null;
	}

	/// Adds a new key-value pair to this map if key does not already exist.
	HashEntryType* InsertNode( const Key& key, const Value& value = Value() )
	{
		CE_ASSERT(m_size != m_capacity);
		if(m_size == m_capacity)
			return null;

		++m_size;

		const u32 kCapacityMask = m_capacity - 1;
		const u32 hashCode = m_hashFunction(key);
		const u32 index = hashCode & kCapacityMask;
		u32 i = index;

		m_nodes[i].hashCount++;

		while(m_nodes[i].hashIndex != kUnusedIndex)
			i = (i + 1) & kCapacityMask;

		Memory::Construct((Key*)&m_nodes[i].data.key, key);
		Memory::Construct(&m_nodes[i].data.value, value);
		m_nodes[i].hashIndex = index;

		return m_nodes + i;
	}

	HashEntryType* Allocate( u32 numElements )
	{
		return (HashEntryType*)m_allocator->Allocate(numElements * sizeof(HashEntryType));
	}

	void Deallocate()
	{
		m_allocator->Deallocate(m_nodes, m_capacity * sizeof(HashEntryType));
	}

	HashFunction m_hashFunction;
	HashEntryType* m_nodes;
	u32 m_size;
	u32 m_capacity;
	Allocator* m_allocator;

};



CE_NAMESPACE_END

