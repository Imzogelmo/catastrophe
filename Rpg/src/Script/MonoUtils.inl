
#include <mono/jit/jit.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-config.h>

// mono logging and debugging
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/utils/mono-logger.h>
#include <stdlib.h>

#include "Common.h"
#include "MonoUtils.h"


namespace MonoUtils
{

	void HandleException( MonoObject* exception )
	{
		if( exception )
		{
			Log("An exception was caught: %s\n", mono_class_get_name(mono_object_get_class(exception)));
			mono_print_unhandled_exception(exception);
		}
	}


	void SetTraceLevel( const char* level )
	{
		mono_trace_set_mask_string("asm"); 
		mono_trace_set_level_string(level);
	}


	void SetDomainDebugging()
	{
		mono_debug_init(MONO_DEBUG_FORMAT_MONO);
		mono_debug_domain_create(mono_domain_get());
	}


	void SetDefaultSearchDirectories(const char* assemblyDirectory, const char* configDirectory)
	{
		// Default search paths for configuration and runtime components.
		// *note* On windows these are borked, and it is required to set mono_set_assemblies_path()
		// unless the user has the Mono runtime installed.

		mono_set_dirs(assemblyDirectory, configDirectory);
	}


	void SetAssembliesPath(const char* path)
	{
		// This is preferred over the default paths as Mono
		// will not append any paths over this string.

		mono_set_assemblies_path(path);
	}


	MonoDomain* CreateDomain( const char* name, const char* version )
	{
		// mono_jit_init creates the domain. Every assembly is loaded
		// and run in a single MonoDomain.

		MonoDomain* domain = mono_jit_init_version(name, version);
		if( !domain )
			Log("Fatal Error: application domain (%s) could not be created!", name);

		return domain;
	}


	MonoAssembly* LoadAssembly( MonoDomain* domain, const char* filename )
	{
		MonoAssembly* assembly = mono_domain_assembly_open(domain, filename);
		if( !assembly )
			Log("Error: Assembly could not be loaded from (%s)", filename);

		return assembly;
	}


	MonoObject* CallStaticMethod( MonoMethod* method, void** params )
	{
		// calling a static method is the exact same as calling an object method
		// except that the object pointer must be NULL.

		return CallObjectMethod((MonoObject*)0, method, params);
	}


	MonoObject* CallObjectMethod( MonoObject* object, MonoMethod* method, void** params )
	{
		MonoObject* exception = 0;
		MonoObject* retObject = mono_runtime_invoke(method, object, params, &exception);
		HandleException(exception);

		return retObject;
	}


	MonoObject* CallObjectUnmanagedThunk0( MonoObject* object, UnmanagedThunkType0 f )
	{
		if( f!= 0 )
		{
			MonoObject* exception = 0;
			f(object, (MonoException**)&exception);
			HandleException(exception);
		}

		return 0;
	}


	MonoClass* GetClassFromName( MonoAssembly* assembly, const char* namespaceName, const char* className )
	{
		MonoClass* monoClass = 0;
		if( assembly )
			monoClass = mono_class_from_name(mono_assembly_get_image(assembly), namespaceName, className);

		return monoClass;
	}


	MonoMethod* GetClassMethodFromParams( MonoClass* monoClass, const char* name, int paramCount )
	{
		MonoMethod* method = mono_class_get_method_from_name(monoClass, name, paramCount);
		return method;
	}


	MonoMethod* GetVirtualClassMethodFromParams( MonoClass* monoClass, const char* name, int paramCount )
	{
		MonoMethod* method = 0;
		for( MonoClass *parent = monoClass; parent != 0; parent = mono_class_get_parent(parent) )
		{
			method = mono_class_get_method_from_name(monoClass, name, paramCount);
			if( method )
				break;
		}

		return method;
	}


	MonoMethod* GetClassMethodFromDecl( MonoClass* monoClass, const char* decl )
	{
		MonoMethod* method = 0;
		MonoMethodDesc* methodDesc = mono_method_desc_new(decl, MONO_FALSE);
		if( methodDesc )
		{
			method = mono_method_desc_search_in_class(methodDesc, monoClass);
			mono_method_desc_free(methodDesc);
		}

		return method;
	}


	MonoMethod* GetVirtualClassMethodFromDecl( MonoClass* monoClass, const char* decl )
	{
		MonoMethod* method = 0;
		MonoMethodDesc* methodDesc = mono_method_desc_new(decl, MONO_FALSE);
		if( methodDesc )
		{
			for( MonoClass *parent = monoClass; parent != 0; parent = mono_class_get_parent(parent) )
			{
				method = mono_method_desc_search_in_class(methodDesc, parent);
				if( method )
					break;
			}

			mono_method_desc_free(methodDesc);
		}

		return method;
	}


	void GetObjectField(MonoObject* object, const char* name, void* value)
	{
		MonoClass* monoClass = mono_object_get_class(object);
		MonoClassField* field = mono_class_get_field_from_name(monoClass, name);
		
		mono_field_get_value(object, field, value);
	}


	void SetObjectField(MonoObject* object, const char* name, void* value)
	{
		MonoClass* monoClass = mono_object_get_class(object);
		MonoClassField* field = mono_class_get_field_from_name(monoClass, name);
		
		mono_field_set_value(object, field, value);
	}


	void GetStaticClassField(MonoClass* monoClass, const char* name, void* value)
	{
		MonoClassField* field = mono_class_get_field_from_name(monoClass, name);
		MonoVTable* vtable = mono_class_vtable(mono_domain_get(), monoClass);
		
		mono_field_static_get_value(vtable, field, value);
	}


	void SetStaticClassField(MonoClass* monoClass, const char* name, void* value)
	{
		MonoClassField* field = mono_class_get_field_from_name(monoClass, name);
		MonoVTable* vtable = mono_class_vtable(mono_domain_get(), monoClass);
		
		mono_field_static_set_value(vtable, field, value);
	}

	MonoObject* BoxValue( MonoClass* monoClass, void* value )
	{
		return mono_value_box(mono_domain_get(), monoClass, value);
	}

	MonoArray* CreateNewArray( MonoClass* monoClass, int size )
	{
		return mono_array_new(mono_domain_get(), monoClass, size);
	}

	/*
	MonoArray* ResizeArray( MonoArray* monoArray, int newSize )
	{
		int oldSize = (int)mono_array_length(monoArray);
		if( oldSize == newSize )
			return;

		MonoArray* newArray = mono_array_new(mono_domain_get(), m_pElementClass, size);

		for( int i(0); i < oldArraySize; ++i )
		{
			if(i < size)
			{
				mono_array_set_addr_with_size((MonoArray *)m_pObject, i, m_elementSize,
					*(void **)mono_array_addr_with_size(pOldArray, m_elementSize, i));
				m_lastIndex = i;
			}
		}
	}
	*/


} // namespace Mono


