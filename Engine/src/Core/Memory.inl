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

#include "Core/Memory.h"
#include "Core/Allocators/Allocator.h"

//#include <string.h> // clib header
//#include <stdlib.h> // clib header

CE_NAMESPACE_BEGIN


namespace Memory
{

	int allocationCount = 0;
	int deallocationCount = 0;

	// Default allocator.

	Allocator gDefaultAllocatorInstance;
	Allocator* gDefaultAllocatorInstancePtr = &gDefaultAllocatorInstance;

	Allocator* GetDefaultAllocator()
	{
		return gDefaultAllocatorInstancePtr;
	}

	void SetDefaultAllocator(Allocator* allocator)
	{
		CE_ASSERT(allocator != null);
		if(allocator != null)
			gDefaultAllocatorInstancePtr = allocator;
	}

} // Memory


CE_NAMESPACE_END

