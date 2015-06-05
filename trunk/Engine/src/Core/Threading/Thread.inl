
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
#include "Catastrophe/Core/Threading/Thread.h"


#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#define NOGDI
	#include <winbase.h>
#else
	#include <pthread.h>
#endif


CE_NAMESPACE_BEGIN


#ifdef WIN32
	DWORD WINAPI ThreadStaticRunFunction(void* ptr)
	{
		Thread* thread = (Thread*)ptr;
		thread->Run();
		return 0;
	}
#else
#endif


Thread::Thread() :
	m_handle(null),
	m_threadPriority(ThreadPriority_Normal),
	m_threadID(0),
	m_shouldRun(false)
{
}


Thread::~Thread()
{
	Join();
}


bool Thread::Create(u32 stackSize)
{
	// Thread was already created. 
	ASSERT(m_handle == null);
	if(m_handle == null)
		return false;

#ifdef WIN32
	m_handle = (void*)CreateThread(
		0,
		stackSize,
		ThreadStaticRunFunction,
		(LPVOID)this,
		CREATE_SUSPENDED,
		(LPDWORD)&m_threadID
	);
#endif

	if(m_handle != null)
		m_shouldRun = true;

	return m_shouldRun;
}


void Thread::Start()
{
	ASSERT(m_handle != null);
	if(m_handle == null)
	{
		LogError("Error: Thread handle is null. Thread::Create must be called before a thread can be run.");
		return;
	}

#ifdef WIN32
	ResumeThread((HANDLE)m_handle);
#endif

	m_shouldRun = false;
}


void Thread::Stop()
{
	ASSERT(m_handle != null);

#ifdef WIN32
	SuspendThread((HANDLE)m_handle);
#endif

	m_shouldRun = false;
}


void Thread::Join()
{
	// Check if already joined
	if(m_handle == null)
		return;

#ifdef WIN32
	WaitForSingleObject((HANDLE)m_handle, INFINITE);
	CloseHandle((HANDLE)m_handle);
#endif

	m_shouldRun = false;
	m_handle = null;
}


bool Thread::ShouldRun() const volatile
{
	return m_shouldRun;
}


/*
void Thread::Yield() const
{
#ifdef WIN32
	::Sleep(0);
#else
	pthread_yield();
	//sched_yield();
#endif
}
*/

void Thread::Sleep(u32 microseconds)
{
	HANDLE timer; 
	LARGE_INTEGER ft; 

	// Convert to 100 nanosecond interval, negative value indicates relative time
	ft.QuadPart = -(10 * (int)microseconds);

	timer = CreateWaitableTimerA(NULL, TRUE, NULL); 
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
	WaitForSingleObject(timer, INFINITE); 
	CloseHandle(timer); 

#ifdef WIN32
	::Sleep(microseconds / 1000);
#else
	usleep(microseconds);
#endif
}


void Thread::SetPriority(ThreadPriority priority)
{
	if(m_handle == null || m_threadPriority == priority)
		return;

#ifdef WIN32
	int osPriorityLevel;
	switch(priority)
	{
		case ThreadPriority_Low: osPriorityLevel = THREAD_PRIORITY_BELOW_NORMAL; break;
		case ThreadPriority_High: osPriorityLevel = THREAD_PRIORITY_ABOVE_NORMAL; break;
		case ThreadPriority_Normal:
		default:
		{
			osPriorityLevel = THREAD_PRIORITY_NORMAL;
			break;
		}
	}

	if(::SetThreadPriority((HANDLE)m_handle, osPriorityLevel) == TRUE)
		m_threadPriority = priority;
#endif
}


CE_NAMESPACE_END

