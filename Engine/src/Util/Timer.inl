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


#include "Util/Timer.h"
#include "timer_lib/timer.c"


bool Timer::m_timer_init = false;


Timer::Timer()
{
	if( !m_timer_init )
	{
		m_timer_init = true;
		timer_lib_initialize();
	}

	timer_initialize( (timer*)&m_time );
}


Timer::~Timer()
{
}


uint64 Timer::Frequency()
{
	return m_time.freq;
}


uint64 Timer::TicksPerSecond()
{
	return m_time.freq;
}


void Timer::Reset()
{
	timer_reset( (timer*)&m_time );
}


uint64 Timer::ElapsedTicks()
{
	return timer_elapsed_ticks( (timer*)&m_time, 0 );
}


uint64 Timer::ElapsedMinutes()
{
	return (ElapsedTicks() / TicksPerSecond()) / 60;
}


uint64 Timer::ElapsedSeconds()
{
	return ElapsedTicks() / TicksPerSecond();
}


uint64 Timer::ElapsedMilliseconds()
{
	return ((uint64)1000 * ElapsedTicks()) / TicksPerSecond();
}


uint64 Timer::ElapsedMicroseconds()
{
	return ((uint64)1000000 * ElapsedTicks()) / TicksPerSecond();
}


double Timer::MilliSeconds()
{
	return Seconds() * 1000.0;
}


double Timer::Seconds()
{
	return timer_elapsed( (timer*)&m_time, 0 );
}


double Timer::Minutes()
{
	return Seconds() / 60.0;
}




