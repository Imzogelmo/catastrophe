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
#include "Input/KeyboardController.h"
#include "Input/Input.h"

CE_NAMESPACE_BEGIN


KeyboardController::KeyboardController()
{
	// define the default controls here.
	m_button_map[0] = KEY_TAB;
	m_button_map[1] = KEY_Z;
	m_button_map[2] = KEY_X;
	m_button_map[3] = KEY_SPACE;
	m_button_map[4] = KEY_C;
	m_button_map[5] = KEY_V;
	m_button_map[6] = KEY_B;
	m_button_map[7] = KEY_N;
	m_button_map[8] = KEY_M;
	m_button_map[9] = KEY_J;
	m_button_map[10] = KEY_K;
	m_button_map[11] = KEY_L;

	m_direction_map[0] = KEY_UP;
	m_direction_map[1] = KEY_RIGHT;
	m_direction_map[2] = KEY_DOWN;
	m_direction_map[3] = KEY_LEFT;

	m_keyboard = Input::GetKeyboard();
}


bool KeyboardController::IsDown( int key ) const
{
	if( (size_t)key < MaxButtons )
		return m_keyboard->IsKeyDown( m_button_map[key] );

	return false;
}


bool KeyboardController::IsPressed( int key ) const
{
	return InternalIsPressed( m_button_map[key] );
}


bool KeyboardController::IsReleased( int key ) const
{
	if( (size_t)key < MaxButtons )
		return m_keyboard->IsKeyReleased( m_button_map[key] );

	return false;
}


bool KeyboardController::IsDPadDown( int dir ) const
{
	if( (size_t)dir < MaxDirections )
		return m_keyboard->IsKeyDown( m_direction_map[dir] );

	return false;
}


bool KeyboardController::IsDPadPressed( int dir ) const
{
	return InternalIsPressed( m_direction_map[dir] );
}


bool KeyboardController::IsDPadReleased( int dir ) const
{
	if( (size_t)dir < MaxDirections )
		return m_keyboard->IsKeyReleased( m_direction_map[dir] );

	return false;
}


int KeyboardController::Button( int key ) const
{
	if( (size_t)key < MaxButtons )
		return m_keyboard->KeyFrames( m_button_map[key] );

	return 0;
}


int KeyboardController::DPad( int dir ) const
{
	if( (size_t)dir < MaxDirections )
		return m_keyboard->KeyFrames( m_direction_map[dir] );

	return 0;
}


void KeyboardController::SetButtonMapping( int key, int value )
{
	if( (size_t)key < MaxButtons )
	{
		if( value < MAX_KEYS )
			m_button_map[key] =  value;
	}
}


void KeyboardController::SetDirMapping( int dir, int value )
{
	if( (size_t)dir < MaxDirections )
	{
		if( value < MAX_KEYS )
			m_direction_map[dir] =  value;
	}
}


bool KeyboardController::InternalIsPressed( int mapped_key ) const
{
	if( (size_t)mapped_key < MaxButtons )
	{
		if( m_use_key_repeat )
		{
			int frames = m_keyboard->KeyFrames( mapped_key );
			if( frames >= m_key_repeat_delay )
			{
				return ((frames - m_key_repeat_delay) % m_key_repeat_rate) == 0;
			}
			else
			{
				return frames == 1;
			}
		}
		else
		{
			return m_keyboard->IsKeyPressed( mapped_key );
		}
	}

	return false;
}


CE_NAMESPACE_END

