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
#include "Catastrophe/Core/Containers/KeyValuePair.h"

CE_NAMESPACE_BEGIN



template <class Key, class Value, u32 N>
struct StaticArrayMap
{
public:
	typedef KeyValuePair<Key, Value>			ElementType;
	typedef KeyValuePair<Key, Value>			KeyValuePairType;
	typedef KeyValuePair<Key, Value>*			Iterator;
	typedef const KeyValuePair<Key, Value>*		ConstIterator;

	StaticArrayMap()
		: m_size(0)
		{
		}
	
	bool Empty() const { return m_size == 0; }
	bool Full() const { return m_size == N; }

	u32 Size() const { return m_size; }
	u32 Capacity() const { return N; }

	Iterator begin() { return m_data; }
	Iterator end() { return m_data + m_size; }
	ConstIterator begin() const { return m_data; }
	ConstIterator end() const { return m_data + m_size; }

	Iterator data() { return m_data; }
	ConstIterator data() const { return m_data; }

	void Clear()
	{
		m_size = 0;
	}

	Value& operator [](const Key& key)
	{
		u32 index = FindIndex(key);
		if(index == m_size)
		{
			if(m_size == N)
			{
				index = 0;
			}
			else
			{
				//new (&m_data[m_size].key) key;
				//new (&m_data[m_size].value) Value;
				//Memory::Construct(m_data + m_size, KeyValuePairType(key));
				KeyValuePairType* p = m_data + m_size;
				new (p) KeyValuePairType(key);
				++m_size;
			}
		}

		return m_data[index].value;
	}

	void Add(const Key& key, const Value& value)
	{
		if( LIKELY(m_size != N && !Contains(key)) )
		{
			// The array is unordered, so we simply add it to the back.
			Memory::Construct(&m_data[m_size].key, key);
			Memory::Construct(&m_data[m_size].value, value);
			++m_size;
		}
	}

	void Remove(const Key& key)
	{
		u32 keyIndex = FindIndex(key);
		if(keyIndex != m_size)	
		{
			// Elements are unordered, so just swap it for the value at the end.
			if(keyIndex != --m_size)
				m_data[keyIndex] = m_data[m_size];

			Memory::Destroy(&m_data[m_size]);
		}
	}

	bool Contains(const Key& key) const
	{
		return FindIndex(key) != m_size;
	}

	ConstIterator Find(const Key& key) const
	{
		return m_data + FindIndex(key);
	}

	Iterator Find(const Key& key)
	{
		return m_data + FindIndex(key);
	}

	u32 FindIndex(const Key& key) const
	{
		for(u32 i(0); i < m_size; ++i)
			if(m_data[i].key == key)
				return i;

		return m_size;
	}

protected:
	KeyValuePairType m_data[N];
	u32 m_size;

};



CE_NAMESPACE_END
