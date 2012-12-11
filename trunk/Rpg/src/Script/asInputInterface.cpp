
#pragma once

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{
	Joystick* JoystickConstructor()
	{
		return Input::GetJoystick(0);
	}

	Keyboard* KeyboardConstructor()
	{
		return Input::GetKeyboard();
	}

	Mouse* MouseConstructor()
	{
		return Input::GetMouse();
	}

} //namespace script


void ScriptEngine::RegisterJoystick()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "joystick", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "joystick", asBEHAVE_FACTORY, "joystick@ f()", asFUNCTION(JoystickConstructor), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "joystick", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(JoystickConstructor), asCALL_CDECL );// assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "joystick", asBEHAVE_ADDREF, "void f()", asFUNCTION(DummyAddRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "joystick", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "joystick", "joystick &opAssign(const joystick&in)", asFUNCTION((RefAssignment<Joystick, Joystick>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "int get_num_buttons() const", asMETHOD(Joystick, GetNumButtons), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "int get_num_axes() const", asMETHOD(Joystick, GetNumAxes), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "int get_num_hats() const", asMETHOD(Joystick, GetNumHats), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "int get_button(int) const", asMETHOD(Joystick, ButtonFrames), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "bool get_button_down(int) const", asMETHOD(Joystick, Button), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "bool get_pressed(int) const", asMETHOD(Joystick, Pressed), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "bool get_released(int) const", asMETHOD(Joystick, Released), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "float get_axis(int) const", asMETHOD(Joystick, Axis), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "float get_previous_axis(int) const", asMETHOD(Joystick, PreviousAxis), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "vec2 get_analog(int) const", asMETHOD(Joystick, Analog), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "vec2 get_previous_analog(int) const", asMETHOD(Joystick, PreviousAnalog), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "int get_hat() const", asMETHOD(Joystick, GetPOV), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "joystick", "float get_threshhold() const", asMETHOD(Joystick, GetAnalogThreshhold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "void set_threshhold(float)", asMETHOD(Joystick, SetAnalogThreshhold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "joystick", "void annul()", asMETHOD(Joystick, AnnulJoystickInput), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterKeyboard()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "keyboard", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "keyboard", asBEHAVE_FACTORY, "keyboard@ f()", asFUNCTION(KeyboardConstructor), asCALL_CDECL ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "keyboard", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "keyboard &opAssign(const keyboard &in)", asFUNCTION((RefAssignment<Keyboard, Keyboard>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "int opIndex(int) const", asMETHOD(Keyboard, KeyFrames), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "keyboard", "int get_frames(int) const", asMETHOD(Keyboard, KeyFrames), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "bool get_down(int) const", asMETHOD(Keyboard, IsKeyDown), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "bool get_pressed(int) const", asMETHOD(Keyboard, IsKeyPressed), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "bool get_released(int) const", asMETHOD(Keyboard, IsKeyReleased), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "keyboard", "void annul()", asMETHOD(Keyboard, Annul), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterMouse()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "mouse", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("mouse", asBEHAVE_FACTORY, "mouse@ f()", asFUNCTION(MouseConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "mouse", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "mouse &opAssign(const mouse &in)", asFUNCTION((RefAssignment<Mouse, Mouse>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "int get_button(int) const", asMETHOD(Mouse, Button), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "bool get_pressed(int) const", asMETHOD(Mouse, Pressed), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "bool get_released(int) const", asMETHOD(Mouse, Released), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "point get_pos() const", asMETHOD(Mouse, GetPos), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "point get_previous() const", asMETHOD(Mouse, GetPrevious), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "int get_x() const", asMETHOD(Mouse, GetX), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "mouse", "int get_y() const", asMETHOD(Mouse, GetY), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterInput()
{
	int r(0);
	using namespace script;
	r = engine->SetDefaultNamespace("input"); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "::joystick@ get_joystick(int)", asFUNCTION(Input::GetJoystick), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "::mouse@ get_mouse()", asFUNCTION(Input::GetMouse), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "::keyboard@ get_keyboard()", asFUNCTION(Input::GetKeyboard), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "::keyboard@ get_key()", asFUNCTION(Input::GetKeyboard), asCALL_CDECL); assert( r >= 0 );
	r = engine->SetDefaultNamespace(""); assert( r >= 0 );
}


void ScriptEngine::RegisterInputInterface()
{
	RegisterJoystick();
	RegisterKeyboard();
	RegisterMouse();
	RegisterInput();
}

