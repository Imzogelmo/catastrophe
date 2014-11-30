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

#include "Common.h"
#include "Controller.h"

CE_NAMESPACE_BEGIN


class CE_API JoystickController : public Controller
{
public:

	JoystickController();
	virtual ~JoystickController()
	{}

	bool IsDown( int key ) const;
	bool IsPressed( int key ) const;
	bool IsReleased( int key ) const;
	bool IsDPadDown( int dir ) const;
	bool IsDPadPressed( int dir ) const;
	bool IsDPadReleased( int dir ) const;

	int Button( int key ) const;
	int DPad( int dir ) const;

	Vector2 Analog( int analogStick ) const;
	float Axis( int axis ) const;

	void SetJoystick( int id );
	void SetButtonMapping( int key, int value );
	void SetDirMapping( int dir, int value );

	void Update();

protected:
	bool InternalIsPressed( int mapped_key ) const;

	Joystick*	m_joystick;
	u32		m_joystick_id;
	int			m_directions[MaxDirections];

};


CE_NAMESPACE_END
