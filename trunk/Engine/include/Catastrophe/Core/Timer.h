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
 * -uses timer_lib under the hood for portability.
 */
class CE_API Timer
{
public:
	struct Time
	{
		uint64 clock;
		uint64 ref;
		uint64 freq;
		double oofreq;
	};

	Timer();
	~Timer();

	void Reset();
	uint64 Frequency();
	uint64 TicksPerSecond();

	uint64 ElapsedTicks();
	uint64 ElapsedMinutes();
	uint64 ElapsedSeconds();
	uint64 ElapsedMilliseconds();
	uint64 ElapsedMicroseconds();

	double MilliSeconds();
	double Seconds();
	double Minutes();

protected:
	Time		m_time;
	static bool m_timer_init;
};

