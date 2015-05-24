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


enum ThreadPriority
{
	ThreadPriority_Low,
	ThreadPriority_Normal,
	ThreadPriority_High
};


class CE_API Thread
{
public:
	typedef void (*FunctionPtr)(void*);

	/// Constructs the thread to an uninitialized state.
	/// The thread cannot be run until Create() is called.
	Thread();

	/// Destructor. Waits for thread to finish and joins it.
	virtual ~Thread();

	/// The function to run in the thread.
	virtual void Run() = 0;

	/// Creates the physical thread and returns true if successful.
	bool Create(u32 stackSize = 0);

	/// Starts running the thread.
	void Start();

	/// Stops the thread. Subsequent calls to ShouldRun() will return false.
	void Stop();

	/// Waits until the thread finishes execution and closes the thread.
	/// A new thread must be created with Create() before it can be started again.
	void Join();

	/// Returns whether the thread should keep on running.
	bool ShouldRun() const volatile;

	/// Returns whether the thread has finished running.
	bool HasFinished(void) const volatile;

	/// Set thread priority. This call does nothing unless Create() has been called first.
	void SetPriority(ThreadPriority priority);

	/// Return whether the OS thread exists.
	bool Exists() const { return m_handle != null; }

	/// Tells the calling thread to yield.
	//static void Yield();

	/// Tells the calling thread to sleep and give back a timeslice to the CPU.
	static void Sleep(u32 microseconds);

protected:
	void* m_handle;
	ThreadPriority m_threadPriority;
	volatile u32 m_threadID;
	volatile bool m_shouldRun;
};



CE_NAMESPACE_END

