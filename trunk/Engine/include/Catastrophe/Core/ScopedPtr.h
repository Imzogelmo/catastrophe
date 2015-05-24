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

CE_NAMESPACE_BEGIN



// ScopedPtr

template <class T> 
class ScopedPtr
{
public:
	typedef T ElementType;

	explicit ScopedPtr( T* ptr = null )
		: m_ptr(ptr)
		{
		}

	~ScopedPtr()
		{
			DeletePtr();
		}

	operator bool() const { return m_ptr != null; }
	bool operator!() const { return m_ptr == null; }

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	T* Get() const { return m_ptr; }

	void Reset( T* ptr = null )
	{
		if( ptr != m_ptr )
		{
			DeletePtr();
			m_ptr = ptr;
		}
	}

	void DeletePtr() const
	{
		if(m_ptr != null)
		{
			delete m_ptr;
			m_ptr = null;
		}
	}

protected:
	ScopedPtr( const ScopedPtr& );
	ScopedPtr& operator=( const ScopedPtr& );
	ScopedPtr& operator=( T* ptr );

	T* m_ptr;
};


template <class T>
	bool operator <(const ScopedPtr<T>& a, const ScopedPtr<T>& b)
	{
		return (a.Get() < b.Get());
	}




// ScopedArrayPtr

template <class T> 
class ScopedArrayPtr
{
public:
	typedef T ElementType;

	explicit ScopedArrayPtr( T* ptr = null )
		: m_ptr(ptr)
		{
		}

	~ScopedArrayPtr()
		{
			DeletePtr();
		}

	operator bool() const { return m_ptr != null; }
	bool operator!() const { return m_ptr == null; }

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	T* Get() const { return m_ptr; }

	T& operator[]( int index ) const { return m_ptr[index]; }

	void Reset( T* ptr = null )
	{
		if( ptr != m_ptr )
		{
			DeletePtr();
			m_ptr = ptr;
		}
	}

	void DeletePtr() const
	{
		if(m_ptr != null)
		{
			delete [] m_ptr;
			m_ptr = null;
		}
	}

protected:
	ScopedArrayPtr( const ScopedArrayPtr& );
	ScopedArrayPtr& operator=( const ScopedArrayPtr& );
	ScopedArrayPtr& operator=( T* ptr );

	T* m_ptr;
};



template <class T>
	bool operator <( const ScopedArrayPtr<T>& a, const ScopedArrayPtr<T>& b )
	{
		return (a.Get() < b.Get());
	}



CE_NAMESPACE_END
