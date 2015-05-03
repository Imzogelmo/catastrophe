/* timer.h  -  v0.5  -  Public Domain  -  2011 Mattias Jansson / Rampant Pixels
 * 
 * This library provides a cross-platform interface to measure
 * elapsed time with (at least) millisecond accuracy.
 *
 * This library is put in the public domain; you can redistribute
 * it and/or modify it without any restrictions.
 *
 * VERSION HISTORY
 *
 * 0.1  (2011-03-15)  Initial release
 * 0.2  (2011-03-20)  Removed timer type (always high precision)
 *                    Fixed timer_ticks_per_second declaration
 *                    Added test application
 * 0.3  (2011-03-22)  Removed unused error checks in POSIX code
 *                    Made timeGetTime fallback optional in Windows code (define USE_FALLBACK to 1)
 *                    Fixed check of QPC weirdness (signed issue)
 * 0.4  (2011-03-23)  timer_lib_initialize() returns non-zero if failed (no high precision timer available)
 *                    Changed POSIX path to use CLOCK_MONOTONIC
 *                    POSIX timer_system use CLOCK_REALTIME for actual timestamp
 *                    Addded Mach-O path for MacOS X
 *                    Changed POSIX path to use nanosecond frequency as returned by clock_gettime
 * 0.5  (2012-10-01)  Merged (cleaned up) MacOSX build fixes from Nicolas Léveillé
 */

#pragma once

/*! \file timer.h
    Timer measuring deltatimes */

#if TIMER_COMPILE
#define TIMER_API
#else
#if __cplusplus
#define TIMER_API extern "C"
#else
#define TIMER_API extern
#endif
#endif

//! Deltaticks type
#if defined( _WIN32 ) || defined( _WIN64 )
typedef unsigned __int64 tick_t;
#else
#include <stdint.h>
typedef uint64_t tick_t;
#endif

//! Deltatime type (float or double)
//typedef float deltatime_t;
typedef double deltatime_t;

//! Timer
typedef struct
{
	//! Old clock
	tick_t         clock;

	//! Reference
	tick_t         ref;

	//! Ticks per second
	tick_t         freq;

	//! Multiplier ( 1 / frequency )
	deltatime_t    oofreq;
} timer;


/*! Initialize timer library */
TIMER_API int            timer_lib_initialize();

/*! Shutdown timer library */
TIMER_API void           timer_lib_shutdown();

/*! Initialize timer and reset
    \param t             Timer */
TIMER_API void           timer_initialize( timer* t );

/*! Reset timer
    \param t             Timer */
TIMER_API void           timer_reset( timer* t );

/*! Get elapsed time since last reset, and optionally reset timer
    \param t             Timer
    \param reset         Reset flag (reset if not zero)
    \return              Number of seconds elapsed */
TIMER_API deltatime_t    timer_elapsed( timer* t, int reset );

/*! Get elapsed ticks since last reset, and optionally reset timer
    \param t             Timer
    \param reset         Reset flag (reset if not zero)
    \return              Number of ticks elapsed */
TIMER_API tick_t         timer_elapsed_ticks( timer* t, int reset );

/*! Get timer frequency, as number of ticks per second
    \param t             Timer
    \return              Ticks per second */
TIMER_API tick_t         timer_ticks_per_second( timer* t );

/*! Get current time, in ticks of system-specific frequency. Measured from some system-specific base time and not in sync with other sytem timestamps
    \return              Current timestamp, in ticks */
TIMER_API tick_t         timer_current();

/*! Get frequency of current time ticks
    \return              Number of ticks per second for timer_current function */
TIMER_API tick_t         timer_current_ticks_per_second();

/*! Get system time, in milliseconds since the epoch (UNIX time)
    \return  Current timestamp, in milliseconds */
TIMER_API tick_t         timer_system();


//////////////////////////////////////////////////////////////////////////
#include "Core/Timer.h"

CE_NAMESPACE_BEGIN


bool Timer::m_timerInit = false;

Timer::Timer()
{
	if( !m_timerInit )
	{
		m_timerInit = true;
		timer_lib_initialize();
	}

	timer_initialize( (timer*)&m_time );
}


Timer::~Timer()
{
}


u64 Timer::Frequency()
{
	return m_time.freq;
}


u64 Timer::TicksPerSecond()
{
	return m_time.freq;
}


