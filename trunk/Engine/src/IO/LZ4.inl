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

#include "lz4/lz4.c"
#include "lz4/lz4hc.c"

#include "IO/LZ4.h"
#include "IO/File.h"
#include "IO/Log.h"

CE_NAMESPACE_BEGIN


u32 LZ4::GetCompressionBounds( u32 inputSize )
{
	return (u32)LZ4_compressBound(inputSize);
}


u32 LZ4::CompressData( void* dest, const void* source, u32 sourceSize )
{
	CE_ASSERT(dest);
	CE_ASSERT(source);
	CE_ASSERT(sourceSize);

	return (u32)LZ4_compressHC((const char*)source, (char*)dest, (int)sourceSize);
}


u32 LZ4::DecompressData( void* dest, const void* source, u32 destSize )
{
	CE_ASSERT(dest);
	CE_ASSERT(source);
	CE_ASSERT(destSize);

	return (u32)LZ4_decompress_fast( (const char*)source, (char*)dest, (int)destSize );
}


CE_NAMESPACE_END

