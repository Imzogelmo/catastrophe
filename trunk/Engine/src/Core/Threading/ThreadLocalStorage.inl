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

#include "Catastrophe/Core/Threading/ThreadLocalStorage.h"

CE_NAMESPACE_BEGIN


ThreadLocalStorage::ThreadLocalStorage()
{
	m_index = (u32)TlsAlloc();

	if(m_index == TLS_OUT_OF_INDEXES) 
	{
		LogError("ThreadLocalStorage could not be allocated: Out of indexes.");
	}
}


ThreadLocalStorage::~ThreadLocalStorage()
{
	TlsFree((DWORD)m_index);
}


void ThreadLocalStorage::SetValue(void* value)
{
	if(TlsSetValue((DWORD)m_index, value) == FALSE)
	{
		LogError("ThreadLocalStorage: Value could not be set: Out of indexes.");
	}
}


void* ThreadLocalStorage::GetValue() const
{
	void* ptr = TlsGetValue((DWORD)m_index);
	return ptr;
}




CE_NAMESPACE_END

