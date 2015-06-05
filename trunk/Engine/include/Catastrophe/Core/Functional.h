// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files ( the "Software" ), to deal
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


// arithmetic operations

template <class T>
struct Plus
{
	T operator()(const T& a, const T& b) const
	{ return a + b; }
};

template <class T>
struct Minus
{
	T operator()(const T& a, const T& b) const
	{ return a - b; }
};

template <class T>
struct Multiplies
{
	T operator()(const T& a, const T& b) const
	{ return a * b; }
};

template <class T>
struct Divides
{
	T operator()(const T& a, const T& b) const
	{ return a / b; }
};

template <class T>
struct Modulus
{
	T operator()(const T& a, const T& b) const
	{ return a % b; }
};

template <class T>
struct Negate
{
	T operator()(const T& a) const
	{ return -a; }
};


// comparison operations

template <class T>
struct EqualTo
{
	bool operator()(const T& a, const T& b) const
	{ return a == b; }
};

template <class T>
struct NotEqualTo
{
	bool operator()(const T& a, const T& b) const
	{ return a != b; }
};

template <class T>
struct Greater
{
	bool operator()(const T& a, const T& b) const
	{ return a > b; }
};

template <class T>
struct Less
{
	bool operator()(const T& a, const T& b) const
	{ return a < b; }
};

template <class T>
struct GreaterEqual
{
	bool operator()(const T& a, const T& b) const
	{ return a >= b; }
};

template <class T>
struct LessEqual
{
	bool operator()(const T& a, const T& b) const
	{ return a <= b; }
};


// logical operations

template <class T>
struct LogicalAnd
{
	bool operator()(const T& a, const T& b) const
	{ return a && b; }
};

template <class T>
struct LogicalOr
{
	bool operator()(const T& a, const T& b) const
	{ return a || b; }
};

template <class T>
struct LogicalNot
{
	bool operator()(const T& a) const
	{ return !a; }
};


// bitwise operations

template <class T>
struct BitwiseAnd
{
	T operator()(const T& a, const T& b) const
	{ return a & b; }
};

template <class T>
struct BitwiseOr
{
	T operator()(const T& a, const T& b) const
	{ return a | b; }
};

template <class T>
struct BitwiseXor
{
	T operator()(const T& a, const T& b) const
	{ return a ^ b; }
};



CE_NAMESPACE_END
