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

#include "../Common.h"

CE_NAMESPACE_BEGIN


#if defined(_MSC_VER)
	#define SwapByteOrder16 _byteswap_ushort
	#define SwapByteOrder32 _byteswap_ulong
	#define SwapByteOrder64 _byteswap_uint64
#elif defined(__GNUC__)
	inline u16 SwapByteOrder16(u16 value) { return (value << 8) | (value >> 8 ); }
	#define SwapByteOrder32 __builtin_bswap32
	#define SwapByteOrder64 __builtin_bswap64
#else
	inline u16 SwapByteOrder16(u16 value) { return (value << 8) | (value >> 8 ); }
	inline u32 SwapByteOrder32(u32 value)
	{
		return (((value << 24) & 0xff000000) |
				((value <<  8) & 0x00ff0000) |
				((value >>  8) & 0x0000ff00) |
				((value >> 24) & 0x000000ff));
	}

	inline u64 SwapByteOrder64(u64 value)
	{
		return (((value << 56) & 0xff00000000000000ULL) |
				((value << 40) & 0x00ff000000000000ULL) |
				((value << 24) & 0x0000ff0000000000ULL) |
				((value << 8)  & 0x000000ff00000000ULL) |
				((value >> 8)  & 0x00000000ff000000ULL) |
				((value >> 24) & 0x0000000000ff0000ULL) |
				((value >> 40) & 0x000000000000ff00ULL) |
				((value >> 56) & 0x00000000000000ffULL));
	}
#endif

// SwapByteOrder
template <class T, u32 NumBytes> inline void SwapByteOrder(T& value) {}
template <class T> inline void SwapByteOrder<T, 1>(T& value) {}
template <class T> inline void SwapByteOrder<T, 2>(T& value) { value = (T)SwapByteOrder16((u16)value); }
template <class T> inline void SwapByteOrder<T, 4>(T& value) { value = (T)SwapByteOrder32((u32)value); }
template <class T> inline void SwapByteOrder<T, 8>(T& value) { value = (T)SwapByteOrder64((u64)value); }



CE_NAMESPACE_END
