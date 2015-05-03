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


CE_NAMESPACE_BEGIN

///
/// @StaticArray
///
/// Constant compile-time array similar to that of
/// std::array.
///
template <class T, u32 N>
struct StaticArray
{
public:
	typedef T								ValueType;
	typedef T*								Iterator;
	typedef const T*						ConstIterator;
	typedef ReverseIterator<ConstIterator>	ConstReverseIterator;
	typedef ReverseIterator<Iterator>		ReverseIterator;

	enum
	{
		MaxSize = N,
		kSizeBytes = N * sizeof(T)
	};

	//aggregate type

	constexpr u32 Size() const { return N; }

	Iterator begin()					{ return &m_data[0]; }
	Iterator end()						{ return begin() + N; }
	ConstIterator begin() const			{ return &m_data[0]; }
	ConstIterator end() const			{ return begin() + N; }

	ReverseIterator rend()				{ return ReverseIterator(begin()); }
	ReverseIterator rbegin()			{ return ReverseIterator(end()); }
	ConstReverseIterator rend() const	{ return ConstReverseIterator(begin()); }
	ConstReverseIterator rbegin() const { return ConstReverseIterator(end()); }

	T* Data()				{ return &m_data[0]; }
	const T* Data() const	{ return &m_data[0]; }

	T& operator [](u32 index) { return m_data[index]; }
	const T& operator [](u32 index) const { return m_data[index]; }

	T& At(u32 index)
	{
		CE_ASSERT(index < Size());
		return m_data[index];
	}

	const T& At(u32 index) const
	{
		CE_ASSERT(index < Size());
		return m_data[index];
	}

	void Assign(const T& value)
	{
		Algorithm::FillValues(begin(), Size(), value);
	}

	bool IteratorIsValid(ConstIterator it) const
	{
		return (it >= begin() && it <= end());
	}

	T m_data[N ? N : 1];
};


template <class T, u32 N> inline
	bool operator ==(const StaticArray<T, N>& a, const StaticArray<T, N>& b)
	{
		return(&a == &b || Algorithm::Equal(a.begin(), a.end(), b.begin()));
	}

template <class T, u32 N> inline
	bool operator !=(const StaticArray<T, N>& a, const StaticArray<T, N>& b)
	{
		return !(a == b);
	}


CE_NAMESPACE_END
