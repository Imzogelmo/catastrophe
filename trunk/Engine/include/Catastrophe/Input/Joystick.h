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
#include "../Math/Vector2.h"
#include "JoystickConstants.h"

CE_NAMESPACE_BEGIN


class CE_API Joystick
{
public:
	enum
	{
		MaxJoysticks = 4,
		MaxButtons = 12,
		MaxAnalogs = 3,
		MaxAxes = MaxAnalogs << 1
	};

	Joystick() : m_analog_threshhold(0.1f), m_pov(0), m_buttonReleaseFlags(0), m_joyNumber(0), m_exists(true)
	{
		for( int i(0); i < MaxButtons; ++i )
			m_button[i] = 0;

		for( int i(0); i < MaxAnalogs; ++i )
			m_analog[i] = m_previous_analog[i] = Vector2::Zero;
	}

	bool Exists() const
	{
		return m_exists;
	}

	void SetExists( bool value = true )
	{
		m_exists = value;
	}

	//Sets the internal joystick number associated with this Object
	void SetJoystickNumber( int thisJoyNumber )
	{
		m_joyNumber = thisJoyNumber;
	}

	//Returns the internal joystick number associated with this Object
	int GetJoystickNumber() const
	{
		return m_joyNumber;
	}

	//Adds a dir flag to the current POV
	void SetPOV( int dir )
	{
		m_pov |= dir;
	}

	//Sets an analog stick to specified values
	void SetAnalog( int analogStick, Vector2 amount )
	{
		m_analog[ analogStick ] = amount;
	}

	//Sets an analog axis to specified value
	void SetAxis( int axis, float amount )
	{
		*(&m_analog[ 0 ].x + axis) = amount;
	}

	//Sets the button count to the specified amount
	void SetButton( int b, int amount )
	{
		m_button[ b ] = amount;
		m_buttonReleaseFlags &= ~( (int)(1 << b) );
	}

	//Returns true if the POV is pressed in the corresponding dir.
	bool POV( int dir ) const
	{
		return ((m_pov & dir) != 0);
	}

	//Returns true if the POV is pressed in the corresponding dir.
	int GetPOV() const
	{
		return (m_pov);
	}

	//Returns true if the button was just pressed this frame.
	bool Pressed( int b ) const
	{
		return (m_button[ b ] == 1);
	}

	//Returns true if the button was just released this frame.
	bool Released( int b ) const
	{
		return ((m_buttonReleaseFlags & ( 1 << b )) != 0);
	}

	//Returns true if the button is currently being pressed.
	bool Button( int b ) const
	{
		return (m_button[ b ] != 0);
	}
	
	//Returns the total number of frames this button has been held.
	int ButtonFrames( int b ) const
	{
		return m_button[ b ];
	}

	//Returns the specified analog x,y values in ranges of -1.0 - 1.0.
	Vector2 Analog( int analogStick ) const
	{
		return m_analog[ analogStick ];
	}

	//Returns the previous analog x,y values in ranges of -1.0 - 1.0.
	Vector2 PreviousAnalog( int analogStick ) const
	{
		return m_previous_analog[ analogStick ];
	}

	//Returns a single axis value between -1.0, 1.0.
	float Axis( int axis ) const
	{
		return (*(&m_analog[ 0 ].x + axis));
	}

	//Returns a previous axis value between -1.0, 1.0.
	float PreviousAxis( int axis ) const
	{
		return (*(&m_previous_analog[ 0 ].x + axis));
	}

	//Annuls joystick input for this frame.
	void AnnulJoystickInput()
	{
		AnnulAnalogInput();
		AnnulButtonInput();
		AnnulPOVInput();
	}

	//Annuls POV input for this frame.
	void AnnulPOVInput()
	{
		m_pov = (0x00000000);
	}

	//Annuls analog input for this frame.
	void AnnulAnalogInput()
	{
		for( int i(0); i < 3; ++i )
			m_analog[ i ] = 0.f;
	}

	//Annuls button input for this frame.
	void AnnulButtonInput()
	{
		for( int i(0); i < 32; ++i )
			m_button[ i ] = 0;

		m_buttonReleaseFlags = (0x00000000);
	}

	void SetAnalogThreshhold( float amount )
	{
		m_analog_threshhold = amount;
	}

	float GetAnalogThreshhold() const
	{
		return m_analog_threshhold;
	}

	void Update();


	int GetNumButtons() const { return MaxButtons; }
	int GetNumAnalogSticks() const { return MaxAnalogs; }
	int GetNumAxes() const { return 6; }
	int GetNumHats() const { return 1; }
	//bool HasPOV() const;

private:
	Vector2 m_analog[ MaxAnalogs ];
	Vector2 m_previous_analog[ MaxAnalogs ];
	float	m_analog_threshhold;
	int	m_button[ MaxButtons ];
	int	m_pov;
	int	m_buttonReleaseFlags;
	int	m_joyNumber;
	bool m_exists;

};

CE_NAMESPACE_END

