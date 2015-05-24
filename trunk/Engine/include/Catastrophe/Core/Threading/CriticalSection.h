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


class CE_API CriticalSection
{
public:
	CriticalSection();
	~CriticalSection();

	/// Enters a critical section.
	void Lock();

	/// Leave the critical section.
	void Unlock();

private:
	CriticalSection(const CriticalSection&);
	CriticalSection& operator = (const CriticalSection&);

	struct InternalMutexTypeBuffer {
		// This creates a buffer big enough to hold a platform specific mutex object.
		AlignedBuffer<(sizeof(void*) == 4) ? 24 : 40, sizeof(void*)> m_buffer;
	};

	InternalMutexTypeBuffer m_criticalSection;
};


class CE_API ScopedLock
{
public:
	typedef CriticalSection CriticalSection;

	/// Constructor which locks the assigned mutex.
	ScopedLock(CriticalSection* criticalSection) :
		m_pCriticalSection(criticalSection)
	{
		ASSERT(criticalSection != null);
		m_pCriticalSection->Lock();
	}

	/// Destructor which unlocks the assigned mutex.
	~ScopedLock()
	{
		m_pCriticalSection->Unlock();
	}

private:
	CriticalSection* m_pCriticalSection;

};


CE_NAMESPACE_END

