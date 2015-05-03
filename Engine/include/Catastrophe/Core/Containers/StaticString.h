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
#include "Catastrophe/Core/PlatformString.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"


///
/// @StaticString
///
/// A POD string class that can hold up to 256 chars (255 + teminating null).
///
/// This string class is optimized so that iteration and size queries are always O(1),
/// and sizeof a StaticString is always equal to N *sizeof(char).
///

template <u32 N>
class StaticString
{
public:
	enum ENUM_TYPE(u32)
	{
		kMaxCapacity = N - 1
	};

	StaticString()
	{
		Clear();
	}

	StaticString(const char* str)
	{
		Assign(str, Strnlen(str, kMaxCapacity));
	}

	StaticString(const char* first, const char* last)
	{
		Assign(first, last);
	}

	StaticString(const StaticString<N>& str)
	{
		Assign(str.begin(), str.size());
	}

	template <u32 U>
	StaticString(const StaticString<U>& str)
	{
		Assign(str.begin(), str.size());
	}

	template <class StringContainerType>
	StaticString(const StringContainerType& str)
	{
		Assign(str.begin(), str.end());
	}

	template <u32 U>
	StaticString<N>& operator =(const StaticString<U>& str)
	{
		Assign(str.begin(), str.size());
		return *this;
	}

	template <class StringContainerType>
	StaticString<N>& operator =(const StringContainerType& str)
	{
		Assign(str.begin(), str.end());
		return *this;
	}

	StaticString<N>& operator =(const StaticString<N>& str) { Assign(str.begin(), str.size()); return *this; }
	StaticString<N>& operator =(const char* str) { Assign(str, Strnlen(str, kMaxCapacity)); return *this; }

	void Assign(const char* str) { Assign(str, Strnlen(str, kMaxCapacity)); }
	void Assign(const char* first, const char* last)
	{
		CE_ASSERT(first <= last);
		Assign(first, u32(last - first));
	}

	void Assign(const char* str, u32 stringLength)
	{
		CE_ASSERT(str != null);
		stringLength = (stringLength < (kMaxCapacity)) ? stringLength : (kMaxCapacity);
		Memory::Memcpy(m_data, str, stringLength);
		SetSize(stringLength);
	}

	constexpr u32 Capacity() const { return kMaxCapacity; }
	void Clear() { m_data[0] = 0; }
	bool Empty() const { return m_data[0] == 0; }
	u32 Size() const { return u32(kMaxCapacity - m_data[kMaxCapacity]); }
	u32 Length() const { return u32(kMaxCapacity - m_data[kMaxCapacity]); }
	const char* CString() const { return m_data; }


	char* begin() { return m_data; }
	const char* begin() const { return m_data; }
	char* end() { return m_data + Size(); }
	const char* end() const { return m_data + Size(); }

	u32 size() const { return u32(kMaxCapacity - m_data[kMaxCapacity]); }
	u32 length() const { return u32(kMaxCapacity - m_data[kMaxCapacity]); }
	char* data() { return m_data; }
	const char* data() const { return m_data; }
	const char* c_str() const { return m_data; }

	char&		operator [] (u32 index)			{ return m_data[index]; }
	const char& operator [] (u32 index) const	{ return m_data[index]; }

	int ToInt() const
	{
		return Strtoi(m_data);
	}

	float ToFloat() const
	{
		return Strtof(m_data);
	}

protected:
	void SetSize(u32 newSize)
	{
		CE_ASSERT(newSize < N);
		m_data[newSize] = (char)(kMaxCapacity - newSize);
	}

	char m_data[N];

};



// Binary operators

template <class StringContainerType, u32 N> inline
	bool operator ==(const StaticString<N>& a, const StringContainerType& b)
	{
		return (a == b.begin());
	}

template <class StringContainerType, u32 N> inline
	bool operator ==(const StringContainerType& a, const StaticString<N>& b)
	{
		return (b == a.begin());
	}

template <u32 N, u32 U> inline
	bool operator ==(const StaticString<N>& a, const StaticString<U>& b)
	{
		const u32 stringLength = N < U ? N : U;
		return (a.size() == b.size() && Memory::Memcmp(a.CString(), b.CString(), stringLength) == 0);
	}

template <u32 N, u32 U> inline
	bool operator !=(const StaticString<N>& a, const StaticString<U>& b)
	{
		return !(a == b);
	}

template <u32 N> inline
	bool operator ==(const StaticString<N>& a, const char* str)
	{
		const u32 stringLength = Strnlen(str, N - 1);
		return (a.size() == stringLength && Memory::Memcmp(a.begin(), str, stringLength) == 0);
	}

template <u32 N> inline
	bool operator !=(const StaticString<N>& a, const char* str)
	{
		return !(a == str);
	}

template <u32 N> inline
	bool operator ==(const char* str, const StaticString<N>& b)
	{
		return (b == str);
	}

template <u32 N> inline
	bool operator !=(const char* str, const StaticString<N>& b)
	{
		return !(b == str);
	}

template <u32 N, u32 U> inline
	bool operator <(const StaticString<N>& a, const StaticString<U>& b)
	{
		return Memory::Memcmp(a.begin(), a.size(), b.begin(), b.size()) < 0;
	}

template <u32 N> inline
	bool operator <(const StaticString<N>& a, const char* str)
	{
		const u32 stringLength = Strnlen(str);
		return Memory::Memcmp(a.begin(), a.size(), str, stringLength) < 0;
	}

template <u32 N> inline
	bool operator <(const char* str, const StaticString<N>& b)
	{
		const u32 stringLength = Strnlen(str);
		return Memory::Memcmp(str, stringLength, b.begin(), b.size()) < 0;
	}


