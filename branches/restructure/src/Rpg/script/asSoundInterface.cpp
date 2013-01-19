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


#include <cassert>
#include <angelscript.h>
#include <Engine/Sound.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"



namespace script
{
	Sound* SoundConstructor()
	{
		return 0;
	}

} //namespace script


void ScriptEngine::RegisterSound()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "sound", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("sound", asBEHAVE_FACTORY, "sound@ f()", asFUNCTION(SoundConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "sound", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "sound &opAssign(const sound &in)", asFUNCTION((RefAssignment<Sound, Sound>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void play(bool restart = true)", asMETHOD(Sound, Play), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void stop()", asMETHOD(Sound, Stop), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void release()", asMETHOD(Sound, Release), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "bool is_playing()", asMETHOD(Sound, IsPlaying), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "bool is_stopped()", asMETHOD(Sound, IsStopped), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sound", "bool is_valid()", asMETHOD(Sound, IsValid), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sound", "bool get_paused()", asMETHOD(Sound, IsPaused), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "bool get_loop()", asMETHOD(Sound, IsLooping), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "float get_volume()", asMETHOD(Sound, GetVolume), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "float get_pan()", asMETHOD(Sound, GetPan), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "int get_position()", asMETHOD(Sound, GetPosition), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "int get_length()", asMETHOD(Sound, GetLength), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sound", "void set_paused(bool)", asMETHOD(Sound, Pause), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void set_loop(bool)", asMETHOD(Sound, SetLooping), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void set_volume(float)", asMETHOD(Sound, SetVolume), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void set_pan(float)", asMETHOD(Sound, SetPan), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sound", "void set_position(int)", asMETHOD(Sound, SetPosition), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterSoundInterface()
{
	RegisterSound();
}


