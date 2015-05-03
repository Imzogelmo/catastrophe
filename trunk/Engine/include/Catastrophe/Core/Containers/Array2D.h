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

#include "Array.h"

CE_NAMESPACE_BEGIN


///
/// Array2D
///
/// A 2-dimensional dynamic and resizable array with x, y components in row-major order.
/// (eg. array[y][x]) Resizing a 2D array will preserve the column
/// and row order of previous elements which makes it handy for use in
/// 2D games or graphics applications.
///

template <class T>
class Array2D : public Array<T>
{
public:
	typedef Array<T>								BaseType;
	typedef typename BaseType::ValueType			ValueType;
	typedef typename BaseType::Iterator				Iterator;
	typedef typename BaseType::ConstIterator		ConstIterator;

	using BaseType::Size;
	using BaseType::Empty;
	using BaseType::data;
	using BaseType::GetAllocator;
	using BaseType::SetAllocator;
	using BaseType::Fill;
	using BaseType::m_allocator;
	using BaseType::m_data;
	using BaseType::m_size;

	Array2D()
		: BaseType(), m_width(0), m_height(0)
		{
		}

	explicit Array2D(Allocator* allocator)
		: BaseType(allocator), m_width(0), m_height(0)
		{
		}

	explicit Array2D(u32 height, u32 width, const T& value = T(), Allocator* allocator = Memory::GetDefaultAllocator())
		: BaseType(width * height, value, allocator), m_width(width), m_height(height)
		{
		}

	Array2D(const Array2D<T>& x)
		: BaseType(x), m_width(x.m_width), m_height(x.m_height)
		{
		}

	T&			operator ()(u32 y, u32 x)			{ return m_data[ PointerOffset(y, x) ]; }
	const T&	operator ()(u32 y, u32 x) const		{ return m_data[ PointerOffset(y, x) ]; }

	T& at(u32 y, u32 x)
	{
		CE_ASSERT(y < m_height && x < m_width);
		return m_data[ PointerOffset(y, x) ];
	}

	const T& at(u32 y, u32 x) const
	{
		CE_ASSERT(y < m_height && x < m_width);
		return m_data[ PointerOffset(y, x) ];
	}

	Iterator		IteratorOffset(u32 y, u32 x)		{ return m_data + PointerOffset(y, x); }
	ConstIterator	IteratorOffset(u32 y, u32 x) const	{ return m_data + PointerOffset(y, x); }

	FORCEINLINE u32 PointerOffset(u32 y, u32 x) const { return (x + y * m_width); }

	FORCEINLINE u32 Width() const { return m_width; }
	FORCEINLINE u32 Height() const { return m_height; }

	NOINLINE void Resize(u32 height, u32 width, const T& value = T())
	{
		const u32 numElements = width * height;

		// Fast path - simply resize as a single array.
		if(numElements == 0 || m_size == 0 || m_width == width)
		{
			Array::Resize(numElements, value);
			m_width = width;
			m_height = height;
		}
		else
		{
			T* ptr = (T*)BaseType::Allocate(numElements);

			const u32 minWidth = Min(width, m_width);
			const u32 minHeight = Min(height, m_height);

			for(u32 i(0); i < minHeight; ++i)
			{
				T* dest = ptr + (i * width);
				T* source = IteratorOffset(i, 0);
				Memory::UninitializedCopy(source, source + minWidth, dest);

				if(m_width < width)
					Memory::UninitializedFillValues(dest, width - m_width, value);
			}

			// default initialize the remaining rows if we are expanding height
			if(height > m_height)
				Memory::UninitializedFillValues(ptr + (minHeight * width), (height - m_height) * width, value);

			Memory::DestroyRange(m_data, m_data + m_size);
			BaseType::Deallocate();

			m_data = ptr;
			m_size = numElements;
			m_width = width;
			m_height = height;
		}
	}

	void WriteRegion(u32 x, u32 y, u32 width, u32 height, const Array2D<T>& region_to_copy)
	{
		CE_ASSERT(x <= m_width);
		CE_ASSERT(y <= m_height);
		CE_ASSERT(width <= region_to_copy.Width());
		CE_ASSERT(height <= region_to_copy.Height());

		if(x + width > m_width)
			width = m_width - x;
		if(y + height > m_height)
			height = m_height - y;

		for(u32 i(0); i < height; ++i)
		{
			ConstIterator it = region_to_copy.IteratorOffset(i, 0);
			Algorithm::Copy(it, it + width, IteratorOffset(y + i, x));
		}
	}

	void CopyRegion(u32 x, u32 y, u32 width, u32 height, Array2D<T>& out_region) const
	{
		CE_ASSERT(x + width <= m_width);
		CE_ASSERT(y + height <= m_height);

		if(out_region.Width() < width || out_region.Height() < height)
			out_region.Resize(height, width);

		for(u32 i(0); i < height; ++i)
		{
			ConstIterator it = IteratorOffset(y + i, x);
			Algorithm::Copy(it, it + width, out_region.IteratorOffset(i, 0));
		}
	}

	Array2D<T> SubArray(u32 x, u32 y, u32 width, u32 height) const
	{
		Array2D<T> x;
		CopyRegion(x, y, width, height, x);
		return x;
	}

	Array2D<T>& operator =(const Array2D<T> &x)
	{
		BaseType::operator =(x);
		m_width = x.m_width;
		m_height = x.m_height;
		return *this;
	}

protected:
	u32 m_width;
	u32 m_height;
};



template <class T> inline
	bool operator ==(const Array2D<T>& a, const Array2D<T>& b)
	{
		return(&a == &b || (a.Width() == b.Width() && a.Height() == b.Height() &&
			Algorithm::Equal(a.begin(), a.end(), b.begin())));
	}

template <class T> inline
	bool operator !=(const Array2D<T>& a, const Array2D<T>& b)
	{
		return !(a == b);
	}



CE_NAMESPACE_END