void Timer::Reset()
{
	timer_reset( (timer*)&m_time );
}


u64 Timer::ElapsedTicks()
{
	return timer_elapsed_ticks( (timer*)&m_time, 0 );
}


u64 Timer::ElapsedMinutes()
{
	return (ElapsedTicks() / TicksPerSecond()) / 60;
}


u64 Timer::ElapsedSeconds()
{
	return ElapsedTicks() / TicksPerSecond();
}


u64 Timer::ElapsedMilliseconds()
{
	return ((u64)1000 * ElapsedTicks()) / TicksPerSecond();
}


u64 Timer::ElapsedMicroseconds()
{
	return ((u64)1000000 * ElapsedTicks()) / TicksPerSecond();
}


f64 Timer::MilliSeconds()
{
	return Seconds() * 1000.0;
}


f64 Timer::Seconds()
{
	return timer_elapsed( (timer*)&m_time, 0 );
}


f64 Timer::Minutes()
{
	return Seconds() / 60.0;
}



CE_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////


/* timer.c  -  v0.5  -  Public Domain  -  2011 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform interface to measure
 * elapsed time with (at least) millisecond accuracy.
 *
 * This library is put in the public domain; you can redistribute
 * it and/or modify it without any restrictions.
 *
 * VERSION HISTORY
 *
 * 0.1  (2011-03-15)  Initial release
 * 0.2  (2011-03-20)  Removed timer type (always high precision)
 *                    Fixed timer_ticks_per_second declaration
 *                    Added test application
 * 0.3  (2011-03-22)  Removed unused error checks in POSIX code
 *                    Made timeGetTime fallback optional in Windows code (define USE_FALLBACK to 1)
 *                    Fixed check of QPC weirdness (signed issue)
 * 0.4  (2011-03-23)  timer_lib_initialize() returns non-zero if failed (no high precision timer available)
 *                    Changed POSIX path to use CLOCK_MONOTONIC
 *                    POSIX timer_system use CLOCK_REALTIME for actual timestamp
 *                    Addded Mach-O path for MacOS X
 *                    Changed POSIX path to use nanosecond frequency as returned by clock_gettime
 * 0.5  (2012-10-01)  Merged (cleaned up) MacOSX build fixes from Nicolas Léveillé
 */

#ifndef USE_FALLBACK
#define USE_FALLBACK 0
#endif

#if defined( _WIN32 ) || defined( _WIN64 )
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  if USE_FALLBACK
#  include <mmsystem.h>
#  endif
static tick_t _timerlib_curtime_freq  = 0;
#elif __APPLE__
#  include <mach/mach_time.h>
#  include <string.h>
static mach_timebase_info_data_t _timerlib_info;
#else
#  include <unistd.h>
#  include <time.h>
#  include <string.h>
#endif


int timer_lib_initialize()
{
#if defined( _WIN32 ) || defined( _WIN64 )
#if USE_FALLBACK
	timeBeginPeriod( 1U );
#endif
	tick_t unused;
	if( !QueryPerformanceFrequency( (LARGE_INTEGER*)&_timerlib_curtime_freq ) ||
		!QueryPerformanceCounter( (LARGE_INTEGER*)&unused ) )
		return -1;
#elif __APPLE__
	if( mach_timebase_info( &_timerlib_info ) )
		return -1;
#else
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	if( clock_gettime( CLOCK_MONOTONIC, &ts ) )
		return -1;
#endif
	return 0;
}


void timer_lib_shutdown()
{
#if defined( _WIN32 ) || defined( _WIN64 )
#if USE_FALLBACK
	timeEndPeriod( 1 );
#endif
#endif
}


void timer_initialize( timer* time )
{
	memset( time, 0, sizeof( time ) );

#if defined( _WIN32 ) || defined( _WIN64 )
	QueryPerformanceFrequency( (LARGE_INTEGER*)&time->freq );
#elif __APPLE__
	time->freq   = 1000000000;
#else
	time->freq   = 1000000000;
#endif
	time->oofreq = (deltatime_t)( 1.0 / (double)time->freq );

	timer_reset( time );
}

#if __APPLE__
static void absolutetime_to_nanoseconds (uint64_t mach_time, uint64_t* clock )
{
	*clock = mach_time * _timerlib_info.numer / _timerlib_info.denom;
}
#endif

