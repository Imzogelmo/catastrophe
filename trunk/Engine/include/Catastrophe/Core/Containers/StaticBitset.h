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


#define CE_INT32_WORDCOUNT(x) (((x - 1) / 32) + 1)
#define CE_INT64_WORDCOUNT(x) (((x - 1) / 64) + 1)
#define CE_INT32_BITCOUNT(x) (x > 0 ? (x * 32) : 32)
#define CE_INT64_BITCOUNT(x) (x > 0 ? (x * 64) : 64)


CE_NAMESPACE_BEGIN


/// BitReference
///
/// class that holds a reference to a word along with a mask, to
/// allow operations on specific bits.
///
class BitReference
{
public:
	BitReference(u32* ptr, u32 position)
		: m_data(*ptr), m_mask(u32(1) << position)
	{}

	BitReference& Flip()
	{
		m_data ^= m_mask;
		return *this;
	}

	operator bool() const
	{
		return (m_data & m_mask) != 0;
	}

	BitReference& operator =(const BitReference& bitReference) { return operator =((m_data & m_mask) != 0); }
	BitReference& operator =(bool value)
	{
		if(value)
		{
			m_data |= m_mask;
		}
		else
		{
			m_data &= ~m_mask;
		}

		return *this;
	}

protected:
	u32& m_data;
	u32 m_mask;

};


/// StaticBitset
///
/// Implements a bitset similar to std::bitset.
///
template<u32 NBits>
class StaticBitset
{
public:

	enum ENUM_TYPE(u32)
	{
		NWords = CE_INT32_WORDCOUNT(NBits),
		BitsPerWord = 32,
		SizeMask = 31,
		SizeShift = 5
	};

	StaticBitset()
	{
		Reset();
	}

	StaticBitset(u32 value)
	{
		m_bits[0] = value;
	}

	BitReference operator [](u32 position)
	{
		return BitReference(&m_bits[position >> SizeShift], position & SizeMask);
	}

	bool operator [](u32 position) const
	{
		return (m_bits[position >> SizeShift] & (u32(1) << (position & SizeMask))) != 0;
	}

	void operator &=(const StaticBitset<NBits>& x)
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] &= x.m_bits[i];
	}

	void operator |=(const StaticBitset<NBits>& x)
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] |= x.m_bits[i];
	}

	void operator ^=(const StaticBitset<NBits>& x)
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] ^= x.m_bits[i];
	}

	void Flip()
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] = ~m_bits[i];
	}

	void FlipBit(u32 position)
	{
		m_bits[position >> SizeShift] ^= u32(1) << (position & SizeMask);
	}

	void Set()
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] = u32(-1);
	}

	void SetBit(u32 position, bool value)
	{
		BitReference(&m_bits[position >> SizeShift], position) = value;
	}

	bool GetBit(u32 position) const
	{
		return (m_bits[position >> SizeShift] & (u32(1) << (position & SizeMask))) != 0;
	}

	void Reset()
	{
		for(u32 i(0); i < NWords; ++i)
			m_bits[i] = u32(0);
	}

	bool operator ==(const StaticBitset<NBits>& x) const
	{
		return Algorithm::Equal(m_bits, m_bits + NWords, x.m_bits);
	}

	bool Any() const
	{
		for(u32 i(0); i < NWords; ++i)
			if(m_bits[i] != u32(0))
				return true;

		return false;
	}

	u32* Data() { return &m_bits[0]; }
	const u32* Data() const { return &m_bits[0]; }

protected:
	u32 m_bits[NWords];

};



template<>
class StaticBitset<32>
{
public:

	StaticBitset() : m_bits(0) {}
	StaticBitset(u32 value) : m_bits(value) {}

	void operator <<=(u32 shift) { m_bits <<= shift; }
	void operator >>=(u32 shift) { m_bits >>= shift; }
	void operator &=(const StaticBitset<32>& x) { m_bits &= x.m_bits; }
	void operator |=(const StaticBitset<32>& x) { m_bits |= x.m_bits; }
	void operator ^=(const StaticBitset<32>& x) { m_bits ^= x.m_bits; }

	BitReference operator [](u32 position)
	{
		return BitReference(&m_bits, position & 31);
	}

	bool operator [](u32 position) const
	{
		return (m_bits & (u32(1) << position)) != 0;
	}

	void Flip(u32 position) { m_bits ^= u32(1) << position; }
	void Flip() { m_bits = ~m_bits; }
	void Reset() { m_bits = u32(0); }
	void Set() { m_bits = ~u32(0); }
	void Set(u32 position, bool value)
	{
		if(value)
			m_bits |= (u32(1) << position);
		else
			m_bits &= ~(u32(1) << position);
	}

	bool operator ==(const StaticBitset<32>& x) const { return m_bits == x.m_bits; }
	bool Any() const { return m_bits != u32(0); }

	u32* Data() { return &m_bits; }
	const u32* Data() const { return &m_bits; }

protected:
	u32 m_bits;

};



CE_NAMESPACE_END

