
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

	MonoObject* CallObjectMethod( const char* decl, void** params = 0 );
	MonoObject* CallObjectVirtualMethod( const char* decl, void** params = 0 );

	void CallDefaultCtor();
	void CallUpdateMethod();
	void CallRenderMethod();

	MonoObject* GetMonoObjectPtr() { return m_object; }

protected:
	MonoObject*	m_object;
	uint32_t	m_gcHandle;

	MonoScriptClassInfo m_classInfo;

	//const char* m_name;
	//const char* m_namespace;

};


