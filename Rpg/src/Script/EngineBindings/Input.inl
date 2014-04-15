// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.


#include <Catastrophe/Input.h>
#include <Catastrophe/Input/Keyboard.h>

#include "Script/MonoEngineBinding.h"


int MonoEngineBinding::Keyboard_GetKeyState( int key )
{
	return Input::GetKeyboard()->KeyFrames(key);
}


int MonoEngineBinding::Joystick_GetButtonState( int joystickID, int button )
{
	return Input::GetJoystick(joystickID)->ButtonFrames(button);
}


float MonoEngineBinding::Joystick_GetAxis( int joystickID, int axis )
{
	return Input::GetJoystick(joystickID)->Axis(axis);
}


Vector2 MonoEngineBinding::Joystick_GetAnalog( int joystickID, int analog )
{
	return Input::GetJoystick(joystickID)->Analog(analog);
}


int MonoEngineBinding::Joystick_GetDPad( int joystickID )
{
	return Input::GetJoystick(joystickID)->GetPOV();
}


void MonoEngineBinding::BindInput()
{
	SetNamespace("CatastropheEngine.Input.");

	AddInternalCall("Keyboard::GetKeyState", Keyboard_GetKeyState);

	AddInternalCall("Joystick::GetJoyButtonState", Joystick_GetButtonState);
	AddInternalCall("Joystick::GetJoyAxis", Joystick_GetAxis);
	AddInternalCall("Joystick::GetJoyAnalogStick", Joystick_GetAnalog);
	AddInternalCall("Joystick::GetJoyDPad", Joystick_GetDPad);

}

