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
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Iterator.h"

CE_NAMESPACE_BEGIN


///
/// StaticArray2D
///
/// A 2-dimensional constant array with x, y components stored 
/// in row-major order.
/// 

template <class T, u32 Y, u32 X>
struct StaticArray2D
{
	typedef T								ElementType;
	typedef T*								Iterator;
	typedef const T*						ConstIterator;
	typedef ReverseIterator<ConstIterator>	ConstReverseIterator;
	typedef ReverseIterator<Iterator>		ReverseIterator;

	enum
	{
		MaxSize = X * Y,
		kSizeBytes = MaxSize * sizeof(T)
	};

	//aggregate type

	constexpr u32 Size() const { return MaxSize; }

	Iterator begin()					{ return m_data; }
	ConstIterator begin() const			{ return m_data; }
	Iterator end()						{ return m_data + MaxSize; }
	ConstIterator end() const			{ return m_data + MaxSize; }

	ReverseIterator rend()				{ return ReverseIterator(begin()); }
	ConstReverseIterator rend() const	{ return ConstReverseIterator(begin()); }
	ReverseIterator rbegin()			{ return ReverseIterator(end()); }
	ConstReverseIterator rbegin() const { return ConstReverseIterator(end()); }

	T* Data()				{ return m_data; }
	const T* Data() const	{ return m_data; }

	T&			operator ()( u32 y, u32 x )			{ return m_data[ PointerOffset(y, x) ]; }
	const T&	operator ()( u32 y, u32 x ) const	{ return m_data[ PointerOffset(y, x) ]; }

	T& At( u32 y, u32 x )
	{
		FC_ASSERT(y < Y && x < X);
		return m_data[ PointerOffset(y, x) ];
	}

	const T& At( u32 y, u32 x ) const
	{
		FC_ASSERT(y < Y && x < X);
		return m_data[ PointerOffset(y, x) ];
	}

	Iterator IteratorOffset( u32 y, u32 x ) { return m_data + PointerOffset(y, x); }
	ConstIterator IteratorOffset( u32 y, u32 x ) const { return m_data + PointerOffset(y, x); }

	FORCEINLINE u32 PointerOffset( u32 y, u32 x ) const { return (x + y * X); }

	u32 Width() const { return X; }
	u32 Height() const { return Y; }

	void Assign( const ElementType& value )
	{
		FillValues( begin(), Size(), value );
	}

	bool IteratorIsValid( ConstIterator position ) const
	{
		return (position >= begin() && position <= end());
	}

	T m_data[MaxSize];
};


template <class T, u32 Y, u32 X> inline
	bool operator ==( const StaticArray2D<T, Y, X>& a, const StaticArray2D<T, Y, X>& b )
	{
		return( &a == &b || equal(a.begin(), a.end(), b.begin()) );
	}

template <class T, u32 Y, u32 X> inline
	bool operator !=( const StaticArray2D<T, Y, X>& a, const StaticArray2D<T, Y, X>& b )
	{
		return !(a == b);
	}


CE_NAMESPACE_END
