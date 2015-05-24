// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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


#if _MSC_VER
	extern "C" long __cdecl _InterlockedIncrement(long volatile*);
	extern "C" long __cdecl _InterlockedDecrement(long volatile*);
	extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
	extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
	extern "C" long __cdecl _InterlockedCompareExchange(long volatile*, long, long);

	#pragma intrinsic(_InterlockedIncrement)
	#pragma intrinsic(_InterlockedDecrement)
	#pragma intrinsic(_InterlockedExchange)
	#pragma intrinsic(_InterlockedExchangeAdd)
	#pragma intrinsic(_InterlockedCompareExchange)
#endif


namespace Atomic
{
	int Increment(volatile int* memory)
	{
		ASSERT_ALIGNED(memory, 4);
		return(int)_InterlockedIncrement((volatile long*)memory);
	}


	int Decrement(volatile int* memory)
	{
		ASSERT_ALIGNED(memory, 4);
		return(int)_InterlockedDecrement((volatile long*)memory);
	}


	int Add(volatile int* memory, int value)
	{
		ASSERT_ALIGNED(memory, 4);
		return(int)_InterlockedExchangeAdd((volatile long*)memory,(long)value);
	}


	int Exchange(volatile int* memory, int value)
	{
		ASSERT_ALIGNED(memory, 4);
		return(int)_InterlockedExchange((volatile long*)memory,(long)value);
	}


	int CompareExchange(volatile int* memory, int exchange, int comperand)
	{
		ASSERT_ALIGNED(memory, 4);
		return(int)_InterlockedCompareExchange((volatile long*)memory,(long)exchange,(long)comperand);
	}

} // namespace Atomic




/// AtomicCounter
///
/// Represents a thread safe integer.

class AtomicCounter
{
public:
	AtomicCounter() : m_value(0) {}
	AtomicCounter(int value) : m_value(value) {}
	AtomicCounter(const AtomicCounter& value) : m_value(value.m_value) {}

	operator int() const volatile { return m_value; }
	int operator =(int value) { Set(value); }

	inline int operator++()
	{
		return Atomic::Increment(&m_value);
	}

	inline int operator--()
	{
		return Atomic::Decrement(&m_value);
	}

	int Increment()
	{
		return Atomic::Decrement(&m_value);
	}

	int Decrement()
	{
		return Atomic::Decrement(&m_value);
	}

	int Add(int amount)
	{
		return Atomic::Add(&m_value, amount);
	}

	int Subtract(int amount)
	{
		return Atomic::Add(&m_value, -amount);
	}

	int Set(int value)
	{
		return Atomic::Exchange(&m_value, value);
	}

	int GetValue() const
	{
		return (int)m_value;
	}

private:
	void operator =(const AtomicCounter& Other){}

	volatile int m_value;
};



CE_NAMESPACE_END

