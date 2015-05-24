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


// CE_API - defaults to static lib.
//
// To compile as export dll - define CE_EXPORT.
// To compile as import dll - define CE_IMPORT.
// To compile directly into an application simply include "ce.cpp".
//
#if defined CE_EXPORT
	#define CE_API __declspec(dllexport)
#elif defined CE_IMPORT
	#define CE_API __declspec(dllimport)
#else
	#define CE_API
#endif

// Default alignment of machine pointer size
#define CE_DEFAULT_ALIGN sizeof(void*)

// String allocation size granularity.
// (Used for scaling string allocation requests to prevent further reallocations)
// For best performance this should match heap block min size. (Typically 8 or 16)
#define CE_DEFAULT_STRING_SIZE_ALIGNMENT	8


// Branch prediction macros. Best used sparingly.
#if defined(__GNUC__)
	#define CE_LIKELY(x) __builtin_expect((x), 1)
	#define CE_UNLIKELY(x) __builtin_expect((x), 0)
#else
	#define CE_LIKELY(x) (x)
	#define CE_UNLIKELY(x) (x)
#endif

#define LIKELY			CE_LIKELY
#define UNLIKELY		CE_UNLIKELY


// Microsoft
#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
	#define CE_PREFIX_ALIGN(n) __declspec(align(n))
	#define CE_POSTFIX_ALIGN(n)
	#define CE_PREFIX_DEPRECATED __declspec(deprecated)
	#define CE_POSTFIX_DEPRECATED
	#define CE_ALIGN(decl, value, n) __declspec(align(n)) decl value
	#define CE_ALIGNOF __alignof
	#define CE_PACKED
	#define CE_RESTRICT __restrict
	#define CE_FORCE_INLINE __forceinline
	#define CE_NO_INLINE __declspec(noinline)

// gcc
#elif defined(__GNUC__)
	#define CE_PREFIX_ALIGN(n)
	#define CE_POSTFIX_ALIGN(n) __attribute__((aligned(n)))
	#define CE_PREFIX_DEPRECATED
	#define CE_POSTFIX_DEPRECATED __attribute__((deprecated))
	#define CE_ALIGN(decl, value, n) decl value __attribute__((aligned(n)))
	#define CE_ALIGNOF(x) __alignof__(x)
	#define CE_PACKED __attribute__((packed))
	#define CE_RESTRICT __restrict
	#define CE_FORCE_INLINE inline __attribute__((always_inline))
	#define CE_NO_INLINE __attribute__((noinline))
#else

// Undefined
#error "Unknown Compiler"
#endif


#define FORCEINLINE		CE_FORCE_INLINE
#define NOINLINE		CE_NO_INLINE


#if defined (DEBUG) || defined (_DEBUG)
	#define CE_DEBUG 1
#endif

// Disable all the stupid dinkumware bullshit
#if defined(_MSC_VER)
	#define _HAS_ITERATOR_DEBUGGING 0
	#if !CE_DEBUG
		#define _HAS_EXCEPTIONS 0
		#define _SECURE_SCL 0
	#endif
#endif


// C++11
#if _MSC_VER < 1600
	#define null 0
	#define constexpr
#else
	#define null nullptr
#endif

// temporary workaround
#ifdef CE_NO_ENUM_TYPE
	#define ENUM_TYPE(_type)
#else
	#define ENUM_TYPE(_type) : _type
#endif


typedef char				sbyte;
typedef unsigned char		byte;
typedef unsigned long		ulong;
typedef unsigned int		uint;

#if defined(_MSC_VER)
	typedef __int8				s8;
	typedef __int16				s16;
	typedef __int32				s32;
	typedef __int64				s64;
	typedef unsigned __int8		u8;
	typedef unsigned __int16	u16;
	typedef unsigned __int32	u32;
	typedef unsigned __int64	u64;
	typedef float				f32;
	typedef double				f64;
#else
	typedef char				s8;
	typedef short				s16;
	typedef int					s32;
	typedef long long			s64;
	typedef unsigned char		u8;
	typedef unsigned short		u16;
	typedef unsigned int		u32;
	typedef unsigned long long	u64;
	typedef float				f32;
	typedef double				f64;
#endif


#ifndef INT_MAX_DEFINED
	#define INT_MAX_DEFINED

	#define INT8_MIN		-128
	#define INT16_MIN		-32768
	#define INT32_MIN		-2147483648
	#define INT64_MIN		-9223372036854775808

	#define INT8_MAX		127
	#define INT16_MAX		32767
	#define INT32_MAX		2147483647
	#define INT64_MAX		9223372036854775807

	#define UINT8_MAX		255
	#define UINT16_MAX		65535
	#define UINT32_MAX		4294967295
	#define UINT64_MAX		18446744073709551615 
#endif



// DebugBreak

#if defined(_MSC_VER)
	#define DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__)
	#define DEBUGBREAK() __builtin_trap()
#else
	#define DEBUGBREAK() __asm { int 3 }
#endif


/// If the assertion fails in debug mode it gets logged as an error and always breaks into the debugger.
/// If the assertion fails in release mode the affect is user defined.
/// Perhaps it should be logged and we exit the program, or perhaps Assert does nothing.

#ifdef CE_NO_ASSERT
	// CE_NO_ASSERT - Always disable assert macros
	#define ASSERT(x)
	#define DEBUG_ASSERT(x)
#else
	#if _DEBUG
		#define ASSERT(x) { if(UNLIKELY(!(x))) { NonInlinedDebugAssertLog(x, __LINE__, __FILE__, __FUNCTION__); DEBUGBREAK(); } }
		#define DEBUG_ASSERT(x) { if(UNLIKELY(!(x))) { NonInlinedDebugAssertLog(x, __LINE__, __FILE__, __FUNCTION__); DEBUGBREAK(); } }
	#else
		#define ASSERT(x)
		#define DEBUG_ASSERT(x)
	#endif
#endif

#define CE_ASSERT ASSERT


/// Assert that the memory is algned to a given alignment.
#define ASSERT_ALIGNED(memory, alignment) ASSERT(Memory::IsAligned(memory, alignment))


/// STATIC_ASSERT - This could be templated in the future to give better error messages.
#ifdef CE_DEBUG
	#define STATIC_ASSERT(x) typedef int assert_##_LINE_ [(x) * 2 - 1];
#else
	#define STATIC_ASSERT(x)
#endif


/// Minimum amount an uninitialized vector will allocate when a function is
/// called that expands its capacity. Example: Vector::Add(...);
/// By default this is set to 1 to keep memory compacted.
#ifndef CE_MIN_VECTOR_GROWTH
	#define CE_MIN_VECTOR_GROWTH 1
#endif


// ce namespace
#define CE_NAMESPACE_BEGIN namespace {} // namespace ce {
#define CE_NAMESPACE_END // }
#define USING_NAMESPACE_CE


CE_NAMESPACE_BEGIN

/// ~DO NOT USE DIRECTLY~
/// Used internally by ASSERT to log messages to error stream in the unlikely event an assertion has failed.
/// This function is not inlined to reduce bloat.
NOINLINE CE_API void NonInlinedDebugAssertLog( bool condition, int line, const char* file, const char* fn );

CE_NAMESPACE_END



