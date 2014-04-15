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


#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include "Common.h"
#include "Script/MonoEngineBinding.h"
#include "Script/MonoUtils.h"


//
// @StaticString
//
// A StaticString is nothing but a safe wrapper around a cstring. The cstring is
// guaranteed to never move around in memory or become invalidated in any way, so
// this is very efficient.

MonoString* MonoEngineBinding::StaticString_ToString( const char* ptr )
{
	MonoString* str = mono_string_new(mono_domain_get(), ptr);
	return str;
}


void MonoEngineBinding::BindStaticString()
{
	mono_add_internal_call("CatastropheEngine.StaticString::ToString", StaticString_ToString);
}
