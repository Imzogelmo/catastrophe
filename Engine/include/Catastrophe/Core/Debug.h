// Permission is hereby granted, free of charge, to any person obtaining a Copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, Copy, modify, merge, publish, distribute, sublicense, and/or sell
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


// DebugBreak

#if defined(_MSC_VER)
	#define DebugBreak() __debugbreak()
#elif defined(__GNUC__)
	#define DebugBreak() __builtin_trap()
#else
	#define DebugBreak() __asm { int 3 }
#endif


/// DO NOT USE DIRECTLY!
/// Used internally by ASSERT to log messages to error stream in the unlikely event an assertion has failed.
/// This function is not inlined to reduce bloat.
NOINLINE void NonInlinedDebugAssertLog( bool condition, int line, const char* file, const char* fn )
{
	// Log the assertion failure and break into the debugger where it failed if Assert is called.
	if( FC_UNLIKELY(!condition) )
		LogError("Assertion failed! Line %i, File: %s, Function: %s", line, file, fn);
}


/// DEBUG: If the assertion fails in debug mode it gets logged as an error and
/// always breaks into the debugger.
/// RELEASE: If the assertion fails in release mode the affect is user defined,
/// perhaps it should be logged and we exit the program, or perhaps Assert does nothing.

#if DEBUG
#define ASSERT(x) if(FC_UNLIKELY(!(x))) { NonInlinedDebugAssertLog(x, __LINE__, __FILE__, __FUNCTION__); DebugBreak(); }
#define DEBUG_ASSERT(x) if(FC_UNLIKELY(!(x))) { NonInlinedDebugAssertLog(x, __LINE__, __FILE__, __FUNCTION__); DebugBreak(); }
#else
#define ASSERT(x)
#define DEBUG_ASSERT(x)
#endif

