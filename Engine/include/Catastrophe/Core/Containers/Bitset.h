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
#include "Catastrophe/Core/Containers/Array.h"
#include "Catastrophe/Core/Containers/StaticBitset.h"

CE_NAMESPACE_BEGIN


/// @Bitset
///
/// Implements a dynamic, resizable, bitset that uses heap memory.
/// Currently this class only supports sizes that are multiples of 32.
///
class Bitset
{
public:

	enum ENUM_TYPE(u32)
	{
		BitsPerWord = 32,
		SizeMask = 31,
		SizeShift = 5
	};

	Bitset()
	{
		Reset();
	}

	Bitset(u32 size)
	{
		Resize(size);
	}

	/// Gets the allocator associated with this container.
	Allocator* GetAllocator() const { return m_array.GetAllocator(); }

	/// Set the allocator used by this container.
	void SetAllocator(Allocator* allocator) { m_array.SetAllocator(allocator); }

	bool Empty() const { return m_array.Size() == 0; }
	u32 Size() const { return m_array.Size() * BitsPerWord; }

	void Resize(u32 newSize)
	{
		newSize = newSize < BitsPerWord ? 1 : (newSize / BitsPerWord);
		m_array.Resize(newSize, 0);
	}

	BitReference operator [](u32 position)
	{
		return BitReference(&m_array[position >> SizeShift], position & SizeMask);
	}

	bool operator [](u32 position) const
	{
		return (m_array[position >> SizeShift] & (u32(1) << (position & SizeMask))) != 0;
	}

	void Flip()
	{
		for(u32 i(0); i < m_array.Size(); ++i)
			m_array[i] = ~m_array[i];
	}

	void FlipBit(u32 position)
	{
		m_array[position >> SizeShift] ^= u32(1) << (position & SizeMask);
	}

	void Set()
	{
		for(u32 i(0); i < m_array.Size(); ++i)
			m_array[i] = u32(-1);
	}

	void SetBit(u32 position, bool value)
	{
		BitReference(&m_array[position >> SizeShift], position) = value;
	}

	bool GetBit(u32 position) const
	{
		return (m_array[position >> SizeShift] & (u32(1) << (position & SizeMask))) != 0;
	}

	void Reset()
	{
		for(u32 i(0); i < m_array.Size(); ++i)
			m_array[i] = u32(0);
	}

	bool operator ==(const Bitset& bitset) const
	{
		return m_array == bitset.m_array;
	}

	bool Any() const
	{
		for(u32 i(0); i < m_array.Size(); ++i)
			if(m_array[i] != u32(0))
				return true;

		return false;
	}

	u32* Data() { return m_array.Data(); }
	const u32* Data() const { return m_array.Data(); }

protected:
	Array<u32> m_array;

};




CE_NAMESPACE_END

