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

CE_NAMESPACE_BEGIN


class CE_API Controller
{
public:
	struct Button
	{
		enum Buttons
		{
			X,
			A,
			B,
			Y,
			L1,
			R1,
			L2,
			R2,
			Select,
			Start,
			L3,
			R3
		};
	};

	struct Dir
	{
		enum Directions
		{
			Up,
			Right,
			Down,
			Left
		};
	};

	enum ControllerTypes
	{
		TypeKeyboard,
		TypeJoystick
	};

	enum : size_t
	{
		MaxButtons = 12,
		MaxDirections = 4,
		MaxAnalogs = 3,
		MaxAxis = MaxAnalogs << 1
	};

	Controller();
	virtual ~Controller()
	{}

	virtual bool IsDown( int key ) const = 0;
	virtual bool IsPressed( int key ) const = 0;
	virtual bool IsReleased( int key ) const = 0;
	virtual bool IsDPadDown( int dir ) const = 0;
	virtual bool IsDPadPressed( int dir ) const = 0;
	virtual bool IsDPadReleased( int dir ) const = 0;

	virtual int Button( int key ) const = 0;
	virtual int DPad( int dir ) const = 0;

	virtual void Update() {}
	virtual void SetJoystick( int id ) {}
	virtual void SetButtonMapping( int key, int value ) = 0;
	virtual void SetDirMapping( int dir, int value ) = 0;
	virtual void SetKeyRepeatDelay( int delay );
	virtual void SetKeyRepeatRate( int rate );
	virtual void UseKeyRepeat( bool enable = true );

protected:
	int		m_button_map[MaxButtons];
	int		m_direction_map[MaxDirections];
	int		m_key_repeat_delay;
	int		m_key_repeat_rate;
	bool	m_use_key_repeat;
};


CE_NAMESPACE_END
