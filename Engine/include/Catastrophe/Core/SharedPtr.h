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
#include "RefCounted.h"

#define SHAREDPTR_ASSERT(x) CE_ASSERT(x != null)

CE_NAMESPACE_BEGIN



/// @SharedPointer
///
/// Shared pointer class with intrusive reference counting.
/// (Is not responsible for the lifetime of the pointer)
///
/// Objects must inherit from RefCounted class or implement
/// internal reference counting. SharedPointer does not store
/// weak references and never allocates memory.
///

template <class T>
class SharedPtr
{
public:
	SharedPtr()
		: m_ptr(null)
		{
		}

	SharedPtr( const SharedPtr<T>& rhs )
		: m_ptr(rhs.m_ptr)
		{
			if( m_ptr )
				m_ptr->AddRef();
		}

	explicit SharedPtr( T* ptr )
		: m_ptr(ptr)
		{
			if( m_ptr )
				m_ptr->AddRef();
		}

	~SharedPtr()
		{
			if( m_ptr )
				m_ptr->ReleaseRef();
		}

	SharedPtr<T>& operator =( const SharedPtr<T>& p )
	{
		if( m_ptr != p.m_ptr )
			Reset(p.m_ptr);

		return *this;
	}

	template<class U>
	SharedPtr<T>& operator =( const SharedPtr<U>& p )
	{
		Reset((T*)p.m_ptr);
		return *this;
	}

	SharedPtr<T>& operator =( T* ptr )
	{
		if( m_ptr != ptr )
			Reset(ptr);

		return *this;
	}

	operator T*() const { return m_ptr; }
	operator bool() const { return m_ptr != null; }
	T* operator ->() const { SHAREDPTR_ASSERT(m_ptr); return m_ptr; }
	T& operator *() const { SHAREDPTR_ASSERT(m_ptr); return *m_ptr; }

	T* Get() const
	{
		return m_ptr;
	}

	void Reset( T* ptr = null )
	{
		if( m_ptr )
			m_ptr->ReleaseRef();

		m_ptr = ptr;
		if( m_ptr )
			m_ptr->AddRef();
	}

	bool IsValid() const
	{
		return m_ptr != null;
	}

protected:
	T* m_ptr;

};


template<class T, class U> inline
bool operator ==( const SharedPtr<T>& a, const SharedPtr<U>& b )
{
	return a.Get() == b.Get();
}

template<class T, class U> inline
bool operator !=( const SharedPtr<T>& a, const SharedPtr<U>& b )
{
	return a.Get() != b.Get();
}

template<class T, class U> inline
bool operator ==( const SharedPtr<T>& a, U* b )
{
	return a.Get() == b;
}

template<class T, class U> inline
bool operator !=( const SharedPtr<T>& a, U* b )
{
	return a.Get() != b;
}

template<class T, class U> inline
bool operator ==( T* a, const SharedPtr<U>& b )
{
	return a == b.Get();
}

template<class T, class U> inline
bool operator !=( T* a, const SharedPtr<U>& b )
{
	return a != b.Get();
}

template<class T> inline
bool operator <( const SharedPtr<T>& a, const SharedPtr<T>& b )
{
	return a.Get() < b.Get();
}



CE_NAMESPACE_END
