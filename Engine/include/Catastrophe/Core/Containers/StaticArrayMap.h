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
#include "Catastrophe/Core/Containers/AlignedBuffer.h"
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

	enum { kMaxCapacity = N };
	typedef AlignedBuffer<(N * sizeof(ElementType)), CE_ALIGNOF(ElementType)> AlignedBufferType;

	StaticArrayMap()
		: m_size(0)
		{
		}

	bool Empty() const { return m_size == 0; }
	bool Full() const { return m_size == N; }

	u32 Size() const { return m_size; }
	u32 Capacity() const { return N; }

	Iterator begin() { return (ElementType*)&m_buffer; }
	ConstIterator begin() const { return (const ElementType*)&m_buffer; }
	Iterator end() { return (ElementType*)&m_buffer + m_size; }
	ConstIterator end() const { return (const ElementType*)&m_buffer + m_size; }

	Iterator Data() { return (ElementType*)&m_buffer; }
	ConstIterator Data() const { return (const ElementType*)&m_buffer; }

	void Clear()
	{
		Memory::DestroyValues(begin(), m_size);
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
				ElementType* pData = (ElementType*)&m_buffer + index;
				Memory::Construct(&pData->key, key);
				Memory::Construct(&pData->value);
				++m_size;
			}
		}

		return ((ElementType*)&m_buffer)[index].value;
	}

	void Add(const Key& key, const Value& value)
	{
		if( LIKELY(m_size != N && !Contains(key)) )
		{
			ElementType* pData = (ElementType*)&m_buffer;

			// The array is unordered, so we simply add it to the back.
			Memory::Construct(&pData[m_size].key, key);
			Memory::Construct(&pData[m_size].value, value);
			++m_size;
		}
	}

	void Remove(const Key& key)
	{
		u32 keyIndex = FindIndex(key);
		if(keyIndex != m_size)	
		{
			ElementType* pData = (ElementType*)&m_buffer;

			// Elements are unordered, so just swap it for the value at the end.
			if(keyIndex != --m_size)
				pData[keyIndex] = pData[m_size];

			Memory::Destroy(&pData[m_size]);
		}
	}

	bool Contains(const Key& key) const
	{
		return FindIndex(key) != m_size;
	}

	ConstIterator Find(const Key& key) const
	{
		return (const ElementType*)&m_buffer + FindIndex(key);
	}

	Iterator Find(const Key& key)
	{
		return (ElementType*)&m_buffer + FindIndex(key);
	}

protected:
	u32 FindIndex(const Key& key) const
	{
		const ElementType* pData = (const ElementType*)&m_buffer;
		for(u32 i(0); i < m_size; ++i)
		{
			if(pData[i].key == key)
				return i;
		}

		return m_size;
	}

	AlignedBufferType m_buffer;
	u32 m_size;

};



template <class Key, class Value, u32 N>
struct StaticArrayMultiMap
{
public:
	typedef KeyValuePair<Key, Value>			ElementType;
	typedef KeyValuePair<Key, Value>			KeyValuePairType;
	typedef KeyValuePair<Key, Value>*			Iterator;
	typedef const KeyValuePair<Key, Value>*		ConstIterator;

	enum { kMaxCapacity = N };
	typedef AlignedBuffer<(N * sizeof(ElementType)), CE_ALIGNOF(ElementType)> AlignedBufferType;

	StaticArrayMultiMap()
		: m_buffer(), m_size(0)
	{
	}

	bool Empty() const { return m_size == 0; }
	bool Full() const { return m_size == N; }

	u32 Size() const { return m_size; }
	u32 Capacity() const { return N; }

	Iterator begin() { return (const ElementType*)&m_buffer; }
	Iterator end() { return (ElementType*)&m_buffer + m_size; }
	ConstIterator begin() const { return (const ElementType*)&m_buffer; }
	ConstIterator end() const { return (ElementType*)&m_buffer + m_size; }

	Iterator Data() { return (ElementType*)&m_buffer; }
	ConstIterator Data() const { return (const ElementType*)&m_buffer; }

	void Clear()
	{
		Memory::DestroyValues(begin(), m_size);
		m_size = 0;
	}

	void Add(const Key& key, const Value& value)
	{
		if( LIKELY(m_size != N) )
		{
			ElementType* pData = (ElementType*)&m_buffer;

			// The array is unordered, so we simply add it to the back.
			Memory::Construct(&pData[m_size].key, key);
			Memory::Construct(&pData[m_size].value, value);
			++m_size;
		}
	}

	void Remove(const Key& key)
	{
		const ElementType* pData = (const ElementType*)&m_buffer;

		for(u32 i(0); i < m_size; ++i)
		{
			if(pData[i].key == key)
			{
				// Elements are unordered, so just swap it for the value at the end.
				if(i != --m_size)
					pData[i] = pData[m_size];

				Memory::Destroy(&pData[m_size]);
			}
		}
	}

	bool Contains(const Key& key) const
	{
		return FindIndex(key) != m_size;
	}

	ConstIterator Find(const Key& key) const
	{
		return (const ElementType*)&m_buffer + FindIndex(key);
	}

	Iterator Find(const Key& key)
	{
		return (ElementType*)&m_buffer + FindIndex(key);
	}

	u32 Count(const Key& key) const
	{
		u32 count = 0;
		const ElementType* pData = (const ElementType*)&m_buffer;

		for(u32 i(0); i < m_size; ++i)
		{
			if(pData[i].key == key)
				++count;
		}

		return count;
	}

protected:
	u32 FindIndex(const Key& key) const
	{
		const ElementType* pData = (const ElementType*)&m_buffer;
		for(u32 i(0); i < m_size; ++i)
		{
			if(pData[i].key == key)
				return i;
		}

		return m_size;
	}

	AlignedBufferType m_buffer;
	u32 m_size;

};



CE_NAMESPACE_END
