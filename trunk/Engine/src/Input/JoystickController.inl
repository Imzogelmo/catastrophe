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

#include "Input/Common.h"
#include "Input/JoystickController.h"
#include "Input/Input.h"

CE_NAMESPACE_BEGIN


JoystickController::JoystickController() :
	m_joystick(0),
	m_joystick_id(0)
{
	// define the default controls here.
	m_button_map[0] = 0;
	m_button_map[1] = 1;
	m_button_map[2] = 2;
	m_button_map[3] = 3;
	m_button_map[4] = 4;
	m_button_map[5] = 5;
	m_button_map[6] = 6;
	m_button_map[7] = 7;
	m_button_map[8] = 8;
	m_button_map[9] = 9;
	m_button_map[10] = 10;
	m_button_map[11] = 11;

	m_direction_map[0] = 0;
	m_direction_map[1] = 1;
	m_direction_map[2] = 2;
	m_direction_map[3] = 3;

	m_joystick = Input::GetJoystick(m_joystick_id);
}


bool JoystickController::IsDown( int key ) const
{
	if( (u32)key < MaxButtons )
		return m_joystick->Button( m_button_map[key] );

	return false;
}


bool JoystickController::IsPressed( int key ) const
{
	if( (u32)key < MaxButtons )
		return InternalIsPressed( m_joystick->ButtonFrames( m_button_map[key] ) );

	return false;
}


bool JoystickController::IsReleased( int key ) const
{
	if( (u32)key < MaxButtons )
		return m_joystick->Released( m_button_map[key] );

	return false;
}


bool JoystickController::IsDPadDown( int dir ) const
{
	if( (u32)dir < MaxDirections )
		return m_directions[ m_direction_map[dir] ] > 0;

	return false;
}


bool JoystickController::IsDPadPressed( int dir ) const
{
	if( (u32)dir < MaxDirections )
		return InternalIsPressed( m_directions[ m_direction_map[dir] ] );

	return false;
}


bool JoystickController::IsDPadReleased( int dir ) const
{
	return false;
}


int JoystickController::Button( int key ) const
{
	if( (u32)key < MaxButtons )
		return m_joystick->Button( m_button_map[key] );

	return 0;
}


int JoystickController::DPad( int dir ) const
{
	if( (u32)dir < MaxDirections )
		return m_directions[ m_direction_map[dir] ];

	return 0;
}


Vector2 JoystickController::Analog( int analogStick ) const
{
	return m_joystick->Analog(analogStick);
}


float JoystickController::Axis( int axis ) const
{
	return m_joystick->Axis(axis);
}


void JoystickController::SetJoystick( int id )
{
	if( id < Input::MaxJoysticks )
	{
		m_joystick_id = id;
		m_joystick = Input::GetJoystick(m_joystick_id);
	}
}


void JoystickController::SetButtonMapping( int key, int value )
{
	if( (u32)key < MaxButtons )
	{
		if( value < MaxButtons )
			m_button_map[key] =  value;
	}
}


void JoystickController::SetDirMapping( int dir, int value )
{
	if( (u32)dir < MaxDirections )
	{
		if( value < MaxDirections )
			m_direction_map[dir] =  value;
	}
}


bool JoystickController::InternalIsPressed( int frames ) const
{
	if( m_use_key_repeat && frames >= m_key_repeat_delay )
	{
		return ((frames - m_key_repeat_delay) % m_key_repeat_rate) == 0;
	}

	return frames == 1;
}


void JoystickController::Update()
{
	int povFlags = m_joystick->GetPOV();

	if( povFlags & 0x01 ) m_directions[ m_direction_map[0] ]++;
	else m_directions[ m_direction_map[0] ] = 0;

	if( povFlags & 0x02 ) m_directions[ m_direction_map[1] ]++;
	else m_directions[ m_direction_map[1] ] = 0;

	if( povFlags & 0x04 ) m_directions[ m_direction_map[2] ]++;
	else m_directions[ m_direction_map[2] ] = 0;

	if( povFlags & 0x08 ) m_directions[ m_direction_map[3] ]++;
	else m_directions[ m_direction_map[3] ] = 0;
}


CE_NAMESPACE_END

