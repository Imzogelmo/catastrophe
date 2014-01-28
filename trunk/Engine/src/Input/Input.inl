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


#include "Common.h"
#include "Input/Input.h"


CE_NAMESPACE_BEGIN

Input Input::m_instance = Input();


Input::Input() :
	m_maxJoystickUsage(MaxJoysticks)
{
	for( int i(0); i < MaxJoysticks; ++i )
	{
		m_joysticks[i].SetExists(true);
		m_joysticks[i].SetJoystickNumber(i);
	}
}


void Input::SetMaxJoystickUsage( size_t numJoysticks )
{
	m_instance.m_maxJoystickUsage =
		Math::Clamp<size_t>(numJoysticks, 0, (size_t)MaxJoysticks);
}


void Input::Update()
{
	//update keyboard for key events.
	m_instance.m_keyboard.Update();

	for( size_t i(0); i < m_instance.m_maxJoystickUsage; ++i )
	{
		m_instance.m_joysticks[i].Update();
	}
}



CE_NAMESPACE_END
