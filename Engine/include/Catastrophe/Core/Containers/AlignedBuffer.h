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


// AlignedBuffer: simple replacement for aligned_storage.

template <u32 N, u32 Alignment> struct AlignedBuffer { char data[N]; };
template <u32 N> struct AlignedBuffer<N, 2> { CE_ALIGN(char, data[N], 2); };
template <u32 N> struct AlignedBuffer<N, 4> { CE_ALIGN(char, data[N], 4); };
template <u32 N> struct AlignedBuffer<N, 8> { CE_ALIGN(char, data[N], 8); };
template <u32 N> struct AlignedBuffer<N, 16> { CE_ALIGN(char, data[N], 16); };
template <u32 N> struct AlignedBuffer<N, 32> { CE_ALIGN(char, data[N], 32); };
template <u32 N> struct AlignedBuffer<N, 64> { CE_ALIGN(char, data[N], 64); };
template <u32 N> struct AlignedBuffer<N, 128> { CE_ALIGN(char, data[N], 128); };


CE_NAMESPACE_END
