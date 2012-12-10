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

#include "../Common.h"
#include "../Math/Point.h"

CE_NAMESPACE_BEGIN


class Mouse
{
public:
	enum
	{
		MaxMouseButtons = 3
	};

	Mouse() : m_pos(Point::Zero), m_previous(Point::Zero), m_wheel(0)
	{
		Annul();
	}

	//TODO: button,press,release.
	int Button( int button ) const
	{
		if( button < MaxMouseButtons )
			return m_button[button];

		return 0;
	}

	bool Pressed( int button ) const
	{
		return (button < MaxMouseButtons && m_button[button]);
	}

	bool Released( int button ) const
	{
		return !Pressed(button);
	}

	void SetButton( int button, bool pressed )
	{
		m_button[button] = pressed;
	}

	void SetPos( const Point& pos )
	{
		m_previous = m_pos;
		m_pos = pos;
	}

	void SetWheelPos( int pos )
	{
		m_wheel = pos;
	}

	void Annul()
	{
		m_wheel = 0;
		for( int i(0); i < MaxMouseButtons; ++i )
		{
			m_button[ i ] = false;
		}
	}

	Point GetPos() const { return m_pos; }
	Point GetPrevious() const { return m_previous; }
	int GetX() const { return m_pos.x; }
	int GetY() const { return m_pos.y; }
	int GetWheel() const { return m_wheel; }

	void Update();

private:
	Point	m_pos, m_previous;
	int		m_wheel;
	int		m_button[MaxMouseButtons];

};


CE_NAMESPACE_END

