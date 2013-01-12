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

#include <cstring>
#include "Input/Controller.h"


Controller::Controller() :
	m_key_repeat_delay(15),
	m_key_repeat_rate(4),
	m_use_key_repeat(true)
{
	::memset(m_button_map, 0, sizeof(int) * MaxButtons);
	::memset(m_direction_map, 0, sizeof(int) * MaxDirections);
}


void Controller::SetKeyRepeatDelay( int delay )
{
	if( delay < 0 )
		delay = 0;

	m_key_repeat_delay = delay;
}


void Controller::SetKeyRepeatRate( int rate )
{
	if( rate > 0 )
	{
		m_key_repeat_rate = rate;
	}
}


void Controller::UseKeyRepeat( bool enable )
{
	m_use_key_repeat = enable;
}

