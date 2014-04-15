
#pragma once

// mono headers contain too many definitions and typedefs, some of which could
// potentially pollute other external header dependencies. Therefore it is
// safer to just forward declare what is needed.

#include <mono/metadata/object.h>


#define MONO_TRUE	1
#define MONO_FALSE	0
#define MONO_ASSERT(x)	FC_ASSERT(x)


/// Function signature: void method();
typedef void (__stdcall *UnmanagedThunkType0)(MonoObject*, MonoException**);


namespace MonoUtils
{

	// Debugging and path functions
	void HandleException( MonoObject* exception );
	void SetTraceLevel( const char* level );
	void SetDebugging();
	void SetDefaultSearchDirectories( const char* assemblyDirectory, const char* configDirectory );
	void SetAssembliesPath( const char* path );

	// AppDomain and assembly functions
	MonoDomain* CreateDomain( const char* name, const char* version = "v2.0.50727" );
	MonoAssembly* LoadAssembly( MonoDomain* domain, const char* filename );

	// Utility functions
	MonoObject* CallStaticMethod( MonoMethod* method, void** params = 0 );
	MonoObject* CallObjectMethod( MonoObject* object, MonoMethod* method, void** params = 0 );
	MonoObject* CallObjectUnmanagedThunk0( MonoObject* object, UnmanagedThunkType0 f );


	MonoClass* GetClassFromName( MonoAssembly* assembly, const char* namespaceName, const char* className );

	// Methods
	MonoMethod* GetClassMethodFromParams( MonoClass* monoClass, const char* name, int paramCount );
	MonoMethod* GetVirtualClassMethodFromParams( MonoClass* monoClass, const char* name, int paramCount );
	MonoMethod* GetClassMethodFromDecl( MonoClass* monoClass, const char* decl );
	MonoMethod* GetVirtualClassMethodFromDecl( MonoClass* monoClass, const char* decl );

	// Object fields
	void GetObjectField( MonoObject* object, const char* name, void* value );
	void SetObjectField( MonoObject* object, const char* name, void* value );
	void GetStaticClassField( MonoClass* monoClass, const char* name, void* value );
	void SetStaticClassField( MonoClass* monoClass, const char* name, void* value );

	// Arrays
	MonoArray* CreateNewArray( MonoClass* monoClass, int size );

	/// Gets the direct pointer to a class field of an object. 
	/// This function may not be portable or compatible with varying mono runtimes.
	inline void* UnsafeGetClassObjectFieldPtr( void* object, int offsetInBytes )
	{
		return (void*)((char*)object + sizeof(MonoObject) + offsetInBytes);
	}

	inline void* UnboxPtr( void* object )
	{
		return (void*)((char*)object + sizeof(MonoObject));
	}

}
