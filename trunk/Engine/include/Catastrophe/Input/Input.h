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

#include "Joystick.h"
#include "Keyboard.h"
#include "Mouse.h"


CE_NAMESPACE_BEGIN


class CE_API Input
{
public:
	enum
	{
		MaxKeys			= MAX_KEYS,
		MaxJoysticks	= 4
	};

	Input();

	static Input* GetInstance() { return &m_instance; }
	static void SetMaxJoystickUsage( size_t numJoysticks );

	static Keyboard* GetKeyboard() { return &m_instance.m_keyboard; }
	static Mouse* GetMouse() { return &m_instance.m_mouse; }
	static Joystick* GetJoystick(size_t index)
	{
		CE_ASSERT(index < MaxJoysticks);
		return &m_instance.m_joysticks[index];
	}

	static void Update();

private:
	Joystick		m_joysticks[MaxJoysticks];
	Keyboard		m_keyboard;
	Mouse			m_mouse;
	size_t			m_maxJoystickUsage;

	static Input	m_instance;
};



CE_NAMESPACE_END