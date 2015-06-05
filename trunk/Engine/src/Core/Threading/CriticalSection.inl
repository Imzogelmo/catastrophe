
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
#include "Catastrophe/Core/Threading/CriticalSection.h"


#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinBase.h>
#else
#include <pthread.h>
#endif


CE_NAMESPACE_BEGIN


CriticalSection::CriticalSection()
{
#ifdef WIN32
	InitializeCriticalSection((CRITICAL_SECTION*)&m_criticalSection);
#else
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
	pthread_mutex_init((pthread_mutex_t*)&m_criticalSection, &attr);
	//pthread_mutexattr_destroy(&attr);
#endif
}


CriticalSection::~CriticalSection()
{
#ifdef WIN32
	DeleteCriticalSection((CRITICAL_SECTION*)&m_criticalSection);
#else
	pthread_mutex_destroy((pthread_mutex_t*)&m_criticalSection);
#endif
}


void CriticalSection::Lock()
{
#ifdef WIN32
	EnterCriticalSection((CRITICAL_SECTION*)&m_criticalSection);
#else
	pthread_mutex_lock((pthread_mutex_t*)&m_criticalSection);
#endif
}


void CriticalSection::Unlock()
{
#ifdef WIN32
	LeaveCriticalSection((CRITICAL_SECTION*)&m_criticalSection);
#else
	pthread_mutex_unlock((pthread_mutex_t*)&m_criticalSection);
#endif
}



CE_NAMESPACE_END