void timer_reset( timer* time )
{
#if defined( _WIN32 ) || defined( _WIN64 )

	QueryPerformanceCounter( (LARGE_INTEGER*)&time->clock );
#if USE_FALLBACK
	time->ref = timeGetTime();
#endif

#elif __APPLE__

	absolutetime_to_nanoseconds( mach_absolute_time(), &time->clock );

#else

	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_MONOTONIC, &ts );
	time->clock = ( (tick_t)ts.tv_sec * 1000000000ULL ) + ts.tv_nsec;

#endif
}


deltatime_t timer_elapsed( timer* time, int reset )
{
	return (deltatime_t)timer_elapsed_ticks( time, reset ) * time->oofreq;
}


tick_t timer_elapsed_ticks( timer* time, int reset )
{
	tick_t dt = 0;

#if defined( _WIN32 ) || defined( _WIN64 )

	tick_t diff;
#if USE_FALLBACK
	tick_t refdiff;
	deltatime_t timerdiff;
	tick_t ref      = time->ref;
#endif
	tick_t curclock = time->clock;

	QueryPerformanceCounter( (LARGE_INTEGER*)&curclock );
#if USE_FALLBACK
	ref = timeGetTime();
#endif

	diff = curclock - time->clock;
#if USE_FALLBACK
	refdiff = ref - time->ref;

	if( ref < time->ref )
		refdiff = (tick_t)( 1000.0 * diff * time->oofreq ); //Catch looping of the millisecond counter

	timerdiff = (deltatime_t)( ( diff * time->oofreq ) - ( refdiff * 0.001 ) );
	if( ( diff < 0 ) || ( timerdiff > 0.1 ) || ( timerdiff < -0.1 ) )
		diff = (tick_t)( ( refdiff * 0.001 ) * time->freq ); //Performance counter messed up, transform reference to counter frequency
#endif

	dt = diff;

#if USE_FALLBACK
	if( reset )
		time->ref = ref;
#endif

#elif __APPLE__

	tick_t curclock = time->clock;
	absolutetime_to_nanoseconds( mach_absolute_time(), &curclock );

	dt = curclock - time->clock;

#else

	tick_t curclock;
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_MONOTONIC, &ts );

	curclock = ( (tick_t)ts.tv_sec * 1000000000ULL ) + ts.tv_nsec;

	dt = curclock - time->clock;

#endif

	if( reset )
		time->clock = curclock;

	return dt;
}


tick_t timer_ticks_per_second( timer* time )
{
	return time->freq;
}


tick_t timer_current()
{
#if defined( _WIN32 ) || defined( _WIN64 )

	//TODO: Fallback to timeGetTime for messed up perf counter values
	tick_t curclock;
	QueryPerformanceCounter( (LARGE_INTEGER*)&curclock );
	return curclock;

#elif __APPLE__

	tick_t curclock = 0;
	absolutetime_to_nanoseconds( mach_absolute_time(), &curclock );
	return curclock;

#else

	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_MONOTONIC, &ts );
	return ( (uint64_t)ts.tv_sec * 1000000000ULL ) + ts.tv_nsec;

#endif
}


tick_t timer_current_ticks_per_second()
{
#if defined( _WIN32 ) || defined( _WIN64 )
	return _timerlib_curtime_freq;
#elif __APPLE__
	return 1000000000;
#else
	return 1000000000;
#endif
}


#if defined( _WIN32 ) || defined( _WIN64 )
#  if _MSC_VER
#    include <sys/timeb.h>
#  else
struct __timeb64 {
	__time64_t time;
	unsigned short millitm;
	short timezone;
	short dstflag;
};
_CRTIMP errno_t __cdecl _ftime64_s(_Out_ struct __timeb64 * _Time);
#  endif
#endif

tick_t timer_system()
{
#if defined( _WIN32 ) || defined( _WIN64 )

	struct __timeb64 tb;
	_ftime64_s( &tb );
	return ( (tick_t)tb.time * 1000ULL ) + (tick_t)tb.millitm;

#elif __APPLE__

	tick_t curclock = 0;
	absolutetime_to_nanoseconds( mach_absolute_time(), &curclock );
	return ( curclock / 1000000ULL );

#else

	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_REALTIME, &ts );
	return ( (uint64_t)ts.tv_sec * 1000ULL ) + ( ts.tv_nsec / 1000000ULL );

#endif
}
