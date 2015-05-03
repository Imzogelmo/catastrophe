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


/// Allocator
///
/// Simple virtual base Allocator that redirects all Allocate, Deallocate
/// calls to the equivalent global Allocate, Deallocate functions.

class Allocator
{
public:

	/// Allocates raw memory from this allocator.
	///
	/// @param  nBytes - The requested of bytes of memory
	/// @param  alignment - The additional alignment requirements of the memory, if any
	/// @return A pointer to raw block of memory
	///
	virtual void* Allocate( u32 nBytes, u32 alignment = 0 );

	
	/// Allows the allocator reclaim memory that was allocated by this allocator.
	///
	/// @param  ptr - pointer to block of memory
	/// @param  size - the number of bytes of the memory block
	///
	virtual void Deallocate( void* ptr, u32 size = 0 );

	// by default, all allocators are created equal.
	virtual bool operator ==( const Allocator& ) const { return true; }

	/// Allows the allocator pointer to propagate to other containers when copy-constructed.
	virtual bool AllowPropagation() const { return false; }
};



CE_NAMESPACE_END


