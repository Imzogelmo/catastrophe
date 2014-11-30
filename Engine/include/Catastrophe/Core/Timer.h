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

/**
 * High performance timer class.
 * Uses timer_lib under the hood for portability.
 */
class CE_API Timer
{
public:
	struct Time
	{
		u64 clock;
		u64 ref;
		u64 freq;
		f64 oofreq;
	};

	Timer();
	~Timer();

	void Reset();

	u64 Frequency();
	u64 TicksPerSecond();

	u64 ElapsedTicks();
	u64 ElapsedMinutes();
	u64 ElapsedSeconds();
	u64 ElapsedMilliseconds();
	u64 ElapsedMicroseconds();

	f64 MilliSeconds();
	f64 Seconds();
	f64 Minutes();

protected:
	Time		m_time;
	static bool m_timerInit;
};


