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

#pragma once

#include "MonoUtils.h"

#include <fc/common.h>
#include <fc/type_traits.h>



/// @MonoScriptClassInfo
///
/// Contains an MonoScriptObject information cache for fast
/// lookup of class methods and method calls.

struct MonoScriptClassInfo
{
	MonoClass* classType;

	// callback function pointer types
	UnmanagedThunkType0 ctorMethod;
	UnmanagedThunkType0 updateMethod;
	UnmanagedThunkType0 renderMethod;
	//UnmanagedThunkType0 onCreateMethod;
	//UnmanagedThunkType0 onDestroyMethod;

};


// Fast memory access.
FC_MAKE_TRAIT(MonoScriptClassInfo, is_pod);



/// @MonoScriptObject
///
/// Represents an instance of a class instantiated within Mono
/// and contains methods for managing that instance.

class MonoScriptObject
{
public:
	MonoScriptObject( const MonoScriptClassInfo& classInfo );
	MonoScriptObject( MonoObject* object, MonoScriptClassInfo& classInfo );
	~MonoScriptObject();

	MonoObject* CallObjectMethod( const char* decl, void** params = null );
	MonoObject* CallObjectVirtualMethod( const char* decl, void** params = null );

	void CallDefaultCtor();
	void CallUpdateMethod();
	void CallRenderMethod();

	MonoObject* GetMonoObjectPtr() const { return m_object; }
	MonoScriptClassInfo* GetClassInfo() const { return const_cast<MonoScriptClassInfo*>(&m_classInfo); }

protected:
	MonoObject*			m_object;
	u32					m_gcHandle;
	MonoScriptClassInfo	m_classInfo;

	//const char* m_name;
	//const char* m_namespace;

};


