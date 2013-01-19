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

#include <assert.h>
#include "NonCopyable.h"


/* Singleton class.
 * Simply ensures that no derived class has more than one instance;
 */
template <class T>
class Singleton : public NonCopyable
{
public:
	Singleton()
	{
		assert(!m_instance && "Error: Singleton::Singleton There can be only one!");
		m_instance = static_cast<T*>(this);
	}

	~Singleton()
	{
		assert(m_instance && "Error: Singleton::~Singleton() : null instance");
		m_instance = 0;
	}

	static T& GetInstance()
	{
		assert(m_instance && "Error: Singleton must be instantiated first!");
		return *m_instance;
	}

	static T& GetInstancePtr()
	{
		assert(m_instance && "Error: Singleton must be instantiated first!");
		return m_instance;
	}

protected:
	static T* m_instance;

};


template<class T> T* Singleton<T>::m_instance = 0;

