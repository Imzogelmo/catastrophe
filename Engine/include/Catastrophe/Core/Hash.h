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
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/StaticString.h"

CE_NAMESPACE_BEGIN


inline u32 SdbmHash(const char* str)
{
	u32 hash = 0;
	u32 c;

	while(c = *str++)
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}


inline u32 Fnv32a( const char* str )
{
	u32 hash = 2166136261;
	if( LIKELY(str) )
	{
		for( const u8* p = (u8*)str; *p; ++p )
		{
			hash ^= *p;
			hash *= 16777619;
		}
	}

	return hash;
}



inline u32 MakeHash(const void* value) { return (u32)value; }
inline u32 MakeHash(s8 value) { return (u32)value; }
inline u32 MakeHash(s16 value) { return (u32)value; }
inline u32 MakeHash(s32 value) { return (u32)value; }
inline u32 MakeHash(s64 value) { return (value >> 32) | (value & 0xffffffff); }
inline u32 MakeHash(u8 value) { return (u32)value; }
inline u32 MakeHash(u16 value) { return (u32)value; }
inline u32 MakeHash(u32 value) { return value; }
inline u32 MakeHash(u64 value) { return (value >> 32) | (value & 0xffffffff); }

inline u32 MakeHash(const char* value)
{
	return Fnv32a(value);
}


inline u32 MakeHash(const String& value)
{
	return MakeHash(value.CString());
}


template <u32 N>
inline u32 MakeHash(const StaticString<N>& value)
{
	return MakeHash(value.CString());
}







CE_NAMESPACE_END


