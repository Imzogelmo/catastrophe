//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

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
