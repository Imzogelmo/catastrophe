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
#include "Catastrophe/Core/PlatformString.h"

CE_NAMESPACE_BEGIN


class StringRef
{
public:
	typedef ReverseIterator<const char*>		ConstReverseIterator;
	typedef ReverseIterator<char*>				ReverseIterator;

	static const u32 npos = u32(-1);
	static const u32 MaxSize = u32(-2);

	StringRef()
		: m_begin(0), m_end(0)
		{
		}

	StringRef( const char* str, u32 stringLength )
		: m_begin((char*)str), m_end((char*)(str + stringLength))
		{
		}

	StringRef( const char* str )
		: m_begin((char*)str), m_end((char*)(str + Strlen(str)))
		{
		}

	StringRef( const StringRef& str )
		: m_begin(str.m_begin), m_end(str.m_end)
		{
		}

	StringRef( const char* first, const char* last )
		: m_begin((char*)first), m_end((char*)last)
		{
		}

	bool empty() const { return m_begin == m_end; }
	u32 size() const { return u32(m_end - m_begin); }
	u32 length() const { return u32(m_end - m_begin); }

	char&		operator [] ( u32 i )		{ return m_begin[i]; }
	const char& operator [] ( u32 i ) const	{ return m_begin[i]; }
	//char& at( u32 i ) { DebugAssert(i < size()); return m_begin[i]; }
	//const char& at( u32 i ) const { DebugAssert(i < size()); return m_begin[i]; }

	char&		front()			{ return *m_begin; }
	const char& front() const	{ return *m_begin; }
	char&		back()			{ return *(m_end - 1); }
	const char& back()	const	{ return *(m_end - 1); }
	char*		begin()			{ return m_begin; }
	const char*	begin() const	{ return m_begin; }
	char*		end()			{ return m_end; }
	const char*	end() const		{ return m_end; }
	ReverseIterator			rbegin()		{ return ReverseIterator(m_end); }
	ReverseIterator			rend()			{ return ReverseIterator(m_begin); }
	ConstReverseIterator	rbegin() const	{ return ConstReverseIterator(m_end); }
	ConstReverseIterator	rend() const	{ return ConstReverseIterator(m_begin); }

	char* data() { return m_begin; }
	const char*	data() const { return m_begin; }
	const char*	CString() const { return m_begin; }

protected:
	friend class String;

	char* m_begin;
	char* m_end;
};



// global operators

inline bool operator ==( const StringRef& a, const StringRef& b )
{
	return (a.size() == b.size() &&
		Memory::Memcmp( a.CString(), b.CString(), a.size()) == 0);
}

inline bool operator !=( const StringRef& a, const StringRef& b )
{
	return !(a == b);
}
/*
bool operator ==( const StringRef& a, const char* str )
{
	return a.compare(str) == 0;
}

bool operator !=( const StringRef& a, const char* str )
{
	return !(a == str);
}

bool operator ==( const char* str, const StringRef& b )
{
	return b.compare(str) == 0;
}

bool operator !=( const char* str, const StringRef& b )
{
	return !(b == str);
}

bool operator <( const StringRef& a, const StringRef& b )
{
	return a.compare(a.begin(), a.end(), b.begin(), b.end()) < 0;
}

bool operator <( const StringRef& a, const char* str )
{
	return a.compare(str) < 0;
}

bool operator <( const char* str, const StringRef& b )
{
	return b.compare(str) < 0;
}

bool operator >( const StringRef& a, const StringRef& b )
{
	return b < a;
}

bool operator >( const StringRef& a, const char* str )
{
	return str < a;
}

bool operator >( const char* str, const StringRef& b )
{
	return b < str;
}

bool operator <=( const StringRef& a, const StringRef& b )
{
	return !(b < a);
}

bool operator <=( const StringRef& a, const char* str )
{
	return !(str < a);
}

bool operator <=( const char* str, const StringRef& b )
{
	return !(b < str);
}

bool operator >=( const StringRef& a, const StringRef& b )
{
	return !(a < b);
}

bool operator >=( const StringRef& a, const char* str )
{
	return !(str < a);
}

bool operator >=( const char* str, const StringRef& b )
{
	return !(str < b);
}
*/



CE_NAMESPACE_END

